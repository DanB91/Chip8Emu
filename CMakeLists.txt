cmake_minimum_required (VERSION 2.6)
project (Pong)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")



include_directories(src)

add_subdirectory(src bin)
