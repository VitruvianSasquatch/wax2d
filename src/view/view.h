#ifndef VIEW_H
#define VIEW_H


#include <SDL2/SDL.h>

#include "../model/phys/vec2.h"
#include "../model/phys/body.h"
#include "../model/world/world.h"


void view_init(SDL_Renderer *renderer, double pixelsPerMetre, int width, int height);

void view_draw(Body_t *wax, Body_t *coins[], int numCoins, Body_t *objects[], int numObjects, World_t *world);



#endif //VIEW_H