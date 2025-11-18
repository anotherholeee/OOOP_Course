cmake_minimum_required(VERSION 4.0)
project(vika_s_lab6)

set(CMAKE_CXX_STANDARD 20)

add_executable(vika_s_lab6 main.cpp)

target_compile_features(vika_s_lab6 PRIVATE cxx_std_20)