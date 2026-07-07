#ifndef CPU_MAP_H
#define CPU_MAP_H

// Arduino Nano (ATmega328P)

// Axis pins
#define X_STEP_PIN      2
#define X_DIRECTION_PIN 5
#define Y_STEP_PIN      3
#define Y_DIRECTION_PIN 6
#define Z_STEP_PIN      4
#define Z_DIRECTION_PIN 7

// Extruder bus
#define E_STEP_PIN      9
#define E_DIRECTION_PIN 8

// Selector bits (74HC138 address)
#define SEL0_PIN        10
#define SEL1_PIN        11
#define SEL2_PIN        12

// Heater + thermistor
#define HEATER_PIN      13
#define THERMISTOR_PIN  A0

// Current sensor
#define CURRENT_PIN     A5

// Optional encoder pin (example)
#define ENCODER_PIN     2  // adjust to your wiring

// Endstops (optional)
#define X_LIMIT_PIN     A1
#define Y_LIMIT_PIN     A2
#define Z_LIMIT_PIN     A3

#endif
