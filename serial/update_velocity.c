#include "vars_defs_functions.h"

void update_velocity(BODY *bodies, double fraction)
{
    // Loop through all bodies and calculate
    for (int i = 0; i < num_bodies; i++)
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