/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

namespace ShaderTest2
{
    static std::function<Layer*()> createFunctions[] =
    {
        CL(EffectSpriteTest),

        CL(BloomSpriteTest),
        CL(CelShadingSpriteTest),
        CL(LensFlareSpriteTest),
    };
    
    static unsigned int TEST_CASE_COUNT = sizeof(ShaderTest2::createFunctions) / sizeof(ShaderTest2::createFunctions[0]);
    
    static int sceneIdx=-1;
    Layer* createTest(int index)
    {
        auto layer = (createFunctions[index])();;
        return layer;
    }
    
    Layer* nextAction();
    Layer* backAction();
    Layer* restartAction();
    
    Layer* nextAction()
    {
        sceneIdx++;
        sceneIdx = sceneIdx % TEST_CASE_COUNT;
        
        return createTest(sceneIdx);
    }
    
    Layer* backAction()
    {
        sceneIdx--;
        if( sceneIdx < 0 )
            sceneIdx = TEST_CASE_COUNT -1;
        
        return createTest(sceneIdx);
    }
    
    Layer* restartAction()
    {
        return createTest(sceneIdx);
    }
    
}

ShaderTestDemo2::ShaderTestDemo2()
{
    
}

void ShaderTestDemo2::backCallback(Ref* sender)
{
    auto s = ShaderTestScene2::create();
    s->addChild( ShaderTest2::backAction() );
    Director::getInstance()->replaceScene(s);
}

void ShaderTestDemo2::nextCallback(Ref* sender)
{
    auto s = ShaderTestScene2::create();
    s->addChild( ShaderTest2::nextAction() );
    Director::getInstance()->replaceScene(s);
}

void ShaderTestDemo2::restartCallback(Ref* sender)
{
    auto s = ShaderTestScene2::create();
    s->addChild(ShaderTest2::restartAction());    
    Director::getInstance()->replaceScene(s);
}

void ShaderTestScene2::runThisTest()
{
    auto layer = ShaderTest2::nextAction();
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}

template <class spriteType>
class ShaderSpriteCreator
{
public:
    static spriteType* createSprite(const std::string& filename)
    {
        spriteType* ret = spriteType::create();
        ret->setTexture(filename);
        ret->initShader();
        ret->setBackgroundNotification();
        return ret;
    }
};


//
// EffectSprite
//
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

    void setEffect(Effect *effect) {
        if(_effect != effect) {
            effect->setTarget(this);

            CC_SAFE_RELEASE(_effect);
            _effect = effect;
            CC_SAFE_RETAIN(_effect);
            setGLProgramState(_effect->getGLProgramState());
        }
    }
protected:
    EffectSprite() : _effect(nullptr) {}
    Effect *_effect;
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

    _glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
    _glprogramstate->retain();

    return _glprogramstate != nullptr;
}

// Blur
class EffectBlur : public Effect
{
public:
    CREATE_FUNC(EffectBlur);

    virtual void setTarget(EffectSprite *sprite) override;

    void setGaussian(float value);
    void setCustomUniforms();
    void setBlurSize(float f);

protected:
    bool init(float blurSize=3.0);

    int       _blurRadius;
    Vec2   _pixelSize;

    int       _samplingRadius;
    float     _scale;
    float     _cons;
    float     _weightSum;
};

void EffectBlur::setTarget(EffectSprite *sprite)
{
    Size s = sprite->getTexture()->getContentSizeInPixels();
    _pixelSize = Vec2(1/s.width, 1/s.height);
    _glprogramstate->setUniformVec2("onePixelSize", _pixelSize);
}

bool EffectBlur::init(float blurSize)
{
    initGLProgramState("Shaders/example_Blur.fsh");
    auto s = Size(100,100);

    _blurRadius = 0;
    _pixelSize = Vec2(1/s.width, 1/s.height);
    _samplingRadius = 0;

    setBlurSize(blurSize);

    _glprogramstate->setUniformVec2("onePixelSize", _pixelSize);
    _glprogramstate->setUniformVec4("gaussianCoefficient", Vec4(_samplingRadius, _scale, _cons, _weightSum));
    return true;
}

