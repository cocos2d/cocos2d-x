/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "ShaderTest2.h"
#include "ShaderTest.h"
#include "../testResource.h"
#include "cocos2d.h"
#include <tuple>

USING_NS_CC;

Shader2Tests::Shader2Tests()
{
    ADD_TEST_CASE(EffectSpriteTest);
    ADD_TEST_CASE(EffectSpriteLamp);
}

//
// EffectSprite
//
static int tuple_sort( const std::tuple<ssize_t,Effect*,QuadCommand> &tuple1, const std::tuple<ssize_t,Effect*,QuadCommand> &tuple2 )
{
    return std::get<0>(tuple1) < std::get<0>(tuple2);
}

class Effect;
class EffectSprite : public Sprite
{
public:
    static EffectSprite *create(const std::string& filename) {
        auto ret = new (std::nothrow) EffectSprite;
        if(ret && ret->initWithFile(filename)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_RELEASE(ret);
        return nullptr;
    }

    void setEffect(Effect* effect) {
        if(_defaultEffect != effect) {
            effect->setTarget(this);

            CC_SAFE_RELEASE(_defaultEffect);
            _defaultEffect = effect;
            CC_SAFE_RETAIN(_defaultEffect);

            setGLProgramState(_defaultEffect->getGLProgramState());
        }
    }
    void addEffect(Effect *effect, ssize_t order) {
        effect->retain();
        effect->setTarget(this);

        _effects.push_back(std::make_tuple(order,effect,QuadCommand()));

        std::sort(std::begin(_effects), std::end(_effects), tuple_sort);
    }

    void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override
    {
#if CC_USE_CULLING
        // Don't do calculate the culling if the transform was not updated
        _insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;

        if(_insideBounds)
#endif
        {
            // negative effects: order < 0
            int idx=0;
            for(auto &effect : _effects) {

                if(std::get<0>(effect) >=0)
                    break;
                auto glProgramState = std::get<1>(effect)->getGLProgramState();
                if (glProgramState)
                {
                    QuadCommand &q = std::get<2>(effect);
                    q.init(_globalZOrder, _texture->getName(), glProgramState, _blendFunc, &_quad, 1, transform, flags);
                    renderer->addCommand(&q);
                }
                idx++;
            }

            // normal effect: order == 0
            _trianglesCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, _polyInfo.triangles, transform, flags);
            renderer->addCommand(&_trianglesCommand);

            // positive effects: order >= 0
            for(auto it = std::begin(_effects)+idx; it != std::end(_effects); ++it) {
                QuadCommand &q = std::get<2>(*it);
                q.init(_globalZOrder, _texture->getName(), std::get<1>(*it)->getGLProgramState(), _blendFunc, &_quad, 1, transform, flags);
                renderer->addCommand(&q);
                idx++;
            }
        }
    }
protected:
    EffectSprite() : _defaultEffect(nullptr)
    {
        _effects.reserve(2);
    }
    ~EffectSprite() {
        for(auto &tuple : _effects) {
            std::get<1>(tuple)->release();
        }
        CC_SAFE_RELEASE(_defaultEffect);
    }

    std::vector<std::tuple<ssize_t,Effect*,QuadCommand>> _effects;
    Effect* _defaultEffect;
};

//
// Effect
//

bool Effect::initGLProgramState(const std::string &fragmentFilename)
{
    auto fileUtiles = FileUtils::getInstance();
    auto fragmentFullPath = fileUtiles->fullPathForFilename(fragmentFilename);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _fragSource = fragSource;
#endif
    
    _glprogramstate = (glprogram == nullptr ? nullptr : GLProgramState::getOrCreateWithGLProgram(glprogram));
    CC_SAFE_RETAIN(_glprogramstate);

    return _glprogramstate != nullptr;
}

Effect::Effect()
: _glprogramstate(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _backgroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                      [this](EventCustom*)
                                                      {
                                                          auto glProgram = _glprogramstate->getGLProgram();
                                                          glProgram->reset();
                                                          glProgram->initWithByteArrays(ccPositionTextureColor_noMVP_vert, _fragSource.c_str());
                                                          glProgram->link();
                                                          glProgram->updateUniforms();
                                                      }
                                                      );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backgroundListener, -1);
#endif
}

Effect::~Effect()
{
    CC_SAFE_RELEASE_NULL(_glprogramstate);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backgroundListener);
#endif
}

