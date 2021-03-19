#ifndef GETUSERTEXT_H
#define GETUSERTEXT_H

#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QRegularExpression>
#include <iostream>


/**
 * @file GetUserText.h
 * @brief Menu principal des interactions avec l'utilisateur : comprend une barre de saisie pour le cryptage et une pour le décryptage,
 *        un bouton de Zoom, deux labels pour l'affichage du texte à codé et du texte codé, et un label pour le résultat du décryptage.
 */
class GetUserText : public QFrame {
    Q_OBJECT
private:
    QGridLayout* layout; // Grid Layout pour le menu des interactions

    QLineEdit *saisie_clair; // Input pour le texte à crypter
    QLineEdit *saisie_crypte; // Input pour le texte à décrypter

    QLabel* texte_clair; // Texte initial en clair
    QLabel* texte_crypte; // Résultat du cryptage
    QLabel *wP3; // Séparation pour la Partie 3
    QLabel *texte_decrypte; // Résultat du décryptage

    QPushButton *bZoomer; // Bouton de Zoom
    QPushButton *bRealTxt; // Bouton d'utilisation du texte codé pour le décryptage

public:
    /**
     * @brief Constructeur par défaut : sert à l'affichage des éléments du menu des interactions
     */ 
    GetUserText();

    /**
     * @brief Renvoie la chaine entrée découpée par des espaces si elle dépasse 130 caractères
     */
    std::string stringCutter(std::string);

    /**
     * @brief Destructeur de classe
     */ 
    ~GetUserText();


public slots:
    /**
     * @brief Slot appelé dès qu'un texte est entré dans la barre de saisie de cryptage.
     * Si ce texte n'est pas vide, il est envoyé au Context pour traitement Cryptage.
     */
    void checkChangeCrypte();

    /**
     * @brief Slot appelé dès qu'un texte est entré dans la barre de saisie de décryptage.
     * Si le texte ne match pas à la regex, un texte d'erreur est écrit. Sinon, on appelle la fonction de décryptage dans le contexte.
     */
    void checkChangeDecrypte(const QString &);
    
    /**
     * @brief Slot appelé une fois le cryptage effectué dans la classe Context (suite au signal émis).
     *        Affiche le texte entré et le texte crypté sur les deux labels une fois le cryptage effectué.
     */
    void textCrypted();

    /**
     * @brief Slot appelé une fois le décryptage effectué dans la classe Context. 
     *        La fonction se base sur le statut renvoyé par le décryptage pour afficher le message adéquat avec le texte décodé.
     */
    void textDecrypted();

    // PushButtons :

    /**
     * @brief Slot appelé lorsque le bouton "Zoom" est appuyé.
     *        Change le facteur de Zoom puis redessine l'arbre binaire via la classe DessineArbre.
     */
    void zoomPushed();

    /** 
     * @brief Slot appelé lorsque le bouton "Utiliser le Texte Codé" est appuyé.
     * La fonction va simplement appelé le slot checkChangeDecrypte() avec le texte crypté du Context.
     */
    void useRealPushed();

signals:

};


#endif // GETUSERTEXT__H
