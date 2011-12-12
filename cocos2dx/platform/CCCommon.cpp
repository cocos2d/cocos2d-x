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
    vsnprintf_s(szBuf, MAX_LEN, MAX_LEN, pszFormat, ap);
    va_end(ap);

    WCHAR wszBuf[MAX_LEN] = {0};
    MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
    OutputDebugStringW(wszBuf);
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

static char s_szLogFilePath[EOS_FILE_MAX_PATH] = {0};

NS_CC_BEGIN;

void CCLog(const char * pszFormat, ...)
{
    if (! s_szLogFilePath[0])
    {
        // save the log file named "Cocos2dxLog.txt" to the directory which the app.so in.
        TUChar AppID[EOS_FILE_MAX_PATH] = {0};
        UInt32 nCmdType = 0;
        Int32  nRet = SS_AppRequest_GetAppName(AppID, &nCmdType);
        if (nRet < 0)
        {
            return;
        }

        TUChar AppPath[EOS_FILE_MAX_PATH] = {0};
        if (SS_GetApplicationPath(AppID, SS_APP_PATH_TYPE_EXECUTABLE, AppPath) < 0)
        {
            return;
        }
        char szAppPath[EOS_FILE_MAX_PATH] = {0};
        TUString::StrUnicodeToStrUtf8((Char*) szAppPath, AppPath);
#ifndef _TRANZDA_VM_
        strcpy(s_szLogFilePath, "");
#else
        strcpy(s_szLogFilePath, "D:/Work7");
#endif
        strcat(s_szLogFilePath, szAppPath);
        strcat(s_szLogFilePath, "Cocos2dxLog.txt");
    }

    char szBuf[MAX_LEN];

    va_list ap;
    va_start(ap, pszFormat);
#ifdef _TRANZDA_VM_
    vsprintf_s(szBuf, MAX_LEN, pszFormat, ap);
#else
    vsnprintf(szBuf, MAX_LEN, pszFormat, ap);
#endif
    va_end(ap);

#ifdef _TRANZDA_VM_
    WCHAR wszBuf[MAX_LEN] = {0};
    MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
    OutputDebugStringW(wszBuf);
    OutputDebugStringA("\n");
#else
    FILE * pf = fopen(s_szLogFilePath, "a+");
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
#include <jni.h>

#include "android/jni/MessageJni.h"

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
 * linux
 ***************************************************/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

#include <stdio.h>
#include "CCStdC.h"

NS_CC_BEGIN;

void CCLog(const char * pszFormat, ...)
{
	char buf[MAX_LEN];
	
	va_list args;
	va_start(args, pszFormat);    	
	vsprintf(buf, pszFormat, args);
	va_end(args);
	
	//TODO will copy how orx do
	printf(buf);
}

// marmalade no MessageBox, use CCLog instead
void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
    CCLog("%s: %s", pszTitle, pszMsg);
}

NS_CC_END;
#endif
/****************************************************
 * marmalade
 ***************************************************/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)

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

// marmalade no MessageBox, use CCLog instead
void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
    CCLog("%s: %s", pszTitle, pszMsg);
}

NS_CC_END;

#endif // CC_PLATFORM_MARMALADE

/****************************************************
 * bada
 ***************************************************/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)
#include <FBaseSys.h>
#include <FUi.h>
#include <stdio.h>
#include <stdarg.h>

using namespace Osp::Ui::Controls;

NS_CC_BEGIN;

void CCLog(const char * pszFormat, ...)
{
	char buf[MAX_LEN] = {0};

	va_list args;
	va_start(args, pszFormat);
	vsnprintf(buf, MAX_LEN, pszFormat, args);
	va_end(args);
	__App_info(__PRETTY_FUNCTION__ , __LINE__, buf);
}

void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
	if (pszMsg != NULL && pszTitle != NULL)
	{
		int iRet = 0;
		MessageBox msgBox;
		msgBox.Construct(pszTitle, pszMsg, MSGBOX_STYLE_OK);
		msgBox.ShowAndWait(iRet);
	}
}

NS_CC_END;

#endif // CC_PLATFORM_BADA


/****************************************************
 * qnx
 ***************************************************/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_QNX)
#include <cstdio>
#include <cstdarg>
#include <stdio.h>
#include <stdarg.h>
using namespace std;

NS_CC_BEGIN;

void CCLog(const char * pszFormat, ...)
{
	char buf[MAX_LEN];

	va_list args;
	va_start(args, pszFormat);
	vsprintf(buf, pszFormat, args);
	va_end(args);

	fprintf(stderr, "cocos2d-x debug info [%s]\n",  buf);
}

void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
	CCLog("%s: %s", pszTitle, pszMsg);
}

NS_CC_END;

#endif // CC_PLATFORM_QNX
