#ifndef PHYS_H
#define PHYS_H

#include "body.h"


#define PHYS_MAX_BODIES 100

typedef int PhysId_t;


double phys_getBodyX(PhysId_t id);

double phys_getBodyY(PhysId_t id);

void phys_update(void);

PhysId_t phys_addBody(double m, double x, double y);



/**
 * @brief Applies an equal and opposite force to two given bodies. 
 * 
 * @param a The first body in the collision. 
 * @param b The second body in the collision. 
 * @param F The magnitude of the reactive force between the two bodies, along the vector outwards from their CoM. 
 */
void phys_collide(PhysId_t a, PhysId_t b, double F);

void phys_forceBody(PhysId_t b, double fx, double fy);


#endif //PHYS_H