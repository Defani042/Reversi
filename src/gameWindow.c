#ifndef _GAMEWINDOW_C_
#define _GAMEWINDOW_C_

#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>

#include "gameWindow.h"

#define FONT_PATH "fich/04B_30__.TTF"
#define PATH_IMAGE "fich/fond.jpg"
#define PATH_FOND_VERT "fich/vert.jpg"
#define N 5



/*
R : Permet d'afficher les pieces
E : taille fenêtre, corrdonnées x et y, joueur
S : rien
*/

void affiche_piece(int h, char x, char y, int joueur){
    int i,j;

    if ((x >= 'A' || x <= 'H') && (y >= '0' || y <= '8')){ /*si les coordonnées sont coorectes*/

        i = x-'A'+1;      /*Converti la lettre pour l'affichage*/
        j = y-'0';        /*Converti la lettre pour l'affichage*/

        if(joueur==2){ /*Si le joueur est blanc*/
            MLV_draw_filled_circle(i*h/9+h/18,j*h/9+h/18,h/24,MLV_COLOR_WHITE);
        }
        if(joueur==1) MLV_draw_filled_circle(i*h/9+h/18,j*h/9+h/18,h/24,MLV_rgba(0,0,0,255)); /*si le joueur est noir*/
        if(joueur==4) MLV_draw_filled_circle(i*h/9+h/18,j*h/9+h/18,h/48,MLV_rgba(172,172,172,255)); /*si le coup est jouable*/
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
R : permet d'afficher le plateau
E : plateau et hauteur de la fenetre
S : 
 */

void afficher_plateau(plat p,int h){
    char i,j;
    for (i='A';i<='H';i++){
        for (j='0';j<='8';j++){
            affiche_piece(h,i,j,p->mat[i-'A'][j-'0']);
        }
    }
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
            i + h/36, h/36,
            aff,                        /* on affiche le caractère */
            font, MLV_rgba(225,192,152,255)
        );
    }
    j=0;
    for(i=h/9;i<h;i+=h/9){  /* boucle visant a afficher aux bon endrois les caractère du tableau */
        sprintf(aff,"%c",chiffre[j++]); /*on transforme le caractère en string*/
        MLV_draw_text_with_font(
            h/36, i+h/36,
            aff,                        /* on affiche le caractère */
            font, MLV_rgba(225,192,152,255)
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
            MLV_draw_line(i,j,i,h,MLV_rgba(0,100,0,255)); /* affiche les lignes horizontales */
            MLV_draw_line(i,j,h,j,MLV_rgba(0,100,0,255)); /* affiche les lignes verticales */
        
        }
    }
    MLV_draw_line(0,h-1,h-1,h-1,MLV_rgba(0,100,0,255));  /*Affiche les lignes aux bords*/
    MLV_draw_line(h-1,0,h-1,h-1,MLV_rgba(0,100,0,255)); /*droit et bas de l'ecran*/
}

/*
R : Permet d'afficher le fond d'écran
E : Hautur ecrran
S : Rien
*/

void background(int h){
    MLV_Image* background;
    background = MLV_load_image(PATH_IMAGE);

    MLV_resize_image(background,h,h);
    MLV_draw_image(background,0,0);

    background = MLV_load_image(PATH_FOND_VERT);

    MLV_resize_image(background,h-h/9,h-h/9);
    MLV_draw_image(background,h/9,h/9);
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
    background(height); /*met le fond d'écran*/
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
    affiche_piece(h,'D','4',2); /* 0 pour le joueur blanc*/
    affiche_piece(h,'E','5',2);
    affiche_piece(h,'E','4',1); /* 1 ( ou autre ) pour le joueur noir*/
    affiche_piece(h,'D','5',1);

    while(i){ /*boucle de jeu*/
        MLV_actualise_window();     /* actualise la fenêtre */
        MLV_wait_mouse(&x,&y);      /* attends un click et met les coordonnées dans x et y */
        if(x<h/9 && y<h/9) i=0;     /* quitte si on clique au bon endroit */
        affiche_piece(h,conversion_ligne(h,x),conversion_colonne(h,y),4);
    }
    MLV_free_window();
}

#endif /*_GAMEWINDOW_C_*/