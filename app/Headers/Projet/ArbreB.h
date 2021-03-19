#ifndef ARBREB_H
#define ARBREB_H
#include "Sommet.h"


/**
 * @file ArbreB.h
 * @brief Partie 1 : Représente un arbre binaire étiqueté par sa racine, sa taille et sa hauteur.
 * 
 * Attributs privés: 
 * @racine      Sommet*     Racine de l'arbre binaire, permettant l'accès à tous les autres nœuds de l'arbre
 * @taille      int         Nombre de sommets que composent l'arbre binaire
 * @hauteur     int         Hauteur de l'arbre binaire
 */
class ArbreB
{
    private :
        Sommet * racine;
        int taille;
        int hauteur;
    public :
        /** 
         * Constructeurs:
         * - Paramètres par défaut
         * - Constructeur vide déclaré implicitement
         * - Constructeur par copie
         */
        ArbreB(Sommet * = NULL , int = 0);
        ArbreB(ArbreB&);

        /**
         *  Destructeur de classe 
         * */
        ~ArbreB();

        /**
         *  Getters et setters des attributs privés (déclarés inline) pour assurer l'encapsulation 
         * */
        Sommet * getRacine() { return racine; }; // Renvoie un pointeur car utilisée récursivement
        int getTaille() { return taille; };
        int getHauteur() { return hauteur; };

        /**
         *  Parcours récursivement l'arbre en cherchant la feuille la plus éloignée de la racine 
         * */
        int calcule_hauteur(Sommet *);

        /**
         *  Méthode ajout surchargée pour ajouter un élément de plusieurs manières 
         * */
        void ajout(Sommet *,Sommet*);
        void ajout(Sommet *,const char,const float);
        void ajout(ArbreB&);

        /**
         *  Affiche l'arbre de gauche à droite sur le terminal 
         * */
        void print_tree(Sommet *root, char *indent, int last);

        /**
         *  Libère la mémoire allouée dynamiquement à un arbre binaire et ses sommets 
         * */
        void free_tree(Sommet *);

        /**
         *  Recherche un sommet de l'arbre par une @lettre ou une @freq 
        */
        int recherche_sommet(Sommet*, const char, std::string&, int);

         /**
          *  Recherche un sommet de l'arbre par une @lettre et renvoie son occurence si elle la trouve, sinon
          elle renvoie -1
         */
        float get_occ_sommet(Sommet *sommet,const char lettre);

        /**
         *  Fusionne deux arbre binaires 
         * */
        void fusion_arbre(ArbreB&, ArbreB&);

        /**
         *  Supprime un sommet de l'arbre 
         * */
        void supprimer_sommet(Sommet *, const char);

        /**
         *  Décompose l'arbre binaire en sa partie gauche et droite 
         * */
        void decomposition(ArbreB&, ArbreB&);

        /**
         *  Redéfinition (surcharge) des opérateurs <<, += et = 
         * */
        friend std::ostream& operator<<(std::ostream&,ArbreB&);
        void operator+=(ArbreB&);
        void operator=(ArbreB&);
};


#endif // ARBREB_H