cmake_minimum_required(VERSION 2.8.11)

project(Partie3Cryptage)

find_package(Qt5 5.0.1 REQUIRED COMPONENTS
    Core Gui Widgets
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME}
    Headers/Projet/Sommet.h 
    Headers/Projet/ArbreB.h 
    Headers/Projet/Lecteur.h 
    Headers/Projet/Cryptage.h 
    Headers/Projet/Decryptage.h 
    Headers/GUI/DessineArbre.h 
    Headers/GUI/MainWindow.h 
    Headers/GUI/GetUserText.h 
    Headers/GUI/DisplayResults.h 
    Headers/GUI/Context.h 

    Sources/Projet/Sommet.cc 
    Sources/Projet/ArbreB.cc 
    Sources/Projet/Lecteur.cc 
    Sources/Projet/Cryptage.cc 
    Sources/Projet/Decryptage.cc 
    Sources/GUI/DessineArbre.cc 
    Sources/GUI/MainWindow.cc 
    Sources/GUI/GetUserText.cc 
    Sources/GUI/Context.cc 
    Sources/GUI/graphicMain.cc

    ../qdarkstyle/style.qrc
)

target_link_libraries(${PROJECT_NAME}

    Qt5::Core Qt5::Gui Qt5::Widgets

)
