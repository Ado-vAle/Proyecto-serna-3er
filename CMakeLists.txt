cmake_minimum_required(VERSION 3.16)
project(Puzzle8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Descarga raylib automáticamente desde GitHub
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
    GIT_SHALLOW TRUE
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

add_executable(puzzle8
    src/main.cpp
    src/Button.cpp
    src/MenuManager.cpp
)

# Carpeta de headers del proyecto
target_include_directories(puzzle8 PRIVATE include)
target_link_libraries(puzzle8 PRIVATE raylib)