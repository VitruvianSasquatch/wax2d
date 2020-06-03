#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <assert.h>

#include <stdbool.h>
#include <string.h>
#include <unistd.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_image.h>


#include <time.h>

#include "phys/vec2.h"
#include "phys/phys.h"
#include "input/input.h"


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480



int eventHandler(void *data, SDL_Event *event)
{
	bool *isRunning = (bool *)data;
	switch (event->type) {
		case SDL_QUIT:
			*isRunning = false; //This allows the current loop to finish. 
			break;
	}
	return 0; //eventHandler is not being used to filter events, so retVal is ignored. 
}



bool initSDL(const char *title, int width, int height, SDL_Window **window, SDL_Renderer **renderer)
{
	bool success = true;
	if ( SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
		success = false;
	}

	*window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN /*SDL_WINDOW_OPENGL*/);
	if (!*window) {
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		success = false;
	} else {
		*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
		if (!*renderer) {
			fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			//Initialize renderer color
			SDL_SetRenderDrawColor(*renderer, 0xff, 0xff, 0xff, 0xff);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if ( !( IMG_Init(imgFlags) & imgFlags ) ) {
				fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
		}
	}
	return success;
}


void closeSDL(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}


typedef enum {
	MOVE_LEFT = 0, 
	MOVE_RIGHT, 
	JUMP, 
	DECREASE_MASS, 
	INCREASE_MASS, 
	STEELPUSH,
	NUM_ACTIONS
} Action_t;


static const int keyAssignments[NUM_ACTIONS] = {
	SDL_SCANCODE_A, 
	SDL_SCANCODE_D, 
	SDL_SCANCODE_SPACE, 
	SDL_SCANCODE_W, 
	SDL_SCANCODE_S, 
	SDL_SCANCODE_LEFTCLICK
};

#define RUN_IMPULSE 5000


void handleInput(PhysId_t wax)
{
	if (input_justPressed(keyAssignments[MOVE_LEFT])) {
		phys_applyImpulse(wax, (Vec2_t){-RUN_IMPULSE, 0});
	} else if (input_justReleased(keyAssignments[MOVE_LEFT])) {
		phys_applyImpulse(wax, (Vec2_t){RUN_IMPULSE, 0});
	}

	if (input_justPressed(keyAssignments[MOVE_RIGHT])) {
		phys_applyImpulse(wax, (Vec2_t){RUN_IMPULSE, 0});
	} else if (input_justReleased(keyAssignments[MOVE_RIGHT])) {
		phys_applyImpulse(wax, (Vec2_t){-RUN_IMPULSE, 0});
	}

	if (input_isDown(keyAssignments[STEELPUSH])) {
		Vec2_t offset = vec2_diff(phys_getBodyPos(wax), (Vec2_t){input_getMouseX(), input_getMouseY()});
		double len = vec2_mag(offset);
		offset = vec2_scale(vec2_norm(offset), 5000);
		phys_forceBody(wax, offset);
	}
	//etc. 
}



int main(void)
{
	bool isRunning = true;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	initSDL("Wax 2D", WINDOW_WIDTH, WINDOW_HEIGHT, &window, &renderer);

	SDL_AddEventWatch(&eventHandler, &isRunning); //Handles exit etc. 

	input_init();

	PhysId_t wax = phys_addBody(100, 0, 0);


	while (isRunning) {

		input_update();
		handleInput(wax);


		phys_update();


		//Clear screen:
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);

		Vec2_t waxPos = phys_getBodyPos(wax);
		SDL_Rect fillRect = {waxPos.x, waxPos.y, 10, 20};
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
		SDL_RenderFillRect(renderer, &fillRect);

		SDL_RenderPresent(renderer);

	}

	closeSDL(window, renderer);

}
