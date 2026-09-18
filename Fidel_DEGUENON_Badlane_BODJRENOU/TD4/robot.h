#ifndef _ROBOT_H_
#define _ROBOT_H_
#include "stdbool.h"
// PUBLIC TYPES ---------------------------------------------------

typedef enum{
    DIR_GAUCHE,
    DIR_DROITE,
    DIR_DEVANT
}direction_t;


typedef struct {
    int left;
    int right;
}encoder_t;

// PUBLIC FUNCTIONS DECLARATIONS ----------------------------------

extern void robot_init(void);
extern void robot_start_forward(void);
extern void robot_stop(void);
extern void robot_turn(direction_t dir);
encoder_t get_encoder(void);
void reset_encoder(void);   
void robot_forward_obstacle(void);
direction_t robot_get_obstacle_direction(void);
bool robot_obstacle_detected(void);

#endif  /* _ROBOT_H_ */