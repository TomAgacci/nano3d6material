# Wiring: Nano → CNC Shields → Selector → Hotend

## Axis Wiring (CNC Shield #1)
Nano → CNC Shield #1:
- D2 → X STEP
- D5 → X DIR
- D3 → Y STEP
- D6 → Y DIR
- D4 → Z STEP
- D7 → Z DIR

## Extruder Bus (Shared STEP/DIR)
Nano → all extruder drivers:
- D9 → STEP (direct + bowden drivers)
- D8 → DIR (direct + bowden drivers)

## Selector (74HC138)
Nano → 74HC138:
- D10 → A0
- D11 → A1
- D12 → A2

Decoder outputs → EN pins:
- Y0 → direct‑drive extruder
- Y1 → bowden 1
- Y2 → bowden 2
- Y3 → bowden 3
- Y4 → bowden 4
- Y5 → bowden 5
- Y6 → bowden 6

Enable pins must be isolated on CNC shields (cut common EN trace if needed).

## Heater + Thermistor
- D13 → MOSFET gate
- Thermistor → A0 (with pull‑up)

## Sensors
- Current sensor → A5
- Encoder → PCINT pin (e.g., D2 or A0)

## Power
- CNC shields: 12–24 V motor supply
- Nano: USB or 5 V regulator
- Common GND between all boards
