//! FunctionParser class
/*!
* \file FunctionParser.h
*
* This file contains the function parsing class methods definition.
*/

#ifndef FUNCTIONPARSER_H
#define FUNCTIONPARSER_H

using namespace std;

class FunctionParser
{
public:
    FunctionParser();
    ~FunctionParser();
    void pythonParser(string filePath, string dirName);
    int numberOfSpacesAtBeginning(string& str);
    string trim(string& str);
};



#endif // FUNCTIONPARSER_H
