#include "ppm_image.hpp"

using namespace std;

void ppm_image::PPMImage(const string& filename) {
    // Ouverture du fichier en mode binaire
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << endl;
        return;
    }

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
                return;
            }
            magic_number_read = true;
        } else if (!dimensions_read) {
            if (!(iss >> width >> height)) {
                cerr << "Erreur : Impossible de lire les dimensions" << endl;
                return;
            }
            dimensions_read = true;
        } else if (!max_value_read) {
            if (!(iss >> max_value)) {
                cerr << "Erreur : Impossible de lire la valeur maximale" << endl;
                return;
            }
            max_value_read = true;
        } else {
            break; // Fin de l'en-tête
        }
    }

    if (magic_number != "P3" || max_value != 255) {
        cerr << "Erreur : Format de fichier non supporté" << endl;
        return;
    }

    // Lecture des données de l'image
    int r, g, b;
    while (file >> r >> g >> b) {
        m_data.push_back(r);
        m_data.push_back(g);
        m_data.push_back(b);
    }

    // Vérification de la taille des données
    if (m_data.size() != m_width * m_height * 3) {
        cerr << "Erreur : Taille des données incorrecte" << endl;
        m_data.clear();
        m_width = 0;
        m_height = 0;
    }
}

