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


#include "renderer/CCRenderCommand.h"
#include "2d/CCCamera.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

RenderCommand::RenderCommand()
: _type(RenderCommand::Type::UNKNOWN_COMMAND)
, _globalOrder(0)
, _isTransparent(true)
, _skipBatching(false)
, _is3D(false)
, _depth(0)
{
}

RenderCommand::~RenderCommand()
{
}

void RenderCommand::init(float globalZOrder, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _globalOrder = globalZOrder;
    if (flags & Node::FLAGS_RENDER_AS_3D)
    {
        if (Camera::getVisitingCamera())
            _depth = Camera::getVisitingCamera()->getDepthInView(transform);
        
        set3D(true);
    }
    else
    {
        set3D(false);
        _depth = 0;
    }
}

void printBits(ssize_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    ssize_t i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = b[i] & (1<<j);
            byte >>= j;
            printf("%u", byte);
        }
    }
    puts("");
}

void RenderCommand::printID()
{
    printf("Command Depth: %f\n", _globalOrder);
}

NS_CC_END
