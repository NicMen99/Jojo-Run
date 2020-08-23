cmake_minimum_required(VERSION 3.15)

project(JoJo_Run)
set(CMAKE_CXX_STANDARD 11)

set(TARGET JoJoRun)

add_executable(${TARGET} "" Src/Game.h Src/Game.cpp)

#
# SFML2, OPENGL
#

# OPENGL not enabled at the moment
# find_package (OPENGL REQUIRED)
# find_package (GLUT REQUIRED)
# find_package (GLEW REQUIRED)

# Configuration options
set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML librares")
# General compiler options
if (SFML_STATIC_LIBRARIES)
    add_definitions(-DSFML_STATIC)
endif()
# Add directory containing FindSFML.cmake to module path
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")
find_package(SFML 2 COMPONENTS audio graphics window system network)
# If found, include and link; otherwise output error message
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else()
    set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
    message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
    message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

message("SFML_FOUND: " ${SFML_FOUND})
message("SFML_INCLUDE_DIR: " ${SFML_INCLUDE_DIR})
message("SFML_LIBRARIES: " ${SFML_LIBRARIES})
message("SFML_DEPENDENCIES: " ${SFML_DEPENDENCIES})


#
# Components
#
add_subdirectory(Src)
add_subdirectory(Test)
