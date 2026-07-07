# Nano‑Selector GRBL Architecture

## Overview
The Nano‑Selector system is a custom GRBL fork enabling a 7‑tool, single‑nozzle 3D printer using:
- Arduino Nano (ATmega328P)
- Two CNC shields
- 7 extruder motors (1 direct + 6 bowden)
- A 74HC138 extruder‑selector decoder
- Shared STEP/DIR bus
- One hotend (heater + thermistor)
- Optional current sensor + encoder for closed‑loop extrusion

GRBL provides:
- Motion planning (X/Y/Z/E)
- Stepper timing
- G‑code parsing

Custom modules provide:
- Tool selection (`T0–T6`)
- Heater control (`M104`, `M109`)
- Flow‑correction engine
- EEPROM persistence
- Auto‑calibration routines

---

## System Blocks
- **Nano MCU**  
  Runs GRBL + selector + heater + flow‑correction.

- **CNC Shield #1**  
  X/Y/Z drivers + direct‑drive extruder.

- **CNC Shield #2**  
  Bowden extruder drivers (T1–T6).

- **Selector (74HC138)**  
  SEL0–SEL2 → Y0–Y6 → EN pins.

- **Sensors**  
  Thermistor, current sensor, encoder.

---

## Data Flow
1. Slicer → G‑code → Nano  
2. Nano parses tool changes → selector bits  
3. GRBL planner computes motion  
4. E‑axis steps go to shared STEP/DIR bus  
5. Selector enables only one extruder driver  
6. Heater loop maintains temperature  
7. Flow‑correction adjusts extrusion dynamically

