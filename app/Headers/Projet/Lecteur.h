#ifndef LECTEUR_H
#define LECTEUR_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @file Lecteur.h
 * @brief Partie 2 : Permet la lecture et le calcul des occurences de chaque lettre dans un texte et 
 *        pour un Alphabet donné.
 * 
 * @private std::string         contenu       Représente le texte en entrée sous forme de chaîne
 * @private std::vector<char>   lettres       Vector de char contenant l'ensemble des lettres d'un texte
 * @private std::vector<float>    occurences    Vector d'entiers contenant les occurrences pour chaque lettre
 */
class Lecteur
{
    private :
        std::string contenu;
        std::vector<char> lettres;
        std::vector<float> occurences;

    public :
        Lecteur(); // Constructeur par défaut
        Lecteur(Lecteur&); // Constructeur par copie
        ~Lecteur(); // Destructeur de classe

        // Getters d'attributs :
        std::vector<char> getLettres() {return lettres;};  
        std::vector<float> getOccurences() {return occurences;};
        std::string getContenu() {return contenu;};

        int get_indice(const char);
        /**
         * @brief Lecture à partir d'un fichier.
         * 
         * Lis le fichier pour le mettre dans une chaîne, puis appelle le lecteur de chaîne.
         */ 
        void lecture(std::ifstream&);

        /**
         * @brief Algorithme de lecture à partir d'une chaîne de caractère.
         * 
         * La fonction stockera l'ensemble des lettres et occurrences dans les deux vectors private de la classe.
         * Pour chacun des caractères ASCII sauf l'espace, on stocke le caractère et on compte son nombre d'occurrences dans le texte.
         */ 
        void lecture(std::string const &);

        // Surcharges des opérateurs = , << , == :
        void operator=(Lecteur&);
        friend bool operator==(Lecteur&,Lecteur&);
        friend std::ostream& operator<<(std::ostream&,Lecteur&);
};




#endif