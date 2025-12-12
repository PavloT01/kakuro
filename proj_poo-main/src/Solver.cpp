#include "Solver.h"
#include <iostream>

// Contructeur
Solver::Solver(const Champ& champ) : champ(champ) {}
// Destructeur
Solver::~Solver(){}

bool Solver::isPresentInRowCol(size_t row, size_t col, const Cell& cell) {

    int value = cell.getValue();
    if (value == 0) return false;

    // verification de presence d'un nombre dans la colonne plus haut que la case
    for (int i = static_cast<int>(row) - 1; i >= 0; --i) {
        const Cell& c = champ.getCell(i, col);
        if (c.getValue() == value) return true;
        if (c.getType() != CellType::EMPTY && c.getType() != CellType::NUMBER) break;
    }
    // verification de presence d'un nombre dans la colonne plus bas que la case
    for (size_t i = row + 1; i < champ.getRows(); ++i) {
        const Cell& c = champ.getCell(i, col);
        if (c.getValue() == value) return true;
        if (c.getType() != CellType::EMPTY && c.getType() != CellType::NUMBER) break;
    }

    // verification de presence d'un nombre dans la colonne plus gauche que la case
    for (int j = static_cast<int>(col) - 1; j >= 0; --j) {
        const Cell& c = champ.getCell(row, j);
        if (c.getValue() == value) return true;
        if (c.getType() != CellType::EMPTY && c.getType() != CellType::NUMBER) break;
    }
    // verification de presence d'un nombre dans la colonne plus droite que la case
     for (size_t j = col + 1; j < champ.getCols(); ++j) {
        const Cell& c = champ.getCell(row, j);
        if (c.getValue() == value) return true;
        if (c.getType() != CellType::EMPTY && c.getType() != CellType::NUMBER) break;
    }

    return false;
}

// Verif si la rangee est valide
bool Solver::isValidRow(size_t row, size_t col, int sum) {
    for(size_t j = col+1; j < champ.getCols(); j++) {
        const Cell& cell = champ.getCell(row, j);


        
        if(isPresentInRowCol(row, j, cell) && 
        ((cell.getType() == CellType::EMPTY) || 
        (cell.getType() == CellType::NUMBER))) {
            return false;
        }

        if(cell.getType() == CellType::EMPTY || cell.getType() == CellType::NUMBER) {
            sum -= cell.getValue();
        }
        

        if (cell.getType() != CellType::EMPTY && cell.getType() != CellType::NUMBER) {
            return !sum;
        }
    }
    return !sum;
}

// Verif si la colonne est valide
bool Solver::isValidColumn(size_t row, size_t col, int sum) {
    for(size_t i = row+1; i < champ.getRows(); i++) {
        const Cell& cell = champ.getCell(i, col);
        
        if(isPresentInRowCol(i, col, cell) && 
        ((cell.getType() == CellType::EMPTY) || 
        (cell.getType() == CellType::NUMBER))) {
            return false;
        }

       

        if(cell.getType() == CellType::EMPTY || cell.getType() == CellType::NUMBER) {
            sum -= cell.getValue();
        }

        if (cell.getType() != CellType::EMPTY && cell.getType() != CellType::NUMBER) {
            return !sum;
        }
    }
    return !sum;
}

// si la grille actuelle est une solution
bool Solver::isSolution(){
    if(!champ.isFullyFilled()) {
        return false; // si la grille n'est pas completement remplie 
    }
    
    for(size_t i = 0; i < champ.getRows(); i++) {
        for(size_t j = 0; j < champ.getCols(); j++) {

            const Cell& cell = champ.getCell(i, j);

            if(cell.getType() == CellType::ROW_COL_SUM) {
                if (!isValidRow(i, j, cell.getRowSum())) {
                    return false;
                }
                if (!isValidColumn(i, j, cell.getColSum())) {
                    return false;
                }
            }

            if (cell.getType() == CellType::ROW_SUM) {
                if (!isValidRow(i, j, cell.getRowSum())) {
                    return false;
                }
            }
            if (cell.getType() == CellType::COL_SUM) {
                if (!isValidColumn(i, j, cell.getColSum())) {
                    return false;
                }
            }
        }
    }
    return true;
}




// fonction backtracking
void Solver::backtrack(size_t row, size_t col) {
    
    if (row == champ.getRows()) {    
        if (isSolution()) {
            solutions.push_back(champ);  
            foundSolution = true;
        }
        return;
    }
    
    if (col == champ.getCols()) {
        backtrack(row + 1, 0); 
        return;
    }

    if (!champ.getCell(row, col).isEditable()) {
        backtrack(row, col + 1); 
        return;
    }

   
    for (int num = 1; num <= 9; num++) {
        champ.getCell(row, col).setValue(num);  
        
        
        backtrack(row, col + 1);
        
        
        if (foundSolution) return;

        champ.getCell(row, col).setValue(0); 
    }
}


// Fonction solve pour commencer le backtracking
void Solver::solve() {
    backtrack(0, 0);  // on commence a partir la premiere case de notre grille
}

std::vector<Champ> Solver::getSolutions() const {
    return solutions;  // retourne tous les solutions possibles
}
    