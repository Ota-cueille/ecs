#ifndef COMPONENT
#define COMPONENT

#include "util.h"

#define component(name, elements...) \
extern uint32_t const CID_##name = __COUNTER__;\
typedef struct name##Component {\
	elements\
} name\

#endif