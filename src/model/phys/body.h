#ifndef BODY_H
#define BODY_H

#include "vec2.h"

typedef struct {
	int isLocked;

	//Shape vars:
	double width;
	double height;

	//State vars:
	double m; //Mass
	Vec2_t p; //Position
	Vec2_t v; //Velocity

	//Dynamic vars:
	Vec2_t F; //Force
} Body_t;


Body_t body_init(double m, Vec2_t pos, double width, double height);

void body_applyForce(Body_t *body, Vec2_t F);

void body_applyImpulse(Body_t *body, Vec2_t dp);

void body_collide(Body_t *b1, Body_t *b2, double F);

void body_update(Body_t *body, double dt);

#endif //BODY_H