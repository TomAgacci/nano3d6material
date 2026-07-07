#include "grbl.h"

void setup() {
  grbl_init();
}

void loop() {
  protocol_main_loop();
}
