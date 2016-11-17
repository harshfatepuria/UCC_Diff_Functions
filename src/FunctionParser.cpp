//! FunctionParser class
/*!
* \file FunctionParser.cpp
*
* This file contains the function parsing class methods.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include "FunctionParser.h"
#include "cc_main.h"
#include "CUtil.h"

using namespace std;

FunctionParser::FunctionParser() {}
FunctionParser::~FunctionParser() {}

/*
* 1. Function Description:
*    Call function parser as per the ClassType of file
*
* 2. Parameters:
*    filePath:          path of python source code
*	 dirName:           directory where the output files are to be stored
*    classTypeOfFile:   class type of the file
*
* 3. Creation Time and Owner:
*	 Version 2016.10
*/
void FunctionParser::callParser(string filePath, string dirName, ClassType classTypeOfFile)
{
    switch(classTypeOfFile)
    {
        case PYTHON: 	pythonParser(filePath, dirName);
                     	break;
        case FORTRAN: 	fortranParser(filePath, dirName);
        				break;
        case VERILOG:	verilogParser(filePath, dirName);
        				break;
        default:     cout<<"\n\nUNKNOWN CLASS TYPE. NO PARSER PRESENT FOR THIS CLASS TYPE!\n\n";
                     break;
    }
}


/*
* 1. Function Description: 
*    Calculate number of white spaces in the start of a string
*
* 2. Parameters: 
*    str： string
*
* 3. Creation Time and Owner: 
*	 Version 2016.10
*/
int FunctionParser::numberOfSpacesAtBeginning(string& str)
{
	size_t idx = str.find_first_not_of(" \t\n\r\f");
    if (idx != string::npos)
    	return idx;
   	else
   		return 0;
}


/*
* 1. Function Description: 
*    Parse the methods in a given python source code file and store them in different files
*
* 2. Parameters: 
*    filePath:  path of python source code
*	 dirName:	directory where the output files are to be stored
*
* 3. Creation Time and Owner: 
*	 Version 2016.10
*/
void FunctionParser::pythonParser(string filePath, string dirName)
{
		set<string> functions; //set storing unique method names
		map<int, string> fileMap; //map storing all lines of code against lineNumber

		vector<int> lineNumberOfComments;

		string line;
	  	ifstream myfile (filePath.c_str()); //file to be read
	  	int lineNumber = 1;
	  	int methodCount=0;
	  	int indentLevel=0;

	  	//code to read input python code and store the lines in fileMap
	  	if (myfile.is_open())
	  	{
	  	  while ( getline (myfile,line))
	  	  {
	  	  	fileMap[lineNumber]=line;
	  	  	lineNumber++;
	  	  }
	  	  myfile.close();
	  	}
	  	else 
	  		cout << "Unable to open file" <<endl;

	  	//iterating through the fileMap to identify methods in the python code
	  	if (fileMap.size()>0)
	  	{
	  		for (map<int, string>::iterator it = fileMap.begin(); it != fileMap.end(); ++it) 
	  		{
	  		    string lineOfCode = it->second;
	  		    string temp = CUtil::TrimString(lineOfCode);
	  	    	if (temp.length()>0 && (temp.substr(0,4)).compare("def ")==0)
	  	    	{
	  	    	    size_t first = temp.find_last_of(')');
	  	    		if (first == string::npos)
	  	    		{
	  	    			continue;
	  	    		}
	  	    		else
	  	    		{
	  	    			//found a method definition
	  	    			string function_name = temp.substr(4,(first - 3));
	  	    			functions.insert(function_name);

	  	    			ofstream newMethodFile;
	  	    			string nameOfMethodFile = dirName + "/" + function_name + ".py";
  						newMethodFile.open (nameOfMethodFile.c_str());
  						newMethodFile << lineOfCode << endl;


	  	    			//finding the method body and storing the last line number in methodBodyMap
	  	    			indentLevel = numberOfSpacesAtBeginning(lineOfCode);
	  	    			map<int, string>::iterator it2 = it;
	  	    			it2++;
	  	    			int methodIndentLevel = numberOfSpacesAtBeginning(it2->second);
	  	    			while((CUtil::TrimString(it2->second).length() == 0 || methodIndentLevel > indentLevel || (((CUtil::TrimString(it2->second)).substr(0,1)).compare("#") == 0)) && it2 != fileMap.end())
	  	    			{
	  	    				if (CUtil::TrimString(it2->second).length() > 0)
	  	    				{
	  	    					newMethodFile << it2->second << endl;
	  	    				}
	  	    				it2++;
	  	    				methodIndentLevel = numberOfSpacesAtBeginning(it2->second);
	  	    			}
	  	    			newMethodFile.close();
	  	    		}
	  	    	}
	  		}
	  	}
}




