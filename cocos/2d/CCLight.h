/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

/**
@js NA
*/
class CC_DLL BaseLight : public Node
{
public:
    
    /**
     * Get the light type,light type MUST be one of LightType::DIRECTIONAL ,
     * LightType::POINT, LightType::SPOT, LightType::AMBIENT.
     */
    virtual LightType getLightType() const = 0;
    
    /** intensity getter and setter */
    float getIntensity() const { return _intensity; }
    void setIntensity(float intensity);
    
    /**light flag getter and setter*/
    LightFlag getLightFlag() const { return _lightFlag; }
    void setLightFlag(LightFlag flag) { _lightFlag = flag; }
    
    /**
     * light enabled getter and setter.
     */
    void setEnabled(bool enabled) { _enabled = enabled; }
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

/**
@js NA
*/
class CC_DLL DirectionLight : public BaseLight
{
public:
    /**
     * Creates a direction light.
     * @param direction The light's direction
     * @param color The light's color.
     *
     * @return The new direction light.
     */
    static DirectionLight* create(const Vec3 &direction, const Color3B &color);
    
    //get light type
    virtual LightType getLightType() const override { return LightType::DIRECTIONAL; }
    
    /**
     * Sets the Direction in parent.
     *
     * @param dir The Direction in parent.
     */
    void setDirection(const Vec3 &dir);
    
    /**
     * Returns the Direction in parent.
     */
    Vec3 getDirection() const;
    
    /**
     * Returns direction in world.
     */
    Vec3 getDirectionInWorld() const;
    
CC_CONSTRUCTOR_ACCESS:
    DirectionLight();
    virtual ~DirectionLight();
    
};

/**
@js NA
*/
class CC_DLL PointLight : public BaseLight
{
public:
    /**
     * Creates a point light.
     * @param position The light's position
     * @param color The light's color.
     * @param range The light's range.
     *
     * @return The new point light.
     */
    static PointLight* create(const Vec3 &position, const Color3B &color, float range);
    
    //get light type
    virtual LightType getLightType() const override { return LightType::POINT; }
    
    /** get or set range */
    float getRange() const { return _range; }
    void setRange(float range) { _range = range; }
    
CC_CONSTRUCTOR_ACCESS:
    PointLight();
    virtual ~PointLight();
    
protected:
    float _range;
};

/**
@js NA
*/
class CC_DLL SpotLight : public BaseLight
{
public:
    /**
     * Creates a spot light.
     * @param direction The light's direction
     * @param position The light's position
     * @param color The light's color.
     * @param innerAngle The light's inner angle (in radians).
     * @param outerAngle The light's outer angle (in radians).
     * @param range The light's range.
     *
     * @return The new spot light.
     */
    static SpotLight* create(const Vec3 &direction, const Vec3 &position, const Color3B &color, float innerAngle, float outerAngle, float range);
    
    //get light type
    virtual LightType getLightType() const override { return LightType::SPOT; }
    
    /**
     * Sets the Direction in parent.
     *
     * @param dir The Direction in parent.
     */
    void setDirection(const Vec3 &dir);
    
    /**
     * Returns the Direction in parent.
     */
    Vec3 getDirection() const;
    
    /**
     * Returns direction in world.
     */
    Vec3 getDirectionInWorld() const;
    
    /**
     * Sets the range of point or spot light.
     *
     * @param range The range of point or spot light.
     */
    void setRange(float range) { _range = range; }
    
    /**
     * Returns the range of point or spot light.
     *
     * @return The range of the point or spot light.
     */
    float getRange() const { return _range; }
    /**
     * Sets the inner angle of a spot light (in radians).
     *
     * @param angle The angle of spot light (in radians).
     */
    void setInnerAngle(float angle);
    
    /**
     * Returns the inner angle the spot light (in radians).
     */
    float getInnerAngle() const { return _innerAngle; }
    
    /** get cos innerAngle */
    float getCosInnerAngle() const { return _cosInnerAngle; }
    
    /**
     * Sets the outer angle of a spot light (in radians).
     *
     * @param outerAngle The angle of spot light (in radians).
     */
    void setOuterAngle(float outerAngle);
    
    /**
     * Returns the outer angle of the spot light (in radians).
     */
    float getOuterAngle() const { return _outerAngle; }
    
    /** get cos outAngle */
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

/**
@js NA
*/
class CC_DLL AmbientLight : public BaseLight
{
public:
    /**
     * Creates a ambient light.
     * @param color The light's color.
     *
     * @return The new ambient light.
     */
    static AmbientLight* create(const Color3B &color);
    
    //get light type
    virtual LightType getLightType() const override { return LightType::AMBIENT; }
    
CC_CONSTRUCTOR_ACCESS:
    AmbientLight();
    virtual ~AmbientLight();
};

NS_CC_END

#endif