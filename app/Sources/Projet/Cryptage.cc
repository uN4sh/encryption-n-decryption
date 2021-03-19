#include "../../Headers/Projet/Cryptage.h"

using namespace std;


/**
    *La classe cryptage ne nécessite réellement que le résultat de l'analyse d'un texte, tout les autres attributs
     sont mis à jour à l'issue de différentes méthodes
*/
Cryptage::Cryptage(Lecteur& l) {
    lecteur = l;
};

/**
    *Le destructeur détruit les éléments que le vecteur et la map contiennent
*/
Cryptage::~Cryptage() {
    arbres_restants.erase(arbres_restants.begin(),arbres_restants.end());
    encod_map.erase ( encod_map.begin(), encod_map.end() );
}; 

/**
   *Échange de deux cases de sommets dans un tableau utile au tri du vecteur de sommet
*/
void swap(Sommet* tab, int i, int j) {
    Sommet S1 = tab[i];
    tab[i] = tab[j];
    tab[j] = S1;
}

/**
    *Version optimisée du tri à bulles des sommets afin d'éviter de chercher les deux sommets de plus petites fréquences
    à chaque fois
*/
void bubbleSort(std::vector<Sommet> *vect, int n) {
    Sommet *tmp_tab = new Sommet[vect->size()];
    int i = 0;
    for (Sommet s : *vect) {
        tmp_tab[i] = vect->back(); vect->pop_back();
        i++;
    }

    int j;
    bool swapped;
    for (i = 0; i < n-1; i++)
    {
        swapped = false;
        for (j = 0; j < n-i-1; j++)
        {
            if (tmp_tab[j].getFreq() > tmp_tab[j+1].getFreq())
            {
                swap(tmp_tab, j, j+1);
                swapped = true;
            }
        }

        // IF no two elements were swapped by inner loop, then break
        if (swapped == false)
            break;
    }

    for(i = n-1; i >= 0; i--)
        vect->push_back(tmp_tab[i]);

    delete[] tmp_tab;
}

/**
 * @brief Algorithme de cryptage: création de l'arbre de Huffman à partir d'un vecteur de lettres et occurrences.
 *
 * Initialement: On créé un arbre (Sommet) étiqueté par l'occurrence de chacune des lettres du `lecteur`
 * Le vecteur `arbres_restants` gère le nombre d'arbres restants lors de l'exécution de l'algorithme
 *
 * Condition d'arrêt de la boucle: Tant qu'il reste plus d'un arbre dans le vecteur arbres_restants
 * 1. On tri le vecteur de sorte à considérer A1 et A2 les deux arbres portant les étiquettes e1 et e2 les plus faibles
 * 2. Création de l'arbre A (Sommet `newSomm`) étiqueté e1 + e2 et attribution de ses fils A1 et A2
 */
void Cryptage::construction_arbre() {
    // Les deux std::vector sont à passer idéalement en Map
    vector<float> tmp2 = lecteur.getOccurences(); // Vector des occurences
    vector<char> tmp1 = lecteur.getLettres(); // Vector des lettres

    // Initialement, on créé un Sommet pour chacune des lettre présente dans le texte
    for(size_t i = 0 ; i < tmp1.size() ; i++) {

       Sommet * tmp = new Sommet(tmp1[i], tmp2[i], 1);
       arbres_restants.push_back(*tmp);
       delete tmp;

    }

    // On trie les arbres restants par occurence à l'aide d'un Tri Fusion
    vector<Sommet> * combinaisons = new vector<Sommet>;
    *combinaisons = arbres_restants;
    bubbleSort(combinaisons, combinaisons->size());

    Sommet *A1, *A2; // Deux sommets qui stockeront les sommets de plus petites fréquences
    Sommet *newSomm; // Nouveau sommet créé, racine de A1 et A2

    // Condition d'arrêt: Tant qu'il y a plus d'un arbre dans le vecteur de gestion des arbres restants
    while(combinaisons->size() > 1) {
        // On considère les deux sommets ayant l'occurence la plus faible
        A1 = new Sommet (combinaisons->back());  combinaisons->pop_back();
        A2 = new Sommet (combinaisons->back());  combinaisons->pop_back();

        // Création de l'arbre A (Sommet newSomm) étiqueté e1 + e2
        newSomm = new Sommet(' ', A1->getFreq() + A2->getFreq(), 1);

        // Le nouvel arbre a pour fils les racines de A1 et A2
        newSomm->setFilsD(A2);
        newSomm->setFilsG(A1);

        // On place le nouvel arbre dans la liste des sommets courants (La surcharde de l'opérateur = copie aussi les fils)
        combinaisons->push_back(*newSomm);

        delete newSomm; // Suppression de l'arbre A maintenant stocké dans la liste des sommets restants
        bubbleSort(combinaisons, combinaisons->size()); // On re-trie la liste des sommets restants
    }

    // À la fin de cette boucle, le vecteur de gestion des arbres restants contient l'abre de cryptage final
    if (combinaisons->size() != 1) {
        std::cout << "Erreur lors de la création de l'arbre de cryptage" << std::endl;
        return;
    }

    // On ajoute maintenant ce Sommet à l'Arbre de la classe Cryptage
    arbre_huffman.ajout(arbre_huffman.getRacine(), &combinaisons->back());

    // delete[] combinaisons; // Ça free mais Seg-fault
    // combinaisons->erase(combinaisons->begin(),combinaisons->end()); // Ça free pas ET seg-fault
};

/**
 * @brief Algorithme d'encodage: Encode chacune des lettres du texte en entrée suivant l'algorithme de Huffman.
 * 
 * Le résultat de l'encodage est stocké dans `std::map<char, std::string>` associant chaque lettre à son encodage.
 * 
 * - Pour chaque noeud de l'arbre, l’arête vers son fils gauche est étiquetée 0 et celle vers son fils droit 1.
 * - Le code associé à une lettre est le mot binaire composé des étiquettes sur les arêtes entre la racine de 
 *   l’arbre final et la feuille étiquetée avec cette lettre.
 * 
 * @return std::string     Chaîne de caractère du résultat de l'encodage mis bout à bout.
 */
string Cryptage::encodage() {
    int taille = arbres_restants.size();

    for(int i = 0 ; i < taille; i++) {
        // On insère les pairs <Lettre, ""> dans la map des résultats
        encod_map.insert(std::make_pair(arbres_restants[i].getLettre(), ""));

        // Chaque lettre est encodé par la fonction create_code, la string est sauvegardé dans la map
        arbre_huffman.recherche_sommet(arbre_huffman.getRacine(), arbres_restants[i].getLettre(), encod_map[arbres_restants[i].getLettre()], 0);
    }

    // Affichage des résultats un à un
    cout << "\n\033[1;37m> Résultat de l'encodage: \033[00m";
    for(std::pair<char, string> p : encod_map)
        cout <<p.first << ": " << p.second<<" | ";
    cout<<endl;

    string contenunew ;
    int ascii;
    char c;
    for(size_t i = 0 ; i < lecteur.getContenu().size() ; i++)
    {
        c = lecteur.getContenu()[i];
        ascii = int(c);
        if(ascii >= 65 && ascii <= 90)
            c = (char) (ascii+32);
        
        // Si la lettre est dans la map, on ajoute son encodage à la chaîne
        if (encod_map.find(c) != encod_map.end()) 
            contenunew += encod_map[c];

        else // Sinon, on ajoute le caractère
            contenunew += c;
    }

    cout<<"\n\033[1;37m> Texte codé: \033[00m"<<contenunew<<endl;
    return contenunew;
}

