#ifndef _GAMEWINDOW_H_
#define _GAMEWINDOW_H_

#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>

#include "plateau.h"


void affiche_piece(int h,char x,char y,int joueur);

char conversion_ligne(int h, int x);

char conversion_colonne(int h, int y);

void afficher_plateau_MLV(s_plateau p,int h);

void coordonnees(int h);

void afficher_plateau_MLV(s_plateau p, int h);

void grille(int h);

void background(int h);

int setMainWindow(s_plateau p);

void fin_partie(plat plat, int h);

void saisir_coup_mlv(plat p,int h);

void affichage_choix_joueur(int h);

void choisir_joueur_mlv(plat p,int h);

void affichage_qui_commence(int h);

int choisir_qui_commence(int h);

void boucle_jeu_mlv();

void jeu(int n);


#endif /*_GAMEWINDOW_H_*/