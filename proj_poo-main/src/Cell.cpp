#include "Cell.h"


// Destructeur
Cell::~Cell() {}

// Contructeur
Cell::Cell(const std::string& raw) {
    if (raw == "#") { // cas si la cellule est de type case noire
        type = CellType::BLACK;
        value = 0;
        rowSum = 0;
        colSum = 0;
        editable = false;
    } // cas si la cellule est de type somme pour une colonne et une rangée
    else if (raw.find("\\") != std::string::npos && raw.find("\\") != 0 && raw.find("\\") != raw.size() - 1) {
        type = CellType::ROW_COL_SUM;
        std::string left = raw.substr(0, raw.find("\\"));
        std::string right = raw.substr(raw.find("\\") + 1);

        rowSum = std::stoi(right);
        colSum = std::stoi(left);
        value = 0;
        editable = false;
    } // cas si la cellule est de type une case de la somme pour une rangée
    else if (raw.find("\\") == 0) {
        type = CellType::ROW_SUM;
        colSum = 0;
        rowSum = std::stoi(raw.substr(1));
        value = 0;
        editable = false;
    } // cas si la cellule est de type une case de la somme pour une colonne
    else if (raw.find("\\") == raw.size() - 1) {
        type = CellType::COL_SUM;
        rowSum = 0;
        colSum = std::stoi(raw.substr(0, raw.size() - 1));
        value = 0;
        editable = false;
    } // cas si la cellule est de type NUMBER
    else if (raw != "_" && raw.find("\\") == std::string::npos) {
        type = CellType::NUMBER;
        value = std::stoi(raw);
        rowSum = 0;
        colSum = 0;
        editable = false;
    } // cas si la cellule est de type EMPTY
    else if (raw == "_"){
        type = CellType::EMPTY;
        value = 0;
        rowSum = 0;
        colSum = 0;
        editable = true;
    } // Format inconnu
    else  {
        std::cerr << "Erreur: format inconnu ou invalide pour la cellule: \"" << raw << "\". Ignoré." << std::endl;
        throw std::invalid_argument("Format inconnu pour la cellule: " + raw);
    }
}


//  retourne le type de Cell
CellType Cell::getType() const {
    return type;
}

//  retourne vrai si c'est un cellule avec les nombres sinon faux
bool Cell::isEditable() const {
    return editable;
}

// retourne valeur de cellule
int Cell::getValue() const {
    return value;
}

//  retourne la somme d'une rangée
int Cell::getRowSum() const {
    return rowSum;
}

// retourne la somme d'une colonne
int Cell::getColSum() const {
    return colSum;
}


// methode setValue modifie la valeur de cellule
void Cell::setValue(int newVal) {
    if (editable) {
        value = newVal;
    } else {
        std::cout << "Error: Attempt to modify a non-editable cell." << std::endl;
    }
}



// methode toString retourne la valeur de cellule 
std::string Cell::toString() const {
    switch (type) {
        case CellType::EMPTY:
            return "_";
        case CellType::NUMBER:
            return std::to_string(value);
        case CellType::BLACK:
            return "#";
        case CellType::ROW_SUM:
            return "\\" + std::to_string(rowSum);
        case CellType::COL_SUM:
            return std::to_string(colSum) + "\\";
        case CellType::ROW_COL_SUM:
            return std::to_string(colSum) + "\\" + std::to_string(rowSum);
        default:
            return "";
    }
}
