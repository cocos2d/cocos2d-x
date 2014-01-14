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


#ifndef _CC_CUSTOMCOMMAND_H_
#define _CC_CUSTOMCOMMAND_H_

#include "CCRenderCommand.h"
#include "CCRenderCommandPool.h"

NS_CC_BEGIN

class CustomCommand : public RenderCommand
{
public:
    CustomCommand();
    ~CustomCommand();
    
public:

    void init(int viewport, int32_t depth);

    // +----------+----------+-----+-----------------------------------+
    // |          |          |     |                |                  |
    // | ViewPort | Transluc |     |      Depth     |                  |
    // |   3 bits |    1 bit |     |    24 bits     |                  |
    // +----------+----------+-----+----------------+------------------+
    virtual int64_t generateID();

    void execute();

    inline bool isTranslucent() { return true; }
    std::function<void()> func;

protected:
    int _viewport;
    int32_t _depth;
};

NS_CC_END

#endif //_CC_CUSTOMCOMMAND_H_
