#include "ecs/ecs.h"

#include <stdarg.h>

void ecs_init(uint32_t component_count, ...) {
	ecs.component_count = component_count;
	ecs.component_offset = (uint64_t*)calloc(component_count, sizeof(uint64_t));
	
	// we are determining the size to allocate for one entity so that
	// this entity will have enough space to store all the components
	// it wants
	va_list component_size;
	va_start(component_size, component_count);

	uint64_t current_component_size = 0, total_offset = 0;

	for(uint32_t i = 0; i < component_count; i++) {
		// getting the size of the component
		current_component_size = va_arg(component_size, uint64_t);
		// getting the offset of the component in the entity storage
		total_offset += current_component_size;
		// storing the offset of the component at it's id so we can retrieve it by id
		ecs.component_offset[i] = total_offset;
		// calculating the size needed to store the components for one entity
		ecs.entity_storage += ecs.component_offset[i];
	}

	va_end(component_size);

	// were are now allocating an array within one cell correspond to
	// one entity storage, calloc automatically sets the value to 0
	ecs.component_array = calloc(MAX_ENTITIES, ecs.entity_storage);
}

void ecs_clear() {
	free(ecs.component_array);
	ecs.component_array = NULL;
	free(ecs.component_offset);
	ecs.component_offset = NULL;
}

Entity CreateEntity() {
	Entity e;
	e.id = _get_unused_id();
	e.component_mask = (bool*)calloc(ecs.component_count, sizeof(bool));
	ecs.entity_count++;
	return e;
}

void RemoveEntity(Entity* e) {
	free(e->component_mask);
	e->component_mask = NULL;
	id_factory.available_ids[e->id] = false;
	e->id = MAX_ENTITIES;
	ecs.entity_count--;
}

internal struct {
	bool available_ids[MAX_ENTITIES];
	uint64_t current_id;
} id_factory;

internal uint64_t _get_unused_id() {
	while(is_available_id()) {
		if(id_factory.available_ids[id_factory.current_id]) {
			return id_factory.current_id;
		}
		if(!id_factory.current_id % MAX_ENTITIES) {
			id_factory.current_id++;
		} else {
			id_factory.current_id = 0;
		}
	}

	// there are no more IDs available
	assert(false);
}

internal address _internal_get_component(Entity_ID entity, uint64_t component_id) {
	return (ecs.component_array + ecs.entity_storage * entity + ecs.component_offset[component_id]);
}

internal bool _internal_has_component(Entity* entity, uint64_t component_id) {
	return entity->component_mask[component_id];
}

internal bool is_available_id() {
	for(uint64_t i = 0; i < MAX_ENTITIES; i++) {
		if(id_factory.available_ids[i]) {
			return true;
		}
	}
	return false;
}
