#include "vars_defs_functions.h"

void update_velocity(BODY *bodies, double delta_time)
{
    // loop through all bodies and calculate
    for (int i = 0; i < num_bodies; i++)
    {
        printf("Body %d Velocity x is: %f, and y is: %f\n", i, bodies[i].vx, bodies[i].vy);
        // compute the acceleration in x and y dir
        double ax = bodies[i].fx / bodies[i].mass; // Acceleration in x direction
        double ay = bodies[i].fy / bodies[i].mass; // Acceleration in y direction
        ax = ax * delta_time;
        ay = ay * delta_time;

        // update the velocity of body n
        bodies[i].vx += ax; // New velocity in x direction
        bodies[i].vy += ay; // New velocity in y direction
    }
}