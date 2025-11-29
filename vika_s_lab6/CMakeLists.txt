cmake_minimum_required(VERSION 4.0)
project(vika_s_lab6)

set(CMAKE_CXX_STANDARD 20)

add_executable(vika_s_lab6 main.cpp
        user.cpp
        user.h
        answer.cpp
        answer.h
        iquestion.cpp
        iquestion.h
        question.cpp
        question.h
        result.cpp
        result.h
        test.cpp
        test.h
        utils.cpp
        utils.h)

