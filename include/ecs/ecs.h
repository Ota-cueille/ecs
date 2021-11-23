#ifndef ECS
#define ECS

#include "util.h"
#include "entities/entity_registry.h"
#include "components/components.h"

extern struct {
	uint64_t entity_storage, component_count, entity_count;
	uint64_t *component_offset;
	address component_array;
} ecs;

void ecs_init(uint32_t component_count, ...);
void ecs_clear();

internal uint64_t _get_unused_id();
internal bool _is_available_id();

internal address _internal_get_component(Entity_ID entity, uint64_t component_id);
internal bool _internal_has_component(Entity*, uint64_t component_id);

Entity CreateEntity();
void RemoveEntity(Entity*);
#define get_component(type, entity) (*((type*)_internal_get_component(entity, CID_##type)))
#define has_component(type, entity) _internal_has_component(entity, CID_##type)

#endif