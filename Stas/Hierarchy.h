#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Point.h"

#define ERR_OPEN_FILE (-1)

using namespace std;

class Hierarchy {
private:
    vector<Point> points;                                  // all points in the field
    vector<vector<double>> distances;                     // distances between clusters
    vector<vector<Point>> clusters;                       // found clusters
public:
    Hierarchy();
    Hierarchy(vector<vector<Point>>& clouds);

    double Distance(Point& first, Point& second);

    pair<long long int, long long int> FindMinDistance();
    void CreateNewDistances(pair<long long int, long long int> united);
    void Search(const long long int numb_of_clusters);

    void Print();
};