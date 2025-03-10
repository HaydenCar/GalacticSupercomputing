#include "vars_defs_functions.h"
#include "math.h"

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
                // Logic to handle collison here!!
                continue;
            }

            double dx = bodies[j].x - bodies[i].x;
            double dy = bodies[j].y - bodies[i].y;
            double distance = sqrt(dx * dx + dy * dy);

            double force = GRAVITY * ((bodies[j].mass * bodies[i].mass) / (distance * distance));

            bodies[i].fx += force * (dx / distance);
            bodies[i].fy += force * (dy / distance);
        }
    }
}
