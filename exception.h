#pragma once
#include <string>
using namespace std;


class CantOpenFile : public exception{
private:
    string exception = "Couldn't open the specified file: ";
public:
    explicit CantOpenFile( string &path ) {
        this->exception += path;
    }
    string getException() {
        return this->exception;
    }
};


class gameSymbolNotFound : public exception{
    string exception = "The symbol loaded from the file -> ";
public:
    explicit gameSymbolNotFound( char symbol ){
        this->exception += symbol;
    }
    string getException(){
        return this->exception;
    }
};