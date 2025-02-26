#include "vars_defs_functions.h"
#include "timer.h"
#include <mpi.h>

int num_bodies = 2;
int timestep = 0;

int main(int argc, char *argv[])
{

    // Initialize MPI
    MPI_Init(&argc, &argv);

    int rank, num_processes;
    // Get the rank (ID) of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    int bodies_per_process = num_bodies / num_processes;
    int remainder = num_bodies % num_processes;

    int start_index = rank * bodies_per_process + (rank < remainder ? rank : remainder);
    int local_num_bodies = bodies_per_process + (rank < remainder ? 1 : 0);

    // prints rank and number
    printf("Process %d of %d started.\n", rank, num_processes);

    // Delta time is important as the smaller the more accurate but takes way longer to run
    double delta_time = 0.1;

    double start, finish, elapsed;
    GET_TIME(start);

    // Declare the bodies and allocate the memory
    BODY *bodies = (BODY *)malloc(num_bodies * sizeof(BODY));
    BODY *local_bodies = (BODY *)malloc(local_num_bodies * sizeof(BODY));

    if (bodies == NULL || local_bodies == NULL)
    {
        printf("Failed to allocate memory for bodies");
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    // initialise the bodies with nums

    if (rank == 0)
    {
        initialise_bodies(bodies);
    }

    MPI_Bcast(bodies, num_bodies * sizeof(BODY), MPI_BYTE, 0, MPI_COMM_WORLD);
    // Copy assigned portion of bodies
    for (int i = 0; i < local_num_bodies; i++)
    {
        local_bodies[i] = bodies[start_index + i];
    }

    compute_force(bodies);

    // open file for writing
    FILE *fp = fopen("output.dat", "w");
    if (fp == NULL)
    {
        printf("Failed to open file for writing");
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    // World generation loop
    for (timestep = 0; timestep < 80000000; timestep++)
    {
        if (timestep % 500000 == 0) // Only print every 100th timestep
        {
            if (rank == 0)
            {
                print_world(bodies, fp);
            }
        }

        // Update forces, velocities, and positions
        // half

        ////////                need to parallelize only these
        update_velocity(bodies, delta_time);
        update_positions(bodies, delta_time);
        compute_force(bodies);
        // full
        update_velocity(bodies, delta_time);

        ///////                 up to here

        // sync all data from bodies
        MPI_Allgather(local_bodies, local_num_bodies * sizeof(BODY), MPI_BYTE,
                      bodies, local_num_bodies * sizeof(BODY), MPI_BYTE, MPI_COMM_WORLD);
    }

    // Close the file, free memory and end program
    if (rank == 0)
    {
        fclose(fp);
    }

    free(bodies);
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %e seconds\n", elapsed);

    printf("process %d reached MPI_Finalize()\n", rank);
    MPI_Finalize();

    int finalized;
    MPI_Finalized(&finalized);
    if (finalized)
    {
        printf("MPI has been successfully finalized in process %d.\n", rank);
    }
    else
    {
        printf("MPI was NOT finalized in process %d!\n", rank);
    }

    return 0;
}