#include "config.h"

extern uint8_t current_tool;
extern float flow_factor[];

extern float current_x;
extern float current_y;
extern float current_z;
extern float current_feedrate;

void plan_buffer_line(float x, float y, float z, float e_steps, float feedrate);

void plan_extruder_move(float e) {
  float corrected = e * flow_factor[current_tool];
  float steps = corrected * DEFAULT_E_STEPS_PER_MM;
  plan_buffer_line(current_x, current_y, current_z, steps, current_feedrate);
}
