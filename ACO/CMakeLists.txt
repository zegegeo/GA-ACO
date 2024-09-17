cmake_minimum_required(VERSION 3.28)
project(ACO)

set(CMAKE_CXX_STANDARD 17)

add_executable(ACO main.cpp
        config.h
        graph.cpp
        graph.h
        Ant.cpp
        Ant.h
        ACO.cpp
        ACO.h
        RandomGenerator.cpp
        RandomGenerator.h
)
