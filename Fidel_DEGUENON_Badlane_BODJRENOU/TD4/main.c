/**
 * @file main.c
 * @brief Programme principal du robot
 *
 * Ce programme lit en boucle une commande clavier et traite la commande.
 */

#include <stdio.h>
#include <pilot.h>
#include <unistd.h>
#include <stdlib.h>
#include "mrpiz.h"

#include "move.h"
#include "follower.h"
#include "solver.h"

/**
 * @brief Point d'entrée principal du programme.
 *
 * @return Toujours 0 (succès).
 */

 
int main()
{

    //initialisation
    pilot_init();//mise en place de la communication avec l'environnement de simulation
    solver_t my_solver;
    solver_init(&my_solver);

    printf("--- Lancement du Robot Solver ---\n");

    
    printf("Recherche d'un mur à droite...\n");
    search_wall(DIR_DROITE);//recherche d'un mur de droite à suivre

    
    while (1) {
        
        //on vérifie ici si le mur est présent ou pas 
        if (wall_lost() ) {
            printf("Mur perdu ! Le solver décide...\n");
            

            //recherche d'une nouvelle direction
            direction_t turn_dir = get_next_direction(&my_solver);

            int angle;
            //choix du tournage
            if (turn_dir == DIR_GAUCHE)
                angle = 90;
            else if (turn_dir == DIR_DROITE)
                angle = 270;
            else  
                angle = 180;

            move_t turn = {MOVE_TURN, angle};
            pilot_start_move(turn);
            
            while (!pilot_stop_at_target());
        } 
        else {
            
            follow_wall();//suivi du mur car presence du mur
            
            
            my_solver.successive_turns = 0;
        }

    }

    return 0;
   
}

