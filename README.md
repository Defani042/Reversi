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

## 📁 Répertoires principaux

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

### 🧱 Types Abstraits de Données (TAD)

#### 🎲 `plat`

Contient les informations relatives au plateau de jeu :

- `mat` : tableau 2D (0 = vide, 1 = noir, 2 = blanc, 4 = jouable)  
- `l`, `c` : dimensions du plateau  
- `joueur`, `bot` : couleur respective (1 = noir, 2 = blanc)  
- `scoreb`, `scoren` : scores des Blancs et Noirs  

#### 🌳  `arbre`

Représente un arbre de décisions pour l’IA :

- `val` : valeur du coup (basée sur une grille stratégique)  
- `coord` : coordonnées du coup  
- `branches` : tableau de sous-arbres (coups suivants)  
- `nb_fils` : nombre de coups enfants  

### 🧬 Structures de données

#### 📍 `coordonnee`

- `x`, `y` : entiers (coordonnées)  

#### `tab_coordonnee`

- `len` : taille du tableau  
- `tab` : tableau de coordonnées  

## Fonctionnement de l’IA

### Phases 1 & 2

L’IA sélectionne une case aléatoirement parmi les coups valides. C’est la version la plus simple.

### Phase 3

Utilisation d’une **matrice d’évaluation** des positions :

<pre> 
      {COIN,BORD,BORD,BORD,BORD,BORD,BORD,COIN},
      {BORD,DANG,MAUV,MAUV,MAUV,MAUV,DANG,BORD},
      {BORD,MAUV,BASE,BASE,BASE,BASE,MAUV,BORD},
      {BORD,MAUV,BASE,DEFA,DEFA,BASE,MAUV,BORD},
      {BORD,MAUV,BASE,DEFA,DEFA,BASE,MAUV,BORD},
      {BORD,MAUV,BASE,BASE,BASE,BASE,MAUV,BORD},
      {BORD,DANG,MAUV,MAUV,MAUV,MAUV,DANG,BORD},
      {COIN,BORD,BORD,BORD,BORD,BORD,BORD,COIN}
</pre>

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

### Phase 5

le problémes que nous rencontrons à cette étapes est le temps de calcul nécessaire pour trouver le bon chemin on utilise l'algo minmax on parcour l'entièreter de l'abre pour palier se problémes on utilise l'algoritmhe alphabeta :

#### Algorithme Alpha-Beta – Résumé pour Reversi

#### 🎯 Objectif
L’algorithme Alpha-Beta est une version optimisée de Minimax, utilisé pour explorer les coups possibles dans un jeu comme Reversi, tout en **réduisant les calculs inutiles** grâce à des **coupes intelligentes**.


#### ⚙️ Fonctionnement général

- **Deux joueurs** :
  - MAX : cherche à maximiser son score
  - MIN : cherche à minimiser le score adverse

- **Paramètres clés** :
  - `Alpha` : meilleure valeur que MAX peut garantir jusqu’ici
  - `Beta` : meilleure valeur que MIN peut garantir jusqu’ici

- **Recherche récursive** :
  - À chaque niveau de profondeur, on explore les coups possibles.
  - On met à jour Alpha et Beta à chaque nœud.
  - Si une branche ne peut pas influencer le résultat final, elle est **coupée** (non explorée).



#### ✂️ Principe des coupes

- Si MIN trouve un coup pire que ce que MAX accepte déjà (`score ≤ alpha`), il arrête d'explorer (coupe Alpha).
- Si MAX trouve un coup meilleur que ce que MIN tolère (`score ≥ beta`), il coupe aussi (coupe Beta).


#### ✅ Avantages dans Reversi

- Évite d’explorer des coups non pertinents.
- Permet une recherche plus **profonde** dans le même temps.
- Plus efficace que Minimax simple, surtout quand l’ordre des coups est bien optimisé.


#### 📌 Utilisation

L’algorithme Alpha-Beta est particulièrement adapté à Reversi en raison du grand nombre de coups possibles à chaque tour. Il est essentiel pour une IA efficace dans ce type de jeu.

## 🚀 Amélioration

### 🌅 l'effet d'horizon ?

L'effet d'horizon survient quand l'IA, à cause de sa **profondeur de recherche limitée**, **n'anticipe pas une menace ou une opportunité majeure** située juste après la fin de sa vision. Cela peut la pousser à :
- Sous-estimer un danger à venir,
- Surestimer un coup avantageux à court terme,
- Reporter une mauvaise situation sans jamais l'éviter.

#### 🎯 Exemple dans Reversi
L’IA peut prendre un coin trop tôt car elle ne voit pas que l’adversaire pourra retourner toute une ligne **juste après** la profondeur analysée.

#### ❗ Conséquences
- Décisions stratégiques faibles ou dangereuses.
- Mauvaise gestion des coups clés en fin de partie.
- Comportement artificiellement optimiste ou pessimiste.

#### 🛠️ Pistes pour limiter cet effet

1. **Profondeur adaptative** : Augmenter la profondeur de recherche dans les situations critiques.
2. **Fonction d’évaluation plus sensible** :
   - Intégrer des indices stratégiques à long terme (mobilité, stabilité des pièces, etc.).
   - Valoriser les positions durables plutôt que les gains immédiats.


### 🧠 Réseau de neurones – Une amélioration pertinente ?

#### ✅ Pourquoi envisager un réseau de neurones ?

Un réseau de neurones peut améliorer la qualité des décisions de l’IA, notamment en :

- **Remplaçant ou renforçant la fonction d’évaluation** des positions.
- **Apprenant à partir de parties humaines ou simulées**, pour reconnaître des schémas gagnants plus complexes.
- Réduisant l’impact de l’**effet d’horizon** en anticipant des conséquences à long terme.
- Étant utilisé **en complément d’Alpha-Beta**, pour mieux évaluer les feuilles de l’arbre.

---

#### ⚠️ Limitations à prendre en compte

- **Complexité d’intégration** : Nécessite souvent des bibliothèques externes ou une liaison entre plusieur langage comme le C + Python.
- **Entraînement nécessaire** : Il faut des milliers de parties bien évaluées pour produire un réseau efficace.
- **Moins rapide** qu’une fonction classique d'évaluation, sauf si on l'optimise.

---

#### 🧩 Quand l’utiliser ?

- Pour une IA **avancée**, visant un niveau expert ou de compétition.
- Si on acceptes d’introduire une **couche logicielle supplémentaire** (ex. liaison avec Python ou C++ moderne).


Un réseau de neurones peut grandement améliorer ton IA, mais il nécessite plus de ressources, de données et de temps de développement.


## Conditions d’utilisation

Toute forme de distribution non autorisée à des fins commerciales est strictement interdite sans l’accord explicite des auteurs.
