/****************************************************************************
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

#include "ShaderTest.h"
#include "../testResource.h"
#include "cocos2d.h"
#include "renderer/ccShaders.h"
#include "renderer/backend/Device.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define SET_UNIFORM(ps, name, value)  do {   \
decltype(value) __v = value;                           \
auto __loc = (ps)->getUniformLocation(name);  \
(ps)->setUniform(__loc, &__v, sizeof(__v));  \
} while(false) 

#define SET_TEXTURE(ps, name, idx, value)  do {   \
auto * __v = value;                           \
auto __loc = (ps)->getUniformLocation(name);  \
(ps)->setTexture(__loc, idx, __v);  \
} while(false) 



ShaderTests::ShaderTests()
{
    ADD_TEST_CASE(ShaderLensFlare);
    ADD_TEST_CASE(ShaderMandelbrot);
    ADD_TEST_CASE(ShaderJulia);
    ADD_TEST_CASE(ShaderHeart);
    ADD_TEST_CASE(ShaderFlower);
    ADD_TEST_CASE(ShaderPlasma);
    ADD_TEST_CASE(ShaderBlur);
    ADD_TEST_CASE(ShaderRetroEffect);
    ADD_TEST_CASE(ShaderMonjori);
    ADD_TEST_CASE(ShaderGlow);
    ADD_TEST_CASE(ShaderMultiTexture);
}

///---------------------------------------
// 
// ShaderNode
// 
///---------------------------------------
enum 
{
    SIZE_X = 256,
    SIZE_Y = 256,
};

ShaderNode::ShaderNode()
:_center(Vec2(0.0f, 0.0f))
,_resolution(Vec2(0.0f, 0.0f))
,_time(0.0f)
{
}

ShaderNode::~ShaderNode()
{
}

ShaderNode* ShaderNode::shaderNodeWithVertex(const std::string &vert, const std::string& frag)
{
    auto node = new (std::nothrow) ShaderNode();
    node->initWithVertex(vert, frag);
    node->autorelease();

    return node;
}

bool ShaderNode::initWithVertex(const std::string &vert, const std::string &frag)
{
    _vertFileName = vert;
    _fragFileName = frag;

    loadShaderVertex(vert, frag);

    _time = 0;
    _resolution = Vec2(SIZE_X, SIZE_Y);

    scheduleUpdate();

    setContentSize(Size(SIZE_X, SIZE_Y));
    setAnchorPoint(Vec2(0.5f, 0.5f));
    
    // init custom command
    auto layout = _programState->getVertexLayout();
    auto attrPosLoc = _programState->getAttributeLocation("a_position");
    layout->setAttribute("a_position", attrPosLoc, backend::VertexFormat::FLOAT2, 0, false);

    float w = SIZE_X, h = SIZE_Y;
    Vec2 vertices[6] = { Vec2(0.0f,0.0f), Vec2(w,0.0f), Vec2(w,h), Vec2(0.0f,0.0f), Vec2(0.0f,h), Vec2(w,h) };
    layout->setLayout(sizeof(Vec2));

    /*
     * TODO: the Y-coordinate of subclasses are flipped in metal
     *
     * keywords: CC_USE_METAL , CC_USE_GL
     */
    
    _customCommand.createVertexBuffer(sizeof(Vec2), 6, CustomCommand::BufferUsage::STATIC);
    _customCommand.updateVertexBuffer(vertices, sizeof(vertices));

    _customCommand.setDrawType(CustomCommand::DrawType::ARRAY);

    return true;
}

void ShaderNode::loadShaderVertex(const std::string &vert, const std::string &frag)
{
    auto fileUtiles = FileUtils::getInstance();

    // frag
    auto fragmentFilePath = fileUtiles->fullPathForFilename(frag);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFilePath);

    // vert
    std::string vertSource;
    if (vert.empty()) {
        vertSource = position_vert; 
    } else {
        std::string vertexFilePath = fileUtiles->fullPathForFilename(vert);
        vertSource = fileUtiles->getStringFromFile(vertexFilePath);
    }
    auto program = backend::Device::getInstance()->newProgram(vertSource.c_str(), fragSource.c_str());
    auto programState = new backend::ProgramState(program);
    setProgramState(programState);
    CC_SAFE_RELEASE(programState);
    CC_SAFE_RELEASE(program);
}

void ShaderNode::update(float dt)
{
    _time += dt;
}

