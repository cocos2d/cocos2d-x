/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

using namespace cocos2d;

namespace cocostudio {

ObjectFactory::TInfo::TInfo(void)
:_class("")
,_fun(nullptr)
{
}

ObjectFactory::TInfo::TInfo(const std::string& type, Instance ins)
:_class(type)
,_fun(ins)
{
    ObjectFactory::getInstance()->registerType(*this);
}

ObjectFactory::TInfo::TInfo(const TInfo &t)
{
    _class = t._class;
    _fun = t._fun;
}

ObjectFactory::TInfo::~TInfo(void)
{
   _class = "";
   _fun = nullptr;
}

ObjectFactory::TInfo& ObjectFactory::TInfo::operator= (const TInfo &t)
{
    _class = t._class;
    _fun = t._fun;
    return *this;
}


ObjectFactory* ObjectFactory::_sharedFactory = nullptr;

ObjectFactory::ObjectFactory(void)
{

}

ObjectFactory::~ObjectFactory(void)
{
    _typeMap.clear();
}

ObjectFactory* ObjectFactory::getInstance()
{
    if ( nullptr == _sharedFactory)
    {
        _sharedFactory = new ObjectFactory();
    }
    return _sharedFactory;
}

void ObjectFactory::destroyInstance()
{
    CC_SAFE_DELETE(_sharedFactory);
}

Object* ObjectFactory::createObject(const std::string &name)
{
	Object *o = nullptr;
	do 
	{
		const TInfo t = _typeMap[name];
		CC_BREAK_IF(t._fun == nullptr);
		o = t._fun();
	} while (0);
   
    return o;
}

Component* ObjectFactory::createComponent(const std::string &name)
{
    std::string comName;
	if (name == "CCSprite" || name == "CCTMXTiledMap" || name == "CCParticleSystemQuad" || name == "CCArmature" || name == "GUIComponent")
	{
		comName = "ComRender";
	}
	else if (name == "CCComAudio" || name == "CCBackgroundAudio")
	{
		comName = "ComAudio";
	}
    else if (name == "CCComController")
    {
        comName = "ComController";
    }
    else if (name == "CCComAttribute")
    {
        comName = "ComAttribute";
    }
    else if (name == "CCScene")
    {
        comName = "Scene";
    }
    else
    {
        CCASSERT(false, "Unregistered Component!");
    }
	Object *o = NULL;
	do 
	{
		const TInfo t = _typeMap[comName];
		CC_BREAK_IF(t._fun == NULL);
		o = t._fun();
	} while (0);

	return (Component*)o;

}

void ObjectFactory::registerType(const TInfo &t)
{
    _typeMap.insert(std::make_pair(t._class, t));
}

}