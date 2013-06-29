/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

// ideas taken from:
//     . The ocean spray in your face [Jeff Lander]
//        http://www.double.co.nz/dust/col0798.pdf
//     . Building an Advanced Particle System [John van der Burg]
//        http://www.gamasutra.com/features/20000623/vanderburg_01.htm
//   . LOVE game engine
//        http://love2d.org/
//
//
// Radius mode support, from 71 squared
//        http://particledesigner.71squared.com/
//
// IMPORTANT: Particle Designer is supported by cocos2d, but
// 'Radius Mode' in Particle Designer uses a fixed emit rate of 30 hz. Since that can't be guaranteed in cocos2d,
//  cocos2d uses a another approach, but the results are almost identical. 
//

#include "CCParticleSystem.h"
#include "CCParticleBatchNode.h"
#include "ccTypes.h"
#include "textures/CCTextureCache.h"
#include "textures/CCTextureAtlas.h"
#include "support/base64.h"
#include "support/CCPointExtension.h"
#include "platform/CCFileUtils.h"
#include "platform/CCImage.h"
#include "platform/platform.h"
#include "support/zip_support/ZipUtils.h"
#include "CCDirector.h"
#include "support/CCProfiling.h"
// opengl
#include "CCGL.h"

#include <string>

using namespace std;


NS_CC_BEGIN

// ideas taken from:
//     . The ocean spray in your face [Jeff Lander]
//        http://www.double.co.nz/dust/col0798.pdf
//     . Building an Advanced Particle System [John van der Burg]
//        http://www.gamasutra.com/features/20000623/vanderburg_01.htm
//   . LOVE game engine
//        http://love2d.org/
//
//
// Radius mode support, from 71 squared
//        http://particledesigner.71squared.com/
//
// IMPORTANT: Particle Designer is supported by cocos2d, but
// 'Radius Mode' in Particle Designer uses a fixed emit rate of 30 hz. Since that can't be guaranteed in cocos2d,
//  cocos2d uses a another approach, but the results are almost identical. 
//

CCParticleSystem::CCParticleSystem()
: _plistFile("")
, _elapsed(0)
, _particles(NULL)
, _emitCounter(0)
, _particleIdx(0)
, _batchNode(NULL)
, _atlasIndex(0)
, _transformSystemDirty(false)
, _allocatedParticles(0)
, _isActive(true)
, _particleCount(0)
, _duration(0)
, _sourcePosition(CCPointZero)
, _posVar(CCPointZero)
, _life(0)
, _lifeVar(0)
, _angle(0)
, _angleVar(0)
, _startSize(0)
, _startSizeVar(0)
, _endSize(0)
, _endSizeVar(0)
, _startSpin(0)
, _startSpinVar(0)
, _endSpin(0)
, _endSpinVar(0)
, _emissionRate(0)
, _totalParticles(0)
, _texture(NULL)
, _opacityModifyRGB(false)
, _isBlendAdditive(false)
, _positionType(kCCPositionTypeFree)
, _isAutoRemoveOnFinish(false)
, _emitterMode(kCCParticleModeGravity)
{
    modeA.gravity = CCPointZero;
    modeA.speed = 0;
    modeA.speedVar = 0;
    modeA.tangentialAccel = 0;
    modeA.tangentialAccelVar = 0;
    modeA.radialAccel = 0;
    modeA.radialAccelVar = 0;
    modeA.rotationIsDir = false;
    modeB.startRadius = 0;
    modeB.startRadiusVar = 0;
    modeB.endRadius = 0;
    modeB.endRadiusVar = 0;            
    modeB.rotatePerSecond = 0;
    modeB.rotatePerSecondVar = 0;
    _blendFunc.src = CC_BLEND_SRC;
    _blendFunc.dst = CC_BLEND_DST;
}
// implementation CCParticleSystem

