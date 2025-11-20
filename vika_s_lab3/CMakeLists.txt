cmake_minimum_required(VERSION 3.31)
project(vika_s_lab3)

set(CMAKE_CXX_STANDARD 20)

add_executable(vika_s_lab3 main.cpp
        transport.cpp
        airplane.cpp
        train.cpp
        car.cpp
        transport.h
        menu.cpp
        menu.h)

