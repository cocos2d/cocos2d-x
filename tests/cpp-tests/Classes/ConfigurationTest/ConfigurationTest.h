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

#ifndef __CONFIGURATIONTEST_H__
#define __CONFIGURATIONTEST_H__

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ConfigurationTests);

class ConfigurationBase : public TestCase
{
protected:

public:
    virtual std::string title() const override;
};

class ConfigurationLoadConfig : public ConfigurationBase
{
public:
    CREATE_FUNC(ConfigurationLoadConfig);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ConfigurationQuery : public ConfigurationBase
{
public:
    CREATE_FUNC(ConfigurationQuery);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ConfigurationInvalid : public ConfigurationBase
{
public:
    CREATE_FUNC(ConfigurationInvalid);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ConfigurationDefault : public ConfigurationBase
{
public:
    CREATE_FUNC(ConfigurationDefault);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class ConfigurationSet : public ConfigurationBase
{
public:
    CREATE_FUNC(ConfigurationSet);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};


#endif // __CONFIGURATIONTEST_H__
