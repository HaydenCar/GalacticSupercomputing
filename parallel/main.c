#include "vars_defs_functions.h"
#include "timer.h"

int timestep = 0;
OCTREE octree;

int main()
{
    double start, finish, elapsed;
    GET_TIME(start);

    // Declare the bodies and allocate the memory
    BODY *bodies = (BODY *)malloc(NUM_BODIES * sizeof(BODY));

    if (bodies == NULL)
    {
        printf("Failed to allocate memory for bodies");
        return 1;
    }

    // Initialise the bodies with random nums
    initialise_bodies(bodies);
    create_octree(&octree, bodies);
    compute_force(&octree, bodies);

    // Open file for writing
    FILE *fp = fopen("../Engine/Dependencies/output.dat", "w");
    if (fp == NULL)
    {
        printf("Failed to open file for writing");
        return 1;
    }

    // Print step 0
    print_world(bodies, fp);
    timestep++;

    // World generation loop
    for (; timestep <= MAX_STEP; timestep++)
    {
        if (timestep % PRINT_INTERVAL == 0 || timestep == MAX_STEP) // Only print every 100th timestep
        {
            // print("Step: %d", timestep);
            print_world(bodies, fp);
        }

        // double startOCTREE, endOCTREE, elapsedOCTREE;

        // Update forces, velocities, and positions
        update_velocity(bodies, 0.5); // half step
        update_positions(bodies);     // full step

        if (timestep % 20 == 0)
        {

            clear_tree(octree.root);
            octree.root = NULL;

            // GET_TIME(startOCTREE);
            create_octree(&octree, bodies);
            // GET_TIME(endOCTREE);

            // elapsedOCTREE = endOCTREE - startOCTREE;
            // printf("The octree to be timed took %lf seconds\n", elapsedOCTREE);
        }

        compute_force(&octree, bodies);
        update_velocity(bodies, 0.5); // second half step
    }

    clear_tree(octree.root);
    octree.root = NULL;
    // Close the file, free memory and end program
    fclose(fp);
    free(bodies);
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %lf seconds\n", elapsed);
    return 0;
}