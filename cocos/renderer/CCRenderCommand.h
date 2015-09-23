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

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

/** Base class of the `RenderCommand` hierarchy.
*
 The `Renderer` knows how to render `RenderCommands` objects.
 */
class CC_DLL RenderCommand
{
public:
    /**Enum the type of render command. */
    enum class Type
    {
        /** Reserved type.*/
        UNKNOWN_COMMAND,
        /** Quad command, used for draw quad.*/
        QUAD_COMMAND,
        /**Custom command, used for calling callback for rendering.*/
        CUSTOM_COMMAND,
        /**Batch command, used for draw batches in texture atlas.*/
        BATCH_COMMAND,
        /**Group command, which can group command in a tree hierarchy.*/
        GROUP_COMMAND,
        /**Mesh command, used to draw 3D meshes.*/
        MESH_COMMAND,
        /**Primitive command, used to draw primitives such as lines, points and triangles.*/
        PRIMITIVE_COMMAND,
        /**Triangles command, used to draw triangles.*/
        TRIANGLES_COMMAND
    };

    /**
     Init function, will be called by all the render commands.
     @param globalZOrder The global order of command, used for rendercommand sorting.
     @param modelViewTransform Modelview matrix when submitting the render command.
     @param flags Flag used to indicate whether the command should be draw at 3D mode or not.
     */
    void init(float globalZOrder, const Mat4& modelViewTransform, uint32_t flags);
    
    /** Get global Z order. */
    inline float getGlobalOrder() const { return _globalOrder; }

    /** Returns the Command type. */
    inline Type getType() const { return _type; }
    
    /** Retruns whether is transparent. */
    inline bool isTransparent() const { return _isTransparent; }
    
    /** Set transparent flag. */
    inline void setTransparent(bool isTransparent) { _isTransparent = isTransparent; }
    /**
     Get skip batching status, if a rendering is skip batching, it will be forced to be rendering separately.
     */
    inline bool isSkipBatching() const { return _skipBatching; }
    /**Set skip batching.*/
    inline void setSkipBatching(bool value) { _skipBatching = value; }
    /**Whether the command should be rendered at 3D mode.*/
    inline bool is3D() const { return _is3D; }
    /**Set the command rendered in 3D mode or not.*/
    inline void set3D(bool value) { _is3D = value; }
    /**Get the depth by current model view matrix.*/
    inline float getDepth() const { return _depth; }
    
protected:
    /**Constructor.*/
    RenderCommand();
    /**Destructor.*/
    virtual ~RenderCommand();
    //used for debug but it is not implemented.
    void printID();

    /**Type used in order to avoid dynamic cast, faster. */
    Type _type;

    /** Commands are sort by global Z order. */
    float _globalOrder;
    
    /** Transparent flag. */
    bool  _isTransparent;
    
    /**
     QuadCommand and TrianglesCommand could be auto batched if there material ID is the same, however, if
     a command is skip batching, it would be forced to draw in a separate function call, and break the batch.
     */
    bool _skipBatching;
    
    /** Is the command been rendered on 3D pass. */
    bool _is3D;
    
    /** Depth from the model view matrix.*/
    float _depth;
};

NS_CC_END
/**
 end of support group
 @}
 */
#endif //__CCRENDERCOMMAND_H_
