//
// Created by Lwz on 2024/9/12.
//

#ifndef GA_ACO_MECHANISM_H
#define GA_ACO_MECHANISM_H

#include"Individual.h"
#include"Population.h"
#include"graph.h"
#include<utility>
#include<algorithm>
#include<iostream>
#include"graph.h"

// reverse template function: 反转一个容器（如vector）的某个区间
template <typename T>
void reverse(T& container, int start, int end) {
    if (start >= 0 && end < container.size() && start < end) {
        std::reverse(container.begin() + start, container.begin() + end + 1);
    } else {
        std::cerr << "Invalid indices for reverse operation." << std::endl;
    }
}

// swap template function: 交换容器中的两个元素
template <typename T>
void swap(T& container, int idx1, int idx2) {
    if (idx1 >= 0 && idx1 < container.size() && idx2 >= 0 && idx2 < container.size()) {
        std::swap(container[idx1], container[idx2]);
    } else {
        std::cerr << "Invalid indices for swap operation." << std::endl;
    }
}

double evaluateFitness(const Individual& individual,const Graph& graph);//评估个体适应度

std::pair<Individual, Individual> uniformCrossover(const Individual& parent1, const Individual& parent2, double crossoverRate);

void bitFlipMutation(Individual& individual,double mutationRate);//位翻转变异

// 声明 tournamentSelection 函数
Individual tournamentSelection(const Population& population, int tournamentSize);

void setGraph(Graph& graph);//设置图

#endif //GA_ACO_MECHANISM_H
