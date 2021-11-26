#ifndef COMPONENT
#define COMPONENT

#include "util.h"

typedef uint64_t Entity_ID;

// there is a problem with structures that have pointers
#define component(name, elements...)\
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

#define p_component(name, elements...)\
typedef struct name##_component {\
	elements\
} name;\
uint32_t const CID_##name = __COUNTER__;\
void copy_##name##_component(address component_address, name component_data);\
name* _internal_set_##name##_component(Entity entity, name component_data) {\
	address component_address = ecs.component_array + ecs.entity_storage * entity.id + ecs.component_offset[CID_##name];\
	entity.component_mask[CID_##name] = true;\
	copy_##name##_component(component_address, component_data);\
	return component_address;\
}\

#endif