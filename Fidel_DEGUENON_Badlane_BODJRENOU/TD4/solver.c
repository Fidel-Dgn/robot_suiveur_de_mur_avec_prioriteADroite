#include "solver.h"
#include <stdio.h>

void solver_init(solver_t *s) {
    s->successive_turns = 0;
}

//la prochaine direction de suivi
direction_t get_next_direction(solver_t *s) {
    s->successive_turns++;

    if (s->successive_turns >= 3) {
        s->successive_turns = 0;
        return DIR_GAUCHE;
    }

    return DIR_DROITE;
}