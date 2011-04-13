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
#include "CCUserPreferences_android.h"
#include "Cocos2dJni.h"

NS_CC_BEGIN;

CCUserPreferences* CCUserPreferences::m_spCCUserPreferences = NULL;

CCUserPreferences::CCUserPreferences()
{
}

CCUserPreferences::~CCUserPreferences()
{
}

CCUserPreferences* CCUserPreferences::sharedPreferences()
{

	if (m_spCCUserPreferences == NULL)
	{
		m_spCCUserPreferences = new CCUserPreferences();
		m_spCCUserPreferences->autorelease();
	}
	
	return m_spCCUserPreferences;
}

void CCUserPreferences::putBoolean(const std::string& key, bool value)
{
	sharedPreferencesPutBooleanJNI(key, value);
}

void CCUserPreferences::putInteger(const std::string& key, int value)
{
	sharedPreferencesPutIntegerJNI(key, value);
}

void CCUserPreferences::putFloat(const std::string& key, float value)
{
	sharedPreferencesPutFloatJNI(key, value);
}

void CCUserPreferences::putString(const std::string& key, const std::string& value)
{
	sharedPreferencesPutStringJNI(key, value);
}

bool CCUserPreferences::getBoolean(const std::string& key, bool defaultValue)
{
	return sharedPreferencesGetBooleanJNI(key, defaultValue);
}

int CCUserPreferences::getInteger(const std::string& key, int defaultValue)
{
	return sharedPreferencesGetIntegerJNI(key, defaultValue);
}

float CCUserPreferences::getFloat(const std::string& key, float defaultValue)
{
	return sharedPreferencesGetFloatJNI(key, defaultValue);
}

std::string CCUserPreferences::getString(const std::string& key, std::string defaultValue)
{
	return sharedPreferencesGetStringJNI(key, defaultValue);
}

void CCUserPreferences::commit()
{
	sharedPreferencesCommitJNI();
}

NS_CC_END;
