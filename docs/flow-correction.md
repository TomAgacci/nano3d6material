# Flow‑Correction Engine

## Purpose
Correct extrusion dynamically by comparing:
- Requested extrusion (E from G‑code)
- Measured extrusion (duration, current, encoder)

## Measurement Methods
### 1. Duration‑Based
Extrusion time → approximate mm extruded.

### 2. Current‑Based
Motor load → pressure → extrusion amount.

### 3. Encoder‑Based
Optical encoder ticks → exact filament motion.

### 4. Hybrid
Weighted combination:
- 60% encoder
- 20% duration
- 20% current

## Flow Factor
Per‑tool:
