/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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

#ifndef __CCPROTOCOLS_H__
#define __CCPROTOCOLS_H__

#include "ccTypes.h"
#include "CCTexture2D.h"
#include <string>

NS_CC_BEGIN

/**
 * Specify the blending function according glBlendFunc
 * Please refer to glBlendFunc in OpenGL ES Manual
 * http://www.khronos.org/opengles/sdk/docs/man/xhtml/glBlendFunc.xml for more details.
 */
class CC_DLL BlendProtocol
{
public:
    virtual ~BlendProtocol() {}

    /**
     * Sets the source blending function.
     *
     * @param blendFunc A structure with source and destination factor to specify pixel arithmetic, 
     *                  e.g. {GL_ONE, GL_ONE}, {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}.
     * @js NA
     * @lua NA
     */
    virtual void setBlendFunc(const BlendFunc &blendFunc) = 0;

    /**
     * Returns the blending function that is currently being used.
     * 
     * @return A BlendFunc structure with source and destination factor which specified pixel arithmetic.
     * @js NA
     * @lua NA
     */
    virtual const BlendFunc &getBlendFunc() const = 0;
};

/** 
 * Node objects that uses a Texture2D to render the images.
 * The texture can have a blending function.
 * If the texture has alpha premultiplied the default blending function is:
 *   src=GL_ONE dst= GL_ONE_MINUS_SRC_ALPHA
 * else
 *   src=GL_SRC_ALPHA dst= GL_ONE_MINUS_SRC_ALPHA
 * But you can change the blending function at any time.
 */
class CC_DLL TextureProtocol : public BlendProtocol
{
public:
    virtual ~TextureProtocol() {}
    /**
     * Returns the currently used texture
     *
     * @return  The texture that is currenlty being used.
     * @js NA
     * @lua NA
     */
    virtual Texture2D* getTexture() const = 0;

    /**
     * Sets a new texuture. It will be retained.
     *
     * @param   texture A valid Texture2D object, which will be applied to this sprite object.
     * @js NA
     * @lua NA
     */
    virtual void setTexture(Texture2D *texture) = 0;
};

/**
 * Common interface for Labels
 */
class CC_DLL LabelProtocol
{
public:
    virtual ~LabelProtocol() {}

    /**
     * Sets a new label using a string
     *
     * @param label A null terminated string
     * @js NA
     * @lua NA
     */
    virtual void setString(const std::string &label) = 0;

    /** 
     * Returns the string that is currently being used in this label 
     *
     * @return The string that is currently being used in this label
     * @js NA
     * @lua NA
     */
    virtual const std::string& getString() const = 0;
};

/** 
 * OpenGL projection protocol 
 */
class CC_DLL DirectorDelegate
{
public:
    virtual ~DirectorDelegate() {}

    /**
     * Will be called by Director when the projection is updated, and "custom" projection is used
     * @js NA
     * @lua NA
     */
    virtual void updateProjection() = 0;
};

NS_CC_END

#endif // __CCPROTOCOLS_H__
