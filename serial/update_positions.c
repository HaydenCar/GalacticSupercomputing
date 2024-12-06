#include "vars_defs_functions.h"

void update_positions(BODY *bodies, double delta_time)
{
    //printf("\n!!!!this is in update positions: %f",delta_time);

    for (int i = 0; i < num_bodies; i++)
    {

        // retrieve current position of body n
        double current_position_x = bodies[i].x;
        double current_position_y = bodies[i].y;

        // retrieve current velocity of body n
        double current_velocity_x = bodies[i].vx;
        double current_velocity_y = bodies[i].vy;

    //printf("\nthis is the current position for %d: at %f : %fx %fy",i,delta_time,current_position_x,current_position_y);

        // calculate new position using formula
        double new_position_x = current_position_x + (current_velocity_x * delta_time);
        double new_position_y = current_position_y + (current_velocity_y * delta_time);

        

    //printf("\nthis is the new position for %d: at %f : %fx %fy",i,delta_time,new_position_x,new_position_y);

        // update body n position to new position
        bodies[i].x = new_position_x;
        bodies[i].y = new_position_y;
    }
}