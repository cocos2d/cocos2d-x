/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
 
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

#include "CCScriptSupport.h"
#include "CCScheduler.h"

NS_CC_BEGIN

#pragma mark -
#pragma mark CCScriptHandlerEntry

CCScriptHandlerEntry* CCScriptHandlerEntry::create(int nHandler)
{
    CCScriptHandlerEntry* entry = new CCScriptHandlerEntry(nHandler);
    entry->autorelease();
    return entry;
}

CCScriptHandlerEntry::~CCScriptHandlerEntry(void)
{
    CCScriptEngineManager::sharedManager()->getScriptEngine()->removeLuaHandler(m_nHandler);
}

#pragma mark -
#pragma mark CCSchedulerScriptHandlerEntry

CCSchedulerScriptHandlerEntry* CCSchedulerScriptHandlerEntry::create(int nHandler, float fInterval, bool bPaused)
{
    CCSchedulerScriptHandlerEntry* pEntry = new CCSchedulerScriptHandlerEntry(nHandler);
    pEntry->init(fInterval, bPaused);
    pEntry->autorelease();
    return pEntry;
}

bool CCSchedulerScriptHandlerEntry::init(float fInterval, bool bPaused)
{
    m_pTimer = new CCTimer();
    m_pTimer->initWithScriptHandler(m_nHandler, fInterval);
    m_pTimer->autorelease();
    m_pTimer->retain();
    m_bPaused = bPaused;
    LUALOG("[LUA] ADD script schedule: %d, entryID: %d", m_nHandler, m_nEntryId);
    return true;
}

CCSchedulerScriptHandlerEntry::~CCSchedulerScriptHandlerEntry(void)
{
    m_pTimer->release();
    LUALOG("[LUA] DEL script schedule %d, entryID: %d", m_nHandler, m_nEntryId);
}


#pragma mark -
#pragma mark CCTouchScriptHandlerEntry

CCTouchScriptHandlerEntry* CCTouchScriptHandlerEntry::create(int nHandler,
                                                             bool bIsMultiTouches,
                                                             int nPriority,
                                                             bool bSwallowsTouches)
{
    CCTouchScriptHandlerEntry* pEntry = new CCTouchScriptHandlerEntry(nHandler);
    pEntry->init(bIsMultiTouches, nPriority, bSwallowsTouches);
    pEntry->autorelease();
    return pEntry;
}

CCTouchScriptHandlerEntry::~CCTouchScriptHandlerEntry(void)
{
    CCScriptEngineManager::sharedManager()->getScriptEngine()->removeLuaHandler(m_nHandler);
    LUALOG("[LUA] Remove touch event handler: %d", m_nHandler);
}

bool CCTouchScriptHandlerEntry::init(bool bIsMultiTouches, int nPriority, bool bSwallowsTouches)
{
    m_bIsMultiTouches = bIsMultiTouches;
    m_nPriority = nPriority;
    m_bSwallowsTouches = bSwallowsTouches;
    
    return true;
}


#pragma mark -
#pragma mark CCScriptValue

const CCScriptValue CCScriptValue::intValue(const int intValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeInt;
    value.m_field.intValue = intValue;
    return value;
}

const CCScriptValue CCScriptValue::floatValue(const float floatValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeFloat;
    value.m_field.floatValue = floatValue;
    return value;
}

const CCScriptValue CCScriptValue::booleanValue(const bool booleanValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeBoolean;
    value.m_field.booleanValue = booleanValue;
    return value;
}

const CCScriptValue CCScriptValue::stringValue(const char* stringValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeString;
    value.m_field.stringValue = new std::string(stringValue);
    return value;
}

const CCScriptValue CCScriptValue::stringValue(const std::string& stringValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeString;
    value.m_field.stringValue = new std::string(stringValue);
    return value;
}

const CCScriptValue CCScriptValue::dictValue(const CCScriptValueDict& dictValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeDict;
    value.m_field.dictValue = new CCScriptValueDict(dictValue);
    return value;
}

const CCScriptValue CCScriptValue::arrayValue(const CCScriptValueArray& arrayValue)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeArray;
    value.m_field.arrayValue = new CCScriptValueArray(arrayValue);
    return value;
}

const CCScriptValue CCScriptValue::ccobjectValue(CCObject* ccobjectValue, const char* objectTypename)
{
    CCScriptValue value;
    value.m_type = CCScriptValueTypeCCObject;
    value.m_field.ccobjectValue = ccobjectValue;
    ccobjectValue->retain();
    value.m_ccobjectType = new std::string(objectTypename);
    return value;
}

const CCScriptValue CCScriptValue::ccobjectValue(CCObject* ccobjectValue, const std::string& objectTypename)
{
    return CCScriptValue::ccobjectValue(ccobjectValue, objectTypename.c_str());
}

CCScriptValue::CCScriptValue(const CCScriptValue& rhs)
{
    copy(rhs);
}

CCScriptValue& CCScriptValue::operator=(const CCScriptValue& rhs)
{
    if (this != &rhs) copy(rhs);
    return *this;
}

CCScriptValue::~CCScriptValue(void)
{
    if (m_type == CCScriptValueTypeString)
    {
        delete m_field.stringValue;
    }
    else if (m_type == CCScriptValueTypeDict)
    {
        delete m_field.dictValue;
    }
    else if (m_type == CCScriptValueTypeArray)
    {
        delete m_field.arrayValue;
    }
    else if (m_type == CCScriptValueTypeCCObject)
    {
        m_field.ccobjectValue->release();
        delete m_ccobjectType;
    }
}

void CCScriptValue::copy(const CCScriptValue& rhs)
{
    memcpy(&m_field, &rhs.m_field, sizeof(m_field));
    m_type = rhs.m_type;
    if (m_type == CCScriptValueTypeString)
    {
        m_field.stringValue = new std::string(*rhs.m_field.stringValue);
    }
    else if (m_type == CCScriptValueTypeDict)
    {
        m_field.dictValue = new CCScriptValueDict(*rhs.m_field.dictValue);
    }
    else if (m_type == CCScriptValueTypeArray)
    {
        m_field.arrayValue = new CCScriptValueArray(*rhs.m_field.arrayValue);
    }
    else if (m_type == CCScriptValueTypeCCObject)
    {
        m_field.ccobjectValue = rhs.m_field.ccobjectValue;
        m_field.ccobjectValue->retain();
        m_ccobjectType = new std::string(*rhs.m_ccobjectType);
    }
}


#pragma mark -
#pragma mark CCScriptEngineManager

static CCScriptEngineManager* s_pSharedScriptEngineManager = NULL;


CCScriptEngineManager::~CCScriptEngineManager(void)
{
    removeScriptEngine();
}

void CCScriptEngineManager::setScriptEngine(CCScriptEngineProtocol *pScriptEngine)
{
    removeScriptEngine();
    m_pScriptEngine = pScriptEngine;
}

void CCScriptEngineManager::removeScriptEngine(void)
{
    if (m_pScriptEngine)
    {
        delete m_pScriptEngine;
        m_pScriptEngine = NULL;
    }
}

CCScriptEngineManager* CCScriptEngineManager::sharedManager(void)
{
    if (!s_pSharedScriptEngineManager)
    {
        s_pSharedScriptEngineManager = new CCScriptEngineManager();
    }
    return s_pSharedScriptEngineManager;
}

void CCScriptEngineManager::purgeSharedManager(void)
{
    if (s_pSharedScriptEngineManager)
    {
        delete s_pSharedScriptEngineManager;
        s_pSharedScriptEngineManager = NULL;
    }
}

NS_CC_END
