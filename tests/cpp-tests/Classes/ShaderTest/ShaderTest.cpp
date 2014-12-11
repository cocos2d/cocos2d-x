#include "ShaderTest.h"
#include "../testResource.h"
#include "cocos2d.h"

static int sceneIdx = -1; 

#define MAX_LAYER    11

static Layer* createShaderLayer(int nIndex)
{
    switch (sceneIdx)
    {
        case 0: return new ShaderLensFlare();
        case 1: return new ShaderMandelbrot();
        case 2: return new ShaderJulia();
        case 3: return new ShaderHeart();
        case 4: return new ShaderFlower();
        case 5: return new ShaderPlasma();
        case 6: return new ShaderBlur();
        case 7: return new ShaderRetroEffect();
        case 8: return new ShaderMonjori();
        case 9: return new ShaderGlow();
        case 10: return new ShaderMultiTexture();
    }
    return nullptr;
}

static Layer* nextAction(void)
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = createShaderLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

static Layer* backAction(void)
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    auto layer = createShaderLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

static Layer* restartAction(void)
{
    auto layer = createShaderLayer(sceneIdx);
    layer->autorelease();

    return layer;
}


ShaderTestDemo::ShaderTestDemo()
{

}

void ShaderTestDemo::backCallback(Ref* sender)
{
    auto s = new (std::nothrow) ShaderTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ShaderTestDemo::nextCallback(Ref* sender)
{
    auto s = new (std::nothrow) ShaderTestScene();//CCScene::create();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

std::string ShaderTestDemo::title() const
{
    return "No title";
}

std::string ShaderTestDemo::subtitle() const
{
    return "";
}

void ShaderTestDemo::restartCallback(Ref* sender)
{
    auto s = new (std::nothrow) ShaderTestScene();
    s->addChild(restartAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();    
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
#if CC_ENABLE_CACHE_TEXTURE_DATA
    auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
            this->setGLProgramState(nullptr);
            loadShaderVertex(_vertFileName, _fragFileName);
        });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif

    _vertFileName = vert;
    _fragFileName = frag;

    loadShaderVertex(vert, frag);

    _time = 0;
    _resolution = Vec2(SIZE_X, SIZE_Y);
    getGLProgramState()->setUniformVec2("resolution", _resolution);

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
    } else {
        std::string vertexFilePath = fileUtiles->fullPathForFilename(vert);
        vertSource = fileUtiles->getStringFromFile(vertexFilePath);
    }

    auto glprogram = GLProgram::createWithByteArrays(vertSource.c_str(), fragSource.c_str());
    auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
    setGLProgramState(glprogramstate);
}

void ShaderNode::update(float dt)
{
    _time += dt;
}

void ShaderNode::setPosition(const Vec2 &newPosition)
{
    Node::setPosition(newPosition);
    auto position = getPosition();
    _center = Vec2(position.x * CC_CONTENT_SCALE_FACTOR(), position.y * CC_CONTENT_SCALE_FACTOR());
    getGLProgramState()->setUniformVec2("center", _center);
}

void ShaderNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(ShaderNode::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void ShaderNode::onDraw(const Mat4 &transform, uint32_t flags)
{
    float w = SIZE_X, h = SIZE_Y;
    GLfloat vertices[12] = {0,0, w,0, w,h, 0,0, 0,h, w,h};

    auto glProgramState = getGLProgramState();
    glProgramState->setVertexAttribPointer("a_position", 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glProgramState->apply(transform);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,6);
}

/// ShaderMonjori

ShaderMonjori::ShaderMonjori()
{
    init();
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
    init();
}

bool ShaderMandelbrot::init()
{
    if (ShaderTestDemo::init())
    {
#if CC_TARGET_PLATFORM != CC_PLATFORM_WINRT && CC_TARGET_PLATFORM != CC_PLATFORM_WP8
        auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/example_Mandelbrot.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Vec2(s.width/2, s.height/2));

        addChild(sn);
#endif
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
    init();
}

bool ShaderJulia::init()
{
    if (ShaderTestDemo::init())
    {
#if CC_TARGET_PLATFORM != CC_PLATFORM_WINRT && CC_TARGET_PLATFORM != CC_PLATFORM_WP8
        auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/example_Julia.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Vec2(s.width/2, s.height/2));

        addChild(sn);
#endif
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
    init();
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
    init();
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
    init();
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
    void initGLProgram();

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
                setGLProgram(nullptr);
                initGLProgram();
            });

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
        
        initGLProgram();

        return true;
    }

    return false;
}

void SpriteBlur::initGLProgram()
{
    GLchar * fragSource = (GLchar*) String::createWithContentsOfFile(
                                FileUtils::getInstance()->fullPathForFilename("Shaders/example_Blur.fsh").c_str())->getCString();  
    auto program = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource);

    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
    setGLProgramState(glProgramState);
    
    auto size = getTexture()->getContentSizeInPixels();
    getGLProgramState()->setUniformVec2("resolution", size);
    getGLProgramState()->setUniformFloat("blurRadius", _blurRadius);
    getGLProgramState()->setUniformFloat("sampleNum", 7.0f);
}

