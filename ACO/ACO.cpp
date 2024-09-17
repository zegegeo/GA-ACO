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

ACO::ACO(int numAnts, int numIterations, double alpha, double beta, double evaporation, double Q)
:numAnts{numAnts},numIterations {numIterations},alpha {alpha},beta {beta},evaporation {evaporation},Q {Q}
{ srand(time(nullptr)); }

void ACO::initialize(Graph& graph) {
    int numCities = graph.getNumCities();
    pheromones.resize(numCities,std::vector<double>(numCities,1.0));
    ants.resize(numAnts,Ant(numCities));
}

int ACO::selectNextCity(const Ant &ant, int currentCity, const Graph &graph) {
    std::vector<double> probabilities(graph.getNumCities(),0.0);
    double sum=0.0;

    //计算选择概率
    for(int i=0;i<graph.getNumCities();i++){
        if(!ant.hasVisited(i)){
            probabilities[i]=pow(pheromones[currentCity][i],alpha)*pow(1.0/graph.getDistance(currentCity,i),beta);
            sum+=probabilities[i];
        }
    }


    RandomGenerator ranGen{RANDOM_SEED};
    //轮盘赌选择下一个城市
    double randVal=ranGen.getUniformDouble()*sum;
    for(int i=0;i<graph.getNumCities();i++){
        if(!ant.hasVisited(i)){
            if(randVal<probabilities[i]){
                return i;
            }
            randVal-=probabilities[i];
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

void ACO::run(Graph &graph) {
    RandomGenerator ranGen{RANDOM_SEED};
    initialize(graph);
    double bestLength=1e9;
    std::vector<int> bestPath;
    for(int iter=0;iter<numIterations;iter++){
        for(auto& ant:ants) {
            ant.reset();
            int startCity = ranGen.getUniformInt(0, graph.getNumCities()) % graph.getNumCities();
            ant.visitCity(startCity,graph);

            for(int i=1;i<graph.getNumCities();i++){
                int currentCity=ant.getPath().back();
                int nextCity=selectNextCity(ant,currentCity,graph);
                ant.visitCity(nextCity,graph);
            }
            ant.visitCity(ant.getPath()[0],graph);

            if(ant.getPathLength(graph)<bestLength){
                bestLength=ant.getPathLength(graph);
                bestPath=ant.getPath();
            }
        }
        updatePheromones(graph);

        std::cout<<"Iteration "<<iter+1<<": Best path length = "<<bestLength<<std::endl;
    }
    std::cout<<"Best path found: ";
    for(int city:bestPath){
        std::cout<<city<<" ";
    }
    std::cout<<std::endl;
}

