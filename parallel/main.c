#include "vars_defs_functions.h"
#include "timer.h"
#include <mpi.h>

int num_bodies = 2; // Total number of bodies
int timestep = 0;

int main()
{

    // Initialize MPI
    MPI_Init;

    int rank, num_processes;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    int bodies_per_process = num_bodies / num_processes;
    int remainder = num_bodies % num_processes;

    int start_index = rank * bodies_per_process + (rank < remainder ? rank : remainder);
    int local_num_bodies = bodies_per_process + (rank < remainder ? 1 : 0);

    // debugging print to make sure even distrubution
    printf("Rank %d: start_index = %d, local_num_bodies = %d\n", rank, start_index, local_num_bodies);

    // prints rank and number of processes
    printf("Process %d of %d started.\n", rank, num_processes);

    // Delta time is important as the smaller the more accurate but takes way longer to run
    double delta_time = 0.1;

    double start, finish, elapsed;
    GET_TIME(start);

    // Declare the bodies and allocate the memory
    BODY *bodies = (BODY *)malloc(num_bodies * sizeof(BODY));
    if (bodies == NULL)
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

    // turns Body into mpi datatype
    MPI_Datatype MPI_BODY;
    MPI_Type_contiguous(sizeof(BODY), MPI_BYTE, &MPI_BODY);
    MPI_Type_commit(&MPI_BODY);

    // broadcast array to other processes
    MPI_Bcast(bodies, num_bodies, MPI_BODY, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    // Open file for writing output
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
        if (timestep % 1000000 == 0) // Only print every 500,000th timestep
        {
            if (rank == 0)
            {
                print_world(bodies, fp); // Print world state from process 0
            }
        }

        // Update forces, velocities, and positions for local bodies
        // these have been mpi implemented?
        // printf("Rank %d: Starting compute_force for timestep %d\n", rank, timestep);

        compute_force(bodies, rank, num_processes);
        // printf("Rank %d: completed compute_force for timestep %d\n", rank, timestep);

        update_velocity(bodies, delta_time, rank, num_processes);
        // printf("Rank %d: completed update velocity for timestep %d\n", rank, timestep);

        update_positions(bodies, delta_time, rank, num_processes);

        compute_force(bodies, rank, num_processes);

        // Full update step
        update_velocity(bodies, delta_time, rank, num_processes);
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Close the file, free memory and end program
    if (rank == 0)
    {
        fclose(fp);
    }

    free(bodies);

    MPI_Type_free(&MPI_BODY);

    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %.6f seconds\n", elapsed);

    printf("Process %d reached MPI_Finalize()\n", rank);
    MPI_Barrier(MPI_COMM_WORLD);

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
