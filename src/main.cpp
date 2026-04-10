#include <iostream>
#include "stb_image.h"
#include <string>
#include <limits>
#include <random>
#include <SFML/Graphics.hpp>

int main()
{
    int width, height, channels;

    unsigned char* image = stbi_load("../../assets/basket.jpg", &width, &height, &channels, 0);
    if (!image) {
        std::cerr << "Erreur : " << stbi_failure_reason() << "\n";
        return 1;
    }

    std::cout << "Image : " << width << "x" << height << " (" << channels << " canaux)\n\n";

    // ====================== CONFIGURATION ======================
    const int OUTPUT_WIDTH = 210;                    // Largeur en caractères (change selon ta console)
    const int BLOCK_SIZE = 2;                        // 2 = bloc 2x2, 4 = bloc 4x4 (plus doux mais plus lent)

    // Calcul de la hauteur en gardant les proportions + correction terminal (caractères plus hauts que larges)
    int output_height = static_cast<int>(
        (static_cast<double>(height) / width) * OUTPUT_WIDTH * 0.55   // 0.55 au lieu de 0.5 → souvent mieux
    );
    if (output_height < 1) output_height = 1;

    const std::string RAMP = " .:-=+*#%@";   // Rampe simple pour commencer

    // ====================== GÉNÉRATION ASCII ======================
    for (int ascii_y = 0; ascii_y < output_height; ++ascii_y) {
        for (int ascii_x = 0; ascii_x < OUTPUT_WIDTH; ++ascii_x) {

            // Coordonnées du bloc dans l'image originale
            int start_x = (ascii_x * width) / OUTPUT_WIDTH;
            int start_y = (ascii_y * height) / output_height;

            // On va additionner tous les pixels du bloc
            long long sum_r = 0, sum_g = 0, sum_b = 0;
            int pixel_count = 0;

            // Boucle sur le bloc (ex: 2x2)
            for (int dy = 0; dy < BLOCK_SIZE; ++dy) {
                for (int dx = 0; dx < BLOCK_SIZE; ++dx) {
                    int px = start_x + dx;
                    int py = start_y + dy;

                    // On reste dans les limites de l'image
                    if (px >= width || py >= height) continue;

                    int index = (py * width + px) * channels;

                    if (channels >= 3) {
                        sum_r += image[index];
                        sum_g += image[index + 1];
                        sum_b += image[index + 2];
                    } else {
                        // Image en niveaux de gris
                        sum_r += image[index];
                        sum_g += image[index];
                        sum_b += image[index];
                    }
                    pixel_count++;
                }
            }

            // Moyenne des couleurs
            unsigned char const r = (pixel_count > 0) ? static_cast<unsigned char>(sum_r / pixel_count) : 0;
            unsigned char const g = (pixel_count > 0) ? static_cast<unsigned char>(sum_g / pixel_count) : 0;
            unsigned char const b = (pixel_count > 0) ? static_cast<unsigned char>(sum_b / pixel_count) : 0;

            // Conversion en gris (luminosité perçue par l'œil)
            unsigned char const gray = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);

            // Choix du caractère selon la luminosité
            size_t ramp_index = static_cast<size_t>((255 - gray) * RAMP.size() / 256);
            std::cout << RAMP[ramp_index];
        }
        std::cout << "\n";
    }

    stbi_image_free(image);

    std::cout << "\nTermine ! Appuie sur Entree...\n";
    std::cin.get();
    return 0;
}