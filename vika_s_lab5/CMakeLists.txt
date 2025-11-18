cmake_minimum_required(VERSION 4.0)
project(vika_s_lab5)

set(CMAKE_CXX_STANDARD 20)

add_executable(vika_s_lab5 main.cpp
        Engine.cpp
        Engine.h
        Body.cpp
        Body.h
        Car.cpp
        Car.h
        Truck.cpp
        Truck.h
        DumpTruck.cpp
        DumpTruck.h
        Menu.cpp
        Menu.h)

target_compile_features(vika_s_lab5 PRIVATE cxx_std_20)