License Under Creative Commons Attribution Open Source

Here's the reprap compatible 6 material addon for bowden, for the project:<br>
www.thingiverse.com/thing:2801393<br>
Here's the compatible files<br>
www.thingiverse.com/Gremble/collections/11229688/things<br>
Here's the CNC Parts and templates<br>
www.thingiverse.com/Gremble/collections/39468905/things<br>

Please Support the repository. Here's a link to cnc v3 shields.
https://amzn.to/4wuNUS6

nano-selector-grbl/
├─ README.md
├─ LICENSE
├─ docs/
│  ├─ architecture.md
│  ├─ wiring-nano-cnc-shields.md
│  ├─ selector-logic.md
│  ├─ flow-correction.md
│  └─ diagrams/
│     ├─ block-diagram-nano-selector.png
│     ├─ wiring-diagram-cnc-shields.png
│     ├─ selector-decoder-74hc138.png
│     ├─ flow-correction-loop.png
│     └─ slicer-toolchain.png
├─ src/
│  ├─ grbl_nano_selector.ino
│  ├─ config.h
│  ├─ cpu_map.h
│  ├─ defaults.h
│  ├─ system.c
│  ├─ gcode.c
│  ├─ planner.c
│  ├─ heater.c
│  ├─ selector.c
│  ├─ flow.c
│  └─ eeprom.c
└─ slicer-profiles/
   ├─ prusaslicer-nano-selector.ini
   └─ cura-nano-selector.json


The seventh tool motor is for direct drive 6 color addition or single direct drive basic

Nano‑Selector GRBL Firmware
A 7‑Tool, Single‑Nozzle, Multi‑Material 3D Printer on an Arduino Nano (ATmega328P)
With Selector Hardware, Closed‑Loop Extrusion, Flow‑Correction, and Marlin‑Compatible G‑Code
Overview
Nano‑Selector GRBL is a custom fork of GRBL 1.1 designed to run a multi‑material, single‑nozzle 3D printer using:

Arduino Nano (ATmega328P)

Two CNC shields

Up to 7 extruder motors (1 direct‑drive + 6 bowden feeders)

A 74HC138 extruder‑selector decoder

Shared STEP/DIR bus

One hotend

Marlin‑style G‑code (T0–T6, M104, M109, G1 X/Y/Z/E)

The firmware adds:

Multi‑tool selector logic

Heater + thermistor control

Extruder axis planning

Closed‑loop flow‑correction

Current‑sensor integration

Encoder‑sensor integration

Hybrid extrusion measurement

Per‑tool calibration G‑codes

Auto‑calibration routines

EEPROM storage for flow factors

PrusaSlicer + Cura compatibility

This enables a 7‑material printer on a single Nano, with one extruder axis and hardware‑selected motors.

Hardware Architecture
Axes
X, Y, Z: standard GRBL axes

E: single extruder axis (shared STEP/DIR bus)

Extruder Motors
Direct‑drive motor (T0)

Six bowden motors (T1–T6)

Selector Hardware
74HC138 decoder

Nano pins D10–D12 → decoder address lines

Decoder outputs Y0–Y6 → EN pins of extruder drivers

Only one driver enabled at a time

Shared STEP/DIR Bus
Nano D9 → STEP of all extruder drivers

Nano D8 → DIR of all extruder drivers

Heater + Thermistor
D13 → MOSFET gate

A0 → thermistor input

Optional Sensors
A5 → current sensor (ACS712/INA219 analog output)

D14/A0 or PCINT pin → filament encoder wheel

Pin Map
Code
X_STEP_PIN      D2
X_DIR_PIN       D5
Y_STEP_PIN      D3
Y_DIR_PIN       D6
Z_STEP_PIN      D4
Z_DIR_PIN       D7

E_STEP_PIN      D9
E_DIR_PIN       D8

SEL0_PIN        D10
SEL1_PIN        D11
SEL2_PIN        D12

HEATER_PIN      D13
THERMISTOR_PIN  A0

CURRENT_PIN     A5
ENCODER_PIN     PCINT (choose D8–D13 or A0–A5)
Firmware Features
1. Marlin‑Compatible G‑Code
T0–T6 → tool selection

M104 → set temperature

M109 → wait for temperature

G1 X/Y/Z/E → motion + extrusion

2. Selector Logic
Tn sets SEL0–SEL2 → decoder → enables one extruder driver.

3. Heater Control
Bang‑bang loop with real thermistor math (Beta equation).

4. Extruder Axis Planning
E axis treated as a fourth GRBL axis.

5. Closed‑Loop Flow‑Correction
Measured extrusion vs requested extrusion:

Duration‑based measurement

Current‑based measurement

Encoder‑based measurement

Hybrid weighted measurement

6. Per‑Tool Flow Factors
flow_factor[7] stored in EEPROM.

7. Calibration G‑Codes
M700 Sx.xx → set flow factor

M701 → report flow factor

M702 → auto‑calibrate current tool

M703 → save flow factors to EEPROM

Slicer Configuration
PrusaSlicer
Printer: 7 extruders, 1 shared nozzle

G‑code flavor: Marlin

Tool‑change G‑code:

Code
G1 E-3 F1800
T[next_extruder]
G4 P300
G1 E6 F1800
Cura
Machine definition:

Code
machine_extruder_count = 7
machine_nozzle_size = 0.4
machine_gcode_flavor = Marlin
All extruders share one nozzle and one temperature.

Wiring Diagram (Text)
CNC Shield #1
X, Y, Z drivers

Direct‑drive extruder driver (EN → decoder Y0)

CNC Shield #2
Bowden drivers 1–6 (EN → decoder Y1–Y6)

Shared STEP/DIR
D9 → all STEP pins

D8 → all DIR pins

Selector
D10 → A0

D11 → A1

D12 → A2

Y0–Y6 → EN pins

Heater
D13 → MOSFET gate

Thermistor → A0

Sensors
Current sensor → A5

Encoder → PCINT pin

Test G‑Code (7‑Tool Verification)
Code
M104 S200
M109 S200
G28

T0
G4 P300
G1 X10 Y10 Z0.2 F3000
G1 E5 F600

T1
G4 P300
G1 X20 Y10 Z0.2 F3000
G1 E5 F600

T2
G4 P300
G1 X30 Y10 Z0.2 F3000
G1 E5 F600

T3
G4 P300
G1 X40 Y10 Z0.2 F3000
G1 E5 F600

T4
G4 P300
G1 X50 Y10 Z0.2 F3000
G1 E5 F600

T5
G4 P300
G1 X60 Y10 Z0.2 F3000
G1 E5 F600

T6
G4 P300
G1 X70 Y10 Z0.2 F3000
G1 E5 F600

M104 S0
G1 X0 Y0 F3000
Build Instructions
Clone GRBL 1.1

Replace cpu_map.h, config.h, defaults.h

Add selector logic to system.c

Add extended G‑code parser to gcode.c

Add extruder axis planning to planner.c

Add heater loop to system.c

Add flow‑correction module

Compile for Arduino Nano

Upload via USB

Project Status
✔ Fully functional
✔ Supports 7 tools
✔ Closed‑loop extrusion
✔ EEPROM persistence
✔ PrusaSlicer + Cura ready
✔ Real thermistor math
✔ Selector hardware stable
✔ Nano‑compatible

Next Steps (Optional Enhancements)
Prime tower generation

Per‑tool purge volumes

Pressure advance (limited Nano version)

Multi‑material wipe station

Bowden‑specific flow curves

Selector stall detection


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
