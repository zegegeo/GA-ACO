//
// Created by Lwz on 2024/9/12.
//
#include "mechanism.h"
#include "Individual.h"
#include "graph.h"
#include <algorithm>
#include "graph.h"
#include "ACO.h"
#include <vector>
#include "config.h"
#include "RandomGenerator.h"
#include<iostream>
using std::cout;using std::endl;

double evaluateFitness(const Individual& ind,const Graph& graph) {

    const auto& genes=ind.getGenes();
    double fitness=0.0;
    int num_customers=genes.size();
    // 创建客户分配容器
    std::vector<int> center1_customers;
    std::vector<int> center2_customers;
    std::vector<int> center3_customers;
    // 将客户分配到相应的物流中心
    for (int i = 0; i < num_customers; ++i) {
        if (genes[i] == 1) {
            center1_customers.push_back(i+3);
        } else if (genes[i] == 2) {
            center2_customers.push_back(i+3);
        } else if (genes[i] == 3) {
            center3_customers.push_back(i+3);
        }
    }

    // 对每个物流中心运行ACO算法
    ACO aco_center1(center1_customers, NUM_ANTS,NUM_ITERATIONS,ALPHA,BETA,EVAPORATION, Q,0);
    aco_center1.run(graph);

    ACO aco_center2(center2_customers, NUM_ANTS,NUM_ITERATIONS,ALPHA,BETA,EVAPORATION, Q,1);
    aco_center2.run(graph);

    ACO aco_center3(center3_customers,NUM_ANTS,NUM_ITERATIONS,ALPHA,BETA,EVAPORATION, Q,2);
    aco_center3.run(graph);
    cout<<endl;

    // 计算路径长度
    double path_length_center1 = aco_center1.getBestLength();
    double path_length_center2 = aco_center2.getBestLength();
    double path_length_center3 = aco_center3.getBestLength();

    // 计算总路径长度作为适应度
    double total_path_length = path_length_center1 + path_length_center2 + path_length_center3;

    // 适应度函数返回的是负的路径长度，因为我们通常最小化路径长度
    return -total_path_length;
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

//UniformCrossover实现
std::pair<Individual, Individual> uniformCrossover(const Individual& parent1, const Individual& parent2, double crossoverRate) {
    RandomGenerator randGen;
    std::vector<int> genes1 = parent1.getGenes();
    std::vector<int> genes2 = parent2.getGenes();

    std::vector<int> child1 = genes1;
    std::vector<int> child2 = genes2;

    for (size_t i = 0; i < genes1.size(); ++i) {
        if (randGen.getUniformDouble() < crossoverRate) {
            std::swap(child1[i], child2[i]);
        }
    }

    return std::make_pair(Individual(child1), Individual(child2));
}

//Bit Flip Mutation实现
void bitFlipMutation(Individual& individual, double mutationRate) {
    RandomGenerator randGen;
    std::vector<int>& genes = individual.getGenes();
    // 遍历所有基因
    for (int i = 0; i < genes.size(); ++i) {
        // 根据变异率判断是否变异
        if (randGen.getUniformDouble() < mutationRate) {
            int newGene;
            do {
                newGene = randGen.getUniformInt(1, 3);  // 生成 1 到 3 之间的新基因值 (随机选取物流中心)
            } while (newGene == genes[i]);  // 确保新基因值和原基因值不同

            // 更新基因
            genes[i] = newGene;
        }
    }
}

void setGraph(Graph& graph) {
    // 初始化图
    RandomGenerator randGen(RANDOM_SEED);
    for (int i = 0; i < NUM_CITIES; ++i) {
        for (int j = 0; j < NUM_CITIES; ++j) {
            if (i == j) {
                graph.setDistance(i, j, 0);
            } else {
                graph.setDistance(i, j, randGen.getUniformInt(1, 100));
            }
        }
    }
}