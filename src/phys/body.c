#include "body.h"

#include "vec2.h"

/**
 * @brief Initialises a body with a desired mass @p m and position ( @p x , @p y ). 
 * 
 * @param m The initial mass of the body. 
 * @param x The initial x position of the body. 
 * @param y The initial y position of the body. 
 * @return Body_t The body with the specified mass and position, with all other state variables zeroed. 
 */
Body_t body_init(float m, float x, float y)
{
	Body_t body = {
		.isLocked = 0,

		.m = m, 
		.p = {x, y}, 
		.v = VEC2_ZERO,

		.F = VEC2_ZERO
	};

	return body;
}

/**
 * @brief Adds @p F to the net forces acting on @p body for this update step. 
 * 
 * @param body A reference to the body to apply a force to. 
 * @param F The force to apply. 
 */
void body_applyForce(Body_t *body, Vec2_t F)
{
	body->F = vec2_sum(body->F, F);
}

/**
 * @brief Applies the accumulated net force and update the state of @p body via simple Euler integration. 
 * 
 * @param body A reference to the body to update. 
 * @param dt The time difference between the last call to this function. 
 */
void body_update(Body_t *body, float dt)
{
	if (!body->isLocked) {
		Vec2_t a = vec2_scale(body->F, 1/body->m);
		body->F = VEC2_ZERO;
		Vec2_t dv = vec2_scale(a, dt);
		body->v = vec2_sum(body->v, dv);
		Vec2_t dp = vec2_scale(body->v, dt);
		body->p = vec2_sum(body->p, dp);
	}
}