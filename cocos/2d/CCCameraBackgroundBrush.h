/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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
#ifndef _CCCAMERA_BACKGROUND_BRUSH_H__
#define _CCCAMERA_BACKGROUND_BRUSH_H__

#include "base/ccTypes.h"
#include "base/CCRef.h"
#include "3d/CCFrustum.h"
#include "renderer/CCQuadCommand.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCFrameBuffer.h"

NS_CC_BEGIN

class CameraBackgroundColorBrush;
class CameraBackgroundDepthBrush;
class CameraBackgroundSkyBoxBrush;

class GLProgramState;
class Camera;

/**
 * @class CameraBackgroundBrush
 * @brief @~english Defines a brush to clear the background of camera. There are 4 types of brush. None brush do nothing, Depth brush clear background with given depth, Color brush clear background with given color and depth, Skybox brush clear the background with a skybox. Camera uses depth brush by default.
 * @~chinese CameraBackgroundBrush 定义一个清除相机背景的背景刷。有4种类型的刷子，None brush不做任何事情，Depth brush用给定的深度来清除背景，Color brush用给定的颜色清除相机背景，Skybox brush用天空盒清除相机背景。相机默认使用depth brush，只清除深度。
 */
class CC_DLL CameraBackgroundBrush : public Ref
{
public:
    /**
     * @~english Brush types. There are 4 types of brush. See CameraBackgroundDepthBrush, CameraBackgroundColorBrush, CameraBackgroundSkyBoxBrush for more information.
     * @~chinese 有4种类型的刷子，None brush不做任何事情，Depth brush用给定的深度来清除背景，Color brush用给定的颜色清除相机背景，Skybox brush用天空盒清除相机背景。
     */
    enum class BrushType
    {
        /** @~english none brush
         * @~chinese None brush不做任何事情
         */
        NONE,
        /** @~english depth brush. See CameraBackgroundDepthBrush
         * @~chinese 深度背景刷
         */
        DEPTH,
        /** @~english color brush. See CameraBackgroundColorBrush
         * @~chinese 颜色背景刷
         */
        COLOR,
        /** @~english skybox brush. See CameraBackgroundSkyBoxBrush
         * @~chinese 天空盒背景刷
         */
        SKYBOX,
    };
    
    /**@~english
     * get brush type
     * @~chinese 获取背景刷类型
     * @return @~english BrushType
     * @~chinese 背景刷类型
     */
    virtual BrushType getBrushType() const { return BrushType::NONE; }
    
    /** @~english
     * Creates a none brush, it does nothing when clear the background
     * @~chinese 创建一个空的背景刷
     * @return @~english Created brush.
     * @~chinese 创建的背景刷
     */
    static CameraBackgroundBrush* createNoneBrush();
    
    /**
     * Creates a depth brush, which clears depth buffer with a given depth.
     * @param depth @~english Depth used to clear depth buffer
     * @~chinese 清除背景刷的深度
     * @return @~english Created brush
     * @~chinese 创建的背景刷
     */
    static CameraBackgroundDepthBrush* createDepthBrush(float depth = 1.f);
    
    /** @~english
     * Creates a color brush
     * @~chinese 创建颜色背景刷
     * @param color @~english Color of brush
     * @~chinese 背景刷的颜色
     * @param depth @~english Depth used to clear depth buffer
     * @~chinese 背景刷的深度
     * @return @~english Created brush
     * @~chinese 创建的背景刷
     */
    static CameraBackgroundColorBrush* createColorBrush(const Color4F& color, float depth);
    
    
    /** @~english Creates a Skybox brush with 6 textures.
     * @~chinese 用6张纹理创建一个天空盒背景刷
     * @param @~english positive_x texture for the right side of the texture cube face.
     * @~chinese 正x方向的纹理。
     * @param negative_x @~english texture for the up side of the texture cube face.
     * @~chinese 负x方向的纹理。
     * @param positive_y @~english texture for the top side of the texture cube face
     * @~chinese 正y方向的纹理。
     * @param negative_y @~english texture for the bottom side of the texture cube face
     * @~chinese 负y方向的纹理。
     * @param positive_z @~english texture for the forward side of the texture cube face.
     * @~chinese 正z方向的纹理。
     * @param negative_z @~english negative_z texture for the rear side of the texture cube face.
     * @~chinese 负z方向的纹理。
     * @return @~english A new brush inited with given parameters.
     * @~chinese 新创建的天空盒背景刷。
     */
    static CameraBackgroundSkyBoxBrush* createSkyboxBrush(const std::string& positive_x, const std::string& negative_x,
                                                          const std::string& positive_y, const std::string& negative_y,
                                                          const std::string& positive_z, const std::string& negative_z);
    /**@~english
     * draw the background
     * @~chinese 绘制相机背景
     */
    virtual void drawBackground(Camera* camera) {}

