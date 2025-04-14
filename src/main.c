/*librairie standart*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include <unistd.h>
#include <getopt.h>

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
    printf("%s : Permet de jouer sur une fenêtre.\n\n",s);
    printf("%s --terminal : Permet de jouer sur le terminal.\n\n",s);
    printf("%s --regles : Permet d'afficher les règles du jeu.\n\n",s);
    printf("%s --niveau val(de 0 à 4) : Choisit la difficulté, par default 2.\n\n",s);
    printf("%s --prof val(<0) : Choisit la profondeur de l'arbre pour l'ordinateur pour un difficulté personalisée.\n\n",s);
}

int main(int argc,char*argv[]){
    int val,index=-1;/*entiers relatifs aux fonctions de getopt.h*/
    int terminal=0,h=1,r=1,niveau=2,profondeur=0;/*entiers relatifs aux options*/
    
    const char* optstring=":htrn:";
    const struct option lopts[] = {
        {"help", 0, NULL, 'h'},
        {"terminal", 0, NULL, 't'},
        {"regle", 0, NULL, 'r'},
        {"niveau", 1, NULL, 'n'},
        {"prof", 1, NULL, 'p'},
        {NULL, 0 , NULL , 0}
    };

    val=getopt_long(argc,argv,optstring,lopts,&index);
    while( val!=EOF){
        switch(val){
        case 'h' : aide(argv[0]);h=0; break;
        case 't' : terminal=1; break;
        case 'r' : regles();r=0; break;
        case 'n' : {niveau = atoi(optarg);
                if (niveau < 0) niveau *= -1;
                niveau = niveau%5;
                printf("Le niveau de difficulté a été réglé à %d.\n",niveau);
                break;
        }
        case 'p' : {profondeur = atoi(optarg);
                if (profondeur < 0) profondeur *= -1;
                profondeur = profondeur%60;
                printf("La profondeur a été réglé à %d.\n",profondeur);
                break;
        }
        case ':' : printf("Argument manquant pour --%c, niveau par defaut utilisé (2).\n",optopt);break;
        case '?' : printf("Option inexistante.\n");break;
        }
        index=-1;
        val=getopt_long(argc,argv,optstring,lopts,&index);
    }

    if(h && r){printf("Aide : %s --help\n",argv[0]);

        /*Test MainWindows*/
        if(terminal) boucle_jeu_terminal();
        else jeu();
    }
    exit(EXIT_SUCCESS);
}
  
