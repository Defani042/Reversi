#ifndef _PLATEAU_H_
#define _PLATEAU_H_

/*std lib*/
#include <stdio.h>
#include <stdlib.h>

/*TAD plateau*/
typedef struct{
  int**mat; /*case vide:0 case noir:1 case blanche:2*/
  int l,c;
}s_plateau;
typedef s_plateau* plat;

plat allocution_plateau(int l,int c);

void liberer_plateau(plat p);

void afficher_plateau(plat p);

void afficher_mat(plat p);

#endif /*_PLATEAU_H_*/
