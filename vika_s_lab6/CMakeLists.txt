cmake_minimum_required(VERSION 4.0)
project(vika_s_lab6)

set(CMAKE_CXX_STANDARD 20)

add_executable(vika_s_lab6 main.cpp
        menu.cpp
        menu.h
        user.cpp
        user.h
        question.cpp
        question.h
        test.cpp
        test.h
        utils.cpp
        utils.h
        answer.cpp
        answer.h
        result.cpp
        result.h
)

