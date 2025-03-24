#include "vars_defs_functions.h"
#include "math.h"
#include <mpi.h>

double G = 6.67430e-11;

void compute_force(BODY *bodies, int rank, int size)
{

    int bodies_per_process = num_bodies / size;
    int remainder = num_bodies % size;

    // Compute the local range of bodies for each process
    int start_index = rank * bodies_per_process + (rank < remainder ? rank : remainder);
    int local_num_bodies = bodies_per_process + (rank < remainder ? 1 : 0);

    for (int i = start_index; i < start_index + local_num_bodies; i++)
    {
        bodies[i].fx = 0;
        bodies[i].fy = 0;

        for (int j = 0; j < num_bodies; j++)
        {
            if (i == j)
            {
                continue;
            }

            double dx = bodies[j].x - bodies[i].x;
            double dy = bodies[j].y - bodies[i].y;
            double distance = sqrt(dx * dx + dy * dy) + 1e-10; // prevents dvision by zero

            double force = G * ((bodies[j].mass * bodies[i].mass) / (distance * distance));

            bodies[i].fx += force * (dx / distance);
            bodies[i].fy += force * (dy / distance);
        }
    }
    MPI_Allgather(MPI_IN_PLACE, local_num_bodies * sizeof(BODY), MPI_BYTE,
                  bodies, local_num_bodies * sizeof(BODY), MPI_BYTE, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
}