void SpriteBlur::setBlurRadius(float radius)
{
    _blurRadius = radius;
    getGLProgramState()->setUniformFloat("blurRadius", _blurRadius);
}

void SpriteBlur::setBlurSampleNum(float num)
{
    _blurSampleNum = num;
    getGLProgramState()->setUniformFloat("sampleNum", _blurSampleNum);
}

// ShaderBlur

ShaderBlur::ShaderBlur()
{
    init();
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
        slider->setPosition(Vec2(screenSize.width / 4.0f, screenSize.height / 3.0f));
        slider->addTargetWithActionForControlEvents(this, cccontrol_selector(ShaderBlur::onRadiusChanged), Control::EventType::VALUE_CHANGED);
        slider->setValue(2.0f);
        addChild(slider);
        _sliderRadiusCtl = slider;
        
        auto label = Label::createWithTTF("Blur Radius", "fonts/arial.ttf", 12.0f);
        addChild(label);
        label->setPosition(Vec2(screenSize.width / 4.0f, screenSize.height / 3.0f - 24.0f));
    }
    
    {
        ControlSlider *slider = ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
        slider->setAnchorPoint(Vec2(0.5f, 1.0f));
        slider->setMinimumValue(0.0f);
        slider->setMaximumValue(11.0f);
        slider->setScale(0.6f);
        slider->setPosition(Vec2(screenSize.width * 3 / 4.0f, screenSize.height / 3.0f));
        slider->addTargetWithActionForControlEvents(this, cccontrol_selector(ShaderBlur::onSampleNumChanged), Control::EventType::VALUE_CHANGED);
        slider->setValue(7.0f);
        addChild(slider);
        _sliderNumCtrl = slider;
        
        auto label = Label::createWithTTF("Blur Sample Num", "fonts/arial.ttf", 12.0f);
        addChild(label);
        label->setPosition(Vec2(screenSize.width * 3 / 4.0f, screenSize.height / 3.0f - 24.0f));
    }
 
}

bool ShaderBlur::init()
{
    if( ShaderTestDemo::init() ) 
    {
#if CC_TARGET_PLATFORM != CC_PLATFORM_WINRT && CC_TARGET_PLATFORM != CC_PLATFORM_WP8
        _blurSprite = SpriteBlur::create("Images/grossini.png");
        auto sprite = Sprite::create("Images/grossini.png");
        auto s = Director::getInstance()->getWinSize();
        _blurSprite->setPosition(Vec2(s.width/3, s.height/2));
        sprite->setPosition(Vec2(2*s.width/3, s.height/2));

        addChild(_blurSprite);
        addChild(sprite);

        createSliderCtls();
#endif
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
    init();
}

bool ShaderRetroEffect::init()
{
    if( ShaderTestDemo::init() ) {

        GLchar * fragSource = (GLchar*) String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("Shaders/example_HorizontalColor.fsh"))->getCString();
        auto p = GLProgram::createWithByteArrays(ccPositionTexture_vert, fragSource);

        auto director = Director::getInstance();
        auto s = director->getWinSize();

        _label = Label::createWithBMFont("fonts/west_england-64.fnt","RETRO EFFECT");
        _label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _label->setGLProgram(p);

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
        auto oldPosition = sprite->getPosition();
        sprite->setPosition(Vec2( oldPosition.x, sinf( _accum * 2 + i/2.0) * 20  ));
        
        // add fabs() to prevent negative scaling
        float scaleY = ( sinf( _accum * 2 + i/2.0 + 0.707) );
        
        sprite->setScaleY(scaleY);
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
    init();
}

std::string ShaderLensFlare::title() const
{
    return "ShaderToy Test";
}

std::string ShaderLensFlare::subtitle() const
{
    return "Lens Flare	";
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
    init();
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
    init();
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
            _sprite->getGLProgramState()->setUniformFloat("u_interpolate",p);
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

        auto glprogram = GLProgram::createWithFilenames("Shaders/example_MultiTexture.vsh", "Shaders/example_MultiTexture.fsh");
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        _sprite->setGLProgramState(glprogramstate);

        glprogramstate->setUniformTexture("u_texture1", right->getTexture());
        glprogramstate->setUniformFloat("u_interpolate",0.5);

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
    auto textrue = Director::getInstance()->getTextureCache()->addImage(textureFiles[_changedTextureId++ % textureFilesCount]);
    Sprite* right = dynamic_cast<Sprite*>(getChildByTag(rightSpriteTag));
    right->setTexture(textrue);
    auto programState = _sprite->getGLProgramState();
    programState->setUniformTexture("u_texture1", right->getTexture());
}


///---------------------------------------
//
// ShaderTestScene
// 
///---------------------------------------
void ShaderTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());

    Director::getInstance()->replaceScene(this);
}
