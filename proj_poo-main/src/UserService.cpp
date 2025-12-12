#include <fstream>
#include <sstream>

#include <filesystem>

namespace fs = std::filesystem;

#include "UserService.h"

// Constructeur
UserService::UserService() {}
// Destructeur
UserService::~UserService() {}


// Fonction de sortir principale
void UserService::activerSortie() {
    std::cout << "Merci et à bientôt !\n";
    exit(EXIT_SUCCESS);
}

// La fonction demande a utilisateur de choisir le mode de chargment de la grille
// 0 - Exit.
// 1 - Manuellement.
// 2 - Depuis un fichier.
int UserService::choisirMode() {
    int choixUser;

    std::cout << "####################################################################\n";
    std::cout << "#--------Bienvenue dans le programme de solveur de jeu Kakuro------#\n";
    std::cout << "####################################################################\n";

    std::cout << "Veuillez choisir un mode de saisie de la grille :\n";
    std::cout << "0. Quitter\n";
    std::cout << "1. Saisir manuellement\n";
    std::cout << "2. Importer depuis un fichier\n";
    std::cout << ">> ";
    std::cin >> choixUser;
    
    return choixUser;
}




// Demande a utilisateur de choisir le mode de reception de la grille de resultat
void UserService::obtenirResultats(Champ& champ, Champ& champD) {
    int choixUser;
    std::cout << "Solutions trouvées !\n";
    std::cout << "Comment souhaitez-vous obtenir les résultats ?\n";
    std::cout << "0. Quitter\n";
    std::cout << "1. Affichage dans le terminal\n";
    std::cout << "2. Sauvegarde dans un fichier texte\n";
    std::cout << "3. Export en PDF\n";
    std::cout << "Exemple : > ";

    std::cin >> choixUser;

    switch (choixUser) {
        case 0:
            this->activerSortie(); 
            break;
        case 1:
            afficherResultatsDansTerminal(champ, champD);
            break;
        case 2:
            sauvegarderResultatsDansFichier(champ, champD);
            break;
        case 3:
            exporterResultatsEnPDF(champ, champD);
            break;
        default:
            std::cout << "Choix invalide. Veuillez relancer le programme.\n";
            exit(EXIT_FAILURE);
    }
}

// La fonction demande à utilisateur de saisir la grille 
void UserService::entrerGrilleManuellement(std::vector<std::vector<std::string>>& grid) {
    size_t rows, cols;
    std::cout << "Entrez le nombre de lignes : ";
    std::cin >> rows;
    std::cout << "Entrez le nombre de colonnes : ";
    std::cin >> cols;

    std::cin.ignore(); // Nettoyer le buffer

    grid.resize(rows, std::vector<std::string>(cols));

    std::cout << "\nVeuillez entrer chaque cellule (ligne par ligne) :\n";
    std::cout << "Attention : Assurez-vous que la grille saisie est **valide**.\n";
    std::cout << "Sinon, le solveur pourrait ne pas trouver de solution ou se comporter de manière inattendue.\n\n";
    std::cout << "Format:\n";
    std::cout << "  _   => case vide (editable)\n";
    std::cout << "  #   => case noire (non-editable)\n";
    std::cout << "  12\\ => 12 est la somme de colonne uniquement\n";
    std::cout << "  \\7  => 7 est somme de ligne uniquement\n";
    std::cout << "  5\\3 => 3 est somme de ligne et 5 est la somme de colonne\n";
    std::cout << "----------------------------\n";

    for (size_t i = 0; i < rows; ++i) {
        std::cout << "Ligne " << i + 1 << " (séparer par espace): ";
        for (size_t j = 0; j < cols; ++j) {
            std::cin >> grid[i][j];
        }
    }

    std::cout << "\nSaisie terminée avec succès !\n";
}

// affiche les fichiers dans le répertoire /data/
void UserService::afficherFichierData() {
    std::string fullPath = "data/";

    // verif si répertoire existe
    if (!fs::exists(fullPath) || !fs::is_directory(fullPath)) {
        std::cerr << "Erreur: le répertoire n'existe pas ou ce n'est pas un répertoire: " << fullPath << std::endl;
        exit(EXIT_FAILURE);
    }
    // boucle pour parcourir tout le répertoire
    for (const auto& entry : fs::directory_iterator(fullPath)) {
        if (fs::is_regular_file(entry)) {
            // affichage de fichier
            std::cout << entry.path().filename().string() << std::endl;  
        }
    }

}

