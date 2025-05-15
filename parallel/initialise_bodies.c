#include "vars_defs_functions.h"
#include "math.h"
#include "time.h"

void initialise_bodies(BODY *bodies)
{
    srand(time(NULL));
    // PRE-SET BODY VALUES
    double sun_m = 1.989e30;
    double earth_m = 5.972e24;
    double moon_m = 7.34767309e22;
    double e_distance = 1.496e11; // There is no exact num for this but I seen this a few times
    double m_distance = 3.844e8;

    bodies[0].x = 0.0;
    bodies[0].y = 0.0;
    bodies[0].z = 1.0e7;

    bodies[1].x = e_distance;
    bodies[1].y = 0.0;
    bodies[1].z = 1000.0;

    bodies[2].x = e_distance + m_distance;
    bodies[2].y = 0.0;
    bodies[2].z = 1.0e7;

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

    // END PRE-SET VALUES

    // RANDOM BODIES CODE

    // Set position (x, y) with random values

    double min_distance = 1.0e7;             // minimum distance between any two bodies
    double max_distance_from_sun = 1.496e11; // Earth's orbit
    int max_attempts = 100;

    for (int i = 3; i < NUM_BODIES; i++)
    {
        int attempt = 0;
        int valid = 0;
        while (!valid && attempt < max_attempts)
        {
            double x = WORLD_MIN_X + ((double)rand() / RAND_MAX) * (WORLD_MAX_X - WORLD_MIN_X);
            double y = WORLD_MIN_Y + ((double)rand() / RAND_MAX) * (WORLD_MAX_Y - WORLD_MIN_Y);
            double z = WORLD_MIN_Z + ((double)rand() / RAND_MAX) * (WORLD_MAX_Z - WORLD_MIN_Z);

            // Check for distance from all existing bodies so they arent too close together
            valid = 1;
            for (int j = 0; j < i; j++)
            {
                double dx = x - bodies[j].x;
                double dy = y - bodies[j].y;
                double dz = z - bodies[j].z;
                double dist = sqrt(dx * dx + dy * dy + dz * dz);
                if (dist < min_distance)
                {
                    valid = 0;
                    break;
                }
            }

            if (valid)
            {
                bodies[i].x = x;
                bodies[i].y = y;
                bodies[i].z = z;
            }
            attempt++;
        }

        if (!valid)
        {
            printf("Failed to place body %d without overlapping after %d attempts\n", i, max_attempts);
            // Fallback: place far away
            bodies[i].x = bodies[i].y = bodies[i].z = max_distance_from_sun + i * min_distance;
        }

        bodies[i].vx = ((double)rand() / RAND_MAX - 0.5) * 2.0 * 1.0e4;
        bodies[i].vy = ((double)rand() / RAND_MAX - 0.5) * 2.0 * 1.0e4;
        bodies[i].vz = ((double)rand() / RAND_MAX - 0.5) * 2.0 * 1.0e4;

        bodies[i].mass = 1e25 + ((double)rand() / RAND_MAX) * 2.0 * (1e25 - 1e20);

        bodies[i].total_force = 0;
    }
    // END RANDOM BODIES CODE
}
