#include "vars_defs_functions.h"

void update_velocity(BODY *bodies, double delta_time)
{
    // loop through all bodies and calculate
    for (int i = 0; i < num_bodies; i++)
    {

        // compute the acceleration in x and y dir
        double ax = bodies[i].fx / bodies[i].mass; // acceleration in x direction
        double ay = bodies[i].fy / bodies[i].mass; // acceleration in y direction
        double az = bodies[i].fz / bodies[i].mass; // acceleration in z direction

        // update the velocity of body n
        bodies[i].vx += ax * delta_time; // new velocity in x direction
        bodies[i].vy += ay * delta_time; // new velocity in y direction
        bodies[i].vz += az * delta_time; // new velocity in z direction
    }
}