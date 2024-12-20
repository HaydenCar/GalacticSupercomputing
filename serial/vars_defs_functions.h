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
extern int update_num;

void initialise_bodies(BODY *bodies);
void update_positions(BODY *bodies, double delta_time);
void print_world(BODY *bodies);
void update_velocity(BODY *bodies, double delta_time);
void compute_force(BODY *bodies);