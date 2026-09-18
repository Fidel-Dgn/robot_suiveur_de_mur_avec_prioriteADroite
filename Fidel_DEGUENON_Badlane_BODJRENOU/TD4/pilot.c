#include "pilot.h"

#include "move.h"
#include "mrpiz.h"
#include <stdio.h>
#include <stdlib.h>  // pour abs()

#define STEP_PER_CM     34.6
#define STEP_PER_DEGRE  2.53
#define OBSTACLE_THRESHOLD 200
#define OBSTACLE_CLOSE     400

// Variables privées du module
static int          encoder_target;
static encoder_ref_e encoder_reference;

void pilot_init(void) {
    if (mrpiz_init() == -1) {
        //Gestion d'erreur pour nous indiquer s'il y a connexion ou pas avec notre environnement de simulation
        mrpiz_error_print("Error : Problème d'initialisation avec le simulateur");
    }
}

void pilot_start_move(move_t move) {
    reset_encoder();

    if (move.type == MOVE_FORWARD) {
        encoder_reference = LEFT;  // ← CORRECTION : référence définie
        encoder_target = (int)(move.magnitude * STEP_PER_CM);
        robot_start_forward();
    }

    if (move.type == MOVE_TURN) {
        encoder_target = (int)(move.magnitude * STEP_PER_DEGRE);

        // Sens horaire (<=180°) → tourne à droite, encodeur gauche avance
        // Sens anti-horaire (>180°) → tourne à gauche, encodeur droit avance
        if (move.magnitude <= 180) {
            encoder_reference = LEFT;
            robot_turn(DIR_DROITE);
        } else {
            encoder_reference = RIGHT;
            robot_turn(DIR_GAUCHE);
            // Pour 270° horaire = 90° anti-horaire
            encoder_target = (int)((360 - move.magnitude) * STEP_PER_DEGRE);
        }
    }
}
//ARRETE LE robot si le  mouvement en cours est terminé ....ceci est basé sur la comparaison des encoders
bool pilot_stop_at_target(void) {
    encoder_t enc = get_encoder();
    int encoder_value;

    if (encoder_reference == LEFT) {

        encoder_value = abs(enc.left);   // ← abs() pour valeurs négatives
        
    } else {
        encoder_value = abs(enc.right);  // ← abs() pour valeurs négatives
       
    }

    if (encoder_value >= encoder_target) {
        robot_stop();
        return true;
    }
    return false;
}


//détection de la présence d'obstacle dans une direction donnée
bool pilot_obstacle_present(direction_t dir) {
    int value = 0;

    switch (dir) {
        case DIR_DROITE:
            value = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_RIGHT);
            break;

        case DIR_GAUCHE:
            value = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_LEFT);
            break;

         case DIR_DEVANT:
            value = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_CENTER);
            break;


        default:
            return false;
    }

    if (value == -1) return false;

    return (value > OBSTACLE_THRESHOLD);
}




 