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
    /*On set les coordonnées*/
    a->coord.x = -1;
    a->coord.y = -1;
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

/*
R: Renvoie une feuille contenant la valeur évaluée du plateau simulé 
E: 1 TAD plat et la couleur
S: La feuille de l'arbre
*/

arbre simuler_coup_prof_0(plat p, int couleur){
    return creer_arbre(eval(p, couleur), 0);
}

/*
R: Renvoie un arbre contenant la valeur évaluée du plateau simulé la plus faible
E: 1 TAD plat et la couleur
S: Un arbre intermédiaire
*/
arbre simuler_coup_prof_1(plat p, int couleur){
    arbre a;
    int nbfils;
    int x,y,n,x_min,y_min;
    plat tmp = NULL;
    tab_coordonnee tc;
    int min = 999;

    x_min = min;
    y_min = min;
    nbfils = plat_compter_quatre(p);
    tc = recup_coup_valide(p);
    a = creer_arbre(min, nbfils);
    tmp = allocution_plateau(LIGNE, COLONNE);
    
    for (n=0;n<nbfils;n++){
        pltcpy(p, tmp);
        afficher_mat(p);
        x = tc.tab[n].x;
        y = tc.tab[n].y;
        if (set_case_plateau(x,y,couleur,tmp) != 1){
            printf("Cas impossible, s'inquiéter si ce message apparait(1)\n");
        }
        tmp=retourner_jetons(tmp,x,y,couleur);
        tmp=plat_supprimer_quatre(tmp);
        tmp=liste_coup_valide(tmp, couleur);
        a->branches[n] = simuler_coup_prof_0(tmp, (couleur%2)+1);
        if (min >= a->branches[n]->val){
            if (min == a->branches[n]->val){
                if (rand()%2){
                min = a->branches[n]->val;
                x_min = x;
                y_min = y;    
                }
            }
            else{
                min = a->branches[n]->val;
                x_min = x;
                y_min = y;
            }
        }
    }
    a->coord.x = x_min;
    a->coord.y = y_min;
    a->val = min;
    liberer_plateau(tmp);
    tmp = NULL;
    liberer_tab_coord(tc);
    return a;
}

/*
R: Renvoie un arbre contenant la valeur évaluée du plateau simulé la plus élevée
E: 1 TAD plat et la couleur
S: La racine de l'arbre
*/
arbre simuler_coup_prof_2(plat p, int couleur){
    arbre a;
    int nbfils;
    int x,y,n, x_max, y_max;
    plat tmp = NULL;
    tab_coordonnee tc;
    int max = -999;

    x_max = max;
    y_max = max;
    nbfils = plat_compter_quatre(p);
    tc = recup_coup_valide(p);
    a = creer_arbre(max, nbfils);
    tmp = allocution_plateau(LIGNE, COLONNE);
    
    for (n=0;n<nbfils;n++){
        pltcpy(p, tmp);
        x = tc.tab[n].x;
        y = tc.tab[n].y;
        if (set_case_plateau(x,y,couleur,tmp) != 1){
            printf("Cas impossible, s'inquiéter si ce message apparait(2)\n");
        }
        tmp=retourner_jetons(tmp,x,y,couleur);
        tmp=plat_supprimer_quatre(tmp);
        tmp=liste_coup_valide(tmp, couleur);
        a->branches[n] = simuler_coup_prof_1(tmp,(couleur%2)+1);
        if (max <= a->branches[n]->val){
            if (max == a->branches[n]->val){
                if (rand()%2){
                    max = a->branches[n]->val;
                    x_max = x;
                    y_max = y;
                }
            }
            else{
            max = a->branches[n]->val;
            x_max = x;
            y_max = y;
            }
        }
    }
    a->coord.x = x_max;
    a->coord.y = y_max;
    a->val = max;
    liberer_plateau(tmp);
    tmp = NULL;
    liberer_tab_coord(tc);
    return a;
}

/*
R: Joue le prochain coup en fonction de plateau simulés
E: 1 TAD plat et la couleur
S: Rien
*/
void simuler_coup_etape_3(plat p, int couleur){
    arbre a;
    a = simuler_coup_prof_2(p, couleur);
    set_case_plateau(a->coord.x,a->coord.y,couleur,p);
    p=retourner_jetons(p,a->coord.x,a->coord.y,couleur);
    p=plat_supprimer_quatre(p);
    liberer_arbre(a);
    a = NULL;
}

/*
R: Permet de jouer avec une IA de niveau étape 3
E: Aucun
S: Rien
*/

void boucle_jeu_etape_3(){
  /*création et allocution du plateau*/
  plat p;
  p=allocution_plateau(LIGNE,COLONNE);
  choisir_joueur(p);/*demande au joueur la couleur qu'il veux jouer*/
  if (!taper_qui_commence()){
      if(verifier_tour_joueur(p,p->bot)){
        simuler_coup_etape_3(p, p->bot); /*le bot joue*/
      } /*si le joueur commence pas, alors le bot joue*/
  }
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
        simuler_coup_etape_3(p, p->bot); /*le bot joue*/
    }
    calculer_score(p);/*on calcule le score*/
  }
  fin_jeux(p);
  liberer_plateau(p);
  printf("fin de partie\n");
 
}

