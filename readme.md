License Under Creative Commons Attribution Open Source

Wiring diagram (text)
Nano → CNC shield #1:

D2 → X STEP

D5 → X DIR

D3 → Y STEP

D6 → Y DIR

D4 → Z STEP

D7 → Z DIR

Nano → extruder bus:

D9 → STEP pins of direct‑drive driver + all bowden drivers

D8 → DIR pins of direct‑drive driver + all bowden drivers

Nano → selector (74HC138):

D10 → A0

D11 → A1

D12 → A2

74HC138 G1 → +5 V, G2A/G2B → GND

Y0 → EN of direct‑drive driver

Y1–Y6 → EN of bowden0–bowden5 drivers

Heater + thermistor:

D13 → MOSFET gate (through resistor), MOSFET source → GND, drain → heater, heater other side → +12–24 V

A0 → thermistor, other side of thermistor → GND, with pull‑up to +5 V as needed.

Endstops: A1/A2/A3 to switches to GND with internal pull‑ups.

✔️ How to compute flow_factor
You need a measurement. You suggested:

“measure the y = requested/measured = duration * y”

Meaning:

You measure duration under load (motor on, selector engaged)

You treat duration as proportional to actual filament delivered

You compare it to the requested amount

So:

c
float flow_factor = requested / measured;
On the Nano, “measured” can be:

Option A — Time‑based measurement (your idea)
Track how long the extruder motor is actually stepping:

c
unsigned long e_start, e_end;
float measured;

void begin_extrude() {
    e_start = micros();
}

void end_extrude() {
    e_end = micros();
    measured = (float)(e_end - e_start) * duration_scale; 
    flow_factor = requested / measured;
}
This is crude but works surprisingly well for bowden feeders.

Option B — Motor load measurement
If you add a simple analog current sensor (ACS712 or INA219):

Measure motor current during extrusion

Higher load = more pressure = more filament

Lower load = slip or under‑extrusion
