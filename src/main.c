#include <stdio.h>

#include "ecs/ecs.h"
#include "components/my_components.h"

int main(int argc, char* argv[]) {

	ecs_init(1, sizeof(position));
	get_component(position, 100);

	return 0;

}
