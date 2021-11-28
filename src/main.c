#include "ecs/ecs.h"
#include "components/my_components.h"

#define TILE_COUNT 10

typedef struct EntityInfo {
	position* pos;
	tag* name;
} EInfo;

int main(int argc, char* argv[]) {

	ecs_init(tag, position, texture);

	// _ecs_init(2, sizeof(position), sizeof(tag));

	Entity tiles[TILE_COUNT];
	EInfo tiles_infos[TILE_COUNT];

	for(size_t i = 0; i < TILE_COUNT; i++) {
		position tile_pos = {
			i, 0
		};
		tag tile_name = { 0 };
		tile_name.name[0] = 48+i;
		
		tiles[i] = create_entity();
		tiles_infos[i].pos = set_component(position, tiles[i], tile_pos);
		tiles_infos[i].name = set_component(tag, tiles[i], tile_name);
	}

	if(has_component(tag, tiles[5])) {
		EInfo tile_5_info = tiles_infos[5];
		printf("tile number: %s\nposition >> %d, %d\n", tile_5_info.name->name, tile_5_info.pos->x, tile_5_info.pos->y);
	}

	for(size_t i = 0; i < TILE_COUNT; i++) {
		remove_entity(&tiles[i]);
	}

	ecs_clear();

	return 0;
}
