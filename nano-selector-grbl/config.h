#ifndef CONFIG_H
#define CONFIG_H

#define N_AXIS 4   // X, Y, Z, E

// Steps per mm
#define DEFAULT_X_STEPS_PER_MM 80.0f
#define DEFAULT_Y_STEPS_PER_MM 80.0f
#define DEFAULT_Z_STEPS_PER_MM 400.0f
#define DEFAULT_E_STEPS_PER_MM 95.0f

// Max feedrates
#define DEFAULT_MAX_FEEDRATE_X 3000.0f
#define DEFAULT_MAX_FEEDRATE_Y 3000.0f
#define DEFAULT_MAX_FEEDRATE_Z 300.0f
#define DEFAULT_MAX_FEEDRATE_E 1500.0f

// Acceleration
#define DEFAULT_ACCELERATION 300.0f

#endif
