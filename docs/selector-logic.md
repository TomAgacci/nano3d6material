# Selector Logic (74HC138)

## Purpose
Select one of seven extruder motors using:
- Shared STEP/DIR bus
- Per‑driver EN pins
- 3‑bit selector address

## Address Mapping
Binary → Tool → Decoder Output → Driver EN
- 000 → T0 → Y0 → Direct‑drive
- 001 → T1 → Y1 → Bowden 1
- 010 → T2 → Y2 → Bowden 2
- 011 → T3 → Y3 → Bowden 3
- 100 → T4 → Y4 → Bowden 4
- 101 → T5 → Y5 → Bowden 5
- 110 → T6 → Y6 → Bowden 6
- 111 → unused / no tool

## Firmware
`selector_set(tool)` sets SEL0–SEL2 pins.

## Electrical Notes
- G1 → +5 V  
- G2A/G2B → GND  
- Only one Y output is active at a time.
