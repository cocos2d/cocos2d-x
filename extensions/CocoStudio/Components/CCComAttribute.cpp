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
#include "cocos2d.h"

NS_CC_EXT_BEGIN

CCComAttribute::CCComAttribute(void)
: m_pJsonDict(NULL)
{
    m_strName = "ComAttribute";
}

CCComAttribute::~CCComAttribute(void)
{
    CC_SAFE_DELETE(m_pJsonDict);
}

bool CCComAttribute::init()
{
	m_pJsonDict = new cs::CSJsonDictionary();
    return true;
}

void CCComAttribute::setInt(const char *key, int value)
{
    m_pJsonDict->insertItem(key, value);
}

void CCComAttribute::setFloat(const char *key, float value)
{
    m_pJsonDict->insertItem(key, value);
}

void CCComAttribute::setBool(const char *key, bool value)
{
    m_pJsonDict->insertItem(key, value);
}

void CCComAttribute::setCString(const char *key, const char *value)
{
    m_pJsonDict->insertItem(key, value);
}


int CCComAttribute::getInt(const char *key) const
{
    return m_pJsonDict->getItemIntValue(key, -1);
}

float CCComAttribute::getFloat(const char *key) const
{
    return m_pJsonDict->getItemFloatValue(key, -1.0f);
}

bool CCComAttribute::getBool(const char *key) const
{
	return m_pJsonDict->getItemBoolvalue(key, false);
}

const char* CCComAttribute::getCString(const char *key) const
{
   return m_pJsonDict->getItemStringValue(key);
}

CCComAttribute* CCComAttribute::create(void)
{
    CCComAttribute * pRet = new CCComAttribute();
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

cs::CSJsonDictionary* CCComAttribute::getDict()
{
	return m_pJsonDict;
}

NS_CC_EXT_END
