#include "vars_defs_functions.h"
#include "math.h"

void initialise_bodies(BODY *bodies)
{
    if (num_bodies != 2)
        return;

    double mass1 = 1e6;
    double mass2 = 1e6;
    double distance = 200.0;
    double G = 6.67430e-11;

    bodies[0].x = -distance / 2.0;
    bodies[0].y = 0.0;
    bodies[1].x = distance / 2.0;
    bodies[1].y = 0.0;

    bodies[0].mass = mass1;
    bodies[1].mass = mass2;

    double v = sqrt(G * (mass1 + mass2) / distance);

    bodies[0].vx = 0.0;
    bodies[0].vy = v * (mass2 / (mass1 + mass2));
    bodies[1].vx = 0.0;
    bodies[1].vy = -v * (mass1 / (mass1 + mass2));

    for (int i = 0; i < num_bodies; i++)
    {
        bodies[i].fx = 0;
        bodies[i].fy = 0;
        bodies[i].total_force = 0;
    }
}
