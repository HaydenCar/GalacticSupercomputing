#include "vars_defs_functions.h"
#include "math.h"

void initialise_bodies(BODY *bodies)
{
    if (num_bodies != 2)
    {
        return;
    }

    double sun_m = 1.989e30;
    double earth_m = 5.972e24;
    double distance = 1.496e11; // There is no exact num for this but I seen this a few times
    double G = 6.67430e-11;

    bodies[0].x = 0.0;
    bodies[0].y = 0.0;
    bodies[1].x = distance;
    bodies[1].y = 0.0;

    bodies[0].mass = sun_m;
    bodies[1].mass = earth_m;

    double v = sqrt(G * sun_m / distance);

    bodies[0].vx = 0.0;
    bodies[0].vy = 0.0;
    bodies[1].vx = 0.0;
    bodies[1].vy = v;

    for (int i = 0; i < num_bodies; i++)
    {
        bodies[i].fx = 0;
        bodies[i].fy = 0;
        bodies[i].total_force = 0;
    }
}
