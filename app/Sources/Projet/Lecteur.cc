#include "../../Headers/Projet/Lecteur.h"
using namespace std;

/**
    *Étant donné la nature des attributs de cette classe aucune initialisation supplémentaire n'est nécessaire, il seront
    mis à jour lors de l'analyse d'un texte
*/
Lecteur::Lecteur()
{
    ;
};

/**
   *Le constructeur par copie se base entièrement sur l'opérateur "=" qui récupère l'ensemble des données nécessaires
   à notre projet
*/
Lecteur::Lecteur(Lecteur& autre)
{
    *this = autre;
};

/**
    *Récupération des données dans les vecteurs et dans le texte à analyser ( si ce n'est pas déjà fait ) grâce aux
    getteurs
*/
void Lecteur::operator=(Lecteur& donneur)
{
    occurences = donneur.getOccurences();
    contenu = donneur.getContenu();
    lettres = donneur.getLettres();
};

/**
    *Lors de l'analyse d'un texte, si on croise un caractère on s'assure d'abord de ne pas l'avoir déjà ajouté dans
    le vecteur nommé "lettres" :
        cette méthode renvoie l'indice dans lequel il se trouve si c'est le cas, sinon elle renvoie -1
*/
int Lecteur::get_indice(const char c)
{
    int taille = lettres.size();
    for(int i = 0; i < taille ; i++)
    {
        if(c == lettres[i])
            return i;
    }

    return -1;
}


/**
 * @brief Lecture à partir d'un fichier.
 * 
 * Lis le fichier pour le mettre dans une chaîne, puis appelle le lecteur de chaîne.
 */ 
void Lecteur::lecture(ifstream& myfile)
{
    std::stringstream strStream;
    if(myfile.is_open() )
    {
        strStream << myfile.rdbuf(); //read the file
        contenu = strStream.str(); //str holds the content of the file
    }
    myfile.close();
    lecture(contenu);
}

 /**
 * @brief Algorithme de lecture à partir d'une chaîne de caractère.
 * 
 * La fonction stockera l'ensemble des lettres et occurrences dans les deux vectors private de la classe.
 * Pour chacun des caractères ASCII sauf la ponctuation, on stocke le caractère et on compte son nombre d'occurrences dans le texte.
 * Avant d'ajouter un nouveau caractère dans le vecteur lettres on s'assure qu'il n'y est déjà pas, sinon on ne fait
    qu'incrémenter l'indice équivalent dans le vecteur occurences.
 * Après avoir compté le nombre de caractères distincts, on calcule dans la boucle qui suit le pourcentage correspondant
   à chacune des occurences
 */ 
void Lecteur::lecture(string const& chaine)
{
    contenu = chaine;
    int size = contenu.size();
    if(size != 0)
    {
        int indice = -1 ;
        int ascii = -1;
        char convert;
        int nb_carac = 0;
        for(int i = 0 ; i < size ; i++)
        {
            if(contenu[i] != ' ' && contenu[i] != ';' && contenu[i] != ',' && contenu[i] != '.' && contenu[i] != '\n' && contenu[i] != '\0')
            {
                ascii= (int) (contenu[i]);
                if( (ascii >= -96 && ascii <= -65) || (ascii >= 0 && ascii <= 127)) // -96 à -65 pour les accentués (ASCII Etendu)
                {
                    nb_carac++;
                    convert = contenu[i];

                    if(ascii >= 65 && ascii <= 90) // Si c'est une majuscule, on la considère minuscule
                        convert = (char) (ascii+32);

                    indice = get_indice(convert);
                    if(indice == -1)
                    {
                        lettres.push_back(convert);
                        occurences.push_back(1.0);
                    }
                    else 
                        occurences[indice] += 1.0;
                }
            }
        }

        size = occurences.size();
        for(int i = 0 ; i < size ; i++)
            occurences[i] = occurences[i] * 100.0 / nb_carac;

    }
}

/**
  *La surchage de l'opérateur '<<' affiche côte à côte un caractère et son pourcentage
*/
ostream& operator<<(ostream& flux,Lecteur& lecteur)
{

    int i = 0;
    flux<<"Pour le texte : \n[ "<<lecteur.contenu<<" ] on obtient :\n\n";
    flux<<"Lecteur : { ";
    int taille = lecteur.occurences.size();
    for(i = 0 ; i < taille ; i++)
    {
            if(i == 0 )
                flux<< "( " <<lecteur.lettres[i] <<" ; "<<lecteur.occurences[i]<<" )";

            else
                flux<< " | ( " <<lecteur.lettres[i] <<" ; "<<lecteur.occurences[i]<<" )";

    }
    flux<<"} \n";
    return flux;
};


bool operator==(Lecteur& premier, Lecteur& second)
{
    if(premier.lettres != second.lettres)
        return false;

    if(premier.occurences != second.occurences)
        return false;

    return true;
}

/**
    *La classe Lecteur ne contient pas d'attributs alloués dynamiquement, il n'y donc rien à delete
*/
Lecteur::~Lecteur()
{
    lettres.erase(lettres.begin(),lettres.end());
    occurences.erase(occurences.begin(),occurences.end());
};