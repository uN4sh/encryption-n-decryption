#include "../../Headers/Projet/Decryptage.h"
using namespace std;
/**
 * @brief Constructeur de classe: constitué d'un chaine cryptée et d'une map
 */
Decryptage::Decryptage(std::string text, std::map <char,std::string> map) {
    crypted = text;
    encod_map = map;
};

/**
 * @brief Constructeur de classe: constitué d'un chaine cryptée et d'un arbre de huffman
 */
Decryptage::Decryptage(std::string text, ArbreB huffman)
{
    arbre_huffman = huffman;
    crypted = text;
};

/** 
 * @brief Renvoie la taille de chaîne maximale parmi les chaine d'encodage de caractères de la map
 */ 
int Decryptage::calcul_taille_max(std::map <char,std::string> encod_map) {
    int max = 0;
    for (std::pair<char,std::string> p : encod_map) {
        if (int(p.second.size()) > max)
            max = p.second.size();
    }
    return max;
};

/**
 * @brief Algorithme de décryptage
 * 
 * - Pour vérifier que le texte crypté correspond bien à la map de l'encodage : 
 *      On récupère la taille de l'encodage maximal de la map
 *      Pour chaque caractère du texte crypté, on l'ajoute à la string current et on compare à ce que contient la map
 *      Si la taille de la string current dépasse la taille maximale, c'est que les caractères cryptés n'existent pas dans cette map
 *      Ce qui veut dire que le texte n'a pas été codé avec cette map
 * 
 *      A l'inverse, si le texte est correctement retranscrit, on conclue que le texte donné pourrait avoir été codé avec cette map (ses lettres sont inclus dans celles de la map)
 * 
 */
void Decryptage::decrypte_map()  {
    int taille_max = calcul_taille_max(encod_map); // On calcule la taille maximale pour définir la condition d'arrêt
    std::string current; // Stocke les caractères lus dans @crypted tant qu'une lettre n'est pas reconnue
    std::string decrypted; // String résultat du décryptage
                
    // std::cout << "Taille maximale: " << taille_max << std::endl;

    // Boucle principale: Pour chaque caractère du texte crypté
    for (char c : crypted)  { 
        // Si le caractère lu ne fait pas partie des caractères non cryptés (n'est ni un 0 ni un 1, cas de l'espace par exp)
        if (c != '0' && c != '1')  { 
            decrypted.push_back(c); // On ajoute directement le caractère clair à la chaine résultat
            continue;
        }

        current.push_back(c); // On stocke le caractère dans la string current
        std::cout << "- Current: " << current << std::endl;

        // Condition d'arrêt: taille de current dépasse taille maximale de la map
        if (int(current.size()) > taille_max)  {
            std::cout << "\033[31mErreur: Le texte crypté donné n'a pas été codé par la map d'encodage donnée\033[00m" << std::endl;
            break;
        }

        // On vérifie si la string existe dans la map en la parcourant
            // Opti: Passer en unordered ou autre pour pouvoir utiliser find(std:string)
        for (std::pair<char,std::string> p : encod_map)  {
            if (current == p.second)  {
                std::cout << "Identification '" << p.second << "': " << p.first << std::endl;
                decrypted.push_back(p.first); // On ajoute le caractère clair à la chaine résultat
                current.clear(); // On vide la string current
                break; // On quitte la boucle
            }
        }
        // std::cout << "Résultat: " << decrypted << std::endl;
    }

    // On vérifie si l'exécution n'a pas étée breaked par la condition d'arrêt:
    // Si current a bien été clear, cela signifie que la lettre a été correctement écrite
    if (current.empty()) {
        std::cout << "\033[1;32mLe texte crypté aurait pu être crypté via la map donnée en paramètre, le texte décrypté est: '" << decrypted << "'\033[00m" << std::endl;
    }
    // Sinon, cela voudrait dire qu'il y a eu dépassement de taille, donc lettre non reconnue
    else  {
        std::cout << "\033[1;31mErreur lors de l'exécution de l'algorithme de décryptage\033[00m" << std::endl;
    }
};

