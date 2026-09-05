cmake_minimum_required(VERSION 3.16)

project(TowerDefence)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_TTF REQUIRED IMPORTED_TARGET SDL2_ttf)

add_executable(TowerDefense
    src/main.cpp
)

target_link_libraries(TowerDefense
    PkgConfig::SDL2
    PkgConfig::SDL2_TTF
)