void ShaderNode::setPosition(const Vec2 &newPosition)
{
    Node::setPosition(newPosition);
    auto position = getPosition();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto retinaFactor = Director::getInstance()->getOpenGLView()->getRetinaFactor();
    _center = Vec2(position.x * frameSize.width / visibleSize.width * retinaFactor, position.y * frameSize.height / visibleSize.height * retinaFactor);
}

void ShaderNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    
    _programState->setUniform(_locResolution, &_resolution, sizeof(_resolution));
    _programState->setUniform(_locCenter, &_center, sizeof(_center));


    auto projectionMatrix = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    auto finalMatrix = projectionMatrix * transform;

    _programState->setUniform(_locMVP, finalMatrix.m, sizeof(finalMatrix.m));

    float time = Director::getInstance()->getTotalFrames() * Director::getInstance()->getAnimationInterval();
    Vec4 uTime(time / 10.0f, time, time * 2.0f, time * 4.0f);
    Vec4 sinTime(time / 8.0f, time / 4.0f, time / 2.0f, sinf(time));
    Vec4 cosTime(time / 8.0f, time / 4.0f, time / 2.0f, cosf(time));

    _programState->setUniform(_locTime, &uTime, sizeof(uTime));
    _programState->setUniform(_locSinTime, &sinTime, sizeof(sinTime));
    _programState->setUniform(_locCosTime, &cosTime, sizeof(cosTime));

    renderer->addCommand(&_customCommand);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 6);
}

void ShaderNode::updateUniforms()
{
    if(_programState == nullptr)
        return;

    _locResolution  = _programState->getUniformLocation("resolution");
    _locCenter      = _programState->getUniformLocation("center");
    _locMVP         = _programState->getUniformLocation("u_MVPMatrix");
    _locTime        = _programState->getUniformLocation("u_Time");
    _locSinTime     = _programState->getUniformLocation("u_SinTime");
    _locCosTime     = _programState->getUniformLocation("u_CosTime");
    _locScreenSize  = _programState->getUniformLocation("u_screenSize");
    
    const Vec2& frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    float retinaFactor = Director::getInstance()->getOpenGLView()->getRetinaFactor();
    auto screenSizeInPixels = frameSize * retinaFactor;
    _programState->setUniform(_locScreenSize, &screenSizeInPixels, sizeof(screenSizeInPixels));
}

/// ShaderMonjori

ShaderMonjori::ShaderMonjori()
{
}

bool ShaderMonjori::init()
{
    if (ShaderTestDemo::init())
    {
        auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/example_Monjori.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Vec2(s.width/2, s.height/2));

        addChild(sn);

        return true;
    }

    return false;
}

std::string ShaderMonjori::title() const
{
    return "Shader: Frag shader";
}

std::string ShaderMonjori::subtitle() const
{
    return "Monjori plane deformations";
}


/// ShaderMandelbrot
ShaderMandelbrot::ShaderMandelbrot()
{
}

bool ShaderMandelbrot::init()
{
    if (ShaderTestDemo::init())
    {
        auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/example_Mandelbrot.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Vec2(s.width/2, s.height/2));

        addChild(sn);
        return true;
    }
    
    return false;
}

std::string ShaderMandelbrot::title() const
{
    return "Shader: Frag shader";
}

std::string ShaderMandelbrot::subtitle() const
{
    return "Mandelbrot shader with Zoom";
}

/// ShaderJulia
ShaderJulia::ShaderJulia()
{
}

bool ShaderJulia::init()
{
    if (ShaderTestDemo::init())
    {
        auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/example_Julia.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Vec2(s.width/2, s.height/2));

        addChild(sn);
        return true;
    }

    return false;
}

std::string ShaderJulia::title() const
{
    return "Shader: Frag shader";
}

std::string ShaderJulia::subtitle() const
{
    return "Julia shader";
}


/// ShaderHeart
ShaderHeart::ShaderHeart()
{
}

bool ShaderHeart::init()
{
    if (ShaderTestDemo::init())
    {
        auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/example_Heart.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Vec2(s.width/2, s.height/2));

        addChild(sn);

        return true;
    }

    return false;
}

std::string ShaderHeart::title() const
{
    return "Shader: Frag shader";
}

std::string ShaderHeart::subtitle() const
{
    return "Heart";
}

/// ShaderFlower
ShaderFlower::ShaderFlower()
{
}

bool ShaderFlower::init()
{
    if (ShaderTestDemo::init())
    {
        auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/example_Flower.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Vec2(s.width/2, s.height/2));

        addChild(sn);

        return true;
    }

    return false;
}

