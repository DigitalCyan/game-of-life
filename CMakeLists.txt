cmake_minimum_required(VERSION 3.22)
project(game-of-life C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2/xd)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(src/include)

file(GLOB SOURCE_FILES src/*.c)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::TTF)
