#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/////////////////////////
// MACRO DEFINITIONS
/////////////////////////

#define WorldMinX -10000
#define WorldMaxX 10000
#define WorldMinY -10000
#define WorldMaxY 10000
#define WorldMinZ -10000
#define WorldMaxZ 10000

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
    struct Node* children[8];
    struct Node* parent;
    double COMx,COMy,COMz; //Centre Of Mass
    BODY* body; // the node is not split and contains a body
    double Totalmass;
    bool hasChildren; // the node is split and does not contain a single body

    // int addressNum; // anywhere from 0-7 instead of a-h (easier to loop through) for now doing quad so 0-3
} Node;



// THE OCTREE
typedef struct octree
{
    Node* root;
} OCTREE;


extern OCTREE octree;
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
void compute_force(OCTREE* octree,BODY *bodies);


void create_octree(OCTREE *octree, BODY *bodies);
Node* createNode(AABB bounds,Node* parent);
void InsertBody(Node* node, BODY* body);
void divideNode(Node* node);
Node* FindNext(Node* node, BODY *body);
void UpdateParent(Node *node);
void test_tree(Node *node, int depth);
void clear_tree(Node *node);
void barnesCalc(BODY *body, Node *node);
