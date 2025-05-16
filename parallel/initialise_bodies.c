#include "vars_defs_functions.h"
#include "math.h"
#include "time.h"

void initialise_bodies(BODY *bodies)
{
    srand(time(NULL));
    // PRE-SET BODY VALUES
    double sun_m = 1.989e30;
    double earth_m = 5.972e24;
    double mercury_m = 3.301e23; // Wikipedia lol
    double venus_m = 4.867e24;
    double mars_m = 6.390e23;
    double jupiter_m = 1.898e27;
    double saturn_m = 5.683e26;
    double uranus_m = 8.682e25;
    double neptune_m = 1.024e26;
    double pluto_m = 1.310e22;
    // These are distance from sun
    double earth_distance = 1.496e11;   // There is no exact num for this but I seen this a few times
    double mercury_distance = 5.800e10; // AGAIN ALL THESE ARE RANDOM DUE TO IT ALWYS CHANGING
    double venus_distance = 1.087e11;
    double mars_distance = 2.280e11;
    double jupiter_distance = 7.780e11;
    double saturn_distance = 1.433e12;
    double uranus_distance = 2.920e12;
    double neptune_distance = 4.471e12;
    double pluto_distance = 5.910e12;

    // SUN
    bodies[0].x = 0.0;
    bodies[0].y = 0.0;
    bodies[0].z = 0.0;

    // EARTH
    bodies[1].x = earth_distance;
    bodies[1].y = 0.0;
    bodies[1].z = 1.0e7;

    // MERCURY
    bodies[2].x = mercury_distance;
    bodies[2].y = 0.0;
    bodies[2].z = 0.5e7;

    // VENUS
    bodies[3].x = venus_distance;
    bodies[3].y = 0.0;
    bodies[3].z = -0.8e7;

    // MARS
    bodies[4].x = mars_distance;
    bodies[4].y = 0.0;
    bodies[4].z = -1.2e7;

    // JUPITER
    bodies[5].x = jupiter_distance;
    bodies[5].y = 0.0;
    bodies[5].z = 1.5e7;

    // SATURN
    bodies[6].x = saturn_distance;
    bodies[6].y = 0.0;
    bodies[6].z = -2.0e7;

    // URANUS
    bodies[7].x = uranus_distance;
    bodies[7].y = 0.0;
    bodies[7].z = 2.5e7;

    // NEPTUNE
    bodies[8].x = neptune_distance;
    bodies[8].y = 0.0;
    bodies[8].z = -3.0e7;

    // PLUTO
    bodies[9].x = pluto_distance;
    bodies[9].y = 0.0;
    bodies[9].z = 4.0e7;

    bodies[0].mass = sun_m;
    bodies[1].mass = earth_m;
    bodies[2].mass = mercury_m;
    bodies[3].mass = venus_m;
    bodies[4].mass = mars_m;
    bodies[5].mass = jupiter_m;
    bodies[6].mass = saturn_m;
    bodies[7].mass = uranus_m;
    bodies[8].mass = neptune_m;
    bodies[9].mass = pluto_m;

    double v_earth = sqrt(GRAVITY * sun_m / earth_distance);
    double v_mercury = sqrt(GRAVITY * sun_m / mercury_distance);
    double v_venus = sqrt(GRAVITY * sun_m / venus_distance);
    double v_mars = sqrt(GRAVITY * sun_m / mars_distance);
    double v_jupiter = sqrt(GRAVITY * sun_m / jupiter_distance);
    double v_saturn = sqrt(GRAVITY * sun_m / saturn_distance);
    double v_uranus = sqrt(GRAVITY * sun_m / uranus_distance);
    double v_neptune = sqrt(GRAVITY * sun_m / neptune_distance);
    double v_pluto = sqrt(GRAVITY * sun_m / pluto_distance);

    bodies[0].vx = 0.0;
    bodies[0].vy = 0.0;
    bodies[0].vz = 0.0;

    bodies[1].vx = 0.0;
    bodies[1].vy = v_earth;
    bodies[1].vz = 0.0;

    bodies[2].vx = 0.0;
    bodies[2].vy = v_mercury;
    bodies[2].vz = 0.0;

    bodies[3].vx = 0.0;
    bodies[3].vy = v_venus;
    bodies[3].vz = 0.0;

    bodies[4].vx = 0.0;
    bodies[4].vy = v_mars;
    bodies[4].vz = 0.0;

    bodies[5].vx = 0.0;
    bodies[5].vy = v_jupiter;
    bodies[5].vz = 0.0;

    bodies[6].vx = 0.0;
    bodies[6].vy = v_saturn;
    bodies[6].vz = 0.0;

    bodies[7].vx = 0.0;
    bodies[7].vy = v_uranus;
    bodies[7].vz = 0.0;

    bodies[8].vx = 0.0;
    bodies[8].vy = v_neptune;
    bodies[8].vz = 0.0;

    bodies[9].vx = 0.0;
    bodies[9].vy = v_pluto;
    bodies[9].vz = 0.0;

    // END PRE-SET VALUES

    // RANDOM BODIES CODE

    // Set position (x, y) with random values

    double min_distance = 1.0e7;             // minimum distance between any two bodies
    double max_distance_from_sun = 1.496e11; // Earth's orbit
    int max_attempts = 100;

    for (int i = 9; i < NUM_BODIES; i++)
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
