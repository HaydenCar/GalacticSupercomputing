#include "vars_defs_functions.h"
#include "math.h"

void compute_force(OCTREE *octree, BODY *bodies)
{
    for (int i = 0; i < NUM_BODIES; i++)
    {
        bodies[i].fx = 0;
        bodies[i].fy = 0;
        bodies[i].fz = 0;

        barnes_calc(&bodies[i], octree->root);
    }
}
