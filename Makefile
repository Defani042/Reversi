#compilateur utilisé
CC = gcc
#Options pour la compilation.
CFLAGS = -Wall -W -std=c89 -pedantic -O2 `pkg-config --cflags MLV`
#Options d'édition des liens pour MLV.
LDFLAGS = `pkg-config --libs-only-other --libs-only-L --libs-only-l MLV`
#option pour GDB.
DEBUG_CFLAGS = -g  `pkg-config --cflags MLV`
#Options d'édition des liens pour GDB.
DEBUG_LDFLAGS =  `pkg-config --libs-only-other --libs-only-L --libs-only-l MLV`

#repertoires et Nom de l'éxécutable
BUILD_DIR = build
SRC_DIR = src
EXEC = Reversi
READ = Rendu 

# Récupère tous les fichiers .c du dossier src/
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
#emplace chaque fichier source src/nom.c par build/nom.o
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
#emplacement de chaque fichier src/nom.c par build/nom.do
DEBUG_OBJECT_FILE = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.do, $(SRC_FILES))

all: $(EXEC)

check : $(EXEC).db
	gdb $(EXEC).db

##REGLE POUR EXECUTABLE##

# Règle principale
$(EXEC): $(BUILD_DIR) $(OBJ_FILES)
	$(CC) -o $@ $(OBJ_FILES) $(LDFLAGS)

# Compilation des fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@


##REGLE POUR GDB##

#Régle principale pour GBD
$(EXEC).db: $(DEBUG_OBJECT_FILE)
	$(CC) -o $@ $(DEBUG_OBJECT_FILE) $(DEBUG_LDFLAGS) 

# Compilation des fichier objets pour GDB
$(BUILD_DIR)/%.do: $(SRC_DIR)/%.c
	$(CC) -c $(DEBUG_CFLAGS) $< -o $@

##REGLE POUR BUILD##

# Création du dossier build s'il n'existe pas
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

latex:
	pdflatex Présentation.tex
	pdflatex Présentation.tex
	rm -rf Présentation.aux Présentation.log Présentation.nav Présentation.out Présentation.snm Présentation.toc

# Nettoyage des fichiers générés
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC) $(BUILD_DIR)/*.do $(EXEC).db


