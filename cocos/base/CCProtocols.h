/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#ifndef __BASE_CCPROTOCOLS_H__
#define __BASE_CCPROTOCOLS_H__
/// @cond DO_NOT_SHOW

#include <string>

#include "base/ccTypes.h"
#include "renderer/CCTexture2D.h"

NS_CC_BEGIN

/**
 * @~english
 * RGBA protocol that affects Node's color and opacity
 * @~chinese 
 * RGBA协议影响节点的颜色和不透明度
 */
class CC_DLL __RGBAProtocol
{
public:
    virtual ~__RGBAProtocol() {}
    
    /**
     * @~english
     * Changes the color with R,G,B bytes
     *
     * @~chinese 
     * 改变颜色的R,G,B值
     * 
     * @param color @~english Example: Color3B(255,100,0) means R=255, G=100, B=0
     * @~chinese 例如:Color3B(255,100,0) 的意思其实是 R=255, G=100, B=0
     * @js NA
     * @lua NA
     */
    virtual void setColor(const Color3B& color) = 0;
    
    /**
     * @~english
     * Returns color that is currently used.
     *
     * @~chinese 
     * 返回当前使用的颜色。
     * 
     * @return @~english The Color3B contains R,G,B bytes.
     * @~chinese Color3B包含R,G,B值。
     * @js NA
     * @lua NA
     */
    virtual const Color3B& getColor() const = 0;
    
    /**
     * @~english
     * Returns the displayed color.
     *
     * @~chinese 
     * 返回显示颜色。
     * 
     * @return @~english The Color3B contains R,G,B bytes.
     * @~chinese Color3B包含R,G,B值。
     * @js NA
     * @lua NA
     */
    virtual const Color3B& getDisplayedColor() const = 0;
    
    /**
     * @~english
     * Returns the displayed opacity.
     *
     * @~chinese 
     * 返回显示不透明度。
     * 
     * @return  @~english The opacity of sprite, from 0 ~ 255
     * @~chinese 精灵的不透明度，范围从0 ~ 255
     * @js NA
     * @lua NA
     */
    virtual GLubyte getDisplayedOpacity() const = 0;

    /**
     * @~english
     * Returns the opacity.
     *
     * The opacity which indicates how transparent or opaque this node is.
     * 0 indicates fully transparent and 255 is fully opaque.
     *
     * @~chinese 
     * 返回不透明度。
     * 
     * 不透明度,表示节点透明或不透明。
     * 0表示完全透明和255是完全不透明的。
     * 
     * @return  @~english The opacity of sprite, from 0 ~ 255
     * @~chinese 精灵的不妥名都，范围从0 ~ 255
     * @js NA
     * @lua NA
     */
    virtual GLubyte getOpacity() const = 0;
    
    /**
     * @~english
     * Changes the opacity.
     *
     * @~chinese 
     * 改变不透明度。
     * 
     * @param opacity   @~english Goes from 0 to 255, where 255 means fully opaque and 0 means fully transparent.
     * @~chinese 从0到255,255意味着完全不透明,0表示完全透明。
     * @js NA
     * @lua NA
     */
    virtual void setOpacity(GLubyte opacity) = 0;
    
    // optional
    
    /**
     * @~english
     * Changes the OpacityModifyRGB property.
     * If thie property is set to true, then the rendered color will be affected by opacity.
     * Normally, r = r * opacity/255, g = g * opacity/255, b = b * opacity/255.
     *
     * @~chinese 
     * OpacityModifyRGB属性变化。
     * 如果该属性设置为true,那么将受到不透明度的影响呈现颜色。
     * 通常情况下,r = r * opacity/255, g = g * opacity/255, b = b * opacity/255.
     * 
     * @param value @~english If true, then the opacity will be applied as: glColor(R,G,B,opacity);
     *              If false, then the opacity will be applied as: glColor(opacity, opacity, opacity, opacity);
     * @~chinese 如果设置为true,那么不透明将被这样使用: glColor(R,G,B,opacity);
     * 如果为false,不透明度将被这样使用: glColor(opacity, opacity, opacity, opacity);
     *
     * @js NA
     * @lua NA
     */
    virtual void setOpacityModifyRGB(bool value) = 0;
    
    /**
     * @~english
     * Returns whether or not the opacity will be applied using glColor(R,G,B,opacity)
     * or glColor(opacity, opacity, opacity, opacity)
     *
     * @~chinese 
     * 返回是否将采用不透明度，glColor（R，G，B，opacity）
     * 或者glColor(opacity, opacity, opacity, opacity)
     * 
     * @return  @~english Returns opacity modify flag.
     * @~chinese 返回不透明度修改标志。
     * @js NA
     * @lua NA
     */
    virtual bool isOpacityModifyRGB() const = 0;
    
    /**
     * @~english
     *  whether or not color should be propagated to its children.
     * @~chinese 
     * 颜色是否应该传播到其子节点。
     * @js NA
     * @lua NA
     */
    virtual bool isCascadeColorEnabled() const = 0;

