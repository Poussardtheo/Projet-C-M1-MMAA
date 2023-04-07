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

Le projet se décompose en 5 fichiers : 
    - ppm_image.hpp qui défini deux classes et les méthodes correspondantes: 
        > Pixel 
        > ppm_images
        
    - ppm_image.cpp: qui implémente le constructeur et une méthode d'écriture sur un fichiers .ppm
     
    - hough_transform.hpp: qui défini la classe HoughTransform et les méthodes correspondantes.
    
    - hough_transform.cpp: qui implémente 
        > le constructeur
        > la méthode transforme qui effectue la transformation de Hough
        > la méthode de détection de ligne sur une image
        >  la méthode qui permet de faire une transformation de Hough 
    
    - main.cpp: qui utilise les autres fichiers pour réaliser la détection de segment sur une image. 
