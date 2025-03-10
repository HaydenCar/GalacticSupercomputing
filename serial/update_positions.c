#include "vars_defs_functions.h"

void update_positions(BODY *bodies)
{
    for (int i = 0; i < num_bodies; i++)
    {

        // Retrieve current position of body n
        double current_position_x = bodies[i].x;
        double current_position_y = bodies[i].y;

        // Retrieve current velocity of body n
        double current_velocity_x = bodies[i].vx;
        double current_velocity_y = bodies[i].vy;

        // Calculate new position using formula
        double new_position_x = current_position_x + (current_velocity_x * DELTA_TIME);
        double new_position_y = current_position_y + (current_velocity_y * DELTA_TIME);

        // Update body n position to new position
        bodies[i].x = new_position_x;
        bodies[i].y = new_position_y;
    }
}