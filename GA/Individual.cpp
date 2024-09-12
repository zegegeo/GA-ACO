//
// Created by Lwz on 2024/9/12.
//

#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>
#include "Individual.h"

Individual::Individual(int size):genes(size),fitness{0}{}

void Individual::initialize() {
    std::iota(genes.begin(),genes.end(),0);
    std::random_device rd;
    std::mt19937 g(rd()); // 使用不同的随机种子初始化生成器
    std::shuffle(genes.begin(),genes.end(),g);
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