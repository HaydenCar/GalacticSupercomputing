#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/////////////////////////
// BODY STRUCTS
/////////////////////////

typedef struct body
{
    double x; // x pos
    double y; // y pos
    double z;
    double mass;
    double vx; // velocity in x dir
    double vy; // velocity in y dir
    double vz;
    double total_force;
    double fx; // force in x dir
    double fy; // force in y dir
    double fz;
    double acceleration;
    char address[];
} BODY;

/////////////////////////
// OCTREE STRUCTS
/////////////////////////

// AXIS ALLIGNED BOUNDING BOX
// https://stackoverflow.com/questions/22512319/what-is-aabb-collision-detection
typedef struct aabb
{
    double maxX;
    double maxY;
    double maxZ;
    double minX;
    double minY;
    double minZ;
} AABB;

// OCTREE NODE
typedef struct node
{
    AABB aabb;
    double xp;
    double yp;
    double zp;
    BODY **bodies;
    double mass;
    uint16_t bodyCount;
    char c;
    struct NODE *leafs[8];
} NODE;

// THE OCTREE
typedef struct octree
{
    NODE root;
} OCTREE;

/////////////////////////
// EXTERN VARS
/////////////////////////

extern int num_bodies;
extern int timestep;

/////////////////////////
// FUNCTIONS
/////////////////////////

void initialise_bodies(BODY *bodies);
void update_positions(BODY *bodies, double delta_time);
void print_world(BODY *bodies, FILE *fp);
void update_velocity(BODY *bodies, double delta_time);
void compute_force(BODY *bodies);