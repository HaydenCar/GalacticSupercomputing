#include "vars_defs_functions.h"

void print_world(BODY *bodies, FILE *fp)
{
    // printf("\nWORLD AT UPDATE NUMBER: %d\n", timestep);
    for (int i = 0; i < NUM_BODIES; i++)
    {
        fprintf(fp, "%d %d %.2f %.2f %.2f\n", timestep, i, bodies[i].x, bodies[i].y, bodies[i].z);
    }
}
