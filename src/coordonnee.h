#ifndef _COORDONNEE_H_
#define _COORDONNEE_H_
#include "plateau.h"

/* Les structures */
typedef struct{
    int x,y;
}coordonnee;

typedef struct{
    int len;
    coordonnee * tab;
} tab_coordonnee;

/* Les prototypes */
int plat_compter_quatre(plat p);

tab_coordonnee creer_coord(int len);

int ajout_coord(tab_coordonnee * tc, int x, int y, int i);

void liberer_tab_coord(tab_coordonnee tc);

void affiche_coord(tab_coordonnee tc);

tab_coordonnee recup_coup_valide(plat p);

#endif /*_COORDONNEE_H_*/