#ifndef DESSINEARBRE_H
#define DESSINEARBRE_H

#include "Context.h"

#include <QMainWindow>
#include <QtGui/QPainter>
#include <QtGui/QPaintDevice>


/**
 * @file DessineArbre.h
 * @brief Algorithme de dessin d'un arbre binaire sur la zone graphique, affiché de gauche à droite, utilise le PaintEvent de Qt.
 * 
 * @private   ArbreB      Arbre binaire à afficher
 */
class DessineArbre : public QWidget{

    Q_OBJECT

private :
    ArbreB *arbre;

public :
    /**
     * Constructeur par défaut
     */ 
    DessineArbre();

    /**
     * Destructeur de classe
     */ 
    ~DessineArbre();

    /**
     * Ecrit un @QString sur l'interface 
     * */
    void write(QPainter*, int, int, QString);

    /** 
     * Représente l'arbre binaire sur l'interface
     */ 
    void paint_tree_scales(Sommet *, int x , int *y, int last, int k, QPainter*, QPen*);
    void paint_tree_scales(Sommet *, int x , int *y, int k, QPainter*, QPen*);

    /**
     * Déclenche l'évènement "dessin" à l'exécution du programme 
     */  
    void paintEvent(QPaintEvent * painter);


public slots:

    /**
     * @brief Réaffiche le nouvel arbre quand il change
     * 
     */
    void arbreChanged();

signals: 

};

#endif // DESSINEARBRE_H
