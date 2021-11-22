#ifndef ENTITY
#define ENTITY

#include "util.h"
#include "world/world.h"

typedef uint64_t Entity_ID;

// Really an entity is just some way to identify the object
// that has different component, some utils could be added
// in the future to simplify the utilisation of the ECS

struct Entity {

	Entity_ID id;
	World* world;

};

typedef struct Entity Entity;

#endif