//
// Created by Lwz on 2024/9/17.
//

#ifndef AC_ACO_H
#define AC_ACO_H
#include<vector>
#include"graph.h"
#include"Ant.h"

class ACO {
public:
    ACO(int numAnts,int numIterations,double alpha,double beta,double evaporation,double Q);
    void initialize(Graph& graph); //初始化
    void run(Graph& graph); //运行
private:
    int numAnts; //蚂蚁数量
    int numIterations; //迭代次数
    double alpha; //信息素重要程度
    double beta; //启发因子重要程度
    double evaporation; //信息素蒸发系数
    double Q; //信息素增加强度
    std::vector<Ant> ants; //蚂蚁
    std::vector<std::vector<double>> pheromones; //信息素

    void updatePheromones(const Graph& graph); //更新信息素
    int selectNextCity(const Ant& ant,int currentCity,const Graph& graph); //选择下一个城市
};

#endif //AC_ACO_H
