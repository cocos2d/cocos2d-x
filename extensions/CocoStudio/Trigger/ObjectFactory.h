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

#ifndef __TRIGGERFACTORY_H__
#define __TRIGGERFACTORY_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include <string>
#include <map>

namespace cocos2d
{
    namespace ui
    {
        class Widget;
    }
    namespace extension
    {
        class WidgetReaderProtocol;
    }
}


NS_CC_EXT_BEGIN

class CC_EX_DLL ObjectFactory
{
public:
    typedef cocos2d::CCObject* (*Instance)(void);
    struct CC_EX_DLL TInfo
    {
        TInfo(void);
        TInfo(const std::string& type, Instance ins = NULL);
        TInfo(const TInfo &t);
        ~TInfo(void);
        TInfo& operator= (const TInfo &t);
        std::string _class;
        Instance _fun;
    };
    typedef std::map<std::string, TInfo>  FactoryMap;
    ObjectFactory(void);
    virtual ~ObjectFactory(void);
    static ObjectFactory* getInstance();
    void destroyInstance();
    CCObject* createObject(std::string name);
	CCComponent* createComponent(std::string name);
    ui::Widget* createGUI(std::string name);
    WidgetReaderProtocol* createWidgetReaderProtocol(std::string name);
    void registerType(const TInfo &t);
    void removeAll();
private:
    static ObjectFactory *_sharedFactory;
    FactoryMap _typeMap;
};


NS_CC_EXT_END

#endif
