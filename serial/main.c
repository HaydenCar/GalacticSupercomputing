#include "vars_defs_functions.h"
#include "timer.h"

int num_bodies = 3;
int update_num = 0;
// is update num just time step?
int main()
{
    double delta_time = 1.0;

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
    compute_force(bodies);
    print_world(bodies);
    // print the bodies to make sure it works

    // world generation loop
    for (update_num = 0; update_num < 10; update_num++)
    {

        print_world(bodies);
        update_positions(bodies, delta_time);
        compute_force(bodies);
        update_velocity(bodies, delta_time);
    }

    update_velocity(bodies, delta_time);

    // free memory and end program
    free(bodies);
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %e seconds\n", elapsed);
    return 0;
}