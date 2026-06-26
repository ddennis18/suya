cmake_minimum_required(VERSION 4.2)
project(Suya)

set(CMAKE_CXX_STANDARD 20)

add_executable(Suya src/main.cpp
        src/board/board.cpp
        src/board/board.h
        src/utils/utils.h
        src/utils/utils.cpp)
