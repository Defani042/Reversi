/*librairie standart*/
#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>

/*Macro*/
#define LIGNE 8
#define COLONNE 8

/*librairie local*/
#include "gameWindow.h"
#include "plateau.h"

int main(){
  /*TEST plateau*/
  plat p; /*plateau de jeu*/
  p=allocution_plateau(LIGNE,COLONNE);
  afficher_mat(p);
  printf("\n");
  afficher_plateau(p);
  liberer_plateau(p);

/*Test MainWindows*/
  jeu();
  exit(EXIT_SUCCESS);
}
