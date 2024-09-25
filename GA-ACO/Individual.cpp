//
// Created by Lwz on 2024/9/12.
//

#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>
#include "Individual.h"
#include "RandomGenerator.h"

Individual::Individual(int size):genes(size),fitness{0}{}

// 这是新增的构造函数
Individual::Individual(const std::vector<int>& genes) : genes(genes), fitness{0} {}

void Individual::initialize() {
    RandomGenerator ranGen;
    for (int i = 0; i < genes.size(); ++i) {
        genes[i] = ranGen.getUniformInt(1, 3);  // 生成 1 到 3 的随机整数
    }
}

double Individual::getFitness() const {
    return fitness;
}

void Individual::setFitness(double fitness) {
    Individual::fitness = fitness;
}

Gene& Individual::getGenes(){
    return genes;
}

const Gene& Individual::getGenes() const {
    return genes;
}

void Individual::setGenes(const Gene &genes) {
    Individual::genes = genes;
}