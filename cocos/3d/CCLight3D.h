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
#include "3d/3dExport.h"

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

class CC_3D_DLL BaseLight3D : public Node
{
public:
    
    //get light type
    virtual LightType getLightType() = 0;
    
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
    BaseLight3D();
    virtual ~BaseLight3D();
    
protected:
    float       _intensity;
    LightFlag   _lightFlag;
    bool        _enabled;
};

class CC_3D_DLL DirectionLight3D : public BaseLight3D
{
public:
    //get light type
    virtual LightType getLightType() { return LightType::DIRECTIONAL; }
    /**
     * Creates a direction light.
     * @param direction The light's direction
     * @param color The light's color.
     *
     * @return The new direction light.
     */
    static DirectionLight3D* create(const Vec3 &direction, const Color3B &color);
    
    /**
     * Sets the Direction in parent.
     *
     * @param dir The Direction in parent.
     */
    void setDirection(const Vec3 &dir);
    
    /**
     * Returns the Direction in parent.
     */
    const Vec3& getDirection() const;
    
    /**
     * Returns direction in world.
     */
    const Vec3& getDirectionInWorld() const;
    
CC_CONSTRUCTOR_ACCESS:
    DirectionLight3D();
    virtual ~DirectionLight3D();
    
};

class CC_3D_DLL PointLight3D : public BaseLight3D
{
public:
    //get light type
    virtual LightType getLightType() { return LightType::POINT; }
    /**
     * Creates a point light.
     * @param position The light's position
     * @param color The light's color.
     * @param range The light's range.
     *
     * @return The new point light.
     */
    static PointLight3D* create(const Vec3 &position, const Color3B &color, float range);
    
CC_CONSTRUCTOR_ACCESS:
    PointLight3D();
    virtual ~PointLight3D();
};

class CC_3D_DLL SpotLight3D : public BaseLight3D
{
public:
    //get light type
    virtual LightType getLightType() { return LightType::SPOT; }
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
    static SpotLight3D* create(const Vec3 &direction, const Vec3 &position, const Color3B &color, float innerAngle, float outerAngle, float range);
    
    /**
     * Sets the Direction in parent.
     *
     * @param dir The Direction in parent.
     */
    void setDirection(const Vec3 &dir);
    
    /**
     * Returns the Direction in parent.
     */
    const Vec3& getDirection() const;
    
    /**
     * Returns direction in world.
     */
    const Vec3& getDirectionInWorld() const;
    
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
    void setOuterAngle(float angle);
    
    /**
     * Returns the outer angle of the spot light (in radians).
     */
    float getOuterAngle() const { return _outerAngle; }
    
    /** get cos outAngle */
    float getCosOuterAngle() const { return _cosInnerAngle; }
    
CC_CONSTRUCTOR_ACCESS:
    SpotLight3D();
    virtual ~SpotLight3D();
    
protected:
    float _range;
    float _innerAngle;
    float _cosInnerAngle;
    float _outerAngle;
    float _cosOuterAngle;
};

class CC_3D_DLL AmbientLight3D : public BaseLight3D
{
public:
    virtual LightType getLightType() { return LightType::AMBIENT; }
    /**
     * Creates a ambient light.
     * @param color The light's color.
     *
     * @return The new ambient light.
     */
    static AmbientLight3D* create(const Color3B &color);
    
CC_CONSTRUCTOR_ACCESS:
    AmbientLight3D() {}
    virtual ~AmbientLight3D() {}
};

class CC_3D_DLL Light3D : public Node
{
public:

    enum class LightType
    {
        DIRECTIONAL = 0,
        POINT = 1,
        SPOT = 2
    };

    /**
     * Create light according to type.
     */
    static Light3D* createDirectionalLight(const Vec3 &direction, const Color3B &color);
    static Light3D* createPointLight(const Vec3 &position, const Color3B &color, float range);
    static Light3D* createSpotLight(const Vec3 &direction, const Vec3 &position, const Color3B &color, float innerAngle, float outerAngle, float range);

    //override
    virtual void onEnter() override;
    virtual void onExit() override;

    /**
     * Gets light type.
     */
    LightType getLightType();

    /**
     * Sets Light Enabled.
     */
    void setEnabled(bool enabled);

    /**
     * Gets Light Enabled.
     */
    bool getEnabled();


    /**
     * Sets the range of point or spot light.
     *
     * @param range The range of point or spot light.
     */
    void setRange(float range);

    /**
     * Returns the range of point or spot light.
     *
     * @return The range of the point or spot light.
     */
    float getRange();

    /**
    * Sets the Direction of Directional light or Spot light.
    *
    * @param dir The Direction of the Directional light or Spot light.
    */
    void setDirection(const Vec3 &dir);

    /**
    * Returns the Direction of Directional light or Spot light.
    *
    * @return dir Direction of the Directional light or Spot light.
    */
    Vec3 getDirection() const;

   /**
    * Returns the World coordinate Direction of Directional light or Spot light.
    *
    * @return dir the World coordinate Direction of the Directional light or Spot light.
    */
    Vec3 getWorldDirection() const;

    /**
     * Sets the inner angle of a spot light (in radians).
     *
     * @param angle The angle of spot light (in radians).
     */
    void setInnerAngle(float angle);

    /**
     * Returns the inner angle the spot light (in radians).
     *
     * @return The inner angle of the spot light (in radians).
     */
    float getInnerAngle();

    /**
     * Sets the outer angle of a spot light (in radians).
     *
     * @param outerAngle The angle of spot light (in radians).
     */
    void setOuterAngle(float angle);

    /**
     * Returns the outer angle of the spot light (in radians).
     *
     * @return The outer angle of the spot light (in radians).
     */
    float getOuterAngle();

CC_CONSTRUCTOR_ACCESS:

    Light3D();
    virtual ~Light3D();

protected:

    /**
     * Sets light type.
     */
    void setLightType(LightType lightType);
    void calculateRotation(const Vec3 &direction);

protected:

    LightType _lightType;
    bool _isEnabled;
    float _range;
    float _innerAngle;
    float _outerAngle;
};

NS_CC_END

#endif