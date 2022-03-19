#include "communications.h"
#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFi.h>
#include <ESPmDNS.h>

//#define TIME_BETWEEN_CONFIG_PORTAL_LOOP 1L  // Adding this define to include a delay to avoid the Task Watchdog reset
//#include <ESPAsyncWebserver.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

const int  WIFI_MODE_PIN = 0;

//#define ALWAYS_AP
#ifndef ALWAYS_AP
WiFiManager wifiManager;
#endif

void configModeCallback (WiFiManager *myESP_WiFiManager)
{
  Serial.print(F("Entered WifiManager config mode"));
  //Serial.println(("AP_SSID : ") + myESP_WiFiManager->getConfigPortalSSID() + (" and AP_PASS = ") + myESP_WiFiManager->getConfigPortalPW());
}

static int communicationsTaskCore = 0;
static int COMMUNICATION_TASK_PRIO = 5;
static long COMMUNICATION_TASK_PERIOD = 50;

#define MAX_SRV_CLIENTS 1
#define TCP_PORT        8080
const char *ssid = "PWDTIMER";
const char *password = "PWDTIMER";
WiFiServer server(TCP_PORT);
WiFiClient serverClients[MAX_SRV_CLIENTS];


static int QUEUE_SIZE = 10;
QueueHandle_t xQueueSendMessages;
QueueHandle_t xQueueRecvMessages;

void processTCPserverConnections();

void communicationsCoreTask( void * pvParameters ){
  // Setup serial communications
  Serial.begin(115200);

  // Setup TCP communications
#ifdef ALWAYS_AP
  send_debug_message("Setting up soft-AP...");
  boolean result = WiFi.softAP(ssid, password);
  if(result == true)
  {
    IPAddress myIP = WiFi.softAPIP();
    send_debug_message("Success!");
    send_debug_message("    soft-AP IP address: ");
    send_debug_message(String(myIP));
  }
  else
  {
      send_debug_message("Failed to set up soft-AP");
      return;
  }
#else 
  // // FOR DEBUG ONLY: reset saved settings
  if (digitalRead(WIFI_MODE_PIN) == LOW)
  {
    send_debug_message("Setting up soft-AP because MODE PIN SET...");
    boolean result = WiFi.softAP(ssid, password);
    if(result == true)
    {
      IPAddress myIP = WiFi.softAPIP();
      send_debug_message("Success!");
      send_debug_message("    soft-AP IP address: ");
      send_debug_message(String(myIP));
    }
    else
    {
        send_debug_message("Failed to set up soft-AP");
        return;
    }

  }
  else
  {
    wifiManager.setAPCallback(configModeCallback);
    wifiManager.autoConnect("PWDMANAGER");
  }
#endif

  if ( MDNS.begin ( "pwdtimer" ) ) {
      Serial.println ( F("MDNS responder started" ));
  }

  server.begin();
  server.setNoDelay(true); 

  // Spin here
  long lastTime = millis();
  while(1)
  {
      long currTime = millis();
      if ( (currTime-lastTime) > COMMUNICATION_TASK_PERIOD)
      {
          processTCPserverConnections();

          ///////////////////////////////////////////////////////////////
          // Send out queued messages
          ///////////////////////////////////////////////////////////////
          // Check the send queue and send them all out
          std::string *pStr = NULL;
          while ( xQueueReceive(xQueueSendMessages, &pStr, (TickType_t)0) == pdPASS)
          {
              // Send over serial                
              Serial.println(pStr->c_str());

              // Send the message over TCP (if connected)
              if (serverClients[0] && serverClients[0].connected()){
                  serverClients[0].println(pStr->c_str());
              }

              // Make sure to clean up the memory
              delete pStr;
          }

          ///////////////////////////////////////////////////////////////
          // Read in pending messages
          ///////////////////////////////////////////////////////////////
          if (Serial.available() > 0)
          {
            String message = Serial.readStringUntil('\n');            
            std::string *pStr = new std::string(message.c_str());
            xQueueSend( xQueueRecvMessages, &pStr, 0);
          }

          if (serverClients[0] && 
              serverClients[0].connected() &&
              serverClients[0].available()) {
            String message = serverClients[0].readStringUntil('\n');
            send_debug_message(message);            
            std::string *pStr = new std::string(message.c_str());
            xQueueSend( xQueueRecvMessages, &pStr, 0);
          }


          lastTime = currTime;
          delay(10);
          taskYIELD();
      }
  }
}


void setup_communications(void)
{
  pinMode(WIFI_MODE_PIN,INPUT_PULLUP);

  xQueueSendMessages = xQueueCreate(QUEUE_SIZE, sizeof(std::string *));
  xQueueRecvMessages = xQueueCreate(QUEUE_SIZE, sizeof(std::string *));

  xTaskCreatePinnedToCore(
                  communicationsCoreTask,   /* Function to implement the task */
                  "communicationsCoreTask", /* Name of the task */
                  10000,      /* Stack size in words */
                  NULL,       /* Task input parameter */
                  COMMUNICATION_TASK_PRIO,          /* Priority of the task */
                  NULL,       /* Task handle. */
                  communicationsTaskCore);  /* Core where the task should run */
}

void send_debug_message(String message)
{
  // Add to the send queue
  String debugMessage = "DEBUG: " + message;
  std::string *pStr = new std::string(debugMessage.c_str());
  xQueueSend( xQueueSendMessages, &pStr, portMAX_DELAY );
}

void send_message(String message)
{
  // Add to the send queue
  std::string *pStr = new std::string(message.c_str());
  xQueueSend( xQueueSendMessages, &pStr, 0 );
}

String receive_message(RecvMessage_t &type)
{
  type = UNDEFINED_MSG;
  String retval = "";
  std::string *pStr = NULL;

  // Receive a message from the queue
  if( xQueueReceive(xQueueRecvMessages, &pStr, (TickType_t)0) == pdPASS)
  {
    retval = String(pStr->c_str());
    delete pStr;
  }

  // Parse the message and determine the type
  if (retval.startsWith("RESET"))
  {
    type = RESET_MSG;
  }
  else if (retval.startsWith("LANES"))
  {
    type = SET_LANES_MSG;
  }

  return retval;
}

int get_lanes_from_message(String message)
{
  int idxStart = message.indexOf(',')+1;
  int idxEnd = message.indexOf('*');
  String lanesStr = message.substring(idxStart,idxEnd);  
  Serial.printf("idxstart:%d  idxend:%d  lanestr:%s\n",idxStart, idxEnd, lanesStr.c_str());
  return lanesStr.toInt();
}

void processTCPserverConnections() 
{
  uint8_t i;
  if (server.hasClient()){
      for(i = 0; i < MAX_SRV_CLIENTS; i++){
          if (!serverClients[i] || !serverClients[i].connected()){
          // Stop a disconnected server
          if(serverClients[i]) 
              serverClients[i].stop();
          serverClients[i] = server.available();
          continue;
          }
      }
      //no free spot
      WiFiClient serverClient = server.available();
      serverClient.stop();
  }
}
