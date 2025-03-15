#ifndef _PLATEAU_H_
#define _PLATEAU_H_

/*std lib*/
#include <stdio.h>
#include <stdlib.h>

/*Macro*/
#define LIGNE 8
#define COLONNE 8

/*TAD plateau*/
typedef struct{
  int**mat; /*case vide:0 case noir:1 case blanche:2*/
  int l,c;
}s_plateau;
typedef s_plateau* plat;

void vider_buffer();

plat allocution_plateau(int l,int c);

void liberer_plateau(plat p);

void afficher_plateau(plat p);

void afficher_mat(plat p);

int plateau_remplie(plat p);

int setcase(int x,int y,int val,plat p);

void saisir_coup(plat p);

void boucle_jeu_terminal();

#endif /*_PLATEAU_H_*/
