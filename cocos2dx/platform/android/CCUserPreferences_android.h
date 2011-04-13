/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) 2011 Marat Yakupov

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
#ifndef __CC_PLATFORM_ANDROID_USER_PREFERENCES_H__
#define __CC_PLATFORM_ANDROID_USER_PREFERENCES_H__

#include "CCCommon.h"
#include "CCObject.h"
#include <string>

NS_CC_BEGIN;

//! @brief  Helper class for accessing and modifying user’s preferences
class CC_DLL CCUserPreferences : public CCObject
{
public:	
	CCUserPreferences(void);
	~CCUserPreferences(void);

public:
	/** returns a shared instance of the user preferences */
	static CCUserPreferences* sharedPreferences(void);

	void putBoolean(const std::string& key, bool value);
	void putInteger(const std::string& key, int value);
	void putFloat(const std::string& key, float value);
	void putString(const std::string& key, const std::string& value);

	bool getBoolean(const std::string& key, bool defaultValue);
	int getInteger(const std::string& key, int defaultValue);
	float getFloat(const std::string& key, float defaultValue);
	std::string getString(const std::string& key, std::string defaultValue);

	void commit();
private:
	static CCUserPreferences* m_spCCUserPreferences;
};

NS_CC_END;

#endif	// end of __CC_PLATFORM_ANDROID_USER_PREFERENCES_H__
