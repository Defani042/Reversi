#ifndef _GAMEWINDOW_H_
#define _GAMEWINDOW_H_

#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>


void affiche_piece(int h,char x,char y,int joueur);

void conversion(int h, int x, int y,int j);

void quitter(int h);

void coordonnees(int h);

void grille(int h);

int setMainWindow();

void jeu();


#endif /*_GAMEWINDOW_H_*/