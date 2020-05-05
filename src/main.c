#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <assert.h>

#include <string.h>
#include <unistd.h>


#include <SDL2/SDL.h>


#include <time.h>




SDL_Window *initSDL(int width, int height)
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


void handleInput(int *isRunning, int16_t *leftSpeed, int16_t *rightSpeed) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: //Key pressed
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        *leftSpeed = INT16_MAX;
                        break;
                    case SDLK_d:
                        *rightSpeed = INT16_MAX;
                        break;
                }
                break;
 
            case SDL_KEYUP: //Key released
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        *leftSpeed = 0;
                        break;
                    case SDLK_d:
                        *rightSpeed = 0;
                        break;
                }
                break;

            case SDL_QUIT:
                *isRunning = 0;

            default:
                break;
        }
    }
}



int main(void)
{
    
    SDL_Window *window = initSDL(640, 480);


    #define NUM_IMU_AXES 9
    int isRunning = 1;
    int16_t imuData[NUM_IMU_AXES] = {0};
    void *receiveThreadArgs[2] = {NULL};
    receiveThreadArgs[0] = (void *)&isRunning;
    receiveThreadArgs[1] = (void *)imuData;
    pthread_t receiveThread;
    pthread_create(&receiveThread, NULL, &receiveTask, receiveThreadArgs); 

    int bytesSent = comms_sendPacket(Alfie, Interface, Micro, Enable, Integer, 1);
    while (isRunning) {


        handleInput(&isRunning, &leftSpeed, &rightSpeed);

    }

    comms_sendPacket(Alfie, Interface, Micro, Enable, Integer, 0);
    pthread_join(receiveThread, NULL);
    comms_disconnect();
    SDL_Quit();
    return 0;
}
