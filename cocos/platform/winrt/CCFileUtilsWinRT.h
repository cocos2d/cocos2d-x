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
#ifndef __CC_FILEUTILS_WINRT_H__
#define __CC_FILEUTILS_WINRT_H__

#include <string>
#include <vector>

#include "platform/CCFileUtils.h"
#include "platform/CCPlatformMacros.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

//! @brief  Helper class to handle file operations
class CC_DLL CCFileUtilsWinRT : public FileUtils
{
    friend class FileUtils;
    CCFileUtilsWinRT();
public:
    /* override funtions */
    bool init();
    virtual std::string getWritablePath() const;
    virtual bool isAbsolutePath(const std::string& strPath) const;
    virtual std::string  getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath) const override;
    virtual std::string getFullPathForDirectoryAndFilename(const std::string& strDirectory, const std::string& strFilename) const override;
	virtual std::string getStringFromFile(const std::string& filename) override;
	static std::string getAppPath();

private:
    virtual bool isFileExistInternal(const std::string& strFilePath) const;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_FILEUTILS_WINRT_H__

