/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 Copyright (c) Microsoft Open Technologies, Inc.
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
protected:
    CCFileUtilsWinRT();
public:
    /* override functions */
    bool init();
    virtual std::string getWritablePath() const;
    virtual bool isAbsolutePath(const std::string& strPath) const;
    virtual std::string getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath) const override;
    virtual std::string getFullPathForDirectoryAndFilename(const std::string& strDirectory, const std::string& strFilename) const override;
    virtual std::string getSuitableFOpen(const std::string& filenameUtf8) const override;
    virtual long getFileSize(const std::string &filepath) override;
	virtual FileUtils::Status getContents(const std::string& filename, ResizableBuffer* buffer) override;
	static std::string getAppPath();

    /**
    *  List all files in a directory.
    *
    *  @param dirPath The path of the directory, it could be a relative or an absolute path.
    *  @return File paths in a string vector
    */
    virtual std::vector<std::string> listFiles(const std::string& dirPath) const;

    /**
    *  List all files recursively in a directory.
    *
    *  @param dirPath The path of the directory, it could be a relative or an absolute path.
    *  @return File paths in a string vector
    */
    virtual void listFilesRecursively(const std::string& dirPath, std::vector<std::string> *files) const;

private:
    virtual bool isFileExistInternal(const std::string& strFilePath) const override;

    /**
    *  Renames a file under the given directory.
    *
    *  @param path     The parent directory path of the file, it must be an absolute path.
    *  @param oldname  The current name of the file.
    *  @param name     The new name of the file.
    *  @return True if the file have been renamed successfully, false if not.
    */
    virtual bool renameFile(const std::string &path, const std::string &oldname, const std::string &name) override;


    /**
    *  Renames a file.
    *
    *  @param oldfullpath  The current name of the file, including path and name.
    *  @param newfullpath  The new name of the file, including path and name
    *  @return True if the file have been renamed successfully, false if not.
    */
    virtual bool renameFile(const std::string &oldfullpath, const std::string& newfullpath) override;

    /**
    *  Checks whether a directory exists without considering search paths and resolution orders.
    *  @param dirPath The directory (with absolute path) to look up for
    *  @return Returns true if the directory found at the given absolute path, otherwise returns false
    */
    virtual bool isDirectoryExistInternal(const std::string& dirPath) const override;

    /**
    *  Removes a file.
    *
    *  @param filepath The full path of the file, it must be an absolute path.
    *  @return True if the file have been removed successfully, false if not.
    */
    virtual bool removeFile(const std::string &filepath) override;

    /**
    *  Creates a directory.
    *
    *  @param dirPath The path of the directory, it must be an absolute path.
    *  @return True if the directory have been created successfully, false if not.
    */
    virtual bool createDirectory(const std::string& dirPath) override;

    /**
    *  Removes a directory.
    *
    *  @param dirPath  The full path of the directory, it must be an absolute path.
    *  @return True if the directory have been removed successfully, false if not.
    */
    virtual bool removeDirectory(const std::string& dirPath) override;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_FILEUTILS_WINRT_H__

