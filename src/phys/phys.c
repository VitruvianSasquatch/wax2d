#include <time.h>


#include "phys.h"

#include "vec2.h"
#include "body.h"



static Body_t bodies[PHYS_MAX_BODIES] = {0};
static int numBodies = 0;


static inline double doubleClock(void)
{
	return (double)clock()/CLOCKS_PER_SEC;
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



void phys_forceBody(PhysId_t b, double fx, double fy)
{
	body_applyForce(&bodies[b], (Vec2_t){fx, fy});
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