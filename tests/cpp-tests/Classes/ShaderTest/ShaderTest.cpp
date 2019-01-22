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

#include "renderer/backend/ProgramState.h"

USING_NS_CC;
USING_NS_CC_EXT;

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

const std::string COCOS2D_SHADER_UNIFORMS =
"uniform mat4 CC_PMatrix;\n"
"uniform mat4 CC_MultiViewPMatrix[4];\n"
"uniform mat4 CC_MVMatrix;\n"
"uniform mat4 CC_MVPMatrix;\n"
"uniform mat4 CC_MultiViewMVPMatrix[4];\n"
"uniform mat3 CC_NormalMatrix;\n"
"uniform vec4 CC_Time;\n"
"uniform vec4 CC_SinTime;\n"
"uniform vec4 CC_CosTime;\n"
"uniform vec4 CC_Random01;\n"
"uniform sampler2D CC_Texture0;\n"
"uniform sampler2D CC_Texture1;\n"
"uniform sampler2D CC_Texture2;\n"
"uniform sampler2D CC_Texture3;\n"
"//CC INCLUDES END\n\n";


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
#if CC_ENABLE_CACHE_TEXTURE_DATA
    auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
            this->setGLProgramState(nullptr);
            loadShaderVertex(_vertFileName, _fragFileName);
        });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif

    loadShaderVertex(vert, frag);

    _time = 0;
    _resolution = Vec2(SIZE_X, SIZE_Y);

    scheduleUpdate();

    setContentSize(Size(SIZE_X, SIZE_Y));
    setAnchorPoint(Vec2(0.5f, 0.5f));
    

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
        vertSource = ccPositionTextureColor_vert;
        vertSource = COCOS2D_SHADER_UNIFORMS + "\n" + vertSource;
    } else {
        std::string vertexFilePath = fileUtiles->fullPathForFilename(vert);
        vertSource = fileUtiles->getStringFromFile(vertexFilePath);
    }

    auto &pipelineDescriptor = _customCommand.getPipelineDescriptor();
    auto programState = new backend::ProgramState(vertSource, fragSource);
    CC_SAFE_RELEASE(pipelineDescriptor.programState);
    pipelineDescriptor.programState = programState;
    
    auto &vertexLayout = pipelineDescriptor.vertexLayout;
    vertexLayout.setAtrribute("a_position", 0, backend::VertexFormat::FLOAT_R32G32, 0, false);
    vertexLayout.setLayout(2 * sizeof(float), backend::VertexStepMode::VERTEX);

    _customCommand.createVertexBuffer(sizeof(float) * 2, 6, CustomCommand::BufferUsage::STATIC);
    _customCommand.createIndexBuffer(CustomCommand::IndexFormat::U_SHORT, 6, CustomCommand::BufferUsage::STATIC);

    float w = SIZE_X, h = SIZE_Y;
    GLfloat vertices[12] = { 0,0, w,0, w,h, 0,0, w, h, 0,h };
    uint16_t indices[6] = { 0, 1, 2, 3, 4, 5 };

    _customCommand.updateVertexBuffer(vertices, 12 * sizeof(float));
    _customCommand.updateIndexBuffer(indices, sizeof(uint16_t) * 6);
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
    //_customCommand.func = CC_CALLBACK_0(ShaderNode::onDraw, this, transform, flags);
    onDraw(transform, flags);

    renderer->addCommand(&_customCommand);
}

void ShaderNode::onDraw(const Mat4 &transform, uint32_t flags)
{
    float w = SIZE_X, h = SIZE_Y;
    GLfloat vertices[12] = {0,0, w,0, w,h, 0,0, 0,h, w,h};

    const cocos2d::Mat4& projectionMat = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Mat4 finalMat = projectionMat * transform;

    auto programState = _customCommand.getPipelineDescriptor().programState;
    auto mvp = programState->getUniformLocation("CC_MVPMatrix");
    auto resolution = programState->getUniformLocation("resolution");
    auto center = programState->getUniformLocation("center");

    float timeValue[4] = { _time, _time, _time, _time};
    auto cctime = programState->getUniformLocation("CC_Time");

    programState->setUniform(mvp, &finalMat.m, sizeof(finalMat.m));
    programState->setUniform(resolution, &_resolution, sizeof(_resolution));
    programState->setUniform(center, &_center, sizeof(_center));
    programState->setUniform(cctime, &timeValue, sizeof(timeValue));

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,6);
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
    void initCustomCommand();

    static SpriteBlur* create(const char *pszFileName);
    void setBlurRadius(float radius);
    void setBlurSampleNum(float num);

