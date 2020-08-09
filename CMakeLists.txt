cmake_minimum_required(VERSION 3.0)

project(GLFW_PRO VERSION 3.3.2)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake/modules;${CMAKE_MODULE_PATH}")
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/IncludeFiles)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(first)
add_subdirectory(exersize1)
add_subdirectory(exersize2)
