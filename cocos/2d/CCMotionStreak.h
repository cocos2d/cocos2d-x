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

#include "base/CCProtocols.h"
#include "2d/CCNode.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class Texture2D;

/**
 * @addtogroup _2d
 * @{
 */

/** @class MotionStreak.
 * @brief Creates a trailing path.
 */
class CC_DLL MotionStreak : public Node, public TextureProtocol
{
public:
    /** Creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture filename.
     *
     * @param fade The fade time, in seconds.
     * @param minSeg The minimum segments.
     * @param stroke The width of stroke.
     * @param color The color of stroke.
     * @param path The texture file name of stoke.
     * @return An autoreleased MotionStreak object.
     */
    static MotionStreak* create(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path);
    /** Creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture.
     * 
     * @param fade The fade time, in seconds.
     * @param minSeg The minimum segments.
     * @param stroke The width of stroke.
     * @param color The color of stroke.
     * @param texture The texture name of stoke.
     * @return An autoreleased MotionStreak object.
     */
    static MotionStreak* create(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture);

    /** Color used for the tint.
     *
     * @param colors The color used for the tint.
     */
    void tintWithColor(const Color3B& colors);

    /** Remove all living segments of the ribbon.
     */
    void reset();

    /** When fast mode is enabled, new points are added faster but with lower precision. 
     * 
     * @return True if fast mode is enabled.
     */
    inline bool isFastMode() const { return _fastMode; }
    /** Sets fast mode or not.
     *
     * @param bFastMode True if enabled fast mode.
     */
    inline void setFastMode(bool bFastMode) { _fastMode = bFastMode; }

    /** Is the starting position initialized or not.
     *
     * @return True if the starting position is initialized.
     */
    inline bool isStartingPositionInitialized() const { return _startingPositionInitialized; }
    /** Sets the starting position initialized or not.
     *
     * @param bStartingPositionInitialized True if initialized the starting position.
     */
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
    virtual Vec3 getPosition3D() const override;
    /**
    * @js NA
    * @lua NA
    */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    /**
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
    
    /** initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture filename */
    bool initWithFade(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path);
    
    /** initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture  */
    bool initWithFade(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture);

protected:
    //renderer callback
    void onDraw(const Mat4 &transform, uint32_t flags);

    bool _fastMode;
    bool _startingPositionInitialized;

    /** texture used for the motion streak */
    Texture2D* _texture;
    BlendFunc _blendFunc;
    Vec2 _positionR;

    float _stroke;
    float _fadeDelta;
    float _minSeg;

    unsigned int _maxPoints;
    unsigned int _nuPoints;
    unsigned int _previousNuPoints;

    /** Pointers */
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

// end of _2d group
/// @}

NS_CC_END

#endif //__CCMOTION_STREAK_H__