protected:
    float _blurRadius;
    float _blurSampleNum;
   // cocos2d::CustomCommand _command;
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
                initGLProgram();
            });

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
        
        initCustomCommand();

        return true;
    }

    return false;
}

void SpriteBlur::initCustomCommand()
{
    std::string fragSource = FileUtils::getInstance()->getStringFromFile(
        FileUtils::getInstance()->fullPathForFilename("Shaders/example_Blur.fsh"));

    //auto vertexShader = positionTextureColor_noMVP_vert;
    this->updateShaders(positionTextureColor_noMVP_vert, fragSource.c_str());

    auto pipelineDescriptor = _trianglesCommand.getPipelineDescriptor();
    auto programState = pipelineDescriptor.programState;

    auto resolution = programState->getUniformLocation("resolution");
    auto blurRadius = programState->getUniformLocation("blurRadius"); 
    auto sampleNum = programState->getUniformLocation("sampleNum");

    auto size = getTexture()->getContentSizeInPixels();
    float sampleNumValue = 7.0f;

    programState->setUniform(resolution, &size, sizeof(size));
    programState->setUniform(blurRadius, &_blurRadius, sizeof(_blurRadius));
    programState->setUniform(sampleNum, &sampleNumValue, sizeof(sampleNumValue));

    programState->setTexture(_textureLocation, 0, _texture->getBackendTexture());
}

void SpriteBlur::setBlurRadius(float radius)
{
    _blurRadius = radius;
    auto programState = _trianglesCommand.getPipelineDescriptor().programState;
    auto blurRadius = programState->getUniformLocation("blurRadius");
    programState->setUniform(blurRadius, &_blurRadius, sizeof(_blurRadius));
}

void SpriteBlur::setBlurSampleNum(float num)
{
    _blurSampleNum = num;
    auto programState = _trianglesCommand.getPipelineDescriptor().programState;
    auto sampleNum = programState->getUniformLocation("sampleNum");
    programState->setUniform(sampleNum, &_blurSampleNum, sizeof(_blurSampleNum));
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
        GLchar * fragSource = (GLchar*)fragStr.c_str();

        auto director = Director::getInstance();
        auto s = director->getWinSize();

        _label = Label::createWithBMFont("fonts/west_england-64.fnt","RETRO EFFECT");
        _label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _label->updateShaderProgram(positionTextureColor_noMVP_vert, fragSource);

        _label->setPosition(Vec2(s.width/2,s.height/2));

        addChild(_label);

        scheduleUpdate();
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
            auto *command = (cocos2d::TrianglesCommand*) _sprite->getRenderCommand();
            auto &programState = command->getPipelineDescriptor().programState;
            auto interpolate = programState->getUniformLocation("u_interpolate");
            programState->setUniform(interpolate, &p, sizeof(p));

        }
    });
    return slider;
}

bool ShaderMultiTexture::init()
{
    if (ShaderTestDemo::init())
    {
        auto s = Director::getInstance()->getWinSize();

        auto fu = FileUtils::getInstance();

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

        auto vertexShaderContent = fu->getDataFromFile("Shaders/example_MultiTexture.vsh").toString();
        auto fragmentShaderContent = fu->getDataFromFile("Shaders/example_MultiTexture.fsh").toString();

        _sprite->updateShaders((const char *)vertexShaderContent.c_str(), (const char *)fragmentShaderContent.c_str());

        auto *command = (cocos2d::TrianglesCommand*) _sprite->getRenderCommand();

        auto &programState = command->getPipelineDescriptor().programState;
        auto u_texture1 = programState->getUniformLocation("u_texture1");
        auto interpolate = programState->getUniformLocation("u_interpolate");

        float interpolateValue = 0.5f;
        programState->setUniform(interpolate, &interpolateValue, sizeof(interpolateValue));
        programState->setTexture(u_texture1, 1, right->getTexture()->getBackendTexture());

        // slider
        createSliderCtl();
        
        // menu
        auto label = Label::createWithTTF(TTFConfig("fonts/arial.ttf"), "change");
        auto mi = MenuItemLabel::create(label, CC_CALLBACK_1(ShaderMultiTexture::changeTexture, this));
        auto menu = Menu::create(mi, nullptr);
        addChild(menu);
        menu->setPosition(s.width * 7 / 8, s.height / 2);

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
    
    auto *command = (cocos2d::TrianglesCommand*) _sprite->getRenderCommand();

    auto &programState = command->getPipelineDescriptor().programState;
    auto u_texture1 = programState->getUniformLocation("u_texture1");;
    programState->setTexture(u_texture1, 1, right->getTexture()->getBackendTexture());

}
