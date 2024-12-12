#include "vars_defs_functions.h"
#include "math.h"
double G = 6.67430;

double distanceCalc(double xOne, double yOne, double xTwo, double yTwo)
{
    return sqrt(pow(xTwo - xOne, 2) + pow(yTwo - yOne, 2));
}
void compute_force(BODY *bodies)
{

    for (int i = 0; i < num_bodies; i++)
    {
        // bodies[i].total_force = 0;

        bodies[i].fx = 0;
        bodies[i].fy = 0;

        for (int j = 0; j < num_bodies; j++)
        {
            if (i == j)
            {
                continue;
            }
            else
            {
                double distance = distanceCalc(bodies[i].x, bodies[i].y, bodies[j].x, bodies[j].y);

                printf("distance is: %f",distance);

                double force = G * ((bodies[j].mass * bodies[i].mass) / (pow(distance, 2)));

                printf("force !!!!!: %f", force);

                bodies[i].total_force += force;
                printf("TOTAL FORCE IS: %f",bodies[i].total_force );
                // for the direction of the force we do the subtraction
                double force_x = force * (bodies[j].x - bodies[i].x) / distance;
                double force_y = force * (bodies[j].y - bodies[i].y) / distance;

                printf("Force new x: %f",force_x);
                printf("Force new y: %f",force_y);



                bodies[i].fx += force_x;
                bodies[i].fy += force_y;
            }
        }
    }
}
