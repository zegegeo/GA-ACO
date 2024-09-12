//
// Created by Lwz on 2024/9/12.
//

#ifndef GA_ACO_CONFIG_H
#define GA_ACO_CONFIG_H

//随机数生成种子
const unsigned int RANDOM_SEED = 12345;

const int populationSize = 100;     // 种群大小
const int chromosomeLength = 50;   // 每个个体的基因序列长度
const int tournamentSize = 3;      // 锦标赛中参与比较的个体数量
const double crossoverRate = 0.8;  // 交叉概率
const double mutationRate = 0.01;  // 变异概率
const int maxGeneration = 1000;     // 最大迭代次数

#endif //GA_ACO_CONFIG_H
