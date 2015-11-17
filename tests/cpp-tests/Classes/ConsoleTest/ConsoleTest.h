/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org

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

#ifndef _CONSOLE_TEST_H_
#define _CONSOLE_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ConsoleTests);

class BaseTestConsole : public TestCase
{
public:
    BaseTestConsole();
    ~BaseTestConsole();

    virtual std::string title() const override;
};


class ConsoleCustomCommand : public BaseTestConsole
{
public:
    CREATE_FUNC(ConsoleCustomCommand);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    ConsoleCustomCommand();
    virtual ~ConsoleCustomCommand();

    cocos2d::Console *_console;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ConsoleCustomCommand);
};

class ConsoleUploadFile : public BaseTestConsole
{
public:
    CREATE_FUNC(ConsoleUploadFile);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

protected:
    ConsoleUploadFile();
    virtual ~ConsoleUploadFile();

    void uploadFile();
    std::string _src_file_path;
    std::string _target_file_name;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ConsoleUploadFile);
};

#endif // _CONSOLE_TEST_H_
