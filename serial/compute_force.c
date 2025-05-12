#include "vars_defs_functions.h"
#include "math.h"


void compute_force(OCTREE* octree,BODY *bodies)

{
    for (int i = 0; i < num_bodies; i++)
    {
        bodies[i].fx = 0;
        bodies[i].fy = 0;
        bodies[i].fz = 0;

        // for (int j = 0; j < num_bodies; j++)
        // {
        //     bodies[i].fx = 0;
        //     bodies[i].fy = 0;
        //     bodies[i].fz = 0;
            // if (i == j)
            // {
            //     continue;
            // }
            // double dx = bodies[j].x - bodies[i].x;
            // double dy = bodies[j].y - bodies[i].y;
            // double dz = bodies[j].z - bodies[i].z;
            // double distance = sqrt(dx * dx + dy * dy + dz * dz);
            // double force = G * ((bodies[j].mass * bodies[i].mass) / (distance * distance));
            // bodies[i].fx += force * (dx / distance);
            // bodies[i].fy += force * (dy / distance);
            // bodies[i].fz += force * (dz / distance);
            barnesCalc(&bodies[i], octree->root);
            //double force = GRAVITY * ((bodies[j].mass * bodies[i].mass) / (distance * distance));
        // }
    }
}
