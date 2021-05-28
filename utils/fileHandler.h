#pragma once
#include <string>
#include "macros.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "../exception.h"
#include "utils.h"

using namespace std;


class fileHandler{
public:
    static void readFile( string &fileName );
    static bool checkExistingFile( string &fileName );
    static void readFile( vector<string> &vec, string &fileName );
    static void buildFile(const string &mazeNumber, int time, string &name);

};
