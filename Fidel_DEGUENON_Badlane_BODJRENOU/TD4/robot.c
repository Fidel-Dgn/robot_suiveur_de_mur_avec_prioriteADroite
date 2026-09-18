#include "robot.h"
#include "mrpiz.h"
#include <unistd.h>


static int speed_pct = 100;

//initialisation du robot 
extern void robot_init(void)
{

    if (mrpiz_init() == -1) {
        mrpiz_error_print("Problème d'initialisation avec le simulateur");
    }
}


//avancement du robot par la mise en marche des deux moteurs 
extern void robot_start_forward(void)
{
    mrpiz_motor_set(MRPIZ_MOTOR_BOTH, speed_pct);
}


//pour stoper le robot
extern void robot_stop(void)
{
    mrpiz_motor_set(MRPIZ_MOTOR_BOTH, 0);
}


//pour tourner selon une direction donnée 
extern void robot_turn(direction_t dir)
{
    switch (dir)
    {
    case DIR_DROITE:
        mrpiz_motor_set(MRPIZ_MOTOR_LEFT,speed_pct);
        mrpiz_motor_set(MRPIZ_MOTOR_RIGHT,-speed_pct);
        break;
    
    case DIR_GAUCHE:
        mrpiz_motor_set(MRPIZ_MOTOR_RIGHT,speed_pct);
        mrpiz_motor_set(MRPIZ_MOTOR_LEFT,-speed_pct);
        break;
    
    default:
        break;
    }
}

//recuper la valeur de l'encoder
encoder_t get_encoder(void){
    encoder_t c;
    c.left=mrpiz_motor_encoder_get(MRPIZ_MOTOR_LEFT );
    c.right=mrpiz_motor_encoder_get(MRPIZ_MOTOR_RIGHT);

    return c;
}

//reseter les encoders
void reset_encoder(void){

    mrpiz_motor_encoder_reset(MRPIZ_MOTOR_BOTH );

}


void robot_forward_obstacle() {
    while (mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_CENTER) < 100) {
        mrpiz_motor_set(MRPIZ_MOTOR_BOTH, 100);
    }

    mrpiz_motor_set(MRPIZ_MOTOR_BOTH, 0);
}

//reccuperer la direction de l'obstacle
direction_t robot_get_obstacle_direction() {
    int left   = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_LEFT);
    int center = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_CENTER);
    int right  = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_RIGHT);

    if (left == -1 || center == -1 || right == -1) {
        return DIR_GAUCHE;
    }

    // obstacle  à gauche
    if (left > right && left > center) {
        return DIR_GAUCHE;
    }

    //obstacle à droite
    if (right > left && right > center) {
        return DIR_DROITE;
    }

    //obstacle en face : il faut choisir le cote le plus libre
    if (left < right) {
        return DIR_DROITE;
    } else {
        return DIR_GAUCHE;
    }

    
}

//permet de detection la presence de l'obstacle en renvoyant un booleen
bool robot_obstacle_detected() {
    int left   = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_LEFT);
    int center = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_CENTER);
    int right  = mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_RIGHT);

    if (left == -1 || center == -1 || right == -1) {
        return false;
    }

    if (center > 100 || left > 120 || right > 120) {
        return true;
    }

    return false;
}