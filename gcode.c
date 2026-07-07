void process_extended_gcode(char *line) {

    // Tool change Tn
    if (line[0] == 'T') {
        int t = atoi(line + 1);
        current_tool = t;
        selector_set(current_tool);
        return;
    }

    // Temperature set M104 Sxxx
    if (starts_with(line, "M104")) {
        float t = parse_S(line);
        target_temp = t;
        return;
    }

    // Temperature wait M109 Sxxx
    if (starts_with(line, "M109")) {
        float t = parse_S(line);
        target_temp = t;
        while (!temp_reached()) {
            heater_loop();
        }
        return;
    }

    // Extruder move E
    if (strchr(line, 'E')) {
        float e = parse_E(line);
        plan_extruder_move(e);   // treat E as a 4th axis
        return;
    }
}