std::string ShaderFlower::title() const
{
    return "Shader: Frag shader";
}

std::string ShaderFlower::subtitle() const
{
    return "Flower";
}

/// ShaderPlasma
ShaderPlasma::ShaderPlasma()
{
}

bool ShaderPlasma::init()
{
    if (ShaderTestDemo::init())
    {
        auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/example_Plasma.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Vec2(s.width/2, s.height/2));

        addChild(sn);

        return true;
    }

    return false;
}

std::string ShaderPlasma::title() const
{
    return "Shader: Frag shader";
}

std::string ShaderPlasma::subtitle() const
{
    return "Plasma";
}

// ShaderBlur

class SpriteBlur : public Sprite
{
public:
    ~SpriteBlur();
    bool initWithTexture(Texture2D* texture, const Rect&  rect);
    void initProgram();

    static SpriteBlur* create(const char *pszFileName);
    void setBlurRadius(float radius);
    void setBlurSampleNum(float num);

protected:
    float _blurRadius;
    float _blurSampleNum;
};

SpriteBlur::~SpriteBlur()
{
}

SpriteBlur* SpriteBlur::create(const char *pszFileName)
{
    SpriteBlur* pRet = new (std::nothrow) SpriteBlur();
    if (pRet)
    {
        bool result = pRet->initWithFile("");
        log("Test call Sprite::initWithFile with bad file name result is : %s", result ? "true" : "false");
    }

    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool SpriteBlur::initWithTexture(Texture2D* texture, const Rect& rect)
{
    _blurRadius = 0;
    if( Sprite::initWithTexture(texture, rect) ) 
    {
#if CC_ENABLE_CACHE_TEXTURE_DATA
        auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
                initProgram();
            });

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
        
        initProgram();

        return true;
    }

    return false;
}

void SpriteBlur::initProgram()
{
    std::string fragSource = FileUtils::getInstance()->getStringFromFile(
        FileUtils::getInstance()->fullPathForFilename("Shaders/example_Blur.fsh"));

    auto program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, fragSource.data());
    auto programState = new backend::ProgramState(program);
    setProgramState(programState);
    CC_SAFE_RELEASE(programState);
    CC_SAFE_RELEASE(program);
    
    auto size = getTexture()->getContentSizeInPixels();

    SET_UNIFORM(_programState, "resolution", size);
    SET_UNIFORM(_programState, "blurRadius", _blurRadius);
    SET_UNIFORM(_programState, "sampleNum", 7.0f);
    SET_UNIFORM(_programState, "u_PMatrix", Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION));
}

void SpriteBlur::setBlurRadius(float radius)
{
    _blurRadius = radius;
    SET_UNIFORM(_programState, "blurRadius", _blurRadius);
}

void SpriteBlur::setBlurSampleNum(float num)
{
    _blurSampleNum = num;
    SET_UNIFORM(_programState, "sampleNum", _blurSampleNum);
}

// ShaderBlur

ShaderBlur::ShaderBlur()
{
}

std::string ShaderBlur::title() const
{
    return "Shader: Frag shader";
}

std::string ShaderBlur::subtitle() const
{
     return "Gaussian blur";
}

void ShaderBlur::createSliderCtls()
{
    auto screenSize = Director::getInstance()->getWinSize();
    
    {
        ControlSlider *slider = ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
        slider->setAnchorPoint(Vec2(0.5f, 1.0f));
        slider->setMinimumValue(0.0f);
        slider->setMaximumValue(25.0f);
        slider->setScale(0.6f);
        slider->setPosition(Vec2(screenSize.width / 4.0f, screenSize.height / 3.0f + 24.0f));
        slider->addTargetWithActionForControlEvents(this, cccontrol_selector(ShaderBlur::onRadiusChanged), Control::EventType::VALUE_CHANGED);
        slider->setValue(2.0f);
        addChild(slider);
        _sliderRadiusCtl = slider;
        
        auto label = Label::createWithTTF("Blur Radius", "fonts/arial.ttf", 12.0f);
        addChild(label);
        label->setPosition(Vec2(screenSize.width / 4.0f, screenSize.height / 3.0f));
    }
    
    {
        ControlSlider *slider = ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
        slider->setAnchorPoint(Vec2(0.5f, 1.0f));
        slider->setMinimumValue(0.0f);
        slider->setMaximumValue(11.0f);
        slider->setScale(0.6f);
        slider->setPosition(Vec2(screenSize.width / 4.0f, screenSize.height / 3.0f - 10.0f));
        slider->addTargetWithActionForControlEvents(this, cccontrol_selector(ShaderBlur::onSampleNumChanged), Control::EventType::VALUE_CHANGED);
        slider->setValue(7.0f);
        addChild(slider);
        _sliderNumCtrl = slider;
        
        auto label = Label::createWithTTF("Blur Sample Num", "fonts/arial.ttf", 12.0f);
        addChild(label);
        label->setPosition(Vec2(screenSize.width / 4.0f, screenSize.height / 3.0f - 34.0f));
    }
 
}

