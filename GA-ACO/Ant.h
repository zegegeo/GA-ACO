//
// Created by Lwz on 2024/9/17.
//

#ifndef AC_ANT_H
#define AC_ANT_H

#include<vector>
#include"graph.h"

class Ant {
public:

    Ant(int numCities); //构造函数
    void visitCity(int city,const Graph& graph); //访问城市
    bool hasVisited(int city) const; //是否访问过
    void reset(); //重置
    double getPathLength(const Graph& graph) const; //计算路径长度
    const std::vector<int>& getPath() const; //获取路径

private:
    int numCities; //城市数量
    std::vector<int> path; //路径
    std::vector<bool> visited; //访问标记
    double pathLength; //路径长度

};


#endif //AC_ANT_H
