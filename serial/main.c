#include "vars_defs_functions.h"
#include "timer.h"

int num_bodies = 2;
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
    compute_force(bodies);

    // open file for writing
    FILE *fp = fopen("output.dat", "w");
    if (fp == NULL)
    {
        printf("Failed to open file for writing");
        return 1;
    }

    printf("Initial State:\n");
    for (int i = 0; i < num_bodies; i++)
    {
        // fprintf(fp, "Initial %d %.2f %.2f %.2f %.2f %.2f\n",
        // i, bodies[i].x, bodies[i].y, bodies[i].mass, bodies[i].vx, bodies[i].vy);
        printf("Body %d: x= %.2f, y= %.2f, mass= %.2f, vx= %.2f, vy= %.2f\n",
               i, bodies[i].x, bodies[i].y, bodies[i].mass, bodies[i].vx, bodies[i].vy);
    }

    // World generation loop
    for (timestep = 0; timestep < 50000000; timestep++)
    {
        if (timestep % 500000 == 0) // Only print every 100th timestep
        {
            for (int i = 0; i < num_bodies; i++)
            {
                fprintf(fp, "TimeStep %d %d %.2f %.2f \n", timestep, i, bodies[i].x, bodies[i].y);
                printf("TimeStep %d: Body %d: x= %.2f, y= %.2f, mass= %.2f, vx= %.2f, vy= %.2f\n",
                       timestep, i, bodies[i].x, bodies[i].y, bodies[i].mass, bodies[i].vx, bodies[i].vy);
            }
        }

        // Update forces, velocities, and positions
        compute_force(bodies);
        update_velocity(bodies, delta_time);
        update_positions(bodies, delta_time);
    }

    // Close the file, free memory and end program
    fclose(fp);
    free(bodies);
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %e seconds\n", elapsed);
    return 0;
}