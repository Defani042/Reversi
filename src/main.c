/*librairie standart*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <MLV/MLV_all.h>

/*Macro*/
#define LIGNE 8
#define COLONNE 8

/*librairie local*/
#include "gameWindow.h"
#include "plateau.h"

int main(int argc,char*argv[]){
  /*TEST plateau*/
  if(argc<1 && strcmp(argv[1], "t")==0){
 
    exit(EXIT_SUCCESS);
  }
/*Test MainWindows*/
  jeu();
  boucle_jeu_terminal();
  exit(EXIT_SUCCESS);
}
  
