#include "vars_defs_functions.h"
#include "math.h"

void barnes_calc(BODY *body, Node *node)
{
    if (node == NULL || (node->body == body && !node->hasChildren))
        return;

    double dx = node->COMx - body->x;
    double dy = node->COMy - body->y;
    double dz = node->COMz - body->z;
    double distance = sqrt(dx * dx + dy * dy + dz * dz);

    double s = node->bounds.maxX - node->bounds.minX; // length of the cube
    double theta = 0.5;

    // is this node far enough? s/d < theta
    if (!node->hasChildren || (s / distance < theta))
    {
        if (node->Totalmass > 0 && node->body != body)
        {
            double force = G * body->mass * node->Totalmass / (distance * distance);
            body->fx += force * dx / distance;
            body->fy += force * dy / distance;
            body->fz += force * dz / distance;
        }
    }
    else
    {
        // if too close
        for (int i = 0; i < 8; i++)
        {
            if (node->children[i] != NULL)
                barnes_calc(body, node->children[i]);
        }
    }
}
