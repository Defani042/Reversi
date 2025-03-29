#compilateur utilisé
CC = gcc
#Options pour la compilation
CFLAGS = -Wall -W -std=c89 -pedantic -O2 `pkg-config --cflags MLV`
#Options d'édition des liens pour MLV.
LDFLAGS = `pkg-config --libs-only-other --libs-only-L --libs-only-l MLV`

#repertoires et Nom de l'éxécutable
BUILD_DIR = build
SRC_DIR = src
EXEC = Reversi

# Récupère tous les fichiers .c du dossier src/
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
#emplace chaque fichier source src/nom.c par build/nom.o
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))


all: $(EXEC)
# Règle principale
$(EXEC): $(BUILD_DIR) $(OBJ_FILES)
	$(CC) -o $@ $(OBJ_FILES) $(LDFLAGS)

# Compilation des fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

# Création du dossier build s'il n'existe pas
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Nettoyage des fichiers générés
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)


