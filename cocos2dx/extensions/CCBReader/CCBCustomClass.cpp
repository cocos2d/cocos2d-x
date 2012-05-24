/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 
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

#include "CCBCustomClass.h"

USING_NS_CC_EXT;

static CCBCustomClassFactory g_FactoryInstance;

// CCBCustomClassFactory
CCBCustomClassFactory::CCBCustomClassFactory()
{
    m_pCustomCreatorsMap = new CUSTOM_CLASS_MAP;
}

CCBCustomClassFactory::~CCBCustomClassFactory()
{
    CC_SAFE_DELETE(m_pCustomCreatorsMap);
}

CCBCustomClassFactory* CCBCustomClassFactory::sharedFactory()
{
    // TBD: don't use static global variable, so ugly
    return &g_FactoryInstance;
}

bool CCBCustomClassFactory::registCustomClass(const char* name, FUNC_CUSTON_CLASS_CREATOR pfnCreator)
{
    bool bRetVal = false;
        
    if (! (*m_pCustomCreatorsMap)[name] )
    {
        (*m_pCustomCreatorsMap)[name] = pfnCreator;
        bRetVal = true;
    }
    else
    {
        CCLOG("CCB: key = [%s] in m_pCustomCreatorsMap is already registed", name);
    }
        
    return bRetVal;
}

CCBCustomClassProtocol* CCBCustomClassFactory::createCustomClassWithName(const char* name)
{
    CCBCustomClassProtocol* pRetVal = NULL;
    FUNC_CUSTON_CLASS_CREATOR pfnCreator = (*m_pCustomCreatorsMap)[name];
    
    if (pfnCreator)
    {
        CCLOG("CCB: creating [%s] object", name);
        pRetVal = pfnCreator();
    }
    
    return pRetVal;
}

