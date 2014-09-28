#include "CCLight3D.h"
#include "2d/CCScene.h"

NS_CC_BEGIN

void BaseLight3D::setIntensity(float intensity)
{
    CC_ASSERT(intensity >= 0);
    _intensity = intensity;
}

void BaseLight3D::onEnter()
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
void BaseLight3D::onExit()
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

void BaseLight3D::setRotationFromDirection( const Vec3 &direction )
{
    float projLen = sqrt(direction.x * direction.x + direction.z * direction.z);
    float rotY = CC_RADIANS_TO_DEGREES(atan2f(-direction.x, -direction.z));
    float rotX = -CC_RADIANS_TO_DEGREES(atan2f(-direction.y, projLen));
    setRotation3D(Vec3(rotX, rotY, 0.0f));
}

BaseLight3D::BaseLight3D()
: _intensity(1.0f)
, _enabled(true)
, _lightFlag(LightFlag::LIGHT0)
{
    
}
BaseLight3D::~BaseLight3D()
{
    
}


////////////////////////////////////////////////////////////////////
DirectionLight3D* DirectionLight3D::create(const Vec3 &direction, const Color3B &color)
{
    auto light = new (std::nothrow) DirectionLight3D();
    light->setRotationFromDirection(direction);
    light->setColor(color);
    light->autorelease();
    return light;
}

void DirectionLight3D::setDirection(const Vec3 &dir)
{
    setRotationFromDirection(dir);
}
const Vec3& DirectionLight3D::getDirection() const
{
    static Vec3 dir;
    Mat4 mat = getNodeToParentTransform();
    dir.set(-mat.m[8], -mat.m[9], -mat.m[10]);
    return dir;
}
Vec3 DirectionLight3D::getDirectionInWorld() const
{
    Vec3 dir;
    Mat4 mat = getNodeToWorldTransform();
    dir.set(-mat.m[8], -mat.m[9], -mat.m[10]);
    return dir;
}
DirectionLight3D::DirectionLight3D()
{
    
}
DirectionLight3D::~DirectionLight3D()
{
    
}

//////////////////////////////////////////////////////////////////
PointLight3D* PointLight3D::create(const Vec3 &position, const Color3B &color, float range)
{
    auto light = new (std::nothrow) PointLight3D();
    light->setPosition3D(position);
    light->setColor(color);
    light->_range = range;
    light->autorelease();
    return light;
}

PointLight3D::PointLight3D()
{
    
}
PointLight3D::~PointLight3D()
{
    
}

//////////////////////////////////////////////////////////////
SpotLight3D* SpotLight3D::create(const Vec3 &direction, const Vec3 &position, const Color3B &color, float innerAngle, float outerAngle, float range)
{
    auto light = new (std::nothrow) SpotLight3D();
    light->setRotationFromDirection(direction);
    light->setPosition3D(position);
    light->setColor(color);
    light->setInnerAngle(innerAngle);
    light->setOuterAngle(outerAngle);
    light->_range = range;
    light->autorelease();
    return light;
}

void SpotLight3D::setDirection(const Vec3 &dir)
{
    setRotationFromDirection(dir);
}

const Vec3& SpotLight3D::getDirection() const
{
    static Vec3 dir;
    Mat4 mat = getNodeToParentTransform();
    dir.set(-mat.m[8], -mat.m[9], -mat.m[10]);
    return dir;
}

Vec3 SpotLight3D::getDirectionInWorld() const
{
    Vec3 dir;
    Mat4 mat = getNodeToWorldTransform();
    dir.set(-mat.m[8], -mat.m[9], -mat.m[10]);
    return dir;
}

void SpotLight3D::setInnerAngle(float angle)
{
    _innerAngle = angle;
    _cosInnerAngle = cosf(angle);
}

void SpotLight3D::setOuterAngle(float angle)
{
    _outerAngle = angle;
    _cosInnerAngle = cosf(angle);
}

SpotLight3D::SpotLight3D()
{

}

SpotLight3D::~SpotLight3D()
{

}

/////////////////////////////////////////////////////////////

AmbientLight3D* AmbientLight3D::create( const Color3B &color )
{
    auto light = new (std::nothrow) AmbientLight3D();
    light->setColor(color);
    light->autorelease();
    return light;
}

AmbientLight3D::AmbientLight3D()
{

}

AmbientLight3D::~AmbientLight3D()
{

}

NS_CC_END