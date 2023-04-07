#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

# Fonction 1
double coefficient_directeur(std::vector<int> A, std::vector<int> B)
{
    double coef_dir;
    coef_dir = (B[1]-A[1])/(B[0]-A[0]); // Calcul du coefficient directeur

    return coef_dir;
}

# Fonction 2

std::vector<int> ordonne_origine(double coeff_dir, std::vector<int> A)
{
    std::vector<int> ordon_orig(2,0);
    ordon_orig[1] = 0;
    ordon_orig[0] = A[0]-coeff_dir*A[1];

    return ordon_orig;
}

# Fonction 3

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

# Fonction 4

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

# Fonction 5

int Tf_retour(std::vector<std::vector<int>> Mat_Hough, std::vector<int> dim_image)
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

# Fonction 6

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

# Fonction 7

bool compare_pixel(std::vector<int> pix_1, std::vector<int> pix_2)
{
    if (pix_1.size() != pix_2.size())   
    {
        cerr << "Erreur : Probmèmes de dimensions des pixels" << endl;
        return false;
    }

    for(int i = 0; i < pix_1.size(); i++)
    {
        if (pix_1[i] != pix_2[i])
        {
            return false;
        }
    }

    return true;
}

# Fonction 8

// Renvoi une matrice donnant les pixels de même couleurs
std::vector<std::vector<int>> matrice_couleur_similaire(std::vector<std::vector<std::vector<int>>> mat_pixel, std::vector<int> dim_image)
{
    std::vector<std::vector<int>> m_c_s;

    for (int i = 0; i < dim_image[0]; i++) //Initialisation matrice de Hough
    {
        std::vector<int> ligne;

        for (int j = 0; j < dim_image[1]; j++)
        {
            ligne.push_back(0);
        }
        m_c_s.push_back(ligne);
    }

    
    for (int i = 0; i < dim_image[0]; i++)
    {
        
        for(int j = 0; j < dim_image[1]; j++)
        {
            if (compare_pixel(mat_pixel[0][0], mat_pixel[i][j]) == true)
            {
                m_c_s[i][j] =  1;
            }
        }
    }

    return m_c_s;
}

# Main 

int main() {

    std::vector<std::vector<std::vector<int>>> Image;
    int noir = 0;
    int blanc = 255;

    for (int i = 0; i < 3; i++)
    {
        std::vector<std::vector<int>> ligne;
        for (int j = 0; j < 3; j++)
        {
            std::vector<int> pix;
            if (((i+j)%2) == 0)
            {
                for(int k = 0; k < 3; k++)
                {
                    pix.push_back(blanc);
                }
            }else{
                for(int k = 0; k < 3; k++)
                {
                    pix.push_back(noir);
                }            
            }
            ligne.push_back(pix);
        }
        Image.push_back(ligne);
    }

   /* for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                std::cout << Image[i][j][k] << " ";
            }
            std::cout << ", ";
        }
        std::cout << endl;
    }*/

    std::vector<int> dim = {3,3};
    std::vector<std::vector<int>> M = matrice_couleur_similaire(Image, dim);
/*
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;

    }
*/


    std::vector<int> A = {3, 0};
    std::vector<int> B = {0, 3};
    std::vector<int> C = {2,1};
    std::vector<int> D = {3,2};

    double m1 = coefficient_directeur(A,B);
    std::vector<int> o1 = ordonne_origine(m1, A);
    double m2 = coefficient_directeur(C,D);
    std::vector<int> o2 = ordonne_origine(m2, C);

    std::vector<double> m = {m1, m2};
    std::vector<std::vector<int>> o;
    o.push_back(o1);
    o.push_back(o2);


   //  std::cout << m << ", (" << o[0] << ", " << o[1] << ")" << std::endl;


    std::vector<int> dim_image(5,5);
    std::vector<std::vector<int>> Tf_Hough = Tf_Hough_finale(m, o, dim_image);
    std::vector<int> retour = Tf_retour(Tf_Hough, dim_image);
    std::vector<std::vector<int>> rpz = rpz_droite_matrice(retour, dim_image);
    
    for(int i = 0; i < dim_image[0]; i++)
    {
        for(int j = 0; j < dim_image[1]; j++)
        {
            std::cout << rpz[i][j] << " ";
        }

        std::cout << std::endl;
    }
    
    return 0;
}
