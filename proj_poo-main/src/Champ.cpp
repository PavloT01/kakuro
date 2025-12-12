#include "Champ.h"

// Destructeur
Champ::~Champ() {}
// Constructeur 
// initialise la grille, la taille de colonnes et de rangées 
Champ::Champ(const std::vector<std::vector<std::string>>& rawGrid) {
    if (rawGrid.empty() || rawGrid[0].empty()) {
        throw std::invalid_argument("La grille fournie est vide ou mal formée.");
    }

    rows = rawGrid.size();
    cols = rawGrid[0].size(); 

    grid.resize(rows, std::vector<Cell>(cols, Cell("_"))); 

    for (size_t i = 0; i < rows; ++i) {
        if (rawGrid[i].size() != cols) {
            throw std::invalid_argument("Toutes les lignes doivent avoir le même nombre de colonnes.");
        }
        for (size_t j = 0; j < cols; ++j) {
            grid[i][j] = Cell(rawGrid[i][j]);
        }
    }
}

// retourne nombre de rangées
size_t Champ::getRows() const {
    return rows;
}
// retourne nombre de colonnes
size_t Champ::getCols() const {
    return cols;
}
// retourne la cellule non modifiable
const Cell& Champ::getCell(size_t row, size_t col) const {
    return grid[row][col];
}
// retourne la cellule modifiable
Cell& Champ::getCell(size_t row, size_t col) {
    return grid[row][col];
}
// Vérifie si la grille est complètement remplie 
// si oui - true.
// sinon - false.
bool Champ::isFullyFilled() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell.isEditable() && cell.getValue() == 0) {
                return false;
            }
        }
    }
    return true;
}

// Affiche la grille de depart dans le terminal 
void Champ::print() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << "\t" <<  cell.toString() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}

// Affiche la grille de soulution dans le terminal
void Champ::printSolution() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if(cell.getType() == CellType::NUMBER || cell.getType() == CellType::EMPTY ) {
                std::cout << "\t" <<  cell.getValue();
            } else {
                std::cout << "\t" <<  cell.toString();
            }
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}


// Fait un export de la grille dans le flux de sortie
void Champ::exportToVector(std::ostream& out, Champ& champ) const {
    int cellSize = 50;
    
    out << 0 << ":" << cellSize << ":"
                << cellSize * (grid[0].size()) << ":" << cellSize << ":"
                << "DEP" << "\n";

    for (size_t  i = 0; i < rows; ++i) {
        for (size_t  j = 0; j < cols; ++j) {
            const Cell& c = grid[i][j];
            std::string label;
            std::string type;

            switch (c.getType()) {
                case CellType::BLACK:
                    label = "BLACK";
                    break;
                case CellType::NUMBER:
                    label = std::to_string(c.getValue());
                    break;
                case CellType::EMPTY:
                    if(c.getValue() == 0) {
                        label = "EMPTY";
                    } else {
                        label = std::to_string(c.getValue());
                    }
                    break;
                case CellType::ROW_SUM:
                    label = "ROW" + std::to_string(c.getRowSum());
                    break;
                case CellType::COL_SUM:
                    label = "COL" + std::to_string(c.getColSum());
                    break;
                case CellType::ROW_COL_SUM:
                    label = std::to_string(c.getColSum()) + "BOTH" + std::to_string(c.getRowSum());
                    break;
                default:
                    label = "?";
                    type = "UNKNOWN";
                    break;
            }

            out << j * cellSize << ":" << (i+2) * cellSize << ":"
                << cellSize << ":" << cellSize << ":"
                << label << "\n";
        }
    }
    
    out << 0 << ":" << cellSize *((grid.size() + 3)) << ":"
                << cellSize * (grid[0].size())  << ":" << cellSize << ":"
                << "SOL" << "\n";

    for (size_t  i = 0; i < champ.getRows(); ++i) {
        for (size_t  j = 0; j < champ.getCols(); ++j) {
            const Cell& c = champ.getCell(i,j);
            std::string label;
            std::string type;

            switch (c.getType()) {
                case CellType::BLACK:
                    label = "BLACK";
                    break;
                case CellType::NUMBER:
                    label = std::to_string(c.getValue());
                    break;
                case CellType::EMPTY:
                    if(c.getValue() == 0) {
                        label = "EMPTY";
                    } else {
                        label = std::to_string(c.getValue());
                    }
                    break;
                case CellType::ROW_SUM:
                    label = "ROW" + std::to_string(c.getRowSum());
                    break;
                case CellType::COL_SUM:
                    label = "COL" + std::to_string(c.getColSum());
                    break;
                case CellType::ROW_COL_SUM:
                    label = std::to_string(c.getColSum()) + "BOTH" + std::to_string(c.getRowSum());
                    break;
                default:
                    label = "?";
                    type = "UNKNOWN";
                    break;
            }

            out << j * cellSize << ":" << (i+grid.size()+3) * cellSize + cellSize << ":"
                << cellSize << ":" << cellSize << ":"
                << label << "\n";
        }
       
    }
    
}   
