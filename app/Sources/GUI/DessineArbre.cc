#include "../../Headers/GUI/DessineArbre.h"
#include <math.h>
#include <QColor>
#include <QtGui/QPaintDevice>


int max_x = 200;
int zoom = 0;
int lrect, hrect;
/**
 * Constructeur par défaut
 */ 
DessineArbre::DessineArbre() {
    arbre = Context::getInstance().getArbre();
    resize(max_x, 500);

    connect(&Context::getInstance(), SIGNAL(arbreChanged()), this, SLOT(arbreChanged()));
};

/**
 * Ecrit un @QString sur l'interface 
 */
void DessineArbre::write(QPainter *p, int x, int y, QString txt) {
    int taille_x = p->fontMetrics().horizontalAdvance(txt);
    p->drawText(x - taille_x/2, y, txt);
}

/**
 * Compte le nombre de sommet fils avant de revenir au frère de @courant
 */
int compte_profondeur(Sommet *courant) {
    if (courant == NULL)
        return 0;
    return 1 + compte_profondeur(courant->getFilsG()) + compte_profondeur(courant->getFilsD());
}

/**
 * Calcule la longueur maximale parmi les sommets de l'arbre
 */
void calcul_ltext(Sommet *racine, QPainter *p) {
    if (racine == NULL) // Condition d'arrêt de la récursion
        return;

    if (p->fontMetrics().horizontalAdvance(racine->formalize_sommet()) > lrect)
        lrect = p->fontMetrics().horizontalAdvance(racine->formalize_sommet());
    
    calcul_ltext(racine->getFilsG(), p);
    calcul_ltext(racine->getFilsD(), p);
}   

/**
 * OLD VERSION: 
 * 
 * Fonction principale d'affichage: affiche l'arbre binaire de la gauche vers la droite.
 * 
 * Deux fils d'un même sommets sont liés par un trait vertical noir.
 * Un fils est lié à son père par un trait angulaire bleu.
 */  
/*
void DessineArbre::paint_tree_scales(Sommet *racine, int x , int *y, int last, int k, QPainter *p, QPen *pen) {
    // Condition d'arrêt de la récursion
    if (racine == NULL)
        return;

    // On réajuste la taille de la zone si l'arbre dépasse la zone de base
    if (x > max_x) {
        max_x = x;
    }

    int hauteur_texte = p->fontMetrics().height();
    int longueur_texte = p->fontMetrics().horizontalAdvance(racine->formalize_sommet());
    longueur_texte = 55;

    const QRectF Rect(x, *y, longueur_texte+20, hauteur_texte+8);
    p->drawText(Rect, Qt::AlignCenter, racine->formalize_sommet());
    p->drawRoundedRect(Rect, 10, 10);

    // Possède un frère: ligne verticale liant les deux frères 
    if (last == 0) {
        pen->setStyle(Qt::DashDotLine);
        p->setPen(*pen);
        p->drawLine(x + 20, *y+hauteur_texte+8,x+20, *y+(k*compte_profondeur(racine)));
    }
    // N'a pas d'autre frère: 
    // else { }
    // Possède au moins un fils 
    if (racine->getFilsG() != NULL || racine->getFilsD() != NULL) {
        pen->setColor(Qt::darkCyan);
        pen->setStyle(Qt::SolidLine);
        p->setPen(*pen);

        int new_y = (*y+hauteur_texte+8)+k - hauteur_texte/2;

        p->drawLine(x+longueur_texte, *y+hauteur_texte+8, x+longueur_texte, new_y);
        p->drawLine(x+longueur_texte, new_y, x+longueur_texte+17, new_y);
    }
    *y += k;


    pen->setColor(Qt::white);
    pen->setStyle(Qt::SolidLine);
    p->setPen(*pen);
    if (racine->getFilsG() != NULL && racine->getFilsD() != NULL) {
        paint_tree_scales(racine->getFilsG(), x+1.8*k, y, 0, k, p, pen);
        paint_tree_scales(racine->getFilsD(), x+1.8*k, y, 1, k, p, pen);
    }
    else {
        if (racine->getFilsD() != NULL )
            paint_tree_scales(racine->getFilsD(), x+1.8*k, y, 1, k, p, pen);

        else
            paint_tree_scales(racine->getFilsD(), x+1.8*k, y, 0, k, p, pen);

        if (racine->getFilsG() != NULL)

            paint_tree_scales(racine->getFilsG(), x+1.8*k, y, 1, k, p, pen);
        else
            paint_tree_scales(racine->getFilsG(), x+1.8*k, y, 0, k, p, pen);
    }

}
*/

