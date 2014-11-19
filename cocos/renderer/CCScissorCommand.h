
#pragma once

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
#include <stack>

NS_CC_BEGIN

// @brief base class for scissor commands, provides a static count
// of the nested scissor commands that have begun. Scissor state
// is only disabled once the count reaches zero.
class ScissorCommand
    : public RenderCommand
{
public:
    
    static int scissorCount() 
    {
        return _scissorCount;
    }
    
protected:
    
    // @brief the scissor clipping region for counts > 0.
    Rect _clippingRegion;
    
    // @brief flag to respect previous clipping regions for nested scissors.
    bool _respectPreviousScissor;

    // @brief tracks the number of nested scissor commands,
    // scissor is disabled when all commands have completed.
    static int _scissorCount;
    
    // @brief previous clipping region
    typedef std::stack<Rect> tClippingRegions;
    static tClippingRegions _clippingRegions;
};

// @brief increments the scissor count and enables the scissor
// if this is the first begin. It also remembers the old scissor
// rectangle, and will restore it when it ends.
class BeginScissorCommand
    : public ScissorCommand
{
public:
    BeginScissorCommand();
    void init(float depth, const Rect& clippingRegion, bool respectPreviousScissor = true);
    void execute();
};

// @brief ends a scissor command, restores the previous scissor
// state if any, and decrements the scissor count. If the scissor
// count reaches zero, then the scissor is disabled.
class EndScissorCommand
    : public ScissorCommand
{
public:
    EndScissorCommand();
    void init(float depth);
    void execute();
};

NS_CC_END