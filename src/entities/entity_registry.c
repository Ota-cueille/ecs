#include "entities/entity_registry.h"

Entity CreateEntity()
{
	static uint64_t current_id = 0;

	if(current_id >= MAX_ENTITIES) assert(false);

	Entity e;
	e.id = current_id++;
	return e;
}

