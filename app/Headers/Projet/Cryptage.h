#ifndef CRYPTAGE_H
#define CRYPTAGE_H
#include "Lecteur.h"
#include "ArbreB.h"
#include "Sommet.h"
#include <string>
#include <map>
#include <utility>

/**
 * @file Cryptage.h
 * @brief Partie 2 : Création de l'arbre de Huffman et encodage du texte en entrée lu par le Lecteur.
 * 
 * Cette classe constitue le corps de la Partie 2 du projet, une fois le texte lu par le Lecteur, 
 * l'algorithme de cryptage de Huffman s'exécutera pour construire l'arbre et retourner le texte crypté.
 */ 
class Cryptage
{
   private :
      Lecteur lecteur;
      ArbreB arbre_huffman; // Arbre binaire de cryptage construit
      std::vector<Sommet> arbres_restants; // Vector de gestion des arbres lors de l'algorithme
      std::map <char,std::string> encod_map; // Map des résultats de l'encodage

   public :
      /**
       * Constructeur et destructeur de classe
       */
      Cryptage(Lecteur&);
      ~Cryptage();

      void echange(const int, const int) ;

      // Getter pour l'arbre de Huffman
      ArbreB& get_arbre() {return arbre_huffman;};
      // Getter pour la map des résultats encodés
      std::map <char,std::string> get_map() { return encod_map; };

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
      void construction_arbre();

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
      std::string encodage();
};


#endif

