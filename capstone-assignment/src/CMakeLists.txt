cmake_minimum_required(VERSION 3.15)

project(Capstone)

set(CMAKE_CXX_STANDARD 20)

add_executable(Capstone main.cpp transaction.cpp location.cpp utils.cpp)
