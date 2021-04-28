#include "world.h"
#include "math.h"


World_t *world_init(World_t *world, int width, int height, double blocksPerUnit)
{
	world->width = width;
	world->height = height;
	world->blocksPerUnit = blocksPerUnit;
	world->collision = malloc(sizeof(Block_t)*width*height);

}



void world_free(World_t *world)
{
	free(world->collision);
}


Block_t world_getType(World_t *world, double x, double y)
{
	Block_t (*collision)[world->height] = world->collision;
	double xBlocks = x*world->blocksPerUnit;
	double yBlocks = y*world->blocksPerUnit;
	return collision[(int)xBlocks][(int)yBlocks];
}

Block_t world_getCollision(World_t *world, double x, double y)
{
	Block_t block = world_getType(world, x, y);
	double xBlocks = x*world->blocksPerUnit;
	double yBlocks = y*world->blocksPerUnit;

	switch (block) {
		double dx = xBlocks - floor(xBlocks);
		double dy = yBlocks - floor(yBlocks);
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