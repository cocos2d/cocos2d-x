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
#include "textures/CCTexture2D.h"
#include <string>

NS_CC_BEGIN

/**
 * RGBA protocol that affects CCNode's color and opacity
 * @js NA
 */
class CC_DLL CCRGBAProtocol
{
public:
    /** 
     * Changes the color with R,G,B bytes
     *
     * @param color Example: ccc3(255,100,0) means R=255, G=100, B=0
     */
    virtual void setColor(const ccColor3B& color) = 0;

    /**
     * Returns color that is currently used.
     *
     * @return The ccColor3B contains R,G,B bytes.
     */
    virtual const ccColor3B& getColor(void) = 0;
    
    /**
     * Returns the displayed color.
     *
     * @return The ccColor3B contains R,G,B bytes.
     */
    virtual const ccColor3B& getDisplayedColor(void) = 0;
    
    /**
     * Returns the displayed opacity.
     *
     * @return  The opacity of sprite, from 0 ~ 255
     */
    virtual GLubyte getDisplayedOpacity(void) = 0;
    /**
     * Returns the opacity.
     *
     * The opacity which indicates how transparent or opaque this node is.
     * 0 indicates fully transparent and 255 is fully opaque.
     *
     * @return  The opacity of sprite, from 0 ~ 255
     */
    virtual GLubyte getOpacity(void) = 0;

    /**
     * Changes the opacity.
     *
     * @param   value   Goes from 0 to 255, where 255 means fully opaque and 0 means fully transparent.
     */
    virtual void setOpacity(GLubyte opacity) = 0;

    // optional

    /**
     * Changes the OpacityModifyRGB property. 
     * If thie property is set to true, then the rendered color will be affected by opacity.
     * Normally, r = r * opacity/255, g = g * opacity/255, b = b * opacity/255.
     *
     * @param   bValue  true then the opacity will be applied as: glColor(R,G,B,opacity);
     *                  false then the opacity will be applied as: glColor(opacity, opacity, opacity, opacity);
     */
    virtual void setOpacityModifyRGB(bool bValue) = 0;

    /**
     * Returns whether or not the opacity will be applied using glColor(R,G,B,opacity) 
     * or glColor(opacity, opacity, opacity, opacity)
     *
     * @return  Returns opacity modify flag.
     */
    virtual bool isOpacityModifyRGB(void) = 0;
    
    /**
     *  whether or not color should be propagated to its children.
     */
    virtual bool isCascadeColorEnabled(void) = 0;
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) = 0;
    
    /** 
     *  recursive method that updates display color 
     */
    virtual void updateDisplayedColor(const ccColor3B& color) = 0;
    
    /** 
     *  whether or not opacity should be propagated to its children.
     */
    virtual bool isCascadeOpacityEnabled(void) = 0;
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) = 0;
    
    /**
     *  recursive method that updates the displayed opacity.
     */
    virtual void updateDisplayedOpacity(GLubyte opacity) = 0;
};

/**
 * Specify the blending function according glBlendFunc
 * Please refer to glBlendFunc in OpenGL ES Manual
 * http://www.khronos.org/opengles/sdk/docs/man/xhtml/glBlendFunc.xml for more details.
 * @js NA
 * @lua NA
 */
class CC_DLL CCBlendProtocol
{
public:
    /**
     * Sets the source blending function.
     *
     * @param blendFunc A structure with source and destination factor to specify pixel arithmetic, 
     *                  e.g. {GL_ONE, GL_ONE}, {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}.
     *
     */
    virtual void setBlendFunc(ccBlendFunc blendFunc) = 0;

    /**
     * Returns the blending function that is currently being used.
     * 
     * @return A ccBlendFunc structure with source and destination factor which specified pixel arithmetic.
     */
    virtual ccBlendFunc getBlendFunc(void) = 0;
};

/** 
 * CCNode objects that uses a CCTexture2D to render the images.
 * The texture can have a blending function.
 * If the texture has alpha premultiplied the default blending function is:
 *   src=GL_ONE dst= GL_ONE_MINUS_SRC_ALPHA
 * else
 *   src=GL_SRC_ALPHA dst= GL_ONE_MINUS_SRC_ALPHA
 * But you can change the blending function at any time.
 * @js NA
 */
class CC_DLL CCTextureProtocol : public CCBlendProtocol
{
public:
    /**
     * Returns the currently used texture
     *
     * @return  The texture that is currenlty being used.
     * @lua NA
     */
    virtual CCTexture2D* getTexture(void) = 0;

    /**
     * Sets a new texuture. It will be retained.
     *
     * @param   texture A valid CCTexture2D object, which will be applied to this sprite object.
     * @lua NA
     */
    virtual void setTexture(CCTexture2D *texture) = 0;
};

/**
 * Common interface for Labels
 * @js NA
 * @lua NA
 */
class CC_DLL CCLabelProtocol
{
public:
    /**
     * Sets a new label using an string
     *
     * @param A null terminated string 
     */
    virtual void setString(const char *label) = 0;

    /** 
     * Returns the string that is currently being used in this label 
     *
     * @return The string that is currently being used in this label
     */
    virtual const char* getString(void) = 0;
};

/** 
 * OpenGL projection protocol 
 * @js NA
 * @lua NA
 */
class CC_DLL CCDirectorDelegate
{
public:
    /** 
     * Will be called by CCDirector when the projection is updated, and "custom" projection is used
     */
    virtual void updateProjection(void) = 0;
};

NS_CC_END

#endif // __CCPROTOCOLS_H__
