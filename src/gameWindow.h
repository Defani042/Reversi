#ifndef _GAMEWINDOW_H_
#define _GAMEWINDOW_H_

#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>


void affiche_piece(int h,char x,char y,int joueur);

char conversion_ligne(int h, int x);

char conversion_colonne(int h, int y);

void coordonnees(int h);

void grille(int h);

int setMainWindow();

void jeu();


#endif /*_GAMEWINDOW_H_*/