/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "Runtime.h"

#include "SimpleAudioEngine.h"
#include "jsb_cocos2dx_auto.hpp"
#include "jsb_cocos2dx_extension_auto.hpp"
#include "jsb_cocos2dx_builder_auto.hpp"
#include "extension/jsb_cocos2dx_extension_manual.h"
#include "cocosbuilder/js_bindings_ccbreader.h"
#include "localstorage/js_bindings_system_registration.h"
#include "chipmunk/js_bindings_chipmunk_registration.h"
#include "jsb_opengl_registration.h"

#ifndef _WIN32
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#endif

#include "CCScheduler.h"

#include <vector>
#include <string>

using namespace std;
using namespace cocos2d;

/*@brief   use "|" splite string  */
vector<string> splitFilter(const char *str)
{
	vector<string> filterArray;
	if (str)
	{
		char *token=NULL;
		char szFilterFile[_MAX_PATH_]={0};
		strcpy(szFilterFile,str);
		token = strtok(szFilterFile, "|" );		
		while( token != NULL )
		{
			filterArray.push_back(token);
			token = strtok( NULL, "|");
		}
	}
	return filterArray;
}

/*@brief wildcard funciton*/
bool wildcardMatches(const char *wildcard, const char *str) 
{
	while (1) {
		if (*wildcard == '\0')
			return *str == '\0';
		if (*wildcard == '?') {
			++wildcard; ++str;
		} else if (*wildcard == '*') {
			for (++wildcard; *str; ++str)
				if (wildcardMatches(wildcard, str))
					return true;
			return *wildcard == '\0';
		} else {
			if (*wildcard != *str)
				return false;
			++wildcard; ++str;
		}
	}
}

/*
*@brief iterator directory and process file.
*/
#ifndef _WIN32
bool browseDir(const char *dir,const char *filespec,vector<string> &filterArray,vector<std::string> &fileList)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL) {
		return false;
	}
	if (chdir(dir) != 0)
		return false;
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) {

			if(strcmp(".",entry->d_name) == 0 ||
				strcmp("..",entry->d_name) == 0)
				continue;
			if (find(filterArray.begin(),filterArray.end(),entry->d_name) != filterArray.end())
			{
				continue;
			}
			char subdir[_MAX_PATH_];
			sprintf(subdir,"%s%s/",dir,entry->d_name);
			if (!browseDir(subdir,filespec,filterArray,fileList))
			{
				closedir(dp);
				return false;
			}
		} else {

			if (!wildcardMatches(filespec,entry->d_name))
				continue;

			char *pszexten=strrchr(entry->d_name,'.');
			char szextension[_MAX_PATH_]={0};
			if (pszexten)
			{
				strcpy(szextension,"*");
				strcat(szextension,pszexten);
				if (find(filterArray.begin(),filterArray.end(),szextension) != filterArray.end())
				{
					continue;
				}
			}

			strcpy(szextension,entry->d_name);
			if (find(filterArray.begin(),filterArray.end(),szextension) != filterArray.end())
			{
				continue;
			}

			char fullFileName[_MAX_PATH_] ={0};
			sprintf(fullFileName,"%s%s",dir,entry->d_name);
			fileList.push_back(fullFileName);
		}
	}
	chdir("..");
	closedir(dp);
	return true;
}
#endif


/************************
* Get file list from specified directory. 
*
*@param dir		    search directory
*@param filespec    search specified type file
*@param filterfile  filter file or folder
*
*Like this:
*    searchFileList("/home","*.*",".svn|.jpg|");  
*********************************/
vector<std::string> searchFileList(string &dir,const char *filespec="*.*",const char *filterfile=NULL);
vector<std::string> searchFileList(string &dir,const char *filespec,const char *filterfile)
{
	char fuldir[_MAX_PATH_]={0};
	vector<string> _filterArray;
	vector<std::string> _lfileList;
	_filterArray = splitFilter(filterfile);

#ifdef WIN32
	if (_fullpath(fuldir,dir.c_str(),_MAX_PATH_) == NULL)
		return _lfileList;
#else
	if (realpath(dir.c_str(), fuldir)== NULL)
		return _lfileList;
#endif
	int len=strlen(fuldir);
	if (fuldir[len-1] != '/')
		strcat(fuldir,"/");

	extern bool browseDir(const char *dir,const char *filespec,vector<string> &filterArray,vector<std::string> &fileList);
	browseDir(fuldir,filespec,_filterArray,_lfileList);
	dir =fuldir;
	return _lfileList;
}

void resetRuntime()
{
	ScriptEngineProtocol *engine = ScriptingCore::getInstance();
	ScriptEngineManager::getInstance()->setScriptEngine(engine);
	ScriptingCore::getInstance()->runScript("cocos2d-jsb.js");
}

class ConnectWaiter: public Object
{
public:
	static ConnectWaiter& getInstance()
	{
		static ConnectWaiter instance;
		return instance;
	}
	void updateConnect(float delta)
	{
		FileUtils::getInstance()->purgeCachedEntries();
		if (!FileUtils::getInstance()->isFileExist(_dotwaitFile))
		{
			_scheduler->unscheduleSelector(SEL_SCHEDULE(&ConnectWaiter::updateConnect),this);
			resetRuntime();	
		}
	}
	void waitDebugConnect(void)
	{
		extern string getDotWaitFilePath();
		_dotwaitFile = getDotWaitFilePath();
		extern string getJsSearchPath();
		_jsSearchPath = getJsSearchPath();
		vector<std::string> fileInfoList = searchFileList(_jsSearchPath,"*.js","runtime|framework|");
		for (unsigned i = 0; i < fileInfoList.size(); i++)
		{
			ScriptingCore::getInstance()->compileScript(fileInfoList[i].substr(_jsSearchPath.length(),-1).c_str());
		}

		if (!FileUtils::getInstance()->isFileExist(_dotwaitFile))
		{
			resetRuntime();
			return;
		}

		if (_scheduler)
			_scheduler->scheduleSelector(SEL_SCHEDULE(&ConnectWaiter::updateConnect), this,0.5f, false);
	}
private:
	ConnectWaiter()
	{
		_scheduler = CCDirector::sharedDirector()->getScheduler();
	}
private:
cocos2d::Scheduler *_scheduler;
string _dotwaitFile;
string _jsSearchPath;
};

void RuntimeInit()
{
#ifdef COCOS2D_DEBUG
	vector<string> searchPathArray;
	extern vector<string> getSearchPath();
	searchPathArray = getSearchPath();
	for (unsigned i = 0; i < searchPathArray.size(); i++)
	{
		FileUtils::getInstance()->addSearchPath(searchPathArray[i]);
	}
	ScriptingCore::getInstance()->start();
	ScriptingCore::getInstance()->enableDebugger();
	ConnectWaiter::getInstance().waitDebugConnect();
#else
	ScriptingCore::getInstance()->start();
	resetRuntime();
#endif
}

