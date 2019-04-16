/****************************************************************************
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

#ifndef __FILEUTILSTEST_H__
#define __FILEUTILSTEST_H__

#include "../BaseTest.h"


DEFINE_TEST_SUITE(FileUtilsTests);

class FileUtilsDemo : public TestCase
{
public:
};

class TestResolutionDirectories : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestResolutionDirectories);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    std::vector<std::string> _defaultSearchPathArray;
    std::vector<std::string> _defaultResolutionsOrderArray;
};

class TestSearchPath : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestSearchPath);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    std::vector<std::string> _defaultSearchPathArray;
    std::vector<std::string> _defaultResolutionsOrderArray;
};

class TestFilenameLookup : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestFilenameLookup);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
};

class TestIsFileExist : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestIsFileExist);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestIsDirectoryExist : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestIsDirectoryExist);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestFileFuncs : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestFileFuncs);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestDirectoryFuncs : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestDirectoryFuncs);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestWriteString : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestWriteString);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestGetContents : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestGetContents);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
private:
    std::string _generatedFile;
};

class TestWriteData : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestWriteData);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestWriteValueMap : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestWriteValueMap);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestWriteValueVector : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestWriteValueVector);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestUnicodePath : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestUnicodePath);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestIsFileExistAsync : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestIsFileExistAsync);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestIsDirectoryExistAsync : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestIsDirectoryExistAsync);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestFileFuncsAsync : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestFileFuncsAsync);
    
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestDirectoryFuncsAsync : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestDirectoryFuncsAsync);
    
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestWriteStringAsync : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestWriteStringAsync);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestWriteDataAsync : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestWriteDataAsync);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestListFiles : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestListFiles);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TestIsFileExistRejectFolder : public FileUtilsDemo
{
public:
    CREATE_FUNC(TestIsFileExistRejectFolder);

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif /* __FILEUTILSTEST_H__ */
