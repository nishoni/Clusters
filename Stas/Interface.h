#pragma once

#include <string>
#include "Field.h"
#include "Point.h"
#include "Cloud.h"
#include "Wave.h"
#include "DBscan.h"
#include "Hierarchy.h"

#define ERR_INPUT_INT (-2)
#define ERR_INPUT (-3)

using namespace std;

class Interface {
private:
    string command;
    string work_com;
    string filename;
public:
    void Control();

    void CommandList();
    void WorkList();

    friend double FoolCheckDouble(bool negative);
    friend long long int FoolCheck(bool non_negative);
};