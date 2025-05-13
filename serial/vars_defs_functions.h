#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/////////////////////////
// MACRO DEFINITIONS
/////////////////////////
#define num_bodies 3
#define WorldMinX -2e11
#define WorldMaxX 2e11
#define WorldMinY -2e11
#define WorldMaxY 2e11
#define WorldMinZ -2e11
#define WorldMaxZ 2e11

extern double G;

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

extern OCTREE octree;
/////////////////////////
// EXTERN VARS
/////////////////////////

extern int timestep; // The current step

/////////////////////////
// CONST VALUES
/////////////////////////
#define MAX_STEP 2500000     // Max amount of steps in the simulation
#define PRINT_INTERVAL 20000 // The data is only stored in intervals due to storage and ram
#define DELTA_TIME 15.0      // Delta time is important as the smaller the more accurate but takes way longer to run
#define GRAVITY 6.67430e-11

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
void UpdateParent(Node *node);
void test_tree(Node *node, int depth);
void clear_tree(Node *node);
void barnesCalc(BODY *body, Node *node);
