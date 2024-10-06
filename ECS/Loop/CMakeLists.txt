set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

add_library(
    Loop
    loop.cpp
)

target_link_libraries(Loop Time)