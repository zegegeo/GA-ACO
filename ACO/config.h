//
// Created by Lwz on 2024/9/17.
//

#ifndef AC_CONFIG_H
#define AC_CONFIG_H

const int RANDOM_SEED = 12345; //随机种子
const int NUM_CITIES = 5; //城市数量
const int NUM_ANTS = 30; //蚂蚁数量
const int NUM_ITERATIONS = 100; //迭代次数
const double ALPHA = 1.0; //信息素重要程度
const double BETA = 2.0; //启发因子重要程度
const double EVAPORATION = 0.5; //信息素蒸发系数
const double Q = 1.0; //信息素增加强度

#endif //AC_CONFIG_H
