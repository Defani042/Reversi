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
R : Afficher récursivement les nœuds d’un arbre (valeur, coordonnées, nombre de fils).
E : 1 TAD arbre (racine de l’arbre).
S : Aucun (affichage sur la sortie standard).
*/
void afficher_arbre(arbre a) {
    /** Variable statique pour suivre la profondeur sans argument externe */
    static int niveau = 0;
    int i, j;

    /** Vérifie si le nœud est vide */
    if (a == NULL) {
        for (j = 0; j < niveau; j++) {
            printf("│   ");
        }
        printf("└── (NULL)\n");
        return;
    }

    /** Affiche l’indentation selon la profondeur actuelle */
    for (j = 0; j < niveau; j++) {
        printf("│   ");
    }

    /** Affiche les infos du nœud courant */
    printf("└── Val: %d | Coord: (%d, %d) | Fils: %d\n",
           a->val, a->coord.x, a->coord.y, a->nb_fils);

    /** Incrémente le niveau pour les fils */
    niveau++;

    /** Appelle récursivement l’affichage sur chaque fils */
    for (i = 0; i < a->nb_fils; i++) {
        afficher_arbre(a->branches[i]);
    }

    /** Décrémente le niveau après avoir fini les fils */
    niveau--;
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
/*
R: Fonction d'évaluation de la position (le score ou la qualité d'une position)
E: 1 TAD arbre (node)
S: Renvoie un entier qui représente l'évaluation de la position dans l'arbre
*/
int evaluation_position(arbre node) {
    return node->val; /* Renvoie la valeur d'évaluation de la position */
}

/*
R: Trier les branches d'un arbre par ordre décroissant de valeur
E: Un arbre `a` à trier, où chaque branche a une valeur dans le champ `val`
S: Les branches de l'arbre sont triées par valeur, de la plus grande à la plus petite
*/

void trier_branches_par_val(arbre a) {
    int i,j;
    if (a == NULL || a->nb_fils <= 1) return;
    /*tri par valeur décroissante*/
    for (i = 0; i < a->nb_fils - 1; i++) {
        for (j = i + 1; j < a->nb_fils; j++) {
            if (a->branches[j]->val > a->branches[i]->val) {
                /* Échange des pointeurs*/
                arbre temp = a->branches[i];
                a->branches[i] = a->branches[j];
                a->branches[j] = temp;
            }
        }
    }
}

/*
R: Réduire le nombre de branches d’un arbre à un maximum de k
E: un arbre a à réduire, un entier k
S: un pointeur vers l’arbre réduit (a), avec au plus k branches conservées
*/

arbre reduire_branches_top_k(arbre a, int k) {
    int i;

    /* Vérifie que l'arbre est non nul */
    if (a == NULL) {
        return NULL;
    }

    /* Si le nombre de fils est inférieur ou égal à k, rien à faire */
    if (a->nb_fils <= k) {
        return a;
    }

    /* Libère les fils au-delà des k premiers */
    for (i = k; i < a->nb_fils; i++) {
        liberer_arbre(a->branches[i]);
    }

    /* Met à jour le nombre de fils */
    a->nb_fils = k;

    return a;
}

/*
R: Préparer un nœud d’arbre pour Alpha-Beta en triant ses branches par valeur décroissante
   et en ne gardant que les k meilleures branches.
E: un arbre a à préparer, un entier top_k représentant le nombre maximum de branches à conserver
S: vide (modifie l’arbre a directement)
*/

void preparer_noeud(arbre a, int top_k) {
    /* Vérifie que l’arbre est non nul et qu’il possède des branches */
    if (a != NULL && a->nb_fils > 0) {
      
        /* Trie les branches par ordre décroissant de valeur (les meilleurs coups d'abord) */
        trier_branches_par_val(a);

        /* Réduit les branches à un maximum de top_k */
        reduire_branches_top_k(a, top_k);
    }
}

/*
R: Algorithme Alpha-Beta pour explorer l'arbre des coups
E: 
    - 1 TAD arbre (node)
    - un entier profondeur (profondeur maximale de recherche)
    - deux entiers alpha et beta (les bornes de l'algorithme alpha-bêta)
    - un entier maximisateur (1 si c'est le tour du joueur, 0 si c'est celui de l'adversaire)
    - 1 pointeur cut pour savoir si un élagage a eu lieu
S: Renvoie un entier représentant la meilleure évaluation d'une position à partir de l'arbre donné
*/
int alphabeta(arbre node, int profondeur, int alpha, int beta, int maximisateur, int *cut) {
    int val;
    int i;
    
    /* Cas de base : Si on atteint une profondeur maximale ou une feuille */
    if (profondeur == 0 || node->nb_fils == 0) {
        return evaluation_position(node); /* Retourne l'évaluation de la position actuelle */
    }
    /* Préparer l'arbre en triant les branches et en réduisant leur nombre à top_k (par exemple, top_k = 5) dans notre cas*/
    preparer_noeud(node, 5);
    
    if (maximisateur) { /* Maximisation pour le joueur actuel */
        int max_val = INT_MIN;
        
        for (i = 0; i < node->nb_fils; i++) {
            val = alphabeta(node->branches[i], profondeur - 1, alpha, beta, 0, cut);
            /* Mise à jour de max_val avec une instruction if */
            if (val > max_val) {
                max_val = val;
            }
            if (alpha > max_val) {
                alpha = max_val;
            }
            
            /* Si l'élagage Alpha est supérieur ou égal à Beta, arrêter l'exploration */
            if (alpha >= beta) {
                *cut = 1; /* Indique qu'un élagage a eu lieu */
            }
        }
        return max_val;
    } else { /* Minimisation pour l'adversaire */
        int min_val = INT_MAX;
        
        for (i = 0; i < node->nb_fils; i++) {
            val = alphabeta(node->branches[i], profondeur - 1, alpha, beta, 1, cut);
            /* Mise à jour de min_val avec une instruction if */
            if (val < min_val) {
                min_val = val;
            }
            if (beta < min_val) {
                beta = min_val;
            }
            
            /* Si l'élagage Beta est inférieur ou égal à Alpha, arrêter l'exploration */
            if (alpha >= beta) {
                *cut = 1; /* Indique qu'un élagage a eu lieu */
            }
        }
        return min_val;
    }
}

/*
R: Trouve le meilleur coup à jouer à partir de l'arbre donné en utilisant l'algorithme Alpha-Beta
E: 
    - 1 TAD arbre (racine) qui représente l'état actuel du jeu
    - un entier profondeur qui détermine jusqu'à quelle profondeur effectuer la recherche
S: Renvoie la coordonnée du meilleur coup à jouer
*/
coordonnee meilleur_coup(arbre racine, int profondeur) {
    int max_val;
    coordonnee meilleur_coup_coord;
    int cut;
    int i;
    int val;
    
    max_val = INT_MIN;
    cut = 0; /* Variable pour suivre si un élagage a eu lieu */
    
    /* Parcours des branches pour trouver le meilleur coup */
    for (i = 0; i < racine->nb_fils; i++) {
        cut = 0; /* Réinitialiser la condition d'élagage */
        val = alphabeta(racine->branches[i], profondeur - 1, INT_MIN, INT_MAX, 0, &cut);
        
        /* Ne choisir que les coups non élagués avec une instruction if */
        if (cut == 0) {
            if (val > max_val) {
                max_val = val;
                meilleur_coup_coord = racine->branches[i]->coord;
            }
        }
    }
    
    return meilleur_coup_coord; /* Retourne la meilleure coordonnée */
}

/*
R: Renvoit l'arbre dont tous les plateaux ont été évalués.
E: 1 TAD plat, la couleur et la profondeur
S: L'arbre de jeu
*/

arbre evaluation_arbre(plat p, int couleur, int prof){
    arbre a;
    int nbfils;
    int x,y,n;
    plat tmp = NULL;
    tab_coordonnee tc;

    /* Cas d'arrêt. Si prof == 0, alors on renvoit une feuille évaluée*/
    if (prof == 0){
        return creer_arbre(eval(p, couleur), 0);
    }

    /*On récupère le nombre de coups valides*/
    nbfils = plat_compter_quatre(p);

    /*On récupère les coordonnées des coups valides*/
    tc = recup_coup_valide(p);

    /*On crée un arbre en évaluant le plateau*/
    a = creer_arbre(eval(p,couleur), nbfils);

    /*On alloue un plateau temporaire*/
    tmp = allocution_plateau(LIGNE, COLONNE);

    /*Pour chaque fils, on simule un coup jouer*/
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

        /*Le nieme fils est simulé via la fonction récursive*/
        a->branches[n] = simuler_coup_prof_n(tmp, (couleur % 2) + 1, prof - 1);
        a->branches[n]->coord.x = x;
        a->branches[n]->coord.y = y;
    }

    liberer_plateau(tmp);
    tmp = NULL;
    liberer_tab_coord(tc);

    /*On revoit l'arbre évalué*/
    return a;
}

