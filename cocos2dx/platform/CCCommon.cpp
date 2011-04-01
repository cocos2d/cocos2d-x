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

#include "CCCommon.h"

#define MAX_LEN         (cocos2d::kMaxLogLen + 1)

/****************************************************
 * win32
 ***************************************************/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <Windows.h>

#include "CCStdC.h"

NS_CC_BEGIN;

void CCLog(const char * pszFormat, ...)
{
    char szBuf[MAX_LEN];

    va_list ap;
    va_start(ap, pszFormat);
    vsprintf_s(szBuf, MAX_LEN, pszFormat, ap);
    va_end(ap);
    OutputDebugStringA(szBuf);
    OutputDebugStringA("\n");
}

void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
    MessageBoxA(NULL, pszMsg, pszTitle, MB_OK);
}

NS_CC_END;

#endif  // CC_PLATFORM_WIN32

/****************************************************
 * wophone
 ***************************************************/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
#include "TG3.h"

#define LOG_FILE_PATH   "/NEWPLUS/TDA_DATA/UserData/Cocos2dLog.txt"

NS_CC_BEGIN;

void CCLog(const char * pszFormat, ...)
{
    SS_printf("Cocos2d: ");
    char szBuf[MAX_LEN];

    va_list ap;
    va_start(ap, pszFormat);
#ifdef _TRANZDA_VM_
    vsprintf_s(szBuf, MAX_LEN, pszFormat, ap);
#else
    vsnprintf(szBuf, MAX_LEN, pszFormat, ap);
#endif
    va_end(ap);

    SS_printf("%s", szBuf);
#ifdef _TRANZDA_VM_
    SS_printf("\n");
#else
    SS_printf("\r\n");
    FILE * pf = fopen(LOG_FILE_PATH, "a+");
    if (! pf)
    {
        return;
    }

    fwrite(szBuf, 1, strlen(szBuf), pf);
    fwrite("\r\n", 1, strlen("\r\n"), pf);
    fflush(pf);
    fclose(pf);
#endif
}

void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
    TUChar tszMsg[MAX_LEN] = { 0 };
    TUChar tszTitle[MAX_LEN] = { 0 };
    TUString::StrUtf8ToStrUnicode(tszMsg,(Char*)pszMsg);
    TUString::StrUtf8ToStrUnicode(tszTitle,(Char*)pszTitle);
    TMessageBox box(tszMsg, tszTitle, WMB_OK);
    box.Show();
}

NS_CC_END;

#endif  // CC_PLATFORM_WOPHONE

/****************************************************
 * ios
 ***************************************************/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

// implement in CCCommon_iso.mm

#endif  // CC_PLATFORM_IOS

/****************************************************
 * android
 ***************************************************/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <android/log.h>
#include <stdio.h>

#include "android/Cocos2dJni.h"

NS_CC_BEGIN;

void CCLog(const char * pszFormat, ...)
{
	char buf[MAX_LEN];

	va_list args;
	va_start(args, pszFormat);    	
	vsprintf(buf, pszFormat, args);
	va_end(args);

	__android_log_print(ANDROID_LOG_DEBUG, "cocos2d-x debug info",  buf);
}

void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
	showMessageBoxJNI(pszMsg, pszTitle);
}

NS_CC_END;

#endif // CC_PLATFORM_ANDROID
/****************************************************
 * airplay
 ***************************************************/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)

#include <s3e.h>
#include "IwUtil.h"
#include "IwUtilInitTerm.h"
#include <IwMemBucketHelpers.h>
#include <stdio.h>

NS_CC_BEGIN;

void CCLog(const char * pszFormat, ...)
{
	char buf[MAX_LEN];
	
	va_list args;
	va_start(args, pszFormat);    	
	vsprintf(buf, pszFormat, args);
	va_end(args);
	
	IwTrace(GAME, (buf));
}

// airplay no MessageBox, use CCLog instead
void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
    CCLog("%s: %s", pszTitle, pszMsg);
}

NS_CC_END;

#endif // CC_PLATFORM_AIRPLAY
