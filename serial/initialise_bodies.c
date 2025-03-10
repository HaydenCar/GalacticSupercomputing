#include "vars_defs_functions.h"
#include "math.h"

void initialise_bodies(BODY *bodies)
{
    double sun_m = 1.989e30;
    double earth_m = 5.972e24;
    double moon_m = 7.34767309e22;
    double e_distance = 1.496e11; // There is no exact num for this but I seen this a few times
    double m_distance = 3.844e8;

    bodies[0].x = 0.0;
    bodies[0].y = 0.0;
    bodies[1].x = e_distance;
    bodies[1].y = 0.0;
    bodies[2].x = e_distance + m_distance;
    bodies[2].y = 0.0;

    bodies[0].mass = sun_m;
    bodies[1].mass = earth_m;
    bodies[2].mass = moon_m;

    double v_sun = sqrt(GRAVITY * sun_m / e_distance);
    double v_moon = sqrt(GRAVITY * earth_m / m_distance);

    bodies[0].vx = 0.0;
    bodies[0].vy = 0.0;
    bodies[1].vx = 0.0;
    bodies[1].vy = v_sun;
    bodies[2].vx = 0.0;
    bodies[2].vy = v_sun + v_moon;

    for (int i = 0; i < num_bodies; i++)
    {
        bodies[i].fx = 0;
        bodies[i].fy = 0;
        bodies[i].total_force = 0;
    }
}
