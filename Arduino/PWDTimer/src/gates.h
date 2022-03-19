#pragma once

#define MAX_LANES 8

void setup_gates(void);
int get_num_gates();
void set_num_gates(int num);
void reset_gates(void);

bool is_starting_gate_set(void);

void read_gates(long &start, long* gates);


extern const int  STARTGATE_PIN;