/*
* 1. Function Description: 
*    Parse the methods in a given fortran source code file and store them in different files
*
* 2. Parameters: 
*    filePath:  path of fortran source code
*	 dirName:	directory where the output files are to be stored
*
* 3. Creation Time and Owner: 
*	 Version 2016.11
*/
void FunctionParser::fortranParser(string filePath, string dirName)
{
		set<string> functions; //set storing unique method names
		map<int, string> fileMap; //map storing all lines of code against lineNumber

		string line;
	  	ifstream myfile (filePath.c_str()); //file to be read
	  	int lineNumber = 1;
	  	int methodCount=0;

	  	//code to read input fortran code and store the lines in fileMap
	  	if (myfile.is_open())
	  	{
	  	  while ( getline (myfile,line))
	  	  {
	  	  	fileMap[lineNumber]=line;
	  	  	lineNumber++;
	  	  }
	  	  myfile.close();
	  	}
	  	else 
	  		cout << "Unable to open file" <<endl;

	  	//iterating through the fileMap to identify methods in the fortran code
	  	if (fileMap.size()>0)
	  	{
	  		for (map<int, string>::iterator it = fileMap.begin(); it != fileMap.end(); ++it) 
	  		{
	  		    string lineOfCode = it->second;
	  		    string temp = CUtil::TrimString(lineOfCode);
	  	    	if (temp.length()>0 && (CUtil::ToLower(temp.substr(0,9))).compare("function ")==0)
	  	    	{
	  	    	    size_t first = temp.find_last_of(')');
	  	    		if (first == string::npos)
	  	    		{
	  	    			continue;
	  	    		}
	  	    		else
	  	    		{
	  	    			//found a method definition
	  	    			string function_name = temp.substr(9,(first - 8));
	  	    			functions.insert(function_name);

	  	    			ofstream newMethodFile;
	  	    			string nameOfMethodFile = dirName + "/" + function_name + ".f";
  						newMethodFile.open (nameOfMethodFile.c_str());
  						newMethodFile << lineOfCode << endl;


	  	    			map<int, string>::iterator it2 = it;
	  	    			it2++;
	  	    			int isEndFunctionPresent = (CUtil::ToLower(CUtil::TrimString(it2->second).substr(0,12))).compare("end function");
	  	    			while((CUtil::TrimString(it2->second).length() == 0 || isEndFunctionPresent != 0) && it2 != fileMap.end())
	  	    			{
	  	    				if (CUtil::TrimString(it2->second).length() > 0)
	  	    				{
	  	    					newMethodFile << it2->second << endl;
	  	    				}
	  	    				it2++;
	  	    				isEndFunctionPresent = (CUtil::ToLower(CUtil::TrimString(it2->second).substr(0,12))).compare("end function");	
	  	    			}
	  	    			if (isEndFunctionPresent == 0)
	  	    				newMethodFile << it2->second << endl;
	  	    			newMethodFile.close();
	  	    		}
	  	    	}
	  		}
	  	}
}





/*
* 1. Function Description: 
*    Parse the methods in a given verilog source code file and store them in different files
*
* 2. Parameters: 
*    filePath:  path of verilog source code
*	 dirName:	directory where the output files are to be stored
*
* 3. Creation Time and Owner: 
*	 Version 2016.11
*/
void FunctionParser::verilogParser(string filePath, string dirName)
{
		set<string> functions; //set storing unique method names
		map<int, string> fileMap; //map storing all lines of code against lineNumber

		string line;
	  	ifstream myfile (filePath.c_str()); //file to be read
	  	int lineNumber = 1;
	  	int methodCount=0;

	  	//code to read input verilog code and store the lines in fileMap
	  	if (myfile.is_open())
	  	{
	  	  while ( getline (myfile,line))
	  	  {
	  	  	fileMap[lineNumber]=line;
	  	  	lineNumber++;
	  	  }
	  	  myfile.close();
	  	}
	  	else 
	  		cout << "Unable to open file" <<endl;

	  	//iterating through the fileMap to identify methods in the verilog code
	  	if (fileMap.size()>0)
	  	{
	  		for (map<int, string>::iterator it = fileMap.begin(); it != fileMap.end(); ++it) 
	  		{
	  		    string lineOfCode = it->second;
	  		    string temp = CUtil::TrimString(lineOfCode);
	  	    	if (temp.length()>0 && (CUtil::ToLower(temp.substr(0,9))).compare("function ")==0)
	  	    	{
	  	    	    size_t first = temp.find_last_of(';');
	  	    		if (first == string::npos)
	  	    		{
	  	    			continue;
	  	    		}
	  	    		else
	  	    		{
	  	    			//found a method definition
	  	    			string function_name = temp.substr(9,(first - 9));
	  	    			functions.insert(function_name);

	  	    			ofstream newMethodFile;
	  	    			string nameOfMethodFile = dirName + "/" + function_name + ".v";
  						newMethodFile.open (nameOfMethodFile.c_str());
  						newMethodFile << lineOfCode << endl;


	  	    			map<int, string>::iterator it2 = it;
	  	    			it2++;
	  	    			int isEndFunctionPresent = (CUtil::ToLower(CUtil::TrimString(it2->second).substr(0,11))).compare("endfunction");
	  	    			while((CUtil::TrimString(it2->second).length() == 0 || isEndFunctionPresent != 0) && it2 != fileMap.end())
	  	    			{
	  	    				if (CUtil::TrimString(it2->second).length() > 0)
	  	    				{
	  	    					newMethodFile << it2->second << endl;
	  	    				}
	  	    				it2++;
	  	    				isEndFunctionPresent = (CUtil::ToLower(CUtil::TrimString(it2->second).substr(0,11))).compare("endfunction");	
	  	    			}
	  	    			if (isEndFunctionPresent == 0)
	  	    				newMethodFile << it2->second << endl;
	  	    			newMethodFile.close();
	  	    		}
	  	    	}
	  		}
	  	}
}
