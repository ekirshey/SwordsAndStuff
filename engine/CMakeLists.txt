cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

project(SAS_ENGINE)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../cmake")

find_package(SDL2)
find_package(SDL2_image)
find_package(SDL2_ttf)

add_subdirectory(SAS_System)
add_subdirectory(SAS_GUI)
add_subdirectory(SAS)