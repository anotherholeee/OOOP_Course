cmake_minimum_required(VERSION 3.31)
project(vika_s_lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(vika_s_lab2 main.cpp
        Money.cpp
        Money.h)

target_compile_features(vika_s_lab2 PRIVATE cxx_std_20)