cmake_minimum_required(VERSION 3.21)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(Minesweeper main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ./SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(.SFML/include)
target_link_libraries(Minesweeper sfml-system sfml-window sfml-graphics sfml-audio sfml-network)