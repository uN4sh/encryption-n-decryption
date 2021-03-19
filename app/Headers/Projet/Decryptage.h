#ifndef DECRYPTAGE_H
#define DECRYPTAGE_H
#include "ArbreB.h"
#include "Lecteur.h"
#include <iostream> // cout
#include <string>
#include <map>


/**
 * @file Decryptage.h
 * @brief Partie 3 : Décryptage d'un texte codé en entrée avec soit une map (tableau des symboles), soit un arbre de cryptage associé.
 *        L'analyse se fait en parcourant l'arbre selon le caractère (0 / 1) lu depuis le texte entré.
 */ 
class Decryptage
{
    private:
        std::string crypted; // Texte crypté 
        ArbreB arbre_huffman; // Arbre binaire de cryptage 
        std::map <char,std::string> encod_map; // Map des encodages
        int status; // Valeur de retour -> Faire un énumération des cas possibles et le mettre dans le status ?
        std::string decrypted; // Texte décrypté si réussi

    public:
        /**
         * @brief Constructeur de classe: constitué d'un chaine cryptée et d'une map
         */
        Decryptage(std::string, std::map <char,std::string>);
        Decryptage(std::string, ArbreB);
        ~Decryptage();

        std::string getDecrypted() { return decrypted; };

        /** 
         * @brief Renvoie la taille de chaîne maximale parmi les chaine d'encodage de caractères de la map
         */ 
        int calcul_taille_max(std::map <char,std::string>);


        /**
         * @brief Algorithme de décryptage à partir d'une map
         * 
         * Pour vérifier que le texte crypté correspond bien à la map de l'encodage : 
         *      On récupère la taille de l'encodage maximal de la map
         *      Pour chaque caractère du texte crypté, on l'ajoute à la string current et on compare à ce que contient la map
         *      Si la taille de la string current dépasse la taille maximale, c'est que les caractères cryptés n'existent pas dans cette map
         *      Ce qui veut dire que le texte n'a pas été codé avec cette map
         * 
         *      A l'inverse, si le texte est correctement retranscrit, on conclue que le texte donné pourrait avoir été codé avec cette map (ses lettres sont inclus dans celles de la map)
         */
        void decrypte_map();

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
        int decrypte_arbre();

        /**
         * @brief fonction qui affiche le résultat de la méthode précédente selon la valeur qui est retournée par cette dernière
         */
        void speakerine(int);
};

#endif // DECRYPTAGE_H