    /**@~english
     * is valid?
     * @~chinese 是否有效？
     */
    virtual bool isValid() { return true; }

CC_CONSTRUCTOR_ACCESS :
    CameraBackgroundBrush();
    virtual ~CameraBackgroundBrush();

    virtual bool init() { return true; }
    
protected:
    GLProgramState* _glProgramState;
};

/** @class CameraBackgroundDepthBrush
 * @brief @~english Depth brush clear depth buffer with given depth
 * @~chinese 深度刷用给定的深度清除深度缓冲
 */
class CC_DLL CameraBackgroundDepthBrush : public CameraBackgroundBrush
{
public:
    /** @~english
     * Create a depth brush
     * @~chinese 创建深度背景刷
     * @param depth @~english Depth used to clear the depth buffer
     * @~chinese 用来清除背景的深度
     * @return @~english Created brush
     * @~chinese 创建的背景刷
     */
    static CameraBackgroundDepthBrush* create(float depth);
    
    /** @~english
     * Get brush type. Should be BrushType::DEPTH
     * @~chinese 获取相机背景刷的类型，应该为BrushType::DEPTH
     * @return @~english brush type
     * @~chinese 背景刷的类型
     */
    virtual BrushType getBrushType() const override { return BrushType::DEPTH; }
    
    /** @~english
     * Draw background
     * @~chinese 绘制背景
     */
    virtual void drawBackground(Camera* camera) override;
    
    /** @~english
     * Set depth
     * @~chinese 设置背景刷深度
     * @param depth @~english Depth used to clear depth buffer
     * @~chinese 清除背景的深度
     */
    void setDepth(float depth) { _depth = depth; }
    
CC_CONSTRUCTOR_ACCESS:
    CameraBackgroundDepthBrush();
    virtual ~CameraBackgroundDepthBrush();

    virtual bool init() override;
    
protected:
    float _depth;
    
    GLboolean _clearColor;
    
    V3F_C4B_T2F_Quad _quad;
};

/**@class CameraBackgroundColorBrush
 * @brief @~english
 * Color brush clear buffer with given depth and color
 * @~chinese 颜色背景刷，用给定的颜色和深度清除背景缓冲
 */
class CC_DLL CameraBackgroundColorBrush : public CameraBackgroundDepthBrush
{
public:
    /** @~english
     * Get brush type. Should be BrushType::COLOR
     * @~chinese 获取背景刷的类型，应该为BrushType::COLOR
     * @return @~english brush type
     * @~chinese 背景刷类型
     */
    virtual BrushType getBrushType() const override { return BrushType::COLOR; }
    
    /** @~english
     * Create a color brush
     * @~chinese 创建颜色背景刷
     * @param color @~english Color used to clear the color buffer
     * @~chinese 清除背景的颜色
     * @param depth @~english Depth used to clear the depth buffer
     * @~chinese 清除背景的深度
     * @return @~english Created brush
     * @~chinese 创建的背景刷
     */
    static CameraBackgroundColorBrush* create(const Color4F& color, float depth);
    
    /** @~english
     * Set clear color
     * @~chinese 设置清除背景的颜色
     * @param color @~english Color used to clear the color buffer
     * @~chinese 清除颜色缓冲的颜色
     */
    void setColor(const Color4F& color);
    
CC_CONSTRUCTOR_ACCESS:
    CameraBackgroundColorBrush();
    virtual ~CameraBackgroundColorBrush();

