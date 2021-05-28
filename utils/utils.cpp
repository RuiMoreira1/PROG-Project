#include "utils.h"

vector<string> Utils::parseString(string &str, char delimiter) {
    vector<string> result;
    stringstream stream(str);
    string temp;
    while( getline( stream, temp, delimiter) ) result.push_back(temp);
    return result;

}

bool Utils::conditionReducer(char comparable, std::string &conditions) {
    for( char i : conditions ){
        if( comparable == i ) return true;
    }
    return false;
}
