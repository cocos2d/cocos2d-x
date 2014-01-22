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

#ifdef _WIN32
#include <io.h>
#include <direct.h>
#define _MAX_PATH_ _MAX_PATH
#else
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <unistd.h>
#define _MAX_PATH_ PATH_MAX
#endif

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cocos2d;

char g_initDir[_MAX_PATH_]={0};
/*@brief   use "|" splite string  */
vector<string> &splitFilter(const char *str)
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
*@brief get relative path and save to StringList
*/
bool processFile(const char *dir,const char *filename,StringList &fileList)
{
	char fileFullName[_MAX_PATH_]={0};
	char relFileName[_MAX_PATH_] ={0};

	strcpy(fileFullName,dir);
	strcat(fileFullName,filename);

	struct stat buf;
	if(stat(fileFullName, &buf) != 0)
		return false;

	strcpy(relFileName,fileFullName+strlen(g_initDir));
	fileList.push_back(relFileName);    
	return true;
}

/*
*@brief iterator directory and process file.
*/
bool browseDir(const char *dir,const char *filespec,vector<string> &filterArray,StringList &fileList)
{
#ifdef WIN32
	if (chdir(dir) != 0)
		return false;
	long hFile;
	_finddata_t fileinfo;
	if ((hFile=_findfirst(filespec,&fileinfo)) != -1)
	{
		do
		{
			if (!(fileinfo.attrib & _A_SUBDIR))
			{
				char *pszexten=strrchr(fileinfo.name,'.');
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

				strcpy(szextension,fileinfo.name);
				if (find(filterArray.begin(),filterArray.end(),szextension) != filterArray.end())
				{
					continue;
				}

				if (!processFile(dir,fileinfo.name,fileList))
					return false;
			}
		} while (_findnext(hFile,&fileinfo) == 0);
		_findclose(hFile);
	}

	if (chdir(dir) != 0)
		return false;
	if ((hFile=_findfirst("*.*",&fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name,".") != 0 && strcmp
					(fileinfo.name,"..") != 0)
				{
					if (find(filterArray.begin(),filterArray.end(),fileinfo.name) != filterArray.end())
					{
						continue;
					}

					char subdir[_MAX_PATH_];
					strcpy(subdir,dir);
					strcat(subdir,fileinfo.name);
					strcat(subdir,"/");
					if (!browseDir(subdir,filespec,filterArray,fileList))
					{
						_findclose(hFile);
						return false;
					}
				}
			}
		} while (_findnext(hFile,&fileinfo) == 0);
		_findclose(hFile);
	}
	return true;
#else
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
			strcpy(subdir,dir);
			strcat(subdir,entry->d_name);
			strcat(subdir,"/");
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

			if (!processFile(dir,entry->d_name,fileList))
			{
				closedir(dp);
				return false;
			}
		}
	}
	chdir("..");
	closedir(dp);
	return true;
#endif

}

/*
*@brief search File from directory.
*/
StringList searchFileList(const char *dir,const char *filespec,const char *filterfile)
{
	memset(g_initDir,0,sizeof(g_initDir));
	vector<string> _filterArray;
	StringList _lfileList;
	_filterArray = splitFilter(filterfile);

#ifdef WIN32
	if (_fullpath(g_initDir,dir,_MAX_PATH_) == NULL)
		return _lfileList;
#else
	if (realpath(dir, g_initDir)== NULL)
		return _lfileList;
#endif

	if (chdir(dir) != 0)
		return _lfileList;

	int len=strlen(g_initDir);
	if (g_initDir[len-1] != '/')
		strcat(g_initDir,"/");

	browseDir(g_initDir,filespec,_filterArray,_lfileList);

	return _lfileList;
}


Runtime::Runtime()
{
	_scheduler = CCDirector::sharedDirector()->getScheduler();
}

Runtime::~Runtime()
{
}

void Runtime::resetRuntime()
{
	ScriptEngineProtocol *engine = ScriptingCore::getInstance();
	ScriptEngineManager::getInstance()->setScriptEngine(engine);
 	ScriptingCore::getInstance()->runScript("cocos2d-jsb.js");
}

Runtime& Runtime::getInstance()
{
	static Runtime s_SharedRuntime;
	return s_SharedRuntime;
}

void Runtime::setSearchPath()
{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
		extern std::string getCurAppPath(void);
		_searchPath = getCurAppPath();
		_searchPath += "/../..";
		string searchPathRes = getCurAppPath();
		searchPathRes += "/HelloJavascriptRes";
		FileUtils::getInstance()->addSearchPath(_searchPath.c_str());
		FileUtils::getInstance()->addSearchPath(searchPathRes.c_str());
#endif

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	extern std::string getPackageNameJNI();
	_searchPath = "/mnt/sdcard/";
	_searchPath += getPackageNameJNI();
	FileUtils::getInstance()->addSearchPath(_searchPath.c_str());
#endif
   
}
void Runtime::updateConnect(float delta)
{
    FileUtils::getInstance()->purgeCachedEntries();
	if (!FileUtils::getInstance()->isFileExist(_dotwaitFile.c_str()))
	{
		_scheduler->unscheduleSelector(SEL_SCHEDULE(&Runtime::updateConnect),this);
		resetRuntime();	
	}
}
void Runtime::waitDebugConnect()
{
	StringList fileInfoList = searchFileList(_searchPath.c_str(),"*.js","runtime|framework|");
	for (int i = 0; i < fileInfoList.size(); i++)
	{
		ScriptingCore::getInstance()->compileScript(fileInfoList[i].c_str());
	}

#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	extern std::string getCurAppPath(void);
	_dotwaitFile = getCurAppPath();
	_dotwaitFile += "/.wait";
#endif

#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID )
	extern std::string getPackageNameJNI();
	string searchPath = getPackageNameJNI();
	_dotwaitFile = "/mnt/sdcard/";
	_dotwaitFile += searchPath;
	_dotwaitFile += "/.wait";
#endif	

#if (CC_TARGET_PLATFORM==CC_PLATFORM_MAC || CC_TARGET_PLATFORM==CC_PLATFORM_IOS )
    extern std::string getResourcePath();
    _dotwaitFile = getResourcePath();
    _dotwaitFile += "/.wait";
#endif
    
    
	if (!FileUtils::getInstance()->isFileExist(_dotwaitFile.c_str()))
	{
		resetRuntime();
		return;
	}
		
	if (_scheduler)
		_scheduler->scheduleSelector(SEL_SCHEDULE(&Runtime::updateConnect), this,0.5f, false);
}

