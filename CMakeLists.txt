cmake_minimum_required(VERSION 3.20)

project(sym-graphs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(external/raylib)
add_subdirectory(external/ogdf)

set(SRC ./src/main.cpp ./src/app.cpp ./src/graph.cpp src/parser/parser.cpp)

add_executable(sym-graphs ${SRC})

target_link_libraries(sym-graphs PRIVATE raylib OGDF)
target_include_directories(sym-graphs PRIVATE src external)

if(UNIX AND NOT APPLE)
  target_link_libraries(sym-graphs PRIVATE pthread m dl X11)
endif()
