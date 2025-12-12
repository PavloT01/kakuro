#ifndef KAKURO_SOLVEUR_CHAMP_H
#define KAKURO_SOLVEUR_CHAMP_H

// class Champ contient un class Cell
#include <iomanip>
#include "Cell.h"

class Champ {
private:
    // une grille de cellules 
    std::vector<std::vector<Cell>> grid;
    size_t  rows; // Nombre de rangées dans grille
    size_t  cols; // Nombre de colonnes dans grille
public:
    // Constructeur
    Champ(const std::vector<std::vector<std::string>>& rawGrid);
    // Destructeur
    ~Champ();
    
    // Getters
    size_t getRows() const;   // Retourne le nombre de rangées
    size_t getCols() const;   // Retourne le nombre de colonnes
    // 2 types : 
    // 1er - un retour sans possibilité de modifier la cellule
    // 2ème - avec la possibilité de modifier la cellule
    const Cell& getCell(size_t row, size_t col) const; // sans modification
    Cell& getCell(size_t row, size_t col);             // avec modification

    // Vérification de la complétion
    bool isFullyFilled() const;  // Vérifie si la grille est complètement remplie 
    
    // Méthodes d'affichage
    void print() const;         // Affiche la grille de depart
    void printSolution() const; // Affiche la solution de la grille
    
    // Exportation
    void exportToVector(std::ostream& out, Champ& champ) const;   // Exporte la grille dans le flux de sortie
};

#endif 