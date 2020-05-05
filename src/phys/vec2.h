#ifndef VEC2_H
#define VEC2_H


typedef struct {
	float x, y;
} Vec2_t;

const Vec2_t VEC2_ZERO  = {0, 0};


Vec2_t vec2_sum(Vec2_t v1, Vec2_t v2);

Vec2_t vec2_scale(Vec2_t v, float a);

float vec2_dot(Vec2_t v1, Vec2_t v2);








#endif //VEC2_H