
#include <SDL2/SDL.h>

#include "../model/phys/vec2.h"
#include "../model/phys/body.h"
#include "../model/world/world.h"



static SDL_Renderer *renderer;
static double pixelsPerUnit;
static Vec2_t viewWindow = {0, 0}; //in pixels
static int width;
static int height;

void view_init(SDL_Renderer *passedRenderer, double passedPixelsPerUnit, int passedWidth, int passedHeight)
{
	renderer = passedRenderer;
	pixelsPerUnit = passedPixelsPerUnit;
	width = passedWidth;
	height = passedHeight;
}


void drawRect(double x, double y, double width, double height, uint8_t shade)
{
	double screenX = (pixelsPerUnit * x) - viewWindow.x;
	double screenY = (pixelsPerUnit * y) - viewWindow.y;
	SDL_Rect fillRect = {screenX, screenY, pixelsPerUnit * width, pixelsPerUnit * height};
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderFillRect(renderer, &fillRect);
}



void drawBody(const Body_t *body)
{
	drawRect(body->p.x, body->p.y, body->width, body->height, 255);
}



void view_draw(Body_t *wax, Body_t *coins[], int numCoins, Body_t *objects[], int numObjects, World_t *world)
{
	//Clear screen:
	SDL_SetRenderDrawColor(renderer, 0x7f, 0x7f, 0x7f, 0xff);
	SDL_RenderClear(renderer);

	drawBody(wax);
	for (int i = 0; i < numCoins; i++) {
		drawBody(coins[i]);
	}
	for (int i = 0; i < numObjects; i++) {
		drawBody(objects[i]);
	}

	int startX = viewWindow.x/pixelsPerUnit; //intentional implicit floor
	int startY = viewWindow.y/pixelsPerUnit;

	for (int i = startX; i < startX + width/pixelsPerUnit; i += 1/world->blocksPerUnit) {
		for (int j = startY; j < startY + height/pixelsPerUnit; j += 1/world->blocksPerUnit) {
			switch (world_getType(world, i, j)) {
				case EMPTY:
					break;
				case FULL:
					drawRect(i, j, 1/world->blocksPerUnit, 1/world->blocksPerUnit, 0);
					break;
				default:
					drawRect(i, j, 1/world->blocksPerUnit, 1/world->blocksPerUnit, 75); //Placeholder for angles. 
			}
		}
	}

	SDL_RenderPresent(renderer);
}


