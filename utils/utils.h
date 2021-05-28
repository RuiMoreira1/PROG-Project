#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Utils {
public:
    static vector<string> parseString( string &str, char delimiter);

    static bool conditionReducer(char comparable, std::string &conditions);
};

