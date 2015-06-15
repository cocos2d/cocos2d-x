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
 * @brief @~english Creates a trailing path.
 * @~chinese 运动条纹，用于游戏对象的运动轨迹上实现拖尾渐隐效果。
 */
class CC_DLL MotionStreak : public Node, public TextureProtocol
{
public:
    /** @~english Creates and initializes a motion streak.
     *
     * @~chinese 创建并初始化一个运动条纹。
     * 
     * @param fade @~english The fade time, in seconds.
     * @~chinese 条纹片段的渐隐时间,以秒为单位。
     * @param minSeg @~english The minimum segments.
     * @~chinese 条纹的最小片段长度。
     * @param stroke @~english The width of streak.
     * @~chinese 条纹的宽度。
     * @param color @~english The color of streak.
     * @~chinese 条纹的效果颜色。
     * @param path @~english The texture file path of streak.
     * @~chinese 条纹的纹理文件路径。
     *
     * @return @~english A initialized MotionStreak node which is marked as "autorelease".
     * @~chinese 一个初始化的MotionStreak节点，该节点会自动被标记为“autorelease”(自动释放)。
     */
    static MotionStreak* create(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path);
    
    /** @~english Creates and initializes a motion streak.
     * 
     * @~chinese 创建并初始化一个运动条纹。
     * 
     * @param fade @~english The fade time, in seconds.
     * @~chinese 条纹片段的渐隐时间,以秒为单位。
     * @param minSeg @~english The minimum segments.
     * @~chinese 条纹的最小片段长度。
     * @param stroke @~english The width of streak.
     * @~chinese 条纹的宽度。
     * @param color @~english The color of streak.
     * @~chinese 条纹的效果颜色。
     * @param texture @~english The texture name of streak.
     * @~chinese 条纹的纹理指针。
     *
     * @return @~english A initialized MotionStreak node which is marked as "autorelease".
     * @~chinese 一个初始化的MotionStreak节点，该节点会自动被标记为“autorelease”(自动释放)。
     */
    static MotionStreak* create(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture);

    /** @~english Color used for the tint.
     *
     * @~chinese 设定条纹的效果颜色。
     * 
     * @param colors @~english The color used for the tint.
     * @~chinese 效果颜色。
     */
    void tintWithColor(const Color3B& colors);

    /** @~english Remove all living segments of the ribbon.
     * @~chinese 删除当前所有的条纹片段。
     */
    void reset();

    /** @~english When fast mode is enabled, new points are added faster but with lower precision. 
     * 
     * @~chinese 获取当前是否启用了快速模式。
     * 
     * @return @~english True if fast mode is enabled.
     * @~chinese 如果启用了快速模式，返回true；否则返回false。
     */
    inline bool isFastMode() const { return _fastMode; }

    /** @~english Sets fast mode or not.
     *
     * @~chinese 设置是否启用快速模式。
     * 当启用快速模式,新的点会被更快地添加，但精度较低。
     * 
     * @param bFastMode @~english True if enabled fast mode.
     * @~chinese true 启用快速模式，false 关闭快速模式。
     */
    inline void setFastMode(bool bFastMode) { _fastMode = bFastMode; }

    /** @~english Get stroke.
     *
     * @~chinese 获取条纹片段的宽度。
     * 
     * @return @~english float stroke.
     * @~chinese 返回条纹片段宽度值。
     */
    inline float getStroke() const { return _stroke; }

    /** @~english Set stroke.
     *
     * @~chinese 设定条纹片段的宽度。
     * 
     * @param stroke @~english The width of stroke.
     * @~chinese 新的条纹片段宽度值。
     */
    inline void setStroke(float stroke) { _stroke = stroke; }

    /** @~english Is the starting position initialized or not.
     *
     * @~chinese 获取起始状态[即未开始移动]是否会添加条纹片段。
     * 
     * @return @~english True if the starting position is initialized.
     * @~chinese 如果起始状态会添加条纹片段返回true，否则返回false。
     */
    inline bool isStartingPositionInitialized() const { return _startingPositionInitialized; }
    
    /** @~english Sets the starting position initialized or not.
     *
     * @~chinese 设置起始状态是否添加条纹片段，默认不添加。
     * 
     * @param bStartingPositionInitialized @~english True if initialized the starting position.
     * @~chinese true，起始状态会添加条纹片段；false，起始状态不添加条纹片段。
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
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    virtual void update(float delta) override;
    virtual Texture2D* getTexture() const override;
    virtual void setTexture(Texture2D *texture) override;

    virtual void setBlendFunc(const BlendFunc &blendFunc) override;    
    virtual const BlendFunc& getBlendFunc() const override;
    virtual GLubyte getOpacity() const override;
    virtual void setOpacity(GLubyte opacity) override;
    virtual void setOpacityModifyRGB(bool value) override;
    virtual bool isOpacityModifyRGB() const override;
    
CC_CONSTRUCTOR_ACCESS:
    MotionStreak();
    virtual ~MotionStreak();
    
    bool initWithFade(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path);
    
    bool initWithFade(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture);

protected:
    void onDraw(const Mat4 &transform, uint32_t flags);

    bool _fastMode;
    bool _startingPositionInitialized;

    Texture2D* _texture;
    BlendFunc _blendFunc;
    Vec2 _positionR;

    float _stroke;
    float _fadeDelta;
    float _minSeg;

    unsigned int _maxPoints;
    unsigned int _nuPoints;
    unsigned int _previousNuPoints;

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
