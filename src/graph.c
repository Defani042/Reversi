#ifndef _GRAPHE_H_
#define _GRAPHE_H_

#include "graph.h"

/* Structure d'analyse globale */
analyse_t analyse;  /* La structure est maintenant non initialisée ici, mais dans la fonction d'initialisation */

/* 
R: Permet d'initialiser l'analyse des coups de jeu
E: Rien
S: Rien
*/
void initialiser_analyse() {
    int i;

    /* Initialiser tous les éléments du tableau à des valeurs par défaut */
    for (i = 0; i < MAX_COUPS; i++) {
        analyse.score_noir[i] = 0;
        analyse.score_blanc[i] = 0;
        analyse.temps_ia[i] = 0.0f;
    }

    /* Initialiser l'indice du dernier coup joué */
    analyse.coup_index = 0;
}

/* 
R: Permet d'enregistrer les données d'analyse après chaque coup joué
E: Modifie la structure analyse
S: Rien
*/
void enregistrer_analyse(int score_noir, int score_blanc, float temps_ia) {
    /* Vérification si on n'a pas dépassé le nombre maximal de coups */
    if (analyse.coup_index < MAX_COUPS) {
        analyse.score_noir[analyse.coup_index] = score_noir;
        analyse.score_blanc[analyse.coup_index] = score_blanc;
        analyse.temps_ia[analyse.coup_index] = temps_ia;
        analyse.coup_index++;  /* Incrémenter l'indice du coup */
    }
}

