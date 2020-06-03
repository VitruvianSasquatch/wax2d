#include <time.h>
#include <unistd.h>


#include "phys.h"

#include "vec2.h"
#include "body.h"

#include <stdio.h>



static Body_t bodies[PHYS_MAX_BODIES] = {0};
static int numBodies = 0;


static inline double doubleClock(void)
{
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return (double)t.tv_sec + (double)t.tv_nsec/1e9;
}



PhysId_t phys_addBody(double m, double x, double y)
{
	bodies[numBodies] = body_init(m, x, y);
	return numBodies++;
}



void phys_collide(PhysId_t a, PhysId_t b, double F) {
	Vec2_t dirAB = vec2_norm(vec2_diff(bodies[b].p, bodies[a].p));
	body_applyForce(&bodies[a], vec2_scale(dirAB, F));
	body_applyForce(&bodies[b], vec2_scale(dirAB, -F));
}



void phys_forceBody(PhysId_t b, Vec2_t f)
{
	body_applyForce(&bodies[b], f);
}



void phys_applyImpulse(PhysId_t b, Vec2_t dp)
{
	bodies[b].v = vec2_sum(bodies[b].v, vec2_scale(dp, 1/bodies[b].m));
}


Vec2_t phys_getBodyPos(PhysId_t id)
{
	return bodies[id].p;
}



void phys_update(void)
{
	static double tPrev = -1;
	if (tPrev == -1) {
		tPrev = doubleClock();
		return;
	}

	double tNow = doubleClock();
	double dt = tNow - tPrev;
	tPrev = tNow;

	for (int i = 0; i < numBodies; i++) {
		body_update(&bodies[i], dt);
	}
}