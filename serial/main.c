#include "vars_defs_functions.h"
#include "timer.h"

int num_bodies = 3;
int update_num = 0;
// is update num just time step?
int main()
{
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
    print_world(bodies);
    // print the bodies to make sure it works

    //open file for writing
    FILE *fp = fopen("output.dat", "w");
    if (fp == NULL) {
        printf("Failed to open file for writing");
        return 1;
    }

    //Prints names at the top

    //Print initial state to file and terminal
    //prints name at the top
    //fprintf(fp, "# Type BodyIndex X_Position Y_Position Mass Velocity_X Velocity_Y\n");
    printf("Initial State:\n");
    for (int i = 0; i < num_bodies; i++) {
       // fprintf(fp, "Initial %d %.2f %.2f %.2f %.2f %.2f\n",
               // i, bodies[i].x, bodies[i].y, bodies[i].mass, bodies[i].vx, bodies[i].vy);
        printf("Body %d: x= %.2f, y= %.2f, mass= %.2f, vx= %.2f, vy= %.2f\n",
               i, bodies[i].x, bodies[i].y, bodies[i].mass, bodies[i].vx, bodies[i].vy);
    }




    // world generation loop
    for (update_num = 0; update_num < 100000; update_num++)
    {

        for (int i = 0; i < num_bodies; i++)
    {
        ///printf("Body %d: x= %.2f, y= %.2f, mass= %.2f, vx= %.2f, vy= %.2f, force= %.2f, fx = %.2f, fy=%.2f\n",
              // i, bodies[i].x, bodies[i].y, bodies[i].mass, bodies[i].vx, bodies[i].vy, bodies[i].total_force, bodies[i].fx, bodies[i].fy);
        //Print the state at every time step to file and terminal
        printf("TimeStep %d:\n", update_num);
        
            fprintf(fp, "TimeStep %d %d %.2f %.2f \n",
                update_num, i, bodies[i].x, bodies[i].y);
            printf("Body %d: x= %.2f, y= %.2f, mass= %.2f, vx= %.2f, vy= %.2f\n",
                i, bodies[i].x, bodies[i].y, bodies[i].mass, bodies[i].vx, bodies[i].vy);
    }

        update_positions(bodies, delta_time);
        compute_force(bodies);
        update_velocity(bodies, delta_time);
    }
    //Close the file
    fclose(fp);


    

    // free memory and end program
    free(bodies);
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %e seconds\n", elapsed);
    return 0;
}