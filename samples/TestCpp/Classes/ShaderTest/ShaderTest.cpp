#include "ShaderTest.h"
#include "../testResource.h"
#include "cocos2d.h"

static int sceneIdx = -1; 

#define MAX_LAYER    8

static CCLayer* createShaderLayer(int nIndex)
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

static CCLayer* nextAction(void)
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createShaderLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

static CCLayer* backAction(void)
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    CCLayer* pLayer = createShaderLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

static CCLayer* restartAction(void)
{
    CCLayer* pLayer = createShaderLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}


ShaderTestDemo::ShaderTestDemo()
{

}

bool ShaderTestDemo::init()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF *label = CCLabelTTF::create(title().c_str(), "Arial", 26);
    addChild(label, 1);
    label->setPosition(ccp(s.width/2, s.height-50));
    label->setColor(ccRED);

    std::string subtitle = this->subtitle();
    if (subtitle.length() > 0)
    {
        CCLabelTTF *l = CCLabelTTF::create(subtitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(ccp(s.width/2, s.height-80));
    }

    CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(ShaderTestDemo::backCallback));
    CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(ShaderTestDemo::restartCallback));
    CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(ShaderTestDemo::nextCallback));

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(ccp(0, 0));
    item1->setPosition(s.width/2- item2->getContentSize().width*2, item2->getContentSize().height/2);
    item2->setPosition(s.width/2, item2->getContentSize().height/2);
    item3->setPosition(s.width/2 + item2->getContentSize().width*2, item2->getContentSize().height/2);
    addChild(menu, 1);

    return true;
}