/**
 * @brief Algorithme de décryptage avec un arbre
 *
 * - Pour vérifier que le texte crypté correspond bien à la map de l'encodage :
 *      On se place à la racine de l'arbre
 *      Pour chaque caractère qu'on lit :
 *         Si c'est un 1 on va à droite dans l'arbre et on regarde si ce sommet correspond à une lettre,
 *            si c'est le cas on l'ajoute dans la string nommée "decrypted" et on revient à la racine.
 *            Sinon on continue à lire le texte
 *         Si c'est un 0 on va à gauche et on applique le même traitement
 *         Si c'est un caractère de ponctuation (';' | ',' | ' ') on vérifie bien qu'on est à la racine et qu'il
 *            ne s'agit pas du premier caractère du texte (avec la variable marqueur qui passe de 0 à 1 dès qu'on
 *            va à gauche ou à droite ) et si c'est le cas on ajoute donc la ponctuation au texte décrypté, sinon
 *            on renvoie une valeur qui correspond à une erreur
 *      À la fin si tout a bien été retranscrit on enregistre le texte, on ne renvoie pas de valeur associée à une erreur
 *     et on conclue que le texte donné pourrait avoir été codé avec cet arbre.
 */
int Decryptage::decrypte_arbre()  {
    Sommet * current = arbre_huffman.getRacine();
    int marqueur = 0;
    for(char c: crypted)
    {
        if(c == '1')
        {
            marqueur = 1;

            if(current->filsd == NULL)
                return -1;

            current = current->filsd;
            if(current->lettre != ' ')
            {

                decrypted += current->lettre;
                current = arbre_huffman.getRacine();
            }
        }

        else if(c == '0')
        {
            marqueur = 1;

            if(current->filsg == NULL)
                return -1;

            current = current->filsg;
            if(current->lettre != ' ')
            {
                decrypted += current->lettre;
                current = arbre_huffman.getRacine();
            }
        }

        else
        {
            if (current != arbre_huffman.getRacine() || marqueur == 0)
            {
                cout << "\033[1;31mErreur lors de l'exécution de l'algorithme de décryptage\033[00m" << std::endl;
                return -1;
            }

            else if (current == arbre_huffman.getRacine() && marqueur == 1)
            {
                decrypted += c;
            }
        }
    }

    if(current != arbre_huffman.getRacine())
        return -1;

    else
    {
        Lecteur l;
        l.lecture(decrypted);
        vector<char> lettres = l.getLettres();
        vector<float> occurences = l.getOccurences();
        int taille = lettres.size();
        float comparateur = 0.0;

        for(int i = 0 ; i < taille ; i++)
        {

            comparateur = arbre_huffman.get_occ_sommet(arbre_huffman.getRacine(),lettres[i]);
            if(comparateur != occurences[i])
                 return 1;

        }
        return 2;
    }
};

/**
 * @brief fonction qui affiche le résultat de la méthode précédente selon la valeur qui est retournée par cette dernière
 */
void Decryptage::speakerine(int status)  {
    switch (status)  {
        case -1:
            // Erreur lors de l'exécution de l'algorithme de décryptage, l'arbre ne correspond donc pas au texte 
            std::cout << "\033[1;31mCe texte ne peut être décodé avec l'arbre binaire de cryptage défini.\033[0m" << std::endl;
            break;
        case 1:
            // Le texte n'a pas été codé par la partie 2, mais l'arbre fourni peut effectivement servir à décoder ce texte
            std::cout << "\033[1;33mCe texte n'a pas été encodé par l'arbre binaire de cryptage défini mais il peut tout de même servir à le décoder\n\033[00mTexte décodé : " << decrypted << std::endl;
            break;
        case 2:
            std::cout << "\033[1;36mCe texte a pu être été codé par l'arbre binaire de cryptage défini car les codes et occurences correspondent.\n\033[00mTexte décodé : " << decrypted << "\n\033[3mOn ne peut toutefois pas s'assurer que l'arbre binaire de cryptage défini a permis d'encoder ce texte.\033[00m"<< std::endl;
            break;
    }
       
};

/**
 * @brief destructeur de la classe qui se contente d'effacer et de free (automatiquement) le contenu de la map
 * d'encodage
 */
Decryptage::~Decryptage()  {
    encod_map.erase(encod_map.begin(),encod_map.end());
};
