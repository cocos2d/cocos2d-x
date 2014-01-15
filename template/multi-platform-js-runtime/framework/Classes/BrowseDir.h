
#ifndef  _BROWSE_DIR_H_
#define  _BROWSE_DIR_H_


#ifdef _WIN32
#include <io.h>
#include <stdlib.h>
#include <direct.h>
#define _MAX_PATH_ _MAX_PATH
#else
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#define _MAX_PATH_ PATH_MAX
#endif

#include <stdio.h>
#include <time.h>

#include <vector>
#include <string>
using namespace std;


typedef struct tagFILEINFOR
{
	string fileName;
	int	   fileSize;
	string fileTime;
	tagFILEINFOR()
	{
		fileName="";
		fileSize=0;
		fileTime="";
	}
}FILEINFOR,*PTFILEINFOR;
typedef vector<FILEINFOR> FileInfoList;

/************************
	CBrowseDir browseDir;  
	browseDir.SetFilter(".svn|abc|.jpg|.jpeg|.jpe|","|");
	browseDir.SetInitDir("/home")
    browseDir.BeginBrowse("*.*");  
*********************************/
class CBrowseDir
{
protected:
	char _initDir[_MAX_PATH_];
	vector<string> _filterArray;
	FileInfoList _lFileInfo;

public:

	CBrowseDir();
	bool setInitDir(const char *dir);
	void setFilter(const char *filterfile,const char *delimiter);
	bool beginBrowse(const char *filespec="*.*");
	FileInfoList &getFileInfoList();
protected:

	bool browseDir(const char *dir,const char *filespec);
	void saveFileInfo(const char *dir,_finddata_t fileinfo);

	virtual bool processFile(const char *dir,const char *filename);
	virtual void processDir(const char *currentdir,const char *parentdir);

};

#endif