CCParticleSystem * CCParticleSystem::create(const char *plistFile)
{
    CCParticleSystem *pRet = new CCParticleSystem();
    if (pRet && pRet->initWithFile(plistFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return pRet;
}

CCParticleSystem* CCParticleSystem::createWithTotalParticles(unsigned int numberOfParticles)
{
    CCParticleSystem *pRet = new CCParticleSystem();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return pRet;
}

bool CCParticleSystem::init()
{
    return initWithTotalParticles(150);
}

bool CCParticleSystem::initWithFile(const char *plistFile)
{
    bool bRet = false;
    _plistFile = CCFileUtils::sharedFileUtils()->fullPathForFilename(plistFile);
    CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(_plistFile.c_str());

    CCAssert( dict != NULL, "Particles: file not found");
    
    // XXX compute path from a path, should define a function somewhere to do it
    string listFilePath = plistFile;
    if (listFilePath.find('/') != string::npos)
    {
        listFilePath = listFilePath.substr(0, listFilePath.rfind('/') + 1);
        bRet = this->initWithDictionary(dict, listFilePath.c_str());
    }
    else
    {
        bRet = this->initWithDictionary(dict, "");
    }
    
    dict->release();

    return bRet;
}

bool CCParticleSystem::initWithDictionary(CCDictionary *dictionary)
{
    return initWithDictionary(dictionary, "");
}

bool CCParticleSystem::initWithDictionary(CCDictionary *dictionary, const char *dirname)
{
    bool bRet = false;
    unsigned char *buffer = NULL;
    unsigned char *deflated = NULL;
    CCImage *image = NULL;
    do 
    {
        int maxParticles = dictionary->valueForKey("maxParticles")->intValue();
        // self, not super
        if(this->initWithTotalParticles(maxParticles))
        {
            // angle
            _angle = dictionary->valueForKey("angle")->floatValue();
            _angleVar = dictionary->valueForKey("angleVariance")->floatValue();

            // duration
            _duration = dictionary->valueForKey("duration")->floatValue();

            // blend function 
            _blendFunc.src = dictionary->valueForKey("blendFuncSource")->intValue();
            _blendFunc.dst = dictionary->valueForKey("blendFuncDestination")->intValue();

            // color
            _startColor.r = dictionary->valueForKey("startColorRed")->floatValue();
            _startColor.g = dictionary->valueForKey("startColorGreen")->floatValue();
            _startColor.b = dictionary->valueForKey("startColorBlue")->floatValue();
            _startColor.a = dictionary->valueForKey("startColorAlpha")->floatValue();

            _startColorVar.r = dictionary->valueForKey("startColorVarianceRed")->floatValue();
            _startColorVar.g = dictionary->valueForKey("startColorVarianceGreen")->floatValue();
            _startColorVar.b = dictionary->valueForKey("startColorVarianceBlue")->floatValue();
            _startColorVar.a = dictionary->valueForKey("startColorVarianceAlpha")->floatValue();

            _endColor.r = dictionary->valueForKey("finishColorRed")->floatValue();
            _endColor.g = dictionary->valueForKey("finishColorGreen")->floatValue();
            _endColor.b = dictionary->valueForKey("finishColorBlue")->floatValue();
            _endColor.a = dictionary->valueForKey("finishColorAlpha")->floatValue();

            _endColorVar.r = dictionary->valueForKey("finishColorVarianceRed")->floatValue();
            _endColorVar.g = dictionary->valueForKey("finishColorVarianceGreen")->floatValue();
            _endColorVar.b = dictionary->valueForKey("finishColorVarianceBlue")->floatValue();
            _endColorVar.a = dictionary->valueForKey("finishColorVarianceAlpha")->floatValue();

            // particle size
            _startSize = dictionary->valueForKey("startParticleSize")->floatValue();
            _startSizeVar = dictionary->valueForKey("startParticleSizeVariance")->floatValue();
            _endSize = dictionary->valueForKey("finishParticleSize")->floatValue();
            _endSizeVar = dictionary->valueForKey("finishParticleSizeVariance")->floatValue();

            // position
            float x = dictionary->valueForKey("sourcePositionx")->floatValue();
            float y = dictionary->valueForKey("sourcePositiony")->floatValue();
            this->setPosition( ccp(x,y) );            
            _posVar.x = dictionary->valueForKey("sourcePositionVariancex")->floatValue();
            _posVar.y = dictionary->valueForKey("sourcePositionVariancey")->floatValue();

            // Spinning
            _startSpin = dictionary->valueForKey("rotationStart")->floatValue();
            _startSpinVar = dictionary->valueForKey("rotationStartVariance")->floatValue();
            _endSpin= dictionary->valueForKey("rotationEnd")->floatValue();
            _endSpinVar= dictionary->valueForKey("rotationEndVariance")->floatValue();

            _emitterMode = dictionary->valueForKey("emitterType")->intValue();

            // Mode A: Gravity + tangential accel + radial accel
            if( _emitterMode == kCCParticleModeGravity ) 
            {
                // gravity
                modeA.gravity.x = dictionary->valueForKey("gravityx")->floatValue();
                modeA.gravity.y = dictionary->valueForKey("gravityy")->floatValue();

                // speed
                modeA.speed = dictionary->valueForKey("speed")->floatValue();
                modeA.speedVar = dictionary->valueForKey("speedVariance")->floatValue();

                // radial acceleration
                modeA.radialAccel = dictionary->valueForKey("radialAcceleration")->floatValue();
                modeA.radialAccelVar = dictionary->valueForKey("radialAccelVariance")->floatValue();

                // tangential acceleration
                modeA.tangentialAccel = dictionary->valueForKey("tangentialAcceleration")->floatValue();
                modeA.tangentialAccelVar = dictionary->valueForKey("tangentialAccelVariance")->floatValue();
                
                // rotation is dir
                modeA.rotationIsDir = dictionary->valueForKey("rotationIsDir")->boolValue();
            }

            // or Mode B: radius movement
            else if( _emitterMode == kCCParticleModeRadius ) 
            {
                modeB.startRadius = dictionary->valueForKey("maxRadius")->floatValue();
                modeB.startRadiusVar = dictionary->valueForKey("maxRadiusVariance")->floatValue();
                modeB.endRadius = dictionary->valueForKey("minRadius")->floatValue();
                modeB.endRadiusVar = 0.0f;
                modeB.rotatePerSecond = dictionary->valueForKey("rotatePerSecond")->floatValue();
                modeB.rotatePerSecondVar = dictionary->valueForKey("rotatePerSecondVariance")->floatValue();

            } else {
                CCAssert( false, "Invalid emitterType in config file");
                CC_BREAK_IF(true);
            }

            // life span
            _life = dictionary->valueForKey("particleLifespan")->floatValue();
            _lifeVar = dictionary->valueForKey("particleLifespanVariance")->floatValue();

            // emission Rate
            _emissionRate = _totalParticles / _life;

            //don't get the internal texture if a batchNode is used
            if (!_batchNode)
            {
                // Set a compatible default for the alpha transfer
                _opacityModifyRGB = false;

                // texture        
                // Try to get the texture from the cache
                std::string textureName = dictionary->valueForKey("textureFileName")->getCString();
                
                size_t rPos = textureName.rfind('/');
               
                if (rPos != string::npos)
                {
                    string textureDir = textureName.substr(0, rPos + 1);
                    
                    if (dirname != NULL && textureDir != dirname)
                    {
                        textureName = textureName.substr(rPos+1);
                        textureName = string(dirname) + textureName;
                    }
                }
                else
                {
                    if (dirname != NULL)
                    {
                        textureName = string(dirname) + textureName;
                    }
                }
                
                CCTexture2D *tex = NULL;
                
                if (textureName.length() > 0)
                {
                    // set not pop-up message box when load image failed
                    bool bNotify = CCFileUtils::sharedFileUtils()->isPopupNotify();
                    CCFileUtils::sharedFileUtils()->setPopupNotify(false);
                    tex = CCTextureCache::sharedTextureCache()->addImage(textureName.c_str());
                    // reset the value of UIImage notify
                    CCFileUtils::sharedFileUtils()->setPopupNotify(bNotify);
                }
                
                if (tex)
                {
                    setTexture(tex);
                }
                else
                {                        
                    const char *textureData = dictionary->valueForKey("textureImageData")->getCString();
                    CCAssert(textureData, "");
                    
                    int dataLen = strlen(textureData);
                    if(dataLen != 0)
                    {
                        // if it fails, try to get it from the base64-gzipped data    
                        int decodeLen = base64Decode((unsigned char*)textureData, (unsigned int)dataLen, &buffer);
                        CCAssert( buffer != NULL, "CCParticleSystem: error decoding textureImageData");
                        CC_BREAK_IF(!buffer);
                        
                        int deflatedLen = ZipUtils::ccInflateMemory(buffer, decodeLen, &deflated);
                        CCAssert( deflated != NULL, "CCParticleSystem: error ungzipping textureImageData");
                        CC_BREAK_IF(!deflated);
                        
                        // For android, we should retain it in VolatileTexture::addCCImage which invoked in CCTextureCache::sharedTextureCache()->addUIImage()
                        image = new CCImage();
                        bool isOK = image->initWithImageData(deflated, deflatedLen);
                        CCAssert(isOK, "CCParticleSystem: error init image with Data");
                        CC_BREAK_IF(!isOK);
                        
                        setTexture(CCTextureCache::sharedTextureCache()->addUIImage(image, textureName.c_str()));

                        image->release();
                    }
                }
                CCAssert( this->_texture != NULL, "CCParticleSystem: error loading the texture");
            }
            bRet = true;
        }
    } while (0);
    CC_SAFE_DELETE_ARRAY(buffer);
    CC_SAFE_DELETE_ARRAY(deflated);
    return bRet;
}

bool CCParticleSystem::initWithTotalParticles(unsigned int numberOfParticles)
{
    _totalParticles = numberOfParticles;

    CC_SAFE_FREE(_particles);
    
    _particles = (tCCParticle*)calloc(_totalParticles, sizeof(tCCParticle));

    if( ! _particles )
    {
        CCLOG("Particle system: not enough memory");
        this->release();
        return false;
    }
    _allocatedParticles = numberOfParticles;

    if (_batchNode)
    {
        for (unsigned int i = 0; i < _totalParticles; i++)
        {
            _particles[i].atlasIndex=i;
        }
    }
    // default, active
    _isActive = true;

    // default blend function
    _blendFunc.src = CC_BLEND_SRC;
    _blendFunc.dst = CC_BLEND_DST;

    // default movement type;
    _positionType = kCCPositionTypeFree;

    // by default be in mode A:
    _emitterMode = kCCParticleModeGravity;

    // default: modulate
    // XXX: not used
    //    colorModulate = YES;

    _isAutoRemoveOnFinish = false;

    // Optimization: compile updateParticle method
    //updateParticleSel = @selector(updateQuadWithParticle:newPosition:);
    //updateParticleImp = (CC_UPDATE_PARTICLE_IMP) [self methodForSelector:updateParticleSel];
    //for batchNode
    _transformSystemDirty = false;
    // update after action in run!
    this->scheduleUpdateWithPriority(1);

    return true;
}

CCParticleSystem::~CCParticleSystem()
{
    // Since the scheduler retains the "target (in this case the ParticleSystem)
	// it is not needed to call "unscheduleUpdate" here. In fact, it will be called in "cleanup"
    //unscheduleUpdate();
    CC_SAFE_FREE(_particles);
    CC_SAFE_RELEASE(_texture);
}

bool CCParticleSystem::addParticle()
{
    if (this->isFull())
    {
        return false;
    }

    tCCParticle * particle = &_particles[ _particleCount ];
    this->initParticle(particle);
    ++_particleCount;

    return true;
}

void CCParticleSystem::initParticle(tCCParticle* particle)
{
    // timeToLive
    // no negative life. prevent division by 0
    particle->timeToLive = _life + _lifeVar * CCRANDOM_MINUS1_1();
    particle->timeToLive = MAX(0, particle->timeToLive);

    // position
    particle->pos.x = _sourcePosition.x + _posVar.x * CCRANDOM_MINUS1_1();

    particle->pos.y = _sourcePosition.y + _posVar.y * CCRANDOM_MINUS1_1();


    // Color
    ccColor4F start;
    start.r = clampf(_startColor.r + _startColorVar.r * CCRANDOM_MINUS1_1(), 0, 1);
    start.g = clampf(_startColor.g + _startColorVar.g * CCRANDOM_MINUS1_1(), 0, 1);
    start.b = clampf(_startColor.b + _startColorVar.b * CCRANDOM_MINUS1_1(), 0, 1);
    start.a = clampf(_startColor.a + _startColorVar.a * CCRANDOM_MINUS1_1(), 0, 1);

    ccColor4F end;
    end.r = clampf(_endColor.r + _endColorVar.r * CCRANDOM_MINUS1_1(), 0, 1);
    end.g = clampf(_endColor.g + _endColorVar.g * CCRANDOM_MINUS1_1(), 0, 1);
    end.b = clampf(_endColor.b + _endColorVar.b * CCRANDOM_MINUS1_1(), 0, 1);
    end.a = clampf(_endColor.a + _endColorVar.a * CCRANDOM_MINUS1_1(), 0, 1);

    particle->color = start;
    particle->deltaColor.r = (end.r - start.r) / particle->timeToLive;
    particle->deltaColor.g = (end.g - start.g) / particle->timeToLive;
    particle->deltaColor.b = (end.b - start.b) / particle->timeToLive;
    particle->deltaColor.a = (end.a - start.a) / particle->timeToLive;

    // size
    float startS = _startSize + _startSizeVar * CCRANDOM_MINUS1_1();
    startS = MAX(0, startS); // No negative value

    particle->size = startS;

    if( _endSize == kCCParticleStartSizeEqualToEndSize )
    {
        particle->deltaSize = 0;
    }
    else
    {
        float endS = _endSize + _endSizeVar * CCRANDOM_MINUS1_1();
        endS = MAX(0, endS); // No negative values
        particle->deltaSize = (endS - startS) / particle->timeToLive;
    }

    // rotation
    float startA = _startSpin + _startSpinVar * CCRANDOM_MINUS1_1();
    float endA = _endSpin + _endSpinVar * CCRANDOM_MINUS1_1();
    particle->rotation = startA;
    particle->deltaRotation = (endA - startA) / particle->timeToLive;

    // position
    if( _positionType == kCCPositionTypeFree )
    {
        particle->startPos = this->convertToWorldSpace(CCPointZero);
    }
    else if ( _positionType == kCCPositionTypeRelative )
    {
        particle->startPos = _position;
    }

    // direction
    float a = CC_DEGREES_TO_RADIANS( _angle + _angleVar * CCRANDOM_MINUS1_1() );    

    // Mode Gravity: A
    if (_emitterMode == kCCParticleModeGravity) 
    {
        CCPoint v(cosf( a ), sinf( a ));
        float s = modeA.speed + modeA.speedVar * CCRANDOM_MINUS1_1();

        // direction
        particle->modeA.dir = ccpMult( v, s );

        // radial accel
        particle->modeA.radialAccel = modeA.radialAccel + modeA.radialAccelVar * CCRANDOM_MINUS1_1();
 

        // tangential accel
        particle->modeA.tangentialAccel = modeA.tangentialAccel + modeA.tangentialAccelVar * CCRANDOM_MINUS1_1();

        // rotation is dir
        if(modeA.rotationIsDir)
            particle->rotation = -CC_RADIANS_TO_DEGREES(ccpToAngle(particle->modeA.dir));
    }

    // Mode Radius: B
    else 
    {
        // Set the default diameter of the particle from the source position
        float startRadius = modeB.startRadius + modeB.startRadiusVar * CCRANDOM_MINUS1_1();
        float endRadius = modeB.endRadius + modeB.endRadiusVar * CCRANDOM_MINUS1_1();

        particle->modeB.radius = startRadius;

        if(modeB.endRadius == kCCParticleStartRadiusEqualToEndRadius)
        {
            particle->modeB.deltaRadius = 0;
        }
        else
        {
            particle->modeB.deltaRadius = (endRadius - startRadius) / particle->timeToLive;
        }

        particle->modeB.angle = a;
        particle->modeB.degreesPerSecond = CC_DEGREES_TO_RADIANS(modeB.rotatePerSecond + modeB.rotatePerSecondVar * CCRANDOM_MINUS1_1());
    }    
}

void CCParticleSystem::stopSystem()
{
    _isActive = false;
    _elapsed = _duration;
    _emitCounter = 0;
}

void CCParticleSystem::resetSystem()
{
    _isActive = true;
    _elapsed = 0;
    for (_particleIdx = 0; _particleIdx < _particleCount; ++_particleIdx)
    {
        tCCParticle *p = &_particles[_particleIdx];
        p->timeToLive = 0;
    }
}
bool CCParticleSystem::isFull()
{
    return (_particleCount == _totalParticles);
}

// ParticleSystem - MainLoop
void CCParticleSystem::update(float dt)
{
    CC_PROFILER_START_CATEGORY(kCCProfilerCategoryParticles , "CCParticleSystem - update");

    if (_isActive && _emissionRate)
    {
        float rate = 1.0f / _emissionRate;
        //issue #1201, prevent bursts of particles, due to too high emitCounter
        if (_particleCount < _totalParticles)
        {
            _emitCounter += dt;
        }
        
        while (_particleCount < _totalParticles && _emitCounter > rate) 
        {
            this->addParticle();
            _emitCounter -= rate;
        }

        _elapsed += dt;
        if (_duration != -1 && _duration < _elapsed)
        {
            this->stopSystem();
        }
    }

    _particleIdx = 0;

    CCPoint currentPosition = CCPointZero;
    if (_positionType == kCCPositionTypeFree)
    {
        currentPosition = this->convertToWorldSpace(CCPointZero);
    }
    else if (_positionType == kCCPositionTypeRelative)
    {
        currentPosition = _position;
    }

    if (_visible)
    {
        while (_particleIdx < _particleCount)
        {
            tCCParticle *p = &_particles[_particleIdx];

            // life
            p->timeToLive -= dt;

            if (p->timeToLive > 0) 
            {
                // Mode A: gravity, direction, tangential accel & radial accel
                if (_emitterMode == kCCParticleModeGravity) 
                {
                    CCPoint tmp, radial, tangential;

                    radial = CCPointZero;
                    // radial acceleration
                    if (p->pos.x || p->pos.y)
                    {
                        radial = ccpNormalize(p->pos);
                    }
                    tangential = radial;
                    radial = ccpMult(radial, p->modeA.radialAccel);

                    // tangential acceleration
                    float newy = tangential.x;
                    tangential.x = -tangential.y;
                    tangential.y = newy;
                    tangential = ccpMult(tangential, p->modeA.tangentialAccel);

                    // (gravity + radial + tangential) * dt
                    tmp = ccpAdd( ccpAdd( radial, tangential), modeA.gravity);
                    tmp = ccpMult( tmp, dt);
                    p->modeA.dir = ccpAdd( p->modeA.dir, tmp);
                    tmp = ccpMult(p->modeA.dir, dt);
                    p->pos = ccpAdd( p->pos, tmp );
                }

                // Mode B: radius movement
                else 
                {                
                    // Update the angle and radius of the particle.
                    p->modeB.angle += p->modeB.degreesPerSecond * dt;
                    p->modeB.radius += p->modeB.deltaRadius * dt;

                    p->pos.x = - cosf(p->modeB.angle) * p->modeB.radius;
                    p->pos.y = - sinf(p->modeB.angle) * p->modeB.radius;
                }

                // color
                p->color.r += (p->deltaColor.r * dt);
                p->color.g += (p->deltaColor.g * dt);
                p->color.b += (p->deltaColor.b * dt);
                p->color.a += (p->deltaColor.a * dt);

                // size
                p->size += (p->deltaSize * dt);
                p->size = MAX( 0, p->size );

                // angle
                p->rotation += (p->deltaRotation * dt);

                //
                // update values in quad
                //

                CCPoint    newPos;

                if (_positionType == kCCPositionTypeFree || _positionType == kCCPositionTypeRelative) 
                {
                    CCPoint diff = ccpSub( currentPosition, p->startPos );
                    newPos = ccpSub(p->pos, diff);
                } 
                else
                {
                    newPos = p->pos;
                }

                // translate newPos to correct position, since matrix transform isn't performed in batchnode
                // don't update the particle with the new position information, it will interfere with the radius and tangential calculations
                if (_batchNode)
                {
                    newPos.x+=_position.x;
                    newPos.y+=_position.y;
                }

                updateQuadWithParticle(p, newPos);
                //updateParticleImp(self, updateParticleSel, p, newPos);

                // update particle counter
                ++_particleIdx;
            } 
            else 
            {
                // life < 0
                int currentIndex = p->atlasIndex;
                if( _particleIdx != _particleCount-1 )
                {
                    _particles[_particleIdx] = _particles[_particleCount-1];
                }
                if (_batchNode)
                {
                    //disable the switched particle
                    _batchNode->disableParticle(_atlasIndex+currentIndex);

                    //switch indexes
                    _particles[_particleCount-1].atlasIndex = currentIndex;
                }


                --_particleCount;

                if( _particleCount == 0 && _isAutoRemoveOnFinish )
                {
                    this->unscheduleUpdate();
                    _parent->removeChild(this, true);
                    return;
                }
            }
        } //while
        _transformSystemDirty = false;
    }
    if (! _batchNode)
    {
        postStep();
    }

    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategoryParticles , "CCParticleSystem - update");
}

void CCParticleSystem::updateWithNoTime(void)
{
    this->update(0.0f);
}

void CCParticleSystem::updateQuadWithParticle(tCCParticle* particle, const CCPoint& newPosition)
{
    CC_UNUSED_PARAM(particle);
    CC_UNUSED_PARAM(newPosition);
    // should be overridden
}

void CCParticleSystem::postStep()
{
    // should be overridden
}

// ParticleSystem - CCTexture protocol
void CCParticleSystem::setTexture(CCTexture2D* var)
{
    if (_texture != var)
    {
        CC_SAFE_RETAIN(var);
        CC_SAFE_RELEASE(_texture);
        _texture = var;
        updateBlendFunc();
    }
}

void CCParticleSystem::updateBlendFunc()
{
    CCAssert(! _batchNode, "Can't change blending functions when the particle is being batched");

    if(_texture)
    {
        bool premultiplied = _texture->hasPremultipliedAlpha();
        
        _opacityModifyRGB = false;
        
        if( _texture && ( _blendFunc.src == CC_BLEND_SRC && _blendFunc.dst == CC_BLEND_DST ) )
        {
            if( premultiplied )
            {
                _opacityModifyRGB = true;
            }
            else
            {
                _blendFunc.src = GL_SRC_ALPHA;
                _blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
            }
        }
    }
}

CCTexture2D * CCParticleSystem::getTexture()
{
    return _texture;
}

// ParticleSystem - Additive Blending
void CCParticleSystem::setBlendAdditive(bool additive)
{
    if( additive )
    {
        _blendFunc.src = GL_SRC_ALPHA;
        _blendFunc.dst = GL_ONE;
    }
    else
    {
        if( _texture && ! _texture->hasPremultipliedAlpha() )
        {
            _blendFunc.src = GL_SRC_ALPHA;
            _blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
        } 
        else 
        {
            _blendFunc.src = CC_BLEND_SRC;
            _blendFunc.dst = CC_BLEND_DST;
        }
    }
}

bool CCParticleSystem::isBlendAdditive()
{
    return( _blendFunc.src == GL_SRC_ALPHA && _blendFunc.dst == GL_ONE);
}

// ParticleSystem - Properties of Gravity Mode 
void CCParticleSystem::setTangentialAccel(float t)
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    modeA.tangentialAccel = t;
}

