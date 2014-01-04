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

#include "cocostudio/CCComRender.h"

namespace cocostudio {

ComRender::ComRender(void)
: _render(nullptr)
{
    _name = "CCComRender";
}


ComRender::ComRender(cocos2d::Node *node, const char *comName)
{
    _render = node;
    _name.assign(comName);
}

ComRender::~ComRender(void)
{
    _render = nullptr;
}

void ComRender::onEnter()
{
    if (_owner != nullptr)
    {
        _owner->addChild(_render);
    }
}

void ComRender::onExit()
{
    _render = nullptr;
}

cocos2d::Node* ComRender::getNode()
{
    return _render;
}

void ComRender::setNode(cocos2d::Node *node)
{
	_render = node;
}

ComRender* ComRender::create(cocos2d::Node *node, const char *comName)
{
    ComRender * ret = new ComRender(node, comName);
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

}
