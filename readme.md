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
