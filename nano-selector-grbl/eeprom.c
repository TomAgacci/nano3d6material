#include <avr/eeprom.h>

#define NUM_TOOLS 7

extern float flow_factor[NUM_TOOLS];

float EEMEM ee_flow_factor[NUM_TOOLS];

void load_flow_factors() {
  for (uint8_t i = 0; i < NUM_TOOLS; i++)
    flow_factor[i] = eeprom_read_float(&ee_flow_factor[i]);
}

void save_flow_factors() {
  for (uint8_t i = 0; i < NUM_TOOLS; i++)
    eeprom_write_float(&ee_flow_factor[i], flow_factor[i]);
}
