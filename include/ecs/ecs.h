#ifndef ECS
#define ECS

#include "util.h"
#include "entities/entity.h"
#include "components/components.h"

typedef struct EntityComponentSystem {
	uint64_t entity_storage, component_count, entity_count, *component_offset;
	Entity *created_entities, *created_entities_end;
	address component_array, *current_group;

	struct Group {
		uint32_t count;
		address *components, end;
	} group;

	struct {
		bool available_ids[MAX_ENTITIES];
		uint64_t current_id;
	} id_factory;

	uint64_t* component_tab;

} EntityComponentSystem;

extern EntityComponentSystem ecs;

void _internal_ecs_init(uint32_t component_count, ...);
#define ecs_init(components...) _internal_ecs_init(__NARG__(components), WRAP(sizeof, components))

void ecs_clear();

bool _is_available_id();
uint64_t _get_unused_id();

address _internal_get_component(Entity entity, uint64_t component_id);
bool _internal_has_component(Entity entity, uint64_t component_id);
bool _internal_has_components(Entity entity, uint64_t* ids, uint32_t component_count);
void _internal_group_components(uint32_t component_count, ...);
void _internal_create_component_tab(uint32_t count, ...);

Entity create_entity();
void remove_entity(Entity*);

#define set_component(type, entity, data) _internal_set_##type##_component(entity, data)
#define get_component(type, entity) (*((type*)_internal_get_component(entity, CID_##type)))
#define has_component(type, entity) _internal_has_component(entity, CID_##type)
#define has_components(entity, types...) _internal_create_component_tab(__NARG__(types), CAT_BACK(CID_, types)), _internal_has_components(entity, ecs.component_tab, __NARG__(types))

#define group(components...) _internal_group_components(__NARG__(components), CAT_BACK(CID_, components))
#define component_in_entities(cast_type, var) cast_type* var = (cast_type*)ecs.group.components; var != ecs.group.end; var++

#endif