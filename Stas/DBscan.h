#pragma once

#include <iostream>
#include <queue>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "Point.h"

#define ERR_OPEN_FILE (-1)

using namespace std;

class Dbscan {
private:
    vector<pair<Point, int>> points;               // all points and their marks(not reached, in queue, visited(current cluster), written)
    queue<pair<Point*, int*>> work_points;         // neighbours
    long long int label = 1;                       // current cluster label
    long long int not_visited;                     // quantity of not visited points
    long long int noise = 0;                       // label for lonely points
public:
    Dbscan();
    Dbscan(vector<vector<Point>>& clouds);

    double Distance(Point& first, Point& second);

    void NewCluster();
    void MarkCluster(const long long int min_points, const long long int k);
    void Search(const double EPS, const long long int min_points);

    void Print();
};