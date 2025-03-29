/*librairie standart*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include <unistd.h>

/*Macro*/
#define LIGNE 8
#define COLONNE 8

/*librairie local*/
#include "gameWindow.h"
#include "plateau.h"

int main(int argc,char*argv[]){
  int val;
  char* optstring="ht";
  int terminal=0;
  int h=1;

  /*TEST plateau*/
  if(argc<1 && strcmp(argv[1], "t")==0){
 
    exit(EXIT_SUCCESS);
  }

  val=getopt(argc,argv,optstring);
  while( val!=EOF){
    switch(val){
      case 'h' : printf("%s    : Permet de jouer sur une fenêtre.\n%s -t : Permet de jouer sur le terminal.\n",argv[0],argv[0]);h=0; break;
      case 't' : terminal=1; break;
    }
  val=getopt(argc,argv,optstring);
  }

  if(h){printf("Aide : %s -h\n",argv[0]);

  /*Test MainWindows*/
    if(terminal) boucle_jeu_terminal();
    else jeu();
  }
  exit(EXIT_SUCCESS);
}
  
