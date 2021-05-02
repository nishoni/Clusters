#pragma once

#include <vector>
#include <random>
#include "Point.h"

using namespace std;

class Cloud {
private:
    pair<double, double> x, y;         // spreading
    Point center;                      // center of this cloud
    vector<Point> cloud;                // list of points in this cloud
    int cloud_count;
public:
    Cloud();
    ~Cloud();
    Cloud(double x_center, double y_center, double x_mn, double x_mx, double y_mn, double y_mx, int count);

    vector<Point>& GetCloud();
    int GetCloudCount();

    void ShiftX(double dx);
    void ShiftY(double dy);
    double MoveXonAngle(Point point, double angle, double _x, double _y);
    double MoveYonAngle(Point point, double angle, double _x, double _y);
    void Turn(int angle, double _x = 0, double _y = 0);

    vector<double> CreateNorm(size_t numb, double minval, double maxval);
    void Filling(size_t count, Point& start, Point& end);
};
