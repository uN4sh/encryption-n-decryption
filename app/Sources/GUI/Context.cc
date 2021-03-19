#include "../../Headers/GUI/Context.h"

/**
 * @brief Constructeur de classe déclaré private, le getter d'instance sera public
 */
Context::Context()  {
    // On initie le contexte avec le texte fourni initialement
    // std::ifstream myfile("Texte.txt");
    setText("elbow below");
}

// Setters:

/**
 * @brief Setter pour l'arbre courant du contexte
 *
 * @param e_arbre
 */
void Context::setArbre(ArbreB arbre)  {
    // L'opérateur = de l'arbre se charge de faire les frees nécessaires
    arbre_courant = arbre;
    // Signal émis à DessineArbre pour récupérer le nouvel arbre
    emit arbreChanged();
}

/**
 * @brief Setter pour modifier le texte en entrée à partir d'un fichier (après action de l'utilisateur)
 * 
 * @param file
 */
void Context::setText(std::ifstream & file)  {
    // On transforme le fichier en string
    std::stringstream strStream;
    std::string contenu;
    if(file.is_open()) {
        strStream << file.rdbuf(); //read the file
        contenu = strStream.str(); //str holds the content of the file
    }
    file.close();
    // On appelle le setter qui utilise la String
    setText(contenu);
}

/**
 * @brief Appelle les classes Lecteur et Cryptage Setter pour modifier le texte en entrée à partir d'une string (après action de l'utilisateur)
 * On émet le signal textCrypted() pour activer la suite du processus d'actualisation
 * @param string
 */
void Context::setText(std::string const& val)  {
    txt_to_crypt = val;

    Lecteur l;
    l.lecture(val);
    std::cout << "\033[1;37m> Texte à coder: \033[0m" << l.getContenu() << std::endl;

    // Faire un nouvel arbre
    Cryptage cr(l);
    cr.construction_arbre();
    crypted_text = cr.encodage();
    map_res = cr.get_map();

    // Signal émis l'actualisation de l'affichage texte
    emit textCrypted();
    emit resultsArrived();

    // On envoie l'arbre seulement s'il existe
    if (cr.get_arbre().getRacine())  {
        // PRINT à RETIRER une FOIS QUE PLUS DE BUGS
        std::cout << cr.get_arbre() << std::endl; // Ok !
        setArbre(cr.get_arbre());
    }
    // else: Envoie signal de clear de Dessine arbre
}

/**
 * @brief Appelle la classe Decryptage pour décrypter le texte entré par l'utilisateur et stocke le résultat dans decrypte_status. 
 *        Emet le signal textDecrypted() une fois que c'est fait.
 */
void Context::decrypteText(std::string const& crypted)  {
    Decryptage d(crypted, arbre_courant);
    decrypte_status = d.decrypte_arbre();
    if (decrypte_status > 0)
        decrypted = d.getDecrypted();
    
    emit textDecrypted(); // Signal émis pour actualiser l'affichage du résultat 
}

/**
 * @brief Setter pour modifier le paramètre Zoom
 */
void Context::changeZoom()  { 
    zoom = 10-zoom; 
    emit arbreChanged(); 
};
