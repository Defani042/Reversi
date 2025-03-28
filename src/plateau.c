 #ifndef _PLATEAU_C_
#define _PLATEAU_C_

#include "plateau.h"

/*
R: vider le buffer sur la ligne de commande
E: vide
S: vide 
*/

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  /* Lire jusqu'à la fin de ligne ou EOF*/
}


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
  printf("Case vide = '.'\n");
  printf("Case Noir = 'N'\n");
  printf("Case Blanche = 'B'\n");
  printf("Case jouable = '+'\n");
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
      case 3:
	printf(" +");
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

/*
R: determine si le plateau est remplie ou non
E: un TAD plat
S: 1 entier 1 si le plateau est rempli 0 sinon
*/

int plateau_remplie(plat p){
  int i,j;
  /*on parcourps le plateau*/
   for(i=0;i<p->c;i++){
    for(j=0;j<p->l;j++){
      if(p->mat[i][j]==0)return 0;/*si une case est à 0 (vide) on renvoi 0*/
    }
   }
   return 1; /*sinon on renvoie 1*/
}

/*
R: permet d'affecter une valeur à une case du plateau
E: 3 entier x,y et la valuer et un TAD plat
S: 1 entier 1 l'affectation c'est bien passer 0 sinon
*/

int set_case_plateau(int x,int y,int val,plat p){
  if(x >= p->c || y >= p->l || x<0 || y<0){/*teste si on depasse la taille du plateau*/
    printf("coordonées invalide [%d,%d]\n",x,y);
    return 0;
  }
  if(p->mat[x][y]!=0 || p->mat[x][y]){/*test si la case est vide ou que le coup est jouable*/
    printf("la case est déjà occupé\n");
    return 0;
  }
  p->mat[x][y]=val;
  return 1;
  
}

/*
R: permet de demander les coordonnées ou le joueur souhaite placer ces pions
E: 1 TAD plat
S: vide
*/

void saisir_coup(plat p) {
    int x, y, res = 0;

    while (!res) {
        printf("Saisir des coordonnées x (entre 1 et %d) et y (entre 1 et %d) : ", p->l, p->c);
        
        /*Vérification de la saisie*/
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Entrée invalide. Veuillez entrer deux nombres entiers.\n");
            vider_buffer();
        }

        /*Vérification et placement du coup*/
        res = set_case_plateau(x-1, y-1, 1, p);
        if (!res) {
            printf("Coordonnées invalides ou case occupée. Réessayez.\n");
        }
        
        vider_buffer();
    }

    printf("Fin du tour\n");
}

/*
R: faire en sorte que tous les coup jouable soit remplacer par des case vide 
E: un TAD plat
S: vide 
*/

void reset_plateau(plat p){
    for(i=0;i<p->l;i++){
        for(j=0;j<p->c;j++){
            if(p->mat[i][j]==4)set_case_plateau(i,j,0,p);
        }
    }
}

/*
R: gestion de la boucle de jeu sur le terminale
E: vide
S: vide
*/

void boucle_jeu_terminal(){
  /*création et allocution du plateau*/
  plat p;
  p=allocution_plateau(LIGNE,COLONNE);
  printf("début de la partie\n");
  /*tant que le plateau n'est pas rempli*/
  while(!plateau_remplie(p)){
    printf("\033[H\033[J");/*clear le terminal*/
    afficher_plateau(p);/*on affiche le plateau*/
    saisir_coup(p);/*on demande un coup a l'utilisateur*/
  }
  liberer_plateau(p);
  printf("fin de partie\n");
}

#endif /*_PLATEAU_C_*/
