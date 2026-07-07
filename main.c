void protocol_main_loop() {
    for (;;) {
        protocol_execute_realtime();
        heater_loop();
    }
}
