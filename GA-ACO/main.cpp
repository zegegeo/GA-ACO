#include <iostream>
#include "Population.h"
#include "Individual.h"
#include "mechanism.h"
#include "config.h"
#include "RandomGenerator.h"
#include "matplotlib.h"
#include "graph.h"

int main() {

    RandomGenerator randGen;

    Graph graph{NUM_CITIES};
    setGraph(graph);

    Population population{populationSize, chromosomeLength, graph};
    population.initializePopulation();

    std::vector<double> x_data;
    std::vector<double> y_data;

    for (int generation = 0; generation < maxGeneration; ++generation) {
        std::cout << "Generation " << generation << std::endl;

        population.evaluate();

        // 输出最优个体的适应度和基因
        Individual bestIndividual = population.getBestIndividual();
        std::cout << ": Best Fitness = "
                  << bestIndividual.getFitness() << " | Genes: ";

        //添加数据
        x_data.push_back(generation);
        y_data.push_back(bestIndividual.getFitness());

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

            double num = randGen.getUniformDouble();
            // 交叉
            Individual offspring1 = parent1;
            Individual offspring2 = parent2;
            if (num < individualCrossoverRate) {
                auto offspringPair = uniformCrossover(parent1, parent2, crossoverRate);
                offspring1 = offspringPair.first;
                offspring2 = offspringPair.second;
            }

            // 变异
            if (randGen.getUniformDouble()< individualMutationRate) {
                bitFlipMutation(offspring1, mutationRate);  // Ensure to pass the number of centers
            }

            if (randGen.getUniformDouble() < individualMutationRate) {
                bitFlipMutation(offspring2,mutationRate);  // Ensure to pass the number of centers
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

    // 保存数据到文件
    saveDataToFile("x_data.txt", "y_data.txt", x_data, y_data);

    //调用Python脚本生成图像
    generatePlot("/Users/lwz/myenv/bin/python", "plot.py", "x_data.txt", "y_data.txt", "plot.png");

    return 0;
}
