#include "ShaderTest.h"
#include "../testResource.h"
#include "cocos2d.h"

static int sceneIdx = -1; 

#define MAX_LAYER    9

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
    case 8: return new ShaderFail();
    }

    return NULL;
}

static Layer* nextAction(void)
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* pLayer = createShaderLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

static Layer* backAction(void)
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    Layer* pLayer = createShaderLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

static Layer* restartAction(void)
{
    Layer* pLayer = createShaderLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}


ShaderTestDemo::ShaderTestDemo()
{

}

void ShaderTestDemo::backCallback(Object* pSender)
{
    Scene* s = new ShaderTestScene();
    s->addChild( backAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void ShaderTestDemo::nextCallback(Object* pSender)
{
    Scene* s = new ShaderTestScene();//CCScene::create();
    s->addChild( nextAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
}

std::string ShaderTestDemo::title()
{
    return "No title";
}

std::string ShaderTestDemo::subtitle()
{
    return "";
}

void ShaderTestDemo::restartCallback(Object* pSender)
{
    Scene* s = new ShaderTestScene();
    s->addChild(restartAction()); 

    Director::sharedDirector()->replaceScene(s);
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
:_center(vertex2(0.0f, 0.0f))
,_resolution(vertex2(0.0f, 0.0f))
,_time(0.0f)
,_uniformCenter(0)
,_uniformResolution(0)
,_uniformTime(0)
{
}

ShaderNode::~ShaderNode()
{
    NotificationCenter::sharedNotificationCenter()->removeObserver(this, EVNET_COME_TO_FOREGROUND);
}

ShaderNode* ShaderNode::shaderNodeWithVertex(const char *vert, const char *frag)
{
    ShaderNode *node = new ShaderNode();
    node->initWithVertex(vert, frag);
    node->autorelease();

    return node;
}

bool ShaderNode::initWithVertex(const char *vert, const char *frag)
{
    NotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                  callfuncO_selector(ShaderNode::listenBackToForeground),
                                                                  EVNET_COME_TO_FOREGROUND,
                                                                  NULL);

    loadShaderVertex(vert, frag);

    _time = 0;
    _resolution = vertex2(SIZE_X, SIZE_Y);

    scheduleUpdate();

    setContentSize(CCSizeMake(SIZE_X, SIZE_Y));
    setAnchorPoint(ccp(0.5f, 0.5f));
    
    _vertFileName = vert;
    _fragFileName = frag;

    return true;
}

void ShaderNode::listenBackToForeground(Object *obj)
{
    this->setShaderProgram(NULL);
    loadShaderVertex(_vertFileName.c_str(), _fragFileName.c_str());
}

void ShaderNode::loadShaderVertex(const char *vert, const char *frag)
{
    GLProgram *shader = new GLProgram();
    shader->initWithVertexShaderFilename(vert, frag);

    shader->addAttribute("aVertex", kVertexAttrib_Position);
    shader->link();

    shader->updateUniforms();

    _uniformCenter = glGetUniformLocation(shader->getProgram(), "center");
    _uniformResolution = glGetUniformLocation(shader->getProgram(), "resolution");
    _uniformTime = glGetUniformLocation(shader->getProgram(), "time");

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
    Point position = getPosition();
    _center = vertex2(position.x * CC_CONTENT_SCALE_FACTOR(), position.y * CC_CONTENT_SCALE_FACTOR());
}

void ShaderNode::draw()
{
    CC_NODE_DRAW_SETUP();

    float w = SIZE_X, h = SIZE_Y;
    GLfloat vertices[12] = {0,0, w,0, w,h, 0,0, 0,h, w,h};

    //
    // Uniforms
    //
    getShaderProgram()->setUniformLocationWith2f(_uniformCenter, _center.x, _center.y);
    getShaderProgram()->setUniformLocationWith2f(_uniformResolution, _resolution.x, _resolution.y);

    // time changes all the time, so it is Ok to call OpenGL directly, and not the "cached" version
    glUniform1f(_uniformTime, _time);

    ccGLEnableVertexAttribs( kVertexAttribFlag_Position );

    glVertexAttribPointer(kVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    CC_INCREMENT_GL_DRAWS(1);
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
        ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Monjori.vsh", "Shaders/example_Monjori.fsh");

        Size s = Director::sharedDirector()->getWinSize();
        sn->setPosition(ccp(s.width/2, s.height/2));

        addChild(sn);

        return true;
    }

    return false;
}

std::string ShaderMonjori::title()
{
    return "Shader: Frag shader";
}

std::string ShaderMonjori::subtitle()
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
        ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Mandelbrot.vsh", "Shaders/example_Mandelbrot.fsh");

        Size s = Director::sharedDirector()->getWinSize();
        sn->setPosition(ccp(s.width/2, s.height/2));

        addChild(sn);

        return true;
    }
    
    return false;
}

std::string ShaderMandelbrot::title()
{
    return "Shader: Frag shader";
}

std::string ShaderMandelbrot::subtitle()
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
        ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Julia.vsh", "Shaders/example_Julia.fsh");

        Size s = Director::sharedDirector()->getWinSize();
        sn->setPosition(ccp(s.width/2, s.height/2));

        addChild(sn);

        return true;
    }

    return false;
}

