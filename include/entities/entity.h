#ifndef ENTITY
#define ENTITY

#include "util.h"

// this fix the maximum number of entities
#define MAX_ENTITIES 50000

typedef uint64_t Entity_ID;

typedef struct Entity {

	Entity_ID id;
	bool* component_mask;

} Entity;

#endif