//
// Created by Lwz on 2024/9/17.
//

#include "Ant.h"
#include "graph.h"

Ant::Ant(int numCities) : numCities{numCities},pathLength{0.0}{
    visited.resize(numCities,false);
}

void Ant::visitCity(int city,const Graph& graph){
    path.push_back(city);
    visited[city] = true;
    if(path.size()>1){
        int prevCity=path[path.size()-2];
        pathLength+=graph.getDistance(prevCity,city);
    }
}

bool Ant::hasVisited(int city) const{
    return visited[city];
}

void Ant::reset() {
    path.clear();
    visited.assign(numCities,false);
    pathLength=0.0;
}

double Ant::getPathLength(const Graph& graph) const {
    // 如果需要计算完整路径（包括回到起点）
    if (!path.empty() && path.size() == numCities) {
        return pathLength + graph.getDistance(path.back(), path.front());
    }
    return pathLength;
}

const std::vector<int>& Ant::getPath() const {
    return path;
}