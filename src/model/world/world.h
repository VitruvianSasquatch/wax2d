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
	int width; //in blocks
	int height;
	double blocksPerUnit;
	Block_t *collision;
} World_t;


World_t *world_init(World_t *world, int width, int height, double blocksPerUnit);

void world_free(World_t *world);

Block_t world_getType(World_t *world, double x, double y);

Block_t world_getCollision(World_t *world, double x, double y);


#endif //WORLD_H