//
// Created by Lwz on 2024/9/17.
//

#include "ACO.h"
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include"RandomGenerator.h"
#include"config.h"
#include<iostream>

ACO::ACO(const std::vector<int>& customers,int numAnts, int numIterations, double alpha, double beta, double evaporation, double Q,int center)
:customers{customers},numAnts{numAnts},numIterations {numIterations},alpha {alpha},beta {beta},evaporation {evaporation},Q {Q},center {center}
{ srand(time(nullptr)); }

void ACO::initialize(const Graph& graph) {
    int numCities = graph.getNumCities();
    pheromones.resize(numCities,std::vector<double>(numCities,1.0));
    ants.resize(numAnts,Ant(numCities));
}

int ACO::selectNextCity(const Ant &ant, int currentCity, const Graph &graph) {
    std::vector<double> probabilities(customers.size(),0.0);
    double sum=0.0;

    //计算选择概率
    for(int i=0;i<customers.size();i++){
        int nextcity=customers[i];
        if(!ant.hasVisited(nextcity)){
            // 计算当前城市到下一个客户的选择概率
            double pheromone = pheromones[currentCity][nextcity];
            double heuristic = 1.0 / graph.getDistance(currentCity, nextcity);  // 启发因子：距离的倒数
            probabilities[i] = std::pow(pheromone, alpha) * std::pow(heuristic, beta);
            sum += probabilities[i];
        }
        else probabilities[i] = 0.0;  // 已访问的城市设为0概率
    }
    // 归一化概率
    for (double& prob : probabilities) {
        prob /= sum;
    }
    RandomGenerator ranGen{RANDOM_SEED};
    //轮盘赌选择下一个城市
    double r=ranGen.getUniformDouble();
    double cumulativeProbability = 0.0;
    for (int i = 0; i < customers.size(); ++i) {
        cumulativeProbability += probabilities[i];
        if (r <= cumulativeProbability) {
            return customers[i];
        }
    }
    // 保险起见，返回最后一个未访问的客户
    for (int customer : customers) {
        if (!ant.hasVisited(customer)) {
            return customer;
        }
    }
    return -1;
}

void ACO::updatePheromones(const Graph &graph) {
    //信息素挥发
    for(int i=0;i<graph.getNumCities();i++){
        for(int j=0;j<graph.getNumCities();j++){
            pheromones[i][j]*=(1-evaporation);
        }
    }

    //信息素更新
    for(auto& ant:ants){
        double contribution=Q/ant.getPathLength(graph);
        const std::vector<int>& path=ant.getPath();
        for(size_t i=0;i<path.size()-1;i++){
            int from=path[i];
            int to=path[i+1];
            pheromones[from][to]+=contribution;
            pheromones[to][from]+=contribution;
        }
    }
}

void ACO::run(const Graph &graph) {
    RandomGenerator ranGen{RANDOM_SEED};
    initialize(graph);
    double bestLength=1e9;
    std::vector<int> bestPath;
    for(int iter=0;iter<numIterations;iter++){
        for(auto& ant:ants) {
            ant.reset();

            // 1. 从固定物流中心出发
            int startCity = center;
            ant.visitCity(startCity,graph);

            for (int i=0;i<customers.size();i++) {
                int currentCity = ant.getPath().back();
                int nextCity = selectNextCity(ant, currentCity, graph);
                ant.visitCity(nextCity, graph);
            }

            ant.visitCity(center,graph);

            if(ant.getPathLength(graph)<bestLength){
                bestLength=ant.getPathLength(graph);
                bestPath=ant.getPath();
                bestPathLength=bestLength;
            }
        }
        updatePheromones(graph);

        //std::cout<<"Iteration "<<iter+1<<": Best path length = "<<bestLength<<std::endl;
    }
    std::cout<<"The Center "<<center<<" Best path found: ";
    for(int city:bestPath){
        std::cout<<city<<" ";
    }
    std::cout<<std::endl;
}

double ACO::getBestLength() const {
    return bestPathLength;
}