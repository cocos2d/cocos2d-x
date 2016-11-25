/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.

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

#include <functional>
#include "base/ObjectFactory.h"


NS_CC_BEGIN

ObjectFactory::TInfo::TInfo(void)
:_class("")
,_fun(nullptr)
,_func(nullptr)
{
}

ObjectFactory::TInfo::TInfo(const std::string& type, Instance ins)
:_class(type)
,_fun(ins)
,_func(nullptr)
{
    ObjectFactory::getInstance()->registerType(*this);
}

ObjectFactory::TInfo::TInfo(const std::string& type, InstanceFunc ins)
    :_class(type)
    ,_fun(nullptr)
    ,_func(ins)
{
    ObjectFactory::getInstance()->registerType(*this);
}

ObjectFactory::TInfo::TInfo(const TInfo &t)
{
    _class = t._class;
    _fun = t._fun;
    _func = t._func;
}

ObjectFactory::TInfo::~TInfo(void)
{
   _class = "";
   _fun = nullptr;
   _func = nullptr;
}

ObjectFactory::TInfo& ObjectFactory::TInfo::operator= (const TInfo &t)
{
    _class = t._class;
    _fun = t._fun;
    _func = t._func;
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
        _sharedFactory = new (std::nothrow) ObjectFactory();
    }
    return _sharedFactory;
}

void ObjectFactory::destroyInstance()
{
    CC_SAFE_DELETE(_sharedFactory);
}

Ref* ObjectFactory::createObject(const std::string &name)
{
    Ref *o = nullptr;
    do 
    {
        const TInfo t = _typeMap[name];
        if (t._fun != nullptr)
        {
            o = t._fun();
        }else if (t._func != nullptr)
        {
            o = t._func();
        }
    } while (0);
   
    return o;
}

void ObjectFactory::registerType(const TInfo &t)
{
    _typeMap.emplace(t._class, t);
}

NS_CC_END
