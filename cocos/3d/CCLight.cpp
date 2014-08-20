#include "CCLight.h"
#include "2d/CCScene.h"

NS_CC_BEGIN

Light3D::Light3D()
    : _isEnabled(true)
    , _range(0.0)
    , _innerAngle(0.0)
    , _outerAngle(0.0)
{
}

Light3D::~Light3D()
{
}

Light3D* Light3D::CreateDirectionalLight( const Vec3 &direction, const Color3B &color )
{
    Light3D *light = new Light3D;
    light->_lightType = DIRECTIONAL;
    light->calculateRotation(direction);
    light->setColor(color);
    light->autorelease();
    return light;
}

Light3D* Light3D::CreatePointLight( const Vec3 &position, const Color3B &color, float range )
{
    Light3D *light = new Light3D;
    light->_lightType = POINT;
    light->setPosition3D(position);
    light->setColor(color);
    light->_range = range;
    light->autorelease();
    return light;
}

Light3D* Light3D::CreateSpotLight( const Vec3 &direction, const Vec3 &position, const Color3B &color, float innerAngle, float outerAngle, float range )
{
    Light3D *light = new Light3D;
    light->_lightType = SPOT;
    light->calculateRotation(direction);
    light->setPosition3D(position);
    light->setColor(color);
    light->_innerAngle = innerAngle;
    light->_outerAngle = outerAngle;
    light->_range = range;
    light->autorelease();
    return light;
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

void Light3D::setEnabled( bool isON )
{
    _isEnabled = isON;
}

bool Light3D::getEnabled()
{
    return _isEnabled;
}

void Light3D::calculateRotation( const Vec3 &direction )
{
    Vec3 inverseDir = -direction;
    float projLen = sqrt(inverseDir.x * inverseDir.x + inverseDir.z * inverseDir.z);
    float rotY = CC_RADIANS_TO_DEGREES(atan2f(inverseDir.x, inverseDir.z));
    float rotX = -CC_RADIANS_TO_DEGREES(atan2f(inverseDir.y, projLen));
    setRotation3D(Vec3(rotX, rotY, 0.0f));
}

void Light3D::setDirection( const Vec3 &dir )
{
    calculateRotation(dir);
}

Vec3 Light3D::getDirection() const
{
    Mat4 mat = getNodeToParentTransform();
    mat.m[12] = mat.m[13] = mat.m[14] = 0.0f;
    mat.inverse();
    mat.transpose();

    Vec3 dir;
    mat.transformVector(0.0f, 0.0f, -1.0f, 0.0f, &dir);

    return dir;
}

Vec3 Light3D::getWorldDirection() const
{
    Mat4 mat = getNodeToWorldTransform();
    mat.m[12] = mat.m[13] = mat.m[14] = 0.0f;
    mat.inverse();
    mat.transpose();

    Vec3 dir;
    mat.transformVector(0.0f, 0.0f, -1.0f, 0.0f, &dir);

    return dir;
}

NS_CC_END