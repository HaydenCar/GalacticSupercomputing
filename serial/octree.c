#include "vars_defs_functions.h"

Node *createNode(AABB bounds, Node *parent)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->bounds = bounds;
    node->hasChildren = false;
    node->COMx = 0;
    node->COMy = 0;
    node->COMz = 0;
    node->Totalmass = 0;
    node->body = NULL;
    node->parent = parent; // necessary to distinguish the root node as root parent is NULL
    for (int i = 0; i < 8; i++)
    {
        node->children[i] = NULL;
    }

    return node;
}





void UpdateParent(Node *node)
{
    Node *parentNode = node->parent;
    while (parentNode != NULL)
    {
        parentNode->Totalmass += node->Totalmass;
        parentNode->COMx = (parentNode->COMx * (parentNode->Totalmass - node->Totalmass) + node->COMx * node->Totalmass) / parentNode->Totalmass;
        parentNode->COMy = (parentNode->COMy * (parentNode->Totalmass - node->Totalmass) + node->COMy * node->Totalmass) / parentNode->Totalmass;
        parentNode->COMz = (parentNode->COMz * (parentNode->Totalmass - node->Totalmass) + node->COMz * node->Totalmass) / parentNode->Totalmass;
        parentNode->body = NULL;
        node = parentNode;
        parentNode = node->parent;
    }
}

void divideNode(Node *node)
{
    double midX = (node->bounds.minX + node->bounds.maxX) / 2;
    double midY = (node->bounds.minY + node->bounds.maxY) / 2;
    double midZ = (node->bounds.minZ + node->bounds.maxZ) / 2;

    AABB childBounds[8] = {
        // Back (Z min)
        {midX, midY, midZ, node->bounds.minX, node->bounds.minY, node->bounds.minZ}, // 0: Bottom-left-back
        {node->bounds.maxX, midY, midZ, midX, node->bounds.minY, node->bounds.minZ}, // 1: Bottom-right-back
        {midX, node->bounds.maxY, midZ, node->bounds.minX, midY, node->bounds.minZ}, // 2: Top-left-back
        {node->bounds.maxX, node->bounds.maxY, midZ, midX, midY, node->bounds.minZ}, // 3: Top-right-back
    
        // Front (Z max)
        {midX, midY, node->bounds.maxZ, node->bounds.minX, node->bounds.minY, midZ}, // 4: Bottom-left-front
        {node->bounds.maxX, midY, node->bounds.maxZ, midX, node->bounds.minY, midZ}, // 5: Bottom-right-front
        {midX, node->bounds.maxY, node->bounds.maxZ, node->bounds.minX, midY, midZ}, // 6: Top-left-front
        {node->bounds.maxX, node->bounds.maxY, node->bounds.maxZ, midX, midY, midZ}  // 7: Top-right-front
    };

    for (int i = 0; i < 8; i++)
    {
        node->children[i] = createNode(childBounds[i], node); // Pass the current node as the parent
    }

    node->hasChildren = true;
    for (int i = 0; i < 8; i++)
{
    node->children[i] = createNode(childBounds[i], node);
    if (node->children[i] == NULL)
    {
        printf("Failed to create child node %d\n", i);
    }
  
}



}

Node *FindNext(Node *node, BODY *body)
{

    bool found = false;

    Node *nextNode;
    for (int i = 0; !found && i < 8; i++)
    {
        Node *current = node->children[i];
        AABB bounds = current->bounds;
        if (body->x <= bounds.maxX && body->x >= bounds.minX &&
            body->y <= bounds.maxY && body->y >= bounds.minY &&
            body->z <= bounds.maxZ && body->z >= bounds.minZ) 
        {
            found = true;
            nextNode = current;
        }
    }
    if (!found)
    {
        printf("error in FindNext");
    }

    return nextNode;
}

void InsertBody(Node *node, BODY *body)
{

    if (node->body == NULL && !node->hasChildren) // check if the node is capable of containing a body
    {


        node->body = body;
        node->COMx = body->x;
        node->COMy = body->y;
        node->COMz = body->z;

        node->Totalmass = body->mass;
        // only update nodes mass if was successfully added to as an external node

        UpdateParent(node); // resets the centres of mass and sets parent->body to null
        // parent node updated by UpdateParent()
    }
    else
    {

        Node *nextNode;
        if (!node->hasChildren)
        {
            // If the node has a body but no children, divide it
            divideNode(node);

            nextNode = FindNext(node, node->body);
            InsertBody(nextNode, node->body);
            nextNode = FindNext(node, body);
            InsertBody(nextNode, body);
            
            // will set parent body to null and set the new body in the new node
        }

        else{

            // the node has children

            nextNode = FindNext(node, body);

            InsertBody(nextNode, body);
            // will set parent body to null and set the new body in the new node

        }
    }
}
void test_tree(Node *node, int depth)
{


    if (node == NULL)
        return;

    // Indentation for current depth
    for (int i = 0; i < depth; i++)
        printf("  ");

    printf("Node at depth %d:\n", depth);

    for (int i = 0; i < depth; i++)
        printf("  ");


    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("COM: (%.2f, %.2f, %.2f), Mass: %.2f\n", node->COMx, node->COMy, node->COMz, node->Totalmass);

    for (int i = 0; i < depth; i++)
        printf("  ");
    if (node->body != NULL)
    {
        printf("Contains body at (%.2f, %.2f,%.2f), mass = %.2f\n",
               node->body->x, node->body->y,node->body->z, node->body->mass);
    }
    else if (!node->hasChildren)
    {
        printf("Leaf node with no body\n");
    }
    else
    {
        printf("Internal node\n");
    }
    // If the node has children, print each one
    if (node->hasChildren)
    {
        for (int i = 0; i < 8; i++)
        {
            if (node->children[i] != NULL)
            {
                test_tree(node->children[i], depth + 1);
            }
            else
            {
                for (int j = 0; j < depth + 1; j++)
                    printf("  ");
                printf("Empty child slot [%d]\n", i);
            }
        }
    }
}




void create_octree(OCTREE* octree, BODY *bodies)
{


    // printf("\nNOW STARTING NEXT TREE\n");

    AABB worldBounds;

    worldBounds.maxX = WorldMaxX;
    worldBounds.minX = WorldMinX;
    worldBounds.maxY = WorldMaxY;
    worldBounds.minY = WorldMinY;
    worldBounds.maxZ = WorldMaxZ;
    worldBounds.minZ = WorldMinZ;

    octree->root = createNode(worldBounds, NULL);


    for (int i = 0; i < num_bodies; i++)
    {

        InsertBody(octree->root, &bodies[i]);

        // test_tree(octree->root, 0);
    }

}


void clear_tree(Node *node)
{
    if (node == NULL)
    return;

if (node->hasChildren)
{
    for (int i = 0; i < 8; i++)
    {
        if (node->children[i] != NULL)
        {
            clear_tree(node->children[i]); 
            node->children[i] = NULL;
        }
    }
}

node->body = NULL;

free(node);
}

