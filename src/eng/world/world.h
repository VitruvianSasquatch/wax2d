#ifndef WORLD_H
#define WORLD_H


#include <stdint.h>

//#define I(i,j) ()



typedef enum {
	EMPTY = 0, 
	FULL, 
} Block_t;


typedef struct {
	int width;
	int height;
	Block_t *collision;

	int numLayers; //Excludes final background? //TODO: Does this require an additional parallax coefficient?
	int numForegroundLayers; //Layers before collision layer. 
	float *parallax; //Array of parallax coefficients. 
	uint16_t **tiles; //Array of 2D arrays of tile codes. //TODO: Change to image pointers. 
} World_t;

//TODO: Have a seperate collision world type that is referenced within a larger worldGraphics type. 



#endif //WORLD_H