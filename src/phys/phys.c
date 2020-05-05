#include <time.h>


#include "phys.h"

#include "body.h"



static Body_t bodies[PHYS_MAX_BODIES] = {0};
static int numBodies = 0;


inline float floatClock(void)
{
	return (float)clock()/CLOCKS_PER_SEC;
}



PhysId_t phys_addBody(float m, float x, float y)
{
	bodies[numBodies] = body_init(m, x, y);
	return numBodies++;
}


void phys_update(void)
{
	static float tPrev = -1;
	if (tPrev == -1) {
		tPrev = floatClock();
		return;
	}

	float tNow = floatClock();
	float dt = tNow - tPrev;
	tPrev = tNow;

	for (int i = 0; i < numBodies; i++) {
		body_update(&bodies[i], dt);
	}
}