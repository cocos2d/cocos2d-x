/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
#ifndef __SUPPORT_CCUSERDEFAULT_H__
#define __SUPPORT_CCUSERDEFAULT_H__

#include "CCPlatformMacros.h"

#include <string>


NS_CC_BEGIN;

class CC_DLL CCUserDefault
{
public:
	~CCUserDefault();

	// get value methods
	bool	getBoolForKey(const char* pKey);
	int		getIntegerForKey(const char* pKey);
	float	getFloatForKey(const char* pKey);
	double  getDoubleForKey(const char* pKey);
	std::string getStringForKey(const char* pKey);

	// set value methods
	void	setBoolForKey(const char* pKey, bool value);
	void	setIntegerForKey(const char* pKey, int value);
	void	setFloatForKey(const char* pKey, float value);
	void	setDoubleForKey(const char* pKey, double value);
	void	setStringForKey(const char* pKey, std::string value);

	static CCUserDefault* sharedUserDefault();
	static void purgeSharedUserDefault();
	const static std::string& getXMLFilePath();

private:
	CCUserDefault() {}
	static bool createXMLFile();
	static bool isXMLFileExist();
	static void initXMLFilePath();
	
	static CCUserDefault* m_spUserDefault;
	static std::string m_sFilePath;
	static bool m_sbIsFilePathInitialized;
};

NS_CC_END;

#endif // __SUPPORT_CCUSERDEFAULT_H__
