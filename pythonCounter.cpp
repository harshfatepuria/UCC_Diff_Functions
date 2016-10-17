#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
using namespace std;

string trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first==last && last==string::npos)
    	return "";
    else
    	return str.substr(first, (last-first+1));
}

int main()
{
		set<string> functions;
		map<int, string> fileMap;
		string line;
	  	ifstream myfile ("reddit_mining.py");
	  	int lineNumber = 1;
	  	
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

	  	if (fileMap.size()>0)
	  	{
	  		for (map<int, string>::iterator it = fileMap.begin(); it != fileMap.end(); ++it) 
	  		{
	  		    string lineOfCode = it->second;
	  		    string temp = trim(lineOfCode);
	  	    	if (temp.length()>0 && (temp.substr(0,4)).compare("def ")==0)
	  	    	{
	  	    		//found a method definition
	  	    		size_t first = temp.find_first_of('(');
	  	    		string function_name=temp.substr(4,(first-4));
	  	    		functions.insert(function_name);
	  	    	}
	  		}
	  		int ii=1;
	  	    for (set<string>::iterator it=functions.begin(); it!=functions.end(); ++it)
	  	    {
	  	    	cout <<"Method "<< ii <<" -->\t" << *it<<endl;
	  	    	ii++;
	  	    }
	  	}






	  	return 0;
}