#include "CCLight.h"
#include "2d/CCScene.h"

NS_CC_BEGIN

Light::Light()
: _range(0.0f)
, _innerAngle(0.0f)
, _outerAngle(0.0f)
{
}


Light::~Light()
{
}

Light* Light::Create( LightType lightType )
{
	Light *light = new Light;
	light->setLightType(lightType);
	light->autorelease();
	return light;
}

void Light::setLightType( LightType lightType )
{
	_lightType = lightType;
}

void Light::setRange( float range )
{
	_range = range;
}

float Light::getRange()
{
	return _range;
}

void Light::setDirection( const Vec3 &dir )
{
	_dir = dir;
}

const Vec3& Light::getDirection() const
{
	return _dir;
}

void Light::setInnerAngle( float angle )
{
	_innerAngle = angle;
}

float Light::getInnerAngle()
{
	return _innerAngle;
}

void Light::setOuterAngle( float angle )
{
	_outerAngle = angle;
}

float Light::getOuterAngle()
{
	return _outerAngle;
}

void Light::onEnter()
{
	auto scene = getScene();
	if (scene)
	{
		auto lights = scene->_lights;
		auto iter = std::find(lights.begin(), lights.end(), this);
		if (iter == lights.end())
			lights.push_back(this);
	}
}

void Light::onExit()
{
	auto scene = getScene();
	if (scene)
	{
		auto lights = scene->_lights;
		auto iter = std::find(lights.begin(), lights.end(), this);
		if (iter != lights.end())
			lights.erase(iter);
	}
}

NS_CC_END
