//
// Created by Lwz on 2024/9/12.
//
#include "mechanism.h"
#include "Individual.h"
#include <algorithm>

double evaluateFitness(const Individual& ind) {

    const auto& genes=ind.getGenes();
    double fitness=0.0;
    for(int i=0;i<genes.size();++i){
        fitness+=i*genes[i];
    }

    return -fitness;

}

//锦标赛选择实现
Individual tournamentSelection(const Population& population, int tournamentSize) {
    std::vector<Individual> tournament;
    const std::vector<Individual>& individuals = population.getIndividuals(); // 获取个体列表

    // 随机选择 tournamentSize 个体进入锦标赛
    for (int i = 0; i < tournamentSize; ++i) {
        int randomIndex = rand() % individuals.size();
        tournament.push_back(individuals[randomIndex]);
    }

    // 在锦标赛中选择适应度最高的个体
    auto bestIndividual = *std::max_element(tournament.begin(), tournament.end(),
                                            [](const Individual& a, const Individual& b) {
                                                return a.getFitness() < b.getFitness();
                                            });

    return bestIndividual;
}

//PMX交叉实现
std::pair<Individual, Individual> pmxCrossover(const Individual& parent1, const Individual& parent2) {
    int chromosomeLength = parent1.getGenes().size();
    Individual offspring1(chromosomeLength), offspring2(chromosomeLength);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, chromosomeLength - 1);

    // 随机选择两个交叉点
    int crossoverPoint1 = dist(gen);
    int crossoverPoint2 = dist(gen);
    if (crossoverPoint1 > crossoverPoint2) std::swap(crossoverPoint1, crossoverPoint2);

    // 交叉区间映射
    std::vector<int> map1(chromosomeLength, -1); // 映射表
    std::vector<int> map2(chromosomeLength, -1); // 映射表

    // 交换交叉点之间的基因
    for (int i = crossoverPoint1; i <= crossoverPoint2; ++i) {
        offspring1.getGenes()[i] = parent2.getGenes()[i];
        offspring2.getGenes()[i] = parent1.getGenes()[i];
        map1[parent2.getGenes()[i]] = parent1.getGenes()[i];
        map2[parent1.getGenes()[i]] = parent2.getGenes()[i];
    }

    // 填充其余部分
    auto fillRemaining = [&](Individual& offspring, const Individual& parent, const std::vector<int>& mapping) {
        for (int i = 0; i < chromosomeLength; ++i) {
            if (i >= crossoverPoint1 && i <= crossoverPoint2) continue;
            int gene = parent.getGenes()[i];
            while (mapping[gene] != -1) {
                gene = mapping[gene];
            }
            offspring.getGenes()[i] = gene;
        }
    };

    fillRemaining(offspring1, parent1, map1);
    fillRemaining(offspring2, parent2, map2);

    return {offspring1, offspring2};
}

//Reverse Mutation 变异实现
void reverseMutation(Individual& ind) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, ind.getGenes().size() - 1);

    // 随机选择两个点
    int point1 = dist(gen);
    int point2 = dist(gen);

    if (point1 > point2) std::swap(point1, point2);

    // 反转基因序列中的一部分
    std::reverse(ind.getGenes().begin() + point1, ind.getGenes().begin() + point2 + 1);
}