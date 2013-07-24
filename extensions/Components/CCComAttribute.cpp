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

#include "CCComAttribute.h"

NS_CC_EXT_BEGIN

ComAttribute::ComAttribute(void)
: _attributes(NULL)
{
    _name = "ComAttribute";
}

ComAttribute::~ComAttribute(void)
{
    CC_SAFE_RELEASE(_attributes);
}

bool ComAttribute::init()
{
    _attributes = Dictionary::create();
    _attributes->retain();
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
    _attributes->setObject(Integer::create(value), key);
}

void ComAttribute::setDouble(const char *key, double value)
{
    CCASSERT(key != NULL, "Argument must be non-nil"); 
    _attributes->setObject(Double::create(value), key);
}

void ComAttribute::setFloat(const char *key, float value)
{
    CCASSERT(key != NULL, "Argument must be non-nil"); 
    _attributes->setObject(Float::create(value), key);
}

void ComAttribute::setBool(const char *key, bool value)
{
    CCASSERT(key != NULL, "Argument must be non-nil"); 
    _attributes->setObject(Bool::create(value), key);
}

void ComAttribute::setCString(const char *key, const char *value)
{
    CCASSERT(key != NULL, "Argument must be non-nil"); 
    _attributes->setObject(String::create(value), key);
}

void ComAttribute::setObject(const char *key, Object *value)
{
    CCASSERT(key != NULL, "Argument must be non-nil"); 
    _attributes->setObject(value, key);
}

int ComAttribute::getInt(const char *key) const
{
    Object *ret = _attributes->objectForKey(key);
	if( ret )
    {
		if( Integer *obj=dynamic_cast<Integer*>(ret) )
			return obj->getValue();

		CCASSERT(false, "Key found, type is not integer");
	}

	// XXX: Should it throw an exception ?
	CCLOG("Key not found: '%s'", key );
	return 0;
}

double ComAttribute::getDouble(const char *key) const
{
    Object *ret = _attributes->objectForKey(key);
	if( ret )
    {
		if( Double *obj=dynamic_cast<Double*>(ret) )
			return obj->getValue();

		CCASSERT(false, "Key found, type is not double");
	}

	// XXX: Should it throw an exception ?
	CCLOG("Key not found: '%s'", key );
	return 0.0;
}

float ComAttribute::getFloat(const char *key) const
{
    Object *ret = _attributes->objectForKey(key);
	if( ret )
    {
		if( Float *obj=dynamic_cast<Float*>(ret) )
			return obj->getValue();

		CCASSERT(false, "Key found, type is not float");
	}

	// XXX: Should it throw an exception ?
	CCLOG("Key not found: '%s'", key );
	return 0.0;
}

bool ComAttribute::getBool(const char *key) const
{
    Object *ret = _attributes->objectForKey(key);
	if( ret )
    {
		if( Bool *boolobj=dynamic_cast<Bool*>(ret) )
			return boolobj->getValue();
		if( String *strobj=dynamic_cast<String*>(ret) )
			return strobj->boolValue();
		CCASSERT(false, "Key found, type is not Bool");
	}

	// XXX: Should it throw an exception ?
	CCLOG("Key not found: '%s'", key );
	return false;
}

const char* ComAttribute::getCString(const char *key) const
{
   Object *ret = _attributes->objectForKey(key);
	if( ret )
    {
		if( String *str=dynamic_cast<String*>(ret) )
			return str->getCString();

		CCASSERT(false, "Key found, type is not CString");
	}

	// XXX: Should it throw an exception ?
	CCLOG("Key not found: '%s'", key );
	return NULL;
}

Object* ComAttribute::getObject(const char *key) const
{
    return _attributes->objectForKey(key);
}

NS_CC_EXT_END
