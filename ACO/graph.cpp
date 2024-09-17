//
// Created by Lwz on 2024/9/17.
//

#include "graph.h"

Graph::Graph(int numCities):numCities {numCities} {
    distances.resize(numCities,std::vector<double>(numCities,0));
}


void Graph::setDistance(int city1, int city2, double distance) {
    distances[city1][city2] = distance;
    distances[city2][city1] = distance;
}

double Graph::getDistance(int city1, int city2) const {
    return distances[city1][city2];
}

int Graph::getNumCities() const {
    return numCities;
}