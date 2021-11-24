#ifndef MY_COMPONENT
#define MY_COMPONENT

#include "ecs/ecs.h"

component(position,
	uint32_t x, y;
)

component(tag,
	const char* name;
)

#endif