float CCParticleSystem::getTangentialAccel()
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    return modeA.tangentialAccel;
}

void CCParticleSystem::setTangentialAccelVar(float t)
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    modeA.tangentialAccelVar = t;
}

float CCParticleSystem::getTangentialAccelVar()
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    return modeA.tangentialAccelVar;
}    

void CCParticleSystem::setRadialAccel(float t)
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    modeA.radialAccel = t;
}

float CCParticleSystem::getRadialAccel()
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    return modeA.radialAccel;
}

void CCParticleSystem::setRadialAccelVar(float t)
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    modeA.radialAccelVar = t;
}

float CCParticleSystem::getRadialAccelVar()
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    return modeA.radialAccelVar;
}

void CCParticleSystem::setRotationIsDir(bool t)
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    modeA.rotationIsDir = t;
}

bool CCParticleSystem::getRotationIsDir()
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    return modeA.rotationIsDir;
}

void CCParticleSystem::setGravity(const CCPoint& g)
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    modeA.gravity = g;
}

const CCPoint& CCParticleSystem::getGravity()
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    return modeA.gravity;
}

void CCParticleSystem::setSpeed(float speed)
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    modeA.speed = speed;
}

float CCParticleSystem::getSpeed()
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    return modeA.speed;
}

void CCParticleSystem::setSpeedVar(float speedVar)
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    modeA.speedVar = speedVar;
}

