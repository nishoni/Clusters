#include "Cloud.h"

Cloud::Cloud() {                       // Default constructor
    x.first = 0;
    x.second = 0;
    y.first = 0;
    y.second = 0;
    center = Point(0, 0);
    cloud.resize(0);
    cloud_count = 0;
}

Cloud::Cloud(double x_center, double y_center, double x_mn, double x_mx, double y_mn, double y_mx, int count) {
    x.first = x_mn;
    x.second = x_mx;
    y.first = y_mn;
    y.second = y_mx;
    center = Point(x_center, y_center);
    cloud_count = count;
}

vector<Point>& Cloud::GetCloud() {
    return cloud;
}

int Cloud::GetCloudCount() {
    return cloud_count;
}

vector<double> Cloud::CreateNorm(size_t numb, double minval, double maxval) {                        //norm gistogramm
    vector<double> normal_array(numb);                                                    // Create a vector of predefined size
    if (minval > maxval) {
        swap(minval, maxval);
    }

    if (minval < 0) {
        swap(minval, maxval);
    }

    random_device rd{};
    mt19937 gen{ rd() };
    if (abs(maxval - minval) / 12 != 0) {
        normal_distribution<double> rng_machine{ (maxval + minval) / 2, abs(maxval - minval) / 12 };           // set normal distribution of points
        for (size_t i = 0; i < numb; ++i) {
            normal_array[i] = rng_machine(gen);
        }
    }
    else {
        for (size_t i = 0; i < numb; ++i) {
            normal_array[i] = maxval;
        }
    }

    return normal_array;
}

void Cloud::ShiftX(double dx) {
    for (auto& point : cloud) {
        point.MoveX(dx);
    }
    center.MoveX(dx);
}

void Cloud::ShiftY(double dy) {
    for (auto& point : cloud) {
        point.MoveY(dy);
    }
    center.MoveY(dy);
}

double Cloud::MoveXonAngle(Point point, double angle, double _x, double _y) {
    return _x + (point.GetX() - _x) * cos(angle) - (point.GetY() - _y) * sin(angle);
}

double Cloud::MoveYonAngle(Point point, double angle, double _x, double _y) {
    return _y + (point.GetX() - _x) * sin(angle) + (point.GetY() - _y) * cos(angle);
}

void Cloud::Turn(int angle, double _x, double _y) {
    for (auto& point : cloud) {
        double new_x = MoveXonAngle(point, angle, _x, _y);
        double new_y = MoveYonAngle(point, angle, _x, _y);
        point.SetX(new_x);
        point.SetY(new_y);
    }

    center.SetX(MoveXonAngle(center, angle, _x, _y));
    center.SetY(MoveXonAngle(center, angle, _x, _y));
}

void Cloud::Filling(size_t count, Point& start, Point& end) {
    cloud.resize(count);
    center = Point((end.GetX() - start.GetX()) / 2, (end.GetY() - start.GetY()) / 2);
    vector <double> x_arr = CreateNorm(count, start.GetX(), end.GetX());
    vector <double> y_arr = CreateNorm(count, start.GetY(), end.GetY());
    for (size_t i = 0; i < count; ++i) {
        cloud[i].SetX(x_arr[i]);
        cloud[i].SetY(y_arr[i]);
        cloud[i].SetLabel(0);
        cloud_count++;
    }
}

Cloud::~Cloud() {
    cloud.clear();
}