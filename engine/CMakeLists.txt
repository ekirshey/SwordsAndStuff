cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

project(SAS_ENGINE)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../cmake")

find_package(SDL2)
find_package(SDL2_image)
find_package(SDL2_ttf)

message("${CMAKE_BINARY_DIR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Using cmd line settings to determine media path until I set up config files
OPTION(LAPTOP "Option description" OFF) 

IF(LAPTOP)
    ADD_DEFINITIONS(-DLAPTOP)
ENDIF(LAPTOP)

add_subdirectory(SAS_System/src)
add_subdirectory(SAS_GUI/src)
add_subdirectory(SAS/src)
add_subdirectory(SAS_TEST/src)
