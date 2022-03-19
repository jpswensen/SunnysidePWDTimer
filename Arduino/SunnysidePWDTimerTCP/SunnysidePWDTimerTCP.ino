/*
   Copyright (c) 2017, John Swensen
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* 
  This version of the timer firmware creates a WiFi access point and provides a TCP socket on it.
  This can still be run using the standard serial interface or can be connected to as an access point.
  NOTE: The reason for extending this to a WIFI solution was so that the computer/projector do not
        have to be near the finish line of the race. You will still need to run power to the finish line,
        but you won't need a long USB cable and monitor cable to have a better computer/projector location.
*/

#define USE_US_TIMER 1

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <algorithm>

#define LANE1_PIN D0
#define LANE2_PIN D1
#define LANE3_PIN D2
#define LANE4_PIN D3
#define LANE5_PIN D4
#define LANE6_PIN D5
#define LANE7_PIN D6
#define LANE8_PIN D8

#define STARTGATE_PIN D7



// Enums for maintaining the race and messaging information 
typedef enum RecvMessageEnum {
  UNDEFINED_MSG = 0,
  RESET_MSG
} RecvMessage_t;


typedef enum TimerStateEnum {
  UNDEFINED = 0,
  RESET,
  SET,
  IN_RACE,
  FINISHED
} TimerState_t;


// Variables for determining the state of the race and car times
#define NUM_TIMERS 8
TimerState_t state = RESET;
long startTime = 0;
long endTime[NUM_TIMERS] = {0, 0, 0, 0, 0, 0, 0, 0};


// Variables for configuring the communications
#define SERIAL_BAUD 115200

#define MAX_SRV_CLIENTS 1
#define TCP_PORT        8080

const char *ssid = "PWDTIMER";
const char *password = "PWDTIMER";
WiFiServer server(TCP_PORT);
WiFiClient serverClients[MAX_SRV_CLIENTS];


/**************************************************************************************************************
 * INTERRUPT HANDLING
 **************************************************************************************************************/

// Declare and ISR handler that can deal with any of the lanes
void laneInterrupt(int num)
{
  if (endTime[num] == 0)
  {
    //Serial.println("Lane1 interrupt");
    endTime[num] = micros();

    bool is_finished = true;
    for (int i = 0 ; i < NUM_TIMERS ; i++)
    {
      is_finished &= (endTime[i] != 0);
    }
    state = is_finished ? FINISHED : IN_RACE;    
  }
}

// Create a templated function that uses the ISR number as the template parameter
template<int N>
void laneInterruptISR() {
  laneInterrupt(N);
}

void startGateInterrupt() {
  //Serial.println("Start gate interrupt");
  if (state == SET)
  {
    startTime = micros();
    
    endTime[0] = 0;
    endTime[1] = 0;
    endTime[2] = 0;
    endTime[3] = 0;
    endTime[4] = 0;
    endTime[5] = 0;
    endTime[6] = 0;
    endTime[7] = 0;

    state = IN_RACE;
  }
}
 
void setupInterrupts () {
  // Set up the gate and lane pins as inputs with weak pull-ups
  pinMode(LANE1_PIN, INPUT_PULLUP);
  pinMode(LANE2_PIN, INPUT_PULLUP);
  pinMode(LANE3_PIN, INPUT_PULLUP);
  pinMode(LANE4_PIN, INPUT_PULLUP);
  pinMode(LANE5_PIN, INPUT_PULLUP);
  pinMode(LANE6_PIN, INPUT_PULLUP);
  pinMode(LANE7_PIN, INPUT_PULLUP);
  pinMode(LANE8_PIN, INPUT_PULLUP);
  pinMode(STARTGATE_PIN, INPUT_PULLUP);

  // Attach the interrupts for each of the lanes.
  // NOTE: Here we are using some C++ template magic above to only have to declare the ISR once.
  attachInterrupt(LANE1_PIN, laneInterruptISR<1>, FALLING);
  attachInterrupt(LANE2_PIN, laneInterruptISR<2>, FALLING);
  attachInterrupt(LANE3_PIN, laneInterruptISR<3>, FALLING);
  attachInterrupt(LANE4_PIN, laneInterruptISR<4>, FALLING);
  attachInterrupt(LANE5_PIN, laneInterruptISR<5>, FALLING);
  attachInterrupt(LANE6_PIN, laneInterruptISR<6>, FALLING);
  attachInterrupt(LANE7_PIN, laneInterruptISR<7>, FALLING);
  attachInterrupt(LANE8_PIN, laneInterruptISR<8>, FALLING);

  // Attach the starting gate interrupt
  attachInterrupt(STARTGATE_PIN, startGateInterrupt, FALLING);
}