    /**
     * @~english
     *  Set whether or not color should be propagated to its children.
     * @~chinese
     * 设置颜色是否应该传播到其子节点。
     *
     * @param cascadeColorEnabled @~english whether or not color should be propagated to its children.
     * @~chinese
     * 颜色是否应该传播到其子节点。
     *
     * @js NA
     * @lua NA
     */
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) = 0;
    
    /**
     * @~english
     *  recursive method that updates display color
     * @~chinese 
     * 使用递归的方法去更新显示的颜色
     * @js NA
     * @lua NA
     */
    virtual void updateDisplayedColor(const Color3B& color) = 0;
    
    /**
     * @~english
     *  whether or not opacity should be propagated to its children.
     * @~chinese 
     * 不透明度是否应该传播到其子节点。
     * @js NA
     * @lua NA
     */
    virtual bool isCascadeOpacityEnabled() const = 0;

    /**
     * @~english Set whether or not opacity should be propagated to its children.
     * @~chinese
     * 设置不透明度是否应该传播到其子节点。
     * @js NA
     * @lua NA
     */
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) = 0;
    
    /**
     * @~english
     *  recursive method that updates the displayed opacity.
     * @~chinese 
     * 使用递归的方法去更新显示的不透明度。
     * @js NA
     * @lua NA
     */
    virtual void updateDisplayedOpacity(GLubyte opacity) = 0;
};

/**
 * @~english
 * Specify the blending function according glBlendFunc
 * Please refer to glBlendFunc in OpenGL ES Manual
 * http://www.khronos.org/opengles/sdk/docs/man/xhtml/glBlendFunc.xml for more details.
 * @~chinese 
 * 指定glBlendFunc混合函数
 * 请参阅glBlendFunc在OpenGL ES手册
 * http://www.khronos.org/opengles/sdk/docs/man/xhtml/glBlendFunc.xml for more details.
 */
class CC_DLL BlendProtocol
{
public:
    virtual ~BlendProtocol() {}

    /**
     * @~english
     * Sets the source blending function.
     *
     * @~chinese 
     * 设置源混合函数。
     * 
     * @param blendFunc @~english A structure with source and destination factor to specify pixel arithmetic, 
     *                  e.g. {GL_ONE, GL_ONE}, {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}.
     * @~chinese 结构与源和目标因素指定像素运算,
     * 例如GL_ONE, GL_ONE}, {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}.
     * @js NA
     * @lua NA
     */
    virtual void setBlendFunc(const BlendFunc &blendFunc) = 0;

    /**
     * @~english
     * Returns the blending function that is currently being used.
     * 
     * @~chinese 
     * 返回当前正在使用的混合函数。
     * 
     * @return @~english A BlendFunc structure with source and destination factor which specified pixel arithmetic.
     * @~chinese BlendFunc结构指定源和目标因素像素运算。
     * @js NA
     * @lua NA
     */
    virtual const BlendFunc &getBlendFunc() const = 0;
};

/**
 * @~english
 * Node objects that uses a Texture2D to render the images.
 * The texture can have a blending function.
 * If the texture has alpha premultiplied the default blending function is:
 *   src=GL_ONE dst= GL_ONE_MINUS_SRC_ALPHA
 * else
 *   src=GL_SRC_ALPHA dst= GL_ONE_MINUS_SRC_ALPHA
 * But you can change the blending function at any time.
 * @~chinese 
 * 节点对象使用Texture2D显示图像。
 * 纹理可以混合函数。
 * 如纹理透明度左乘默认混合函数是:
 * src = GL_ONE dst = GL_ONE_MINUS_SRC_ALPHA
 * 其他:
 * src = GL_SRC_ALPHA dst = GL_ONE_MINUS_SRC_ALPHA
 * 你可以在任何时候改变混合函数。
 */
class CC_DLL TextureProtocol : public BlendProtocol
{
public:
    virtual ~TextureProtocol() {}

    /**
     * @~english
     * Returns the currently used texture
     *
     * @~chinese 
     * 返回当前使用的纹理
     * 
     * @return  @~english The texture that is currently being used.
     * @~chinese 现在正在使用的纹理。
     * @js NA
     * @lua NA
     */
    virtual Texture2D* getTexture() const = 0;

    /**
     * @~english
     * Sets a new texture. It will be retained.
     *
     * @~chinese 
     * 设置一个新的纹理。
     * 
     * @param texture @~english A valid Texture2D object, which will be applied to this sprite object.
     * @~chinese 一个有效Texture2D对象,它将被应用到这个精灵。
     * @js NA
     * @lua NA
     */
    virtual void setTexture(Texture2D *texture) = 0;
};

/**
 * @~english
 * Common interface for Labels
 * @~chinese 
 * 通用接口的标签
 */
class CC_DLL LabelProtocol
{
public:
    virtual ~LabelProtocol() {}

    /**
     * @~english
     * Sets a new label using a string
     *
     * @~chinese 
     * 使用一个字符串设置一个新的Label
     * 
     * @param label @~english A null terminated string
     * @~chinese 以空字符结尾的字符串
     * @js NA
     * @lua NA
     */
    virtual void setString(const std::string &label) = 0;

    /**
     * @~english
     * Returns the string that is currently being used in this label 
     *
     * @~chinese 
     * 返回字符串中目前使用的这个标签
     * 
     * @return @~english The string that is currently being used in this label
     * @~chinese 这个Label正在使用的字符串
     * @js NA
     * @lua NA
     */
    virtual const std::string& getString() const = 0;
};

/**
 * @~english
 * OpenGL projection protocol 
 * @~chinese 
 * OpenGL投影协议
 */
class CC_DLL DirectorDelegate
{
public:
    virtual ~DirectorDelegate() {}

    /**
     * @~english
     * Will be called by Director when the projection is updated, and "custom" projection is used
     * @~chinese 
     * 在Director投影时更新,并且使用“custom”投影的方法
     * @js NA
     * @lua NA
     */
    virtual void updateProjection() = 0;
};

NS_CC_END

/// @endcond
#endif // __BASE_CCPROTOCOLS_H__
