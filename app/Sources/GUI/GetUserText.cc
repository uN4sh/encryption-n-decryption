#include "../../Headers/GUI/GetUserText.h"
#include "../../Headers/GUI/Context.h"

GetUserText::GetUserText()  {
    layout = new QGridLayout();
    setLayout(layout);

    // Saisie de texte à crypter / à décrypter :

    // Saisie de texte à crypter
    saisie_clair = new QLineEdit(this);  saisie_clair->show();
    saisie_clair->setPlaceholderText("Saisissez ici le texte à encoder");
    layout->addWidget(saisie_clair, 2, 0, 1, 3); // Troisieme de la grille de menu, à gauche

    // Saisie de texte à décrypter
    saisie_crypte = new QLineEdit(this);  saisie_crypte->show();
    saisie_crypte->setPlaceholderText("Saisissez ici le texte à décoder");
    layout->addWidget(saisie_crypte, 4, 0, 1, 2); // Cinquieme de la grille de menu à gauche
    
    // Connexion des évènements "TextChanged" aux slots Crypte / Decrypte pour traiter les textes entrés 
    connect(saisie_crypte, SIGNAL(textChanged(QString)), this, SLOT(checkChangeDecrypte(const QString&)));
    connect(saisie_clair, SIGNAL(textChanged(QString)), this, SLOT(checkChangeCrypte()));
    // Connexion des slots Crypted / Decrypted aux signaux émis par le Context
    connect(&Context::getInstance(), SIGNAL(textCrypted()), this, SLOT(textCrypted()));
    connect(&Context::getInstance(), SIGNAL(textDecrypted()), this, SLOT(textDecrypted()));


    // Labels (écritaux):

    // Texte initial en clair
    texte_clair = new QLabel(QString::fromStdString("<b>Texte à coder : </b>"+ Context::getInstance().getText()));
    texte_clair->show();  texte_clair->setWordWrap(true);
    layout->addWidget(texte_clair, 0, 0, 1, 2); // Premier de la grille de menu

    // Résultat du cryptage
    texte_crypte = new QLabel(QString::fromStdString("<b>Texte codé : </b>" + Context::getInstance().getResult()));
    texte_crypte->show();  texte_crypte->setWordWrap(true); // Retour à la ligne si le texte est trop long
    layout->addWidget(texte_crypte, 1, 0, 1, 3); // Deuxieme de la grille de menu
    
    // Séparation pour la Partie 3
    wP3 = new QLabel(QString::fromStdString("<b>Partie 3 :</b> Décryptage d'un texte à partir de l'arbre binaire de cryptage défini ci-dessus"));
    wP3->show();   layout->addWidget(wP3, 3, 0, 1, 3); // Quatrieme de la grille de menu 

    // Résultat du décryptage
    texte_decrypte = new QLabel();
    texte_decrypte->setWordWrap(true); // Retour à la ligne si le texte est trop long
    texte_decrypte->show();
    layout->addWidget(texte_decrypte, 5, 0, 1, 3); // Sixieme de la grille de menu 

    // PushButtons : 

    // Utiliser le Texte codé
    bRealTxt = new QPushButton("Utiliser le Texte codé", this);
    bRealTxt->show();  layout->addWidget(bRealTxt, 4, 2);
    connect(bRealTxt, SIGNAL(clicked()), this, SLOT(useRealPushed()));

    // Zoom
    bZoomer = new QPushButton("🔍", this);
    bZoomer->show();  bZoomer->setMaximumWidth(40);  layout->addWidget(bZoomer, 0, 2);
    connect(bZoomer, SIGNAL(clicked()), this, SLOT(zoomPushed()));
}

/**
 * @brief Renvoie la chaine entrée découpée par des espaces si elle dépasse 130 caractères
 */
std::string GetUserText::stringCutter(std::string tmp)  {
    if( (tmp.length() > 130)  )  { 
        for(size_t i = 1; i <= tmp.length()/130; i++)  {
            int n = i * 130;
            tmp.insert(n, " ");
        }
    }
    return tmp;
}

GetUserText::~GetUserText() { }

