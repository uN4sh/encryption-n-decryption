# Projet C++ : Cryptage et décryptage 

Le but principal de ce projet est de développer un système de codage et de décodage basé sur le
code de Huffmann.
Le codage d’Huffmann a pour but de coder un texte en binaire préfixé qui consiste à coder chaque
lettre par un mot sur 0, 1 (toujours le même pour une lettre).

## Déroulement et fonctionnalités

- Lecture et calcul des occurrences de chaque lettre d'un texte en entrée 
- Construction de l'arbre binaire de Cryptage 
- Codification du texte en entrée 
- Décryptage d'un texte codé à l'aide d'une map ou d'un arbre
- Interprétation des résultats 
- L'interface graphique de l'application est propulsée par Qt

## Commandes et utilisation

1. Exécuter le programme avec l'outil de compilation CMake :
```
 make 
```

2. Exécuter le programme avec QMake :
```
make gui
```

3. Générer la documentation Doxygen et le listing des fichiers :
```
make listing
```
> Nécessite le programme Doxygen. Un répertoire `doc/` sera créé avec le listing en `html`. Le Makefile tentera par défaut d'ouvrir la documentation avec `firefox` mais cela pourrait ne pas fonctionner si vous n'avez pas le programme. Je vous recommande donc d'ouvrir le fichier `doc/html/files.html` avec votre navigateur habituel pour accéder au listing détaillé et commenté des classes.

4. Exécuter une série de tests en mode CLI (sans faire intervenir les classes Qt)
```
make cli
```

5. Exécuter en mode debug (Valgrind et mem-check)
```
make debug
```

## Détails de la structure du code

![Classes du projet](https://github.com/vdElyn/[reponame]/blob/main/res/listing.png?raw=true)

## Aperçu d'exécution

![Aperçu d'exécution](https://github.com/vdElyn/[reponame]/blob/main/res/apercu.gif?raw=true)
