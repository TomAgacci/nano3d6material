uint8_t current_tool = 0;

void selector_set(uint8_t tool) {
    if (tool > 6) tool = 0;

    digitalWrite(SEL0_PIN, tool & 0x01);
    digitalWrite(SEL1_PIN, (tool >> 1) & 0x01);
    digitalWrite(SEL2_PIN, (tool >> 2) & 0x01);
}
