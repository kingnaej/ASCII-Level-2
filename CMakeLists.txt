cmake_minimum_required(VERSION 4.1)
project(Level2)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Si CMake ne trouve pas SFML automatiquement sur UCRT64
# set(SFML_DIR "/ucrt64/lib/cmake/SFML")

# SFML est trouvé une seule fois ici, puis utilisé dans src/
find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_subdirectory(src)