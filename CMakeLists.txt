cmake_minimum_required(VERSION 3.16)

project(TowerDefence)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

add_executable(TowerDefense
    src/main.cpp
)

target_link_libraries(TowerDefense
    PkgConfig::SDL2
)
