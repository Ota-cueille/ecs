#include "ecs/ecs.h"

EntityComponentSystem ecs;

void _internal_ecs_init(uint32_t component_count, ...) {
	// setting the component count
	ecs.component_count = component_count;

	// allocation space for the component offset array ans setting all id's available
	ecs.component_offset = (uint64_t*)calloc(component_count, sizeof(uint64_t));
	memset(ecs.id_factory.available_ids, true, MAX_ENTITIES * sizeof(bool));

	// we are determining the size to allocate for one entity so that
	// entities will have enough space to store all the components they want
	va_list component_size;
	va_start(component_size, component_count);

	uint64_t current_component_size = 0, total_offset = 0;

	for(uint32_t i = 0; i < component_count; i++) {
		// getting the size of the component
		current_component_size = va_arg(component_size, uint64_t);

		// storing the offset of the component at it's id so we can retrieve it by id
		ecs.component_offset[i] = total_offset;

		// getting the offset of the component in the entity storage
		total_offset += current_component_size;

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

Entity create_entity() {
	Entity e;
	e.id = _get_unused_id();
	e.component_mask = (bool*)calloc(ecs.component_count, sizeof(bool));
	ecs.entity_count++;

	ecs.id_factory.available_ids[e.id] = false;

	ecs.created_entities = realloc(ecs.created_entities, ecs.entity_count * sizeof(Entity));
	ecs.created_entities[ecs.entity_count - 1].id = e.id;
	ecs.created_entities[ecs.entity_count - 1].component_mask = e.component_mask;
	ecs.created_entities_end  = ecs.created_entities + ecs.entity_count;
	
	return e;
}

void remove_entity(Entity* e) {
	free(e->component_mask);
	e->component_mask = NULL;

	ecs.id_factory.available_ids[e->id] = true;

	e->id = MAX_ENTITIES;
	ecs.entity_count--;

	ecs.created_entities[ecs.entity_count].id = MAX_ENTITIES;
	ecs.created_entities[ecs.entity_count].component_mask = NULL;
	ecs.created_entities = realloc(ecs.created_entities, ecs.entity_count * sizeof(Entity));
	ecs.created_entities_end = ecs.created_entities + ecs.entity_count;
}

bool _is_available_id() {
	for(uint64_t i = 0; i < MAX_ENTITIES; i++) {
		if(ecs.id_factory.available_ids[i]) {
			return true;
		}
	}
	return false;
}


uint64_t _get_unused_id() {
	// while we can create entities
	while(ecs.entity_count < MAX_ENTITIES) {
		// if the current id is less than the maximum
		if(!(ecs.id_factory.current_id >= MAX_ENTITIES)) {
			// increment id by one
			ecs.id_factory.current_id++;
		} else {
			// otherwise set it to zero again to begin a new cycle
			ecs.id_factory.current_id = 0;
		}
		// looking if the last id is available
		if(ecs.id_factory.available_ids[ecs.id_factory.current_id]) {
			// if so return it
			return ecs.id_factory.current_id-1;
		}
	}
	// there are no more IDs available
	return MAX_ENTITIES;
}

address _internal_get_component(Entity entity, uint64_t component_id) {
	return (ecs.component_array + ecs.entity_storage * entity.id + ecs.component_offset[component_id]);
}

bool _internal_has_component(Entity entity, uint64_t component_id) {
	return entity.component_mask[component_id];
}

bool _internal_has_components(Entity entity, uint64_t* component_ids, uint32_t component_count) {
	bool has = true;
	for(uint64_t i = 0; i < component_count; i++) {
		has = has && entity.component_mask[component_ids[i]];
	}
	return has;
}

void _internal_group_components(uint32_t component_count, ...) {
	if(component_count == 0) return;

	va_list component_ids;
	va_start(component_ids, component_count);

	Entity *owner_entities[MAX_ENTITIES];
	uint64_t owner_entities_count = 0, *ids = NULL;
	free(ecs.group.components);

	ids = (uint64_t*)malloc(component_count * sizeof(uint64_t));

	for(uint32_t i = 0; i < component_count; i++) {
		ids[i] = va_arg(component_ids, uint64_t);
	}

	for(Entity* e = &ecs.created_entities[0]; e != ecs.created_entities_end; e++) {
		if(_internal_has_components(*e, ids, component_count)) {
			owner_entities[owner_entities_count] = e;
			owner_entities_count++;
		}
	}

	ecs.group.count = owner_entities_count;
	ecs.group.components = calloc(component_count * owner_entities_count, sizeof(address));

	for(uint32_t entity_offset = 0; entity_offset < owner_entities_count; entity_offset++) {
		for(uint32_t component_offset = 0; component_offset < component_count; component_offset++) {
			ecs.group.components[entity_offset * component_count + component_offset] = _internal_get_component(*owner_entities[entity_offset], ids[component_offset]);
		}
	}

	ecs.group.end = ecs.group.components + component_count * owner_entities_count;

	va_end(component_ids);
}

void _internal_create_component_tab(uint32_t component_count, ...) {
	va_list component_ids;
	va_start(component_ids, component_count);
	
	ecs.component_tab = (uint64_t*)realloc(ecs.component_tab, component_count * sizeof(uint64_t));
	for(uint32_t i = 0; i < component_count; i++) {
		ecs.component_tab[i] = va_arg(component_ids, uint64_t);
	}

	va_end(component_ids);
}