/**
 * @brief Fonction d'affichage de l'arbre de Huffman : affiche l'arbre binaire de la gauche vers la droite.
 * 
 * Le somet père est lié d'un trait simple à ses deux fils. 
 * L'algorithme est adaptable en fonction de l'échelle k et de la taille du texte pour permettre le Zoom.
 */  
void DessineArbre::paint_tree_scales(Sommet *racine, int x , int *y, int k, QPainter *p, QPen *pen) {
    // Condition d'arrêt de la récursion
    if (racine == NULL)
        return;

    // On réajuste la taille de la zone si l'arbre dépasse la zone de base
    if (x+lrect > max_x) {
        max_x = x+lrect;
    }

    pen->setStyle(Qt::SolidLine); p->setPen(*pen);
    // RoundedRect pour le noeud courant
    const QRectF Rect(x, *y, lrect, hrect); 
    p->drawText(Rect, Qt::AlignCenter, racine->formalize_sommet());
    p->drawRoundedRect(Rect, 8, 8);

    // Si le noeud courant a 2 fils, on le relie aux deux
    int btm_y = *y+hrect; // Bas du rectangle courant
    if (racine->getFilsG() != NULL && racine->getFilsD() != NULL) {
        int lst_y = k+btm_y+(k*compte_profondeur(racine->getFilsG())) - hrect/3; // Fils le plus bas
        // Ligne verticale entre le père et son fils le plus bas
        p->drawLine(x+lrect/5, btm_y, x+lrect/5, lst_y);

        // Ligne horizontale vers le premier fils
        // pen->setStyle(Qt::DashDotLine); p->setPen(*pen); // Dashline pour les traits horizontaux ?
        p->drawLine(x+lrect/5, btm_y+k-hrect/3, x+(1.8*k), btm_y+k-hrect/3);
        
        // Ligne horizontale vers le deuxième fils
        p->drawLine(x+lrect/5, lst_y, x+(1.8*k), lst_y);
    }

    *y += k;

    paint_tree_scales(racine->getFilsG(), x+1.8*k, y, k, p, pen);
    paint_tree_scales(racine->getFilsD(), x+1.8*k, y, k, p, pen);
}

/**
 * Déclenche l'évènement "dessin" à l'exécution du programme 
 */  
void DessineArbre::paintEvent(QPaintEvent *) {
    QPainter paint(this);
    QPen pen(Qt::white, 2);
    paint.setPen(pen);
    paint.setRenderHint(QPainter::Antialiasing);
    
    // Récupère le Zoom pour définir la taille de texte
    QFont font = paint.font() ;
    font.setPointSize(font.pointSize() + zoom); paint.setFont(font);

    // Fixe la longueur et la hauteur des rectangles selon la taille du texte
    lrect = 0; calcul_ltext(arbre->getRacine(), &paint); lrect += lrect/2;
    hrect = paint.fontMetrics().height(); hrect += hrect/2;

    int y = 20;
    // paint_tree_scales(arbre->getRacine(), 10, &y, 1, 40*(1.2 + zoom/10), &paint, &pen); // Old version
    if (arbre->getRacine() != NULL)  {
        paint_tree_scales(arbre->getRacine(), 10, &y, 40*(1 + zoom/10), &paint, &pen);
        resize(max_x+90, y);
    }   
    else
        std::cout << "Pas d'arbre à dessiner yo" << std::endl; 
};

DessineArbre::~DessineArbre() { };

void DessineArbre::arbreChanged() {
    arbre = Context::getInstance().getArbre();
    zoom = Context::getInstance().getZoom();
    repaint();
}
