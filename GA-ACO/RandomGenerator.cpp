//
// Created by Lwz on 2024/9/12.
//

#include "RandomGenerator.h"
#include<random>
// RandomGenerator.cpp

RandomGenerator::RandomGenerator(unsigned int seed) : gen(seed) {}

double RandomGenerator::getUniformDouble() {
    return distDouble(gen);
}

int RandomGenerator::getUniformInt(int min, int max) {
    distInt = std::uniform_int_distribution<>(min, max);
    return distInt(gen);
}