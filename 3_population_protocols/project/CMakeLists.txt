cmake_minimum_required(VERSION 3.12)
project(zad3)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# enable C++11
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -ggdb -O3 -flto ${CMAKE_CXX_FLAGS}")

file(GLOB SOURCES "src/*.cpp")
add_executable(zad3 ${SOURCES})

target_link_libraries (zad3 Eigen3::Eigen)
include_directories( "src/*" )

target_link_libraries( zad3 )