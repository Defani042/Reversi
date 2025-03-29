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

    if ((x >= 'A' || x <= 'H') && (y >= '0' || y <= '7')){ /*si les coordonnées sont coorectes*/

        i = x-'A'+1;      /*Converti la lettre pour l'affichage*/
        j = y-'0'+1;        /*Converti la lettre pour l'affichage*/

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

char conversion_ligne(int h,int x){
    int j;
    char l='z'; /*l = ligne*/
    
    for(j=1;j<9;j++){   /*Converti les coordonnées x de la souris en lettre*/
        if(x>h/9*j) l=j+'A';
    }
    return l;
}

/*
R : Converti les coordonnées en lettres
E : coordonnées x
S : le caractère de la colonne
*/

char conversion_colonne(int h,int y){
    int i;
    char c='z'; /*l = colonne*/
    
    for(i=1;i<9;i++){ /*Converti les coordonnées y de la souris en chiffre*/
        if(y>h/9*i) c=i+'0';
    }

    return c;
}

/*
R : permet d'afficher le plateau
E : plateau et hauteur de la fenetre
S : 
 */

void afficher_plateau_MLV(s_plateau p,int h){
    char i,j;
    for (i='A';i<='H';i++){
        for (j='0';j<='8';j++){
            affiche_piece(h,i,j,p.mat[i-'A'][j-'0']);
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
    free(font);
    font=NULL;
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

    free(background);
    background=NULL;
    background = MLV_load_image(PATH_FOND_VERT);

    MLV_resize_image(background,h-h/9,h-h/9);
    MLV_draw_image(background,h/9,h/9);
    
    free(background);
    background=NULL;
}

/*
R : Permet de créer la fenêtre princiale
E : plateau
S : la taille de la fenêtre
*/

int setMainWindow(s_plateau p){
    int height;

    height = MLV_get_desktop_height()-75; /* initialise la taille de l'écran*/


    background(height); /*met le fond d'écran*/
    grille(height);     /* créer la grille*/
    coordonnees(height);    /* affiches les coordonnées */
    afficher_plateau_MLV(p,height);
    MLV_actualise_window(); /* actualise la fenêtre */
    return height;          /* renvoie la taille de la fenêtre*/
}


/*
R : Affiche la fin de la partie
E : plateau et height
S : rien
*/

void fin_partie(plat plat, int h){
    int n,b,p,x,y;
    MLV_Font* font=NULL;                    /* font initialisé a NULL */
    p=20;                                   /* taille pixels */
    font = MLV_load_font(FONT_PATH , p );   /* chargement font */

    b=plat->scoreb;
    n=plat->scoren;
    if(b<n){
        MLV_draw_filled_rectangle(0,0,h,h/9,MLV_COLOR_BLACK);
        MLV_draw_text_with_font(
            20, 20,
            "Les noirs ont gagne",                        /* on affiche le caractère */
            font, MLV_rgba(135,135,135,255)
        );
    }
    if (n<b){
        MLV_draw_filled_rectangle(0,0,h,h/9,MLV_COLOR_WHITE);
        MLV_draw_text_with_font(
            20, 20,
            "Les blancs ont gagne",                        /* on affiche le caractère */
            font, MLV_rgba(135,135,135,255)
        );
    }
    if(n==b){
        MLV_draw_filled_rectangle(0,0,h,h/9,MLV_COLOR_YELLOW);
        MLV_draw_text_with_font(
            h/4, 30,
            "Egalite",                        /* on affiche le caractère */
            font, MLV_rgba(135,135,135,255)
        );
    }
    MLV_actualise_window();
    MLV_wait_mouse(&x,&y);
    free(font);
    font=NULL;
}   

/*
R: permet de demander les coordonnées ou le joueur souhaite placer ces pions
E: 1 TAD plat
S: vide
*/

void saisir_coup_mlv(plat p,int h) {
    int x=0, y=0, res = 0;
    while (!res) {
        
        /*Vérification de la saisie*/
        MLV_wait_mouse(&x ,&y);
        x=conversion_ligne(h,x)-'A'-1;
        y=conversion_colonne(h,y)-'0'-1;

        /*Vérification et placement du coup*/
        res = set_case_plateau(x, y, p->joueur, p);
    }
    
    p = retourner_jetons(p,x,y,p->joueur);
    printf("\n");
    afficher_mat(p);
    printf("\n");
    printf("Fin du tour\n");
}

/*
R : permet d'afficher le choix des couleurs
E : vide
S : vide
*/

void affichage_choix_joueur(int h){
    MLV_Font* font=NULL;                             /* font initialisé a NULL */
    int p;
    p=20;                                   /* taille pixels */
    font = MLV_load_font(FONT_PATH , p );   /* chargement font */
    MLV_draw_filled_rectangle(0,0,h/2,h,MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(h/2,0,h/2,h,MLV_COLOR_BLACK);
    MLV_draw_text_with_font(
        0, 30,
        "Cliquez sur une couleur pour choisir la votre",                        /* on affiche le caractère */
        font, MLV_rgba(135,135,135,255)
    );
    MLV_actualise_window();
    free(font);
    font=NULL;
}


/*
R : permet de choisir la couleur
E : vide
S : vide
*/

void choisir_joueur_mlv(plat p,int h){
    int x,y;
    affichage_choix_joueur(h);
    MLV_wait_mouse(&x,&y);
    if(x<h/2) {       
        p->joueur = 2;
        p->bot = 1;
    }
    else{
        p->joueur = 1;
        p->bot = 2;
    }
}

/*
R: gestion de la boucle de jeu sur mlv
E: vide
S: vide
*/

void boucle_jeu_mlv(){
    /*création et allocution du plateau*/
    int h;
    plat p;
    p=allocution_plateau(LIGNE,COLONNE);
    h=setMainWindow(*p);
    choisir_joueur_mlv(p,h);/*demande au joueur la couleur qu'il veux jouer*/
    /*tant que le plateau n'est pas rempli*/
    while(verifier_tour_joueur(p,p->joueur) || verifier_tour_joueur(p,p->bot)){
      p=liste_coup_valide(p,p->joueur); /*on affiche les coups valides*/
      h=setMainWindow(*p);
      if(verifier_tour_joueur(p,p->joueur)){
         saisir_coup_mlv(p,h);/*on demande un coup a l'utilisateur*/  
      }
      p=plat_supprimer_quatre(p); /*on efface les coups jouables pour le joueur*/
      if(verifier_tour_joueur(p,p->bot)){
          h=setMainWindow(*p);
          MLV_wait_milliseconds(500);
          coup_ordinateur(p); /*le bot joue*/
      }
      p=plat_supprimer_quatre(p); /*on efface les coups jouables pour le joueur*/
      calculer_score(p);/*on calcule le score*/
    }
    h=setMainWindow(*p);
    fin_jeux(p);
    liberer_plateau(p);
    fin_partie(p,h);
   
  }

/*
R : permet de jouer
E : rien
S : rien
*/

void jeu(){
    int height;
    height = MLV_get_desktop_height()-75; 

    MLV_create_window("Réversi","Réversi",height,height); /* créer la fenêtre*/

    boucle_jeu_mlv();
    
    MLV_free_window();
}

#endif /*_GAMEWINDOW_C_*/