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
#include "CCScheduler.h"

#ifdef _WIN32
#define realpath(dir,fuldir) _fullpath(fuldir,dir,_MAX_PATH_)
#else
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#endif

#include <vector>
#include <string>

using namespace std;
using namespace cocos2d;

extern string getDotWaitFilePath();
extern string getProjSearchPath();
extern vector<string> getSearchPath();
extern bool browseDir(const char *dir,const char *filespec,vector<string> &filterArray,vector<std::string> &fileList);

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
		{
			return *str == '\0';
		}
		if (*wildcard == '?') 
		{
			++wildcard; ++str;
		} 
		else if (*wildcard == '*') 
		{
			for (++wildcard; *str; ++str)
			{
				if (wildcardMatches(wildcard, str))
				{
					return true;
				}
			}
			return *wildcard == '\0';
		} 
		else 
		{
			if (*wildcard != *str)
			{
				return false;
			}
			++wildcard; ++str;
		}
	}
}


#ifndef _WIN32
/*
*@brief iterator directory and process file.
*/
bool browseDir(const char *dir,const char *filespec,vector<string> &filterArray,vector<std::string> &fileList)
{
	DIR *dp=NULL;
	struct dirent *entry=NULL;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL) 
	{
		return false;
	}

	if (chdir(dir) != 0)
	{
		return false;
	}

	while((entry = readdir(dp)) != NULL) 
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) 
		{
			if(strcmp(".",entry->d_name) == 0 ||strcmp("..",entry->d_name) == 0)
			{
				continue;
			}

			if (find(filterArray.begin(),filterArray.end(),entry->d_name) != filterArray.end())
			{
				continue;
			}

			char subdir[_MAX_PATH_]={0};
			sprintf(subdir,"%s%s/",dir,entry->d_name);
			if (!browseDir(subdir,filespec,filterArray,fileList))
			{
				closedir(dp);
				return false;
			}
		} 
		else 
		{

			if (!wildcardMatches(filespec,entry->d_name))
			{
				continue;
			}

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
vector<std::string> searchFileList(string &dir,const char *filespec="*.*",const char *filterfile=NULL)
{
	char fulldir[_MAX_PATH_]={0};
	vector<string> _filterArray;
	vector<std::string> _lfileList;
	_filterArray = splitFilter(filterfile);

	if (realpath(dir.c_str(), fulldir)== NULL)
	{
		return _lfileList;
	}

	int len=strlen(fulldir);
	if (fulldir[len-1] != '/')
	{
		strcat(fulldir,"/");
	}

	browseDir(fulldir,filespec,_filterArray,_lfileList);
	dir =fulldir;
	return _lfileList;
}

void startScript()
{
	ScriptEngineProtocol *engine = ScriptingCore::getInstance();
	ScriptEngineManager::getInstance()->setScriptEngine(engine);
	ScriptingCore::getInstance()->runScript("cocos2d-jsb.js");
}

void reloadScript()
{
    
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
			startScript();	
		}
	}
	void waitDebugConnect(void)
	{
		_dotwaitFile = getDotWaitFilePath();
		_jsSearchPath = getProjSearchPath();
		vector<std::string> fileInfoList = searchFileList(_jsSearchPath,"*.js","runtime|framework|");
		for (unsigned i = 0; i < fileInfoList.size(); i++)
		{
			ScriptingCore::getInstance()->compileScript(fileInfoList[i].substr(_jsSearchPath.length(),-1).c_str());
		}

		if (!FileUtils::getInstance()->isFileExist(_dotwaitFile))
		{
			startScript();
			return;
		}

		if (_scheduler)
		{
			_scheduler->scheduleSelector(SEL_SCHEDULE(&ConnectWaiter::updateConnect), this,0.5f, false);
		}
	}
private:
	ConnectWaiter()
	{
		_scheduler = CCDirector::sharedDirector()->getScheduler();
	}

	cocos2d::Scheduler *_scheduler;
	string _dotwaitFile;
	string _jsSearchPath;
};

void startRuntime()
{	
	vector<string> searchPathArray;
	searchPathArray = getSearchPath();
	for (unsigned i = 0; i < searchPathArray.size(); i++)
	{
		FileUtils::getInstance()->addSearchPath(searchPathArray[i]);
	}
#ifdef COCOS2D_DEBUG
	ScriptingCore::getInstance()->start();
	ScriptingCore::getInstance()->enableDebugger();
	ScriptEngineProtocol *engine = ScriptingCore::getInstance();
	ScriptEngineManager::getInstance()->setScriptEngine(engine);
	ScriptingCore::getInstance()->runScript("jsb.js");
	ConnectWaiter::getInstance().waitDebugConnect();
#else
	ScriptingCore::getInstance()->start();
	startScript();
#endif
}




// SimulatorConfig
SimulatorConfig *SimulatorConfig::s_sharedInstance = NULL;
SimulatorConfig *SimulatorConfig::getInstance(void)
{
	if (!s_sharedInstance)
	{
		s_sharedInstance = new SimulatorConfig();
	}
	return s_sharedInstance;
}

SimulatorConfig::SimulatorConfig(void)
{
	m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 3Gs (480x320)", 480, 320));
	m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 4 (960x640)", 960, 640));
	m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 5 (1136x640)", 1136, 640));
	m_screenSizeArray.push_back(SimulatorScreenSize("iPad (1024x768)", 1024, 768));
	m_screenSizeArray.push_back(SimulatorScreenSize("iPad Retina (2048x1536)", 2048, 1536));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (800x480)", 800, 480));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (854x480)", 854, 480));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (960x540)", 960, 540));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (1024x600)", 1024, 600));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (1280x720)", 1280, 720));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (1280x800)", 1280, 800));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (1920x1080)", 1920, 1080));
}

int SimulatorConfig::getScreenSizeCount(void)
{
	return (int)m_screenSizeArray.size();
}

const SimulatorScreenSize SimulatorConfig::getScreenSize(int index)
{
	return m_screenSizeArray.at(index);
}