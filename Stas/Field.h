#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Point.h"
#include "Cloud.h"

#define ERR_OPEN_FILE (-1)

using namespace std;

class Field {
private:
    vector<vector<Point>> clouds;    // all clouds in this field
    vector<Point> points;            // all points in this field
    long long int clouds_count;
    long long int points_count;
public:
    Field();
    ~Field();

    int GetFieldFromFile(string filename);

    long long int GetCloudsCount();
    long long int GetPointsCount();
    vector<Point>& GetFieldPoints();
    vector<vector<Point>>& GetClouds();

    void SetCloudsCount(long long int _clouds_count);
    void AddPointsCount(long long int _points_count);

    void PrintGNU();
    void PrintField();
};
