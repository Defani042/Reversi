#ifndef _ARBRE_C_
#define _ARBRE_C_
#include "arbre.h"
/*
R: creer l'arbre vide
E: vide
S: 1 TAD arbre (l'arbre vide)
*/

arbre creer_arbre_vide(){
    return NULL;
}
/*
R: verifier si l'arbre est vide
E: 1 TAD arbre
S: 1 si oui sinon 0
*/

int est_arbre_vide(arbre a){
    return a == creer_arbre_vide();
}

/*
R: créer un arbre (non vide)
E: 1 TAD plat, 1 entier (le nombre de fils)
S: 1 TAD arbre
*/

arbre creer_arbre(int p,int nb_fils){
    arbre a;
    int i;
    /*allocution de l'arbre*/
    if((a=(arbre)malloc(sizeof(branche))) == NULL){
        printf("erreur Malloc par la fonction creer_arbre()\n");
        exit(EXIT_FAILURE);
    }
    a->val = p;
    /*allocution des branches de l'arbres*/
    if((a->branches=(branche**)malloc(nb_fils*sizeof(branche*))) == NULL){
        printf("erreur Malloc par la fonction creer_arbre()\n");
        exit(EXIT_FAILURE);
    }
    /*on set nb_fils*/
    a->nb_fils = nb_fils;
    /*on set toute les branches à NULL*/
    for(i=0;i<nb_fils;i++){
        a->branches[i] = NULL;
    }
    return a;
}

/*
R: ajout un fils à un arbre
E: 2 TADs arbre (pere) (fils) 
S: 1 TAD arbre
*/

arbre ajouter_branches(arbre a, arbre f){
    int i =0;
    if(est_arbre_vide(a))return f;/*si jamais a est l'arbre vide on retourne f*/
    /*on se déplace jusqu'à se qu'on trouve une branche Null ou qu'on atteigne la fin du tableau*/
    while(i<a->nb_fils && a->branches[i]!=NULL){
        i++;
    }
    if(i == a->nb_fils){
        if((a->branches=(branche**)realloc(a->branches,(a->nb_fils+1)*sizeof(branche)))==NULL){
            printf("erreur Realloc par la fonction ajouter_fils()\n");
            exit(EXIT_FAILURE);
        }
        a->nb_fils++;
        a->branches[i+1]=f;
    }
    else{
        a->branches[i] = f;
    }
    return a;
}

/*
R: ajout un fils à un arbre
E: 2 TADs arbre (pere) (fils) 
S: 1 vide
*/

void liberer_arbre(arbre a){
    int i;
    for(i=0;i<a->nb_fils;i++){
        if(a->branches[i]!=NULL){
            liberer_arbre(a->branches[i]);
        }
    }
    free(a);
    a =NULL;

}

/*
R: calculer le score d'un coup jouer sur le plateau
E: 1 TAD plat 1 int (la couleur du joueur)
S: 1 int le score
*/

int eval(plat p, int couleur){
  int x, y, score=0;
  int mat_eval[LIGNE][COLONNE] = {
      {COIN,BORD,BORD,BORD,BORD,BORD,BORD,COIN},
      {BORD,DANG,MAUV,MAUV,MAUV,MAUV,DANG,BORD},
      {BORD,MAUV,BASE,BASE,BASE,BASE,MAUV,BORD},
      {BORD,MAUV,BASE,DEFA,DEFA,BASE,MAUV,BORD},
      {BORD,MAUV,BASE,DEFA,DEFA,BASE,MAUV,BORD},
      {BORD,MAUV,BASE,BASE,BASE,BASE,MAUV,BORD},
      {BORD,DANG,MAUV,MAUV,MAUV,MAUV,DANG,BORD},
      {COIN,BORD,BORD,BORD,BORD,BORD,BORD,COIN}
  };
  
  for (x=0;x<p->l;x++){
    for (y=0;y<p->c;y++){
      if (p->mat[x][y] == couleur){
        score += mat_eval[x][y];
      } 
    }
  }
  return score;
}




#endif /*_ARBRE_C_*/