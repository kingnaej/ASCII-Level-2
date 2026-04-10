#include <iostream>
#include "stb_image.h"
#include <SFML/Graphics.hpp>   // tu l'as inclus, on le garde pour plus tard si tu veux afficher l'image normalement
#include <string>
#include <filesystem>
#include <vector>
#include <random>
#include <string>
#include <limits>

// ====================== PARAMÈTRES DE L'ASCII ART ======================
const std::string RAMP = " .:-=+*#%@";   // du plus clair (espace) au plus foncé (@)
// Plus il y a de caractères, plus c'est détaillé (tu peux en ajouter)

int main()
{
    int width, height, channels;   // noms standards (plus clair que hauteur/largeur)

    // Chargement de l'image
    unsigned char* image = stbi_load("../../assets/KN.jpeg", &width, &height, &channels, 0);
    if (!image) {
        std::cerr << "Erreur de chargement : " << stbi_failure_reason() << "\n";
        return 1;
    }

    // ====================== CONFIGURATION ASCII ======================
    const int OUTPUT_WIDTH = 210;                    // nombre de caractères par ligne (ajuste selon ta console)
    // On calcule la hauteur en gardant les proportions + correction aspect ratio
    // (les caractères sont environ 2 fois plus hauts que larges)
    int output_height = static_cast<int>(
        (static_cast<double>(height) / width) * OUTPUT_WIDTH * 0.5
    );
    if (output_height < 1) output_height = 1;

    // ====================== AFFICHAGE ASCII ======================
    for (int ascii_y = 0; ascii_y < output_height; ++ascii_y) {
        for (int ascii_x = 0; ascii_x < OUTPUT_WIDTH; ++ascii_x) {

            // On prend un pixel représentatif dans l'image originale
            // (sous-échantillonnage = on ne prend pas tous les pixels)
            const int pixel_x = (ascii_x * width) / OUTPUT_WIDTH;
            const int pixel_y = (ascii_y * height) / output_height;

            // Calcul de l'index dans le tableau de pixels
            const int index = (pixel_y * width + pixel_x) * channels;

            unsigned char gray;   // valeur de luminosité 0 (noir) → 255 (blanc)

            if (channels == 1) {
                // Image déjà en niveaux de gris
                gray = image[index];
            } else {
                // Image couleur (RGB ou RGBA)
                const unsigned char r = image[index];
                const unsigned char g = image[index + 1];
                unsigned char const b = image[index + 2];

                // Formule de luminance (pondération selon l'œil humain)
                gray = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
            }

            // Mapping luminosité → caractère de la rampe
            const size_t ramp_index = static_cast<size_t>((255 - gray) * RAMP.size() / 256);
            std::cout << RAMP[ramp_index];
        }
        std::cout << "\n";   // fin de ligne
    }

    stbi_image_free(image);

    std::cout << "\nProgramme termine.\n";
    std::cout << "Appuyer sur Entrer pour fermer...\n";
    std::cin.get();

    return 0;
}