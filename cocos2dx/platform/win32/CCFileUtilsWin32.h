#ifndef __CC_FILEUTILS_WIN32_H__
#define __CC_FILEUTILS_WIN32_H__

#include "platform/CCFileUtils.h"
#include <windows.h>

NS_CC_BEGIN

class CC_DLL CCFileUtilsWin32 :
	public CCFileUtils
{
public:
	CCFileUtilsWin32();

	virtual const char* fullPathFromRelativePath(const char *pszRelativePath);

	void setResourcePath(const char *pszDirectoryName);
	const char* getResourcePath();
private:
	std::string m_strResourcePath;
};

NS_CC_END

#endif