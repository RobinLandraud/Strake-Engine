set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)

add_library(
    ECS
    config.cpp
)

add_subdirectory(Time)
add_subdirectory(Window)
add_subdirectory(Loop)

target_link_libraries(ECS PRIVATE
    Time
    Window
    Loop
)

target_include_directories(ECS PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)