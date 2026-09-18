#ifndef PILOT_H
#define PILOT_H
#include "move.h"
#include <stdbool.h>

#include "robot.h"

// Énumération des encodeurs de référence
typedef enum
{
    LEFT,
    RIGHT
} encoder_ref_e;

extern void pilot_init(void);
extern void pilot_start_move(move_t move);

extern bool pilot_stop_at_target(void);
bool pilot_obstacle_present(direction_t dir);

#endif