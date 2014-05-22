/****************************************************************************
Copyright (c) 2011      ForzeField Studios S.L.
Copyright (c) 2010-2012 cocos2d-x.org
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
#ifndef __CCMOTION_STREAK_H__
#define __CCMOTION_STREAK_H__

#include "2d/CCProtocols.h"
#include "2d/CCTexture2D.h"
#include "base/ccTypes.h"
#include "2d/CCNode.h"
#include "renderer/CCCustomCommand.h"
#ifdef EMSCRIPTEN
#include "CCGLBufferedNode.h"
#endif // EMSCRIPTEN

NS_CC_BEGIN

/**
 * @addtogroup misc_nodes
 * @{
 */

/** MotionStreak.h
 创建一个精灵尾巴的路径
 */
class CC_DLL MotionStreak : public Node, public TextureProtocol
#ifdef EMSCRIPTEN
, public GLBufferedNode
#endif // EMSCRIPTEN
{
public:
    /** 创建并且初始化一个拖动渐隐效果包含参数fade:渐隐时间（以秒为单位），minSeg:最小的片段（渐隐片段的大小）, stroke:渐隐条带的宽度，color：顶点颜色值, path:纹理文件名 */
    static MotionStreak* create(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path);
    /** 创建并且初始化一个拖动渐隐效果包含参数fade:渐隐时间（以秒为单位），minSeg:最小的片段（渐隐片段的大小）, stroke:渐隐条带的宽度，color：顶点颜色值, texture:纹理对象指针 */
    static MotionStreak* create(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture);

    /** 色彩使用的颜色 */
    void tintWithColor(const Color3B& colors);

    /** 删除所有活动的条带段 */
    void reset();

    /** 当是快速模式时,新的顶点被更快速的加入，但是新的顶点具有更小的精确值 */
    inline bool isFastMode() const { return _fastMode; }
    inline void setFastMode(bool bFastMode) { _fastMode = bFastMode; }

    inline bool isStartingPositionInitialized() const { return _startingPositionInitialized; }
    inline void setStartingPositionInitialized(bool bStartingPositionInitialized) 
    {
        _startingPositionInitialized = bStartingPositionInitialized; 
    }

    // Overrides
    virtual void setPosition(const Vec2& position) override;
    virtual void setPosition(float x, float y) override;
    virtual const Vec2& getPosition() const override;
    virtual void getPosition(float* x, float* y) const override;
    virtual void setPositionX(float x) override;
    virtual void setPositionY(float y) override;
    virtual float getPositionX(void) const override;
    virtual float getPositionY(void) const override;
    /**
    * @js NA
    * @lua NA
    */
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
    /**
    * @js NA
    * @lua NA
    */
    virtual void update(float delta) override;
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D *texture) override;
    /**
    * @js NA
    * @lua NA
    */
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    /**
    * @js NA
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc() const override;
    virtual GLubyte getOpacity() const override;
    virtual void setOpacity(GLubyte opacity) override;
    virtual void setOpacityModifyRGB(bool value) override;
    virtual bool isOpacityModifyRGB() const override;
    
CC_CONSTRUCTOR_ACCESS:
    MotionStreak();
    virtual ~MotionStreak();
    
    /** 创建并且初始化一个拖动渐隐效果包含参数fade:渐隐时间（以秒为单位），minSeg:最小的片段（渐隐片段的大小）, stroke:渐隐条带的宽度，color：顶点颜色值, path:纹理文件名 */
    bool initWithFade(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path);
    
    /** 创建并且初始化一个拖动渐隐效果包含参数fade:渐隐时间（以秒为单位），minSeg:最小的片段（渐隐片段的大小）, stroke:渐隐条带的宽度，color：顶点颜色值, texture:纹理对象指针  */
    bool initWithFade(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture);

protected:
    //渲染器回调
    void onDraw(const Mat4 &transform, bool transformUpdated);

    bool _fastMode;
    bool _startingPositionInitialized;

    /** 拖尾渐隐效果使用的纹理 */
    Texture2D* _texture;
    BlendFunc _blendFunc;
    Vec2 _positionR;

    float _stroke;
    float _fadeDelta;
    float _minSeg;

    unsigned int _maxPoints;
    unsigned int _nuPoints;
    unsigned int _previousNuPoints;

    /** 指针 */
    Vec2* _pointVertexes;
    float* _pointState;

    // Opengl
    Vec2* _vertices;
    GLubyte* _colorPointer;
    Tex2F* _texCoords;
    
    CustomCommand _customCommand;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MotionStreak);
};

// end of misc_nodes group
/// @}

NS_CC_END

#endif //__CCMOTION_STREAK_H__
