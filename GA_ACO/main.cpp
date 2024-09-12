#include <iostream>
#include "Population.h"
#include "Individual.h"
#include "mechanism.h"
#include "config.h"
#include "RandomGenerator.h"

int main() {

    RandomGenerator randGen(RANDOM_SEED);

    Population population{populationSize, chromosomeLength};
    population.initializePopulation();

    for (int generation = 0; generation < maxGeneration; ++generation) {
        std::cout << "Generation " << generation << std::endl;

        population.evaluate();

        // 输出最优个体的适应度和基因
        Individual bestIndividual = population.getBestIndividual();
        std::cout << ": Best Fitness = "
                  << bestIndividual.getFitness() << " | Genes: ";
        for (int gene : bestIndividual.getGenes()) {
            std::cout << gene << " ";
        }
        std::cout << std::endl;

        //population.printPopulation();

        // 创建新的个体集合
        std::vector<Individual> newIndividuals;
        newIndividuals.reserve(populationSize);

        // 生成新的个体
        while (newIndividuals.size() < populationSize) {
            // 锦标赛选择
            Individual parent1 = tournamentSelection(population, tournamentSize);
            Individual parent2 = tournamentSelection(population, tournamentSize);

            // 交叉
            Individual offspring1 = parent1;
            Individual offspring2 = parent2;
            if (randGen.getUniformDouble()< crossoverRate) {
                auto offspringPair = pmxCrossover(parent1, parent2);
                offspring1 = offspringPair.first;
                offspring2 = offspringPair.second;
            }

            // 变异
            if (randGen.getUniformDouble()< mutationRate) {
                reverseMutation(offspring1);
            }
            if (randGen.getUniformDouble()< mutationRate) {
                reverseMutation(offspring2);
            }

            // 添加到新种群
            newIndividuals.push_back(offspring1);
            if (newIndividuals.size() < populationSize) {
                newIndividuals.push_back(offspring2);
            }
        }

        // 替换旧种群为新种群
        for (int i = 0; i < populationSize; ++i) {
            population.setIndividual(i, newIndividuals[i]);
        }
    }

    return 0;
}
