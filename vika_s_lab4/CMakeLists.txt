cmake_minimum_required(VERSION 4.0)
project(vika_s_lab4)

set(CMAKE_CXX_STANDARD 20)

add_executable(vika_s_lab4 main.cpp
        worker.h
        worker.cpp
        menu.cpp
        menu.h)

target_compile_features(vika_s_lab4 PRIVATE cxx_std_20)