cmake_minimum_required(VERSION 3.31)
project(vika_s_lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(vika_s_lab1 main.cpp
        box.cpp
        box.h
        menu.cpp
        menu.h)

target_compile_features(vika_s_lab1 PRIVATE cxx_std_20)