/**
 * @brief Slot appelé dès qu'un texte est entré dans la barre de saisie de cryptage.
 * Si ce texte n'est pas vide, il est envoyé au Context pour traitement Cryptage.
 */
void GetUserText::checkChangeCrypte() {
    if (!saisie_clair->text().isEmpty()) // En cas de Valider sans rien pour pas seg-fault
        Context::getInstance().setText(saisie_clair->text().toStdString());
}

/**
 * @brief Slot appelé une fois le décryptage effectué dans la classe Context (suite au signal émis).
 *        La fonction affichera simplement le texte entré et le texte crypté sur les deux labels.
 */
void GetUserText::textCrypted() {
    // On actualise l'affichage du texte clair
    texte_clair->setText(QString::fromStdString("<b>Texte à coder : </b>" + Context::getInstance().getText()));
    
    // On actualise l'affichage du resultat en passant par la fonction stringCutter
    texte_crypte->setText(QString::fromStdString(stringCutter("<b>Texte codé : </b>" + Context::getInstance().getResult())));
}

/**
 * @brief Slot appelé dès qu'un texte est entré dans la barre de saisie de décryptage.
 * Si le texte ne match pas à la regex, un texte d'erreur est écrit. Sinon, on appelle la fonction de décryptage dans la classe Context.
 */
void GetUserText::checkChangeDecrypte(const QString & text)  {
    if (text.isEmpty())
        return;
    // QRegularExpression regex("^[0-1]+$"); 
    QRegularExpression regex("^(1|0| |,|;)+$");
    QRegularExpressionMatch match = regex.match(text);
    if (!match.hasMatch()) 
        texte_decrypte->setText("<font color='red'>L'expression à décoder doit contenir uniquement des 0 ou des 1.</font>");
    else  {
        texte_decrypte->setText(text);
        // Envoyer au contexte pour décryptage  
        Context::getInstance().decrypteText(text.toStdString());
    }
}

/**
 * @brief Slot appelé une fois le décryptage effectué dans la classe Context (suite au signal émis).
 * Cette fonction se base sur le statut renvoyé par le décryptage pour afficher le message adéquat avec le texte décodé.
 */
void GetUserText::textDecrypted()  {
    switch (Context::getInstance().getDecrypteStatus())  {
        case -1:
            // Erreur lors de l'exécution de l'algorithme de décryptage, l'arbre ne correspond donc pas au texte 
            texte_decrypte->setText("<font color='red'>Ce texte ne peut être décodé avec l'arbre binaire de cryptage défini.</font>");
            break;
        case 1:
            // Le texte n'a pas été codé par la partie 2, mais l'arbre fourni peut effectivement servir à décoder ce texte
            texte_decrypte->setText("<font color='yellow'>Ce texte n'a pas été encodé par l'arbre binaire de cryptage défini mais il peut tout de même servir à le décoder :</font><br><b>Texte décodé : " + QString::fromStdString(Context::getInstance().getDecrypted()) + "</b></br>");
            break;
        case 2:
            texte_decrypte->setText("<font color='green'>Ce texte a pu être été codé par l'arbre binaire de cryptage défini car les codes et occurences correspondent :</font><br><b>Texte décodé : " + QString::fromStdString(Context::getInstance().getDecrypted()) + "</b><br><i>On ne peut toutefois pas s'assurer que l'arbre binaire de cryptage défini a permis d'encoder ce texte.</i>");
            break;
    }
}

/**
 * @brief Slot appelé lorsque le bouton "Zoom" est appuyé.
 *        Change le facteur de Zoom puis redessine l'arbre binaire via la classe DessineArbre.
 */
void GetUserText::zoomPushed()  {
    Context::getInstance().changeZoom();
}

/** 
 * @brief Slot appelé lorsque le bouton "Utiliser le Texte Codé" est appuyé.
 *        Appelle le slot checkChangeDecrypte() avec le texte crypté du Context.
 */
void GetUserText::useRealPushed()  {
    QString crypted = QString::fromStdString(Context::getInstance().getResult());
    saisie_crypte->setText(crypted);
    checkChangeDecrypte(crypted);
}
