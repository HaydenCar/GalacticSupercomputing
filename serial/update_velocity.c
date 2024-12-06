#include "vars_defs_functions.h"

void update_velolcity(BODY *bodies, double delta_time)
{

    // loop through all bodies and calculate
    for (int i = 0; i < num_bodies; i++)
    {

        // compute the acceleration
        bodies[i].acceleration += (bodies[i].fx / bodies[i].mass, bodies[i].fy / bodies[i].mass);

        // update the velocity of body n
        bodies[i].vx += (bodies[i].acceleration * delta_time); // delta_time in place of timestep
        bodies[i].vy += (bodies[i].acceleration * delta_time);
    }
}