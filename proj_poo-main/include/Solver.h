#ifndef KAKURO_SOLVEUR_SOLVER_H
#define KAKURO_SOLVEUR_SOLVER_H

// class Solver contient un class Champ
#include "Champ.h"

class Solver {
    private:
        // un boolean si la solution est trouve
        bool foundSolution = false;
        Champ champ; // champ principale
        std::vector<Champ> solutions; // champ des colustions possibles pour la grille
        
        // Les methodes de verfification
        bool isValidRow(size_t row, size_t col, int sum);     // si une rangée est valide dans la grille 
        bool isValidColumn(size_t row, size_t col, int sum);  // si une colonne est valide dans la grille
        bool isSolution();                              // si la grille actuelle est une solution

        bool isPresentInRowCol(size_t row, size_t col, const Cell& cell); // Si un nombre dans la cellule donnée est deja presentee dans la grille ou non
        
        // fonction principale de backtracking
        void backtrack(size_t row, size_t col); // fonction backtracking 
    public:
        // Contructeur
        Solver(const Champ& champ); 
        ~Solver();
        // Fonction pour lance la fonction backtracking 
        void solve(); 
        // Getter de solutions possibles
        std::vector<Champ> getSolutions() const; 
    };

#endif 