#include "entities/entity_registry.h"

Entity CreateEntity(World* world) {
	Entity e = {
		_get_unused_id(),
		world
	};
	return e;
}

static struct {
	uint64_t *deleted_id, deleted_id_count, current_max_id;
} id_factory;

uint64_t _get_unused_id() {
	if(id_factory.deleted_id_count > 1) {
		id_factory.deleted_id_count--;
		uint64_t value = id_factory.deleted_id[id_factory.deleted_id_count];
		id_factory.deleted_id = realloc(id_factory.deleted_id, id_factory.deleted_id_count * sizeof(uint64_t));
		return value;
	} else if(id_factory.deleted_id_count == 1) {
		uint64_t value = id_factory.deleted_id[0];
		id_factory.deleted_id_count--;
		free(id_factory.deleted_id);
		return value;
	}
	if(id_factory.current_max_id >= MAX_ENTITIES) assert(false);
	return id_factory.current_max_id++;
}
