#include "vars_defs_functions.h"
#include <omp.h>
void update_positions(BODY *bodies)
{
#pragma omp parallel for
    for (int i = 0; i < NUM_BODIES; i++)
    {
        // Retrieve current position of body n
        double current_position_x = bodies[i].x;
        double current_position_y = bodies[i].y;
        double current_position_z = bodies[i].z;

        // Retrieve current velocity of body n
        double current_velocity_x = bodies[i].vx;
        double current_velocity_y = bodies[i].vy;
        double current_velocity_z = bodies[i].vz;

        // calculate new position using formula
        double new_position_x = current_position_x + (current_velocity_x * DELTA_TIME);
        double new_position_y = current_position_y + (current_velocity_y * DELTA_TIME);
        double new_position_z = current_position_z + (current_velocity_z * DELTA_TIME);

        // Update body n position to new position
        bodies[i].x = new_position_x;
        bodies[i].y = new_position_y;
        bodies[i].z = new_position_z;
    }
}