void plan_extruder_move(float e) {
  float e_steps = e * DEFAULT_E_STEPS_PER_MM;
  plan_buffer_line(current_x, current_y, current_z, e_steps, current_feedrate);
}
