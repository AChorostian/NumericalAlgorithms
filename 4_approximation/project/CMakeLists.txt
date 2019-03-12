cmake_minimum_required(VERSION 3.12)
project(zad4)

find_package (Eigen3 REQUIRED NO_MODULE)

# enable C++11
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -ggdb -O3 -flto ${CMAKE_CXX_FLAGS}")

file(GLOB SOURCES "src/*.cpp")
add_executable(zad4 ${SOURCES})


include_directories( "include" )

target_link_libraries( zad4 Eigen3::Eigen )