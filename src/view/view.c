
#include <SDL2/SDL.h>

#include "../model/phys/vec2.h"
#include "../model/phys/body.h"
#include "../model/world/world.h"



static SDL_Renderer *renderer;
static double pixelsPerUnit;
static Vec2_t viewWindow = {0, 0}; //in pixels
static uint16_t width;
static uint16_t height;

void view_init(SDL_Renderer *passedRenderer, double passedPixelsPerUnit, uint16_t passedWidth, uint16_t passedHeight)
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
	uint8_t r, g, b;
	r = g = b = shade;
	SDL_SetRenderDrawColor(renderer, r, g, b, 0xff);
	SDL_RenderFillRect(renderer, &fillRect);
}



void drawBody(const Body_t *body)
{
	drawRect(body->p.x, body->p.y, body->width, body->height, 255);
}



void view_draw(Body_t *wax, Body_t coins[], size_t numCoins, Body_t *objects[], size_t numObjects, World_t *world)
{
	//Clear screen:
	SDL_SetRenderDrawColor(renderer, 0x7f, 0x7f, 0x7f, 0xff);
	SDL_RenderClear(renderer);

	drawBody(wax);
	for (size_t i = 0; i < numCoins; i++) {
		drawBody(&coins[i]);
	}
	for (size_t i = 0; i < numObjects; i++) {
		drawBody(objects[i]);
	}

	double startX = floor(viewWindow.x/pixelsPerUnit);
	double startY = floor(viewWindow.y/pixelsPerUnit);

	for (double i = startX; i < startX + width/pixelsPerUnit; i += 1/world->blocksPerUnit) {
		for (double j = startY; j < startY + height/pixelsPerUnit; j += 1/world->blocksPerUnit) {
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


