cmake_minimum_required(VERSION 4.0)
project(vika_s_lab7)

set(CMAKE_CXX_STANDARD 20)

add_executable(vika_s_lab7 main.cpp
        menu.cpp
        menu.h
        test.cpp
        test.h
        user.cpp
        user.h
        answer.cpp
        answer.h
        result.cpp
        result.h
        question.cpp
        question.h
        transaction.cpp
        transaction.h
        utils.cpp
        utils.h)
