#include "ShaderTest.h"
#include "../testResource.h"
#include "cocos2d.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCRenderer.h"

static int sceneIdx = -1; 

#define MAX_LAYER    8

static Layer* createShaderLayer(int nIndex)
{
    switch (sceneIdx)
    {
    case 0: return new ShaderMonjori();
    case 1: return new ShaderMandelbrot();
    case 2: return new ShaderJulia();
    case 3: return new ShaderHeart();
    case 4: return new ShaderFlower();
    case 5: return new ShaderPlasma();
    case 6: return new ShaderBlur();
    case 7: return new ShaderRetroEffect();
    }

    return NULL;
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
    auto s = new ShaderTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ShaderTestDemo::nextCallback(Ref* sender)
{
    auto s = new ShaderTestScene();//CCScene::create();
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
    auto s = new ShaderTestScene();
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
:_center(Vertex2F(0.0f, 0.0f))
,_resolution(Vertex2F(0.0f, 0.0f))
,_time(0.0f)
,_uniformCenter(0)
,_uniformResolution(0)
,_uniformTime(0)
{
}

ShaderNode::~ShaderNode()
{
}

ShaderNode* ShaderNode::shaderNodeWithVertex(const char *vert, const char *frag)
{
    auto node = new ShaderNode();
    node->initWithVertex(vert, frag);
    node->autorelease();

    return node;
}

bool ShaderNode::initWithVertex(const char *vert, const char *frag)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
            this->setShaderProgram(nullptr);
            loadShaderVertex(_vertFileName.c_str(), _fragFileName.c_str());
        });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif

    loadShaderVertex(vert, frag);

    _time = 0;
    _resolution = Vertex2F(SIZE_X, SIZE_Y);

    scheduleUpdate();

    setContentSize(Size(SIZE_X, SIZE_Y));
    setAnchorPoint(Point(0.5f, 0.5f));
    
    _vertFileName = vert;
    _fragFileName = frag;

    return true;
}

void ShaderNode::loadShaderVertex(const char *vert, const char *frag)
{
    auto shader = new GLProgram();
    shader->initWithFilenames(vert, frag);

    shader->bindAttribLocation("aVertex", GLProgram::VERTEX_ATTRIB_POSITION);
    shader->link();

    shader->updateUniforms();

    _uniformCenter = shader->getUniformLocation("center");
    _uniformResolution = shader->getUniformLocation("resolution");
    _uniformTime = shader->getUniformLocation("time");

    this->setShaderProgram(shader);

    shader->release();
}

void ShaderNode::update(float dt)
{
    _time += dt;
}

void ShaderNode::setPosition(const Point &newPosition)
{
    Node::setPosition(newPosition);
    auto position = getPosition();
    _center = Vertex2F(position.x * CC_CONTENT_SCALE_FACTOR(), position.y * CC_CONTENT_SCALE_FACTOR());
}

void ShaderNode::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(ShaderNode::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void ShaderNode::onDraw(const kmMat4 &transform, bool transformUpdated)
{
    auto shader = getShaderProgram();
    shader->use();
    shader->setUniformsForBuiltins(transform);
    shader->setUniformLocationWith2f(_uniformCenter, _center.x, _center.y);
    shader->setUniformLocationWith2f(_uniformResolution, _resolution.x, _resolution.y);
    
    // time changes all the time, so it is Ok to call OpenGL directly, and not the "cached" version
    glUniform1f(_uniformTime, _time);
    
    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );

    float w = SIZE_X, h = SIZE_Y;
    GLfloat vertices[12] = {0,0, w,0, w,h, 0,0, 0,h, w,h};

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    
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
        auto sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Monjori.vsh", "Shaders/example_Monjori.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Point(s.width/2, s.height/2));

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
        auto sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Mandelbrot.vsh", "Shaders/example_Mandelbrot.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Point(s.width/2, s.height/2));

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
    init();
}

bool ShaderJulia::init()
{
    if (ShaderTestDemo::init())
    {
        auto sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Julia.vsh", "Shaders/example_Julia.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Point(s.width/2, s.height/2));

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
    init();
}

bool ShaderHeart::init()
{
    if (ShaderTestDemo::init())
    {
        auto sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Heart.vsh", "Shaders/example_Heart.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Point(s.width/2, s.height/2));

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
        auto sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Flower.vsh", "Shaders/example_Flower.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Point(s.width/2, s.height/2));

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
        auto sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Plasma.vsh", "Shaders/example_Plasma.fsh");

        auto s = Director::getInstance()->getWinSize();
        sn->setPosition(Point(s.width/2, s.height/2));

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
    void setBlurSize(float f);
    bool initWithTexture(Texture2D* texture, const Rect&  rect);
    virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;
    void initProgram();

    static SpriteBlur* create(const char *pszFileName);

