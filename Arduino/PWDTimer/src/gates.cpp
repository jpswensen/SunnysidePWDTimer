#include <Arduino.h>
#include "state.h"
#include "gates.h"

#include <stddef.h>
#include <stdint.h>
#include <ctype.h>


static int gatesTaskCore = 1;
static int GATES_TASK_PRIO = 10;

const int  LANE1_PIN = 12;
const int  LANE2_PIN = 14;
const int  LANE3_PIN = 27;
const int  LANE4_PIN = 26;
const int  LANE5_PIN = 25;
const int  LANE6_PIN = 33;
const int  LANE7_PIN = 32;
const int  LANE8_PIN = 23;

const int  STARTGATE_PIN = 22;

int numGates = 8;
volatile long startTime = 0;
volatile long endTime[MAX_LANES] = {0};

const int parms[] = {0,1,2,3,4,5,6,7};

void laneInterrupt(void *arg);
void startGateInterrupt();

// Declare and ISR handler that can deal with any of the lanes
void IRAM_ATTR laneInterrupt(void *arg)
{
  
  int num = *(int*)arg;
  if (endTime[num] == 0)
  {
    //Serial.println("Lane1 interrupt");
    endTime[num] = micros();

    // bool is_finished = true;
    // for (int i = 0 ; i < numGates ; i++)
    // {
    //   is_finished &= (endTime[i] != 0);
    // }
    // state = is_finished ? FINISHED : IN_RACE;    
  }
}

// Interrupt used to handle when the gate has been triggered
void IRAM_ATTR startGateInterrupt() {
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


void gatepinsInterruptCoreTask( void * pvParameters ){
  pinMode(LANE1_PIN, INPUT_PULLUP);
  pinMode(LANE2_PIN, INPUT_PULLUP);
  pinMode(LANE3_PIN, INPUT_PULLUP);
  pinMode(LANE4_PIN, INPUT_PULLUP);
  pinMode(LANE5_PIN, INPUT_PULLUP);
  pinMode(LANE6_PIN, INPUT_PULLUP);
  pinMode(LANE7_PIN, INPUT_PULLUP);
  pinMode(LANE8_PIN, INPUT_PULLUP);
  pinMode(STARTGATE_PIN, INPUT_PULLUP);

  attachInterruptArg(LANE1_PIN, laneInterrupt, (void*)&parms[0], FALLING);
  attachInterruptArg(LANE2_PIN, laneInterrupt, (void*)&parms[1], FALLING);
  attachInterruptArg(LANE3_PIN, laneInterrupt, (void*)&parms[2], FALLING);
  attachInterruptArg(LANE4_PIN, laneInterrupt, (void*)&parms[3], FALLING);
  attachInterruptArg(LANE5_PIN, laneInterrupt, (void*)&parms[4], FALLING);
  attachInterruptArg(LANE6_PIN, laneInterrupt, (void*)&parms[5], FALLING);
  attachInterruptArg(LANE7_PIN, laneInterrupt, (void*)&parms[6], FALLING);
  attachInterruptArg(LANE8_PIN, laneInterrupt, (void*)&parms[7], FALLING);
  
  // Attach the starting gate interrupt
  attachInterrupt(STARTGATE_PIN, startGateInterrupt, FALLING);

  while(1)
  {
    delay(500);
    taskYIELD();
  }
}

void setup_gates(void)
{
  reset_gates();
  xTaskCreatePinnedToCore(
                    gatepinsInterruptCoreTask,   /* Function to implement the task */
                    "gatepinsInterruptCoreTask", /* Name of the task */
                    10000,      /* Stack size in words */
                    NULL,       /* Task input parameter */
                    GATES_TASK_PRIO,          /* Priority of the task */
                    NULL,       /* Task handle. */
                    gatesTaskCore);  /* Core where the task should run */
}

int get_num_gates()
{
  return numGates;
}

void set_num_gates(int num)
{
  numGates = num;
}

void reset_gates(void)
{
  startTime = -1;
  endTime[0] = 0;
  endTime[1] = 0;
  endTime[2] = 0;
  endTime[3] = 0;
  endTime[4] = 0;
  endTime[5] = 0;
  endTime[6] = 0;
  endTime[7] = 0;
}

bool is_starting_gate_set(void)
{
  return (digitalRead(STARTGATE_PIN)==1);
}

void read_gates(long &start, long* gates)
{
  // Disable interrupts
  portDISABLE_INTERRUPTS ();

  // Copy the data
  start = startTime;
  gates[0] = endTime[0];
  gates[1] = endTime[1];
  gates[2] = endTime[2];
  gates[3] = endTime[3];
  gates[4] = endTime[4];
  gates[5] = endTime[5];
  gates[6] = endTime[6];
  gates[7] = endTime[7];

  // Enable interrupts
  portENABLE_INTERRUPTS ();
}