/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2013 Lee, Jae-Hong

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

#include "CCFileUtilsTizen.h"
#include "platform/CCCommon.h"
#include "ccMacros.h"
#include "CCApplication.h"
#include "cocoa/CCString.h"
#include <FApp.h>
#include <FBase.h>
#include <FIo.h>
#include <FText.h>

NS_CC_BEGIN
using namespace std;
using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Io;
using namespace Tizen::Text;

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new CCFileUtilsTizen();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

CCFileUtilsTizen::CCFileUtilsTizen()
{
}

bool CCFileUtilsTizen::init()
{
    UiApp* pApp = UiApp::GetInstance();
    if (!pApp)
    {
        return false;
    }

    String resPath = pApp->GetAppResourcePath();
    if (resPath.IsEmpty())
    {
        return false;
    }

    AsciiEncoding ascii;
    ByteBuffer* buffer = ascii.GetBytesN(resPath);
    m_strDefaultResRootPath = (const char *)buffer->GetPointer();
    delete buffer;
    return CCFileUtils::init();
}

string CCFileUtilsTizen::getWritablePath()
{
    UiApp* pApp = UiApp::GetInstance();
    if (!pApp)
    {
        return null;
    }

    string path("");
    AsciiEncoding ascii;
    String dataPath = pApp->GetAppDataPath();
    if (!dataPath.IsEmpty())
    {
        ByteBuffer* buffer = ascii.GetBytesN(dataPath);
        path.append((const char*)buffer->GetPointer());
        delete buffer;
    }

    return path;
}

bool CCFileUtilsTizen::isFileExist(const std::string& strFilePath)
{
    std::string strPath = strFilePath;
    if (!isAbsolutePath(strPath))
    { // Not absolute path, add the default root path at the beginning.
        strPath.insert(0, m_strDefaultResRootPath);
    }

    return File::IsFileExist(strPath.c_str());
}

NS_CC_END

