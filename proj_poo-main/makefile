# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O3 -Iinclude


# Repertoires
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
RESULTATS_DIR = resultats
SCRIPT_DIR = scripts


SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
TARGET = $(BIN_DIR)/main

# Fichiers d'export
TEX_FILE = $(RESULTATS_DIR)/output.tex
PDF_FILE = $(RESULTATS_DIR)/output.pdf


all: $(TARGET)

# Compilation binaire
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation des fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dossiers nécessaires
$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

# Génération du PDF (commande personnalisée)
pdf: $(PDF_FILE)

# Exécution avec valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET)

$(PDF_FILE): $(VECTOR_FILE) | $(OUTPUT_DIR)
	@echo "[*] Génération de output.tex depuis output.vector..."
	./$(SCRIPT_DIR)/vector2tex.sh < $(VECTOR_FILE) > $(TEX_FILE)
	@echo "[*] Compilation LaTeX vers PDF..."
	pdflatex -output-directory=$(OUTPUT_DIR) $(TEX_FILE) > /dev/null



# make chmod pour donner les droits de creation d'autres au fichier vector2tex.sh
chmod:
	chmod 777 $(SCRIPT_DIR)/vector2tex.sh
	@echo "[*] Droits d'exécution accordés: $(SCRIPT_DIR)/vector2tex.sh"

# make latex pour installer latex si cest pas le cas alors on peut le sauter
latex:
	sudo apt-get update
	sudo apt-get install -y texlive-full texstudio
	@echo "[*] LaTeX installé."	


# Nettoyage
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) *.o *.aux *.log
	rm -f $(RESULTATS_DIR)/output.tex 

rebuild: clean all
