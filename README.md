# Projet C++ M1 MMAA Poussard/Nebout/Métayer

L'idée du projet est de faire de la détection de segment en C++. 


Pour ce faire, on a décomposé le projet en plusieurs étapes.

Analyse du problème:
- Compréhension thérorique de la transformée de Hough et les changements d'espaces.
- Mise en oeuvre d'une réflexion pour exhiber les fonctions utiles à la résolution du problème.

Travail prévu :
- Une partie sur la gestion des pixels et des triplets de couleurs associés
- Gestion de l'anticrénélage
- Lecture/écriture fichier image
- Une partie pour la transformée en coordonnées cartesiennes
- Une partie pour la transformée en coordonnées polaires.

Exemple en coordonnées cartésiennes :

Etant donnée un coefficient direteur de 1 et une ordonnée à l'origine de 1 (dans un repère ordonné comme celui d'une matrice), la transformée nous renvoie la matrice
M = (0,0,0,0)
    (1,0,0,0)
    (0,1,0,0)
    (0,0,1,0)
 
De plus, en considérant un ensemble de couple (mi, pi), la transformée renverra une matrice dont le plus grand coefficient (entier naturel) représentera le nombre de points de l'espace d'origine présent sur le segment de l'image.

Exemple en coordonnées polaires :