/*Etape 4, arbre de profondeur n*/

/*
R: Joue le prochain coup en fonction du plateau simulé de profondeur n 
E: 1 TAD plat, la couleur et la profondeur
S: Rien
*/
void simuler_coup_etape_4(plat p, int couleur, int prof){
    arbre a;
    a = simuler_coup_prof_n(p, couleur, prof);
    set_case_plateau(a->coord.x,a->coord.y,couleur,p);
    p=retourner_jetons(p,a->coord.x,a->coord.y,couleur);
    p=plat_supprimer_quatre(p);
    liberer_arbre(a);
    a = NULL;
}

/*
R: Renvoit l'arbre simulant les prochains coups du bot ou du joueur en fonction de la profondeur
E: 1 TAD plat, la couleur et la profondeur
S: L'arbre de jeu
*/
arbre simuler_coup_prof_n(plat p, int couleur, int prof){
    arbre a;
    int nbfils;
    int x,y,n, x_min, y_min, x_max, y_max;
    plat tmp = NULL;
    tab_coordonnee tc;
    int min = 999, max = -999;

    if (prof == 0){
        return creer_arbre(eval(p, couleur), 0);
    }
    if (prof % 2 == 0){
        x_max = max;
        y_max = max;
        nbfils = plat_compter_quatre(p);
        tc = recup_coup_valide(p);
        a = creer_arbre(max, nbfils);
        tmp = allocution_plateau(LIGNE, COLONNE);

        for (n = 0; n < nbfils; n++){
            pltcpy(p, tmp);
            x = tc.tab[n].x;
            y = tc.tab[n].y;
            if (set_case_plateau(x, y, couleur, tmp) != 1){
                printf("Cas impossible, s'inquiéter si ce message apparait(2)\n");
            }
            tmp = retourner_jetons(tmp, x, y, couleur);
            tmp = plat_supprimer_quatre(tmp);
            tmp = liste_coup_valide(tmp, couleur);
            a->branches[n] = simuler_coup_prof_n(tmp, (couleur % 2) + 1, prof-1);
            if (max <= a->branches[n]->val){
                if (max == a->branches[n]->val){
                    if (rand() % 2){
                        max = a->branches[n]->val;
                        x_max = x;
                        y_max = y;
                    }
                }
                else{
                    max = a->branches[n]->val;
                    x_max = x;
                    y_max = y;
                }
            }
        }
        a->coord.x = x_max;
        a->coord.y = y_max;
        a->val = max;
        liberer_plateau(tmp);
        tmp = NULL;
        liberer_tab_coord(tc);
        return a;
    }
    else{
        x_min = min;
        y_min = min;
        nbfils = plat_compter_quatre(p);
        tc = recup_coup_valide(p);
        a = creer_arbre(min, nbfils);
        tmp = allocution_plateau(LIGNE, COLONNE);

        for (n = 0; n < nbfils; n++){
            pltcpy(p, tmp);
            /*afficher_mat(p);*/
            x = tc.tab[n].x;
            y = tc.tab[n].y;
            if (set_case_plateau(x, y, couleur, tmp) != 1){
                printf("Cas impossible, s'inquiéter si ce message apparait(1)\n");
            }
            tmp = retourner_jetons(tmp, x, y, couleur);
            tmp = plat_supprimer_quatre(tmp);
            tmp = liste_coup_valide(tmp, couleur);
            a->branches[n] = simuler_coup_prof_n(tmp, (couleur % 2) + 1, prof-1);
            if (min >= a->branches[n]->val){
                if (min == a->branches[n]->val){
                    if (rand() % 2){
                        min = a->branches[n]->val;
                        x_min = x;
                        y_min = y;
                    }
                }
                else{
                    min = a->branches[n]->val;
                    x_min = x;
                    y_min = y;
                }
            }
        }
        a->coord.x = x_min;
        a->coord.y = y_min;
        a->val = min;
        liberer_plateau(tmp);
        tmp = NULL;
        liberer_tab_coord(tc);
        return a;
    }
}

/*
R: Permet de jouer avec une IA de niveau étape 3
E: Un entier profondeur
S: Rien
*/

void boucle_jeu_etape_4(int prof){
  /*création et allocution du plateau*/
  plat p;
  p=allocution_plateau(LIGNE,COLONNE);
  choisir_joueur(p);/*demande au joueur la couleur qu'il veux jouer*/
  if (!taper_qui_commence()){
      if(verifier_tour_joueur(p,p->bot)){
        simuler_coup_etape_4(p, p->bot, prof); /*le bot joue*/
      } /*si le joueur commence pas, alors le bot joue*/
  }
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
        simuler_coup_etape_4(p, p->bot, prof); /*le bot joue*/
    }
    calculer_score(p);/*on calcule le score*/
  }
  fin_jeux(p);
  liberer_plateau(p);
  printf("fin de partie\n");
 
}

#endif /*_ARBRE_C_*/