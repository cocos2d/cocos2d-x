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

#ifndef _FONT_TEST_H_
#define _FONT_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(FontTests);

class FontTest : public TestCase
{
public:
    static FontTest* create(const std::string& fontFile)
    {
        auto ret = new (std::nothrow) FontTest;
        if (ret && ret->init())
        {
            ret->showFont(fontFile);
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }

        return ret;
    }

    void showFont(const std::string& fontFile);

    virtual std::string title() const override;
};

class FontNoReplacementTest : public TestCase
{
public:
	static FontNoReplacementTest* create();
	~FontNoReplacementTest();
	virtual void onEnter() override;
	virtual std::string title() const override;
protected:
	FontNoReplacementTest();

	bool _replace;
};

class FontReplacementTest : public FontNoReplacementTest
{
public:
	static FontReplacementTest* create();
	virtual std::string title() const override;
protected:
	FontReplacementTest();
};

#endif // _FONT_TEST_H_
