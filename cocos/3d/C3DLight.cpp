#include "Base.h"
#include "C3DLight.h"

namespace cocos3d
{

C3DLight::C3DLight(const char* strId) : C3DNode(strId), _component(NULL), _enable(true)
{

}

C3DLight::~C3DLight()
{
	SAFE_RELEASE(_component);
}

C3DLight::Type C3DLight::getLightType() const
{
    return _component ? _component->_type : UNKNOWN;
}

C3DLight* C3DLight::create(const char* strId)
{
	C3DLight* light = new C3DLight(strId);
	light->autorelease();
	return light;
}

void C3DLight::setComponent(C3DLightComponent* component)
{
	if (component == _component)
		return;

	SAFE_RELEASE(_component);
	
	if (component)
	{
		component->retain();
		_component = component;
		_component->_light = this;
	}
}

void C3DLight::update(unsigned int deltatime)
{
	if (_component)
		_component->update(deltatime);
}

//////////////////////////////////////////////////////////////////////////

C3DLightComponent::C3DLightComponent(C3DLight::Type type) : _type(type), _light(NULL), _color(0.0f, 0.0f, 0.0f)
{

}

const C3DVector3& C3DLightComponent::getColor() const
{
	return _color;
}

void C3DLightComponent::setColor(const C3DVector3& color)
{
	_color = color;
}


//////////////////////////////////////////////////////////////////////////

C3DPointLight::C3DPointLight() : C3DLightComponent(C3DLight::POINT), _range(1.0f), _rangeInverse(1.0f)
{

}

C3DPointLight* C3DPointLight::create(const C3DVector3& color, float range)
{
	C3DPointLight* pLight = new C3DPointLight();
	pLight->setColor(color);
	pLight->setRange(range);
	pLight->autorelease();
	return pLight;
}

void C3DPointLight::setRange(float range)
{
	_range = range;
	_rangeInverse = 1.0f / range;
}

//////////////////////////////////////////////////////////////////////////

C3DDirectionalLight::C3DDirectionalLight() : C3DLightComponent(C3DLight::DIRECTIONAL)
{

}

C3DDirectionalLight* C3DDirectionalLight::create(const C3DVector3& color)
{
	C3DDirectionalLight* pLight = new C3DDirectionalLight();
	pLight->setColor(color);
	pLight->autorelease();
	return pLight;
}

//////////////////////////////////////////////////////////////////////////

C3DSpotLight::C3DSpotLight() : C3DLightComponent(C3DLight::SPOT)
{


}

void C3DSpotLight::setRange(float range)
{
	_range = range;
	_rangeInverse = 1.0f / range;
}

void C3DSpotLight::setInnerAngle(float innerAngle)
{
	_innerAngle = innerAngle;
	_innerAngleCos = cos(innerAngle);
}

void C3DSpotLight::setOuterAngle(float outerAngle)
{
	_outerAngle = outerAngle;
	_outerAngleCos = cos(outerAngle);
}

C3DSpotLight* C3DSpotLight::create(const C3DVector3& color, float range, float innerAngle, float outerAngle)
{
	C3DSpotLight* pLight = new C3DSpotLight();
	pLight->setColor(color);
	pLight->setRange(range);
	pLight->setInnerAngle(innerAngle);
	pLight->setOuterAngle(outerAngle);
	pLight->autorelease();

	return pLight;
}

}