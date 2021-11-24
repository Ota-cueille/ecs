#include <stdio.h>

#include "ecs/ecs.h"
#include "components/my_components.h"

#define TILE_COUNT 10

typedef struct EntityInfo {
	position* pos;
	tag* name;
} EInfo;

const char* number[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

int main(int argc, char* argv[]) {

	ecs_init(2, sizeof(position), sizeof(tag));

	Entity tiles[TILE_COUNT];
	EInfo tiles_infos[TILE_COUNT];

	for(size_t i = 0; i < TILE_COUNT; i++) {
		position tile_pos = {
			i, 0
		};
		tag tile_name = { &number[i] };
		
		tiles[i] = CreateEntity();
		tiles_infos[i].pos = set_component(position, tiles[i], tile_pos);
		tiles_infos[i].name = set_component(tag, tiles[i], tile_name);
	}

	if(has_component(tag, tiles[5])) {
		EInfo tile_5_info = tiles_infos[5];
		printf("tile number: %s\nposition >> %d, %d\n", tile_5_info.name->name, tile_5_info.pos->x, tile_5_info.pos->y);
	}

	for(size_t i = 0; i < TILE_COUNT; i++) {
		RemoveEntity(&tiles[i]);
	}

	ecs_clear();

	return 0;
}
