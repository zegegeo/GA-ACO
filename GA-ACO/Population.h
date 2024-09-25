//
// Created by Lwz on 2024/9/12.
//

#ifndef GA_ACO_POPULATION_H
#define GA_ACO_POPULATION_H

#include <vector>
#include "Individual.h"
#include "graph.h"

class Population {

public:

    //构造函数，根据种群大小和染色体大小构建种群并初始化
    Population(int populationSize,int chromosomeSize,const Graph& graph);

    void initializePopulation();

    //获取种群中的个体
    const std::vector<Individual>& getIndividuals() const;

    //设置种群中的个体
    void setIndividual(int index,const Individual& individual);

    //获取指定个体
    const Individual& getIndividual(int index) const;

    //获取种群中的个体数量
    int getPopulationSize() const;

    //评估种群中的个体适应度
    void evaluate();

    // 打印种群中的所有个体
    void printPopulation() const;

    // 查找适应度最好的个体
    const Individual& getBestIndividual() const;

private:

    std::vector<Individual> individuals;
    const Graph& graph; // 添加 graph 成员变量

};


#endif //GA_ACO_POPULATION_H
