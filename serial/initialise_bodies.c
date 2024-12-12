#include "vars_defs_functions.h" // Ensure this defines BODY, num_bodies, and random generator
#include "time.h"
#include "math.h"

void initialise_bodies(BODY *bodies)
{
    srand(time(NULL));

    for (int i = 0; i < num_bodies; i++)
    {
        // Set position (x, y) with random values between 0.0 and 1000.0
        bodies[i].x = -5000.00 + ((double)rand() / RAND_MAX) * (10000.00);
        bodies[i].y = -5000.00 + ((double)rand() / RAND_MAX) * (10000.00);

        // Generate velocity (vx, vy) with random values between -10.0 and 10.0
        bodies[i].vx = -10.00 + ((double)rand() / RAND_MAX) * (10.00 - (-10.00));
        bodies[i].vy = -10.00 + ((double)rand() / RAND_MAX) * (10.00 - (-10.00));

        // Set mass to a random value between 10 and 1000
        bodies[i].mass = 10.00 + ((double)rand() / RAND_MAX) * (10000000.00 - 10.00);

        // Initialize forces to 0
        bodies[i].fx = 0;
        bodies[i].fy = 0;
        bodies[i].total_force = 0;
    }
}
