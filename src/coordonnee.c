#ifndef _COORDONNEE_C_
#define _COORDONNEE_C_
#include "coordonnee.h"

/*
R: permet de compter les coups possibles
E: 1 TAD plat
S: Le nombre de coup possibles
*/
int plat_compter_quatre(plat p){
    int x,y,score=0;
    for (x=0;x<p->l;x++){
    for (y = 0; y < p->c; y++){
      if (p->mat[x][y] == 4){
          score++;
      }
    }
  } 
  return score;
}

/*
R: permet de creer un tableau de coordonnées
E: Un int len
S: Le tab_coordonnee
*/
tab_coordonnee creer_coord(int len){
    int x;
    tab_coordonnee tc;
    if ((tc.tab = (coordonnee *) malloc (len * sizeof(coordonnee))) == NULL){
        printf("Erreur malloc par la fonction creer_coord()\n");
        exit(EXIT_FAILURE);
    }
    /*On initialise le talbeau de valeurs à -1*/
    for (x=0;x<len;x++){
        tc.tab[x].x = -1;
        tc.tab[x].y = -1;
    }
    tc.len = len;
    return tc;
}

/*
R: permet de rajouter des coordonnées dans un tableau
E: Le tableau de coordonnée, un entier x, y ainsi que l'indice i dans lequel on doit l'insérer
S: 1 si tout est bon, -1 si erreur
*/
int ajout_coord(tab_coordonnee * tc, int x, int y, int i){
    if ((i >= tc->len) || (i < 0)){
        printf("Ajout_coord() : Erreur, indice %i hors de portée\n", i);
        return -1;
    }
    tc->tab[i].x=x;
    tc->tab[i].y=y;
    return 1;
}

/*
R: Libère le tableau de coordonnées
E: Le tableau de coordonnée
S: Rien
*/
void liberer_tab_coord(tab_coordonnee tc){
    free (tc.tab);
    tc.tab = NULL;
}

/*
R: Affiche dans le terminal le tableau de coordonnées
E: Le tableau de coordonnée
S: Rien
*/
void affiche_coord(tab_coordonnee tc){
    int x=0;
    printf("{");
    while ((x < tc.len) || (tc.tab[x].x == -1) || (tc.tab[x].y == -1)){
        if (x != 0){
            printf(", ");
        }
        printf("(%d, %d)", tc.tab[x].x, tc.tab[x].y);
        x++;
    }
    printf("}\n");
}

/*
R: Récupère la position de tous les coups valides
E: Le plateau
S: Le tableau de coordonnées.
*/

tab_coordonnee recup_coup_valide(plat p){
    int x,y,n=0;
    tab_coordonnee tc;
    tc = creer_coord(plat_compter_quatre(p));
    
    for (x=0;x<p->c;x++){
        for (y=0;y<p->l;y++){
            if (p->mat[x][y] == 4){
                if (ajout_coord(&tc, x, y, n) == -1){
                    printf("Erreur, plus de coup récupérés que de coups valides\n");
                }
                n++;
            }
        }
    }
    return tc;
}

#endif /*_COORDONNEE_C_*/