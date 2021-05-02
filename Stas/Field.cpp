#include "Field.h"

Field::Field() {
    points.resize(0);
    clouds.resize(0);
    clouds_count = 0;
    points_count = 0;
}

long long int Field::GetCloudsCount() {
    return clouds_count;                 // quantity of clouds
}

long long int Field::GetPointsCount() {         // quantity of points
    return points_count;
}

void Field::SetCloudsCount(long long int _clouds_count) {
    clouds_count = _clouds_count;
}

void Field::AddPointsCount(long long int _points_count) {
    points_count += _points_count;
}

vector<Point>& Field::GetFieldPoints() {
    return points;
}

vector<vector<Point>>& Field::GetClouds() {
    return clouds;
}

int Field::GetFieldFromFile(string filename) {                           // read from file, file is set by user
    ifstream fin(filename);
    double x, y;
    long long int l;
    if (!fin.is_open()) {
        cout << "Couldn't open the file" << endl;
        return ERR_OPEN_FILE;
    }
    else {
        while (!fin.eof()) {
            fin >> x >> y >> l;
            points.push_back(Point(x, y, l));
            points_count++;
            if (l > clouds_count) clouds_count = l;
        }
        fin.close();
    }
    PrintField();
    return 0;
}

void Field::PrintGNU() {                                               // output to gnuplot
    fstream script("output.plt", ios::out | ios::trunc);                                       
    if (!script.is_open()) {
        cout << "Couldn't open the file" << endl;
        exit(ERR_OPEN_FILE);
    }
    script << "plot 'data.txt' u 1:2:3 with points lc variable title 'work'" << endl;
    script.close();
}

void Field::PrintField() {                         // print to file
    ofstream fout("data.txt");
    if (!fout.is_open()) {
        cout << "Couldn't open the file" << endl;
        exit(ERR_OPEN_FILE);
    }
    for (auto& cloud : clouds) {                                                             // print to file
        for (auto& point : cloud) {
            fout << point.GetX() << " " << point.GetY() << " " << point.GetLabel() << endl;
        }
    }
    fout.close();
    PrintGNU();
}

Field::~Field() {
    points.clear();
    clouds.clear();
    points_count = 0;
    clouds_count = 0;
}