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
#ifndef __ANDROID_COCOS2D_JNI_H__
#define __ANDROID_COCOS2D_JNI_H__

#include <jni.h>
#include <string>

extern "C"

{
	extern JavaVM *gJavaVM;
	void enableAccelerometerJNI();
	void disableAccelerometerJNI();
	void showMessageBoxJNI(const char * pszMsg, const char * pszTitle);
	
	void sharedPreferencesPutBooleanJNI(const std::string& key, bool value);
	void sharedPreferencesPutIntegerJNI(const std::string& key, int value);
	void sharedPreferencesPutFloatJNI(const std::string& key, float value);
	void sharedPreferencesPutStringJNI(const std::string& key, const std::string& value);

	bool sharedPreferencesGetBooleanJNI(const std::string& key, bool defaultValue);
	int sharedPreferencesGetIntegerJNI(const std::string& key, int defaultValue);
	float sharedPreferencesGetFloatJNI(const std::string& key, float defaultValue);
	std::string sharedPreferencesGetStringJNI(const std::string& key, const std::string& defaultValue);

	void sharedPreferencesCommitJNI();
}

#endif // __ANDROID_COCOS2D_JNI_H__