// charge la grille depuis un fichier
void UserService::chargerGrilleDepuisFichier(const std::string& filename, std::vector<std::vector<std::string>>& grid) {
    std::string fullPath = "data/" + filename;
    std::ifstream file(fullPath);
    if (!file.is_open()) {
        std::cerr << "Erreur: impossible d’ouvrir le fichier " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Chargement de la grille depuis le fichier: " << filename << std::endl;

    grid.clear();
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::istringstream ss(line);
        std::string cell;

        while (ss >> cell) {
            row.push_back(cell);
        }

        if (!row.empty()) {
            grid.push_back(row);
        }
    }

    if (grid.empty()) {
        std::cerr << "Erreur : le fichier est vide ou mal formaté.\n";
        return;
    }

    file.close();
    std::cout << "Grille chargée avec succès ! (" << grid.size() << " lignes et "<< grid[0].size() << " colonnes)\n";
}

// affiche le resultat dans le terminal
void UserService::afficherResultatsDansTerminal(Champ& champ, Champ& champD) {
    std::cout << "Voici la grille de depart\n";
    champD.print();
    std::cout << "Voici le résultat dans le terminal:\n";
    champ.printSolution();
}

// sauvegarde la grille de solution dans un fichier
void UserService::sauvegarderResultatsDansFichier(Champ& champ, Champ& champD) {
    std::string filename;
    std::cout << "Entrez le nom du fichier de sauvegarde (ex. resultats.txt) : ";
    std::cin >> filename;
    std::string fullPath = "resultats/" + filename;
    std::ofstream file(fullPath);
    if (!file) {
        std::cerr << "Erreur: impossible d'ouvrir le fichier pour l'écriture.\n";
        return;
    }
    file << "La grille de depart" << std::endl;
    for (size_t i = 0; i < champD.getRows(); ++i) {
        for (size_t j = 0; j < champD.getCols(); ++j) {
            const Cell& cell = champD.getCell(i, j);

            if (cell.getType() == CellType::NUMBER || cell.getType() == CellType::EMPTY) {
                file << cell.toString() << " ";
            } else {
                file << cell.toString() << " ";
            }
        }
        file << "\n";
    }
    file << "La solution" << std::endl;
    for (size_t i = 0; i < champ.getRows(); ++i) {
        for (size_t j = 0; j < champ.getCols(); ++j) {
            const Cell& cell = champ.getCell(i, j);

            if (cell.getType() == CellType::NUMBER || cell.getType() == CellType::EMPTY) {
                file << cell.getValue() << " ";
            } else {
                file << cell.toString() << " ";
            }
        }
        file << "\n";
    }
    file.close();
    std::cout << "Les résultats ont été sauvegardés dans le fichier " << filename << ".\n";
}

// exporte le resultat dans un pdf 
void UserService::exporterResultatsEnPDF(Champ& champ, Champ& champD) {
    std::cout << "Export des résultats en PDF en cours...\n";
    std::ofstream vectorFile("build/output.vector");
    if (!vectorFile) {
        std::cerr << "Erreur: impossible de créer le fichier output.vector dans repositoire /build/\n";
        return;
    }
    champD.exportToVector(vectorFile, champ);

    vectorFile.close();

    // 2. Lancer vector2tex.sh
    int result1 = system("./scripts/vector2tex.sh < build/output.vector > build/output.tex");
    if (result1 != 0) {
        std::cerr << "Erreur lors de l'exécution de vector2tex.sh\n";
        return;
    }

    // 3. Compiler avec pdflatex
    int result2 = system("pdflatex -output-directory=resultats build/output.tex");
    if (result2 != 0) {
        std::cerr << "Erreur lors de la génération du PDF avec pdflatex\n";
        return;
    }



    std::cout << "PDF généré avec succès : resultats/output.pdf\n";

    // suppression de fichiers scripts
    std::remove("resultats/output.aux");
    std::remove("resultats/output.log");
}

