#include <Arduino.h>
#include "cpu_map.h"

extern uint8_t current_tool;
extern float target_temp;
extern float requested_e;
extern void selector_set(uint8_t tool);
extern void begin_extrude();
extern void end_extrude();
extern bool temp_reached();
extern void heater_loop();
extern void plan_extruder_move(float e);
extern float flow_factor[];

void report_flow(uint8_t tool, float f) {
  Serial.print(F("Flow factor T"));
  Serial.print(tool);
  Serial.print(F(" = "));
  Serial.println(f, 4);
}

float parse_S(char *line) {
  char *s = strchr(line, 'S');
  if (!s) return 0.0f;
  return atof(s + 1);
}

float parse_E(char *line) {
  char *e = strchr(line, 'E');
  if (!e) return 0.0f;
  return atof(e + 1);
}

bool starts_with(const char *line, const char *prefix) {
  return strncmp(line, prefix, strlen(prefix)) == 0;
}

void process_extended_gcode(char *line) {

  if (line[0] == 'T') {
    int t = atoi(line + 1);
    current_tool = (t > 6) ? 0 : t;
    selector_set(current_tool);
    return;
  }

  if (starts_with(line, "M104")) {
    float s = parse_S(line);
    target_temp = s;
    return;
  }

  if (starts_with(line, "M109")) {
    float s = parse_S(line);
    target_temp = s;
    while (!temp_reached()) heater_loop();
    return;
  }

  if (starts_with(line, "M700")) {  // set flow factor
    float f = parse_S(line);
    flow_factor[current_tool] = f;
    return;
  }

  if (starts_with(line, "M701")) {  // report flow factor
    report_flow(current_tool, flow_factor[current_tool]);
    return;
  }

  if (starts_with(line, "M702")) {  // auto-calibrate current tool
    requested_e = 10.0f;
    begin_extrude();
    plan_extruder_move(requested_e);
    end_extrude();
    report_flow(current_tool, flow_factor[current_tool]);
    return;
  }

  if (starts_with(line, "M703")) {  // save flow factors
    save_flow_factors();
    return;
  }

  if (strchr(line, 'E')) {
    requested_e = parse_E(line);
    begin_extrude();
    plan_extruder_move(requested_e);
    end_extrude();
    return;
  }

  // For all other commands, fall through to GRBL's normal parser
  grbl_process_line(line);
}