float CCParticleSystem::getSpeedVar()
{
    CCAssert( _emitterMode == kCCParticleModeGravity, "Particle Mode should be Gravity");
    return modeA.speedVar;
}

// ParticleSystem - Properties of Radius Mode
void CCParticleSystem::setStartRadius(float startRadius)
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    modeB.startRadius = startRadius;
}

float CCParticleSystem::getStartRadius()
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    return modeB.startRadius;
}

void CCParticleSystem::setStartRadiusVar(float startRadiusVar)
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    modeB.startRadiusVar = startRadiusVar;
}

float CCParticleSystem::getStartRadiusVar()
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    return modeB.startRadiusVar;
}

void CCParticleSystem::setEndRadius(float endRadius)
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    modeB.endRadius = endRadius;
}

float CCParticleSystem::getEndRadius()
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    return modeB.endRadius;
}

void CCParticleSystem::setEndRadiusVar(float endRadiusVar)
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    modeB.endRadiusVar = endRadiusVar;
}

float CCParticleSystem::getEndRadiusVar()
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    return modeB.endRadiusVar;
}

void CCParticleSystem::setRotatePerSecond(float degrees)
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    modeB.rotatePerSecond = degrees;
}

float CCParticleSystem::getRotatePerSecond()
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    return modeB.rotatePerSecond;
}