/**************************************************************************************************************
 * COMMUNICATIONS : TCP (DATA) AND SERIAL (DEBUG)
 **************************************************************************************************************/
void setupCommunications() {
  delay(1000);
  Serial.begin(SERIAL_BAUD);
  Serial.println();

  Serial.print("Setting up soft-AP...");
  boolean result = WiFi.softAP(ssid, password);
  if(result == true)
  {
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("Success!");
    Serial.print("    soft-AP IP address: ");
    Serial.println(myIP);
  }
  else
  {
    Serial.println("Failed to set up soft-AP");
  }

}
    

void setupTCPserver() {  
  server.begin();
  server.setNoDelay(true); 
}

void processTCPserverConnections() {
  uint8_t i;
  if (server.hasClient()){
    for(i = 0; i < MAX_SRV_CLIENTS; i++){
      if (!serverClients[i] || !serverClients[i].connected()){
        if(serverClients[i]) serverClients[i].stop();
        serverClients[i] = server.available();
        continue;
      }
    }
    //no free spot
    WiFiClient serverClient = server.available();
    serverClient.stop();
  }
}

RecvMessage_t readMessage()
{
  // TODO: Check both the serial and the TCP for a message
  
  // Check whether a reset command has been sent via serial
  if (Serial.available() >=5)
  {
    String readString;
    while (Serial.available()) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    }

    
    if (readString.equals("RESET"))
    {
      return RESET_MSG;
    }
  }
  
  return UNDEFINED_MSG;
}

void sendMessage(int currentTime)
{
  // Build the message to be sent
  char msgBuffer[512];
  sprintf(msgBuffer, "$%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d*", state, startTime, currentTime,
                     endTime[0], endTime[1], endTime[2], endTime[3],
                     endTime[4], endTime[5], endTime[6], endTime[7]);

  // Send the message over serial
  Serial.println(msgBuffer);

  // Send the message over TCP (if connected)
  if (serverClients[0] && serverClients[0].connected()){
    serverClients[0].println(msgBuffer);
  }
}

/**************************************************************************************************************
 * VARIOUS OTHER FUNCTIONS
 **************************************************************************************************************/
void resetRace() {
  state = RESET;
  startTime = -1;
  for (int i = 0 ; i < NUM_TIMERS ; i++) {
    endTime[i] = 0; 
  }
}


/**************************************************************************************************************
 * SETUP AND LOOP
 **************************************************************************************************************/
void setup() {
  delay(1000);
  setupCommunications();

  setupTCPserver();

  setupInterrupts();
}

void loop() {

  // Process TCP connects and disconnects
  processTCPserverConnections();

  // Read in messages from either serial or TCP
  RecvMessage_t msg = readMessage();
  if (msg == RESET_MSG) {
    resetRace();
  }
  

  long currentTime = -1;
  
  switch (state) {
    case RESET:
      startTime = -1;

      if (digitalRead(STARTGATE_PIN) == HIGH)
      {
        state = SET;
      }
      else
      {
        sendMessage(currentTime);
      }
      
      break;

    case SET:
      sendMessage(currentTime);
      break;

    case IN_RACE:
      currentTime = micros();
      sendMessage(currentTime);
      break;

    case FINISHED:
      currentTime = std::max(std::max(std::max(endTime[0], endTime[1]),endTime[2]),endTime[3]);
      sendMessage(currentTime);
      break;
    
  }

  delay(50);
  
}
