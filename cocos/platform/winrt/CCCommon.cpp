/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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
#include "platform/CCCommon.h"
#include "platform/CCStdC.h"
#include "CCWinRTUtils.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#include "platform/wp8/CCGLViewImpl-wp8.h"
#endif

#if defined(VLD_DEBUG_MEMORY)
#include <vld.h>
#endif

NS_CC_BEGIN


void MessageBox(const char * pszMsg, const char * pszTitle)
{
    // Create the message dialog and set its content
    Platform::String^ message = ref new Platform::String(CCUtf8ToUnicode(pszMsg, -1).c_str());
    Platform::String^ title = ref new Platform::String(CCUtf8ToUnicode(pszTitle, -1).c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	Windows::UI::Popups::MessageDialog^ msg = ref new Windows::UI::Popups::MessageDialog(message, title);
    // Set the command to be invoked when a user presses 'ESC'
    msg->CancelCommandIndex = 1;

    // Show the message dialog
    msg->ShowAsync();
#else
    GLViewImpl::sharedOpenGLView()->ShowMessageBox(title, message);
#endif

}


void CCLuaLog(const char *pszMsg)
{
#if defined(COCOS2D_DEBUG)
    int bufflen = MultiByteToWideChar(CP_UTF8, 0, pszMsg, -1, NULL, 0);
    WCHAR* widebuff = new WCHAR[bufflen + 1];
    memset(widebuff, 0, sizeof(WCHAR) * (bufflen + 1));
    MultiByteToWideChar(CP_UTF8, 0, pszMsg, -1, widebuff, bufflen);


    OutputDebugStringW(widebuff);
    OutputDebugStringA("\n");

	bufflen = WideCharToMultiByte(CP_ACP, 0, widebuff, -1, NULL, 0, NULL, NULL);
	char* buff = new char[bufflen + 1];
	memset(buff, 0, sizeof(char) * (bufflen + 1));
	WideCharToMultiByte(CP_ACP, 0, widebuff, -1, buff, bufflen, NULL, NULL);
	puts(buff);

	delete[] widebuff;
	delete[] buff;
#endif
}

NS_CC_END
