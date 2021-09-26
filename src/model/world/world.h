#ifndef WORLD_H
#define WORLD_H


#include "common.h"

//#define I(i,j) ()



typedef enum {
	EMPTY = 0, 
	FULL, 
	HALF_BOTTOMLEFT, 
	HALF_BOTTOMRIGHT,
	HALF_TOPLEFT, 
	HALF_TOPRIGHT,

	NUM_BLOCK_TYPES
} Block_t;


typedef struct {
	size_t width; //in blocks
	size_t height;
	double blocksPerUnit;
	Block_t *collision;
} World_t;


World_t *world_init(size_t width, size_t height, double blocksPerUnit);

void world_free(World_t *world);

Block_t world_getType(World_t *world, double x, double y);

Block_t world_getCollision(World_t *world, double x, double y);


#endif //WORLD_H