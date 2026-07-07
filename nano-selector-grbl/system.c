#include <Arduino.h>
#include "cpu_map.h"
#include "config.h"

#define NUM_TOOLS 7

uint8_t current_tool = 0;
float flow_factor[NUM_TOOLS] = {1,1,1,1,1,1,1};

unsigned long e_start = 0;
float measured_e = 0.0f;
float requested_e = 0.0f;

float target_temp = 0.0f;

// Encoder
volatile long encoder_ticks = 0;
float ticks_to_mm = 0.01f;

// Current sensor scale
float load_scale = 0.001f;

// Thermistor constants
#define THERMISTOR_NOMINAL 100000.0f
#define TEMPERATURE_NOMINAL 25.0f
#define B_COEFFICIENT 3950.0f
#define SERIES_RESISTOR 100000.0f

void selector_set(uint8_t tool) {
  if (tool > 6) tool = 0;
  digitalWrite(SEL0_PIN, tool & 0x01);
  digitalWrite(SEL1_PIN, (tool >> 1) & 0x01);
  digitalWrite(SEL2_PIN, (tool >> 2) & 0x01);
}

float thermistor_to_celsius(int raw) {
  float v = (float)raw / 1023.0f;
  float r = SERIES_RESISTOR * (1.0f / v - 1.0f);

  float steinhart = r / THERMISTOR_NOMINAL;
  steinhart = log(steinhart);
  steinhart /= B_COEFFICIENT;
  steinhart += 1.0f / (TEMPERATURE_NOMINAL + 273.15f);
  steinhart = 1.0f / steinhart;
  steinhart -= 273.15f;

  return steinhart;
}

float read_motor_load() {
  int raw = analogRead(CURRENT_PIN);
  return (float)raw * load_scale;
}

void begin_extrude() {
  e_start = micros();
  encoder_ticks = 0;
}

void end_extrude() {
  unsigned long e_end = micros();
  unsigned long dt = e_end - e_start;

  float duration_mm = (float)dt * 0.00001f;
  float load_mm     = read_motor_load();
  float encoder_mm  = encoder_ticks * ticks_to_mm;

  measured_e = 0.6f * encoder_mm + 0.2f * duration_mm + 0.2f * load_mm;

  if (measured_e > 0.0f)
    flow_factor[current_tool] = requested_e / measured_e;

  encoder_ticks = 0;
}

bool temp_reached() {
  int raw = analogRead(THERMISTOR_PIN);
  float t = thermistor_to_celsius(raw);
  return (t >= target_temp - 1.0f);
}

void heater_loop() {
  int raw = analogRead(THERMISTOR_PIN);
  float t = thermistor_to_celsius(raw);

  if (t < target_temp - 2.0f) digitalWrite(HEATER_PIN, HIGH);
  else if (t > target_temp + 2.0f) digitalWrite(HEATER_PIN, LOW);
}

// Called from main loop
void protocol_main_loop() {
  for (;;) {
    protocol_execute_realtime();
    heater_loop();
  }
}

// Example encoder ISR (adjust to your pin/PCINT setup)
ISR(PCINT2_vect) {
  encoder_ticks++;
}
