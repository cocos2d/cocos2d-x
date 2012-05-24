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

#ifndef _CC_CUSTOM_CLASS_H_
#define _CC_CUSTOM_CLASS_H_

#include "cocos2d.h"
#include <map>

NS_CC_EXT_BEGIN
    
/**
 @brief This is a simple reflection implement for custom classes in CocosBuilder
 
 You should declare your custom class like: 
 class MyCustomLayer : public CCBCustomClass, public CCLayer
 CCBCustomClass is a pure virtual class. It doesn't inherit CCObject to prevent dead-diamond.
*/
class CCBCustomClassProtocol
{
public:    
    /** You should implement this static function in your custom class, and return a valid object */
    static CCBCustomClassProtocol* createInstance() { return NULL; }; // cannot create virual class here
    
    CCBCustomClassProtocol() {};
    virtual ~CCBCustomClassProtocol() {};
    
    /** This pure virtual methods should be implemented in your custom class
        please refer to tests/ExtensionsTest/CocosBuilderTest as a sample */
    virtual bool callbackSetChildren(const char* name, cocos2d::CCObject* node) = 0;
    
    /** This pure virtual methods should be implemented in your custom class
     please refer to tests/ExtensionsTest/CocosBuilderTest as a sample */
    virtual cocos2d::SEL_MenuHandler callbackGetSelectors(const char* selectorName) = 0;
    
    /** This pure virtual methods should be implemented in your custom class
     please refer to tests/ExtensionsTest/CocosBuilderTest as a sample */
    virtual void callbackAfterCCBLoaded() = 0;
};

/**
 @brief CCBCustomClass should be registed into this factory, then CCBReader can create your custom class via its name string.
 
 See tests/Extensionstest/CocosBuilderTest/CocosBuilderTest.cpp as the reference
 */
class CC_DLL CCBCustomClassFactory
{
private:    
    /// a function pointer for CCCustomClassProtocol::createInstance
    typedef CCBCustomClassProtocol* (*FUNC_CUSTON_CLASS_CREATOR)();  
    typedef std::map<std::string, FUNC_CUSTON_CLASS_CREATOR> CUSTOM_CLASS_MAP;
    CUSTOM_CLASS_MAP* m_pCustomCreatorsMap;
    
public:    
    CCBCustomClassFactory();
    virtual ~CCBCustomClassFactory();
    
    /** get the singleton */
    static CCBCustomClassFactory* sharedFactory();

    /** Note that you should regist custom class before invoke CCBReader::nodeGraphFromFile 
        For example:
        CCBCustomClassFactory::sharedFactory()->registCustomClass("HelloCocosBuilder", 
                                                                  HelloCocosBuilder::createInstance);
     */
    bool registCustomClass(const char* name, FUNC_CUSTON_CLASS_CREATOR pfnCreator);
    
    /** This function is only used in CCBReader. Developers don't need to know it */
    CCBCustomClassProtocol* createCustomClassWithName(const char* name);
    

};

NS_CC_EXT_END;

#endif // _CC_CUSTOM_CLASS_H_
