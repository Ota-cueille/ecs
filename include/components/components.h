#ifndef COMPONENT
#define COMPONENT

#include "util.h"

typedef uint64_t Entity_ID;

#define component(name, elements...) \
typedef struct name##_component {\
	elements\
} name;\
uint32_t const CID_##name = __COUNTER__;\
name* _internal_set_##name##_component(Entity entity, name component_data) {\
	address component_address = ecs.component_array + ecs.entity_storage * entity.id + ecs.component_offset[CID_##name];\
	entity.component_mask[CID_##name] = true;\
	memcpy(component_address, &component_data, sizeof(name));\
	return component_address;\
}\

#endif