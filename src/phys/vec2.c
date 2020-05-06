#include <math.h>

#include "vec2.h"


Vec2_t vec2_sum(Vec2_t v1, Vec2_t v2)
{
	Vec2_t ans = {v1.x + v2.x, v1.y + v2.y};
	return ans;
}

Vec2_t vec2_diff(Vec2_t v1, Vec2_t v2)
{
	Vec2_t ans = {v1.x - v2.x, v1.y - v2.y};
	return ans;
}

Vec2_t vec2_scale(Vec2_t v, double a)
{
	Vec2_t ans = {v.x * a, v.y * a};
	return ans;
}

double vec2_mag(Vec2_t v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

Vec2_t vec2_norm(Vec2_t v)
{
	return vec2_scale(v, 1/vec2_mag(v));
}

double vec2_dot(Vec2_t v1, Vec2_t v2)
{
	double ans = v1.x*v2.x + v1.y*v2.y;
	return ans;
}