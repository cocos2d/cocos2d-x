
#include <io.h>
#include <direct.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "cocos2d.h"
using namespace std;


string getProjSearchPath()
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
	searchPathArray.push_back(getProjSearchPath());
	searchPathArray.push_back(searchPathRes);
	return searchPathArray;
}

string getIPAddress()
{
	WSADATA wsaData;  
	char name[155]={0};
	char *ip=nullptr;
	PHOSTENT hostinfo;

	if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )   
	{  
		if( gethostname ( name, sizeof(name)) == 0)   
		{ 
			if((hostinfo = gethostbyname(name)) != NULL)   
			{ 
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
			}   
		}   
		WSACleanup( );
	}   
	return ip;
}
