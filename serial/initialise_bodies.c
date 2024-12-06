#include "vars_defs_functions.h" // Ensure this defines BODY, num_bodies, and random generator
#include "time.h"

void initialise_bodies(BODY *bodies)
{
    srand(time(NULL));


//    double mass;
//     double total_force;
//     double acceleration;


    for (int i = 0; i < num_bodies; i++)
    {
        // Set position (x, y) with random values
        bodies[i].x = rand() % 1000;
        bodies[i].y = rand() % 1000;

        // Generate velocity (vx, vy)
        bodies[i].vx = ((float)(rand() % 200) - 100) / 10.0; // vx between -10.0 and +10.0
        bodies[i].vy = ((float)(rand() % 200) - 100) / 10.0; // vy between -10.0 and +10.0


        // Set mass
        bodies[i].mass = rand() % 1000 + 10;
    }
}
