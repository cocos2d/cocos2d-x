#include "2d/CCLight.h"
#include "2d/CCScene.h"

NS_CC_BEGIN

void BaseLight::setIntensity(float intensity)
{
    CC_ASSERT(intensity >= 0);
    _intensity = intensity;
}

void BaseLight::onEnter()
{
    auto scene = getScene();
    if (scene)
    {
        auto &lights = scene->_lights;
        auto iter = std::find(lights.begin(), lights.end(), this);
        if (iter == lights.end())
            lights.push_back(this);
    }
    Node::onEnter();
}
void BaseLight::onExit()
{
    auto scene = getScene();
    if (scene)
    {
        auto &lights = scene->_lights;
        auto iter = std::find(lights.begin(), lights.end(), this);
        if (iter != lights.end())
            lights.erase(iter);
    }
    Node::onExit();
}

void BaseLight::setRotationFromDirection( const Vec3 &direction )
{
    float projLen = sqrt(direction.x * direction.x + direction.z * direction.z);
    float rotY = CC_RADIANS_TO_DEGREES(atan2f(-direction.x, -direction.z));
    float rotX = -CC_RADIANS_TO_DEGREES(atan2f(-direction.y, projLen));
    setRotation3D(Vec3(rotX, rotY, 0.0f));
}

BaseLight::BaseLight()
: _intensity(1.0f)
, _lightFlag(1)
, _enabled(true)
{
    
}
BaseLight::~BaseLight()
{
    
}

BaseLight* BaseLight::deepCopy()
{
  return nullptr;
}


////////////////////////////////////////////////////////////////////
DirectionLight* DirectionLight::create(const Vec3 &direction, const Color3B &color)
{
    auto light = new (std::nothrow) DirectionLight();
    light->setRotationFromDirection(direction);
    light->setColor(color);
    light->autorelease();
    return light;
}

void DirectionLight::setDirection(const Vec3 &dir)
{
    setRotationFromDirection(dir);
}
Vec3 DirectionLight::getDirection() const
{
    Mat4 mat = getNodeToParentTransform();
    return Vec3(-mat.m[8], -mat.m[9], -mat.m[10]);
}
Vec3 DirectionLight::getDirectionInWorld() const
{
    Mat4 mat = getNodeToWorldTransform();
    return Vec3(-mat.m[8], -mat.m[9], -mat.m[10]);
}
DirectionLight::DirectionLight()
{
    
}
DirectionLight::~DirectionLight()
{
    
}

DirectionLight* DirectionLight::deepCopy()
{
  return DirectionLight::create(this->getDirection(), this->getColor());
}

//////////////////////////////////////////////////////////////////
PointLight* PointLight::create(const Vec3 &position, const Color3B &color, float range)
{
    auto light = new (std::nothrow) PointLight();
    light->setPosition3D(position);
    light->setColor(color);
    light->_range = range;
    light->autorelease();
    return light;
}

PointLight::PointLight()
{
    
}
PointLight::~PointLight()
{
    
}

PointLight* PointLight::deepCopy()
{
  return PointLight::create(this->getPosition3D(), this->getColor(), this->getRange());
}

//////////////////////////////////////////////////////////////
SpotLight* SpotLight::create(const Vec3 &direction, const Vec3 &position, const Color3B &color, float innerAngle, float outerAngle, float range)
{
    auto light = new (std::nothrow) SpotLight();
    light->setRotationFromDirection(direction);
    light->setPosition3D(position);
    light->setColor(color);
    light->setInnerAngle(innerAngle);
    light->setOuterAngle(outerAngle);
    light->_range = range;
    light->autorelease();
    return light;
}

void SpotLight::setDirection(const Vec3 &dir)
{
    setRotationFromDirection(dir);
}

Vec3 SpotLight::getDirection() const
{
    Mat4 mat = getNodeToParentTransform();
    return Vec3(-mat.m[8], -mat.m[9], -mat.m[10]);
}

Vec3 SpotLight::getDirectionInWorld() const
{
    Mat4 mat = getNodeToWorldTransform();
    return Vec3(-mat.m[8], -mat.m[9], -mat.m[10]);
}

void SpotLight::setInnerAngle(float angle)
{
    _innerAngle = angle;
    _cosInnerAngle = cosf(angle);
}

void SpotLight::setOuterAngle(float angle)
{
    _outerAngle = angle;
    _cosOuterAngle = cosf(angle);
}

SpotLight::SpotLight()
{

}

SpotLight::~SpotLight()
{

}

SpotLight* SpotLight::deepCopy()
{
  return SpotLight::create(this->getDirection(), this->getPosition3D(), this->getColor(), this->getInnerAngle(), this->getOuterAngle(), this->getRange());
}

/////////////////////////////////////////////////////////////

AmbientLight* AmbientLight::create( const Color3B &color )
{
    auto light = new (std::nothrow) AmbientLight();
    light->setColor(color);
    light->autorelease();
    return light;
}

AmbientLight::AmbientLight()
{

}

AmbientLight::~AmbientLight()
{

}

AmbientLight* AmbientLight::deepCopy()
{
  return AmbientLight::create(this->getColor());
}

NS_CC_END