#pragma once
#include <Arduino.h>

// Enums for maintaining the race and messaging information 
typedef enum RecvMessageEnum {
  UNDEFINED_MSG = 0,
  RESET_MSG
} RecvMessage_t;

void setup_communications(void);
String receive_message(RecvMessage_t &type);
void send_debug_message(String message);
void send_message(String message);