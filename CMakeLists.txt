###############################################################
### CMake minimum version
###############################################################
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

###############################################################
### Project name
###############################################################
PROJECT("StrakeEngine" VERSION 0.1.0 LANGUAGES CXX)

###############################################################
### C++ standard
###############################################################
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_EXTENSIONS OFF)

###############################################################
### Output directories
###############################################################
if(WIN32)
    # Multi-config Windows (Visual Studio)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/Debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/Release)
    set(OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CMAKE_BUILD_TYPE}})
else()
    # Linux / Makefile / Ninja
    # Create a Build/Debug or Build/Release folder
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release")  # Default if not specified
    endif()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_BUILD_TYPE})
    set(OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

message("[X] Output path: ${OUTPUT_PATH}")

###############################################################
### Compiler flags
###############################################################
# Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS_DEBUG_INIT} ")
if(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
endif()
# Release
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_CXX_FLAGS_RELEASE_INIT} ")
if(WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()


###############################################################
### Generate compile_commands.json
###############################################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###############################################################
### Include Strake engine
###############################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Strake/include)


###############################################################
### Find packages
###############################################################
# Si VCPKG est dispo, configure le toolchain
if(WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Please provide -DCMAKE_TOOLCHAIN_FILE on Windows (vcpkg).")
else()

endif()

# Threads (Linux/macOS only, Windows n’en a pas besoin)
if (NOT WIN32)
    find_package(Threads REQUIRED)
endif()

# update resources path to executable output directory
set("STRAKE_RESOURCES" "${CMAKE_CURRENT_SOURCE_DIR}/Resources")
message("[X] Resources will be copied to: ${STRAKE_RESOURCES}")
set(DEFAULT_STRAKE_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/Strake/resources")
file(COPY ${DEFAULT_STRAKE_RESOURCE}/. DESTINATION ${STRAKE_RESOURCES})


message("[X] Adding library: Strake Engine")
add_subdirectory(Strake)

# Add executable target with source files listed in SOURCE_FILES variable
ADD_EXECUTABLE(
    ${PROJECT_NAME}
    main.cpp
)

if(WIN32)
    # vcpkg bin folder
    get_filename_component(VCPKG_ROOT_DIR "${CMAKE_TOOLCHAIN_FILE}" DIRECTORY)
    set(VCPKG_BIN_DIR "${VCPKG_ROOT_DIR}/../../installed/x64-windows/bin")
    set(VCPKG_DEBUG_BIN_DIR "${VCPKG_ROOT_DIR}/../../installed/x64-windows/debug/bin")

    # DLLs standard
    set(DLLS
        glfw3.dll
        assimp-vc143-mt.dll
        minizip.dll
        zlib1.dll
        pugixml.dll
        poly2tri.dll
    )

    foreach(dll ${DLLS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "[X] Copying ${dll} to $<TARGET_FILE_DIR:${PROJECT_NAME}>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${VCPKG_BIN_DIR}/${dll}"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endforeach()

    # Copy GLEW dll depending on build configuration
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "[X] Copying GLEW dll for $<CONFIG> configuration"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<IF:$<CONFIG:Debug>,${VCPKG_DEBUG_BIN_DIR}/glew32d.dll,${VCPKG_BIN_DIR}/glew32.dll>"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC Strake)