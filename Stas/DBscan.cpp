#include "DBscan.h"

ostream& operator<<(ostream& out, Point& point) {
    return out << setprecision(5) << point.GetX() << "\t" << point.GetY() << "\t" << point.GetLabel() << endl;
}

Dbscan::Dbscan() {
    points.resize(0);
    work_points;
    label = 1;
    not_visited = 0;
}

Dbscan::Dbscan(vector<vector<Point>>& clouds) {
    for (size_t j = 0; j < clouds.size(); ++j) {
        vector<Point> cloud = clouds[j];
        for (size_t i = 0; i < cloud.size(); ++i) {
            points.push_back(make_pair(cloud[i], 0));
        }
    }
    not_visited = points.size();
}

double Dbscan::Distance(Point& first, Point& second) {
    double x = first.GetX() - second.GetX();
    double y = first.GetY() - second.GetY();
    return sqrt((abs(x * x) + abs(y * y)));
}

void Dbscan::NewCluster() {
    for (size_t i = 0; i < points.size(); ++i) {
        if (points[i].second == 0) {
            points[i].second = 2;
            work_points.push(make_pair(&points[i].first, &points[i].second));
            not_visited--;
            break;
        }
    }
}

void Dbscan::MarkCluster(const long long int min_points, const long long int k) {                // mark new cluster
    for (auto& p : points) {
        if (p.second == 2 && k >= min_points) {
            p.second = 3;
            p.first.SetLabel(label);
        }
        else if (p.second == 2 && k < min_points) {                  // lonely points(do not belong to any cluster), let them be, they're as happy as any of us
            p.second = 3;
            p.first.SetLabel(noise);
        }
    }
    if (k >= min_points) ++label;                                   // if it was a cluster and not just noise(lonely point)
}

void Dbscan::Search(const double EPS, const long long int min_points) {
    while (not_visited > 0) {
        if (not_visited != 0 && work_points.empty()) {                    // cluster was formed, but there is points left
            NewCluster();
        }

        long long int k = 0;                                                        // how many points in this cluster(if enough to make a cluster)
        while (!work_points.empty()) {                                    // algorithm
            pair<Point*, int*> p = work_points.front();
            work_points.pop();
            *p.second = 2;
            ++k;
            for (size_t i = 0; i < points.size(); ++i) {
                pair<Point*, int*> to = make_pair(&points[i].first, &points[i].second);
                if (*to.second == 0 && Distance(*p.first, *to.first) <= EPS) {
                    *to.second = 1;
                    work_points.push(to);
                    --not_visited;
                }
            }
        }
        MarkCluster(min_points, k);
    }
}

void Dbscan::Print() {
    ofstream fout("data.txt");
    if (!fout.is_open()) {
        cout << "Couldn't open the file" << endl;
        exit(ERR_OPEN_FILE);
    }

    vector<long long> colors;
    long long int color_count = 0;
    for (auto& point : points) {
        if (point.first.GetLabel() > color_count) {
            color_count = point.first.GetLabel();
        }
    }

    colors.resize(color_count + 1, 0);
    srand(time(NULL));
    for (size_t i = 0; i < color_count; ++i) {
        if (colors[i] == 0) {
            colors[i] = 65536 * rand() + 256 * rand() + rand();
        }
    }

    for (auto& point : points) {                                                             // print to file
        fout << point.first.GetX() << " " << point.first.GetY() << " " << colors[point.first.GetLabel()] << endl;
    }
    fout.close();

    fstream script("output.plt", ios::out | ios::trunc);                                       // output to gnuplot
    if (!script.is_open()) {
        cout << "Couldn't open the file" << endl;
        exit(ERR_OPEN_FILE);
    }
    script << "plot 'data.txt' u 1:2:3 with points lc variable title 'dbscan'" << endl;
    script.close();
}