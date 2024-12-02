#include <stdlib.h>
#include <stdio.h>

typedef struct body
{
    double x; // x pos
    double y; // y pos
    double mass;
    double vx; // velocity in x dir
    double vy; // velocity in y dir
    double total_force;
    double fx; // force in x dir
    double fy; // force in y dir
    double acceleration;
} BODY;

extern int num_bodies;
extern int delta_time;
extern int time_step;

void initialise_bodies(BODY *bodies);