std::string ShaderJulia::title()
{
    return "Shader: Frag shader";
}

std::string ShaderJulia::subtitle()
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
        ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Heart.vsh", "Shaders/example_Heart.fsh");

        Size s = Director::sharedDirector()->getWinSize();
        sn->setPosition(ccp(s.width/2, s.height/2));

        addChild(sn);

        return true;
    }

    return false;
}

std::string ShaderHeart::title()
{
    return "Shader: Frag shader";
}

std::string ShaderHeart::subtitle()
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
        ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Flower.vsh", "Shaders/example_Flower.fsh");

        Size s = Director::sharedDirector()->getWinSize();
        sn->setPosition(ccp(s.width/2, s.height/2));

        addChild(sn);

        return true;
    }

    return false;
}

std::string ShaderFlower::title()
{
    return "Shader: Frag shader";
}

std::string ShaderFlower::subtitle()
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
        ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Plasma.vsh", "Shaders/example_Plasma.fsh");

        Size s = Director::sharedDirector()->getWinSize();
        sn->setPosition(ccp(s.width/2, s.height/2));

        addChild(sn);

        return true;
    }

    return false;
}

std::string ShaderPlasma::title()
{
    return "Shader: Frag shader";
}

std::string ShaderPlasma::subtitle()
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
    void draw();
    void initProgram();
    void listenBackToForeground(Object *obj);

    static SpriteBlur* create(const char *pszFileName);

    Point blur_;
    GLfloat    sub_[4];

    GLuint    blurLocation;
    GLuint    subLocation;
};

SpriteBlur::~SpriteBlur()
{
    NotificationCenter::sharedNotificationCenter()->removeObserver(this, EVNET_COME_TO_FOREGROUND);
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

void SpriteBlur::listenBackToForeground(Object *obj)
{
    setShaderProgram(NULL);
    initProgram();
}

bool SpriteBlur::initWithTexture(Texture2D* texture, const Rect& rect)
{
    if( Sprite::initWithTexture(texture, rect) ) 
    {
        NotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                      callfuncO_selector(SpriteBlur::listenBackToForeground),
                                                                      EVNET_COME_TO_FOREGROUND,
                                                                      NULL);
        
        Size s = getTexture()->getContentSizeInPixels();

        blur_ = ccp(1/s.width, 1/s.height);
        sub_[0] = sub_[1] = sub_[2] = sub_[3] = 0;

        this->initProgram();
        
        return true;
    }

    return false;
}

void SpriteBlur::initProgram()
{
    GLchar * fragSource = (GLchar*) String::createWithContentsOfFile(
                                FileUtils::sharedFileUtils()->fullPathForFilename("Shaders/example_Blur.fsh").c_str())->getCString();
    GLProgram* pProgram = new GLProgram();
    pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
    setShaderProgram(pProgram);
    pProgram->release();
    
    CHECK_GL_ERROR_DEBUG();
    
    getShaderProgram()->addAttribute(kAttributeNamePosition, kVertexAttrib_Position);
    getShaderProgram()->addAttribute(kAttributeNameColor, kVertexAttrib_Color);
    getShaderProgram()->addAttribute(kAttributeNameTexCoord, kVertexAttrib_TexCoords);
    
    CHECK_GL_ERROR_DEBUG();
    
    getShaderProgram()->link();
    
    CHECK_GL_ERROR_DEBUG();
    
    getShaderProgram()->updateUniforms();
    
    CHECK_GL_ERROR_DEBUG();
    
    subLocation = glGetUniformLocation( getShaderProgram()->getProgram(), "substract");
    blurLocation = glGetUniformLocation( getShaderProgram()->getProgram(), "blurSize");
    
    CHECK_GL_ERROR_DEBUG();
}

void SpriteBlur::draw()
{
    ccGLEnableVertexAttribs(kVertexAttribFlag_PosColorTex );
    ccBlendFunc blend = getBlendFunc();
    ccGLBlendFunc(blend.src, blend.dst);

    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();
    getShaderProgram()->setUniformLocationWith2f(blurLocation, blur_.x, blur_.y);
    getShaderProgram()->setUniformLocationWith4fv(subLocation, sub_, 1);

    ccGLBindTexture2D( getTexture()->getName());

    //
    // Attributes
    //
#define kQuadSize sizeof(_quad.bl)
    long offset = (long)&_quad;

    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CC_INCREMENT_GL_DRAWS(1);
}

void SpriteBlur::setBlurSize(float f)
{
    Size s = getTexture()->getContentSizeInPixels();

    blur_ = ccp(1/s.width, 1/s.height);
    blur_ = ccpMult(blur_,f);
}

// ShaderBlur

ShaderBlur::ShaderBlur()
{
    init();
}

std::string ShaderBlur::title()
{
    return "Shader: Frag shader";
}

std::string ShaderBlur::subtitle()
{
     return "Gaussian blur";
}

