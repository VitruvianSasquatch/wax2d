#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <assert.h>

#include <string.h>
#include <unistd.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>


#include <time.h>



int eventHandler(void *data, SDL_Event *event)
{
    switch (event->type) {
        case SDL_QUIT:
            int *isRunning = ((int **)data)[0];
            *isRunning = 0; //This allows the current loop to finish. 
            break;
    }
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

const static keyAssignments[NUM_ACTIONS] = {SDLK_a, SDLK_d, SDLK_SPACE, SDLK_w, SDLK_s};


void updateInput(uint8_t *keyboardState, int *numKeys, uint32_t *mouseState, int *mouseX, int *mouseY)
{
    SDL_PumpEvents();
    keyboardState = SDL_GetKeyState(numKeys);
    *mouseState = SDL_GetMouseState(mouseX, mouseY);
}

void handleInput(void) {
    static uint8_t *keyboardState = NULL;
    static int numKeys = 0;
    static uint32_t mouseState = 0;
    static int mouseX = 0;
    static int mouseY = 0;


    updateInput(keyboardState, &numKeys, &mouseState, &mouseX, &mouseY);


    if (keyboardState[keyAssignments[MOVE_LEFT]]) {
        //do stuff. 
    }
    //etc. 
}



int main(void)
{
    int isRunning = 1;

    SDL_Window *window = init(640, 480);
    SDL_AddEventWatch(&eventHandler, &isRunning); //Handles exit etc. 


    
    while (isRunning) {


        handleInput();

    }

}
