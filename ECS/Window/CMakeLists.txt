set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

add_library(
    Window STATIC
    window.cpp
)

target_link_libraries(Window PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)