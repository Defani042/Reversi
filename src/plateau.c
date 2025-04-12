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
R: permet au jouer de choisir sa couleur 
E: un TAD plat
S: vide
*/
void choisir_joueur(plat p){
    int c=0;
    printf("Couleur Noire = 1\n");
    printf("Couleur Blanc = 2\n");
    printf("Quelle couleur voulez vous jouez ?\n");
    /*Vérification de la saisie*/
    while(c!=1 && c!=2){
        if (scanf("%d",&c) != 1) {
            printf("Entrée invalide. Veuillez entrer un entier (1 ou 2).\n");
            vider_buffer();
        }
        vider_buffer();
    }
    if(c==1){
        p->joueur = 1;
        p->bot = 2;
    }
    else{
        p->joueur = 2;
        p->bot = 1;
    }
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
  /*le score correpson au nombre de pions de meme couleur sur le plateau*/
  p->scoreb = 2;
  p->scoren = 2;
  /*setting de base le joueur => noire et le bot => Blancs*/
  p->joueur = 1;
  p->bot = 2; 
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
R: calculer le score du plateu
E: un TAD plat
S: vide
*/

void calculer_score(plat p){
    int i,j;
    p->scoren = 0;
    p->scoreb = 0;
    /*on parcourps le plateau*/
    for(i=0;i<p->c;i++){
        for(j=0;j<p->l;j++){
            if(p->mat[i][j]==1){
                p->scoren++;
            }
            if(p->mat[i][j]==2){
                p->scoreb++;
            }
        }
    }
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
  /*printf("Taille_c =  %d\n",p->c);
    printf("Taille_l = %d\n",p->l);*/
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
      case 4:
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
  printf("score équipe Noire : %d\n",p->scoren);
  printf("score équipe Blanc : %d\n",p->scoreb);

/*printf("\n");
  afficher_mat(p);
  printf("\n");*/
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
  if(p->mat[x][y]!=4){/*test si la case est vide ou que le coup est jouable*/
    printf("la case est déjà occupé ou le coup est invalide\n");
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
    int x=0, y=0, res = 0;

    while (!res) {
        printf("Saisir des coordonnées x (entre 1 et %d) et y (entre 1 et %d) : ", p->l, p->c);
        
        /*Vérification de la saisie*/
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Entrée invalide. Veuillez entrer deux nombres entiers.\n");
            vider_buffer();
        }
        y--;
        x--;
        /*Vérification et placement du coup*/
        res = set_case_plateau(x, y, p->joueur, p);
        if (!res) {
            printf("Coordonnées invalides ou case occupée. Réessayez.\n");
        }
        
        vider_buffer();
    }
    
    p = retourner_jetons(p,x,y,p->joueur);
    printf("\n");
    afficher_mat(p);
    printf("\n");
    printf("Fin du tour\n");
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
  if ((x < 0) || (x >= p->l) || (y < 0) || (y >= p->c) || (p->mat[x][y] != 0)) return 0;

  for (i = -1; i < 2; i++){
    for (j = -1; j < 2; j++){
      /* Une boucle sur les 8 positions possibles*/
      if ((x+i < 0) || (x+i >= p->l) || (y+j < 0) || (y+j >= p->c) || ((x == x+i)&&(y == y+j))){
        ;
        /*Sont exclus les cas où les coordonnées tombent en dehors de la matrice où si les coordonnées sont égales à celle rentrées par l'utilisateur*/
      }
      else{
        if (p->mat[x+i][y+j] == adversaire){
          /* Si jamais les coordonnées qu'on regarde correspondent à celle d'un pion adversaire :*/
          x_tmp = x+i*2;
          y_tmp = y+j*2;
          trouve = 0;
          do{
            /* Tant que les coordonnées qu'on regarde sont définies dans la matrice :*/
            if ((x_tmp < 0) || (x_tmp >= p->l) || (y_tmp < 0) || (y_tmp >= p->c)){
              trouve = -1;
            }
            /*On regarde si les coordonnées correspondent a du vide (donc coup invalide) ou à un pion de la couleur du joueur (coup valide)*/
            else{
              if (p->mat[x_tmp][y_tmp] == couleur){
                trouve = 1;
              }
              else{
                if ((p->mat[x_tmp][y_tmp] == 0) || (p->mat[x_tmp][y_tmp] == 4)){
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
    for (y=0;y<p->c;y++){
      if (coup_valide(p, x, y, couleur) == 1){
        p->mat[x][y] = 4;
      }
    }
  } 
  return p;
}

/*
R: permet de jouer un coup avec le bot
E: 1 TAD plat déjà remplie de 4, adresse de x et y
S: Rnvoie 0 en cas d'erreur et 1 sinon.
*/

int coup_ordinateur(plat p){
    int nbr_coup = 0, x_tmp, y_tmp, cherche = 0, objectif, x=0 ,y=0,res;
  /*On compte le nombre de coups disponibles*/
  for (x_tmp=0;x_tmp<p->l;x_tmp++){
    for (y_tmp = 0; y_tmp < p->c; y_tmp++){
      if (p->mat[x_tmp][y_tmp] == 4){
        nbr_coup++;
      }
    }
  } 

if (nbr_coup == 0){
  return 0;
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
          x = x_tmp;
          y = y_tmp;
          /*On fait en sorte de sortir de la boucle*/
          x_tmp = p->l;
          y_tmp = p->c;
        }
      }
    }
  } 

  /*On joue le coup*/
  res= set_case_plateau(x,y,p->bot,p);
    if (!res) {
        printf("Coup Bot invalide.\n");
        printf("coup joué en [%d,%d]\n",x+1,y+1);
    }
   p=plat_supprimer_quatre(p);
   p=retourner_jetons(p,x,y,p->bot);
  
  return 1;
}

/*
R: permet de supprimer la liste des coups possibles
E: 1 TAD plat
S: Le TAD plat
*/
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

/*
R: Retourne les jetons entourés
E: 1 TAD plat, la coordonnée x et y du coup joué et la couleur.
S: Le TAD plat modifié
*/

plat retourner_jetons(plat p, int x, int y, int couleur){
  int x_tmp, y_tmp, i, j, adversaire, trouve, cmpt;
  if (couleur == 1) adversaire = 2;
  else adversaire = 1;
/* On regarde les cas particuliers où le joueur a indiqué les coordonnées d'une case non vide ou d'une case aux coordonnées invalides*/
  if ((x < 0) || (x >= p->l) || (y < 0) || (y >= p->c) || (p->mat[x][y] != couleur)) return p;

/*La fonction reprend en grande partie la fonction "coup_valide"*/
  for (i = -1; i < 2; i++){
    for (j = -1; j < 2; j++){
      /* Une boucle sur les 8 positions possibles*/
      if ((x+i < 0) || (x+i >= p->l) || (y+j < 0) || (y+j >= p->c) || ((x == x+i)&&(y == y+j))){
        /*Sont exclus les cas où les coordonnées tombent en dehors de la matrice où si les coordonnées sont égales à celle rentrées par l'utilisateur*/
      }
      else{
        if (p->mat[x+i][y+j] == adversaire){
          /* Si jamais les coordonnées qu'on regarde correspondent à celle d'un pion adversaire :*/
          x_tmp = x+i*2;
          y_tmp = y+j*2;
          trouve = 0;
          cmpt = 1;
          while(trouve == 0){
            /* Tant que les coordonnées qu'on regarde sont définies dans la matrice :*/
            if ((x_tmp < 0) || (x_tmp >= p->l) || (y_tmp < 0) || (y_tmp >= p->c)){
              trouve = -1;
            }
            /*On regarde si les coordonnées correspondent a du vide (donc coup invalide) ou à un pion de la couleur du joueur (coup valide)*/
            else{
              if (p->mat[x_tmp][y_tmp] == couleur){
                trouve = 1;
                while (cmpt != 0){
                  /*Partie modifiée de la fonction coup_valide. On remonte les coordonnées jusqu'à retomber sur les coordonnées de départ.*/
                  x_tmp -= i;
                  y_tmp -= j;
                  p->mat[x_tmp][y_tmp] = couleur;
                  cmpt--;
                }
              }
              else{
                if (p->mat[x_tmp][y_tmp] != adversaire){
                  trouve = -1;
                }
              }
              x_tmp += i;
              y_tmp += j;
              cmpt++;
            }
          }
        }
      }
    }
  }
  return p;
}

/*
R: verifie si le joeur peux jouer sur le plateau
E: 1 TAD plat et un entier
S: 1 si on peux jouer sinon 0
*/

int verifier_tour_joueur(plat p, int val){
    int i,j;
    p = liste_coup_valide(p,val);/*on donne la liste des coups valide*/
    for (i=0;i<p->l;i++){
        for (j=0;j<p->c;j++){
            if(p->mat[i][j]== 4)return 1; /* on retourne 1 */
        }
    }
    switch (val){
    case 1:/*cas ou le joueur Noire ne peux pas jouer*/
	printf("Les pions Noires ne peuvent pas jouer au tours des blancs.\n");
	break;
    case 2:
        printf("Les pions Blancs ne peuvent pas jouer au tours des Noires.\n");
        break;
    default:
        printf("Erreur: le joueur %d n'existe pas! \n",val);
        break;
    }      
    return 0;
}

/*
R: gestion de la fin de partie 
E: un TAD plat
S: vide
*/

void fin_jeux(plat p){
    if(p->scoreb > p->scoren){
        printf("Les pions Blancs Gagnent! \n");
        printf("Blanc: %d\n",p->scoreb);
        printf("Noire: %d\n",p->scoren);
    }
    else if(p->scoreb < p->scoren){
        printf("Les pions Noires Gagnent! \n");
        printf("Noire: %d\n",p->scoren);
        printf("Blanc: %d\n",p->scoreb);
    }
    else{
        printf("Egalité !!!");
        printf("Blanc: %d\n",p->scoreb);
        printf("Noire: %d\n",p->scoren);
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
  choisir_joueur(p);/*demande au joueur la couleur qu'il veux jouer*/
  /*tant que le plateau n'est pas rempli*/
  while(verifier_tour_joueur(p,p->joueur) || verifier_tour_joueur(p,p->bot)){
    printf("\033[H\033[J");/*clear le terminal*/
    p=liste_coup_valide(p,p->joueur); /*on affiche les coups valides*/
    afficher_plateau(p);/*on affiche le plateau*/
    if(verifier_tour_joueur(p,p->joueur)){
       saisir_coup(p);/*on demande un coup a l'utilisateur*/  
    }
    p=plat_supprimer_quatre(p); /*on efface les coups jouables pour le joueur*/
    if(verifier_tour_joueur(p,p->bot)){
        coup_ordinateur(p); /*le bot joue*/
    }
    calculer_score(p);/*on calcule le score*/
  }
  fin_jeux(p);
  liberer_plateau(p);
  printf("fin de partie\n");
 
}


#endif /*_PLATEAU_C_*/
