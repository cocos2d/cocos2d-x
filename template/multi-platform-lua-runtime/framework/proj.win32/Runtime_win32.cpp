
#include <io.h>
#include <direct.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "cocos2d.h"
using namespace std;


string getProSearchPath()
{
	extern std::string getCurAppPath(void);
	string searchPath = getCurAppPath();
	searchPath += "/../..";
	char fuldir[MAX_PATH]={0};
	_fullpath(fuldir,searchPath.c_str(),MAX_PATH);
	return fuldir;
}

vector<string> getSearchPath()
{
	extern std::string getCurAppPath(void);
	vector<string> searchPathArray;
	string searchPathRes = getCurAppPath();
	searchPathRes += "/Resources";
	searchPathArray.push_back(getProSearchPath());
	searchPathArray.push_back(searchPathRes);
	return searchPathArray;
}
