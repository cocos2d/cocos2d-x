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

CCComAttribute::CCComAttribute(void)
: m_pAttributes(NULL)
{
    m_strName = "ComAttribute";
}

CCComAttribute::~CCComAttribute(void)
{
    CC_SAFE_RELEASE(m_pAttributes);
}

bool CCComAttribute::init()
{
    return true;
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

void CCComAttribute::setIntValue(const char *key, int value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    if (m_pAttributes == NULL)
    {
        m_pAttributes = CCDictionary::create();
        m_pAttributes->retain();
    }
    
    std::stringstream streamValue;
    streamValue << value;
    CCString *old = dynamic_cast<CCString*>(m_pAttributes->objectForKey(key));
    if (old != NULL)
    {
        old->m_sString.assign(streamValue.str());
    }
    else
    {
        CCString *newvalue = CCString::create(streamValue.str());
        m_pAttributes->setObject(newvalue, key);
    }
}

void CCComAttribute::setDoubleValue(const char *key, double value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    if (m_pAttributes == NULL)
    {
        m_pAttributes = CCDictionary::create();
        m_pAttributes->retain();
    }
    
    std::stringstream streamValue;
    streamValue << value;
    CCString *old = dynamic_cast<CCString*>(m_pAttributes->objectForKey(key));
    if (old != NULL)
    {
        old->m_sString.assign(streamValue.str());
    }
    else
    {
        CCString *newvalue = CCString::create(streamValue.str());
        m_pAttributes->setObject(newvalue, key);
    }
}

void CCComAttribute::setFloatValue(const char *key, float value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    if (m_pAttributes == NULL)
    {
        m_pAttributes = CCDictionary::create();
        m_pAttributes->retain();
    }
    
    std::stringstream streamValue;
    streamValue << value;
    CCString *old = dynamic_cast<CCString*>(m_pAttributes->objectForKey(key));
    if (old != NULL)
    {
        old->m_sString.assign(streamValue.str());
    }
    else
    {
        CCString *newvalue = CCString::create(streamValue.str());
        m_pAttributes->setObject(newvalue, key);
    }
}

void CCComAttribute::setBoolValue(const char *key, bool value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    if (m_pAttributes == NULL)
    {
        m_pAttributes = CCDictionary::create();
        m_pAttributes->retain();
    }
    
    std::stringstream streamValue;
    streamValue << value;
    CCString *old = dynamic_cast<CCString*>(m_pAttributes->objectForKey(key));
    if (old != NULL)
    {
        old->m_sString.assign(streamValue.str());
    }
    else
    {
        CCString *newvalue = CCString::create(streamValue.str());
        m_pAttributes->setObject(newvalue, key);
    }
}

void CCComAttribute::setStringValue(const char *key, const char *value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    if (m_pAttributes == NULL)
    {
        m_pAttributes = CCDictionary::create();
        m_pAttributes->retain();
    }
    
    std::stringstream streamValue;
    streamValue << value;
    CCString *old = dynamic_cast<CCString*>(m_pAttributes->objectForKey(key));
    if (old != NULL)
    {
        old->m_sString.assign(streamValue.str());
    }
    else
    {
        CCString *newvalue = CCString::create(streamValue.str());
        m_pAttributes->setObject(newvalue, key);
    }

}

void CCComAttribute::setCCObjectValue(const char *key, CCObject *value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    if (m_pAttributes == NULL)
    {
        m_pAttributes = CCDictionary::create();
        m_pAttributes->retain();
    }
    
    m_pAttributes->setObject(value, key);
}

int CCComAttribute::getAsInt(const char *key)
{
    int ret = -1;
    CCString *num = NULL;
    CCAssert(key != NULL, "Argument must be non-nil");
    do
    {
        CC_BREAK_IF(NULL == key);
        CC_BREAK_IF(NULL == m_pAttributes);
        
        num = dynamic_cast<CCString*>(m_pAttributes->objectForKey(key));
        CC_BREAK_IF(NULL == num);
        
        ret =  num->intValue();
        
    } while (0);
     
    return ret;
}

double CCComAttribute::getAsDouble(const char *key)
{
    double ret = -1.0;
    CCString *num = NULL;
    CCAssert(key != NULL, "Argument must be non-nil");
    do
    {
        CC_BREAK_IF(NULL == key);
        CC_BREAK_IF(NULL == m_pAttributes);
        
        num = dynamic_cast<CCString*>(m_pAttributes->objectForKey(key));
        CC_BREAK_IF(NULL == num);
        
        ret =  num->doubleValue();
        
    } while(0);
     
    return ret;
}

float CCComAttribute::getAsFloat(const char *key)
{
    float ret = -1.0;
    CCString *num = NULL;
    CCAssert(key != NULL, "Argument must be non-nil");
    do
    {
        CC_BREAK_IF(NULL == key);
        CC_BREAK_IF(NULL == m_pAttributes);
        
        num = dynamic_cast<CCString*>(m_pAttributes->objectForKey(key));
        CC_BREAK_IF(NULL == num);
        
        ret =  num->floatValue();
        
    } while(0);
     
    return ret;
}

bool CCComAttribute::getAsBool(const char *key)
{
    bool ret = false;
    CCString *num = NULL;
    CCAssert(key != NULL, "Argument must be non-nil");
    do
    {
        CC_BREAK_IF(NULL == key);
        CC_BREAK_IF(NULL == m_pAttributes);
        
        num = dynamic_cast<CCString*>(m_pAttributes->objectForKey(key));
        CC_BREAK_IF(NULL == num);
        
        ret =  num->boolValue();
        
    } while(0);
     
    return ret;
}

const char* CCComAttribute::getAsString(const char *key)
{
    const char* ret = NULL;
    CCString *num = NULL;
    CCAssert(key != NULL, "Argument must be non-nil");
    do
    {
        CC_BREAK_IF(NULL == key);
        CC_BREAK_IF(NULL == m_pAttributes);
        
        num = dynamic_cast<CCString*>(m_pAttributes->objectForKey(key));
        CC_BREAK_IF(NULL == num);
        
        ret =  num->m_sString.c_str();
        
    } while(0);
     
    return ret;
}

CCObject* CCComAttribute::getAsCCObject(const char *key)
{
    CCObject* ret = NULL;
    CCAssert(key != NULL, "Argument must be non-nil");
    do
    {
        CC_BREAK_IF(NULL == key);
        CC_BREAK_IF(NULL == m_pAttributes);
        
        ret =  m_pAttributes->objectForKey(key);
        
    } while(0);
     
    return ret;
}

NS_CC_EXT_END
