#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdint.h>

typedef struct {
	int numLayers; //Excludes final background? //TODO: Does this require an additional parallax coefficient?
	int numForegroundLayers; //Layers before collision layer. 
	float *parallax; //Array of parallax coefficients. 
	uint16_t **tiles; //Array of 2D arrays of tile codes. //TODO: Change to image pointers. 
} TileMap_t;


#endif //TILEMAP_H