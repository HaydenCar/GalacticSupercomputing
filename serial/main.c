#include "vars_defs_functions.h"
#include "timer.h"

int num_bodies = 4;
int timestep = 0;

int main()
{
    // Delta time is important as the smaller the more accurate but takes way longer to run
    double delta_time = 0.1;

    double start, finish, elapsed;
    GET_TIME(start);

    // Declare the bodies and allocate the memory
    BODY *bodies = (BODY *)malloc(num_bodies * sizeof(BODY));
    
    if (bodies == NULL)
    {
        printf("Failed to allocate memory for bodies");
        return 1;
    }

    // initialise the bodies with random nums
    initialise_bodies(bodies);
    create_octree(bodies);
    compute_force(bodies);

    // open file for writing
    FILE *fp = fopen("output.dat", "w");
    if (fp == NULL)
    {
        printf("Failed to open file for writing");
        return 1;
    }

    // World generation loop
    // for (timestep = 0; timestep < 80000000; timestep++)
    for (timestep = 0; timestep < 2; timestep++)

    {
        // if (timestep % 500000 == 0) // Only print every 100th timestep
        // {
            print_world(bodies, fp);
        // }

        // Update forces, velocities, and positions
        // half
        update_velocity(bodies, delta_time);
        update_positions(bodies, delta_time);
        compute_force(bodies);
        // full
        update_velocity(bodies, delta_time);
    }

    // Close the file, free memory and end program
    fclose(fp);
    free(bodies);
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %e seconds\n", elapsed);
    return 0;
}