ControlSlider* ShaderBlur::createSliderCtl()
{
    Size screenSize = Director::sharedDirector()->getWinSize();

    ControlSlider *slider = ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
    slider->setAnchorPoint(ccp(0.5f, 1.0f));
    slider->setMinimumValue(0.0f); // Sets the min value of range
    slider->setMaximumValue(3.0f); // Sets the max value of range
    slider->setValue(1.0f);
    slider->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 3.0f));

    // When the value of the slider will change, the given selector will be call
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(ShaderBlur::sliderAction), ControlEventValueChanged);

    return slider;
 
}

bool ShaderBlur::init()
{
    if( ShaderTestDemo::init() ) 
    {
        _blurSprite = SpriteBlur::create("Images/grossini.png");

        Sprite *sprite = Sprite::create("Images/grossini.png");

        Size s = Director::sharedDirector()->getWinSize();
        _blurSprite->setPosition(ccp(s.width/3, s.height/2));
        sprite->setPosition(ccp(2*s.width/3, s.height/2));

        addChild(_blurSprite);
        addChild(sprite);

        _sliderCtl = createSliderCtl();

        addChild(_sliderCtl);
        return true;
    }

    return false;
}

void ShaderBlur::sliderAction(Object* sender, ControlEvent controlEvent)
{
    ControlSlider* pSlider = (ControlSlider*)sender;
    _blurSprite->setBlurSize(pSlider->getValue());
}

// ShaderRetroEffect

ShaderRetroEffect::ShaderRetroEffect()
: _label(NULL)
, _accum(0.0f)
{
    init();
}

bool ShaderRetroEffect::init()
{
    if( ShaderTestDemo::init() ) {

        GLchar * fragSource = (GLchar*) String::createWithContentsOfFile(FileUtils::sharedFileUtils()->fullPathForFilename("Shaders/example_HorizontalColor.fsh").c_str())->getCString();
        GLProgram *p = new GLProgram();
        p->initWithVertexShaderByteArray(ccPositionTexture_vert, fragSource);

        p->addAttribute(kAttributeNamePosition, kVertexAttrib_Position);
        p->addAttribute(kAttributeNameTexCoord, kVertexAttrib_TexCoords);

        p->link();
        p->updateUniforms();


        Director *director = Director::sharedDirector();
        Size s = director->getWinSize();

        _label = LabelBMFont::create("RETRO EFFECT", "fonts/west_england-64.fnt");

        _label->setShaderProgram(p);

        p->release();


        _label->setPosition(ccp(s.width/2,s.height/2));

        addChild(_label);

        scheduleUpdate();
        return true;
    }

    return false;
}

void ShaderRetroEffect::update(float dt)
{
    _accum += dt;

    Array* pArray = _label->getChildren();

    int i=0;
    Object* pObj = NULL;
    CCARRAY_FOREACH(pArray, pObj)
    {
        Sprite *sprite = (Sprite*)pObj;
        i++;
        Point oldPosition = sprite->getPosition();
        sprite->setPosition(ccp( oldPosition.x, sinf( _accum * 2 + i/2.0) * 20  ));

        // add fabs() to prevent negative scaling
        float scaleY = ( sinf( _accum * 2 + i/2.0 + 0.707) );

        sprite->setScaleY(scaleY);
    }
}

std::string ShaderRetroEffect::title()
{
    return "Shader: Retro test";
}

std::string ShaderRetroEffect::subtitle()
{
    return "sin() effect with moving colors";
}

// ShaderFail
const GLchar *shader_frag_fail = "\n\
#ifdef GL_ES					\n\
precision lowp float;			\n\
#endif							\n\
\n\
varying vec2 v_texCoord;				\n\
uniform sampler2D CC_Texture0;			\n\
\n\
vec4 colors[10];						\n\
\n\
void main(void)								\n\
{											\n\
colors[0] = vec4(1,0,0,1);				\n\
colors[1] = vec4(0,1,0,1);				\n\
colors[2] = vec4(0,0,1,1);				\n\
colors[3] = vec4(0,1,1,1);				\n\
colors[4] = vec4(1,0,1,1);				\n\
colors[5] = vec4(1,1,0,1);				\n\
colors[6] = vec4(1,1,1,1);				\n\
colors[7] = vec4(1,0.5,0,1);			\n\
colors[8] = vec4(1,0.5,0.5,1);			\n\
colors[9] = vec4(0.5,0.5,1,1);			\n\
\n\
int y = int( mod(gl_FragCoord.y / 3.0, 10.0 ) );						\n\
gl_FragColor = colors[z] * texture2D(CC_Texture0, v_texCoord);			\n\
}																			\n\
\n";

ShaderFail::ShaderFail()
{
    GLProgram *p = new GLProgram();
    p->initWithVertexShaderByteArray(ccPositionTexture_vert, shader_frag_fail);
    
    p->addAttribute(kAttributeNamePosition, kVertexAttrib_Position);
    p->addAttribute(kAttributeNameTexCoord, kVertexAttrib_TexCoords);
    
    p->link();
    p->updateUniforms();
    p->release();
}

string ShaderFail::title()
{
    return "Shader: Invalid shader";
}

string ShaderFail::subtitle()
{
    return "See console for output with useful error log";
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

    Director::sharedDirector()->replaceScene(this);
}
