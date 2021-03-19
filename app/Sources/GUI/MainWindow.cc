#include "../../Headers/GUI/MainWindow.h"


MainWindow::MainWindow() {
    layout = new QGridLayout();
    setLayout(layout);

    // Taille maximale de la fenêtre principale
    this->setMaximumSize(1920, 1080);

    // Zone d'intéraction avec l'utilisateur (barre de saisie et boutons)
    wInput = new GetUserText();
    wInput->show();
    layout->addWidget(wInput, 2, 0, 1, 2);

    // Zone résultats
    resultats = new DisplayResults();

    wZoneResultats = new QScrollArea(this);
    wZoneResultats->setWidget(resultats);
    wZoneResultats->show();
    wZoneResultats->setFixedWidth(300);
    layout->addWidget(wZoneResultats, 0, 1);

    // Zone de dessin (Mid)
    dessin = new DessineArbre();

    wZoneArbre = new QScrollArea(this);
    wZoneArbre->setWidget(dessin);
    wZoneArbre->show();
    wZoneArbre->setMinimumWidth(700);
    layout->addWidget(wZoneArbre, 0, 0);
}

/**
 * @brief Surcharge de l'évènement Qt keyPressEvent pour permettre de quitter l'application par touche ESC
 */
void MainWindow::keyPressEvent(QKeyEvent* event)  {
    if(event->key() == Qt::Key_Escape)
        QCoreApplication::quit();   
    else
        QWidget::keyPressEvent(event);
}

MainWindow::~MainWindow() { }
