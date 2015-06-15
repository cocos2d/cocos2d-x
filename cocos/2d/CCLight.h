/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCLIGHT_H__
#define __CCLIGHT_H__

#include "2d/CCNode.h"

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

enum class LightType
{
    DIRECTIONAL = 0,
    POINT = 1,
    SPOT = 2,
    AMBIENT = 3,
};

enum class LightFlag
{
    LIGHT0 = 1,
    LIGHT1 = 1 << 1,
    LIGHT2 = 1 << 2,
    LIGHT3 = 1 << 3,
    LIGHT4 = 1 << 4,
    LIGHT5 = 1 << 5,
    LIGHT6 = 1 << 6,
    LIGHT7 = 1 << 7,
    LIGHT8 = 1 << 8,
    LIGHT9 = 1 << 9,
    LIGHT10 = 1 << 10,
    LIGHT11 = 1 << 11,
    LIGHT12 = 1 << 12,
    LIGHT13 = 1 << 13,
    LIGHT14 = 1 << 14,
    LIGHT15 = 1 << 15,
};

/** @class BaseLight
 * @brief @~english BaseLight is the parent of all the lights. cocos2d-x supports 4 types of lights, directional light, point light, spot light and ambient light. Each light has an light flag, objects whose light mask & (1<<lightFlag) is not zero will be lighted by this light.
 * @~chinese BaseLight 是所有灯光的基类，cocos2d-x支持4种灯光，方向光、点光源、聚光灯和环境光。每个灯光都有一个灯光标记lightflag, 只有当物体的灯光掩码lightmask与(1<<lightFlag)做与运算不为0的时候这个物体才会被该灯光照亮。
@js NA
*/
class CC_DLL BaseLight : public Node
{
public:
    
    /**
     * @~english Get the light type,light type MUST be one of LightType::DIRECTIONAL ,
     * LightType::POINT, LightType::SPOT, LightType::AMBIENT.
     * @~chinese 获取灯光的类型，灯光类型为LightType::DIRECTIONAL、LightType::POINT、LightType::SPOT、LightType::AMBIENT之一。
     * @return @~english light type. @~chinese 灯光类型
     */
    virtual LightType getLightType() const = 0;
    
    /** 
     * @~english Get light intensity
     * @~chinese 获取灯光强度
     * @return @~english light intensity. @~chinese 灯光强度
     */
    float getIntensity() const { return _intensity; }
    
    /**
     * @~english Set light intensity
     * @~chinese 设置灯光强度
     * @param intensity @~english intensity of light. @~chinese 灯光强度
     */
    void setIntensity(float intensity);
    
    /**
     * @~english Get light flag.
     * @~chinese 获取灯光标记
     * @return @~english light flag. @~chinese 灯光标记
     */
    LightFlag getLightFlag() const { return _lightFlag; }
    
    /**
     * @~english Set light flag. Objects whose light mask & (1<<lightFlag) is not zero will be lighted by this light.
     * @~chinese 设置灯光标记。只有当物体的灯光掩码lightmask与(1<<lightFlag)做与运算不为0的时候这个物体才会被该灯光照亮。
     * @param flag @~english light flag. @~chinese 灯光标记
     */
    void setLightFlag(LightFlag flag) { _lightFlag = flag; }
    
    /**
     * @~english Set light enabled or disabled.
     * @~chinese 设置灯光的开关
     * @param enabled @~english true means enabled, false make the light disabled
     * @~chinese true为开启灯光，false使该灯光失效
     */
    void setEnabled(bool enabled) { _enabled = enabled; }
    
    /**
     * @~english is the light enabled or not.
     * @~chinese 灯光是否开启
     * @return @~english is the light enabled
     * @~chinese 灯光是否开启
     */
    bool isEnabled() const { return _enabled; }
    
    //override
    virtual void onEnter() override;
    virtual void onExit() override;
    
CC_CONSTRUCTOR_ACCESS:
    BaseLight();
    virtual ~BaseLight();
    
protected:
    void setRotationFromDirection( const Vec3 &direction );
    
protected:
    float       _intensity;
    LightFlag   _lightFlag;
    bool        _enabled;
};

/** @class DirectionLight
 * @brief @~english DirectionLight simulates light that is being emitted from a source that is infinitely far away. This means that all shadows cast by this light will be parallel. The sunlight is typical directional light.
 * @~chinese 方向光模拟无限远的灯光，它意味着这种灯光投射的影子是平行的，太阳光是个典型的方向光。
 @js NA
 */
