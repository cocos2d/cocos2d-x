#ifndef LIGHT_H_
#define LIGHT_H_

#include "C3DVector3.h"
#include "C3DNode.h"

namespace cocos3d
{
class C3DLightComponent;

/**
 * Represents the light for a node.
 */
class  C3DLight : public C3DNode
{
    friend class C3DLightNode;
	
public:
	/**
     * Destructor.
     */
	virtual ~C3DLight();

    /**
     * Defines the supported light types.
     */
    enum Type
    {
		UNKNOWN = 0,
        DIRECTIONAL = 1,
        POINT = 2,
        SPOT = 3,
		ANIMATE = 4,
    };

	/**
     * Gets light type.
     */
    Type getLightType() const;

	/**
     * Gets node type.
     */
    C3DNode::Type getType() const { return C3DNode::NodeType_Light; }

	/**
     * Returns true if this light is enable.
     */
	bool isLightEnable() const { return _enable; }

	/**
     * Sets light enable.
     */
	void setLightEnable(bool enable) { _enable = enable; }

	/**
     * Gets C3DLightComponent.
     */
	C3DLightComponent* getComponent() const { return _component; }

	/**
     * Sets C3DLightComponent.
     */
	void setComponent(C3DLightComponent* component);

	/**
     * Creats C3DLight.
     */
	static C3DLight* create(const char* strId = "light");

	/**
     * update.
     */
	virtual void update(unsigned int deltatime);

protected:
	/**
     * Constructor.
     */
    C3DLight(const char* strId);

	C3DLightComponent* _component;
	bool _enable;
};

/**
 * 
 * describe the copmonent of light
 *
 */
class C3DLightComponent : public cocos2d::CCObject
{
	friend class C3DLight;
public:
	/**
     * Destructor.
     */
	virtual ~C3DLightComponent() {};

    /**
     * Gets the light color.
     * 
     * @return The light color.
     */
    const C3DVector3& getColor() const;

    /**
     * Sets the light color.
     * 
     * @param color The light color to set.
     */
    void setColor(const C3DVector3& color);

	/**
     * Gets the light.
     */
	C3DLight* getLight() const { return _light; }

	/**
     * update.
     */
	virtual void update(unsigned int deltatime) {};

protected:
	/**
     * Constructor.
     */
	C3DLightComponent(C3DLight::Type type);

	C3DLight* _light;
	C3DVector3 _color;
	C3DLight::Type _type;
};


/**
 *  efines structure to describe point light 
 */
class C3DPointLight : public C3DLightComponent
{
public:

    /**
     * Creates a point light.
     * 
     * @param color The light's color.
     * @param range The light's range.
     * 
     * @return The new point light.
     */
	static C3DPointLight* create(const C3DVector3& color, float range);

	/**
     * Returns the Range of the point or spot light. 
     *
     * @return The range of the point or spot light.
     */
	float getRange() const { return _range; }

    /**
     * Sets the range of point or spot light.
     *
     * @param range The range of point or spot light.
     */
    void setRange(float range);

    /**
     * Returns the inverse of the range of point or spot light.
     *
     * @return The range of the point or spot light.
     */
    float getRangeInverse() const { return _rangeInverse; }

protected:
	/**
     * Constructor.
     */
	C3DPointLight();

	float _range;
	float _rangeInverse;

};


/**
 *  efines structure to describe directional light 
 */
class C3DDirectionalLight : public C3DLightComponent
{
public:

	/**
     * Creates a directional light.
     * 
     * @param color The light's color.
     * 
     * @return The new directional light.
     */
	static C3DDirectionalLight* create(const C3DVector3& color);

protected:
	/**
     * Constructor.
     */
	C3DDirectionalLight();

};

/**
 *  efines structure to describe spot light 
 */
class C3DSpotLight : public C3DLightComponent
{
public:

	/**
     * Creates a spot light.
     * 
     * @param color The light's color.
     * @param range The light's range.
     * @param innerAngle The light's inner angle (in radians).
     * @param outerAngle The light's outer angle (in radians).
     * 
     * @return The new spot light.
     */
    static C3DSpotLight* create(const C3DVector3& color, float range, float innerAngle, float outerAngle);

	    /**
     * Returns the Range of the point or spot light. 
     *
     * @return The range of the point or spot light.
     */
	float getRange() const { return _range; }

    /**
     * Sets the range of point or spot light.
     *
     * @param range The range of point or spot light.
     */
    void setRange(float range);

    /**
     * Returns the inverse of the range of point or spot light.
     *
     * @return The range of the point or spot light.
     */
    float getRangeInverse() const { return _rangeInverse; }

    /**
     * Returns the inner angle the spot light (in radians).
     *
     * @return The inner angle of the spot light (in radians).
     */
    float getInnerAngle() const { return _innerAngle; }

    /**
     * Sets the inner angle of a spot light (in radians).
     *
     * @param innerAngle The angle of spot light (in radians).
     */
    void setInnerAngle(float innerAngle);

    /**
     * Returns the outer angle of the spot light (in radians).
     *
     * @return The outer angle of the spot light (in radians).
     */
    float getOuterAngle() const { return _outerAngle; }

    /**
     * Sets the outer angle of a spot light (in radians).
     *
     * @param outerAngle The angle of spot light (in radians).
     */
    void setOuterAngle(float outerAngle);

    /**
     * Returns the cosine of the inner angle of spot light.
     *
     * @return The cosine of the inner angle of spot light.
     */
    float getInnerAngleCos() const { return _innerAngleCos; }

    /**
     * Returns the cosine of the outer angle of spot light.
     *
     * @return The cosine of the outer angle of spot light.
     */
    float getOuterAngleCos() const { return _outerAngleCos; }

protected:
	/**
     * Constructor.
     */
	C3DSpotLight();
	
	float _range;
	float _rangeInverse;
	float _innerAngle;
	float _innerAngleCos;
	float _outerAngle;
	float _outerAngleCos;
};

}

#endif
