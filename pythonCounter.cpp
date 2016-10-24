#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
using namespace std;

string trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    size_t first_tab = str.find_first_not_of('\t');
    size_t last_tab = str.find_last_not_of(' ');
    if (first_tab < first && first_tab != string::npos)
    {
    	return str.substr(first_tab, (last-first_tab+1));
    }
    else if (first==last && last==string::npos)
    	return "";
    else
    	return str.substr(first, (last-first+1));
}

int numberOfSpacesAtBeginning(string& str)
{
	return str.find_first_not_of(' ');
}

void pythonParser(string filePath)
{
		set<string> functions; //set storing unique method names
		map<int, string> fileMap; //map storing all lines of code against lineNumber

		vector<int> lineNumberOfComments;

		string line;
	  	ifstream myfile (filePath); //file to be read
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
	  		cout << "Unable to open file"; 

	  	//iterating through the fileMap to identify methods in the python code
	  	if (fileMap.size()>0)
	  	{
	  		//find comments
	  	// 	for (map<int, string>::iterator it = fileMap.begin(); it != fileMap.end();) 
	  	// 	{
	  	// 		string lineOfCode = it->second;
	  	// 	    string temp = trim(lineOfCode);
	  	// 	    if ((temp.substr(0,1)).compare("#")==0)
				// {
				// 	lineNumberOfComments.push_back(it->first);
				// 	it++;
				// 	continue;
				// }
				// else if(temp.substr(0,3)).compare("'''")==0)
				// {
				// 	it++;
				// 	continue;
				// }
				// it++;
	  	// 	}


	  		for (map<int, string>::iterator it = fileMap.begin(); it != fileMap.end(); ++it) 
	  		{
	  		    string lineOfCode = it->second;
	  		    string temp = trim(lineOfCode);
	  	    	if (temp.length()>0 && (temp.substr(0,4)).compare("def ")==0)
	  	    	{
	  	    		size_t first = temp.find_first_of('(');
	  	    		if (first==string::npos)
	  	    		{
	  	    			continue;
	  	    		}
	  	    		else
	  	    		{
	  	    			//found a method definition
	  	    			string function_name=temp.substr(4,(first-4));
	  	    			functions.insert(function_name);

	  	    			ofstream newMethodFile;
  						newMethodFile.open (function_name+".py");
  						newMethodFile << lineOfCode << endl;


	  	    			//finding the method body and storing the last line number in methodBodyMap
	  	    			indentLevel=numberOfSpacesAtBeginning(lineOfCode);
	  	    			map<int, string>::iterator it2=it;
	  	    			it2++;
	  	    			int methodIndentLevel=numberOfSpacesAtBeginning(it2->second);
	  	    			while((trim(it2->second).length()==0 || methodIndentLevel>indentLevel || (((trim(it2->second)).substr(0,1)).compare("#")==0)) && it2 != fileMap.end())
	  	    			{
	  	    				newMethodFile << it2->second << endl;
	  	    				it2++;
	  	    				int currentLineNumber= it2->first;
	  	    				methodIndentLevel=numberOfSpacesAtBeginning(it2->second);
	  	    			}
	  	    			newMethodFile.close();
	  	    		}
	  	    	}
	  		}

	  		methodCount=functions.size();
	  		if (methodCount>0)
	  		{
	  				cout<<methodCount<<" methods identified"<<endl;

	  				int ii=1;
	  			    for (set<string>::iterator it=functions.begin(); it!=functions.end(); ++it)
	  			    {
	  			    	cout <<"Method "<< ii <<" -->\t" << *it<<endl;
	  			    	ii++;
	  			    }
	  		}
	  	}
}

int main()
{
	pythonParser("reddit_mining.py");
	return 0;
}