/***************************************************************************
 Copyright (c) 2012 Zynga Inc.
 Copyright (c) 2013 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologic Inc.

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
***************************************************************************/
 

/*
 Local Storage support for the JS Bindings for iOS.
 Works on cocos2d-iphone and cocos2d-x.
 */

#include "storage/local-storage/LocalStorage.h"
#include "platform/CCPlatformMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "jni.h"
#include "platform/android/jni/JniHelper.h"

USING_NS_CC;
static int _initialized = 0;

static std::string className = "org/cocos2dx/lib/Cocos2dxLocalStorage";

static void splitFilename (std::string& str)
{
	size_t found = 0;
	found=str.find_last_of("/\\");
	if (found != std::string::npos)
	{
		str = str.substr(found+1);
	}
}

void localStorageInit( const std::string& fullpath)
{
	if (fullpath.empty())
        return;

	if( ! _initialized )
    {
        std::string strDBFilename = fullpath;
        splitFilename(strDBFilename);
        if (JniHelper::callStaticBooleanMethod(className, "init", strDBFilename, "data")) {
            _initialized = 1;
        }
	}
}

void localStorageFree()
{
	if( _initialized ) {
        JniHelper::callStaticVoidMethod(className, "destory");
		_initialized = 0;
	}
}

/** sets an item in the LS */
void localStorageSetItem( const std::string& key, const std::string& value)
{
	assert( _initialized );
    JniHelper::callStaticVoidMethod(className, "setItem", key, value);
}

/** gets an item from the LS */
bool localStorageGetItem( const std::string& key, std::string *outItem )
{
	assert( _initialized );
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxLocalStorage", "getItem", "(Ljava/lang/String;)Ljava/lang/String;"))
    {
        jstring jkey = t.env->NewStringUTF(key.c_str());
        jstring jret = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, jkey);
        outItem->assign(JniHelper::jstring2string(jret));
        t.env->DeleteLocalRef(jret);
        t.env->DeleteLocalRef(jkey);
        t.env->DeleteLocalRef(t.classID);
        return true;
    }
    else
    {
        return false;
    }
}

/** removes an item from the LS */
void localStorageRemoveItem( const std::string& key )
{
	assert( _initialized );
    JniHelper::callStaticVoidMethod(className, "removeItem", key);

}

/** removes all items from the LS */
void localStorageClear()
{
    assert( _initialized );
    JniHelper::callStaticVoidMethod(className, "clear");
}

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
