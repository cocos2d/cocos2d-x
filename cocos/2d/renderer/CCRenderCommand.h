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


#ifndef __CCRENDERCOMMAND_H_
#define __CCRENDERCOMMAND_H_

#include "CCPlatformMacros.h"
#include <stdint.h>
#include "ccTypes.h"
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

//TODO make RenderCommand inherent from Object
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

    /** Get Render Command Id */
    virtual inline int64_t getID() { return _id; }
    
    virtual inline Type getType() { return _type; }

protected:
    RenderCommand();
    virtual ~RenderCommand();

    void printID();

    //Generated IDs
    int64_t _id; /// used for sorting render commands
    Type _type;
};

NS_CC_END

#endif //__CCRENDERCOMMAND_H_
