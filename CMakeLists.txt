cmake_minimum_required(VERSION 4.1)
project(Level2)

set(CMAKE_CXX_STANDARD 26)

# Ajouter le dossier headers (si tu as des headers customs)
include_directories(headers)

# Ajouter le dossier src
add_subdirectory(src)