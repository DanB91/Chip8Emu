cmake_minimum_required (VERSION 2.6)
project (Pong)

find_package(SDL REQUIRED)
find_package(Curses REQUIRED)
set(CMAKE_CXX_FLAGS "-std=c++11 -g3 -Wall")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -g3 -Wall")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


include_directories(src)

add_subdirectory(src bin)
