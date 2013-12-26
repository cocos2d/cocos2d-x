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


#ifndef __CCRENDERCOMMAND_H_
#define __CCRENDERCOMMAND_H_

#include "CCPlatformMacros.h"
#include <stdint.h>
#include "ccTypes.h"
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

//Currently we use 24 bit for depth, so the max is 2^24=16777216
#define CC_RENDERER_DEPTH_MAX 16777216
#define CC_RENDERER_DEPTH_HALF 8388608
#define CC_RENDERER_DEPTH_MIN 0

class RenderCommand
{
public:

    enum class Type
    {
        QUAD_COMMAND,
        CUSTOM_COMMAND,
        GROUP_COMMAND,
        UNKNOWN_COMMAND,
    };

    virtual int64_t generateID() = 0;
    void init(int viewport, float depth);

    /** Get Render Command Id */
    virtual inline int64_t getID() { return _id; }
    
    virtual inline Type getType() { return _type; }
    virtual void releaseToCommandPool() =0;

protected:
    RenderCommand();
    virtual ~RenderCommand();

    void printID();

    //Generated IDs
    int64_t _id; /// used for sorting render commands
    Type _type;
    
    int _viewport; /// Which view port it belongs to
    int32_t _depth; /// Depth of the render command
};

NS_CC_END

#endif //__CCRENDERCOMMAND_H_
