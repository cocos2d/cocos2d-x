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

#include "CCComponent.h"


NS_CC_BEGIN

Component::Component(void)
: _owner(nullptr)
, _enabled(true)
{
}

Component::~Component(void)
{
}

bool Component::init()
{
    return true;
}

void Component::onEnter()
{
}

void Component::onExit()
{
}

void Component::update(float delta)
{
}

bool Component::serialize(void *ar)
{
    return true;
}

Component* Component::create(void)
{
    Component * ret = new Component();
    if (ret != nullptr && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}

const std::string& Component::getName() const
{
    return _name;
}

void Component::setName(const std::string& name)
{
    _name = name;
}

Node* Component::getOwner() const
{
    return _owner;
}

void Component::setOwner(Node *owner)
{
    _owner = owner;
}

bool Component::isEnabled() const
{
    return _enabled;
}

void Component::setEnabled(bool b)
{
    _enabled = b;
}

NS_CC_END
