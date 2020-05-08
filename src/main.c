#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <assert.h>

#include <string.h>
#include <unistd.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>


#include <time.h>


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



SDL_Window *init(int width, int height)
{
    if( SDL_Init(SDL_INIT_VIDEO & 0) < 0) {
        fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_Window *window = SDL_CreateWindow("Alfie Driver", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    if (!window){
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    return window;
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



void handleInput(void) {
    
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

    SDL_Window *window = init(640, 480);

    int *eventRefs[1] = {&isRunning};
    SDL_AddEventWatch(&eventHandler, eventRefs); //Handles exit etc. 

    input_init();

    
    while (isRunning) {

        input_update();
        handleInput();

    }

}
