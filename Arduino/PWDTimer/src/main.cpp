#include <Arduino.h>
#include "state.h"
#include "communications.h"
#include "gates.h"
#include <LittleFS.h>   


template<typename T>
T find_max_time(T *arr, size_t n)
{
    return *std::max_element(arr, arr+n);
}

String create_gate_times_message(TimerState_t state, long startTime, long currentTime, int numGates, long* endTimes)
{
  char msgBuffer[512];
  sprintf(msgBuffer, "$%d,%ld,%ld,%d,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld*", 
                    state, startTime, currentTime, numGates, 
                    endTimes[0], endTimes[1], endTimes[2], endTimes[3],endTimes[4], endTimes[5], endTimes[6], endTimes[7]);
  return String(msgBuffer);
}

#include "soc/rtc_wdt.h"
void setup() {
  rtc_wdt_protect_off();
  rtc_wdt_disable();
  Serial.begin(115200);
  Serial.println("Waiting for WIFI mode");
  delay(2000);
  
  // put your setup code here, to run once:
  setup_communications();
  setup_gates();    
}


void loop() {
  RecvMessage_t msgType = UNDEFINED_MSG;
  long startTime = -1;
  long endTimes[MAX_LANES];
  
  long currentTime = micros();
  int numGates = get_num_gates();
  read_gates(startTime, endTimes);    

  // Process incoming messages first
  String inMsg = receive_message(msgType);
  if (msgType == RESET_MSG)
  {
    state = RESET;
    reset_gates();
  }
  
  // Handle the current state of the system
  switch (state) {
    case RESET:
    {
      startTime = -1;      

      if (is_starting_gate_set())
      {
        state = SET;
      }      
      break;
    }
    case SET:
    {
      break;
    }
    case IN_RACE:
    {
      bool is_finished = true;
      for (int i = 0 ; i < numGates ; i++)
      {
        is_finished &= (endTimes[i] != 0);
      }
      state = is_finished ? FINISHED : IN_RACE;                      
      break;
    }
    case FINISHED:
    {
      currentTime = find_max_time(endTimes,numGates);
      break;
    }
    default:
    {
      send_debug_message("UNKNOWN STATE");
      break;
    }
  }

  // Send out a message regardless of which state we are in that contains the 
  String outMessage = create_gate_times_message(state, startTime, currentTime, numGates, endTimes);
  send_message(outMessage);

  delay(50);

  
}