void CCParticleSystem::setRotatePerSecondVar(float degrees)
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    modeB.rotatePerSecondVar = degrees;
}

float CCParticleSystem::getRotatePerSecondVar()
{
    CCAssert( _emitterMode == kCCParticleModeRadius, "Particle Mode should be Radius");
    return modeB.rotatePerSecondVar;
}

bool CCParticleSystem::isActive()
{
    return _isActive;
}

unsigned int CCParticleSystem::getParticleCount() const
{
    return _particleCount;
}

float CCParticleSystem::getDuration()
{
    return _duration;
}

void CCParticleSystem::setDuration(float var)
{
    _duration = var;
}

const CCPoint& CCParticleSystem::getSourcePosition()
{
    return _sourcePosition;
}

void CCParticleSystem::setSourcePosition(const CCPoint& var)
{
    _sourcePosition = var;
}

const CCPoint& CCParticleSystem::getPosVar()
{
    return _posVar;
}

void CCParticleSystem::setPosVar(const CCPoint& var)
{
    _posVar = var;
}

float CCParticleSystem::getLife()
{
    return _life;
}

void CCParticleSystem::setLife(float var)
{
    _life = var;
}

float CCParticleSystem::getLifeVar()
{
    return _lifeVar;
}

void CCParticleSystem::setLifeVar(float var)
{
    _lifeVar = var;
}

