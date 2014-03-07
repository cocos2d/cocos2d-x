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

#include "ObjectFactory.h"
#include "../GUI/BaseClasses/UIWidget.h"
#include "../Reader/WidgetReader/WidgetReaderProtocol.h"


NS_CC_EXT_BEGIN

ObjectFactory::TInfo::TInfo(void)
:_class("")
,_fun(NULL)
{
}

ObjectFactory::TInfo::TInfo(const std::string& type, Instance ins)
:_class(type)
,_fun(ins)
{
    cocos2d::extension::ObjectFactory::getInstance()->registerType(*this);
}

ObjectFactory::TInfo::TInfo(const TInfo &t)
{
    _class = t._class;
    _fun = t._fun;
}

ObjectFactory::TInfo::~TInfo(void)
{
   _class = "";
   _fun = NULL;
}

ObjectFactory::TInfo& ObjectFactory::TInfo::operator= (const TInfo &t)
{
    _class = t._class;
    _fun = t._fun;
    return *this;
}


ObjectFactory* ObjectFactory::_sharedFactory = NULL;

ObjectFactory::ObjectFactory(void)
{

}

ObjectFactory::~ObjectFactory(void)
{
    _typeMap.clear();
}

ObjectFactory* ObjectFactory::getInstance()
{
    if ( NULL == _sharedFactory)
    {
        _sharedFactory = new ObjectFactory();
    }
    return _sharedFactory;
}

void ObjectFactory::destroyInstance()
{
    CC_SAFE_DELETE(_sharedFactory);
}

CCObject* ObjectFactory::createObject(std::string name)
{
	CCObject *o = NULL;
	do 
	{
		const TInfo t = _typeMap[name];
		CC_BREAK_IF(t._fun == NULL);
		o = t._fun();
	} while (0);
   
    return o;
}

CCComponent* ObjectFactory::createComponent(std::string name)
{
	if (name == "CCSprite" || name == "CCTMXTiledMap" || name == "CCParticleSystemQuad" || name == "CCArmature" || name == "GUIComponent")
	{
		name = "CCComRender";
	}
	else if (name == "CCComAudio" || name == "CCBackgroundAudio")
	{
		name = "CCComAudio";
	}
    else if (name == "CCComController")
    {
        name = "CCComController";
    }
    else if (name == "CCComAttribute")
    {
        name = "CCComAttribute";
    }
    else if (name == "CCScene")
    {
        name = "CCScene";
    }
    else
    {
        CCAssert(false, "Unregistered Component!");
    }
    
	CCObject *o = NULL;
	do 
	{
		const TInfo t = _typeMap[name];
		CC_BREAK_IF(t._fun == NULL);
		o = t._fun();
	} while (0);

	return (CCComponent*)o;

}

ui::Widget* ObjectFactory::createGUI(std::string name)
{
    CCObject* object = NULL;
    
    if (name == "Panel")
    {
        name = "Layout";
    }
    else if (name == "TextArea")
    {
        name = "Label";
    }
    else if (name == "TextButton")
    {
        name = "Button";
    }
    
    do
    {
        const TInfo t = _typeMap[name];
        CC_BREAK_IF(t._fun == NULL);
        object = t._fun();
    } while (0);
    
    return static_cast<ui::Widget*>(object);
}

WidgetReaderProtocol* ObjectFactory::createWidgetReaderProtocol(std::string name)
{
    CCObject* object = NULL;
    
    do
    {
        const TInfo t = _typeMap[name];
        CC_BREAK_IF(t._fun == NULL);
        object = t._fun();
    } while (0);
    
    return dynamic_cast<WidgetReaderProtocol*>(object);
}

void ObjectFactory::registerType(const TInfo &t)
{
    _typeMap.insert(FactoryMap::value_type(t._class, t));
}
NS_CC_EXT_END