cmake_minimum_required(VERSION 3.10)

project(myGL)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Shaders STATIC src/Shaders/Shaders.cpp)

add_library(myGL STATIC ${CMAKE_CURRENT_SOURCE_DIR}/myGL.cpp)

target_include_directories(myGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Shaders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(myGL PUBLIC Shaders)