# TetrisSFML

Réutilisation d'ancien code, il se peut qu'il reste des lignes inutiles dans le projet final






***Comment compiler le projet***:

Installation des modules nécessaires:

-sudo apt-get install cmake  
-sudo apt-get install clang-11  
sudo apt-get install libsfml-dev  

Télécharger le projet dans un dossier

-git clone https://github.com/alexdembele/TetrisSFML  
-cd ../

Construire le projet  
-mkdir build  
-cd build  
-cmake ../TetrisSFML  
-make  

***Attention*** 
Dans mon code, le dossier s'appelle projet, il faut renommer les chemins d'inclusions pour avoir les graphismes; cela se trouve dans le constructeur de la classe Game. De plus, pour le mutlijoueur, il faut mettre l'ip du serveur en dur dans le code (main du joueur) car la fonction de sfml renvoie une mauvaise IP.


Exécuter le projet  
-./sfml-app

Pour jouer en multijoueur, il faut lancer le server avant de lancer les joueurs. 

