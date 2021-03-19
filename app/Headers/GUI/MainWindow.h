#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GetUserText.h"
#include "DisplayResults.h"
#include "DessineArbre.h"

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>

#include <QKeyEvent>


/**
 * @file MainWindow.h
 * @brief Fenêtre principale du programme graphique, composé d'une bannière, d'un menu et d'une zone de dessin.
 * 
 * @private      QGridLayout*    Layout en grille pour le programme graphique
 * @private      GetUserText*    Menu principal des interactions avec l'utilisateur (barre de saisie, boutons et labels)
 * @private      QScrollArea*    Zone à barre de défilement pour l'affichage du dessin
 * @private      QScrollArea*    Zone à barre de défilement pour l'affichage des résultats
 * @private      DessineArbre*   Dessin de l'arbre binaire
 */ 
class MainWindow : public QWidget {
private :
    QGridLayout* layout; // Grid Layout pour l'affichage
    
    GetUserText* wInput; // Menu principal des interactions avec l'utilisateur (barre de saisie, boutons et labels)

    DisplayResults* resultats;
    QScrollArea* wZoneResultats;

    DessineArbre* dessin;
    QScrollArea* wZoneArbre;

public :
    /**
     * Constructeur par défaut
     */ 
    MainWindow();
    

    /**
     * @brief Surcharge de l'évènement Qt keyPressEvent pour permettre de quitter l'application par touche ESC
     */
    void keyPressEvent(QKeyEvent* event);

    /**
     * Destructeur de classe
     */ 
    ~MainWindow();
};

#endif // MAINWINDOW_H
