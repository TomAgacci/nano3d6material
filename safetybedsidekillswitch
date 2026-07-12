1. Hardware mapping for 8 f‑stop killswitches
On the Nano‑Selector GRBL side (from the repo):

Endstops are already suggested on analog pins:

A1, A2, A3 → endstop switches to GND with internal pull‑ups.

You want 8 switches, so we’ll treat them as a kill ring, not as normal endstops:

Suggested mapping:

Use A1–A3 for normal X/Y/Z endstops (as in the docs).

Use D14–D19 (A0–A5 as digital) for 8 kill inputs if you’re willing to repurpose some analog pins.

Or, if you only need 4–6 around the bed, keep some pins free for sensors.

Example mapping (for 8 switches):

// In cpu_map.h or a dedicated header
#define KILL0_PIN   A0  // D14
#define KILL1_PIN   A1  // D15
#define KILL2_PIN   A2  // D16
#define KILL3_PIN   A3  // D17
#define KILL4_PIN   A4  // D18
#define KILL5_PIN   A5  // D19
#define KILL6_PIN   D2  // if free in your variant
#define KILL7_PIN   D3  // if free in your variant

You can adjust which pins are actually free in your build—just keep them as input with pull‑up, and wire each switch to GND so pressing it pulls the pin low.
