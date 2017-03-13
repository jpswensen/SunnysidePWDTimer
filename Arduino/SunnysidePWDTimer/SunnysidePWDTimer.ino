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

/* Create a WiFi access point and provide a web server on it. */

#define USE_US_TIMER 1

#include <algorithm>

#define LANE1_PIN D1
#define LANE2_PIN D2
#define LANE3_PIN D5
#define LANE4_PIN D6

#define STARTGATE_PIN D7

/* Variables for maintaining the race information */
typedef enum TimerStateEnum {
  UNDEFINED = 0,
  RESET,
  SET,
  IN_RACE,
  FINISHED
} TimerState_t;

TimerState_t state = RESET;
long startTime = 0;
long endTime[4] = {0, 0, 0, 0};

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  setupInterrupts();
}

void setupInterrupts () {
  pinMode(LANE1_PIN, INPUT_PULLUP);
  pinMode(LANE2_PIN, INPUT_PULLUP);
  pinMode(LANE3_PIN, INPUT_PULLUP);
  pinMode(LANE4_PIN, INPUT_PULLUP);
  pinMode(STARTGATE_PIN, INPUT_PULLUP);

  attachInterrupt(LANE1_PIN, lane1Interrupt, FALLING);
  attachInterrupt(LANE2_PIN, lane2Interrupt, FALLING);
  attachInterrupt(LANE3_PIN, lane3Interrupt, FALLING);
  attachInterrupt(LANE4_PIN, lane4Interrupt, FALLING);

  attachInterrupt(STARTGATE_PIN, startGateInterrupt, FALLING);
}

void lane1Interrupt() {
  if (endTime[0] == 0)
  {
    //Serial.println("Lane1 interrupt");
    endTime[0] = micros();
    if (endTime[1] != 0 && endTime[2] != 0 && endTime[3] != 0)
    {
      state = FINISHED;
    }
  }
}

void lane2Interrupt() {
  if (endTime[1] == 0)
  {
    endTime[1] = micros();
    //Serial.println("Lane2 interrupt");
    if (endTime[0] != 0 && endTime[2] != 0 && endTime[3] != 0)
    {
      state = FINISHED;
    }
  }
}

void lane3Interrupt() {
  if (endTime[2] == 0)
  {
    endTime[2] = micros();
    //Serial.println("Lane3 interrupt");
    if (endTime[0] != 0 && endTime[1] != 0 && endTime[3] != 0)
    {
      state = FINISHED;
    }
  }
}

void lane4Interrupt() {
  if (endTime[3] == 0)
  {
    endTime[3] = micros();
    //Serial.println("Lane4 interrupt");
    if (endTime[0] != 0 && endTime[1] != 0 && endTime[2] != 0)
    {
      state = FINISHED;
    }
  }
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

    state = IN_RACE;
  }
}

void sendMessage(int currentTime)
{
  char stateBuffer[32];
  char startTimeBuffer[32];
  char currentTimeBuffer[32];
  char endTimeBuffer[4][32];

  itoa(state, stateBuffer, 10);
  itoa(startTime, startTimeBuffer, 10);
  itoa(currentTime, currentTimeBuffer, 10);
  for (int i = 0 ; i < 4 ; i++)
  {
    itoa (endTime[i], endTimeBuffer[i], 10);
  }

  Serial.print("$");
  Serial.print(stateBuffer);
  Serial.print(",");
  Serial.print(startTimeBuffer);
  Serial.print(",");
  Serial.print(currentTimeBuffer);
  for (int i = 0 ; i < 4 ; i++)
  {
    Serial.print(",");
    Serial.print(endTimeBuffer[i]);
  }
  Serial.println("*");


}

void loop() {

  // TODO: Change this to a state machine. This main loop is current atrocious.


  // Check whether a reset command has been sent
  if (Serial.available() >=5)
  {
    String readString;
    while (Serial.available()) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    }

    if (readString.equals("RESET"))
    {
      state = RESET;
      startTime = -1;
      endTime[0] = 0;
      endTime[1] = 0;
      endTime[2] = 0;
      endTime[3] = 0;
    }
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
  

  /*
  // Output the current date
  long currentTime = -1;

  if (state == RESET)
  {
    startTime = -1;
    delay(50);
    return;
  }


  if (state == IN_RACE)
  {
    currentTime = micros();
  }
  else if (state == FINISHED)
  {
    currentTime = std::max(std::max(std::max(endTime[0], endTime[1]),endTime[2]),endTime[3]);
  }



  char stateBuffer[32];
  char startTimeBuffer[32];
  char currentTimeBuffer[32];
  char endTimeBuffer[4][32];

  itoa(state, stateBuffer, 10);
  itoa(startTime, startTimeBuffer, 10);
  itoa(currentTime, currentTimeBuffer, 10);
  for (int i = 0 ; i < 4 ; i++)
  {
    itoa (endTime[i], endTimeBuffer[i], 10);
  }

  Serial.print("$");
  Serial.print(stateBuffer);
  Serial.print(",");
  Serial.print(startTimeBuffer);
  Serial.print(",");
  Serial.print(currentTimeBuffer);
  for (int i = 0 ; i < 4 ; i++)
  {
    Serial.print(",");
    Serial.print(endTimeBuffer[i]);
  }
  Serial.println("*");

  delay(50);
  */
}
