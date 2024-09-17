#include <iostream>
#include "Ant.h"
#include "ACO.h"
#include "graph.h"
#include "RandomGenerator.h"
#include "config.h"

int main() {
    Graph graph{NUM_CITIES}; //创建五个城市的图
    graph.setDistance(0,1,2);
    graph.setDistance(0,2,2);
    graph.setDistance(0,3,4);
    graph.setDistance(0,4,3);
    graph.setDistance(1,2,3);
    graph.setDistance(1,3,2);
    graph.setDistance(1,4,1);
    graph.setDistance(2,3,5);
    graph.setDistance(2,4,2);
    graph.setDistance(3,4,3);

    ACO aco{NUM_ANTS,NUM_ITERATIONS,ALPHA,BETA,EVAPORATION,Q};
    aco.run(graph);

    return 0;
}
