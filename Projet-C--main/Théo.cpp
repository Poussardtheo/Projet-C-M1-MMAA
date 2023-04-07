#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>

using namespace std;

// Fonction qui affiche l'image PPM sous forme matricielle
vector<vector<array<int, 3>>> recupererMatriceImagePPM(const string& filename) {
    // Ouverture du fichier en mode binaire
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << endl;
        return {};
    }
    
    // Lecture des informations de l'en-tête
        // Lecture des informations de l'en-tête
    string line;
    string magic_number;
    int width, height, max_value;
    bool magic_number_read = false, dimensions_read = false, max_value_read = false;
    while (getline(file, line)) {
        // Ignorer les lignes de commentaire qui commencent par #
        if (line[0] == '#') {
            continue;
        }
        
        // Extraire les informations de l'en-tête
        istringstream iss(line);
        if (!magic_number_read) {
            if (!(iss >> magic_number)) {
                cerr << "Erreur : Impossible de lire le nombre magique" << endl;
                return {};
            }
            magic_number_read = true;
        } else if (!dimensions_read) {
            if (!(iss >> width >> height)) {
                cerr << "Erreur : Impossible de lire les dimensions" << endl;
                return {};
            }
            dimensions_read = true;
        } else if (!max_value_read) {
            if (!(iss >> max_value)) {
                cerr << "Erreur : Impossible de lire la valeur maximale" << endl;
                return {};
            }
            max_value_read = true;
        } else {
            break; // Fin de l'en-tête
        }
    }
        
    if (magic_number != "P3" || max_value != 255) {
        cerr << "Erreur : Format de fichier non supporté" << endl;
        return {};
    }
    
    // Lecture des données de l'image
    vector<vector<array<int, 3>>> pixels(height, vector<array<int, 3>>(width));

    // Parcours du reste du fichier pour récupérer les valeurs RGB de chaque pixel
    int i = 0, j = 0, k = 0;
    int r, g, b;
    while (file >> r >> g >> b) {
        pixels[i][j][0] = r;
        pixels[i][j][1] = g;
        pixels[i][j][2] = b;

        // Passage au pixel suivant
        k++;
        j++;
        if (k % width == 0) {
            i++;
            j = 0;
        }
    }

    return pixels;
}



bool comparerPixels(const vector<vector<vector<unsigned char>>>& pixels, int x1, int y1, int x2, int y2) {
    // Vérification des coordonnées
    int height = pixels.size();
    int width = pixels[0].size();
    if (x1 < 0 || x1 >= width || y1 < 0 || y1 >= height || x2 < 0 || x2 >= width || y2 < 0 || y2 >= height) {
        cerr << "Erreur : Coordonnées de pixel invalides" << endl;
        return false;
    }
    
    // Comparaison des valeurs RGB
    for (int c = 0; c < 3; ++c) {
        if (pixels[y1][x1][c] != pixels[y2][x2][c]) {
            return false;
        }
    }
    
    return true;
}

int main(){
    // Nom du fichier PPM
    string filename = "m1projetcpp2.ppm";
    
    // Récupération de la matrice des pixels de l'image
    auto matrice_pixels = recupererMatriceImagePPM(filename);
    
    // Affichage de la matrice des pixels
    for (const auto& ligne : matrice_pixels) {
        for (const auto& pixel : ligne) {
            cout << "(" << pixel[0] << ", " << pixel[1] << ", " << pixel[2] << ") ";
        }
        cout << endl;
    }
    
    /*bool resultat = comparerPixels(pixels, 0, 0, 1, 0);
    if (resultat) {
        cout << "Les pixels sont identiques" << endl;
    } else {
        cout << "Les pixels sont différents" << endl;
    }*/

    return 0;
}
