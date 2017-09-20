/****************************************************************************
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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
 * Defines a brush to clear the background of camera.
 * There are 4 types of brush. None brush do nothing, Depth brush clear background with given depth, Color brush clear background with given color and depth, Skybox brush clear the background with a skybox. Camera uses depth brush by default.
 */
class CC_DLL CameraBackgroundBrush : public Ref
{
public:
    /**
     * Brush types. There are 4 types of brush. See CameraBackgroundDepthBrush, CameraBackgroundColorBrush, CameraBackgroundSkyBoxBrush for more information.
     */
    enum class BrushType
    {
        NONE, //none brush
        DEPTH, // depth brush. See CameraBackgroundDepthBrush
        COLOR, // color brush. See CameraBackgroundColorBrush
        SKYBOX, // skybox brush. See CameraBackgroundSkyBoxBrush
    };
    
    /**
     * get brush type
     * @return BrushType
     */
    virtual BrushType getBrushType() const { return BrushType::NONE; }
    
    /**
     * Creates a none brush, it does nothing when clear the background
     * @return Created brush.
     */
    static CameraBackgroundBrush* createNoneBrush();
    
    /**
     * Creates a depth brush, which clears depth buffer with a given depth.
     * @param depth Depth used to clear depth buffer
     * @return Created brush
     */
    static CameraBackgroundDepthBrush* createDepthBrush(float depth = 1.f);
    
    /**
     * Creates a color brush
     * @param color Color of brush
     * @param depth Depth used to clear depth buffer
     * @return Created brush
     */
    static CameraBackgroundColorBrush* createColorBrush(const Color4F& color, float depth);
    
    
    /** Creates a Skybox brush with 6 textures.
     @param positive_x texture for the right side of the texture cube face.
     @param negative_x texture for the up side of the texture cube face.
     @param positive_y texture for the top side of the texture cube face
     @param negative_y texture for the bottom side of the texture cube face
     @param positive_z texture for the forward side of the texture cube face.
     @param negative_z texture for the rear side of the texture cube face.
     @return  A new brush inited with given parameters.
     */
    static CameraBackgroundSkyBoxBrush* createSkyboxBrush(const std::string& positive_x, const std::string& negative_x,
                                                          const std::string& positive_y, const std::string& negative_y,
                                                          const std::string& positive_z, const std::string& negative_z);
    /**
     * draw the background
     */
    virtual void drawBackground(Camera* /*camera*/) {}

    virtual bool isValid() { return true; }

CC_CONSTRUCTOR_ACCESS :
    CameraBackgroundBrush();
    virtual ~CameraBackgroundBrush();

    virtual bool init() { return true; }
    
protected:
    GLProgramState* _glProgramState;
};

/**
 * Depth brush clear depth buffer with given depth
 */
class CC_DLL CameraBackgroundDepthBrush : public CameraBackgroundBrush
{
public:
    /**
     * Create a depth brush
     * @param depth Depth used to clear the depth buffer
     * @return Created brush
     */
    static CameraBackgroundDepthBrush* create(float depth);
    
    /**
     * Get brush type. Should be BrushType::DEPTH
     * @return brush type
     */
    virtual BrushType getBrushType() const override { return BrushType::DEPTH; }
    
    /**
     * Draw background
     */
    virtual void drawBackground(Camera* camera) override;
    
    /**
     * Set depth
     * @param depth Depth used to clear depth buffer
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
    GLuint      _vao;
    GLuint      _vertexBuffer;
    GLuint      _indexBuffer;
};

/**
 * Color brush clear buffer with given depth and color
 */
class CC_DLL CameraBackgroundColorBrush : public CameraBackgroundDepthBrush
{
public:
    /**
     * Get brush type. Should be BrushType::COLOR
     * @return brush type
     */
    virtual BrushType getBrushType() const override { return BrushType::COLOR; }
    
    /**
     * Create a color brush
     * @param color Color used to clear the color buffer
     * @param depth Depth used to clear the depth buffer
     * @return Created brush
     */
    static CameraBackgroundColorBrush* create(const Color4F& color, float depth);
    
    /**
     * Set clear color
     * @param color Color used to clear the color buffer
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

/**
 * Skybox brush clear buffer with a skybox
 */
class CC_DLL CameraBackgroundSkyBoxBrush : public CameraBackgroundBrush
{
public:
    /**
     * Get brush type. Should be BrushType::SKYBOX
     * @return brush type
     */
    virtual BrushType getBrushType() const override { return BrushType::SKYBOX; }
    
    /** Creates a Skybox brush with 6 textures.
     @param positive_x texture for the right side of the texture cube face.
     @param negative_x texture for the up side of the texture cube face.
     @param positive_y texture for the top side of the texture cube face
     @param negative_y texture for the bottom side of the texture cube face
     @param positive_z texture for the forward side of the texture cube face.
     @param negative_z texture for the rear side of the texture cube face.
     @return  A new brush inited with given parameters.
     */
    static CameraBackgroundSkyBoxBrush* create(const std::string& positive_x, const std::string& negative_x,
                                        const std::string& positive_y, const std::string& negative_y,
                                        const std::string& positive_z, const std::string& negative_z);
    
    /** Creates a Skybox brush with 6 textures.
     */
    static CameraBackgroundSkyBoxBrush* create();
    /**
     * Set skybox texture 
     * @param texture Skybox texture
     */
    void setTexture(TextureCube*  texture);
    
    /**
     * Draw background
     */
    virtual void drawBackground(Camera* camera) override;

    bool isActived() const;
    void setActived(bool actived);
    virtual void setTextureValid(bool valid);
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
