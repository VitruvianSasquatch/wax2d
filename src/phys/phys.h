#ifndef PHYS_H
#define PHYS_H

#include "body.h"


#define PHYS_MAX_BODIES 100

typedef int PhysId_t;


void phys_update(void);

PhysId_t phys_addBody(double m, double x, double y);

void phys_collide(PhysId_t a, PhysId_t b, double F);


#endif //PHYS_H