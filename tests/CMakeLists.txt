cmake_minimum_required(VERSION 3.10)

# Project name
project("test.out" VERSION 0.1 LANGUAGES CXX C)

# Set CMake module path and C++ standard
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)

# Set debug flags and compile commands export
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -ggdb -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set executable output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Add executable
add_executable(${PROJECT_NAME} opengl.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Add GLAD library
add_library(glad STATIC glad/src/glad.c)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw dl)