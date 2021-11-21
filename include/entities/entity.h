#ifndef ENTITY
#define ENTITY

#include <stdint.h>

typedef uint64_t Entity_ID;

// Really an entity is just some way to identify the object
// that has different component, some utils could be added
// in the future to simplify the utilisation of the ECS

typedef struct entity {

	Entity_ID id;

} Entity;

#endif