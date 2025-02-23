#include "vars_defs_functions.h"
#include "math.h"

double G = 6.67430e-11;

void compute_force(BODY *bodies)
{
    for (int i = 0; i < num_bodies; i++)
    {
        bodies[i].fx = 0;
        bodies[i].fy = 0;

        for (int j = 0; j < num_bodies; j++)
        {
            if (i == j)
            {
                continue;
            }

            double dx = bodies[j].x - bodies[i].x;
            double dy = bodies[j].y - bodies[i].y;
            double distance = sqrt(dx * dx + dy * dy);

            double force = G * ((bodies[j].mass * bodies[i].mass) / (distance * distance));

            bodies[i].fx += force * (dx / distance);
            bodies[i].fy += force * (dy / distance);
        }
    }
}