/* 
R: Permet d'afficher un graphique avec l'évolution des scores et du temps de réflexion de l'IA
E: Rien
S: Rien
*/
void afficher_graphique_sur_fenetre() {
    /* Déclaration des variables */
    int i;
    int width;
    int height;
    int margin;
    int graph_width;
    int graph_height;
    int max_score;
    float max_time;

    int scores_noir[MAX_COUPS];
    int scores_blanc[MAX_COUPS];
    float temps_ia[MAX_COUPS];

    MLV_Color blue;
    MLV_Color red;
    MLV_Color green;
    MLV_Color black;
    MLV_Color grey;

    char buffer[16];

    int x, x1, x2;
    int y;
    int y1_noir, y2_noir;
    int y1_blanc, y2_blanc;
    int y1_time, y2_time;

    int margin2;
    int graph_height2;
    int time_is_seconds;  /* Variable pour déterminer l'unité du temps */

    /* Initialisation des dimensions et autres paramètres */
    width = 800;
    height = 700;
    margin = 50;
    margin2 = height / 2 + 50;  /* Décalage pour abaisser le second graphique */
    
    graph_width = width - 2 * margin;
    graph_height = height / 2 - 50;
    graph_height2 = height / 2 - 70;

    max_score = 0;
    max_time = 0.0f;

    blue = MLV_COLOR_BLUE;
    red = MLV_COLOR_RED;
    green = MLV_COLOR_GREEN;
    black = MLV_COLOR_BLACK;
    grey = MLV_rgba(200, 200, 200, 255);  /* Gris clair pour les lignes de fond */

    /* Effacer la fenêtre pour afficher les nouveaux graphiques */
    MLV_clear_window(MLV_COLOR_WHITE);

    /* Récupération des valeurs des scores et du temps */
    for (i = 0; i < MAX_COUPS; i++) {
        scores_noir[i] = analyse.score_noir[i];
        scores_blanc[i] = analyse.score_blanc[i];
        temps_ia[i] = analyse.temps_ia[i];

        if (scores_noir[i] > max_score) {
            max_score = scores_noir[i];
        }
        if (scores_blanc[i] > max_score) {
            max_score = scores_blanc[i];
        }
        if (temps_ia[i] > max_time) {
            max_time = temps_ia[i];
        }
    }

    /* Si la valeur maximale du score est 0, définir la valeur maximale comme 1 pour éviter les divisions par zéro */
    if (max_score == 0) {
        max_score = 1;
    }
    /* Si la valeur maximale du temps est 0, définir la valeur maximale comme 1 pour éviter les divisions par zéro */
    if (max_time == 0.0f) {
        max_time = 1.0f;
    }

    /* Choisir l'unité du temps (seconde ou milliseconde) en fonction de la valeur maximale */
    time_is_seconds = 0;  /* 0 pour secondes, 1 pour millisecondes */

    if (max_time < 1.0f) {
        time_is_seconds = 1;  /* Si le temps est inférieur à 1 seconde, utiliser millisecondes */
    }

    /* Titre du premier graphique : Evolution du score */
    MLV_draw_text(width / 2 - 80, margin - 30, "Evolution du score", black);

    /* Grille horizontale et étiquettes Y pour le premier graphique */
    for (i = 0; i <= 10; i++) {
        y = margin + i * graph_height / 10;
        MLV_draw_line(margin, y, width - margin, y, grey);
        sprintf(buffer, "%d", max_score - (i * max_score / 10));
        MLV_draw_text(margin - 40, y - 5, buffer, black);
    }

    /* Grille verticale et étiquettes X pour le premier graphique */
    for (i = 0; i < MAX_COUPS; i++) {
        x = margin + i * graph_width / (MAX_COUPS - 1);
        MLV_draw_line(x, margin, x, margin + graph_height, grey);
        sprintf(buffer, "%d", i + 1);
        if (i % 5 == 0) {
            MLV_draw_text(x - 5, margin + graph_height + 5, buffer, black);
        }
    }

    /* Axes pour le premier graphique */
    MLV_draw_line(margin, margin, margin, margin + graph_height, black);
    MLV_draw_line(margin, margin + graph_height, width - margin, margin + graph_height, black);

    /* Tracés pour le premier graphique */
    for (i = 0; i < MAX_COUPS - 1; i++) {
        x1 = margin + i * graph_width / (MAX_COUPS - 1);
        x2 = margin + (i + 1) * graph_width / (MAX_COUPS - 1);

        y1_noir = margin + graph_height - (scores_noir[i] * graph_height / max_score);
        y2_noir = margin + graph_height - (scores_noir[i + 1] * graph_height / max_score);
        MLV_draw_line(x1, y1_noir, x2, y2_noir, blue);

        y1_blanc = margin + graph_height - (scores_blanc[i] * graph_height / max_score);
        y2_blanc = margin + graph_height - (scores_blanc[i + 1] * graph_height / max_score);
        MLV_draw_line(x1, y1_blanc, x2, y2_blanc, red);
    }

    /* Titre du deuxième graphique : Temps coup IA */
    MLV_draw_text(width / 2 - 90, margin2 - 30, "Temps coup IA", black);

    /* Grille horizontale et étiquettes Y pour le deuxième graphique (temps IA) */
    for (i = 0; i <= 10; i++) {
        y = margin2 + i * graph_height2 / 10;
        MLV_draw_line(margin, y, width - margin, y, grey);

        /* Appliquer le scaling ici pour l'affichage des valeurs sur l'axe Y */
        if (time_is_seconds) {
            sprintf(buffer, "%.2f ms", (max_time * 1000.0f) - (i * max_time * 1000.0f / 10));
        } else {
            sprintf(buffer, "%.2f s", max_time - (i * max_time / 10));  /* Afficher en secondes */
        }
        MLV_draw_text(margin - 40, y - 5, buffer, black);
    }

    /* Grille verticale et étiquettes X pour le deuxième graphique */
    for (i = 0; i < MAX_COUPS; i++) {
        x = margin + i * graph_width / (MAX_COUPS - 1);
        MLV_draw_line(x, margin2, x, margin2 + graph_height2, grey);
        sprintf(buffer, "%d", i + 1);
        if (i % 5 == 0) {
            MLV_draw_text(x - 5, margin2 + graph_height2 + 5, buffer, black);
        }
    }

    /* Axes pour le deuxième graphique */
    MLV_draw_line(margin, margin2, margin, margin2 + graph_height2, black);
    MLV_draw_line(margin, margin2 + graph_height2, width - margin, margin2 + graph_height2, black);

    /* Tracés pour le deuxième graphique (temps IA) */
    for (i = 0; i < MAX_COUPS - 1; i++) {
        x1 = margin + i * graph_width / (MAX_COUPS - 1);
        x2 = margin + (i + 1) * graph_width / (MAX_COUPS - 1);

        y1_time = margin2 + graph_height2 - (int)(temps_ia[i] * graph_height2 / max_time);  /* Pas de scaling ici */
        y2_time = margin2 + graph_height2 - (int)(temps_ia[i + 1] * graph_height2 / max_time);  /* Pas de scaling ici */
        MLV_draw_line(x1, y1_time, x2, y2_time, green);
    }

    /* Légende sous le second graphique avec les traits de couleur */
    MLV_draw_line(width / 2 - 120, height+10, width / 2 - 100, height+10, blue);  /* Trait bleu pour "Noir" */
    MLV_draw_text(width / 2 - 80, height+10, "Noir", blue);

    MLV_draw_line(width / 2 - 40, height+10, width / 2 - 20, height+10, red);  /* Trait rouge pour "Blanc" */
    MLV_draw_text(width / 2, height+10, "Blanc", red);

    MLV_draw_line(width / 2 + 40, height+10, width / 2 + 60, height+10, green);  /* Trait vert pour "Temps IA" */
    MLV_draw_text(width / 2 + 80, height+10, "Temps IA", green);

    /* Mise à jour de la fenêtre et attente avant de fermer */
    MLV_update_window();
    MLV_wait_mouse(&x,&y);
}




#endif /*_GRAPH_C_*/