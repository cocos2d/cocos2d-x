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

#ifndef _CC_PRIMITIVE_COMMAND_H__
#define _CC_PRIMITIVE_COMMAND_H__

#include "renderer/CCPrimitive.h"
#include "renderer/CCRenderCommand.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN
class GLProgramState;
/**
 Command used to render primitive, similar to QuadCommand.
 Every QuadCommand will have generate material ID by give textureID, glProgramState, Blend function. 
 However, primitive command could not be batched.
 */
class CC_DLL PrimitiveCommand : public RenderCommand
{
public:
    /**@{
     Constructor and Destructor.
     */
    PrimitiveCommand();
    ~PrimitiveCommand();
    
    /**@}*/
    
    /** Initializes the command.
     @param globalOrder GlobalZOrder of the command.
     @param textureID The openGL handle of the used texture.
     @param glProgramState The specified glProgram and its uniform.
     @param blendType Blend function for the command.
     @param primitive Rendered primitive for the command.
     @param mv ModelView matrix for the command.
     @param flags to indicate that the command is using 3D rendering or not.
     */
    void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, Primitive* primitive, const Mat4& mv, uint32_t flags);
    CC_DEPRECATED_ATTRIBUTE void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, Primitive* primitive,const Mat4& mv);
    
    /**Get the generated material ID.*/
    inline uint32_t getMaterialID() const { return _materialID; }
    /**Get the texture ID used for drawing.*/
    inline GLuint getTextureID() const { return _textureID; }
    /**Get the glprogramstate used for drawing.*/
    inline GLProgramState* getGLProgramState() const { return _glProgramState; }
    /**Get the blend function for drawing.*/
    inline BlendFunc getBlendType() const { return _blendType; }
    /**Get the modelview matrix when draw the primitive.*/
    inline const Mat4& getModelView() const { return _mv; }
    /**Execute and draw the command, called by renderer.*/
    void execute() const;
protected:
    
    uint32_t _materialID;
    GLuint _textureID;
    GLProgramState* _glProgramState;
    BlendFunc _blendType;
    Primitive* _primitive;
    Mat4 _mv;
};

NS_CC_END

/**
 end of support group
 @}
 */
#endif //_CC_PRIMITIVE_COMMAND_H__