class CC_DLL DirectionLight : public BaseLight
{
public:
    /**
     * @~english Creates a direction light. The DirectionLight inherits from Node indirectly. The Node also contains a local space. The direction of directional light is the -z of local space.
     * @~chinese 创建一个方向光。方向光间接从Node继承，Node中包含局部坐标，而方向光的方向就是灯光的局部坐标系的-z方向。
     * @param direction @~english The light's direction. @~chinese 灯光的方向
     * @param color @~english The light's color. @~chinese 灯光颜色
     * @return @~english Created directional light. @~chinese 新创建的方向灯光
     */
    static DirectionLight* create(const Vec3 &direction, const Color3B &color);
    
    /**
     * @~english get light type
     * @~chinese 获取灯光类型
     * @return @~english light type. @~chinese 灯光类型
     */
    virtual LightType getLightType() const override { return LightType::DIRECTIONAL; }
    
    /**
     * @~english Sets the Direction of light in parent space.
     * @~chinese 设置方向光在父空间的方向
     * @param dir @~english The Direction in parent. @~chinese 设置方向光在父空间的方向
     */
    void setDirection(const Vec3 &dir);
    
    /**
     * @~english Gets the direction of light in parent space
     * @~chinese 获取方向光在父空间的方向
     * @return @~english Direction in parent. @~chinese 方向光在父空间的方向
     */
    Vec3 getDirection() const;
    
    /**
     * @~english Gets light's direction in word
     * @~chinese 获取方向光在世界空间的方向
     */
    Vec3 getDirectionInWorld() const;
    
CC_CONSTRUCTOR_ACCESS:
    DirectionLight();
    virtual ~DirectionLight();
    
};

/** @class PointLight
 * @brief @~english Point light has a position, and sends rays in all directions.
 * @~chinese 点光源类型的灯光有一个位置，并且向四周发射光线。
 @js NA
 */
class CC_DLL PointLight : public BaseLight
{
public:
    /**
     * @~english Creates a point light.
     * @~chinese 创建一个点光源类型的灯光
     * @param position @~english The light's position. @~chinese 灯光的位置
     * @param color @~english The light's color. @~chinese 灯光的颜色
     * @param range @~english The light's range. @~chinese 灯光的范围
     *
     * @return @~english The new point light. @~chinese 新创建的灯光
     */
    static PointLight* create(const Vec3 &position, const Color3B &color, float range);
    
    /**
     * @~english get light type
     * @~chinese 获取灯光类型
     * @return @~english light type. @~chinese 灯光类型
     */
    virtual LightType getLightType() const override { return LightType::POINT; }
    
    /** 
     * @~english get light range
     * @~chinese 获取灯光的范围
     * @return @~english light' range. @~chinese 灯光的范围
     */
    float getRange() const { return _range; }
    /**
     * @~english get light range
     * @~chinese 获取灯光的范围
     * @return @~english light' range. @~chinese 灯光的范围
     */
    void setRange(float range) { _range = range; }
    
CC_CONSTRUCTOR_ACCESS:
    PointLight();
    virtual ~PointLight();
    
protected:
    float _range;
};

/** @class SpotLight
 * @brief @~english Spot light is a special light that all light rays are restricted to a cone of light. The lights on the stage are ofen this type.
 * @~chinese 聚光灯是一种特殊类型的灯光，所有光线都约束在一个光锥内，舞台上的聚光灯一般是这种类型。
 @js NA
 */
class CC_DLL SpotLight : public BaseLight
{
public:
    /**
     * @~english Creates a spot light.
     * @~chinese 创建一个聚光灯
     * @param direction @~english The light's direction. @~chinese 聚光灯方向
     * @param position @~english The light's position. @~chinese 聚光灯的位置
     * @param color @~english The light's color. @~chinese 聚光灯的颜色
     * @param innerAngle @~english The light's inner angle (in radians). @~chinese 聚光灯的内角（单位弧度）
     * @param outerAngle @~english The light's outer angle (in radians). @~chinese 聚光灯外角（单位弧度）
     * @param range @~english The light's range. @~chinese 聚光灯范围
     *
     * @return @~english The new spot light. @~chinese 新创建的灯光
     */
    static SpotLight* create(const Vec3 &direction, const Vec3 &position, const Color3B &color, float innerAngle, float outerAngle, float range);
    
    /**
     * @~english get light type
     * @~chinese 获取灯光类型
     * @return @~english light type. @~chinese 灯光类型
     */
    virtual LightType getLightType() const override { return LightType::SPOT; }
    
