#ifndef _GAMEWINDOW_C_
#define _GAMEWINDOW_C_

#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>

#define FONT_PATH "fich/04B_30__.TTF"
#define N 5



/*
R : Permet d'afficher les pieces
E : taille fenêtre, corrdonnées x et y, joueur
S : rien
*/

void affiche_piece(int h, char x, char y, int joueur){
    int i,j;

    if ((x >= 'a' || x <= 'h') && (y >= '0' || y <= '8')){ /*si les coordonnées sont coorectes*/

        i = x-'A'+1;      /*Converti la lettre pour l'affichage*/
        j = y-'0';        /*Converti la lettre pour l'affichage*/

        if(joueur==0){ /*Si le joueur est blanc*/
            MLV_draw_filled_circle(i*h/9+h/18,j*h/9+h/18,h/24,MLV_COLOR_WHITE);
        }
        /*sinon*/
        else MLV_draw_filled_circle(i*h/9+h/18,j*h/9+h/18,h/24,MLV_rgba(50,50,50,255));
    }
    /*si les coordonnées sont incorrectes, n'affiche rien*/
}

/*
R : Converti les coordonnées en lettres
E : coordonnées y
S : le caractère de la ligne
*/

char conversion_ligne(int h, int x){
    int j;
    char l='z'; /*l = ligne*/
    
    for(j=1;j<9;j++){   /*Converti les coordonnées y de la souris en lettre*/
        if(x>h/9*j) l=j+'A'-1;
    }
    return l;
}

/*
R : Converti les coordonnées en lettres
E : coordonnées x
S : le caractère de la colonne
*/

char conversion_colonne(int h, int y){
    int i;
    char c='z'; /*l = colonne*/
    
    for(i=1;i<9;i++){ /*Converti les coordonnées x de la souris en chiffre*/
        if(y>h/9*i) c=i+'0';
    }

    return c;
}

/*
R : Permet d'afficher le boutton quitter
E : hauteur de la fenêtre
S : Rien
*/

void quitter(int h){
    int p;
    MLV_Font* font=NULL;

    p=50; /*taille police*/
    font = MLV_load_font(FONT_PATH , p ); /*pointeur vers le fichier*/

    if(font==NULL){
        printf("Erreur : impossible de trouver le font, arrêt du programme");
        exit(EXIT_FAILURE); /*cas d'arrêt si on ne trouve pas le fichier font*/
    }

    /*affiche le rectangle rouge d'affichage*/
    MLV_draw_filled_rectangle(0,0,h/9,h/9,MLV_rgba(255,0,0,255));

    /*affiche le 'x' sur le fond rouge*/
    MLV_draw_text_with_font(
        (h/35), (h/50), /*<--- coordonnées du x*/
        "x",
        font, MLV_COLOR_WHITE 
    );
}

/*
R : Permet d'afficher les coordonnées
E : hauteur de la fenêtre
S : Rien
*/

void coordonnees(int h){
    int p,i,j=0;
    char lettre[]={'A','B','C','D','E','F','G','H'}; /* tableau de lettres */
    char chiffre[]={'1','2','3','4','5','6','7','8'};/* tableau de chiffres */
    char aff[N];                                     /* tableau pour afficher la lettre */
    MLV_Font* font=NULL;                             /* font initialisé a NULL */

    p=50;                                   /* taille pixels */
    font = MLV_load_font(FONT_PATH , p );   /* chargement font */

    if(font==NULL){ /* si le font est introuvable alors erreur */
        printf("Erreur : impossible de trouver le font, arrêt du programme");
        exit(EXIT_FAILURE);
    }

    for(i=h/9;i<h;i+=h/9){  /* boucle visant a afficher aux bon endrois les caractère du tableau */
        sprintf(aff,"%c",lettre[j++]); /* on transforme le caractère en string */
        MLV_draw_text_with_font(
            i, 0,
            aff,                        /* on affiche le caractère */
            font, MLV_COLOR_WHITE
        );
    }
    j=0;
    for(i=h/9;i<h;i+=h/9){  /* boucle visant a afficher aux bon endrois les caractère du tableau */
        sprintf(aff,"%c",chiffre[j++]); /*on transforme le caractère en string*/
        MLV_draw_text_with_font(
            0, i,
            aff,                        /* on affiche le caractère */
            font, MLV_COLOR_WHITE
        );
    }
}

/*
R : Permet de créer la grille
E : hauteur de la fenêtre
S : rien
*/

void grille(int h){
    int i,j;
    for(i=0;i<h;i+=h/9){
        for(j=0;j<h;j+=h/9){
            MLV_draw_line(i,j,i,h,MLV_rgba(255,255,255,255)); /* affiche les lignes horizontales */
            MLV_draw_line(i,j,h,j,MLV_rgba(255,255,255,255)); /* affiche les lignes verticales */
        
        }
    }
    MLV_draw_line(0,h-1,h-1,h-1,MLV_rgba(255,255,255,255));  /*Affiche les lignes aux bords*/
    MLV_draw_line(h-1,0,h-1,h-1,MLV_rgba(255,255,255,255));  /*droit et bas de l'ecran*/

    MLV_draw_line(h/9,h/9,h/9,h,MLV_rgba(255,255,0,255)); /*affiches les lignes colorées*/
    MLV_draw_line(h/9,h/9,h,h/9,MLV_rgba(255,255,0,255));
}

/*
R : Permet de créer la fenêtre princiale
E : rien
S : la taille de la fenêtre
*/

int setMainWindow(){
    int height;

    height = MLV_get_desktop_height()-75; /* initialise la taille de l'écran*/

    MLV_create_window("Réversi","Réversi",height,height); /* créer la fenêtre*/
    quitter(height);    /* créer le boutton quitter*/
    grille(height);     /* créer la grille*/
    coordonnees(height);    /* affiches les coordonnées */
    MLV_actualise_window(); /* actualise la fenêtre */
    return height;          /* renvoie la taille de la fenêtre*/
}

/*
R : permet de jouer
E : rien
S : rien
*/

void jeu(){
    int x,y,h,i=1;

    h=setMainWindow();

    /*Affichage 4 piece de base*/
    affiche_piece(h,'D','4',0); /* 0 pour le joueur blanc*/
    affiche_piece(h,'E','5',0);
    affiche_piece(h,'E','4',1); /* 1 ( ou autre ) pour le joueur noir*/
    affiche_piece(h,'D','5',1);

    while(i){ /*boucle de jeu*/
        MLV_actualise_window();     /* actualise la fenêtre */
        MLV_wait_mouse(&x,&y);      /* attends un click et met les coordonnées dans x et y */
        if(x<h/9 && y<h/9) i=0;     /* quitte si on clique au bon endroit */
        affiche_piece(h,conversion_ligne(h,x),conversion_colonne(h,y),0);
    }
}

#endif /*_GAMEWINDOW_C_*/