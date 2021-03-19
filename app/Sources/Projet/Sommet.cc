#include "../../Headers/Projet/Sommet.h"
using namespace std;


/**
    Quand on créer un sommet on ne lui donne qu'un caractère et qu'une occurence, ses fils seront ajoutés lors de la
    formation de l'arbre
*/
Sommet::Sommet(char car, float part,int size)
{
    filsd = NULL;
    filsg = NULL;
    lettre = car;
    freq = part;
    taille = size;
};

/**
   Copie des données de manière récursives tant qu'il y a des fils à copier
*/
Sommet::Sommet(const Sommet& s)
{
    filsg = NULL;
    filsd = NULL;

    if (s.filsd != NULL)  {
        filsd = new Sommet(*s.filsd);
    }

    if (s.filsg != NULL)  {
        filsg = new Sommet(*s.filsg);
    }

    freq = s.freq;
    lettre = s.lettre;
    taille = s.taille;
};


/**
    L'opérateur '=' utilise les setteurs afin de reprendre et copier les données du sommet passé en param
*/
void Sommet::operator=(const Sommet& source)
{
    lettre = source.lettre;
    freq = source.freq;
    taille = source.taille;
    if(source.filsd != NULL )   //Si le sommet à copier a un fils droit
    {
        if(filsd != NULL)
            *filsd = *source.filsd;

        else
        {
            filsd = new Sommet;
            *filsd = (*source.filsd);
        }
    }
    else                       //S'il n'en a pas
    {
        if(filsd != NULL)
        {
            delete filsd;
            filsd = NULL;
        }
    }
    if(source.filsg != NULL ) //Si le sommet à copier a un fils gauche
    {
        if(filsg != NULL)
            *filsg = *source.filsg;

        else
        {
            filsg = new Sommet;
            *filsg = (*source.filsg);
        }
    }
    if(source.filsg == NULL ) //S'il n'en a pas
    {
        if(filsg != NULL)
        {
            delete filsg;
            filsg = NULL;
        }
    }


};


/**
   *La somme de deux sommets nous donne un sommet sans lettre ( avec le caractère espace ) et la somme de leur
    fréquence
*/
Sommet operator+(Sommet& terme1, Sommet& terme2)
{
   Sommet nouveau;
   nouveau.setLettre(' ');                                       //caractère vide assignée
   nouveau.setFreq ( terme1.getFreq() + terme2.getFreq() );    //somme des fréquences assignée
   nouveau.filsg = &terme1;
   nouveau.filsd = &terme2;
   nouveau.setTaille(3);

   return nouveau;
};

/**
    ici on affiche un sommet de façon textuelle (utilisée pour avoir les informations d'un sommet seul)
*/
std::ostream& operator<<(std::ostream& flux,Sommet& sommet) //affichage de la lettre et de sa fréquence
{
    flux<<"Ce sommet a pour lettre "<<sommet.lettre<<" ,qui apparaît "<<sommet.freq<<" fois dans le texte\n";
    return flux;
};

/**
    ici on affiche un sommet de façon plus 'mathématique', c-a-d qu'il est sous forme de couple de valeurs (utilisé
    dans l'affichage d'un arbre)
*/
char * Sommet::formalize_sommet() {
    char * sommet = new char [13];
    sprintf(sommet, "(%c : %.1f)", lettre, freq);
    sommet[12] = '\0';
    return sommet;
}

/**
    Cette méthode libère la mémoire d'un sommet (et de ses fils potentiels)  avant qu'on copie d'autres données dans ce
    dernier, et on adopte la récursion comme pour les arbres
*/
void Sommet::clean_sommet()
{
    if(filsg != NULL)
    {
        filsg->clean_sommet();
        delete filsg;
        filsg = NULL;
    }

    if(filsd != NULL)
    {
        filsd->clean_sommet();
        delete filsd;
        filsd = NULL;
    }
}


/**
    Le destructeur fait appel à la méthode précédente afin de supprimer les fils récursivement
*/
Sommet::~Sommet()
{
   clean_sommet();
};