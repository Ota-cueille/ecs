#include "ecs/ecs.h"

#include <stdarg.h>

void ecs_init(uint32_t component_count, ...)
{
	// we are determining the size to allocate for one entity so that
	// this entity will have enough space to store all the components
	// it wants
	va_list component_size;
	va_start(component_size, component_count);

	uint64_t current_offset = 0, total_offset = 0;

	for(uint32_t i = 0; i < component_count; i++) {
		current_offset = va_arg(component_size, uint64_t);
		total_offset += current_offset;
		ecs.component_offset[i] = total_offset;
		ecs.entity_storage += ecs.component_offset[i];
	}

	va_end(component_size);

	// were are now allocating an array wich one cell correspond to
	// one entity storage
	ecs.component_array = calloc(MAX_ENTITIES, ecs.entity_storage);
	memset(ecs.component_array, 0, MAX_ENTITIES * ecs.entity_storage);

}

internal address _internal_get_component(Entity_ID entity, uint64_t component_id) {
	return (ecs.component_array + ecs.entity_storage * entity + ecs.component_offset[component_id]);
}