void ShaderTestDemo::backCallback(CCObject* pSender)
{
    CCScene* s = new ShaderTestScene();
    s->addChild( backAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ShaderTestDemo::nextCallback(CCObject* pSender)
{
    CCScene* s = new ShaderTestScene();//CCScene::create();
    s->addChild( nextAction() );
    CCDirector::sharedDirector()->replaceScene(s);
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

void ShaderTestDemo::restartCallback(CCObject* pSender)
{
    CCScene* s = new ShaderTestScene();
    s->addChild(restartAction()); 

    CCDirector::sharedDirector()->replaceScene(s);
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
:m_center(vertex2(0.0f, 0.0f))
,m_resolution(vertex2(0.0f, 0.0f))
,m_time(0.0f)
,m_uniformCenter(0)
,m_uniformResolution(0)
,m_uniformTime(0)
{
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

    loadShaderVertex(vert, frag);

    m_time = 0;
    m_resolution = vertex2(SIZE_X, SIZE_Y);

    scheduleUpdate();

    setContentSize(CCSizeMake(SIZE_X, SIZE_Y));
    setAnchorPoint(ccp(0.5f, 0.5f));

    return true;
}

void ShaderNode::loadShaderVertex(const char *vert, const char *frag)
{
    CCGLProgram *shader = new CCGLProgram();
    shader->initWithVertexShaderFilename(vert, frag);

    shader->addAttribute("aVertex", kCCVertexAttrib_Position);
    shader->link();

    shader->updateUniforms();

    m_uniformCenter = glGetUniformLocation(shader->getProgram(), "center");
    m_uniformResolution = glGetUniformLocation(shader->getProgram(), "resolution");
    m_uniformTime = glGetUniformLocation(shader->getProgram(), "time");

    this->setShaderProgram(shader);

    shader->release();
}

void ShaderNode::update(float dt)
{
    m_time += dt;
}

void ShaderNode::setPosition(const CCPoint &newPosition)
{
    CCNode::setPosition(newPosition);
    CCPoint position = getPosition();
    m_center = vertex2(position.x * CC_CONTENT_SCALE_FACTOR(), position.y * CC_CONTENT_SCALE_FACTOR());
}

void ShaderNode::draw()
{
    CC_NODE_DRAW_SETUP();

    float w = SIZE_X, h = SIZE_Y;
    GLfloat vertices[12] = {0,0, w,0, w,h, 0,0, 0,h, w,h};

    //
    // Uniforms
    //
    getShaderProgram()->setUniformLocationWith2f(m_uniformCenter, m_center.x, m_center.y);
    getShaderProgram()->setUniformLocationWith2f(m_uniformResolution, m_resolution.x, m_resolution.y);

    // time changes all the time, so it is Ok to call OpenGL directly, and not the "cached" version
    glUniform1f(m_uniformTime, m_time);

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);

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

        CCSize s = CCDirector::sharedDirector()->getWinSize();
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

        CCSize s = CCDirector::sharedDirector()->getWinSize();
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

        CCSize s = CCDirector::sharedDirector()->getWinSize();
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

        CCSize s = CCDirector::sharedDirector()->getWinSize();
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

        CCSize s = CCDirector::sharedDirector()->getWinSize();
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

        CCSize s = CCDirector::sharedDirector()->getWinSize();
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

class SpriteBlur : public CCSprite
{
public:
    void setBlurSize(float f);
    bool initWithTexture(CCTexture2D* texture, const CCRect&  rect);
    void draw();

    static SpriteBlur* create(const char *pszFileName);

    CCPoint blur_;
    GLfloat    sub_[4];

    GLuint    blurLocation;
    GLuint    subLocation;
};

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

bool SpriteBlur::initWithTexture(CCTexture2D* texture, const CCRect& rect)
{
    if( CCSprite::initWithTexture(texture, rect) ) 
    {
        CCSize s = getTexture()->getContentSizeInPixels();

        blur_ = ccp(1/s.width, 1/s.height);
        sub_[0] = sub_[1] = sub_[2] = sub_[3] = 0;

        GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(
            CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("Shaders/example_Blur.fsh"))->getCString();
        CCGLProgram* pProgram = new CCGLProgram();
        pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
        setShaderProgram(pProgram);
        pProgram->release();

        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->link();

        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->updateUniforms();

        CHECK_GL_ERROR_DEBUG();

        subLocation = glGetUniformLocation( getShaderProgram()->getProgram(), "substract");
        blurLocation = glGetUniformLocation( getShaderProgram()->getProgram(), "blurSize");

        CHECK_GL_ERROR_DEBUG();
        return true;
    }

    return false;
}

void SpriteBlur::draw()
{
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

    getShaderProgram()->use();
    getShaderProgram()->setUniformForModelViewProjectionMatrix();
    getShaderProgram()->setUniformLocationWith2f(blurLocation, blur_.x, blur_.y);
    getShaderProgram()->setUniformLocationWith4fv(subLocation, sub_, 1);

    ccGLBindTexture2D(  getTexture()->getName() );

    //
    // Attributes
    //
#define kQuadSize sizeof(m_sQuad.bl)
    long offset = (long)&m_sQuad;

    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CC_INCREMENT_GL_DRAWS(1);
}

void SpriteBlur::setBlurSize(float f)
{
    CCSize s = getTexture()->getContentSizeInPixels();

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

CCControlSlider* ShaderBlur::createSliderCtl()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    CCControlSlider *slider = CCControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
    slider->setAnchorPoint(ccp(0.5f, 1.0f));
    slider->setMinimumValue(0.0f); // Sets the min value of range
    slider->setMaximumValue(3.0f); // Sets the max value of range
    slider->setValue(1.0f);
    slider->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 3.0f));

    // When the value of the slider will change, the given selector will be call
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(ShaderBlur::sliderAction), CCControlEventValueChanged);

    return slider;
 
}

bool ShaderBlur::init()
{
    if( ShaderTestDemo::init() ) 
    {
        m_pBlurSprite = SpriteBlur::create("Images/grossini.png");

        CCSprite *sprite = CCSprite::create("Images/grossini.png");

        CCSize s = CCDirector::sharedDirector()->getWinSize();
        m_pBlurSprite->setPosition(ccp(s.width/3, s.height/2));
        sprite->setPosition(ccp(2*s.width/3, s.height/2));

        addChild(m_pBlurSprite);
        addChild(sprite);

        m_pSliderCtl = createSliderCtl();

        addChild(m_pSliderCtl);
        return true;
    }

    return false;
}

void ShaderBlur::sliderAction(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    m_pBlurSprite->setBlurSize(pSlider->getValue());
}

// ShaderRetroEffect

ShaderRetroEffect::ShaderRetroEffect()
: m_pLabel(NULL)
, m_fAccum(0.0f)
{
    init();
}

bool ShaderRetroEffect::init()
{
    if( ShaderTestDemo::init() ) {

        GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("Shaders/example_HorizontalColor.fsh"))->getCString();
        CCGLProgram *p = new CCGLProgram();
        p->initWithVertexShaderByteArray(ccPositionTexture_vert, fragSource);

        p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

        p->link();
        p->updateUniforms();


        CCDirector *director = CCDirector::sharedDirector();
        CCSize s = director->getWinSize();

        m_pLabel = CCLabelBMFont::create("RETRO EFFECT", "fonts/west_england-64.fnt");

        m_pLabel->setShaderProgram(p);

        p->release();


        m_pLabel->setPosition(ccp(s.width/2,s.height/2));

        addChild(m_pLabel);

        scheduleUpdate();
        return true;
    }

    return false;
}

void ShaderRetroEffect::update(float dt)
{
    m_fAccum += dt;

    CCArray* pArray = m_pLabel->getChildren();

    int i=0;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pArray, pObj)
    {
        CCSprite *sprite = (CCSprite*)pObj;
        i++;
        CCPoint oldPosition = sprite->getPosition();
        sprite->setPosition(ccp( oldPosition.x, sinf( m_fAccum * 2 + i/2.0) * 20  ));

        // add fabs() to prevent negative scaling
        float scaleY = ( sinf( m_fAccum * 2 + i/2.0 + 0.707) );

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

///---------------------------------------
// 
// ShaderTestScene
// 
///---------------------------------------
void ShaderTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());

    CCDirector::sharedDirector()->replaceScene(this);
}
