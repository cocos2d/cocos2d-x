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
#ifndef __CC_MOTION_STREAK3D_H__
#define __CC_MOTION_STREAK3D_H__

#include "base/CCProtocols.h"
#include "2d/CCNode.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class Texture2D;

/**
 * @addtogroup _3d
 * @{
 */

/** @class MotionStreak3D.
 * @brief @~english Creates a trailing path. It is created from a line segment sweeping along the path.
 * @~chinese 路径轨迹，通过一个线段扫过一条路径创建。
 */
class CC_DLL MotionStreak3D : public Node, public TextureProtocol
{
public:
    /** @~english Creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture filename.
     * @~chinese 创建并初始化一个运动轨迹，参数轨迹为消失的时间，单位秒，条纹的最小片段长度，轨迹宽度，轨迹颜色和材质贴图文件名。
     *
     * @param fade @~english The fade time, in seconds. @~chinese轨迹消失时间，单位秒
     * @param minSeg @~english The minimum segments. @~chinese 条纹的最小片段长度
     * @param stroke @~english The width of stroke. @~chinese 轨迹宽度
     * @param color @~english The color of stroke. @~chinese 轨迹颜色
     * @param path @~english The texture file name of stoke. @~chinese 轨迹贴图文件名
     * @return @~english An autoreleased MotionStreak3D object. @~chinese 创建的轨迹
     */
    static MotionStreak3D* create(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path);
    /** @~english Creates and initializes a motion streak with fade in seconds, minimum segments, stroke's width, color, texture.
     * @~chinese 创建并初始化一个运动轨迹，参数为轨迹消失时间，单位秒，条纹的最小片段长度，轨迹宽度，轨迹颜色，轨迹纹理
     * @param fade @~english The fade time, in seconds. @~chinese 轨迹消失时间，单位秒
     * @param minSeg @~english The minimum segments. @~chinese 条纹的最小片段长度
     * @param stroke @~english The width of stroke. @~chinese 轨迹宽度
     * @param color @~english The color of stroke. @~chinese 轨迹颜色
     * @param texture @~english The texture name of stoke. @~chinese 轨迹纹理
     * @return @~english An autoreleased MotionStreak3D object. @~chinese 创建的纹理
     */
    static MotionStreak3D* create(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture);

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
    virtual void setPosition3D(const Vec3& position) override;
    virtual void setRotation3D(const Vec3& rotation) override {}
    virtual void setRotationQuat(const Quaternion& quat) override {}
    
    virtual const Vec2& getPosition() const override;
    virtual void getPosition(float* x, float* y) const override;
    virtual void setPositionX(float x) override;
    virtual void setPositionY(float y) override;
    virtual float getPositionX(void) const override;
    virtual float getPositionY(void) const override;
    virtual Vec3 getPosition3D() const override;
    /** @~english override draw routine @~chinese 重写的draw函数
    * @js NA
    * @lua NA
    */
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    /** @~english update routine @~chinese 重写的update函数
    * @lua NA
    */
    virtual void update(float delta) override;
    /** @~english Get texture @~chinese 获取Texture纹理*/
    virtual Texture2D* getTexture() const override;
    /** @~english Set texture @~chinese 设置Texture纹理*/
    virtual void setTexture(Texture2D *texture) override;
    /** @~english Set blend function @~chinese 设置blend方式
    * @js NA
    * @lua NA
    */
    virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    /** @~english Get blend function @~chinese 或者Blend function
    * @js NA
    * @lua NA
    */
    virtual const BlendFunc& getBlendFunc() const override;
    virtual GLubyte getOpacity() const override;
    virtual void setOpacity(GLubyte opacity) override;
    virtual void setOpacityModifyRGB(bool value) override;
    virtual bool isOpacityModifyRGB() const override;
    
    /**
     * @~english Set the direction of sweeping line segment. @~chinese 设置扫描轴
     * @param sweepAxis @english Direction of sweeping line segment @~chinese 扫描轴方向
     */
    void setSweepAxis(const Vec3& sweepAxis) { _sweepAxis = sweepAxis.getNormalized(); }
    
    /**
     * @~english Get the direction of sweeping line segment @~chinese 获取扫描轴的方向
     */
    const Vec3& getSweepAxis() const { return _sweepAxis; }
    
CC_CONSTRUCTOR_ACCESS:
    MotionStreak3D();
    virtual ~MotionStreak3D();
    
    /** initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture filename */
    bool initWithFade(float fade, float minSeg, float stroke, const Color3B& color, const std::string& path);
    
    /** initializes a motion streak with fade in seconds, minimum segments, stroke's width, color and texture  */
    bool initWithFade(float fade, float minSeg, float stroke, const Color3B& color, Texture2D* texture);

protected:
    //renderer callback
    void onDraw(const Mat4 &transform, uint32_t flags);

    bool _startingPositionInitialized;

    /** texture used for the motion streak */
    Texture2D* _texture;
    BlendFunc _blendFunc;
    Vec3 _positionR;
    mutable Vec2 _positionR2D;
    Vec3         _sweepAxis;
    

    float _stroke;
    float _fadeDelta;
    float _minSeg;

    unsigned int _maxPoints;
    unsigned int _nuPoints;
    unsigned int _previousNuPoints;

    /** Pointers */
    Vec3* _pointVertexes;
    float* _pointState;

    // Opengl
    Vec3* _vertices;
    GLubyte* _colorPointer;
    Tex2F* _texCoords;
    
    CustomCommand _customCommand;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MotionStreak3D);
};

// end of _3d group
/// @}

NS_CC_END

#endif //__CC_MOTION_STREAK3D_H__
