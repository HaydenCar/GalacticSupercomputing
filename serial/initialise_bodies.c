#include "vars_defs_functions.h" // Ensure this defines BODY, num_bodies, and random generator
#include "time.h"
#include "math.h"
double distanceCalc(double xOne, double yOne, double xTwo, double yTwo);

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

        bodies[i].total_force = 0;
    }

    // double distance = distanceCalc(bodies[0].x,bodies[0].y,bodies[1].x,bodies[1].y);
    // double force = G*((bodies[1].mass*bodies[0].mass)/(pow(distance,2)));

    // bodies[0].total_force = force;
    // bodies[1].total_force = -(force);
}