    /**
     * @~english Sets the light direction in parent, the direction is local transform's -z axis. @~chinese 设置灯光在父空间的方向，灯光的方向为局部坐标系的-z轴
     *
     * @param dir @~english The Direction in parent. @~chinese 灯光在父空间的方向，
     */
    void setDirection(const Vec3 &dir);
    
    /**
     * @~english Gets the light direction in parent space. Light direction is the -z axis of local transform.
     * @~chinese 获取灯光在父空间的方向。灯光方向是局部空间的-z轴朝向
     * @return @~english light direction in parent space. @~chinese 灯光在父空间的方向
     */
    Vec3 getDirection() const;
    
    /**
     * @~english Gets direction in world, light direction is -z axis in local space.
     * @~chinese 获取时间坐标系下灯光的朝向，灯光方向是局部坐标系下的-z朝向。
     * @return @~english light direction in world space. @~chinese 灯光在世界坐标系的方向。
     */
    Vec3 getDirectionInWorld() const;
    
    /**
     * @~english Sets the range of point or spot light.
     * @~chinese 设置灯光的范围
     *
     * @param range @~english The range of point or spot light. @~chinese 点光源或者聚光灯的范围。
     */
    void setRange(float range) { _range = range; }
    
    /**
     * @~english Gets the range of point or spot light.
     * @~chinese 获取灯光的范围
     * @return @~english The range of the point or spot light. @~chinese 点光源或者聚光灯的范围。
     */
    float getRange() const { return _range; }
    /**
     * @~english Sets the inner angle of a spot light (in radians).
     * @~chinese 设置聚光灯的内角（单位弧度）。
     * @param angle @english The inner angle of spot light (in radians). @chinese 聚光灯的内角。
     */
    void setInnerAngle(float angle);
    
    /**
     * @~english Gets the inner angle of spot light (in radians). 
     * @~chinese 获取聚光灯的内角（单位弧度）。
     * @return @~english inner angle of spot light. @~chinese 聚光灯的内角。
     */
    float getInnerAngle() const { return _innerAngle; }
    
    /** 
     * @~english Gets cos of innerAngle.
     * @~chinese 获取内角的cos值。
     * @return @~english cos of inner angle. @~chinese 内角的cos值。
     */
    float getCosInnerAngle() const { return _cosInnerAngle; }
    
    /**
     * @~english Sets the outer angle of a spot light (in radians).
     * @~chinese 设置聚光灯的外角（单位弧度）。
     * @param outerAngle @~english The angle of spot light (in radians). @~chinese 聚光灯的外角（单位弧度）。
     */
    void setOuterAngle(float angle);
    
    /**
     * @~english Gets the outter angle of the spot light (in radians).
     * @~chinese 获取聚光灯的外角（单位弧度）。
     * @return @~english outter angle of spot light. @~chinese 聚光灯的外角。
     */
    float getOuterAngle() const { return _outerAngle; }
    
   /**
    * @~english Gets cos of outter angle.
    * @~chinese 获取外角的cos值。
    * @return @~english cos of outter angle. @~chinese 外角的cos值。
    */
    float getCosOuterAngle() const { return _cosOuterAngle; }
    
CC_CONSTRUCTOR_ACCESS:
    SpotLight();
    virtual ~SpotLight();
    
protected:
    float _range;
    float _innerAngle;
    float _cosInnerAngle;
    float _outerAngle;
    float _cosOuterAngle;
};

/** @class AmbientLight
 * @brief @~english Ambient light simulates the light in the enviorment, it emits to all direction with the same intensity.
 * @~chinese 环境灯光用来模拟环境中的光照，它向四周均匀发射。
 @js NA
 */
class CC_DLL AmbientLight : public BaseLight
{
public:
    /**
     * @~english Creates a ambient light.
     * @~chinese 创建环境光
     * @param color @~english The light's color. @~chinese 灯光颜色
     *
     * @return @~english The new ambient light. @~chinese 创建的环境灯光
     */
    static AmbientLight* create(const Color3B &color);
    
    /**
     * @~english get light type
     * @~chinese 获取灯光类型
     * @return @~english light type. @~chinese 灯光类型
     */
    virtual LightType getLightType() const override { return LightType::AMBIENT; }
    
CC_CONSTRUCTOR_ACCESS:
    AmbientLight();
    virtual ~AmbientLight();
};

// end of _2d group
/// @}

NS_CC_END

#endif