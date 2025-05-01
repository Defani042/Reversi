#ifndef _ARBRE_H_
#define _ARBRE_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#include "plateau.h"
#include "coordonnee.h"

/*macro*/
#define COIN 4
#define BORD 2
#define BASE 1
#define DEFA 0
#define MAUV -1
#define DANG -2

/*TAD arbre*/
typedef struct branche{
    int val;
    int nb_fils;
    coordonnee coord;
    struct branche **branches;
}branche;
typedef struct branche* arbre;

arbre creer_arbre_vide();

int est_arbre_vide(arbre a);

arbre creer_arbre(int p,int nb_fils);

arbre ajouter_branche(arbre a, arbre f);

void liberer_arbre(arbre a);

int eval(plat p, int couleur);

arbre simuler_coup_prof_0(plat p, int couleur);

arbre simuler_coup_prof_1(plat p, int couleur);

arbre simuler_coup_prof_2(plat p, int couleur);

void simuler_coup_etape_3(plat p, int couleur);

void boucle_jeu_etape_3();

void simuler_coup_etape_4(plat p, int couleur, int prof);

arbre simuler_coup_prof_n(plat p, int couleur, int prof);

void boucle_jeu_etape_4(int prof);

int alphabeta(arbre noeud, int alpha, int beta, int is_min);

#endif /*_ARBRE_H_*/