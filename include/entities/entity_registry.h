#ifndef ENTITY_REG
#define ENTITY_REG

#include "util.h"
#include "entity.h"

// The entity registry is used to hold the entity IDs
// and to link them to the list of components they have

#define MAX_ENTITIES 100
typedef struct EntityRegistry {

	uint64_t entity_count;
	Entity entities[MAX_ENTITIES];

} EntityRegistry;

Entity CreateEntity();

// Removing an entity will also destroy the components attached to it
void RemoveEntity(Entity_ID entity);

#endif