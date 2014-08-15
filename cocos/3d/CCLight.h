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

class CC_DLL Light : public Node
{
public:

	enum class LightType
	{
		DIRECTIONAL,
		POINT,
		SPOT
	};

	/**
     * Create light according to type.
     */
	static Light* Create(LightType lightType);

	//override
	virtual void onEnter() override;
	virtual void onExit() override;

	/**
     * Sets light type.
     */
	void setLightType(LightType lightType);

    /**
     * Gets light type.
     */
	LightType getLightType();

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
     * Sets the Direction of Directional light.
     *
     * @param dir The Direction of the Directional light.
     */
	void setDirection(const Vec3 &dir);

    /**
     * Returns the Direction of Directional light.
     *
     * @return dir Direction of the Directional light.
     */
	const Vec3& getDirection() const;

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

	Light();
	virtual ~Light();

protected:

	LightType _lightType;
	Vec3 _dir;
	float _range;
	float _innerAngle;
	float _outerAngle;
};

NS_CC_END

#endif