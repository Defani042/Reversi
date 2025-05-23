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
  int**mat; /*case vide:0 case noir:1 case blanche:2 case jouable:4*/
  int l,c;
  int joueur,bot; /*definir qui est le joueur et qui est le bot*/
  int scoreb,scoren; /*score de chacune des équipe*/ 
}s_plateau;
typedef s_plateau* plat;

void vider_buffer();

void choisir_joueur(plat p);

plat allocution_plateau(int l,int c);

void liberer_plateau(plat p);

void calculer_score(plat p);

void afficher_plateau(plat p);

void afficher_mat(plat p);

int plateau_remplie(plat p);

int set_case_plateau(int x,int y,int val,plat p);

void saisir_coup(plat p);

int coup_valide(plat p, int x, int y, int couleur);

int position_gagnante(plat p, int couleur);

plat liste_coup_valide(plat p, int couleur);

int coup_ordinateur(plat p);

plat plat_supprimer_quatre(plat p);

plat retourner_jetons(plat p, int x, int y, int couleur);

int verifier_tour_joueur(plat p, int val);

void fin_jeux(plat p);

int taper_qui_commence();

void boucle_jeu_terminal();

int  pltcpy(plat p, plat pc);

int eval_score(plat p,int couleur);
    

#endif /*_PLATEAU_H_*/