    virtual bool init() override;
    
protected:
    Color4F _color;
};

class TextureCube;
class GLProgramState;
class EventListenerCustom;

/**@class CameraBackgroundSkyBoxBrush 
 * @brief @~english Skybox brush clear buffer with a skybox
 * @~chinese 天空盒背景刷，用天空盒来清除相机背景
 */
class CC_DLL CameraBackgroundSkyBoxBrush : public CameraBackgroundBrush
{
public:
    /**@~english
     * Get brush type. Should be BrushType::SKYBOX
     * @~chinese 获取背景刷类型。应该为BrushType::SKYBOX
     * @return @~english brush type
     * @~chinese 背景刷类型
     */
    virtual BrushType getBrushType() const override { return BrushType::SKYBOX; }
    
    /** @~english Creates a Skybox brush with 6 textures.
     @param positive_x @~english texture for the right side of the texture cube face.
     @~chinese 正x方向纹理
     @param negative_x @~english texture for the up side of the texture cube face.
     @~chinese 负x方向纹理
     @param positive_y @~english texture for the top side of the texture cube face
     @~chinese 正y方向纹理
     @param negative_y @~english texture for the bottom side of the texture cube face
     @~chinese 负y方向纹理
     @param positive_z @~english texture for the forward side of the texture cube face.
     @~chinese 正z方向纹理
     @param negative_z @~english texture for the rear side of the texture cube face.
     @~chinese 负z方向纹理
     @return @~english A new brush inited with given parameters.
     @~chinese 创建的天空盒背景刷
     */
    static CameraBackgroundSkyBoxBrush* create(const std::string& positive_x, const std::string& negative_x,
                                        const std::string& positive_y, const std::string& negative_y,
                                        const std::string& positive_z, const std::string& negative_z);
    
    /** @~english Creates a Skybox brush
     * @~chinese 创建天空盒背景刷
     */
    static CameraBackgroundSkyBoxBrush* create();
    /**
     * @~english Set skybox texture
     * @~chinese 设置天空盒的纹理
     * @param texture @~english Skybox texture
     * @~chinese 天空盒纹理
     */
    void setTexture(TextureCube*  texture);
    
    /** @~english
     * Draw background
     * @~chinese 绘制背景刷
     */
    virtual void drawBackground(Camera* camera) override;

    /** @~english Get if the sky box background brush is actived.
     * @~chinese 获取天空盒背景画刷是否激活
     * @return @~english If the background brush is actived.
     * @~chinese 天空盒背景画刷是否激活
     */
    bool isActived() const;

    /** @~english Set sky box background brush is actived status.
     * @~chinese 设置天空盒背景刷激活状态
     * @param actived @~english Background brush active status to be set.
     * @~chinese 要设置的天空盒背景刷激活状态
     */
    void setActived(bool actived);

    /** @~english Set sky box background texture validate status.
     * @~chinese 设置天空盒背景刷纹理的validate状态
     @param valid Texture validate status to be set.
    */
    virtual void setTextureValid(bool valid);

    /** @~english Get if the sky box background brush is valid.
     * @~chinese 获取天空盒背景刷是否有效
     * @return @~english If the background brush is valid.
     * @~chinese 天空盒背景刷是否有效
     */
    virtual bool isValid()override;

CC_CONSTRUCTOR_ACCESS :
    CameraBackgroundSkyBoxBrush();
    virtual ~CameraBackgroundSkyBoxBrush();
    
    /**
     * init Skybox.
     */
    virtual bool init() override;
    
protected:
    void initBuffer();
    
    GLuint      _vao;
    GLuint      _vertexBuffer;
    GLuint      _indexBuffer;
    
    TextureCube*  _texture;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    EventListenerCustom* _backToForegroundListener;
#endif

private:
    bool _actived;
    bool _textureValid;
};

NS_CC_END

#endif// _CCCAMERA_BACKGROUND_BRUSH_H__