float CCParticleSystem::getAngle()
{
    return _angle;
}

void CCParticleSystem::setAngle(float var)
{
    _angle = var;
}

float CCParticleSystem::getAngleVar()
{
    return _angleVar;
}

void CCParticleSystem::setAngleVar(float var)
{
    _angleVar = var;
}

float CCParticleSystem::getStartSize()
{
    return _startSize;
}

void CCParticleSystem::setStartSize(float var)
{
    _startSize = var;
}

float CCParticleSystem::getStartSizeVar()
{
    return _startSizeVar;
}

void CCParticleSystem::setStartSizeVar(float var)
{
    _startSizeVar = var;
}

float CCParticleSystem::getEndSize()
{
    return _endSize;
}

void CCParticleSystem::setEndSize(float var)
{
    _endSize = var;
}

float CCParticleSystem::getEndSizeVar()
{
    return _endSizeVar;
}

void CCParticleSystem::setEndSizeVar(float var)
{
    _endSizeVar = var;
}

const ccColor4F& CCParticleSystem::getStartColor()
{
    return _startColor;
}

void CCParticleSystem::setStartColor(const ccColor4F& var)
{
    _startColor = var;
}

const ccColor4F& CCParticleSystem::getStartColorVar()
{
    return _startColorVar;
}