// Blur
class EffectBlur : public Effect
{
public:
    CREATE_FUNC(EffectBlur);
    virtual void setTarget(EffectSprite *sprite) override;
    void setBlurRadius(float radius);
    void setBlurSampleNum(float num);

protected:
    bool init(float blurRadius = 10.0f, float sampleNum = 5.0f);
    
    float _blurRadius;
    float _blurSampleNum;
};

void EffectBlur::setTarget(EffectSprite *sprite)
{
    if (_glprogramstate == nullptr)
        return;
    
    Size size = sprite->getTexture()->getContentSizeInPixels();
    _glprogramstate->setUniformVec2("resolution", size);
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    _glprogramstate->setUniformFloat("blurRadius", _blurRadius);
    _glprogramstate->setUniformFloat("sampleNum", _blurSampleNum);
#endif
}

bool EffectBlur::init(float blurRadius, float sampleNum)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    initGLProgramState("Shaders/example_Blur.fsh");
#else
    initGLProgramState("Shaders/example_Blur_winrt.fsh");
#endif
    _blurRadius = blurRadius;
    _blurSampleNum = sampleNum;
    
    return true;
}

void EffectBlur::setBlurRadius(float radius)
{
    _blurRadius = radius;
}

void EffectBlur::setBlurSampleNum(float num)
{
    _blurSampleNum = num;
}

// Outline
class EffectOutline : public Effect
{
public:
    CREATE_FUNC(EffectOutline);

    bool init()
    {
        initGLProgramState("Shaders/example_Outline.fsh");

        Vec3 color(1.0f, 0.2f, 0.3f);
        GLfloat radius = 0.01f;
        GLfloat threshold = 1.75;

        _glprogramstate->setUniformVec3("u_outlineColor", color);
        _glprogramstate->setUniformFloat("u_radius", radius);
        _glprogramstate->setUniformFloat("u_threshold", threshold);
        return true;
    }
};

// Noise
class EffectNoise : public Effect
{
public:
    CREATE_FUNC(EffectNoise);

protected:
    bool init() {
        initGLProgramState("Shaders/example_Noisy.fsh");
        return true;
    }

    virtual void setTarget(EffectSprite* sprite) override
    {
        auto s = sprite->getTexture()->getContentSizeInPixels();
        getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));
    }
};

// Edge Detect
class EffectEdgeDetect : public Effect
{
public:
    CREATE_FUNC(EffectEdgeDetect);

protected:
    bool init() {
        initGLProgramState("Shaders/example_EdgeDetection.fsh");
        return true;
    }

    virtual void setTarget(EffectSprite* sprite) override
    {
        auto s = sprite->getTexture()->getContentSizeInPixels();
        getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));
    }
};

// Grey
class EffectGreyScale : public Effect
{
public:
    CREATE_FUNC(EffectGreyScale);

protected:
    bool init() {
        initGLProgramState("Shaders/example_GreyScale.fsh");
        return true;
    }
};

// Sepia
class EffectSepia : public Effect
{
public:
    CREATE_FUNC(EffectSepia);

protected:
    bool init() {
        initGLProgramState("Shaders/example_Sepia.fsh");
        return true;
    }
};

// bloom
class EffectBloom : public Effect
{
public:
    CREATE_FUNC(EffectBloom);

protected:
    bool init() {
        initGLProgramState("Shaders/example_Bloom.fsh");
        return true;
    }

    virtual void setTarget(EffectSprite* sprite) override
    {
        auto s = sprite->getTexture()->getContentSizeInPixels();
        getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));
    }
};

// cel shading
class EffectCelShading : public Effect
{
public:
    CREATE_FUNC(EffectCelShading);

protected:
    bool init() {
        initGLProgramState("Shaders/example_CelShading.fsh");
        return true;
    }

    virtual void setTarget(EffectSprite* sprite) override
    {
        auto s = sprite->getTexture()->getContentSizeInPixels();
        getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));
    }
};

// Lens Flare
class EffectLensFlare : public Effect
{
public:
    CREATE_FUNC(EffectLensFlare);

protected:
    bool init() {
        initGLProgramState("Shaders/example_LensFlare.fsh");
        return true;
    }

    virtual void setTarget(EffectSprite* sprite) override
    {
        auto s = sprite->getTexture()->getContentSizeInPixels();
        getGLProgramState()->setUniformVec2("textureResolution", Vec2(s.width, s.height));

        s = Director::getInstance()->getWinSize();
        getGLProgramState()->setUniformVec2("resolution", Vec2(s.width, s.height));

    }
};

