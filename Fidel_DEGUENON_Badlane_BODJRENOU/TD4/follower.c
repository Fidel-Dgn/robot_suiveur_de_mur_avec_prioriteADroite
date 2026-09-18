
#include "pilot.h"

#include <stdbool.h>
#include <unistd.h>
#include "mrpiz.h"
#include "follower.h"

#define WALL_DISTANCE_MIN 150
#define WALL_LOST_THRESHOLD 50

static direction_t side_followed = DIR_DROITE;

void search_wall(direction_t dir) {
    side_followed = dir;
    // On tourne sur place jusqu'à ce que le capteur latéral détecte quelque chose
    while (!pilot_obstacle_present(side_followed)) {
        move_t turn_move = {MOVE_TURN, 10}; // Petites rotations de 10 degrés
        pilot_start_move(turn_move);
        while (!pilot_stop_at_target());
    }
}

bool wall_lost(void) {
    int sensor_val;
    if (side_followed == DIR_DROITE) {
        sensor_val = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_RIGHT);
    } else {
        sensor_val = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_LEFT);
    }
    return (sensor_val < WALL_LOST_THRESHOLD);
}

void follow_wall(void) {
    if (wall_lost()) {
        // Si mur perdu, on tente de se rapprocher
        move_t adjust = {MOVE_TURN, (side_followed == DIR_DROITE) ? 15 : 345}; 
        pilot_start_move(adjust);
        while (!pilot_stop_at_target());
    }
    
    // Avance d'un petit pas
    move_t step = {MOVE_FORWARD, 5};
    pilot_start_move(step);
    while (!pilot_stop_at_target());
}


