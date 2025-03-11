#ifndef _PLATEAU_C_
#define _PLATEAU_C_

#include "plateau.h"

/*
R: allouer un TAD plat dans la mémoire
E: 2 entiers <nb_ligne> <nb_colonne>
S: un TAD plat 
*/

plat allocution_plateau(int l,int c){
  plat p;
  int i;
  
  /*allocution d'un TAD plat*/
  if((p = (plat)malloc(sizeof(s_plateau)))==NULL){
    printf("erreur malloc \n");
    exit(EXIT_FAILURE);
  }
  
  /*on rentre les dimensions de la matrice*/
  p->l=l;
  p->c=c;
  
  /*allocution des lignes de la matrice*/
  if((p->mat = (int**)calloc(l,sizeof(int*)))==NULL){
    printf("erreur calloc \n");
    exit(EXIT_FAILURE);
  }
  
  /*alloction des colonnes de la matrice*/
  for(i=0;i<l;i++){
    if((p->mat[i] = (int*)calloc(c,sizeof(int)))==NULL){
      printf("erreur calloc \n");
      exit(EXIT_FAILURE);
    }
  }
  /*initialisation des case de base du plateau*/
  p->mat[3][3]=1;
  p->mat[4][4]=1;
  p->mat[3][4]=2;
  p->mat[4][3]=2;
  return p;
}

/*
R: libération du TAD plat dans la mémoire
E: 1 TAD plat
S: vide
*/

void liberer_plateau(plat p){
  int i;
  /*liberation des colonnes de la matrice*/
  for(i=0;i<p->c;i++){
    free(p->mat[i]);
    p->mat[i]=NULL;
  }
  /*liberation des lignes de la matrice*/
  free(p->mat);
  p->mat=NULL;
  /*liberation des colonne de la matrice*/
  free(p);
  p=NULL;
  

}

/*
R: affichage du TAD dans le terminale
E: un TAD plat
S: vide
*/

void afficher_plateau(plat p){
  int i,j;
  /*bordure supérieur du plateau*/
  printf("    ");
  for(i=0;i<p->c;i++){
    printf("%d ",i+1);
  }
  printf("\n");
  printf("   ---------------- \n");
  for(i=0;i<p->c;i++){
    printf("%d |",i+1);/*bordure gauche du plateau*/
    for(j=0;j<p->l;j++){
      switch (p->mat[i][j]){
      case 0:/*cas ou la case est vide*/
	printf(" .");
	break;
      case 1:/*cas ou la case est Noir*/
	printf(" N");
	break;
      case 2:/*cas ou la case est Blanche*/
	printf(" B");
	break;
      default:/*cas d'erreur*/
	printf(" E");
	break;
      }

    }
    printf("|\n");/*bordure droite du plateau*/

  }
  /*bordure inférieur du plateau*/
  printf("   ---------------- \n");
}

/*
R: affichage d'une matrice dans le terminale
E: un TAD plat
S: vide
*/

void afficher_mat(plat p){
  int i,j;
  for(i=0;i<p->c;i++){
    for(j=0;j<p->l;j++){
      printf("%d ",p->mat[i][j]);/*afichage de la case [i][j]*/
    }
    printf("\n");
  }
}

#endif /*_PLATEAU_C_*/
