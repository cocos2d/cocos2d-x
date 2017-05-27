
/****************************************************************************
 Copyright (c) 2016 Chukong Technologies Inc.
 
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


#ifndef __CREATOR_CCSCALE9SPRITE_H__
#define __CREATOR_CCSCALE9SPRITE_H__

#include "2d/CCNode.h"
#include "2d/CCSpriteFrame.h"
#include "renderer/CCTrianglesCommand.h"

#include <math.h>

namespace creator {

class CC_DLL SpriteV2 : public cocos2d::Node
{
public:
    enum class FillType
    {
        HORIZONTAL = 0,
        VERTICAL = 1,
        RADIAL = 2,
    };
    
    enum class RenderingType
    {
        SIMPLE = 0,
        SLICED = 1,
        TILED = 2,
        FILLED = 3,
    };
    
    enum class State
    {
        NORMAL = 0,
        GRAY = 1,
        DISTORTION = 2,
    };

public:
    SpriteV2();
    virtual ~SpriteV2();
    
    bool initWithTexture (cocos2d::Texture2D* texture) {
        return this->setTexture(texture);
    }
    
    bool initWithTexture (const std::string& textureFile) {
        return this->setTexture(textureFile);
    }
    
    bool initWithSpriteFrame (cocos2d::SpriteFrame* spriteFrame) {
        return this->setSpriteFrame(spriteFrame);
    }
    
    bool initWithSpriteFrame (const std::string& sfName) {
        return this->setSpriteFrame(sfName);
    }
    
    bool setTexture (const std::string& textureFile);
    bool setTexture (cocos2d::Texture2D* texture);
    bool setSpriteFrame(const std::string& sfName);
    bool setSpriteFrame(cocos2d::SpriteFrame* spriteFrame);
    
    void setBlendFunc(const cocos2d::BlendFunc& blendFunc);
    void setBlendFunc(GLenum src, GLenum dst);
    const cocos2d::BlendFunc& getBlendFunc() const;
    
    virtual void setContentSize(const cocos2d::Size& contentSize) override;
    
    void enableTrimmedContentSize (bool isTrimmed);
    bool isTrimmedContentSizeEnabled() const { return this->_isTrimmedContentSize; }
    
    void setState(State state);
    State getState() const { return this->_brightState; }
    
    void setRenderingType(RenderingType type);
    RenderingType getRenderingType() const { return this->_renderingType; }
    
    void setInsetLeft(float value);
    void setInsetTop(float value);
    void setInsetRight(float value);
    void setInsetBottom(float value);
    
    float getInsetLeft() const { return this->_insetLeft; }
    float getInsetTop() const { return this->_insetTop; }
    float getInsetRight() const { return this->_insetRight; }
    float getInsetBottom() const { return this->_insetBottom; }
    
    void setFillType(FillType value);
    void setFillCenter(const cocos2d::Vec2& center);
    void setFillCenter(float x, float y);
    void setFillStart(float value);
    void setFillRange(float value);
    
    FillType getFillType() const { return this->_fillType; }
    const cocos2d::Vec2& getFillCenter() const { return this->_fillCenter; }
    float getFillStart() const { return this->_fillStart; }
    float getFillRange() const { return this->_fillRange; }
    
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
public:
    //for distortion sprite
    void setDistortionOffset(const cocos2d::Vec2& v);
    void setDistortionTiling(const cocos2d::Vec2& v);
protected:
    virtual void updateColor() override;

private:
    void _rebuildQuads ();
    //resource data
    cocos2d::SpriteFrame* _spriteFrame;
    
    //scale 9 data
    float _insetLeft;
    float _insetRight;
    float _insetTop;
    float _insetBottom;
    //blend function
    cocos2d::BlendFunc _blendFunc;
    //sliced or simple
    RenderingType _renderingType;
    //bright or not
    State _brightState;
    //rendering quads
    std::vector<cocos2d::V3F_C4B_T2F_Quad> _quads;
    bool _quadsDirty;
    cocos2d::V3F_C4B_T2F_Quad _rawQuad;
    bool _isTriangle;
    bool _isTrimmedContentSize;
    //fill type
    FillType _fillType;
    //for fill radial
    cocos2d::Vec2 _fillCenter;
    //normalized filled start and range
    float _fillStart;
    float _fillRange;
    //indicate that rendercommand need to be rebuild or not;
    bool _needRebuildRenderCommand;
    
    std::vector<cocos2d::V3F_C4B_T2F> _verts;
    std::vector<unsigned short> _indices;
    cocos2d::TrianglesCommand _renderCommand;
    
    cocos2d::Vec2 _distortionOffset;
    cocos2d::Vec2 _distortionTiling;
    
};

}

#endif
