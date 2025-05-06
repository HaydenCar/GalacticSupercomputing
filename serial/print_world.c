#include "vars_defs_functions.h"

void print_world(BODY *bodies, FILE *fp)
{
    // printf("\nWORLD AT UPDATE NUMBER: %d\n", timestep);
    for (int i = 0; i < num_bodies; i++)
    {


        fprintf(fp, "%d %d %.2f %.2f\n", timestep, i, bodies[i].x, bodies[i].y);


        // fprintf(fp, "TimeStep %d %d x: %.2f y: %.2f z: %.2f \n", timestep, i, bodies[i].x, bodies[i].y, bodies[i].z);
        // printf("TimeStep %d: Body %d: x= %.2f, y= %.2f,z= %.2f, mass= %.2f, vx= %.2f, vy= %.2f, vz= %.2f\n",
        //        timestep, i, bodies[i].x, bodies[i].y, bodies[i].z, bodies[i].mass, bodies[i].vx, bodies[i].vy, bodies[i].vz);



    }
}
