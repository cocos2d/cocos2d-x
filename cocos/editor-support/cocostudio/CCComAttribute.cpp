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
: _dict(NULL)
{
    _name = "ComAttribute";
}

ComAttribute::~ComAttribute(void)
{
    CC_SAFE_RELEASE(_dict);
}

bool ComAttribute::init()
{
    _dict = CCDictionary::create();
	_dict->retain();
    return true;
}

void ComAttribute::setInt(const char *key, int value)
{
    _dict->setObject(CCInteger::create(value), key);
}

void ComAttribute::setFloat(const char *key, float value)
{
    _dict->setObject(CCFloat::create(value), key);
}

void ComAttribute::setBool(const char *key, bool value)
{
    _dict->setObject(CCBool::create(value), key);
}

void ComAttribute::setCString(const char *key, const char *value)
{
    _dict->setObject(CCString::create(value), key);
}


int ComAttribute::getInt(const char *key, int def) const
{
    CCObject *ret = _dict->objectForKey(key);
	if(ret)
    {
		
		if( CCInteger *obj=dynamic_cast<CCInteger*>(ret) )
			return obj->getValue();
	}
    return def;
}

float ComAttribute::getFloat(const char *key, float def) const
{
    CCObject *ret = _dict->objectForKey(key);
	if(ret)
    {
		
		if( CCFloat *obj=dynamic_cast<CCFloat*>(ret) )
			return obj->getValue();
	}
    return def;
}

bool ComAttribute::getBool(const char *key, bool def) const
{
    CCObject *ret = _dict->objectForKey(key);
	if(ret) {
		
		if( CCBool *obj = dynamic_cast<CCBool*>(ret) )
			return obj->getValue();
	}
    return def;
}

const char* ComAttribute::getCString(const char *key, const char *def) const
{
   CCObject *ret = _dict->objectForKey(key);
	if(ret) {
		
		if( CCString *obj = dynamic_cast<CCString*>(ret) )
			return obj->getCString();
	}
    return def;
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


}