class EffectNormalMapped : public Effect
{
public:
    CREATE_FUNC(EffectNormalMapped);
    static EffectNormalMapped* create(const std::string&normalMapFileName)
    {
        EffectNormalMapped *normalMappedSprite = new (std::nothrow) EffectNormalMapped();
        if (normalMappedSprite && normalMappedSprite->init() && normalMappedSprite->initNormalMap(normalMapFileName))
        {
            
            normalMappedSprite->autorelease();
            return normalMappedSprite;
        }
        CC_SAFE_DELETE(normalMappedSprite);
        return nullptr;
    }
    void setKBump(float value);
    void setLightPos(const Vec3& pos);
    void setLightColor(const Color4F& color);
    float getKBump()const{return _kBump;}
protected:
    bool init();
    bool initNormalMap(const std::string&normalMapFileName);
    virtual void setTarget(EffectSprite* sprite) override;
    EffectSprite* _sprite;
    Vec3 _lightPos;
    Color4F _lightColor;
    float  _kBump;
};

bool EffectNormalMapped::init()
{
    initGLProgramState("Shaders3D/Normal.frag");
    _kBump = 2;
    return true;
}
bool EffectNormalMapped::initNormalMap(const std::string& normalMapFileName)
{
    auto normalMapTexture = Director::getInstance()->getTextureCache()->addImage(normalMapFileName);
    getGLProgramState()->setUniformTexture("u_normalMap", normalMapTexture);
    return true;
}
void EffectNormalMapped::setTarget(EffectSprite* sprite)
{
    _sprite = sprite;
    getGLProgramState()->setUniformFloat("u_kBump", _kBump);
    getGLProgramState()->setUniformVec2("u_contentSize", Vec2(sprite->getContentSize().width,sprite->getContentSize().height));
}

void EffectNormalMapped::setKBump(float value)
{
    _kBump = value;
    auto glProgramState = getGLProgramState();
    if(glProgramState) glProgramState->setUniformFloat("u_kBump", _kBump);
}

void EffectNormalMapped::setLightPos(const Vec3& pos)
{
    _lightPos = pos;
    auto glProgramState = getGLProgramState();
    if(glProgramState) glProgramState->setUniformVec4("u_lightPosInLocalSpace", Vec4(_lightPos.x,_lightPos.y,_lightPos.z,1));
    
}

void EffectNormalMapped::setLightColor(const Color4F& color)
{
    _lightColor = color;
    auto glProgramState = getGLProgramState();
    if(glProgramState) getGLProgramState()->setUniformVec3("u_diffuseL", Vec3(_lightColor.r,_lightColor.g,_lightColor.b));
    
}

EffectSpriteTest::EffectSpriteTest()
{
}

bool EffectSpriteTest::init()
{
    if (ShaderTestDemo2::init()) {

        auto layer = LayerColor::create(Color4B::BLUE);
        this->addChild(layer);

        auto s = Director::getInstance()->getWinSize();

        auto itemPrev = MenuItemImage::create("Images/b1.png", "Images/b2.png",
                                          [&](Ref *sender) {
                                              _vectorIndex--;
                                              if(_vectorIndex<0)
                                                  _vectorIndex = _effects.size()-1;
                                              _sprite->setEffect(_effects.at(_vectorIndex));
                                          });

        auto itemNext = MenuItemImage::create("Images/f1.png", "Images/f2.png",
                                          [&](Ref *sender) {
                                              _vectorIndex++;
                                              if(_vectorIndex>=_effects.size())
                                                  _vectorIndex = 0;
                                              _sprite->setEffect(_effects.at(_vectorIndex));
                                          });

        auto menu = Menu::create(itemPrev, itemNext, nullptr);
        menu->alignItemsHorizontally();
        menu->setScale(0.5);
        menu->setAnchorPoint(Vec2(0,0));
        menu->setPosition(Vec2(s.width/2,70));
        addChild(menu);

        _sprite = EffectSprite::create("Images/grossini.png");
        _sprite->setPosition(Vec2(0, s.height/2));
        addChild(_sprite);

        auto jump = JumpBy::create(4, Vec2(s.width,0), 100, 4);
        auto rot = RotateBy::create(4, 720);
        auto spawn = Spawn::create(jump, rot, nullptr);
        auto rev = spawn->reverse();
        auto seq = Sequence::create(spawn, rev, nullptr);
        auto repeat = RepeatForever::create(seq);
        _sprite->runAction(repeat);

        // set the Effects
        _effects.pushBack(EffectBlur::create());
        _effects.pushBack(EffectOutline::create());
        _effects.pushBack(EffectNoise::create());
        _effects.pushBack(EffectEdgeDetect::create());
        _effects.pushBack(EffectGreyScale::create());
        _effects.pushBack(EffectSepia::create());
        _effects.pushBack(EffectBloom::create());
        _effects.pushBack(EffectCelShading::create());
        _effects.pushBack(EffectLensFlare::create());

        _vectorIndex = 0;
        _sprite->setEffect( _effects.at(_vectorIndex) );

//        _sprite->addEffect( _effects.at(8), -10 );
//        _sprite->addEffect( _effects.at(1), 1 );
        
        return true;
    }
    return false;
}

