# Reversi

## Avant-propos

Jeu de Reversi en C.

## Préambule

Ce jeu a été réalisé dans un cadre universitaire, en tant que projet de programmation impérative pour la seconde année de licence en informatique à l’université Jean Monnet.

Les personnes ayant participé au projet sont :
- Adrien Defay  
- Gaultier Peyrard  
- Dorian Breuil  

## Prérequis

Pour exécuter le Makefile du projet, il est nécessaire d’installer la bibliothèque **MLV**.  
Pour plus d’informations :  
👉 [Installation de MLV](http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/installation.html)

## Répertoires principaux

- **`src/`** : Contient le code source de l’application.  
- **`fich/`** : Contient les fichiers de configuration et les scripts auxiliaires.  
- **`build/`** : Contient les fichiers objets générés lors de la compilation.  

## Modules et structure du code

Le code est organisé en plusieurs modules :

- **Main** : module principal  
- **Gamewindow** : gestion de la fenêtre de jeu  
- **Plateau** : gestion du plateau de jeu  
- **Arbre** : gestion de l’arbre de décisions  
- **Coordonnee** : gestion des coordonnées  

### Types Abstraits de Données (TAD)

#### `plat`

Contient les informations relatives au plateau de jeu :

- `mat` : tableau 2D (0 = vide, 1 = noir, 2 = blanc, 4 = jouable)  
- `l`, `c` : dimensions du plateau  
- `joueur`, `bot` : couleur respective (1 = noir, 2 = blanc)  
- `scoreb`, `scoren` : scores des Blancs et Noirs  

#### `arbre`

Représente un arbre de décisions pour l’IA :

- `val` : valeur du coup (basée sur une grille stratégique)  
- `coord` : coordonnées du coup  
- `branches` : tableau de sous-arbres (coups suivants)  
- `nb_fils` : nombre de coups enfants  

### Structures de données

#### `coordonnee`

- `x`, `y` : entiers (coordonnées)  

#### `tab_coordonnee`

- `len` : taille du tableau  
- `tab` : tableau de coordonnées  

## Fonctionnement de l’IA

### Phases 1 & 2

L’IA sélectionne une case aléatoirement parmi les coups valides. C’est la version la plus simple.

### Phase 3

Utilisation d’une **matrice d’évaluation** des positions :

```text
{  4, 2, 2, 2, 2, 2, 2, 4 },
{  2,-2,-1,-1,-1,-1,-2, 2 },
{  2,-1, 1, 1, 1, 1,-1, 2 },
{  2,-1, 1, 0, 0, 1,-1, 2 },
{  2,-1, 1, 0, 0, 1,-1, 2 },
{  2,-1, 1, 1, 1, 1,-1, 2 },
{  2,-2,-1,-1,-1,-1,-2, 2 },
{  4, 2, 2, 2, 2, 2, 2, 4 }

**Légende** :
- `4 (COIN)` : coins, prioritaires car irréversibles  
- `2 (BORD)` : bords avantageux  
- `1 (BASE)` : positions sûres  
- `0 (DEFA)` : neutres  
- `-1 (MAUV)` : risquées  
- `-2 (DANG)` : à éviter absolument  

Utilisation de `simuler_cou_prof_3()` :  
Elle simule 2 coups du joueur et 2 coups du bot. Elle retourne un arbre d’évaluation des coups possibles.  
Si plusieurs coups ont la même valeur, le choix est fait aléatoirement.

### Phase 4

Approche récursive avec `simuler_coup_prof_n()` :  
Cette fonction permet de simuler une profondeur arbitraire de coups pour l’IA.  
Elle prend en argument :
- un plateau  
- la couleur du bot  
- la profondeur de l’arbre à calculer  

## Conditions d’utilisation

Toute forme de distribution non autorisée à des fins commerciales est strictement interdite sans l’accord explicite des auteurs.
