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

#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

CustomCommand::CustomCommand()
: func(nullptr)
, _viewport(0)
, _depth(0)
{
    _type = RenderCommand::Type::CUSTOM_COMMAND;
}

void CustomCommand::init(int viewport, int32_t depth)
{
    _viewport = viewport;
    _depth = depth;
}

CustomCommand::~CustomCommand()
{

}

int64_t CustomCommand::generateID()
{
    _id = 0;

    _id = (int64_t)_viewport << 61
            | (int64_t)1 << 60 // translucent
            | (int64_t)_depth << 36;

    return _id;
}

void CustomCommand::execute()
{
    if(func)
    {
        func();
    }
}

NS_CC_END