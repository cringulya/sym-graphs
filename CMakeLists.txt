cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0167 NEW)

project(sym-graphs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Freetype REQUIRED)
find_package(Boost 1.82 REQUIRED COMPONENTS filesystem system)
find_package(PNG REQUIRED)

file(GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.cpp
     ${CMAKE_SOURCE_DIR}/shared/Core/*.cpp)

add_executable(sym-graphs ${SRC})

target_link_libraries(
  sym-graphs
  PRIVATE GLEW::glew
          OpenGL::GL
          SDL2::SDL2
          SDL2_image
          Freetype::Freetype
          Boost::filesystem
          Boost::system
          PNG::PNG
          -lpcre2-8)

target_include_directories(sym-graphs PRIVATE ${CMAKE_SOURCE_DIR}/shared
                                              ${SDL2_INCLUDE_DIRS})
