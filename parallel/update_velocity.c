#include "vars_defs_functions.h"
#include <mpi.h>

void update_velocity(BODY *bodies, double delta_time, int rank, int size)
{
    int bodies_per_process = num_bodies / size;
    int remainder = num_bodies % size;

    int start_index = rank * bodies_per_process + (rank < remainder ? rank : remainder);
    int local_num_bodies = bodies_per_process + (rank < remainder ? 1 : 0);

    // loop through all bodies and calculate
    for (int i = start_index; i < start_index + local_num_bodies; i++)
    {

        // compute the acceleration in x and y dir
        double ax = bodies[i].fx / bodies[i].mass; // acceleration in x direction
        double ay = bodies[i].fy / bodies[i].mass; // acceleration in y direction

        // update the velocity of body n
        bodies[i].vx += ax * (delta_time / 2.0); // new velocity in x direction
        bodies[i].vy += ay * (delta_time / 2.0); // new velocity in y direction

        MPI_Allgather(MPI_IN_PLACE, local_num_bodies * sizeof(BODY), MPI_BYTE,
                      bodies, local_num_bodies * sizeof(BODY), MPI_BYTE, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
    }
}