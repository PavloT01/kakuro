#ifndef KAKURO_SOLVEUR_CELL_H
#define KAKURO_SOLVEUR_CELL_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

/* ----------  enum class CellType  ----------

Un type énuméré sécurisé pour une case. 

EMPTY - une simple case vide.
NUMBER - une case contenant un nombre au départ, qui a priori est déjà
bien positionné et de bonne valeur.
BLACK - une case noire.
ROW_SUM - une case contenant la somme d'une rangée
(s'écrit \x) où x est un nombre quelconque. 

COL_SUM - une case contenant la somme d'une colonne
(s'écrit x\) où x est un nombre quelconque.

ROW_COL_SUM - une case contenant la somme d'une colonne et d'une rangée
en même temps (s'écrit x\y), où x(colonne) et y(rangée) sont des nombres quelconques.

*/ 

enum class CellType {
    EMPTY,      // 0
    NUMBER,     // 1
    BLACK,      // 2
    ROW_SUM,    // 3
    COL_SUM,    // 4
    ROW_COL_SUM // 5 
};



/* ----------  class Cell  ----------

La classe Cell contient 
les variables suivantes :

1) CellType type - pour définir le type de cellule precedement défini,
afin d’attribuer un nom à chaque type de cellule présent ici.
Chaque type possède une valeur (de 0 à 5).

2) int value - la valeur contenue la cellule de la grille.
Les cellules avec de types  EMPTY, BLACK,  ROW_SUM, COL_SUM, ROW_COL_SUM 
contiennent  la valeur 0.
La cellule de type NUMBER contient la valeur donnée dans la grille. 

3) int rowSum - la somme d'une rangée.
Seules les cellules de types ROW_SUM, ROW_COL_SUM contiennent 
les valeurs données  dans la grille.
Les autres cellules  contiennent  la valeur par defaut 0.

4) int colSum - la somme d'une colonne.
Seules les cellules de types COL_SUM et ROW_COL_SUM contiennent 
les valeurs données  dans la grille.
Les autres cellules  contiennent  la valeur par defaut 0.

5) bool editable - indique si la valeur de la cellule peut être modifiée ou non.
Seules les cellules de type EMPTY peut être modifiées; les autres non.


*/
class Cell {
    private :
        CellType type;   // le type de cellule précédemment défini
        int value;       // valeur si le type est NUMBER ou EMPTY
        int rowSum;      // somme si le type est ROW_SUM ou ROW_COL_SUM
        int colSum;      // somme si le type est COL_SUM ou ROW_COL_SUM
        bool editable;   // indique si la cellule est modifiable ou non

        
    public :
        // Constructeur
        Cell(const std::string& raw);
        // Destructeur
        ~Cell();
        // Getters
        int getValue() const;           // retourne la valeur de la cellule
        int getRowSum() const;          // retourne la somme pour une colonne de la cellule
        int getColSum() const;          // retourne la somme pour une rangée de la cellule
        CellType getType() const;       // retourne le type de la cellule
        bool isEditable() const;        // indique si la cellule est modifiable (true) ou non (false)
        // Setter
        void setValue(int newVal);      // met à jour la valeur de la cellule
        // Méthode pour afficher la cellule sous forme de chaîne
        std::string toString() const;   // retourne une chaîne de caractères représentant la cellule
};

#endif // Cell.h