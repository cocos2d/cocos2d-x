/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Cocos2D-X Qt 5 Platform
 Copyright (C) 2013 Jolla Ltd.
 Contact: Thomas Perl <thomas.perl@jollamobile.com>

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


#include "platform/CCFileUtils.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCCommon.h"
#include "ccTypes.h"
#include "ccTypeInfo.h"
#include "ccMacros.h"

#include <unistd.h>
#include <sys/stat.h>

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

NS_CC_BEGIN

class CC_DLL FileUtilsQt5 : public FileUtils
{
    public:
        FileUtilsQt5();

        /* override funtions */
        virtual bool init();
        virtual std::string getWritablePath();
        virtual bool isFileExist(const std::string& strFilePath);
};

FileUtils *
FileUtils::getInstance()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new FileUtilsQt5();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

FileUtilsQt5::FileUtilsQt5()
{
}

bool
FileUtilsQt5::init()
{
    // Determine directory of the application executable
    QDir app_dir = QDir("/proc/self/exe").canonicalPath();
    app_dir.cdUp();

    // Resources should be placed alongside the binary (same directory)
    QString path = app_dir.path() + "/Resources/";
    _defaultResRootPath = path.toStdString();

    return FileUtils::init();
}

std::string
FileUtilsQt5::getWritablePath()
{
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));

    // Create directory if it does not exist yet
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    return dir.path().toStdString();
}

bool FileUtilsQt5::isFileExist(const std::string& strFilePath)
{
    QString filePath = QString::fromStdString(strFilePath);

    // Try filename without any path first
    if (QFile(filePath).exists()) {
        return true;
    }

    // If not found, look for file in _defaultResRootPath
    QString defaultResRootPath = QString::fromStdString(_defaultResRootPath);
    return QFile(QDir(defaultResRootPath).filePath(filePath)).exists();
}

NS_CC_END
