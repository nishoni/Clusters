#include "Hierarchy.h"

Hierarchy::Hierarchy() {
    points.resize(0);
    distances.resize(0);
    clusters.resize(0);
}

Hierarchy::Hierarchy(vector<vector<Point>>& clouds) {
    size_t label = 1, i = 0;
    size_t size_of_clusters = 0;
    for (auto& cloud : clouds) {
        size_of_clusters += cloud.size();
    }

    clusters.resize(size_of_clusters);
    for (auto& cloud : clouds) {
        for (auto& point : cloud) {
            point.SetLabel(label);                                                 // each point is a cluster by the start
            points.push_back(point);
            clusters[i].push_back(point);
            ++label;
            ++i;
        }
    }

    size_t points_size = points.size();
    for (size_t i = 0; i < points_size; ++i) {
        distances.resize(points_size);
        for (size_t j = 0; j < points_size; ++j) {
            distances[i].push_back(Distance(points[i], points[j]));
        }
    }
}

double Hierarchy::Distance(Point& first, Point& second) {
    double x = first.GetX() - second.GetX();
    double y = first.GetY() - second.GetY();
    return sqrt((x * x + y * y));
}

pair<long long int, long long int> Hierarchy::FindMinDistance() {
    long long int mn = -1;
    long long int res_i = -1, res_j = -1;
    for (size_t i = 0; i < distances.size(); ++i) {
        for (size_t j = 0; j < distances[i].size(); ++j) {
            if ((distances[i][j] < mn || mn < 0) && i != j) {                    // set mn as -1, because there can't be negative distance
                mn = distances[i][j];
                res_i = i;
                res_j = j;
            }
        }
    }
    return make_pair(res_i, res_j);
}

void Hierarchy::CreateNewDistances(pair<long long int, long long int> united) {
    vector<vector<double>> new_distances = distances;
    for (size_t i = 0; i < distances.size(); ++i) {
        if (i != united.first) {                                             // formulas for distance
            distances[united.first][i] = (1 / 2) * distances[united.first][i] + (1 / 2) * distances[united.second][i] - (1 / 2) * abs(distances[united.first][i] - distances[united.second][i]);
            distances[i][united.first] = 1 / 2 * distances[united.first][i] + 1 / 2 * distances[united.second][i] - 1 / 2 * abs(distances[united.first][i] - distances[united.second][i]);
        }
    }

    for (size_t i = 0; i < distances.size(); ++i) {                           // delete one of the united clusters
        new_distances[i].erase(new_distances[i].begin() + united.second);
        if (i >= new_distances.size()) {
            break;
        }
    }
    new_distances.erase(new_distances.begin() + united.second);
    distances = new_distances;
}

void Hierarchy::Search(const long long int numb_of_clusters) {
    while (distances.size() != numb_of_clusters) {                          // algorithm
        pair<long long int, long long int> united = FindMinDistance();                               // find min distance between two clusters
        CreateNewDistances(united);                                              // unite two min-distance clusters, update distances
        for (size_t i = 0; i < clusters[united.second].size(); ++i) {
            clusters[united.first].push_back(clusters[united.second][i]);                   // continue to unite two min-distance clusters, update clusters
        }
        clusters.erase(clusters.begin() + united.second);                             // delete one of the united clusters
    }

    long long int label = 1;
    for (auto& cluster : clusters) {                                             // set labels in right order
        for (auto& point : cluster) {
            point.SetLabel(label);
        }
        ++label;
    }
}

void Hierarchy::Print() {
    ofstream fout("data.txt");
    if (!fout.is_open()) {
        cout << "Couldn't open the file" << endl;
        exit(ERR_OPEN_FILE);
    }

    vector<long long> colors;
    long long color_count = 0;
    for (auto& cloud : clusters) {
        for (auto& point : cloud) {
            if (point.GetLabel() > color_count) {
                color_count = point.GetLabel();
            }
        }
    }

    colors.resize(color_count + 1, 0);
    srand(time(NULL));
    for (size_t i = 0; i < color_count; ++i) {
        if (colors[i] == 0) {
            colors[i] = 65536 * rand() + 256 * rand() + rand();
        }
    }

    for (auto& points : clusters) {                                                             // print to file
        for (auto& point : points) {
            fout << point.GetX() << " " << point.GetY() << " " << colors[point.GetLabel()] << endl;
        }
    }
    fout.close();

    fstream script("output.plt", ios::out | ios::trunc);                                       // output to gnuplot
    if (!script.is_open()) {
        cout << "Couldn't open the file" << endl;
        exit(ERR_OPEN_FILE);
    }
    script << "plot 'data.txt' u 1:2:3 with points lc variable title 'hierarchy'" << endl;
    script.close();
}
