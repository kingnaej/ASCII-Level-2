set(SOURCES
        main.cpp
        stb_image.cpp
)

# Créer l’exécutable
add_executable(Level2 ${SOURCES})

target_include_directories(Level2 PRIVATE
        ${PROJECT_SOURCE_DIR}/headers
)

# 1. On installe l'exécutable dans un dossier 'bin'
install(TARGETS Level2 DESTINATION bin)

# 2. On installe le dossier data juste à côté
install(DIRECTORY "${CMAKE_SOURCE_DIR}/assets" DESTINATION bin)
