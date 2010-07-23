/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCFileUtils.h"
#include <string.h>

char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
	// do not convert an absolute path (starting with '/')
	if (strlen(pszRelativePath) > 0 && pszRelativePath[0] == '/')
	{
		return (char*)pszRelativePath;
	}

	// get the user data path and append relativepath to it
    char *pszUserPath = (char*)EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_USER_DATA);
	char *pszRet;

	INT32 nLen = strlen(pszRelativePath) + strlen(pszUserPath) + 1;
	pszRet = new char[nLen];
	strncat(pszRet, pszUserPath, strlen(pszUserPath));
	strncat(pszRet, pszRelativePath, strlen(pszRelativePath));

	return pszRet;
}
