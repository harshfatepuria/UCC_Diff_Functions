#ifndef FUNCTIONPARSER_H
#define FUNCTIONPARSER_H

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