EffectSpriteLamp::EffectSpriteLamp()
{
}

bool EffectSpriteLamp::init()
{
    if (ShaderTestDemo2::init()) {
        
        auto s = Director::getInstance()->getWinSize();
        _sprite = EffectSprite::create("Images/elephant1_Diffuse.png");
        //auto contentSize = _sprite->getContentSize();
        _sprite->setPosition(Vec2(s.width/2, s.height/2));
        addChild(_sprite);
        
        auto lampEffect = EffectNormalMapped::create("Images/elephant1_Normal.png");
        
        Vec3 pos(150,150, 50);
        _lightSprite = Sprite::create("Images/ball.png");
        this->addChild(_lightSprite);
        _lightSprite->setPosition(Vec2(pos.x, s.height- pos.y));
        Mat4 mat = _sprite->getNodeToWorldTransform();
        Point lightPosInLocalSpace = PointApplyAffineTransform(Vec2(pos.x, pos.y), _sprite->getWorldToNodeAffineTransform());
        lampEffect->setLightColor(Color4F(1,1,1,1));
        lampEffect->setLightPos(Vec3(lightPosInLocalSpace.x, lightPosInLocalSpace.y, 50));
        lampEffect->setKBump(2);
        _sprite->setEffect(lampEffect);
        _effect = lampEffect;
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(EffectSpriteLamp::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(EffectSpriteLamp::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(EffectSpriteLamp::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        return true;
    }
    return false;
}


void EffectSpriteLamp::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto s = Director::getInstance()->getWinSize();
        Point loc_winSpace = touch->getLocationInView();
        _lightSprite->setPosition(Vec2( loc_winSpace.x,  s.height - loc_winSpace.y));
        Vec3 pos(loc_winSpace.x,loc_winSpace.y, 50);
        Mat4 mat = _sprite->getNodeToWorldTransform();
        Point lightPosInLocalSpace = PointApplyAffineTransform(Vec2(pos.x, pos.y), _sprite->getWorldToNodeAffineTransform());
        ((EffectNormalMapped*)_effect)->setLightPos(Vec3(lightPosInLocalSpace.x, lightPosInLocalSpace.y, 50));
    }
}

void EffectSpriteLamp::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto s = Director::getInstance()->getWinSize();
        Point loc_winSpace = touch->getLocationInView();
        _lightSprite->setPosition(Vec2( loc_winSpace.x, s.height - loc_winSpace.y));
        Vec3 pos(loc_winSpace.x,loc_winSpace.y, 50);
        Mat4 mat = _sprite->getNodeToWorldTransform();
        Point lightPosInLocalSpace = PointApplyAffineTransform(Vec2(pos.x, pos.y), _sprite->getWorldToNodeAffineTransform());
        ((EffectNormalMapped*)_effect)->setLightPos(Vec3(lightPosInLocalSpace.x, lightPosInLocalSpace.y, 50));
    }
}

void EffectSpriteLamp::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto s = Director::getInstance()->getWinSize();
        Point loc_winSpace = touch->getLocationInView();
        _lightSprite->setPosition(Vec2( loc_winSpace.x, s.height - loc_winSpace.y));
        Vec3 pos(loc_winSpace.x,loc_winSpace.y, 50);
        Mat4 mat = _sprite->getNodeToWorldTransform();
        Point lightPosInLocalSpace = PointApplyAffineTransform(Vec2(pos.x, pos.y), _sprite->getWorldToNodeAffineTransform());
        ((EffectNormalMapped*)_effect)->setLightPos(Vec3(lightPosInLocalSpace.x, lightPosInLocalSpace.y, 50));
    }
}
