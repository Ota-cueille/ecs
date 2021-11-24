#ifndef ECS
#define ECS

#include "util.h"
#include "entities/entity_registry.h"

typedef struct EntityComponentSystem {
	uint64_t entity_storage, component_count, entity_count;
	uint64_t *component_offset;
	address component_array;
	
	struct {
		bool available_ids[MAX_ENTITIES];
		uint64_t current_id;
	} id_factory;
} EntityComponentSystem;

extern EntityComponentSystem ecs;

void ecs_init(uint32_t component_count, ...);
void ecs_clear();

bool _is_available_id();
uint64_t _get_unused_id();

address _internal_get_component(Entity entity, uint64_t component_id);
bool _internal_has_component(Entity entity, uint64_t component_id);

Entity CreateEntity();
void RemoveEntity(Entity*);

#define set_component(type, entity, data) _internal_set_##type##_component(entity, data)
#define get_component(type, entity) (*((type*)_internal_get_component(entity, CID_##type)))
#define has_component(type, entity) _internal_has_component(entity, CID_##type)

#endif