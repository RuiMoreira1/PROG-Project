#include "fileHandler.h"

/**
 * @brief Read file and output the content to the console
 * @param fileName - file name
 */
void fileHandler::readFile( string &fileName ) {
    fstream file;
    file.open(fileName, ios::in);
    try {
        cout << endl;
        if (file) {
            string temp;
            while (getline(file, temp)) cout << temp << "\n";
        }
        else throw CantOpenFile(fileName);
    }
    catch ( CantOpenFile &exc ){
        cerr << exc.getException() << endl;
        exit(ERROR);
    }
    file.close();
}

/**
 * @brief Check existing file
 * @param fileName - file name
 * @return true upon success, false otherwise
 */
bool fileHandler::checkExistingFile(string &fileName) {
    fstream file;
    file.open(fileName, ios::in | ios::out);
    if( file.is_open() ){
        file.close();
        return true;
    }
    return false;
}

/**
 * @brief Read file and put each line inside a vector
 * @param fileName - file name
 * @param vec - contains each file line
 */
void fileHandler::readFile(vector<string> &vec, string &fileName) {
    fstream file;
    file.open(fileName, ios::in);
    try {
        cout << endl;
        if (file) {
            string temp;
            while (getline(file, temp)) vec.push_back(temp);
        }
        else throw CantOpenFile(fileName);
    }
    catch ( CantOpenFile &exc ){
        cerr << exc.getException() << endl;
        exit(ERROR);
    }
    file.close();
}

/**
 * @brief Sort Function
 * @param str1
 * @param str2
 * @return
 */
bool compare( string &str1, string &str2 ){
    string str11 = str1;
    str11.erase(0,17);
    string str22 = str2;
    str22.erase(0,17);
    return (str11 < str22);
}

/**
 * @brief Build winner file
 * @param mazeNumber
 * @param time - execution time
 * @param name - player name
 */
void fileHandler::buildFile(const string &mazeNumber, int time, string &name) {
    fstream file;
    string temp = "files/MAZE_";
    temp += mazeNumber + "_WINNERS.txt";
    vector<string> res;
    readFile(res,temp);
    string newstr = name;
    for( int i = newstr.size(); i <= 15; i++ ){
        if( i == 15 ) newstr += '-';
        else newstr += ' ';
    }
    newstr += " " + to_string(time);
    res.push_back(newstr);
    sort(res.begin()+2, res.end(), compare);

    for(string &r: res) {
        cout << r << endl;
    }
    file.open(temp, ios::out);
    try {
        cout << endl;
        if (file) {
            for( string &it : res){
                file << it << endl;
            }

        }
        else throw CantOpenFile(temp);
    }
    catch ( CantOpenFile &exc ){
        cerr << exc.getException() << endl;
        exit(ERROR);
    }
    file.close();

}
