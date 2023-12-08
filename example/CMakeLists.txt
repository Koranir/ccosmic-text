cmake_minimum_required(VERSION 3.5.0)

project(
    CCosmicTextExample
    VERSION 0.0.1
    LANGUAGES C
)

link_directories(${CMAKE_SOURCE_DIR}/../target/lib)

add_executable(
    CCosmicTextExample
    src/main.c
)
find_package(SDL2)
target_link_libraries(CCosmicTextExample ccosmic_text SDL2::SDL2 SDL2::SDL2main)
target_include_directories(CCosmicTextExample PUBLIC ${CMAKE_SOURCE_DIR}/../target/lib)
