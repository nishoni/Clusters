#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <chrono>
#include <iomanip>
#include "Point.h"

#define ERR_OPEN_FILE (-1)

using namespace std;

class Wave {
private:
    vector<pair<Point, int>> points;               // all points and their marks(not reached, in queue, visited(current cluster), written)
    queue<pair<Point*, int*>> work_points;         // neighbours
    long long int label = 1;                       // current cluster label
    long long int not_visited;                     // quantity of not visited points
public:
    Wave();
    Wave(vector<vector<Point>>& clouds);

    double Distance(Point& first, Point& second);

    void FindNotVisited();
    void MarkCluster();
    void Search(const double EPS);

    void Print();
};
