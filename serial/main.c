#include "vars_defs_functions.h"
#include "timer.h"

int num_bodies = 3;
int update_num = 0;

int main()
{

    double start, finish, elapsed, delta;
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
    // print the bodies to make sure it works

    print_world(bodies);

    GET_TIME(delta);

    printf("this is what start is %f", start);
    printf("this is what delta is %f", delta);

    //! PROBLEM WAS HERE: start and delta are equal, delta time = 0?
    // double delta_time = start - delta;

    double delta_time = 1.0;
    printf("\nthis is in main: %f", delta_time);
    update_positions(bodies, delta_time);

    print_world(bodies);

    update_velocity(bodies, delta_time);

    // free memory and end program
    free(bodies);
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %e seconds\n", elapsed);
    return 0;
}