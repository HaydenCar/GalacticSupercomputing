#include "vars_defs_functions.h"

void update_velocity(BODY *bodies)
{
    double half = 2.0;
    // Loop through all bodies and calculate
    for (int i = 0; i < num_bodies; i++)
    {

        // Compute the acceleration in x and y dir
        double ax = bodies[i].fx / bodies[i].mass; // Acceleration in x direction
        double ay = bodies[i].fy / bodies[i].mass; // Acceleration in y direction

        // Update the velocity of body n
        bodies[i].vx += ax * (DELTA_TIME / half); // New velocity in x direction
        bodies[i].vy += ay * (DELTA_TIME / half); // New velocity in y direction
    }
}