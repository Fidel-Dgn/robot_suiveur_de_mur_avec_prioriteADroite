#ifndef _FOLLOWER_H_
#define _FOLLOWER_H_




#include <stdbool.h>
#include "robot.h"

//void search_wall(direction_t dir);
void search_wall(direction_t dir);
void follow_wall(void);
bool wall_lost(void);


#endif