void CCParticleSystem::setStartColorVar(const ccColor4F& var)
{
    _startColorVar = var;
}

const ccColor4F& CCParticleSystem::getEndColor()
{
    return _endColor;
}

void CCParticleSystem::setEndColor(const ccColor4F& var)
{
    _endColor = var;
}

const ccColor4F& CCParticleSystem::getEndColorVar()
{
    return _endColorVar;
}

void CCParticleSystem::setEndColorVar(const ccColor4F& var)
{
    _endColorVar = var;
}

float CCParticleSystem::getStartSpin()
{
    return _startSpin;
}

void CCParticleSystem::setStartSpin(float var)
{
    _startSpin = var;
}

float CCParticleSystem::getStartSpinVar()
{
    return _startSpinVar;
}

void CCParticleSystem::setStartSpinVar(float var)
{
    _startSpinVar = var;
}

float CCParticleSystem::getEndSpin()
{
    return _endSpin;
}

void CCParticleSystem::setEndSpin(float var)
{
    _endSpin = var;
}
float CCParticleSystem::getEndSpinVar()
{
    return _endSpinVar;
}

void CCParticleSystem::setEndSpinVar(float var)
{
    _endSpinVar = var;
}

float CCParticleSystem::getEmissionRate()
{
    return _emissionRate;
}