bool ShaderBlur::init()
{
    if( ShaderTestDemo::init() ) 
    {
        _blurSprite = SpriteBlur::create("Images/grossini.png");
        auto sprite = Sprite::create("Images/grossini.png");
        auto s = Director::getInstance()->getWinSize();
        _blurSprite->setPosition(Vec2(s.width/3, s.height/2 + 30.0f));
        sprite->setPosition(Vec2(2*s.width/3, s.height/2 + 30.0f));

        addChild(_blurSprite);
        addChild(sprite);
        
        auto label = Label::createWithTTF("Normal Sprite", "fonts/arial.ttf", 12.0f);
        addChild(label);
        label->setPosition(Vec2(2*s.width/3, s.height/3.0f));
        createSliderCtls();
        
        return true;
    }

    return false;
}

void ShaderBlur::onRadiusChanged(Ref* sender, Control::EventType)
{
    ControlSlider* slider = (ControlSlider*)sender;
    _blurSprite->setBlurRadius(slider->getValue());
}

void ShaderBlur::onSampleNumChanged(Ref* sender, Control::EventType)
{
    ControlSlider* slider = (ControlSlider*)sender;
    _blurSprite->setBlurSampleNum(slider->getValue());
}

// ShaderRetroEffect

ShaderRetroEffect::ShaderRetroEffect()
: _label(nullptr)
, _accum(0.0f)
{
}

bool ShaderRetroEffect::init()
{
    if( ShaderTestDemo::init() ) {
        
        auto fragStr = FileUtils::getInstance()->getStringFromFile(FileUtils::getInstance()->fullPathForFilename("Shaders/example_HorizontalColor.fsh"));
        char * fragSource = (char*)fragStr.c_str();

        auto program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, fragSource);
        auto p = new backend::ProgramState(program);
        auto director = Director::getInstance();
        const auto& screenSizeLocation = p->getUniformLocation("u_screenSize");
        const auto& frameSize = director->getOpenGLView()->getFrameSize();
        float retinaFactor = director->getOpenGLView()->getRetinaFactor();
        auto screenSizeInPixels = frameSize * retinaFactor;
        p->setUniform(screenSizeLocation, &screenSizeInPixels, sizeof(screenSizeInPixels));
        
        auto s = director->getWinSize();

        _label = Label::createWithBMFont("fonts/west_england-64.fnt","RETRO EFFECT");
        _label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _label->setProgramState(p);
        CC_SAFE_RELEASE(p);

        _label->setPosition(Vec2(s.width/2,s.height/2));

        addChild(_label);

        scheduleUpdate();
        CC_SAFE_RELEASE(program);
        return true;
    }

    return false;
}

void ShaderRetroEffect::update(float dt)
{
    _accum += dt;
    int letterCount = _label->getStringLength();
    for (int i = 0; i < letterCount; ++i)
    {
        auto sprite = _label->getLetter(i);
        if (sprite != nullptr)
        {
            auto oldPosition = sprite->getPosition();
            sprite->setPosition(Vec2( oldPosition.x, sinf( _accum * 2 + i/2.0) * 20  ));
            
            // add fabs() to prevent negative scaling
            float scaleY = ( sinf( _accum * 2 + i/2.0 + 0.707) );
            
            sprite->setScaleY(scaleY);
        }
    }
}

std::string ShaderRetroEffect::title() const
{
    return "Shader: Retro test";
}

std::string ShaderRetroEffect::subtitle() const
{
    return "sin() effect with moving colors";
}


ShaderLensFlare::ShaderLensFlare()
{
}

std::string ShaderLensFlare::title() const
{
    return "ShaderToy Test";
}

std::string ShaderLensFlare::subtitle() const
{
    return "Lens Flare";
}

