#ifndef VEC2_H
#define VEC2_H


typedef struct {
	double x, y;
} Vec2_t;

#define VEC2_ZERO ((Vec2_t){0, 0})

Vec2_t vec2_sum(Vec2_t v1, Vec2_t v2);

Vec2_t vec2_diff(Vec2_t v1, Vec2_t v2);

Vec2_t vec2_scale(Vec2_t v, double a);

double vec2_mag(Vec2_t v);

Vec2_t vec2_norm(Vec2_t v);

double vec2_dot(Vec2_t v1, Vec2_t v2);








#endif //VEC2_H