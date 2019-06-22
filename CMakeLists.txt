cmake_minimum_required(VERSION 3.14)
project(Caesar)

set(CMAKE_CXX_STANDARD 17)

add_executable(Caesar main.cpp argh.h caesar.cpp caesar.h)