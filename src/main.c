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

#include "phys/phys.h"
#include "input/input.h"


int eventHandler(void *data, SDL_Event *event)
{
    int *isRunning = ((int **)data)[0];
    switch (event->type) {
        case SDL_QUIT:
            *isRunning = 0; //This allows the current loop to finish. 
            break;
    }
    return 0; //eventHandler is not being used to filter events, so retVal is ignored. 
}



bool initSDL(int width, int height, SDL_Window *window, SDL_Renderer *renderer)
{
    bool success = true;
    if ( SDL_Init(SDL_INIT_VIDEO & 0) < 0) {
        fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
        success = false;
    }

    window = SDL_CreateWindow("Alfie Driver", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        success = false;
    } else {
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        if (!renderer) {
			fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
		} else {
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

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


bool closeSDL(void)
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
    NUM_ACTIONS
} Action_t;

static const int keyAssignments[NUM_ACTIONS] = {
    SDL_SCANCODE_A, 
    SDL_SCANCODE_D, 
    SDL_SCANCODE_SPACE, 
    SDL_SCANCODE_W, 
    SDL_SCANCODE_S
};




void handleInput(PhysId_t wax) {
    
    if (input_isDown(keyAssignments[MOVE_LEFT])) {
        printf("Left down!\n");
    } else {
        printf("Left up!\n");
    }
    //etc. 
}



int main(void)
{
    int isRunning = 1;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    init(640, 480, window, renderer);

    int *eventRefs[1] = {&isRunning};
    SDL_AddEventWatch(&eventHandler, eventRefs); //Handles exit etc. 

    input_init();

    PhysId_t wax = phys_addBody(100, 0, 0);


    
    
    while (isRunning) {

        input_update();
        handleInput(wax);


        phys_update();

    }

    

}
