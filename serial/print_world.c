    #include "vars_defs_functions.h" 
    
    void print_world(BODY *bodies){
        printf("\nWORLD AT UPDATE NUMBER: %d\n",update_num);
    for (int i = 0; i < num_bodies; i++)
    {
        printf("Body %d: x= %.2f, y= %.2f, mass= %.2f, vx= %.2f, vy= %.2f\n",
               i, bodies[i].x, bodies[i].y, bodies[i].mass, bodies[i].vx, bodies[i].vy);
    }

    update_num++;

    }