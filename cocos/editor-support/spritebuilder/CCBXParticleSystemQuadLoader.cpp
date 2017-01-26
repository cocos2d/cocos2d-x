#include "CCBXParticleSystemQuadLoader.h"

NS_CC_BEGIN

namespace spritebuilder {

static const std::string PROPERTY_EMITERMODE("emitterMode");
static const std::string PROPERTY_POSVAR("posVar");
static const std::string PROPERTY_EMISSIONRATE("emissionRate");
static const std::string PROPERTY_POSITIONTYPE("particlePositionType");
static const std::string PROPERTY_DURATION("duration");
static const std::string PROPERTY_TOTALPARTICLES("totalParticles");
static const std::string PROPERTY_LIFE("life");
static const std::string PROPERTY_STARTSIZE("startSize");
static const std::string PROPERTY_ENDSIZE("endSize");
static const std::string PROPERTY_STARTSPIN("startSpin");
static const std::string PROPERTY_ENDSPIN("endSpin");
static const std::string PROPERTY_ANGLE("angle");
static const std::string PROPERTY_STARTCOLOR("startColor");
static const std::string PROPERTY_ENDCOLOR("endColor");
static const std::string PROPERTY_BLENDFUNC("blendFunc");
static const std::string PROPERTY_GRAVITY("gravity");
static const std::string PROPERTY_SPEED("speed");
static const std::string PROPERTY_TANGENTIALACCEL("tangentialAccel");
static const std::string PROPERTY_RADIALACCEL("radialAccel");
static const std::string PROPERTY_TEXTURE("texture");
static const std::string PROPERTY_STARTRADIUS("startRadius");
static const std::string PROPERTY_ENDRADIUS("endRadius");
static const std::string PROPERTY_ROTATEPERSECOND("rotatePerSecond");
static const std::string PROPERTY_RESETONVISIBLE("resetOnVisibilityToggle");
    
class BuilderParticleSystemQuad: public ParticleSystemQuad
{
public:
    static BuilderParticleSystemQuad * createWithTotalParticles(int numberOfParticles) {
        BuilderParticleSystemQuad *particleSystemQuad = new (std::nothrow) BuilderParticleSystemQuad();
        if (particleSystemQuad && particleSystemQuad->initWithTotalParticles(numberOfParticles))
        {
            particleSystemQuad->autorelease();
            return particleSystemQuad;
        }
        CC_SAFE_DELETE(particleSystemQuad);
        return nullptr;
    }
    virtual void setVisible(bool visible) override
    {
        if(_resetOnVisible && isVisible() != visible)
        {
            if(visible)
                resetSystem();
            else
                stopSystem();
        }
        ParticleSystemQuad::setVisible(visible);
    }
    void setResetOnVisible(bool resetOnVisible)
    {
        _resetOnVisible = resetOnVisible;
    }
    bool getResetOnVisible()
    {
        return _resetOnVisible;
    }
    virtual void update(float dt) override
    {
        if(isVisible())
        {
            ParticleSystemQuad::update(dt);
        }
    }
CC_CONSTRUCTOR_ACCESS:
    BuilderParticleSystemQuad():_resetOnVisible(false)
    {
    }
private:
    bool _resetOnVisible;
};
    
ParticleSystemQuadLoader *ParticleSystemQuadLoader::create()
{
    ParticleSystemQuadLoader *ret = new ParticleSystemQuadLoader();
    ret->autorelease();
    return ret;
}
    
Node *ParticleSystemQuadLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    BuilderParticleSystemQuad *builderParticleSystemQuad =  BuilderParticleSystemQuad::createWithTotalParticles(_totalParticles);
    builderParticleSystemQuad->setAnchorPoint(Vec2(0.0f, 0.0f));
    return builderParticleSystemQuad;
}
    
void ParticleSystemQuadLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner) const
{
    BuilderParticleSystemQuad *particle = static_cast<BuilderParticleSystemQuad*>(node);
    
    particle->setPosVar(_posVar * CCBXReader::getResolutionScale());
    
    particle->setEmissionRate(_emissionRate);
    particle->setDuration(_duration);
    particle->setLife(_life.x);
    particle->setLifeVar(_life.y);
    particle->setStartSize(_startSize.x * CCBXReader::getResolutionScale());
    particle->setStartSizeVar(_startSize.y * CCBXReader::getResolutionScale());
    particle->setEndSize(_endSize.x * CCBXReader::getResolutionScale());
    particle->setEndSizeVar(_endSize.y * CCBXReader::getResolutionScale());
    particle->setStartSpin(_startSpin.x);
    particle->setStartSpinVar(_startSpin.y);
    particle->setEndSpin(_endSpin.x);
    particle->setEndSpinVar(_endSpin.y);
    particle->setAngle(_angle.x);
    particle->setAngleVar(_angle.y);
    particle->setTexture(_texture);
    particle->setBlendFunc(_blendFunc);
    particle->setEmitterMode(_emitterMode);
    particle->setPositionType(_positionType);
    
    switch(_emitterMode)
    {
        case ParticleSystem::Mode::GRAVITY:
            particle->setTangentialAccel(_tangentialAccel.x * CCBXReader::getResolutionScale());
            particle->setTangentialAccelVar(_tangentialAccel.y * CCBXReader::getResolutionScale());
            particle->setRadialAccel(_radialAccel.x * CCBXReader::getResolutionScale());
            particle->setRadialAccelVar(_radialAccel.y * CCBXReader::getResolutionScale());
            particle->setGravity(_gravity * CCBXReader::getResolutionScale());
            particle->setSpeed(_speed.x * CCBXReader::getResolutionScale());
            particle->setSpeedVar(_speed.y * CCBXReader::getResolutionScale());
            break;
        case ParticleSystem::Mode::RADIUS:
            particle->setStartRadius(_startRadius.x * CCBXReader::getResolutionScale());
            particle->setStartRadiusVar(_startRadius.y * CCBXReader::getResolutionScale());
            particle->setEndRadius(_endRadius.x * CCBXReader::getResolutionScale());
            particle->setEndRadiusVar(_endRadius.y * CCBXReader::getResolutionScale());
            particle->setRotatePerSecond(_rotatePerSecond.x);
            particle->setRotatePerSecondVar(_rotatePerSecond.y);
            break;
    }
    particle->setStartColor(_startColor);
    particle->setStartColorVar(_startColorVar);
    particle->setEndColor(_endColor);
    particle->setEndColorVar(_endColorVar);
    particle->setResetOnVisible(_resetOnVisible);
}
 
ParticleSystemQuadLoader::ParticleSystemQuadLoader()
    :_texture(nullptr)
    ,_blendFunc({GL_SRC_ALPHA, GL_ONE})
    ,_emitterMode(ParticleSystem::Mode::GRAVITY)
    ,_positionType(ParticleSystem::PositionType::FREE)
    ,_posVar(40.0f, 20.0f)
    ,_emissionRate(80.0f)
    ,_duration(-1)
    ,_totalParticles(250)
    ,_resetOnVisible(true)
    ,_life(3.0f, 0.25f)
    ,_startSize(54.0f, 10.0f)
    ,_angle(90.0f, 10.0f)
    ,_speed(60.0f, 20.0f)
    ,_startColor(Color4F::BLACK)
    ,_startColorVar(0, 0, 0, 0)
    ,_endColor(Color4F::BLACK)
    ,_endColorVar(0, 0, 0, 0)
{
    
}

ParticleSystemQuadLoader::~ParticleSystemQuadLoader()
{

}

