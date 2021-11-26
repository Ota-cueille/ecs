#ifndef MY_COMPONENT
#define MY_COMPONENT

#include "ecs/ecs.h"

p_component(tag,
	char name[10];
)

void copy_tag_component(address component_address, tag component_data) {
	// for(size_t i = 0; component_data.name[i] != '\0'; i++) {
    //    ((tag*)component_address)->name[i] = component_data.name[i];
	// }
	strcpy(&(((tag*)component_address)->name[0]), &component_data.name[0]);
}

component(position,
	uint32_t x, y;
)

#endif