void CCParticleSystem::setEmissionRate(float var)
{
    _emissionRate = var;
}

unsigned int CCParticleSystem::getTotalParticles()
{
    return _totalParticles;
}

void CCParticleSystem::setTotalParticles(unsigned int var)
{
    CCAssert( var <= _allocatedParticles, "Particle: resizing particle array only supported for quads");
    _totalParticles = var;
}

ccBlendFunc CCParticleSystem::getBlendFunc()
{
    return _blendFunc;
}

void CCParticleSystem::setBlendFunc(ccBlendFunc blendFunc)
{
    if( _blendFunc.src != blendFunc.src || _blendFunc.dst != blendFunc.dst ) {
        _blendFunc = blendFunc;
        this->updateBlendFunc();
    }
}

bool CCParticleSystem::getOpacityModifyRGB()
{
    return _opacityModifyRGB;
}

void CCParticleSystem::setOpacityModifyRGB(bool bOpacityModifyRGB)
{
    _opacityModifyRGB = bOpacityModifyRGB;
}

tCCPositionType CCParticleSystem::getPositionType()
{
    return _positionType;
}

void CCParticleSystem::setPositionType(tCCPositionType var)
{
    _positionType = var;
}

bool CCParticleSystem::isAutoRemoveOnFinish()
{
    return _isAutoRemoveOnFinish;
}

void CCParticleSystem::setAutoRemoveOnFinish(bool var)
{
    _isAutoRemoveOnFinish = var;
}

int CCParticleSystem::getEmitterMode()
{
    return _emitterMode;
}

void CCParticleSystem::setEmitterMode(int var)
{
    _emitterMode = var;
}


// ParticleSystem - methods for batchNode rendering

CCParticleBatchNode* CCParticleSystem::getBatchNode(void)
{
    return _batchNode;
}

void CCParticleSystem::setBatchNode(CCParticleBatchNode* batchNode)
{
    if( _batchNode != batchNode ) {

        _batchNode = batchNode; // weak reference

        if( batchNode ) {
            //each particle needs a unique index
            for (unsigned int i = 0; i < _totalParticles; i++)
            {
                _particles[i].atlasIndex=i;
            }
        }
    }
}

//don't use a transform matrix, this is faster
void CCParticleSystem::setScale(float s)
{
    _transformSystemDirty = true;
    CCNode::setScale(s);
}

void CCParticleSystem::setRotation(float newRotation)
{
    _transformSystemDirty = true;
    CCNode::setRotation(newRotation);
}

void CCParticleSystem::setScaleX(float newScaleX)
{
    _transformSystemDirty = true;
    CCNode::setScaleX(newScaleX);
}

void CCParticleSystem::setScaleY(float newScaleY)
{
    _transformSystemDirty = true;
    CCNode::setScaleY(newScaleY);
}


NS_CC_END

