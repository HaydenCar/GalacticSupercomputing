#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
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
    // char address[];
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
typedef struct Node
{
    AABB bounds;
    struct Node *children[8];
    struct Node *parent;
    double COMx, COMy, COMz; // Centre Of Mass
    BODY *body;              // the node is not split and contains a body
    double Totalmass;
    bool hasChildren; // the node is split and does not contain a single body

    // int addressNum; // anywhere from 0-7 instead of a-h (easier to loop through) for now doing quad so 0-3
} Node;
// THE OCTREE
typedef struct octree
{
    Node *root;
} OCTREE;
/////////////////////////
// EXTERN VARS
/////////////////////////
extern int timestep; // The current step
extern OCTREE octree;
extern double HighestX, HighestY, HighestZ, LowestX, LowestY, LowestZ;
/////////////////////////
// CONST VALUES
/////////////////////////
#define MAX_STEP 1000000000  // Max amount of steps in the simulation
#define PRINT_INTERVAL 50000 // The data is only stored in intervals due to storage and ram
#define DELTA_TIME 0.5       // Delta time is important as the smaller the more accurate but takes way longer to run
#define GRAVITY 6.67430e-11
#define NUM_BODIES 800
#define WORLD_MIN_X -6e12
#define WORLD_MAX_X 6e12
#define WORLD_MIN_Y -6e12
#define WORLD_MAX_Y 6e12
#define WORLD_MIN_Z -6e12
#define WORLD_MAX_Z 6e12
#define MAX_THREADS 8
/////////////////////////
// FUNCTIONS
/////////////////////////
void initialise_bodies(BODY *bodies);
void update_positions(BODY *bodies);
void print_world(BODY *bodies, FILE *fp);
void update_velocity(BODY *bodies, double fraction);
void compute_force(OCTREE *octree, BODY *bodies);
void create_octree(OCTREE *octree, BODY *bodies);
Node *createNode(AABB bounds, Node *parent);
void InsertBody(Node *node, BODY *body);
void divideNode(Node *node);
Node *FindNext(Node *node, BODY *body);
void update_parent(Node *node);
void test_tree(Node *node, int depth);
void clear_tree(Node *node);
void barnes_calc(BODY *body, Node *node);
