#include "Point.h"


Point::Point() {                  // Default constructor
    x = 0;
    y = 0;
    cluster_label = -1;
}

Point::Point(double _x, double _y) {               // New point
    x = _x;
    y = _y;
    cluster_label = -1;
}

Point::Point(double _x, double _y, long long int _cluster_label) {        // Adding point to the cluster
    x = _x;
    y = _y;
    cluster_label = _cluster_label;
}

double Point::GetX() {
    return x;
}

double Point::GetY() {
    return y;
}

long long int Point::GetLabel() {
    return cluster_label;
}

void Point::SetX(double _x) {
    x = _x;
}

void Point::SetY(double _y) {
    y = _y;
}

void Point::SetLabel(long long int _label) {
    cluster_label = _label;
}

void Point::MoveX(double dx) {
    x += dx;
}

void Point::MoveY(double dy) {
    y += dy;
}

Point& Point::operator=(const Point& point) {
    x = point.x;
    y = point.y;
    cluster_label = point.cluster_label;

    return *this;
}