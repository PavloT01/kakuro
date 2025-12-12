#include "Solver.h"
#include "UserService.h"



int main()
{

    UserService userService;
    std::vector<std::vector<std::string>> grid;
    
    // Demande a utilisateur le mode de chargement de la grille
    int mode = userService.choisirMode();
    switch (mode) {
        case 0:
            userService.activerSortie();
            break;
        case 1:
            userService.entrerGrilleManuellement(grid);
            break;
        case 2: {
            std::string filename;
            
            std::cout << "Les fichiers disponibles dans /data/ sont : " << std::endl;
    
            userService.afficherFichierData();
            std::cout << "Entrez le nom du fichier : ";
            std::cin >> filename;
            userService.chargerGrilleDepuisFichier(filename, grid);
            break;
        }
        default:
            std::cout << "Choix invalide. Veuillez relancer le programme.\n";
            return EXIT_FAILURE;
    }

    std::cout << "La grille est : \n";
    Champ champ(grid);
    champ.print();
    std::cout << "Nous recherchons une solution pour cette grille, veuillez patienter...\n";
    
    // Cherche une solution
    Solver solver(champ);
    solver.solve();
    std::vector<Champ> solutions = solver.getSolutions();
    if(solutions.size() == 0) {
        std::cout << "Desole la solution n'a pas été trouve\n";
        return EXIT_FAILURE;
    }
    
    
    userService.obtenirResultats(solutions[0], champ);


    std::cout << "Merci beaucoup et à bientôt !" << std::endl;
    return EXIT_SUCCESS;
}
