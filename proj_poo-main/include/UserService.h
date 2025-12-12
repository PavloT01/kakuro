#ifndef KAKURO_SOLVEUR_USERSERVICE_H
#define KAKURO_SOLVEUR_USERSERVICE_H

//  class UserService contient un class Champ
#include "Champ.h"


class UserService {
public:
    // Constructeur
    UserService();
    // Destructeur
    ~UserService();

    // Fonction de sortir principale
    void activerSortie();

    // La fonction demande a utilisateur de choisir le mode de chargment de la grille 
    int choisirMode();

    // La fonction affiche les fichiers disponibles dans le repertoire /data/
    // pour la meuilleure visualisation
    void afficherFichierData();

    // La fonction demande à utilisateur de saisir la grille 
    void entrerGrilleManuellement(std::vector<std::vector<std::string>>& grid);
    
    // La fonction de chargement de la grille depuis un fichier existant 
    void chargerGrilleDepuisFichier(const std::string& filename, std::vector<std::vector<std::string>>& grid);
    
    // Demande a utilisateur de choisir le mode de reception de la grille de resultat
    void obtenirResultats(Champ& champ, Champ& champD) ;

    // affiche le resultat dans le terminal
    void afficherResultatsDansTerminal(Champ& champ, Champ& champD) ;

    // sauvegarde la grille de solution dans un fichier
    void sauvegarderResultatsDansFichier(Champ& champ, Champ& champD) ;

    // exporte le resultat dans un pdf 
    void exporterResultatsEnPDF(Champ& champ, Champ& champD) ;
};

#endif // KAKURO_SOLVEUR_USERSERVICE_H