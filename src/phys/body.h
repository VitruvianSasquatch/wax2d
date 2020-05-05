#ifndef BODY_H
#define BODY_H

#include "vec2.h"

typedef struct {
	int isLocked;

	//State vars:
	float m; //Mass
	Vec2_t p; //Position
	Vec2_t v; //Velocity

	//Dynamic vars:
	Vec2_t F; //Force
} Body_t;


Body_t body_init(float m, float x, float y);

void body_applyForce(Body_t *body, Vec2_t F);

void body_update(Body_t *body, float dt);

#endif //BODY_H