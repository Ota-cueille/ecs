#include <stdio.h>

#include "ecs/ecs.h"
#include "components/my_components.h"

int main(int argc, char* argv[]) {

	ecs_init(2, sizeof(position), sizeof(tag));

	Entity my_entity = CreateEntity();

	position a = { 0, 0 };
	position* m_Position = set_component(position, my_entity, a);

	tag name = { "First Entity !!!" };
	tag* m_Tag = set_component(tag, my_entity, name);

	if(has_component(position, my_entity) && has_component(tag, my_entity)) {
		position my_entity_position = get_component(position, my_entity);
		tag my_entity_tag = get_component(tag, my_entity);
		printf("L'entitee %s a pour position: (%d;%d)\n", my_entity_tag.name, my_entity_position.x, my_entity_position.y);
	}

	RemoveEntity(&my_entity);

	return 0;
}
