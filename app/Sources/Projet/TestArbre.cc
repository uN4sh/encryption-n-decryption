#include "../../Headers/Projet/ArbreB.h"
#include "../../Headers/Projet/Lecteur.h"
#include "../../Headers/Projet/Cryptage.h"
#include "../../Headers/Projet/Decryptage.h"
using namespace std;
/**
 * @file TestArbre.cc
 * @brief Partie 3 : Constitue la fonction main lors de l'exécution sans interface graphique pour le Cryptage et le Decryptage.
 * Construit l'arbre de cryptage du texte lu depuis le fichier text.txt puis l'encode selon l'algorithme de Huffman. 
 * Trois exemples de décryptages sont ensuite effectués pour tester la méthode.
 */
int main(int argc, char* argv[]) {
    std::cout << "\033[1;33mProjet LA - Cryptage et décryptage | Samy BOUMALI & Amine ATEK\033[0m - Exécution CLI\n" << std::endl;

    // Ouverture, lecture et calcul des occurrences des lettres pour le texte donné en entrée
    Lecteur l;
    std::ifstream mytext("app/text.txt");
    l.lecture(mytext);

    // Affichage du texte
    std::cout << "\033[1;37m> Texte à coder: \033[0m" << l.getContenu() << std::endl;
    Cryptage cr(l);

    // Construction et affichage de l'arbre binaire de cryptage
    cr.construction_arbre();
    std::cout << "\n\033[1;37mArbre binaire de cryptage:\033[0m\n" << cr.get_arbre() << std::endl;

    // Encodage et affichage du texte après exécution de l'algorithme de Huffman
    std::string crypted = cr.encodage();

    // Décryptage d'un mauvais texte
    std::cout << "\n\033[1;37m> Essai de décryptage du texte : '00011'\033[0m (Symboles non contenus dans l'arbre)" << std::endl;
    Decryptage dr1("00011", cr.get_arbre());
    dr1.speakerine(dr1.decrypte_arbre());

    // Décryptage d'un bon texte avec mauvaises occurrences
    std::cout << "\n\033[1;37m> Essai de décryptage du texte : '000111110'\033[0m (Symboles contenus dans l'arbre mais avec occurrences différentes)" << std::endl;
    Decryptage dr2("000111110", cr.get_arbre());
    dr2.speakerine(dr2.decrypte_arbre());

    // Décryptage du bon texte
    std::cout << "\n\033[1;37m> Essai de décryptage du texte : '101111100100 110101110100'\033[0m (Bon texte crypté initialement par l'arbre)" << std::endl;
    Decryptage dr(crypted, cr.get_arbre());
    dr.speakerine(dr.decrypte_arbre());

}
