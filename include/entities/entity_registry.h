#ifndef ENTITY_REG
#define ENTITY_REG

#include "util.h"
#include "entities/entity.h"
#include "components/components.h"

// The entity registry is used to hold the entity IDs
// and to link them to the list of components they have

#define MAX_ENTITIES 100
typedef struct EntityRegistry {

	address entities[MAX_ENTITIES];

} EntityRegistry;

#endif