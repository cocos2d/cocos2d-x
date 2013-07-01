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

#include "support/component/CCComponent.h"


NS_CC_BEGIN

Component::Component(void)
: _owner(NULL)
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

void Component::serialize(void *ar)
{
}

Component* Component::create(void)
{
    Component * pRet = new Component();
    if (pRet != NULL && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

const char* Component::getName() const
{
    return _name.c_str();
}

Node* Component::getOwner() const
{
    return _owner;
}

void Component::setOwner(Node *pOwner)
{
    _owner = pOwner;
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
