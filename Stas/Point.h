#pragma once

class Point {
private:
    double x, y;
    long long int cluster_label;
public:
    Point();
    Point(double _x, double _y);
    Point(double _x, double _y, long long int _cluster_label);

    double GetX();
    double GetY();
    long long int GetLabel();

    void SetX(double _x);
    void SetY(double _y);
    void SetLabel(long long int _label);

    void MoveX(double dx);
    void MoveY(double dy);

    Point& operator=(const Point& point);
};