void ParticleSystemQuadLoader::onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_EMITERMODE) {
        _emitterMode = static_cast<ParticleSystem::Mode>(value);
    } else if (propertyName == PROPERTY_POSITIONTYPE) {
        _positionType = static_cast<ParticleSystem::PositionType>(value);
    } else {
        NodeLoader::onHandlePropTypeIntegerLabeled(propertyName, isExtraProp, value);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypePoint(const std::string &propertyName, bool isExtraProp, const cocos2d::Point &value)
{
    if(propertyName == PROPERTY_POSVAR) {
        _posVar = value;
    } else if(propertyName == PROPERTY_GRAVITY) {
        _gravity = value;
    } else {
        NodeLoader::onHandlePropTypePoint(propertyName, isExtraProp, value);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value)
{
    if(propertyName == PROPERTY_EMISSIONRATE) {
        _emissionRate = value;
    } else if(propertyName == PROPERTY_DURATION) {
        _duration = value;
    } else {
        NodeLoader::onHandlePropTypeFloat(propertyName, isExtraProp, value);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypeInteger(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_TOTALPARTICLES) {
        _totalParticles = value;
    } else {
        NodeLoader::onHandlePropTypeInteger(propertyName, isExtraProp, value);
    }
    
}

void ParticleSystemQuadLoader::onHandlePropTypeFloatVar(const std::string &propertyName, bool isExtraProp, const Vec2 &value)
{
    if(propertyName == PROPERTY_LIFE) {
        _life = value;
    } else if(propertyName == PROPERTY_STARTSIZE) {
        _startSize = value;
    } else if(propertyName == PROPERTY_ENDSIZE) {
        _endSize = value;
    } else if(propertyName == PROPERTY_STARTSPIN) {
        _startSpin = value;
    } else if(propertyName == PROPERTY_ENDSPIN) {
        _endSpin = value;
    } else if(propertyName == PROPERTY_ANGLE) {
        _angle = value;
    } else if(propertyName == PROPERTY_SPEED) {
        _speed = value;
    } else if(propertyName == PROPERTY_TANGENTIALACCEL) {
        _tangentialAccel = value;
    } else if(propertyName == PROPERTY_RADIALACCEL) {
        _radialAccel = value;
    } else if(propertyName == PROPERTY_STARTRADIUS) {
        _startRadius = value;
    } else if(propertyName == PROPERTY_ENDRADIUS) {
        _endRadius = value;
    } else if(propertyName == PROPERTY_ROTATEPERSECOND) {
        _rotatePerSecond = value;
    } else {
        NodeLoader::onHandlePropTypeFloatVar(propertyName, isExtraProp, value);
    }

}

void ParticleSystemQuadLoader::onHandlePropTypeColor4FVar(const std::string &propertyName, bool isExtraProp, const std::pair<Color4F, Color4F> &value)
{
    if(propertyName == PROPERTY_STARTCOLOR) {
        _startColor = value.first;
        _startColorVar = value.second;
    } else if(propertyName == PROPERTY_ENDCOLOR) {
        _endColor = value.first;
        _endColorVar = value.second;
    } else {
        NodeLoader::onHandlePropTypeColor4FVar(propertyName, isExtraProp, value);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const cocos2d::BlendFunc &pBlendFunc)
{
    if(propertyName == PROPERTY_BLENDFUNC) {
        _blendFunc = pBlendFunc;
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(propertyName, isExtraProp, pBlendFunc);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypeTexture(const std::string &propertyName, bool isExtraProp, cocos2d::Texture2D * pTexture2D)
{
    if(propertyName == PROPERTY_TEXTURE) {
        _texture = pTexture2D;
    } else {
        NodeLoader::onHandlePropTypeTexture(propertyName, isExtraProp, pTexture2D);
    }
}
    
void ParticleSystemQuadLoader::onHandlePropTypeCheck(const std::string &propertyName, bool isExtraProp, bool value)
{
    if(propertyName == PROPERTY_RESETONVISIBLE) {
        _resetOnVisible = value;
    } else {
        NodeLoader::onHandlePropTypeCheck(propertyName, isExtraProp, value);
    }
}

}

NS_CC_END
