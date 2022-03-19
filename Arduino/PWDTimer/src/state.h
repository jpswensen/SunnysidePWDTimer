#pragma once

typedef enum TimerStateEnum {
  UNDEFINED = 0,
  RESET,
  SET,
  IN_RACE,
  FINISHED
} TimerState_t;


extern TimerState_t state;