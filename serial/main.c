#include "vars_defs_functions.h"
#include "timer.h"

int num_bodies = 3;

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
    double delta_time = start - delta;
    printf("\nthis is in main: %f",delta_time);
    update_positions(bodies, delta_time);


    print_world(bodies);



    // free memory and end program
    free(bodies);
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %e seconds\n", elapsed);
    return 0;
}