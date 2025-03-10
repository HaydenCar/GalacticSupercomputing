#include "vars_defs_functions.h"
#include "timer.h"

int num_bodies = 3;
int timestep = 0;

int main()
{
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
    compute_force(bodies);

    // open file for writing
    FILE *fp = fopen("output.dat", "w");
    if (fp == NULL)
    {
        printf("Failed to open file for writing");
        return 1;
    }

    // Print step 0
    print_world(bodies, fp);
    timestep++;

    // World generation loop
    for (; timestep < MAX_STEP; timestep++)
    {
        if (timestep % PRINT_INTERVAL == 0) // Only print every 100th timestep
        {
            print_world(bodies, fp);
        }

        // Update forces, velocities, and positions
        // half
        update_velocity(bodies);
        update_positions(bodies);
        compute_force(bodies);
        // full
        update_velocity(bodies);
    }

    // Close the file, free memory and end program
    fclose(fp);
    free(bodies);
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %e seconds\n", elapsed);
    return 0;
}