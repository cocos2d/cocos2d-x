

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
			char szFilterFile[_MAX_PATH_]={0};
			strcpy(szFilterFile,filterfile);
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
#ifdef WIN32
	if (_fullpath(_initDir,dir,_MAX_PATH_) == NULL)
		return false;
#else
    if (realpath(dir, _initDir)== NULL)
		return false;
#endif

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

bool wildcard_matches(const char *wildcard, const char *str) {
	while (1) {
		if (*wildcard == '\0')
			return *str == '\0';
		if (*wildcard == '?') {
			++wildcard; ++str;
		} else if (*wildcard == '*') {
			for (++wildcard; *str; ++str)
				if (wildcard_matches(wildcard, str))
					return true;
			return *wildcard == '\0';
		} else {
			if (*wildcard != *str)
				return false;
			++wildcard; ++str;
		}
	}
}


bool CBrowseDir::browseDir(const char *dir,const char *filespec)
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

					char subdir[_MAX_PATH_];
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
            if (find(_filterArray.begin(),_filterArray.end(),entry->d_name) != _filterArray.end())
            {
                continue;
            }
            char subdir[_MAX_PATH_];
            strcpy(subdir,dir);
            strcat(subdir,entry->d_name);
            strcat(subdir,"/");
            processDir(subdir,dir);
            if (!browseDir(subdir,filespec))
            {
                closedir(dp);
                return false;
            }
		} else {
            
            if (!wildcard_matches(filespec,entry->d_name))
                 continue;
            
            char *pszexten=strrchr(entry->d_name,'.');
            char szextension[_MAX_PATH_]={0};
            if (pszexten)
            {
                strcpy(szextension,"*");
                strcat(szextension,pszexten);
                if (find(_filterArray.begin(),_filterArray.end(),szextension) != _filterArray.end())
                {
                    continue;
                }
            }
            
            strcpy(szextension,entry->d_name);
            if (find(_filterArray.begin(),_filterArray.end(),szextension) != _filterArray.end())
            {
                continue;
            }
            
            if (!processFile(dir,entry->d_name))
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


bool CBrowseDir::processFile(const char *dir,const char *filename)
{
    char fileFullName[_MAX_PATH_]={0};
	char relFileName[_MAX_PATH_] ={0};
    
    strcpy(fileFullName,dir);
	strcat(fileFullName,filename);
    
    struct stat buf;
    if(stat(fileFullName, &buf) != 0)
        return false;
    
    strcpy(relFileName,fileFullName+strlen(_initDir));
    FILEINFOR tempfileinfo;
	tempfileinfo.fileName=relFileName;
	tempfileinfo.fileSize=buf.st_size;
	//tempfileinfo.fileTime=ctime(&buf.st_mtime);
	
	_lFileInfo.push_back(tempfileinfo);
    
	return true;
}

void CBrowseDir::processDir(const char *currentdir,const char *parentdir)
{
}



