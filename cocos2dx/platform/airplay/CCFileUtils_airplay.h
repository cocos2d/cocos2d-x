#ifndef __PLATFORM_AIRPLAY_CCFILE_UTILS_H__
#define __PLATFORM_AIRPLAY_CCFILE_UTILS_H__

#include "string.h"
#include "CCMutableDictionary.h"
#include "FileUtils.h"

NS_CC_BEGIN;

//! @brief  Helper class to handle file operations
class CC_DLL CCFileUtils : public FileUtils
{
public:

    /**
    @brief   Generate the absolute path of the file.
    @param   pszRelativePath     The relative path of the file.
    @return  The absolute path of the file.
    @warning We only add the ResourcePath before the relative path of the file.
             If you have not set the ResourcePath,the function add "/NEWPLUS/TDA_DATA/UserData/" as default.
             You can set ResourcePath by function void setResourcePath(const char *pszResourcePath);
    */
	static const char* fullPathFromRelativePath(const char *pszRelativePath);

	/// @cond
	static const char* fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile);
	/// @endcond

    /**
    @brief   Generate a NSDictionary pointer by file
    @param   pFileName  The file name of *.plist file
    @return  The NSDictionary pointer generated from the file
    */
	static CCDictionary<std::string, CCObject*> *dictionaryWithContentsOfFile(const char *pFileName);
	
	/**
    @brief Get resource file data
    @param[in]  pszFileName The resource file name which contain the path
    @param[in]  pszMode The read mode of the file
    @param[out] pSize If get the file data succeed the it will be the data size,or it will be 0
    @return if success,the pointer of data will be returned,or NULL is returned
    @warning If you get the file data succeed,you must delete it after used.
    */
	static unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
	
	
private:
//	static std::string m_sRelativePath;
//	static std::string m_sResourcePath;
};
NS_CC_END;

#endif // __PLATFORM_UPHONE_CCFILE_UTILS_H__
