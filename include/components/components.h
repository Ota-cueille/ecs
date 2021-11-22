#ifndef COMPONENT
#define COMPONENT

#include "util.h"

// No prebuild component are given you have to create one
// based on the base structure component that will have
// infos about the component your creating
typedef struct Component {
	uint32_t offset;
} Component;

#endif