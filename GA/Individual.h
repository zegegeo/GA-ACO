//
// Created by Lwz on 2024/9/12.
//

#ifndef GA_ACO_INDIVIDUAL_H
#define GA_ACO_INDIVIDUAL_H

#include <vector>
#include <algorithm>
#include <random>

using Gene=std::vector<int>;

class Individual {

public:

    //构造函数,根据size大小构建种群中的个体并初始化
    explicit Individual(int size);

    void initialize();

    //获取个体的适应度
    double getFitness() const;

    //设置个体适应度
    void setFitness(double fitness);

    //获取个体的基因序列
    Gene& getGenes() ;

    const Gene& getGenes() const;

    //设置个体的基因序列
    void setGenes(const Gene& genes);

private:

    Gene genes;
    double fitness;

};

#endif //GA_ACO_INDIVIDUAL_H
