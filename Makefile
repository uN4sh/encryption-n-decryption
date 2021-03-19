OUT_DIR = target

final: # gui
	@cmake app/CMakeLists.txt
	@cd app; make
	./app/Partie3Cryptage

# Execution en CLI (Affichage sur terminal)
cli: compil
	./${OUT_DIR}/TestArbre

# Execution via Valgrind (debug)
debug: compil
	valgrind ./${OUT_DIR}/TestArbre

# Execution en GUI (Interface graphique Qt)
gui: 
	@qmake -makefile -o QMakefile app/Partie3Cryptage.pro 
	make -f QMakefile
	@./Partie3Cryptage

# Listing des fichiers
listing:
	doxygen Doxyfile
	firefox doc/html/files.html

# Compilation CLI
compil: ${OUT_DIR} ${OUT_DIR}/TestArbre.o ${OUT_DIR}/ArbreB.o ${OUT_DIR}/Sommet.o ${OUT_DIR}/Lecteur.o ${OUT_DIR}/Cryptage.o ${OUT_DIR}/Decryptage.o
	g++ -std=c++11 -Wall -g -o ${OUT_DIR}/TestArbre ${OUT_DIR}/TestArbre.o ${OUT_DIR}/ArbreB.o ${OUT_DIR}/Sommet.o ${OUT_DIR}/Lecteur.o ${OUT_DIR}/Cryptage.o ${OUT_DIR}/Decryptage.o


### Représentations intermédiaires

${OUT_DIR}/TestArbre.o: app/Sources/Projet/TestArbre.cc app/Headers/Projet/ArbreB.h app/Headers/Projet/Sommet.h
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/TestArbre.o app/Sources/Projet/TestArbre.cc

${OUT_DIR}/ArbreB.o: app/Sources/Projet/ArbreB.cc app/Headers/Projet/ArbreB.h app/Headers/Projet/Sommet.h
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/ArbreB.o app/Sources/Projet/ArbreB.cc

${OUT_DIR}/Sommet.o: app/Sources/Projet/Sommet.cc app/Headers/Projet/Sommet.h
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/Sommet.o app/Sources/Projet/Sommet.cc

${OUT_DIR}/Lecteur.o: app/Sources/Projet/Lecteur.cc app/Headers/Projet/Lecteur.h
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/Lecteur.o app/Sources/Projet/Lecteur.cc

${OUT_DIR}/Cryptage.o: app/Sources/Projet/Cryptage.cc app/Headers/Projet/Cryptage.h
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/Cryptage.o app/Sources/Projet/Cryptage.cc

${OUT_DIR}/Decryptage.o: app/Sources/Projet/Decryptage.cc app/Headers/Projet/Decryptage.h 
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/Decryptage.o app/Sources/Projet/Decryptage.cc

# ======= #

### Utilitaires

${OUT_DIR}:
	mkdir -p ${OUT_DIR}

clean:
	@rm -f qrc_style.cpp
	@rm -f app/Partie3Cryptage
	@rm -rf app/CMakeFiles
	@rm -rf app/Partie3Cryptage_autogen/
	@rm -f app/CMakeCache.txt
	@rm -f app/cmake_install.cmake
	@rm -f app/Makefile
	@rm -f *.o
	@rm -f moc_*
	@rm -f QMakefile
	@rm -rf ${OUT_DIR}
	@rm -rf doc/
