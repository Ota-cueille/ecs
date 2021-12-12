#include "ecs/ecs.h"
#include "components/my_components.h"

#define TILE_COUNT 10

typedef struct EntityComponentsInfo {
	tag* name;
	position* pos;
	texture* t;
} ECInfo;

typedef struct TagPositionInfo {
	tag* name;
	position* pos;
} TPInfo;

typedef struct PositionTextureInfo {
	position* pos;
	texture* t;
} PTInfo;

int main(int argc, char* argv[]) {

	ecs_init(tag, position, texture);

	Entity tiles[TILE_COUNT];
	ECInfo tiles_infos[TILE_COUNT];

	for(size_t i = 0; i < TILE_COUNT; i++) {
		position tile_pos = {
			i, 0
		};
		tag tile_name = { 0 };
		tile_name.name[0] = 48+i;

		tiles[i] = create_entity();
		tiles_infos[i].pos = set_component(position, tiles[i], tile_pos);
		tiles_infos[i].name = set_component(tag, tiles[i], tile_name);

		if(i%2 == 0) {
			texture tile_texture;
			tile_texture.id = i;
			tile_texture.x = i + 1;
			tile_texture.y = i + 2;
			tile_texture.z = i + 3;
			tiles_infos[i].t = set_component(texture, tiles[i], tile_texture);
		}
	}

	if(has_components(tiles[0], tag, position)) {
		printf("it's a fact !\n");
	}
	if(has_components(tiles[1], texture, position)) {
		printf("also true !\n");
	}

	if(has_components(tiles[0], texture, tag)) {
		printf("yes !\n");
	}
	if(has_components(tiles[1], tag)) {
		printf("retrocompatible !\n");
	}

	for(size_t i = 0; i < TILE_COUNT; i++) {
		remove_entity(&tiles[i]);
	}

	ecs_clear();

	return 0;
}
