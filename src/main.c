#include <stdio.h>

#include "ecs/ecs.h"
#include "components/my_components.h"

int main(int argc, char* argv[]) {

	Entity my_entity = CreateEntity();

	ecs_init(1, sizeof(position));

	if(has_component(position, &my_entity)) {
		position my_entity_position = get_component(position, my_entity.id);
	}

	RemoveEntity(&my_entity);

	return 0;

}
