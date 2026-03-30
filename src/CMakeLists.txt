set(SOURCES
        main.cpp
        stb_image.cpp
)

# Créer l’exécutable
add_executable(Level2 ${SOURCES})

target_include_directories(Level2 PRIVATE
        ${PROJECT_SOURCE_DIR}/headers
)

target_link_libraries(Level2 PRIVATE SFML::Graphics)