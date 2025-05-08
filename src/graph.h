#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>

#define MAX_COUPS 60  /* Nombre maximum de coups */

/* Structure pour stocker l'analyse des coups */
typedef struct {
    int score_noir[MAX_COUPS];  /* Scores des pions noirs à chaque coup */
    int score_blanc[MAX_COUPS]; /* Scores des pions blancs à chaque coup */
    float temps_ia[MAX_COUPS];  /* Temps de réflexion de l'IA pour chaque coup */
    int coup_index;             /* Indice du dernier coup joué */
} analyse_t;

extern analyse_t analyse;

void initialiser_analyse();

void enregistrer_analyse(int score_noir, int score_blanc, float temps_ia);

 void afficher_graphique_sur_fenetre();


#endif /*_GRAPH_H_*/
