#include "vars_defs_functions.h"
#include <omp.h>
void update_velocity(BODY *bodies, double fraction)
{
#pragma omp parallel for num_threads(MAX_THREADS)
    // Loop through all bodies and calculate
    for (int i = 0; i < NUM_BODIES; i++)
    {
        // compute the acceleration in x, y and z dir
        double ax = bodies[i].fx / bodies[i].mass; // acceleration in x direction
        double ay = bodies[i].fy / bodies[i].mass; // acceleration in y direction
        double az = bodies[i].fz / bodies[i].mass; // acceleration in y direction

        // compute the velocity in x, y and z dir
        bodies[i].vx += ax * DELTA_TIME * fraction;
        bodies[i].vy += ay * DELTA_TIME * fraction;
        bodies[i].vz += az * DELTA_TIME * fraction;
    }
}