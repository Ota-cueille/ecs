A simple ECS (Entity Component System) based on what I learned until today
one rule will be that the code must have the less possible heap allocation
so the memory won't be to complicated to manage (typecast will be usefull)

this is using boost predefined macros to facilitate the call of the functions
boost is under license described in LICENSE.txt