#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//Fonction 1
double coefficient_directeur(std::vector<int> A, std::vector<int> B)
{
    double coef_dir;
    coef_dir = (B[1]-A[1])/(B[0]-A[0]); // Calcul du coefficient directeur

    return coef_dir;
}

//Fonction 2

std::vector<int> ordonne_origine(double coeff_dir, std::vector<int> A)
{
    std::vector<int> ordon_orig(2,0);
    ordon_orig[1] = 0;
    ordon_orig[0] = A[0]-coeff_dir*A[1];

    return ordon_orig;
}

//Fonction 3

std::vector<std::vector<int>> Tf_Hough_a_couple_donnee(double coef_dir, std::vector<int> ordon_orig, std::vector<int> dim_image)
{
    std::vector<std::vector<int>> Matrice_Hough;

    for (int i = 0; i < dim_image[0]; i++) //Initialisation matrice de Hough
    {
        std::vector<int> ligne;
        for (int j = 0; j < dim_image[1]; j++)
        {
            ligne.push_back(0);
        }
        Matrice_Hough.push_back(ligne);
    }

    for(int i = 0; i < dim_image[0]; i++) // 
    {
        double valeur_abscisse = (i-ordon_orig[0])/coef_dir; // On détermine l'abscisse à ordonné fixée
        int partie_entiere_inf = int(floor(valeur_abscisse)); // On prend la partie entière inférieure

        if (valeur_abscisse < 0 || valeur_abscisse > dim_image[1]) 
        {
            continue; // passe à l'itération suivante
        }else{
            if (valeur_abscisse > partie_entiere_inf + 0.5) // Nous informe à quel colonne on met un 1 (pixel à gauche ou à droite du segment)
            {
                Matrice_Hough[i][partie_entiere_inf+1] = 1; 
            }else{
                Matrice_Hough[i][partie_entiere_inf] = 1;
            }
        }

    }
    
    return Matrice_Hough;
}

//Fonction 4

// On regarde combien de droites parmi celle donné en entrée passent par chaque pixel
std::vector<std::vector<int>> Tf_Hough_finale(std::vector<double> coeff_dir, std::vector<std::vector<int>> ordonn_orig, std::vector<int> dim_image) // La longeur des deux vecteurs doit être la même
{
    std::vector<std::vector<int>> Tf_Hough_finale;

    for (int i = 0; i < dim_image[0]; i++) //Initialisation matrice de Hough finale
    {
        std::vector<int> ligne;
        for (int j = 0; j < dim_image[1]; j++)
        {
            ligne.push_back(0);
        }
        Tf_Hough_finale.push_back(ligne);
    }

    for(int i = 0; i < coeff_dir.size(); i++)
    {
        std::vector<int> tmp; // On crée le i-ème point d'ordonné à l'origine lié au i-ème coefficient directeur.
        tmp.push_back(ordonn_orig[i][0]);
        tmp.push_back(ordonn_orig[i][1]);
        std::vector<std::vector<int>> Mat_a_addition = Tf_Hough_a_couple_donnee(coeff_dir[i], tmp, dim_image);

        for (int j = 0; j < dim_image[0]; j++) // On fait une addition de matrice
        {
            for (int k = 0; k < dim_image[1]; k++)
            {
            Tf_Hough_finale[j][k] = Tf_Hough_finale[j][k] + Mat_a_addition[j][k];
            }
        }
    }

    return Tf_Hough_finale;
}

//Fonction 5

std::vector<int> Tf_retour(std::vector<std::vector<int>> Mat_Hough, std::vector<int> dim_image)
{
    int maximum = Mat_Hough[0][0];
    std::vector<int> coordonnees_max;
    coordonnees_max.push_back(0);
    coordonnees_max.push_back(0);

    for (int i = 0; i < dim_image[0]; i++)
    {
        for (int j = 0; j < dim_image[1]; j++)
        {
            if (Mat_Hough[i][j] > maximum)
            {
                maximum = Mat_Hough[i][j];
                coordonnees_max[0] = i;
                coordonnees_max[1] = j;

            }
        }
    }

    return coordonnees_max;
}

//Fonction 6

std::vector<std::vector<int>> rpz_droite_matrice(std::vector<int> coordonnees, std::vector<int> dim_image)
{
    std::vector<std::vector<int>> droite_mat;
    for (int i = 0; i < dim_image[0]; i++) //Initialisation matrice de Hough finale
    {
        std::vector<int> ligne;

        for (int j = 0; j < dim_image[1]; j++)
        {
            ligne.push_back(0);
        }
        droite_mat.push_back(ligne);
    }

    for(int i = 0; i < dim_image[0]; i++) // 
    {
        double valeur_abscisse = (i-coordonnees[1])/coordonnees[0]; // On détermine l'abscisse à ordonné fixée
        int partie_entiere_inf = int(floor(valeur_abscisse)); // On prend la partie entière inférieure

        if (valeur_abscisse < 0 || valeur_abscisse > dim_image[1]) 
        {
            continue; // passe à l'itération suivante
        }else{
            if (valeur_abscisse > partie_entiere_inf + 0.5) // Nous informe a quel colonne on met un 1 (pixel à gauche ou à droite du segment)
            {
                droite_mat[i][partie_entiere_inf+1] = 1; 
            }else{
                droite_mat[i][partie_entiere_inf] = 1;
            }
        }

    }

    return droite_mat;
}