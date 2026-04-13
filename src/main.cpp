#include <iostream>
#include "stb_image.h"
#include <string>
#include <limits>
#include <random>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <map>
#include <algorithm>
#include <cctype>

int main()
{
    std::string const folderPath = "../../assets";
    std::map<int, std::filesystem::path> files;
    if (std::filesystem::exists(folderPath)) {
        int file_count = 0;
        for (auto const &file : std::filesystem::directory_iterator(folderPath)) {
            if (std::filesystem::is_regular_file(file)) {
                std::string ext = file.path().extension().string();

                // Conversion en minuscules (insensible à la casse)
                std::ranges::transform(
                    ext, ext.begin(), [](unsigned char const c) {
                        return std::tolower(c);
                    }
                );

                if (ext == ".png" || ext == ".jpg" || ext == ".jpeg") {
                    files[file_count] = file.path();
                    ++file_count;
                }
            }
        }
    }
    else {
        std::cout << "This Path doesn't exist !" << std::endl;
    }

    // for (auto const &[Key, Value] : files) {
    //     std::cout << Key << " ==> " << Value << "\n";
    // }

    if (files.empty()) {
        std::cout << "Aucune image trouvée dans le dossier !" << std::endl;
        return 1;
    }

    // LA PARTIE RANDOM

    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<int> distribution(0, static_cast<int>(files.size()) - 1);

    // PARTIE GENERATEUR DE CODE ASCII

    const std::string RAMP = " .:-=+*#%@";
    int width, height, channels;

    auto const keyFile = distribution(random_engine);
    const auto file = files.at(keyFile).string();

    unsigned char* image = stbi_load(file.c_str(), &width, &height, &channels, 0);
    if (!image) {
        std::cerr << "Erreur : " << stbi_failure_reason() << "\n";
        return 1;
    }

    int const OUTPUTWIDTH = 210;
    int OUTPUTHEIGHT = static_cast<int>(
        static_cast<double> (height / width) * OUTPUTWIDTH * 0.55
    );
    if (OUTPUTHEIGHT < 1) OUTPUTHEIGHT = 1;

    for (auto ascii_y = 0; ascii_y < OUTPUTHEIGHT; ++ascii_y) {
        for (auto ascii_x = 0; ascii_x < OUTPUTWIDTH; ++ascii_x) {
            int const BLOCK = 2;
            int const start_x = (ascii_x * width) / OUTPUTWIDTH;
            int const start_y = (ascii_y * height) / OUTPUTHEIGHT;

            long long sum_r = 0, sum_g = 0, sum_b = 0;
            int pixel_count = 0;

            for (int dy = 0; dy < BLOCK; ++dy) {
                for (int dx = 0; dx < BLOCK; ++dx) {
                    int const px = start_x + dx;
                    int const py = start_y + dy;

                    if (py >= height || px >= width) continue;

                    int const index = (py * width + px) * channels;

                    if (channels >= 3) {
                        sum_r += image[index];
                        sum_g += image[index + 1];
                        sum_b += image[index + 2];
                    }
                    else {
                        sum_r += image[index];
                        sum_g += image[index];
                        sum_b += image[index];
                    }
                    pixel_count++;
                }
            }

            unsigned const char r = pixel_count > 0 ? static_cast<unsigned char>(sum_r / pixel_count) : 0;
            unsigned const char g = pixel_count > 0 ? static_cast<unsigned char>(sum_g / pixel_count) : 0;
            unsigned const char b = pixel_count > 0 ? static_cast<unsigned char>(sum_b / pixel_count) : 0;

            unsigned const char gray = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
            size_t const ramp_index = (255 - gray) * RAMP.size() / 256;
            std::cout << RAMP[ramp_index];
        }
        std::cout << "\n";
    }
    stbi_image_free(image);
    std::cout << "\nCliquez sur la touche 'Entrer' pour quitter le programme" << std::endl;
    std::cin.get();

    return 0;
}