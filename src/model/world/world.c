#include "world.h"
#include "math.h"


World_t *world_init(size_t width, size_t height, double blocksPerUnit)
{
	World_t *world = calloc(1, sizeof(World_t));
	world->width = width;
	world->height = height;
	world->blocksPerUnit = blocksPerUnit;
	return world;
}



void world_free(World_t *world)
{
	free(world->collision);
}


Block_t world_getType(World_t *world, double x, double y)
{
	size_t xBlocks = floor(x*world->blocksPerUnit);
	size_t yBlocks = floor(y*world->blocksPerUnit);
	return world->collision[xBlocks + yBlocks*world->width];
}

Block_t world_getCollision(World_t *world, double x, double y)
{
	Block_t block = world_getType(world, x, y);
	double xBlocks = x*world->blocksPerUnit;
	double yBlocks = y*world->blocksPerUnit;

	double dx = xBlocks - floor(xBlocks);
	double dy = yBlocks - floor(yBlocks);

	switch (block) {
		case FULL:
			return FULL;
			break;
		case HALF_BOTTOMLEFT:
			return dy > dx ? HALF_BOTTOMLEFT : EMPTY;
			break; //Unneeded
		case HALF_BOTTOMRIGHT:
			return dx + dy > 1/world->blocksPerUnit ? HALF_BOTTOMRIGHT : EMPTY;
			break;
		case HALF_TOPLEFT:
			return dx + dy < 1/world->blocksPerUnit ? HALF_TOPLEFT : EMPTY;
			break;
		case HALF_TOPRIGHT:
			return dy < dx ? HALF_BOTTOMLEFT : EMPTY;
			break;
		default:
			return EMPTY;
	}
}