#include "Interface.h"

double FoolCheckDouble(bool negative = false) {
    string input;
    bool flag = true, flag_point = false;
    int j = 0;

    while (flag) {
        try {
            cin >> input;
            if (input[0] == '-' && negative) j = 1;
            if (j >= input.length()) throw ERR_INPUT;

            for (int i = j; i < input.length(); i++) {
                if (((int(input[i]) > 57 || int(input[i]) < 48) && int(input[i]) != 46) || (int(input[i]) == 46 && flag_point)) {
                    throw ERR_INPUT;
                }
                if (int(input[i]) == 46 && !flag_point) {
                    flag_point = true;
                }
            }

            flag = false;
        }
        catch (int a) {
            cout << "Enter correct number: ";
        }
    }

    return stod(input);
}

long long int FoolCheck(bool non_negative = false) {
    string input;
    bool flag = true;
    int j = 0;

    while (flag) {
        try {
            cin >> input;
            if (input[0] == '-' && !non_negative) j = 1;
            if (j >= input.length()) throw ERR_INPUT_INT;

            for (int i = j; i < input.length(); i++) {
                if (int(input[i]) > 57 || int(input[i]) < 48)
                    throw ERR_INPUT_INT;
            }

            flag = false;
        }
        catch (int a) {
            cout << "Enter correct number: ";
        }
    }

    return stoll(input);
}

void Interface::Control() {
    Field field;
    Point point;
    Cloud cloud;

    CommandList();
    cout << "Enter command: " << endl;

    do {
        bool mistake = false;
        getline(cin, command);
        bool flag = true;

        if (command == "name") {
            do {
                cout << "Enter name of file: " << endl;
                getline(cin, filename);
                int n = filename.length();
                string format = ".txt";
                flag = true;

                if (n > 3) {
                    for (int i = n - 4; i < n; i++) {
                        if (filename[i] != format[i - n + 4]) {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) {
                        cout << "Not valid name of file" << endl;
                        mistake = true;
                    }
                    else if (field.GetFieldFromFile(filename)) {
                        mistake = true;
                        flag = false;
                    }
                    else {
                        cout << "The field have been initialized!" << endl;
                        flag = true;
                    }
                }
            } while (!flag);
        }
        else if (command == "help") {
            CommandList();
        }
        else if (command == "create") {
            long long int clouds_count = 0;
            Point first;
            Point second;
            string command;
            while (true) {
                cout << "Enter x_start, y_start, x_end, y_end: " << endl;
                first.SetX(FoolCheckDouble(true));
                first.SetY(FoolCheckDouble(true));
                second.SetX(FoolCheckDouble(true));
                second.SetY(FoolCheckDouble(true));
                cout << "Enter quantity of points: " << endl;
                long long int count = FoolCheck();
                cloud.Filling(count, first, second);
                field.GetClouds().push_back(cloud.GetCloud());
                if (cloud.GetCloud().size()) {
                    ++clouds_count;
                }
                field.SetCloudsCount(clouds_count);
                field.PrintField();

                if (!field.GetCloudsCount() || !cloud.GetCloud().size()) {
                    cout << "You haven't initialized the field" << endl;
                    mistake = true;
                }
                else {
                    field.AddPointsCount(cloud.GetCloud().size());
                    cin.ignore();
                    WorkList();
                    cout << "Enter work command: " << endl;
                    do {
                        getline(cin, work_com);
                        if (work_com == "help") {
                            WorkList();
                        }
                        else if (work_com == "turn") {
                            cout << "Enter angle: " << endl;
                            int angle = FoolCheck(true);
                            cout << "Enter x: " << endl;
                            long long int x = FoolCheck();
                            cout << "Enter y: " << endl;
                            long long int y = FoolCheck();

                            cloud.Turn(angle, x, y);
                            field.GetClouds().pop_back();
                            field.GetClouds().push_back(cloud.GetCloud());
                            field.PrintField();

                            cout << "The cloud has been turned by " << angle << " degrees around (" << x << ", " << y << ")" << endl;
                        }
                        else if (work_com == "shift x") {
                            cout << "Enter delta x: " << endl;
                            long long int dx = FoolCheck();
                            cloud.ShiftX(dx);
                            field.GetClouds().pop_back();
                            field.GetClouds().push_back(cloud.GetCloud());
                            field.PrintField();

                            cout << "The cloud has been shift by " << dx << endl;
                        }
                        else if (work_com == "shift y") {
                            cout << "Enter delta y: " << endl;
                            long long int dy = FoolCheck();
                            cloud.ShiftY(dy);
                            field.GetClouds().pop_back();
                            field.GetClouds().push_back(cloud.GetCloud());
                            field.PrintField();

                            cout << "The cloud has been shift by " << dy << endl;
                        }
                        else if (work_com != "exit") {
                            if (work_com != "") cout << "Not valid work command (enter help for list of commands)" << endl;
                            else cout << "Enter work command: " << endl;
                        }
                    } while (work_com != "exit");
                    break;

                }
            }
        }
        else if (command == "wave" || command == "hierarchy" || command == "dbscan") {
            if (!field.GetCloudsCount()) {
                cout << "You haven't initialized the field yet." << endl;
                mistake = true;
            }
            else {
                if (command == "wave") {
                    cout << "Set EPS: " << endl;
                    double EPS;
                    EPS = FoolCheckDouble();
                    Wave wave(field.GetClouds());
                    wave.Search(EPS);
                    wave.Print();
                    cin.ignore();
                }
                if (command == "hierarchy") {
                    long long int numb_of_clusters = -1;
                    do {
                        if (numb_of_clusters > field.GetPointsCount()) {
                            cout << "There is not enough points for so many clusters. ";
                        }
                        if (numb_of_clusters == 0) {
                            cout << "You have set zero clusters. ";
                        }
                        cout << "Set quantity of clusters: " << endl;
                        numb_of_clusters = FoolCheck(true);
                    } while (numb_of_clusters > field.GetPointsCount() || numb_of_clusters == 0);
                    Hierarchy hierarchy(field.GetClouds());
                    hierarchy.Search(numb_of_clusters);
                    hierarchy.Print();
                    cin.ignore();
                }
                if (command == "dbscan") {
                    double EPS;
                    long long int min_points;
                    cout << "Set EPS and minimum points in cluster: " << endl;
                    EPS = FoolCheckDouble();
                    min_points = FoolCheck(true);
                    Dbscan dbscan(field.GetClouds());
                    dbscan.Search(EPS, min_points);
                    dbscan.Print();
                    cin.ignore();
                }
            }
        }
        else if (command != "exit") {
            cout << "Not valid command (enter help for list of commands)" << endl;
        }
        if (!mistake && command != "exit") cout << "Enter command: " << endl;
    } while (command != "exit");
}

void Interface::CommandList() {
    cout << "List of command: \n"
        "help - print list of commands\n"
        "name - enter name of file\n"
        "create - create clusters\n"
        "wave - run wave search\n"
        "dbscan - run dbscan search\n"
        "hierarchy - run hierarchy search\n"
        "exit" << endl;
}

void Interface::WorkList() {
    cout << "List of work commands: \n"
        "help - print list of work commands\n"
        "turn - turn cloud at the angle\n"
        "shift x - move cloud by x\n"
        "shift y - move cloud by y\n"
        "exit" << endl;
}
