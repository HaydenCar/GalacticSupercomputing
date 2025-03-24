#include "vars_defs_functions.h"
#include <mpi.h>

void update_positions(BODY *bodies, double delta_time, int rank, int size)
{ // divides bodies by processes
    int bodies_per_process = num_bodies / size;
    // remainder
    int remainder = num_bodies % size;

    int start_index = rank * bodies_per_process + (rank < remainder ? rank : remainder);
    int local_num_bodies = bodies_per_process + (rank < remainder ? 1 : 0);

    for (int i = start_index; i < start_index + local_num_bodies; i++)
    {

        // retrieve current position of body n
        double current_position_x = bodies[i].x;
        double current_position_y = bodies[i].y;

        // retrieve current velocity of body n
        double current_velocity_x = bodies[i].vx;
        double current_velocity_y = bodies[i].vy;

        // calculate new position using formula
        double new_position_x = current_position_x + (current_velocity_x * delta_time);
        double new_position_y = current_position_y + (current_velocity_y * delta_time);

        // update body n position to new position
        bodies[i].x = new_position_x;
        bodies[i].y = new_position_y;
    }

    MPI_Allgather(MPI_IN_PLACE, local_num_bodies * sizeof(BODY), MPI_BYTE,
                  bodies, local_num_bodies * sizeof(BODY), MPI_BYTE, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
}