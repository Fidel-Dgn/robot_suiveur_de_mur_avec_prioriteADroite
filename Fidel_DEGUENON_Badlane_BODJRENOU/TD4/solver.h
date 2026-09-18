#ifndef SOLVER_H
#define SOLVER_H

#include "robot.h"

typedef struct {
    int successive_turns;
} solver_t;


void solver_init(solver_t *s);


direction_t get_next_direction(solver_t *s);

#endif