void EffectBlur::setBlurSize(float f)
{
    if(_blurRadius == (int)f)
        return;
    _blurRadius = (int)f;

    _samplingRadius = _blurRadius;
    if (_samplingRadius > 10)
    {
        _samplingRadius = 10;
    }
    if (_blurRadius > 0)
    {
        float sigma = _blurRadius / 2.0f;
        _scale = -0.5f / (sigma * sigma);
        _cons = -1.0f * _scale / 3.141592f;
        _weightSum = -_cons;

        float weight;
        int squareX;
        for(int dx = 0; dx <= _samplingRadius; ++dx)
        {
            squareX = dx * dx;
            weight = _cons * exp(squareX * _scale);
            _weightSum += 2.0 * weight;
            for (int dy = 1; dy <= _samplingRadius; ++dy)
            {
                weight = _cons * exp((squareX + dy * dy) * _scale);
                _weightSum += 4.0 * weight;
            }
        }
    }
}

// Outline
class EffectOutline : public Effect
{
public:
    CREATE_FUNC(EffectOutline);

    bool init()
    {
        initGLProgramState("Shaders/example_outline.fsh");

        Vec3 color(1.0, 0.2, 0.3);
        GLfloat radius = 0.01;
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

    void setTarget(EffectSprite* sprite) override
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
        initGLProgramState("Shaders/example_edgeDetection.fsh");
        return true;
    }

    void setTarget(EffectSprite* sprite) override
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
        initGLProgramState("Shaders/example_greyScale.fsh");
        return true;
    }
};

//
// ShaderSprite
//
class ShaderSprite : public Sprite
{
public:
    ShaderSprite();
    ~ShaderSprite();

    virtual void initShader();
    void setBackgroundNotification();
    void listenBackToForeground(Ref *obj);
    
protected:
    virtual void setCustomUniforms() = 0;

    std::string _fragSourceFile;
    std::string _vertSourceFile;
};

ShaderSprite::ShaderSprite()
:_vertSourceFile("")
{
}

ShaderSprite::~ShaderSprite()
{
}

void ShaderSprite::setBackgroundNotification()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
            this->setGLProgramState(nullptr);
            this->initShader();
        });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
}

void ShaderSprite::initShader()
{
    auto fileUtiles = FileUtils::getInstance();
    auto fragmentFilePath = fileUtiles->fullPathForFilename(_fragSourceFile);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFilePath);
    std::string vertSource;
    if (_vertSourceFile.empty()) {
        vertSource = ccPositionTextureColor_noMVP_vert;
    }else{
        std::string vertexFilePath = fileUtiles->fullPathForFilename(_vertSourceFile);
        vertSource = fileUtiles->getStringFromFile(vertexFilePath);
    }

    auto glprogram = GLProgram::createWithByteArrays(vertSource.c_str(), fragSource.c_str());
    auto glprogramState = GLProgramState::getOrCreateWithGLProgram(glprogram);
    this->setGLProgramState(glprogramState);

    setCustomUniforms();
}

class BloomSprite : public ShaderSprite, public ShaderSpriteCreator<BloomSprite>
{
public:
    CREATE_FUNC(BloomSprite);
    BloomSprite();
    
protected:
    virtual void setCustomUniforms() override;

    GLfloat _resolution[2];
};

BloomSprite::BloomSprite()
{
    _fragSourceFile = "Shaders/example_bloom.fsh";
}

void BloomSprite::setCustomUniforms()
{
}

class CelShadingSprite : public ShaderSprite, public ShaderSpriteCreator<CelShadingSprite>
{
public:
    CREATE_FUNC(CelShadingSprite);
    CelShadingSprite();
    
protected:
    virtual void setCustomUniforms() override;

    GLfloat _resolution[2];
};

CelShadingSprite::CelShadingSprite()
{
    _fragSourceFile = "Shaders/example_celShading.fsh";
}

void CelShadingSprite::setCustomUniforms()
{
    auto programState = getGLProgramState();

    _resolution[0] = getContentSize().width;
    _resolution[1] = getContentSize().height;

    programState->setUniformVec2("resolution", Vec2(_resolution[0], _resolution[1]));
}

