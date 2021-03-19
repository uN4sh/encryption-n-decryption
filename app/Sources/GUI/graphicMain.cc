#include "../../Headers/GUI/MainWindow.h"

#include <QApplication>

#include <QFile>
#include <QTextStream>


/**
 * @file graphicMain.cc
 * @brief Partie 3 : Constitue la fonction main lors de l'exécution graphique pour le Cryptage et le Decryptage, charge le thème et l'interface graphique.
 */
int main(int argc, char* argv[])
{
    std::cout << "\033[1;33mProjet LA - Partie 2 | Samy BOUMALI & Amine ATEK\033[0m - Exécution GUI\n\n" << std::endl;

    /* Qt application graphique */
    QApplication app(argc, argv);
    
    /* Modification du style d'affichage pour éviter les soucis de compatibilité couleurs entre les OS */
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
        printf("Unable to set stylesheet, file not found\n");
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    // Affichage graphique //
    MainWindow aff;
    aff.show();

    return app.exec();
}
