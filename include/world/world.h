#ifndef WORLD
#define WORLD

#include "entities/entity_registry.h"

// the entities have to live in a world
// and they need a way to interact with
// each others via systems

typedef struct World {

	EntityRegistry registry;

} World;

#endif