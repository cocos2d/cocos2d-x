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

#include <stdint.h>

#include "platform/CCPlatformMacros.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

/** Base class of the `RenderCommand` hierarchy.
*
 The `Renderer` knows how to render `RenderCommands` objects.
 */
class CC_DLL RenderCommand
{
public:

    enum class Type
    {
        UNKNOWN_COMMAND,
        QUAD_COMMAND,
        CUSTOM_COMMAND,
        BATCH_COMMAND,
        GROUP_COMMAND,
        MESH_COMMAND,
        PRIMITIVE_COMMAND,
        TRIANGLES_COMMAND
    };

    /**
     * init function, will be called by all the render commands
     */
    void init(float globalZOrder, const Mat4& modelViewTransform, uint32_t flags);
    
    /** Get Render Command Id */
    inline float getGlobalOrder() const { return _globalOrder; }

    /** Returns the Command type */
    inline Type getType() const { return _type; }
    
    /** Retruns whether is transparent */
    inline bool isTransparent() const { return _isTransparent; }
    
    /** set transparent flag */
    inline void setTransparent(bool isTransparent) { _isTransparent = isTransparent; }

    inline bool isSkipBatching() const { return _skipBatching; }

    inline void setSkipBatching(bool value) { _skipBatching = value; }
    
    inline bool is3D() const { return _is3D; }
    
    inline void set3D(bool value) { _is3D = value; }
    
    inline float getDepth() const { return _depth; }
    
protected:
    RenderCommand();
    virtual ~RenderCommand();

    void printID();

    // Type used in order to avoid dynamic cast, faster
    Type _type;

    // commands are sort by depth
    float _globalOrder;
    
    // transparent flag
    bool  _isTransparent;

    // skip auto batching
    bool _skipBatching;
    
    // is the command been rendered on 3D pass
    bool _is3D;
    
    // depth
    float _depth;
};

NS_CC_END

#endif //__CCRENDERCOMMAND_H_
