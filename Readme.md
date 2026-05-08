## QU'EST-CE QUE ASCII LEVEL 2 ?

ASCII LEVEL 2 EST UNE APP QUI CONSISTE A CREER UN ART ASCII A PARMIS D'IMAGES CONTENU DANS LE DOSSIER ASSETS DU PROJETS.

L'IMAGE SERA SELCTIONNE ALEATOIREMENT !

N.B : VOUS POUVEZ AJOUTER VOS IMAGES DANS LE DOSSIER 'ASSETS' POUR VOIR VOS IMAGES EN FORMAT ASCII


### 1. Prérequis
* Un compilateur C++ (GCC, Clang ou MSVC)
* CMake 3.20 ou plus

### 2. Compilation

* 1- Cloner le projet : git clone https://github.com/kingnaej/ASCII-Level-2.git
* 2- cd ASCII-Level-2

* 3- 

    #### Pour Windows avec Visual Studio, Linux ou MAC :
        cmake -S . -B build
    #### Pour Windows avec MinGW :
	    cmake -S . -B build -G "MinGW Makefiles"

* 4- cmake --build build

### 3. DISTRIBUTION

    cmake --install build --prefix ./dist

### 4. LANCER L'APP

Pour Windows
    
		.\dist\bin\Level2.exe

Linux / macOS

		./dist/bin/Level2