//
// Created by Lwz on 2024/9/12.
//

#ifndef GA_ACO_RANDOMGENERATOR_H
#define GA_ACO_RANDOMGENERATOR_H

#include <random>

class RandomGenerator {
public:
    RandomGenerator(unsigned int seed = std::random_device{}());

    // 生成 [0.0, 1.0] 范围内的随机浮点数
    double getUniformDouble();

    // 生成 [min, max] 范围内的随机整数
    int getUniformInt(int min, int max);

private:
    std::mt19937 gen;
    std::uniform_real_distribution<> distDouble{0.0, 1.0};
    std::uniform_int_distribution<> distInt;
};


#endif //GA_ACO_RANDOMGENERATOR_H
