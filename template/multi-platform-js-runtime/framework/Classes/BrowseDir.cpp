

#include "BrowseDir.h"


CBrowseDir::CBrowseDir()
{
}

void CBrowseDir::setFilter(const char *filterfile,const char *delimiter)
{
	if (delimiter)
	{
		char *token=NULL;
		if (filterfile)
		{
			token=NULL;
			char szFilterFile[_MAX_PATH]={0};
			strcpy_s(szFilterFile,_MAX_PATH-1,filterfile);
			token = strtok(szFilterFile, delimiter );		
			while( token != NULL )
			{
				_filterArray.push_back(token);
				token = strtok( NULL, delimiter );
			}
		}
	}
}

bool CBrowseDir::setInitDir(const char *dir)
{
	if (_fullpath(_initDir,dir,_MAX_PATH) == NULL)
		return false;

	if (chdir(dir) != 0)
		return false;

	int len=strlen(_initDir);
	if (_initDir[len-1] != '/')
		strcat(_initDir,"/");

	return true;
}

bool CBrowseDir::beginBrowse(const char *filespec)
{
	processDir(_initDir,NULL);
	return browseDir(_initDir,filespec);
}

FileInfoList &CBrowseDir::getFileInfoList()
{
	return _lFileInfo;
}
bool CBrowseDir::browseDir(const char *dir,const char *filespec)
{
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
				char szextension[_MAX_PATH]={0};
				if (pszexten)
				{
					strcpy(szextension,"*");
					strcat(szextension,pszexten);
					if (find(_filterArray.begin(),_filterArray.end(),szextension) != _filterArray.end())
					{
						continue;
					}	
				}

				strcpy(szextension,fileinfo.name);
				if (find(_filterArray.begin(),_filterArray.end(),szextension) != _filterArray.end())
				{
					continue;
				}
				
				saveFileInfo(dir,fileinfo);
				if (!processFile(dir,fileinfo.name))
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
					if (find(_filterArray.begin(),_filterArray.end(),fileinfo.name) != _filterArray.end())
					{
						continue;
					}

					char subdir[_MAX_PATH];
					strcpy(subdir,dir);
					strcat(subdir,fileinfo.name);
					strcat(subdir,"/");
					processDir(subdir,dir);
					if (!browseDir(subdir,filespec))
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
}

void CBrowseDir::saveFileInfo(const char *dir,_finddata_t fileinfo)
{
	char fileFullName[_MAX_PATH]={0};
	char relFileName[_MAX_PATH] ={0};
	char fileTime[_MAX_PATH]={0};

	strcpy(fileFullName,dir);
	strcat(fileFullName,fileinfo.name);
	struct tm *pFileTime = localtime(&fileinfo.time_write);   
	sprintf(fileTime,"%d-%02d-%02d %02d:%02d:%02d",pFileTime->tm_year+1900,pFileTime->tm_mon+1,pFileTime->tm_mday,
		pFileTime->tm_hour,pFileTime->tm_min,pFileTime->tm_sec);

	strcpy(relFileName,fileFullName+strlen(_initDir));
	FILEINFOR tempfileinfo;
	tempfileinfo.fileName=relFileName;
	tempfileinfo.fileSize=fileinfo.size;
	tempfileinfo.fileTime=fileTime;
	
	_lFileInfo.push_back(tempfileinfo);
}


bool CBrowseDir::processFile(const char *dir,const char *filename)
{

	return true;
}

void CBrowseDir::processDir(const char *currentdir,const char *parentdir)
{
}



