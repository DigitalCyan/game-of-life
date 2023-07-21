cmake_minimum_required(VERSION 3.25)
project(game_of_life C)

set(CMAKE_C_STANDARD 23)

find_package(PkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

file(GLOB SOURCE_FILES src/*.c)
include_directories(${SDL2_INCLUDE_DIRS} src/include)

file(GLOB SOURCE_FILES src/*.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
