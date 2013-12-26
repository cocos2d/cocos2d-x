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

#include "cocostudio/CCComAttribute.h"
using namespace cocos2d;

namespace cocostudio {

ComAttribute::ComAttribute(void)
: _jsonDict(nullptr)
{
    _name = "ComAttribute";
}

ComAttribute::~ComAttribute(void)
{
	CC_SAFE_DELETE(_jsonDict);
}

bool ComAttribute::init()
{
	_jsonDict = new JsonDictionary();
    return true;
}

ComAttribute* ComAttribute::create(void)
{
    ComAttribute * pRet = new ComAttribute();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void ComAttribute::setInt(const char *key, int value)
{
    CCASSERT(key != NULL, "Argument must be non-nil"); 
    _jsonDict->insertItem(key, value);
}

void ComAttribute::setFloat(const char *key, float value)
{
    CCASSERT(key != NULL, "Argument must be non-nil"); 
    _jsonDict->insertItem(key, value);
}

void ComAttribute::setBool(const char *key, bool value)
{
    CCASSERT(key != NULL, "Argument must be non-nil"); 
    _jsonDict->insertItem(key, value);
}

void ComAttribute::setCString(const char *key, const char *value)
{
    CCASSERT(key != NULL, "Argument must be non-nil"); 
    _jsonDict->insertItem(key, value);
}


int ComAttribute::getInt(const char *key) const
{
    return _jsonDict->getItemIntValue(key, -1);
}

float ComAttribute::getFloat(const char *key) const
{
    return _jsonDict->getItemFloatValue(key, -1.0f);
}

bool ComAttribute::getBool(const char *key) const
{
	return _jsonDict->getItemBoolvalue(key, false);
}

const char* ComAttribute::getCString(const char *key) const
{
   return _jsonDict->getItemStringValue(key);
}

JsonDictionary* ComAttribute::getDict() const
{
	return _jsonDict;
}

}
