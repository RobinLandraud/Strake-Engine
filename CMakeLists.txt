# Specify the minimum version for CMake
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# Project's name
PROJECT("Ghost" VERSION 0.1 LANGUAGES CXX)


# Specify the C++ standard
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler flags for Debug build
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -ggdb -O0")

# Set compiler flags for Release build
## set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Add the compile commands to the output
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Add executable target with source files listed in SOURCE_FILES variable
ADD_EXECUTABLE(
    ${PROJECT_NAME}
    main.cpp
)

#find sfml
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
# add subdirectories and packages here
add_subdirectory(ECS)

#link sfml
target_link_libraries(${PROJECT_NAME} ECS)