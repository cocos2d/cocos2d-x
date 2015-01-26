/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#ifndef __Java_org_cocos2dx_lib_Cocos2dxHelper_H__
#define __Java_org_cocos2dx_lib_Cocos2dxHelper_H__

#include <string>

typedef void (*EditTextCallback)(const char* text, void* ctx);

extern const char * getApkPath();
extern void showDialogJNI(const char * message, const char * title);
extern void showEditTextDialogJNI(const char* title, const char* content, int inputMode, int inputFlag, int returnType, int maxLength, EditTextCallback callback, void* ctx);
extern void terminateProcessJNI();
extern std::string getCurrentLanguageJNI();
extern std::string getPackageNameJNI();
extern std::string getFileDirectoryJNI();
extern void enableAccelerometerJni();
extern void disableAccelerometerJni();
extern void setAccelerometerIntervalJni(float interval);
extern void setKeepScreenOnJni(bool value);
extern bool openURLJNI(const char* url);
// functions for UserDefault
extern bool getBoolForKeyJNI(const char* key, bool defaultValue);
extern int getIntegerForKeyJNI(const char* key, int defaultValue);
extern float getFloatForKeyJNI(const char* key, float defaultValue);
extern double getDoubleForKeyJNI(const char* key, double defaultValue);
extern std::string getStringForKeyJNI(const char* key, const char* defaultValue);
extern void setBoolForKeyJNI(const char* key, bool value);
extern void setIntegerForKeyJNI(const char* key, int value);
extern void setFloatForKeyJNI(const char* key, float value);
extern void setDoubleForKeyJNI(const char* key, double value);
extern void setStringForKeyJNI(const char* key, const char* value);

#endif /* __Java_org_cocos2dx_lib_Cocos2dxHelper_H__ */
