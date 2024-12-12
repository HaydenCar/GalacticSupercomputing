     #include "vars_defs_functions.h" 
    #include "math.h"


    double distanceCalc(double xOne,double yOne,double xTwo, double yTwo){
        return sqrt(pow(xTwo - xOne, 2) + pow(yTwo - yOne, 2));
    }

    void calculate_forces(BODY *bodies){

        for (int i = 0; i < num_bodies; i++){
            // bodies[i].total_force = 0;

            bodies[i].fx = 0;
            bodies[i].fy = 0;


            for(int j = 0; j < num_bodies; j++){
                if(i==j){
                    continue;
                }
                else{
                    double distance = distanceCalc(bodies[i].x,bodies[i].y,bodies[j].x,bodies[j].y);
                    double force = G*((bodies[j].mass*bodies[i].mass)/(pow(distance,2)));                 
                    bodies[i].total_force += force;


                        //for the direction of the force we do the subtraction
                    double force_x = force * (bodies[j].x - bodies[i].x) / distance;
                    double force_y = force * (bodies[j].y - bodies[i].y) / distance;

                    bodies[i].fx += force_x;
                    bodies[i].fy += force_y;
                }
            }

        }


    }
