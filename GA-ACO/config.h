//
// Created by Lwz on 2024/9/12.
//

#ifndef GA_ACO_CONFIG_H
#define GA_ACO_CONFIG_H

//随机数生成种子
const unsigned int RANDOM_SEED = 12345;

const int NUM_WAREHOUSES = 3; //仓库数量
const int NUM_CUSTOMERS = 47; //城市数量
const int NUM_CITIES = NUM_WAREHOUSES + NUM_CUSTOMERS; //总城市数量
const int NUM_ANTS = 30; //蚂蚁数量
const int NUM_ITERATIONS = 10; //迭代次数
const double ALPHA = 1.0; //信息素重要程度
const double BETA = 2.0; //启发因子重要程度
const double EVAPORATION = 0.5; //信息素蒸发系数
const double Q = 1.0; //信息素增加强度

const int populationSize = 10;     // 种群大小
const int chromosomeLength = NUM_CUSTOMERS;   // 每个个体的基因序列长度
const int tournamentSize = 3;      // 锦标赛中参与比较的个体数量
const double individualCrossoverRate=0.8; //个体交叉概率
const double individualMutationRate=0.05; //个体变异概率
const double crossoverRate = 0.6;  // 基因交叉概率
const double mutationRate = 0.1;  // 基因变异概率
const int maxGeneration = 10;     // 最大迭代次数

#endif //GA_ACO_CONFIG_H
