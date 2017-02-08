# Locate the SDL2_ttf library. This CMake module is a modified version
# of the original FindSDL_ttf.cmake file
# ###########################################################################
# Locate SDL_ttf library
# This module defines
# SDL2TTF_LIBRARY, the name of the library to link against
# SDLTTF_FOUND, if false, do not try to link to SDL
# SDL2TTF_INCLUDE_DIR, where to find SDL/SDL.h
#
# $SDLDIR is an environment variable that would
# correspond to the ./configure --prefix=$SDLDIR
# used in building SDL.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake 
# module, but with modifications to recognize OS X frameworks and 
# additional Unix paths (FreeBSD, etc).

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distributed this file outside of CMake, substitute the full
#  License text for the above reference.)

FIND_PATH(SDL2TTF_INCLUDE_DIR
  NAMES SDL_ttf.h
  HINTS
  $ENV{SDL2TTFDIR}
  PATH_SUFFIXES include
)

FIND_LIBRARY(SDL2TTF_LIB 
  NAMES SDL2_ttf
  HINTS
  $ENV{SDL2TTFDIR}
  PATH_SUFFIXES lib64 lib/x64
)

FIND_LIBRARY(SDL2TTF_LIB_DBG
  NAMES SDL2_ttf_d
  HINTS
  $ENV{SDL2TTFDIR}
  PATH_SUFFIXES lib64 lib/x64
)

mark_as_advanced(SDL2TTF_LIB SDL2TTF_LIB_DBG SDL2TTF_INCLUDE_DIR)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2TTF REQUIRED_VARS SDL2TTF_LIB SDL2TTF_INCLUDE_DIR)

# set up output vars
if (SDL2TTF_FOUND)
    set (SDL2TTF_INCLUDE_DIR ${SDL2TTF_INCLUDE_DIR})
    set (SDL2TTF_LIBRARIES ${SDL2TTF_LIB})
    if (SDL2TTF_LIB_DBG)
        set (SDL2TTF_LIBRARIES_DBG ${SDL2TTF_LIB_DBG})
    endif()
    if (SDL2TTF_LIB_STATIC)
        set (SDL2TTF_LIBRARIES_STATIC ${SDL2TTF_LIB_STATIC})
    endif()
    if (SDL2TTF_LIB_STATIC_DBG)
        set (SDL2TTF_LIBRARIES_STATIC_DBG ${SDL2TTF_LIB_STATIC_DBG})
    endif()
else()
    set (SDL2TTF_INCLUDE_DIR)
    set (SDL2TTF_LIBRARIES)
    set (SDL2TTF_LIBRARIES_DBG)
    set (SDL2TTF_LIBRARIES_STATIC)
    set (SDL2TTF_LIBRARIES_STATIC_DBG)
endif()