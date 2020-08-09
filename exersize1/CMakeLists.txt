cmake_minimum_required(VERSION 3.0)

project(exersize1 VERSION 3.3.2)

find_package(GLFW)
include_directories(${GLFW_INCLUDE_DIRS})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SRC_FILES
	${GLFW_INCLUDE_DIRS}/gladsrc/glad.c
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

if(GLFW_FOUND)
	target_link_libraries(${PROJECT_NAME} ${GLFW_RELEASE_LIBRARIES})
endif(GLFW_FOUND)