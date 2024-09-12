cmake_minimum_required(VERSION 3.28)
project(GA_ACO)

set(CMAKE_CXX_STANDARD 17)

add_executable(GA_ACO main.cpp
        Individual.cpp
        Individual.h
        mechanism.h
        mechanism.cpp
        Population.cpp
        Population.h
        config.h
        RandomGenerator.cpp
        RandomGenerator.h)
