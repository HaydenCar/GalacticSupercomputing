#include "vars_defs_functions.h"
#include "math.h"
#include "time.h"
void initialise_bodies(BODY *bodies)
{

    srand(time(NULL));

    
        // for (int i = 0; i < num_bodies; i++)
        // {
            

  
  //PRE-SET BODY VALUES
  
  
   double sun_m = 1.989e30;
  double earth_m = 5.972e24;
   double moon_m = 7.34767309e22;
   double e_distance = 1.496e11; // There is no exact num for this but I seen this a few times
   double m_distance = 3.844e8;

   bodies[0].x = 0.0;
   bodies[0].y = 0.0;
   bodies[0].z = 0.0;

   bodies[1].x = e_distance;
   bodies[1].y = 0.0;
   bodies[1].z = 0.0;

   bodies[2].x = e_distance + m_distance;
  bodies[2].y = 0.0;
  bodies[2].z = 0.0;

   bodies[0].mass = sun_m;
   bodies[1].mass = earth_m;
   bodies[2].mass = moon_m;

   double v_sun = sqrt(GRAVITY * sun_m / e_distance);
   double v_moon = sqrt(GRAVITY * earth_m / m_distance);

   bodies[0].vx = 0.0;
   bodies[0].vy = 0.0;
   bodies[0].vz = 0.0;

   bodies[1].vx = 0.0;
   bodies[1].vy = v_sun;
   bodies[1].vz = 0.0;

   bodies[2].vx = 0.0;
   bodies[2].vy = v_sun + v_moon;
   bodies[2].vz = 0.0;
          
          
//END PRE-SET VALUES


            //RANDOM BODIES CODE

            // Set position (x, y) with random values
            // bodies[i].x = rand() % 1000;
            // bodies[i].y = rand() % 1000;
            // bodies[i].z = rand() % 1000;
            // // Generate velocity (vx, vy)
            // bodies[i].vx = ((float)(rand() % 200) - 100) / 10.0; // vx between -10.0 and +10.0
            // bodies[i].vy = ((float)(rand() % 200) - 100) / 10.0; // vy between -10.0 and +10.0
            // bodies[i].vz = ((float)(rand() % 200) - 100) / 10.0; // vy between -10.0 and +10.0
    
            // // Set mass
            // bodies[i].mass = rand() % 1000 + 10;
    
            // bodies[i].total_force = 0;
    
            //END RANDOM BODIES CODE

        // }
}
