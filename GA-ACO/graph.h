//
// Created by Lwz on 2024/9/17.
//

#ifndef AC_GRAPH_H
#define AC_GRAPH_H

#include<vector>

class Graph {
public:
    Graph(int numCities); //构造函数
    void setDistance(int city1,int city2,double distance); //设置两个城市之间的距离
    double getDistance(int city1,int city2) const; //获取两个城市之间的距离
    int getNumCities() const; //获取城市数量

private:
    std::vector<std::vector<double>> distances; //存储城市之间的距离
    int numCities; //城市数量
};

#endif //AC_GRAPH_H