protected:
    void onDraw(const kmMat4 &transform, bool transformUpdated);

    int       _blurRadius;
    Point     _pixelSize;

    int       _samplingRadius;
    //gaussian = cons * exp( (dx*dx + dy*dy) * scale);
    float     _scale;
    float     _cons;
    float     _weightSum;

    GLuint    pixelSizeLocation;
    GLuint    coefficientLocation;

    CustomCommand _customCommand;
};

SpriteBlur::~SpriteBlur()
{
}

SpriteBlur* SpriteBlur::create(const char *pszFileName)
{
    SpriteBlur* pRet = new SpriteBlur();
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
        auto listener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
                setShaderProgram(nullptr);
                initProgram();
            });

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
        
        auto s = getTexture()->getContentSizeInPixels();

        _pixelSize = Point(1/s.width, 1/s.height);
        _samplingRadius = 0;
        this->initProgram();

        return true;
    }

    return false;
}

void SpriteBlur::initProgram()
{
    GLchar * fragSource = (GLchar*) String::createWithContentsOfFile(
                                FileUtils::getInstance()->fullPathForFilename("Shaders/example_Blur.fsh").c_str())->getCString();  
    auto program = new GLProgram();
    program->initWithByteArrays(ccPositionTextureColor_vert, fragSource);
    setShaderProgram(program);
    program->release();
    
    CHECK_GL_ERROR_DEBUG();
    
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    program->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

    CHECK_GL_ERROR_DEBUG();
    
    program->link();
    
    CHECK_GL_ERROR_DEBUG();
    
    program->updateUniforms();
    
    CHECK_GL_ERROR_DEBUG();
    
    pixelSizeLocation = program->getUniformLocation("onePixelSize");
    coefficientLocation = program->getUniformLocation("gaussianCoefficient");

    CHECK_GL_ERROR_DEBUG();
}

void SpriteBlur::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(SpriteBlur::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void SpriteBlur::onDraw(const kmMat4 &transform, bool transformUpdated)
{
    GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
    BlendFunc blend = getBlendFunc();
    GL::blendFunc(blend.src, blend.dst);

    auto program = getShaderProgram();
    program->use();
    program->setUniformsForBuiltins(transform);
    program->setUniformLocationWith2f(pixelSizeLocation, _pixelSize.x, _pixelSize.y);
    program->setUniformLocationWith4f(coefficientLocation, _samplingRadius, _scale,_cons,_weightSum);
    
    GL::bindTexture2D( getTexture()->getName());
    
    //
    // Attributes
    //
    #define kQuadSize sizeof(_quad.bl)
    size_t offset = (size_t)&_quad;
    
    // vertex
    int diff = offsetof( V3F_C4B_T2F, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    // texCoods
    diff = offsetof( V3F_C4B_T2F, texCoords);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( V3F_C4B_T2F, colors);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,4);
}

void SpriteBlur::setBlurSize(float f)
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
    log("_blurRadius:%d",_blurRadius);
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

ControlSlider* ShaderBlur::createSliderCtl()
{
    auto screenSize = Director::getInstance()->getWinSize();
    
    ControlSlider *slider = ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
    slider->setAnchorPoint(Point(0.5f, 1.0f));
    slider->setMinimumValue(0.0f); // Sets the min value of range
    slider->setMaximumValue(25.0f); // Sets the max value of range
    
    slider->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 3.0f));

    // When the value of the slider will change, the given selector will be call
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(ShaderBlur::sliderAction), Control::EventType::VALUE_CHANGED);
    slider->setValue(2.0f);

    return slider;
 
}

bool ShaderBlur::init()
{
    if( ShaderTestDemo::init() ) 
    {
        _blurSprite = SpriteBlur::create("Images/grossini.png");

        auto sprite = Sprite::create("Images/grossini.png");

        auto s = Director::getInstance()->getWinSize();
        _blurSprite->setPosition(Point(s.width/3, s.height/2));
        sprite->setPosition(Point(2*s.width/3, s.height/2));

        addChild(_blurSprite);
        addChild(sprite);

        _sliderCtl = createSliderCtl();

        addChild(_sliderCtl);
        return true;
    }

    return false;
}

void ShaderBlur::sliderAction(Ref* sender, Control::EventType controlEvent)
{
    ControlSlider* pSlider = (ControlSlider*)sender;
    _blurSprite->setBlurSize(pSlider->getValue());
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

        GLchar * fragSource = (GLchar*) String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("Shaders/example_HorizontalColor.fsh").c_str())->getCString();
        auto p = new GLProgram();
        p->initWithByteArrays(ccPositionTexture_vert, fragSource);

        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

        p->link();
        p->updateUniforms();

        auto director = Director::getInstance();
        auto s = director->getWinSize();

        _label = Label::createWithBMFont("fonts/west_england-64.fnt","RETRO EFFECT");
        _label->setAnchorPoint(Point::ANCHOR_MIDDLE);
        _label->setShaderProgram(p);

        p->release();

        _label->setPosition(Point(s.width/2,s.height/2));

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
        sprite->setPosition(Point( oldPosition.x, sinf( _accum * 2 + i/2.0) * 20  ));
        
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
