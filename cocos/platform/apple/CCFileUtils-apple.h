/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#ifndef __CC_FILEUTILS_APPLE_H__
#define __CC_FILEUTILS_APPLE_H__

#include <memory>
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
class CC_DLL FileUtilsApple : public FileUtils
{
public:
    FileUtilsApple();
    virtual ~FileUtilsApple();
    /* override functions */
    virtual std::string getWritablePath() const override;
    virtual std::string getFullPathForDirectoryAndFilename(const std::string& directory, const std::string& filename) const override;

    virtual ValueMap getValueMapFromFile(const std::string& filename) const override;
    virtual ValueMap getValueMapFromData(const char* filedata, int filesize) const override;
    virtual bool writeToFile(const ValueMap& dict, const std::string& fullPath) const override;

    virtual ValueVector getValueVectorFromFile(const std::string& filename) const override;
#if CC_FILEUTILS_APPLE_ENABLE_OBJC
    void setBundle(NSBundle* bundle);
#endif
    
    virtual bool createDirectory(const std::string& path) const override;
private:
    virtual bool isFileExistInternal(const std::string& filePath) const override;
    virtual bool removeDirectory(const std::string& dirPath) const override;
    virtual void valueMapCompact(ValueMap& valueMap) const override;
    virtual void valueVectorCompact(ValueVector& valueVector) const override;

    struct IMPL;
    std::unique_ptr<IMPL> pimpl_;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_FILEUTILS_APPLE_H__
