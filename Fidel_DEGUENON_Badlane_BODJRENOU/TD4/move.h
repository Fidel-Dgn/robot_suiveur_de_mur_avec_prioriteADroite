#ifndef MOVE_H
#define MOVE_H

typedef enum  {
    MOVE_FORWARD,
    MOVE_TURN
}move_type_t;

typedef struct {
    move_type_t type;
    int magnitude; //cm ou degre(0 à 360) 
}move_t;



#endif