bool ShaderLensFlare::init()
{
    if (ShaderTestDemo::init())
    {
        auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/shadertoy_LensFlare.fsh");
        
        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Vec2(s.width/2, s.height/2));
        sn->setContentSize(Size(s.width/2,s.height/2));
        addChild(sn);
        
        return true;
    }
    
    return false;
}

//
// ShaderGlow
//
ShaderGlow::ShaderGlow()
{
}

std::string ShaderGlow::title() const
{
    return "ShaderToy Test";
}

std::string ShaderGlow::subtitle() const
{
    return "Glow";
}

bool ShaderGlow::init()
{
    if (ShaderTestDemo::init())
    {
        auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/shadertoy_Glow.fsh");
        
        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Vec2(s.width/2, s.height/2));
        sn->setContentSize(Size(s.width/2,s.height/2));
        addChild(sn);
        
        return true;
    }
    
    return false;
}

//
// ShaderMultiTexture
//
ShaderMultiTexture::ShaderMultiTexture():_changedTextureId(0)
{
}

std::string ShaderMultiTexture::title() const
{
    return "MultiTexture test";
}

std::string ShaderMultiTexture::subtitle() const
{
    return "MultiTexture";
}

ui::Slider* ShaderMultiTexture::createSliderCtl()
{
    auto screenSize = Director::getInstance()->getWinSize();

    ui::Slider* slider = ui::Slider::create();
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->setPercent(50);

    slider->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 3.0f));
    addChild(slider);

    slider->addEventListener([&](Ref* sender, ui::Slider::EventType type) {

        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
            ui::Slider* slider = dynamic_cast<ui::Slider*>(sender);
            float p = slider->getPercent() / 100.0f;
            auto state = _sprite->getProgramState();
            SET_UNIFORM(state, "u_interpolate", p);
        }
    });
    return slider;
}

bool ShaderMultiTexture::init()
{
    if (ShaderTestDemo::init())
    {
        auto s = Director::getInstance()->getWinSize();

        // Left: normal sprite
        auto left = Sprite::create("Images/grossinis_sister1.png");
        addChild(left);
        left->setPosition(s.width*1/4, s.height/2);

        // Right: normal sprite
        auto right = Sprite::create("Images/grossinis_sister2.png");
        addChild(right, 0, rightSpriteTag);
        right->setPosition(s.width*3/4, s.height/2);


        // Center: MultiTexture
        _sprite = Sprite::createWithTexture(left->getTexture());
        addChild(_sprite);
        _sprite->setPosition(Vec2(s.width/2, s.height/2));

        auto * fu = FileUtils::getInstance();
        auto vertexShader = fu->getStringFromFile("Shaders/example_MultiTexture.vsh");
        auto fragmentShader = fu->getStringFromFile("Shaders/example_MultiTexture.fsh");
        auto program = backend::Device::getInstance()->newProgram(vertexShader.c_str(), fragmentShader.c_str());
        auto programState = new backend::ProgramState(program);
        _sprite->setProgramState(programState);

        SET_TEXTURE(programState, "u_texture1", 1,  right->getTexture()->getBackendTexture());
        SET_UNIFORM(programState, "u_interpolate",0.5f);

        // slider
        createSliderCtl();
        
        // menu
        auto label = Label::createWithTTF(TTFConfig("fonts/arial.ttf"), "change");
        auto mi = MenuItemLabel::create(label, CC_CALLBACK_1(ShaderMultiTexture::changeTexture, this));
        auto menu = Menu::create(mi, nullptr);
        addChild(menu);
        menu->setPosition(s.width * 7 / 8, s.height / 2);

        CC_SAFE_RELEASE(programState);
        CC_SAFE_RELEASE(program);
        return true;
    }

    return false;
}

void ShaderMultiTexture::changeTexture(Ref*)
{
    static const int textureFilesCount = 3;
    static const std::string textureFiles[textureFilesCount] = {
        "Images/grossini.png",
        "Images/grossinis_sister1.png",
        "Images/grossinis_sister2.png"
    };
    auto texture = Director::getInstance()->getTextureCache()->addImage(textureFiles[_changedTextureId++ % textureFilesCount]);
    Sprite* right = dynamic_cast<Sprite*>(getChildByTag(rightSpriteTag));
    right->setTexture(texture);
    auto programState = _sprite->getProgramState();
    SET_TEXTURE(programState, "u_texture1", 1, right->getTexture()->getBackendTexture());
}
