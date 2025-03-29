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

void regles(){
  printf("Règles du reversi : \n");
  printf("\tLe jeu se joue en solo contre l'ordinateur;\n");
  printf("\tAu debut de la partie, le joueur choisit sa couleur ;\n");
  printf("\tLe joueur jouera toujours en premier peu importe sa couleur ;\n");
  printf("\tLes pions de depart sont posés au milieu du plateau ;\n");
  printf("\tLe but du jeu est d'avoir le plus de pions de la couleur du joueur ;\n");
  printf("\tPour se faire, le joueur doit poser un pion de telle sorte qu'il encarde un pion adverse ;\n");
  printf("\tLes pions ainsi encerclés changent de couleur ;\n");
  printf("\tL'encadrement peux se faire horizontalement, verticalement, ou diagonalement ;\n");
  printf("\tSeules les poses de pions qui encadrent ceux de l'adveraire sont acceptées ;\n");
  printf("\tLa partie prendra fin que si les deux joueurs ne peuvent plus jouer.\n");
  printf("\nEssayez donc par vous-même.\n\n");
}

void aide(char *s){
  printf("%s    : Permet de jouer sur une fenêtre.\n",s);
  printf("%s -t : Permet de jouer sur le terminal.\n",s);
  printf("%s -r : Permet d'afficher les règles du jeu.\n",s);
}

int main(int argc,char*argv[]){
  int val;
  char* optstring="htr";
  int terminal=0;
  int h=1,r=1;

  /*TEST plateau*/
  if(argc<1 && strcmp(argv[1], "t")==0){
 
    exit(EXIT_SUCCESS);
  }

  val=getopt(argc,argv,optstring);
  while( val!=EOF){
    switch(val){
      case 'h' : aide(argv[0]);h=0; break;
      case 't' : terminal=1; break;
      case 'r' : regles();r=0; break;
    }
  val=getopt(argc,argv,optstring);
  }

  if(h && r){printf("Aide : %s -h\n",argv[0]);

  /*Test MainWindows*/
    if(terminal) boucle_jeu_terminal();
    else jeu();
  }
  exit(EXIT_SUCCESS);
}
  
