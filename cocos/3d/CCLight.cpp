#include "CCLight.h"
#include "2d/CCScene.h"

NS_CC_BEGIN

Light3D::Light3D()
:  _range(0.0f)
, _innerAngle(0.0f)
, _outerAngle(0.0f)
{
}


Light3D::~Light3D()
{
}

void Light3D::setLightType( LightType lightType )
{
	_lightType = lightType;
}


Light3D::LightType Light3D::getLightType()
{
	return _lightType;
}

void Light3D::setRange( float range )
{
    _range = range;
}

float Light3D::getRange()
{
    return _range;
}

void Light3D::setDirection( const Vec3 &dir )
{
    _dir = dir;
}

const Vec3& Light3D::getDirection() const
{
    return _dir;
}

void Light3D::setInnerAngle( float angle )
{
    _innerAngle = angle;
}

float Light3D::getInnerAngle()
{
    return _innerAngle;
}

void Light3D::setOuterAngle( float angle )
{
    _outerAngle = angle;
}

float Light3D::getOuterAngle()
{
    return _outerAngle;
}

void Light3D::onEnter()
{
    auto scene = getScene();
    if (scene)
    {
        auto &lights = scene->_lights;
        auto iter = std::find(lights.begin(), lights.end(), this);
        if (iter == lights.end())
            lights.push_back(this);
    }
}

void Light3D::onExit()
{
    auto scene = getScene();
    if (scene)
    {
        auto &lights = scene->_lights;
        auto iter = std::find(lights.begin(), lights.end(), this);
        if (iter != lights.end())
            lights.erase(iter);
    }
}

Light3D* Light3D::CreateDirectionalLight( const Vec3 &direction, const Color3B &color )
{
	Light3D *light = new Light3D;
	light->setLightType(DIRECTIONAL);
	light->setDirection(direction);
	light->setColor(color);
	light->autorelease();
	return light;
}

Light3D* Light3D::CreatePointLight( const Vec3 &position, const Color3B &color, float range )
{
	Light3D *light = new Light3D;
	light->setLightType(POINT);
	light->setPosition3D(position);
	light->setColor(color);
	light->setRange(range);
	light->autorelease();
	return light;
}

Light3D* Light3D::CreateSpotLight( const Vec3 &direction, const Vec3 &position, const Color3B &color, float innerAngle, float outerAngle, float range )
{
	Light3D *light = new Light3D;
	light->setLightType(SPOT);
	light->setDirection(direction);
	light->setPosition3D(position);
	light->setColor(color);
	light->setInnerAngle(innerAngle);
	light->setOuterAngle(outerAngle);
	light->setRange(range);
	light->autorelease();
	return light;
}

NS_CC_END