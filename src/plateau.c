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

int setcase(int x,int y,int val,plat p){
  if(x >= p->c || y >= p->l || x<0 || y<0){/*teste si on depasse la taille du plateau*/
    printf("coordonées invalide [%d,%d]\n",x,y);
    return 0;
  }
  if(p->mat[x][y]!=0){/*test si la case est vide*/
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
            continue;
        }

        /*Vérification et placement du coup*/
        res = setcase(x-1, y-1, 1, p);
        if (!res) {
            printf("Coordonnées invalides ou case occupée. Réessayez.\n");
        }
        
        vider_buffer();
    }

    printf("Fin du tour\n");
}



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

/*
R: permet de lire si le coup est valide ou non
E: 1 TAD plat, int x (ligne) et y (colonne) pour les coordonnées, et la couleur du joueur
S: 0 si invalide, 1 est valide
*/

int coup_valide(plat p, int x, int y, int couleur){
  int x_tmp, y_tmp, i, j, adversaire, trouve;
  if (couleur == 1) adversaire = 2;
  else adversaire = 1;
/* On regarde les cas particuliers où le joueur a indiqué les coordonnées d'une case non vide ou d'une case aux coordonnées invalides*/
  if ((x < 0) || (x >= p->c) || (y < 0) || (y >= p->c) || (p->mat[x][y] != 0)) return 0;

  for (i = -1; i < 2; i++){
    for (j = -1; j < 2; j++){
      /* Une boucle sur les 8 positions possibles*/
      if ((x+i < 0) || (x+i >= p->l) || (y+j < 0) || (y+j >= p->c) || ((x == x+i)&&(y == y+i))){
        ;
        /*Sont exclus les cas où les coordonnées tombent en dehors de la matrice où si les coordonnées sont égales à celle rentrées par l'utilisateur*/
      }
      else{
        if (p->mat[x+i][y+j] == adversaire){
          /* Si jamais les coordonnées qu'on regarde correspondent à celle d'un pion adversaire :*/
          x_tmp = x+2*i;
          y_tmp = y+2*j;
          trouve = 0;
          do{
            /* Tant que les coordonnées qu'on regarde tombent sont définies dans la matrice :*/
            if ((x_tmp < 0) || (x_tmp >= p->l) || (y_tmp < 0) || (y_tmp >= p->c)){
              trouve = -1;
            }
            /*On regarde si les coordonnées correspondent a du vide (donc coup invalide) ou à un pion de la couleur du joueur (coup valide)*/
            else{
              if (p->mat[x_tmp][y_tmp] == couleur){
                trouve = 1;
              }
              else{
                if (p->mat[x_tmp][y_tmp] == 0){
                  trouve = -1;
                }
              }
              x_tmp += i;
              y_tmp += j;
            }
          } while (trouve == 0);
          if (trouve == 1){
            /*Si on a trouvé un coup valide, on sort tout de suite des différentes boucles :*/
            i = 2;
            j = 2;
          }
        }
      }
    }
  }
  /*Si on a pas trouvé un coup valide, alors on renvoit 0, sinon 1*/
  if (trouve != 1){
    return 0;
  }
  return 1;
}

/*
R: permet de trouver qui est le gagnant de la partie
E: 1 TAD plat, couleur du joueur
S: -1 si le bot est vainqueur, 1 si le joueur est vainqueur, 0 si égalité
*/
int position_gagnante(plat p, int couleur){
  int score_j=0, score_b=0, x, y;
  /*Deux boucles pour couvrir toutes les cases*/
  for (x=0;x<p->l;x++){
    for (y=0;y<p->c;y++){
      /*Si c'est de la couleur du joueur, on augmente son score*/
      if (p->mat[x][y] == couleur){
        score_j++;
      }
      else{
        /*Si c'est vide, personne n'a de point*/
        if (p->mat[x][y] == 0){
          ;
        }
        else{
          /*Sinon, il ne reste plus que le cas où c'est la couleur du bot*/
          score_b++;
        }
      }
    }
  }
  if (score_j > score_b) return 1;
  if (score_j == score_b) return 0;
  return -1;
}

/*
R: permet d'ajouter des 4 dans la matrice de jeu afin de visualiser les coups valides
E: 1 TAD plat, couleur du bot
S: Le plateau
*/
plat liste_coup_valide(plat p, int couleur){
  int x,y;
  /*On regarde pour chacune des cases s'il y a un coup valide*/
  for (x=0;x<p->l;x++){
    for (y = 0; y < p->c; y++){
      if (coup_valide(p, x, y, couleur) == 1){
        p->mat[x][y] = 4;
      }
    }
  } 
  return p;
}

/*
R: permet de renvoyer dans x et y les coordonnées que joue le bot.
E: 1 TAD plat déjà remplie de 4, adresse de x et y
S: Ne renvoit rien, modifie les valeurs d'adresse x et y. En cas d'erreur, x et y valent -1
*/
void coup_ordinateur(plat p, int * x, int * y){
  int nbr_coup = 0, x_tmp, y_tmp, cherche = 0, objectif;
  /*On initialise les variables données dans la fonction afin de les renvoyer directement si on a pu jouer aucun coup*/
  *x=-1;
  *y=-1;

  /*On compte le nombre de coups disponibles*/
  for (x_tmp=0;x_tmp<p->l;x_tmp++){
    for (y_tmp = 0; y_tmp < p->c; y_tmp++){
      if (p->mat[x_tmp][y_tmp] == 4){
        nbr_coup++;
      }
    }
  } 

  /*On pioche aléatoirement quel sera le coup que le bot va jouer*/
  objectif = (rand()%nbr_coup+1);

  /*On trouve le coup numéro objectif, et on insère ses coordonnées dans x et y*/
  for (x_tmp=0;x_tmp<p->l;x_tmp++){
    for (y_tmp = 0; y_tmp < p->c; y_tmp++){
      
      if (p->mat[x_tmp][y_tmp] == 4){
        cherche++;
        /*Si on a atteint*/
        if (cherche == objectif){
          *x = x_tmp;
          *y = y_tmp;
          /*On fait en sorte de sortir de la boucle*/
          x_tmp = p->l;
          y_tmp = p->c;
        }
      }
    }
  } 
}

plat plat_supprimer_quatre(plat p){
  int x,y;
  for (x=0;x<p->l;x++){
    for (y = 0; y < p->c; y++){
      if (p->mat[x][y] == 4){
        p->mat[x][y] = 0;
      }
    }
  } 
  return p;
}

#endif /*_PLATEAU_C_*/