/*
R: Joue le prochain coup en utilisant l'algorithme alpha beta
E: 1 TAD plat et la profondeur
S: Rien
*/
void simuler_coup_etape_5(int prof,plat p){
    coordonnee c;
    arbre a;
    int res;
     
    /*creation de l'abre + remplissage et recuperation des meilleure coordonnees*/
    a = creer_arbre_vide();
    a = evaluation_arbre(p,p->bot,prof);
    /* afficher_arbre(a);*/
    c = meilleur_coup(a,prof);
    /*on joue la coordonnee en cas d'érreur la fonction renvoie -1 -1 en coordonnee */
    
    /* printf("coup jouer par le bot [%d,%d]\n",c.x,c.y);*/
    res = set_case_plateau(c.x,c.y,p->bot,p);
    if(!res){
        printf("erreur coup jouer impossible [%d,%d]\n",c.x,c.y);
        printf("arret du jeux\n");
        exit(EXIT_FAILURE);
    }
    /*on retourne les pions*/
    p = retourner_jetons(p,c.x,c.y,p->bot);

}

/*
R: Permet de jouer avec une IA de niveau étape 3 utilisant alphabeta pour parcourir ces possibilitées
E: Un entier profondeur
S: Rien
*/

void boucle_jeu_etape_5(int prof){
  /*création et allocution du plateau*/
  plat p;
  p=allocution_plateau(LIGNE,COLONNE);
  choisir_joueur(p);/*demande au joueur la couleur qu'il veux jouer*/
  if (!taper_qui_commence()){
      if(verifier_tour_joueur(p,p->bot)){
        simuler_coup_etape_5(prof,p); /*le bot joue*/
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
        simuler_coup_etape_5(prof, p); /*le bot joue*/
    }
    calculer_score(p);/*on calcule le score*/
  }
  fin_jeux(p);
  liberer_plateau(p);
  printf("fin de partie\n");
 
}

#endif /*_ARBRE_C_*/