class LensFlareSprite : public ShaderSprite, public ShaderSpriteCreator<LensFlareSprite>
{
public:
    CREATE_FUNC(LensFlareSprite);
    LensFlareSprite();

protected:
    virtual void setCustomUniforms() override;

    GLfloat _resolution[2];
    GLfloat _textureResolution[2];
};

LensFlareSprite::LensFlareSprite()
{
    _fragSourceFile = "Shaders/example_lensFlare.fsh";
}

void LensFlareSprite::setCustomUniforms()
{
    auto programState = getGLProgramState();

    _textureResolution[0] = getTexture()->getContentSizeInPixels().width;
    _textureResolution[1] = getTexture()->getContentSizeInPixels().height;
    _resolution[0] = getContentSize().width;
    _resolution[1] = getContentSize().height;

    programState->setUniformVec2("resolution", Vec2(_resolution[0], _resolution[1]));
    programState->setUniformVec2("textureResolution", Vec2(_textureResolution[0], _textureResolution[1]));
}

BloomSpriteTest::BloomSpriteTest()
{
    if (ShaderTestDemo2::init())
    {
        auto s = Director::getInstance()->getWinSize();
        BloomSprite* sprite = BloomSprite::createSprite("Images/stone.png");
        sprite->setPosition(Vec2(s.width * 0.75, s.height/2));
        auto sprite2 = Sprite::create("Images/stone.png");
        sprite2->setPosition(Vec2(s.width * 0.25, s.height/2));
        addChild(sprite);
        addChild(sprite2);
    }
}

CelShadingSpriteTest::CelShadingSpriteTest()
{
    if (ShaderTestDemo2::init())
    {
        auto s = Director::getInstance()->getWinSize();
        CelShadingSprite* sprite = CelShadingSprite::createSprite("Images/stone.png");
        sprite->setPosition(Vec2(s.width * 0.75, s.height/2));
        auto sprite2 = Sprite::create("Images/stone.png");
        sprite2->setPosition(Vec2(s.width * 0.25, s.height/2));
        addChild(sprite);
        addChild(sprite2);
    }
}

LensFlareSpriteTest::LensFlareSpriteTest()
{
    if (ShaderTestDemo2::init())
    {
        auto s = Director::getInstance()->getWinSize();
        LensFlareSprite* sprite = LensFlareSprite::createSprite("Images/noise.png");
        Rect rect = Rect::ZERO;
        rect.size = Size(480,320);
        sprite->setPosition(Vec2(s.width * 0.5, s.height/2));
        addChild(sprite);
    }
}

EffectSpriteTest::EffectSpriteTest()
{
    if (ShaderTestDemo2::init()) {

        auto s = Director::getInstance()->getWinSize();

        auto item = MenuItemImage::create("Images/r1.png", "Images/r2.png",
                                          [&](Ref *sender) {
                                              _vectorIndex++;
                                              if(_vectorIndex>=_effects.size())
                                                  _vectorIndex = 0;
                                              _sprite->setEffect(_effects.at(_vectorIndex));
                                          });
        item->setPosition(Vec2(40,40));
        item->setScale(0.5);

        auto menu = Menu::create(item, NULL);
        menu->setPosition(Vec2(0,0));
        addChild(menu);

        _sprite = EffectSprite::create("Images/grossini.png");
        _sprite->setPosition(Vec2(0, s.height/2));
        addChild(_sprite);

        auto jump = JumpBy::create(4, Vec2(s.width,0), 100, 4);
        auto rot = RotateBy::create(4, 720);
        auto spawn = Spawn::create(jump, rot, NULL);
        auto rev = spawn->reverse();
        auto seq = Sequence::create(spawn, rev, NULL);
        auto repeat = RepeatForever::create(seq);
        _sprite->runAction(repeat);

        // set the Effects
        _effects.pushBack(EffectBlur::create());
        _effects.pushBack(EffectOutline::create());
        _effects.pushBack(EffectNoise::create());
        _effects.pushBack(EffectEdgeDetect::create());
        _effects.pushBack(EffectGreyScale::create());

        _vectorIndex = 0;
        _sprite->setEffect( _effects.at(_vectorIndex) );
    }
}

