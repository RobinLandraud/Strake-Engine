# Specify the minimum version for CMake
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# Project's name
PROJECT("Strake.out" VERSION 0.1.0 LANGUAGES CXX)

# Specify the C++ standard
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_BUILD_TYPE "Release")

# Set compiler flags for Debug build
#set(CMAKE_CXX_FLAGS_DEBUG "-g3 -ggdb -O0")

# Set compiler flags for Release build
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release build")
    if (MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "/O2")
    else()
        set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    endif()
else()
    message("Debug build")
    if (MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "/Od")
    else()
        set(CMAKE_CXX_FLAGS_DEBUG "-O0")
    endif()
endif()

# Add the compile commands to the output
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Add include directory for ECS
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ECS/include)

cmake_policy(SET CMP0072 NEW) # FindOpenGL prefers GLVND by default when available

# find_package(Threads REQUIRED)
message("Finding Packages")

if (WIN32)
    if (NOT DEFINED VCPKG_ROOT)
        message(FATAL_ERROR "Please define VCPKG_ROOT environment variable")
    endif()
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")
    set(CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed/x64-windows/share")
    include_directories("${VCPKG_ROOT}/installed/x64-windows/include")
    message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
    include_directories(${GLM_INCLUDE_DIRS})
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
message("Found Packages")

add_subdirectory(ECS)

# Add executable target with source files listed in SOURCE_FILES variable
ADD_EXECUTABLE(
    ${PROJECT_NAME}
    main.cpp
)

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${VCPKG_ROOT}/installed/x64-windows/bin/glfw3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${VCPKG_ROOT}/installed/x64-windows/bin/glew32.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    else()
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${VCPKG_ROOT}/installed/x64-windows/debug/bin/glew32d.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ECS)