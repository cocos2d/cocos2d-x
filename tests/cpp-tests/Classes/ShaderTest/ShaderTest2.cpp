	#include "ShaderTest2.h"
#include "ShaderTest.h"
#include "../testResource.h"
#include "cocos2d.h"
#include "renderer/CCRenderCommand.h"
#include "renderer/CCCustomCommand.h"

namespace ShaderTest2
{
    static std::function<Layer*()> createFunctions[] =
    {
        CL(AttribShaderTest),
        CL(NormalSpriteTest),
        CL(GreyScaleSpriteTest),
        CL(BlurSpriteTest),
        CL(NoiseSpriteTest),
        CL(EdgeDetectionSpriteTest),
        CL(BloomSpriteTest),
        CL(CelShadingSpriteTest),
        CL(LensFlareSpriteTest),
        CL(OutlineShadingSpriteTest),
        CL(UniformShaderTest),
       
        CL(UniformAttribShaderTest)
        
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

class ShaderSprite : public Sprite
{
public:
    ShaderSprite();
    ~ShaderSprite();

    virtual void initShader();
    void setBackgroundNotification();

    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;
    void listenBackToForeground(Ref *obj);
    
protected:
    virtual void buildCustomUniforms() = 0;
    virtual void setCustomUniforms() = 0;
protected:
    std::string _fragSourceFile;
    std::string _vertSourceFile;
protected:
    CustomCommand _renderCommand;
    void onDraw(const Matrix &transform, bool transformUpdated);

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
            this->setShaderProgram(nullptr);
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
        vertSource = ccPositionTextureColor_vert;
    }else{
        std::string vertexFilePath = fileUtiles->fullPathForFilename(_vertSourceFile);
        vertSource = fileUtiles->getStringFromFile(vertexFilePath);
    }

    auto program = new GLProgram();
    program->initWithByteArrays(vertSource.c_str(), fragSource.c_str());
    setShaderProgram(program);
    program->release();
    
    CHECK_GL_ERROR_DEBUG();

    program->link();
    
    CHECK_GL_ERROR_DEBUG();
    
    program->updateUniforms();
    
    CHECK_GL_ERROR_DEBUG();
    
    buildCustomUniforms();
    
    CHECK_GL_ERROR_DEBUG();

    program->getVertexAttrib("a_color")->redefineTypeAndSize(GL_UNSIGNED_BYTE, 4, GL_TRUE);
    program->getVertexAttrib("a_position")->redefineTypeAndSize(GL_FLOAT, 3, GL_FALSE);
    program->getVertexAttrib("a_texCoord")->redefineTypeAndSize(GL_FLOAT, 2, GL_FALSE);
}

void ShaderSprite::draw(Renderer *renderer, const Matrix &transform, bool transformUpdated)
{
    _renderCommand.init(_globalZOrder);
    _renderCommand.func = CC_CALLBACK_0(ShaderSprite::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_renderCommand);

}

void ShaderSprite::onDraw(const Matrix &transform, bool transformUpdated)
{
    auto shader = getShaderProgram();
    shader->use();
    shader->setUniformsForBuiltins(transform);

    setCustomUniforms();
    
    GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);
    GL::bindTexture2D( getTexture()->getName());
    
    //
    // Attributes
    //
    #define kQuadSize sizeof(_quad.bl)
    size_t offset = (size_t)&_quad;
    
    // vertex
    int diff = offsetof( V3F_C4B_T2F, vertices);
    shader->getVertexAttrib("a_position")->setPointer(kQuadSize, (void*) (offset + diff));

    // texCoods
    diff = offsetof( V3F_C4B_T2F, texCoords);
    shader->getVertexAttrib("a_texCoord")->setPointer(kQuadSize, (void*) (offset + diff));

    // color
    diff = offsetof( V3F_C4B_T2F, colors);
    shader->getVertexAttrib("a_color")->setPointer(kQuadSize, (void*) (offset + diff));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
}

class NormalSprite : public ShaderSprite, public ShaderSpriteCreator<NormalSprite>
{
public:
    CREATE_FUNC(NormalSprite);
    NormalSprite();
protected:
    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
};

NormalSprite::NormalSprite()
{
    _fragSourceFile = "Shaders/example_normal.fsh";
}

void NormalSprite::buildCustomUniforms()
{
    
}

void NormalSprite::setCustomUniforms()
{
    
}

class GreyScaleSprite : public ShaderSprite, public ShaderSpriteCreator<GreyScaleSprite>
{
public:
    CREATE_FUNC(GreyScaleSprite);
    GreyScaleSprite();
protected:
    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
};

GreyScaleSprite::GreyScaleSprite()
{
    _fragSourceFile = "Shaders/example_greyScale.fsh";
}

void GreyScaleSprite::buildCustomUniforms()
{
    
}

void GreyScaleSprite::setCustomUniforms()
{
    
}

class BlurSprite : public ShaderSprite, public ShaderSpriteCreator<BlurSprite>
{
public:
    CREATE_FUNC(BlurSprite);
    BlurSprite();
    void setBlurSize(float f);
protected:
    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
protected:
    int       _blurRadius;
    Vector2     _pixelSize;
    
    int       _samplingRadius;
    float     _scale;
    float     _cons;
    float     _weightSum;
    
    GLuint    pixelSizeLocation;
    GLuint    coefficientLocation;
};

BlurSprite::BlurSprite()
{
    _fragSourceFile = "Shaders/example_Blur.fsh";
}

void BlurSprite::buildCustomUniforms()
{
    auto s = getTexture()->getContentSizeInPixels();
    _blurRadius = 0;
    _pixelSize = Vector2(1/s.width, 1/s.height);
    _samplingRadius = 0;

    setBlurSize(3.0f);
    auto program = getShaderProgram();
    pixelSizeLocation = program->getUniformLocation("onePixelSize");
    coefficientLocation = program->getUniformLocation("gaussianCoefficient");
}

void BlurSprite::setCustomUniforms()
{
    auto program = getShaderProgram();
    program->setUniformLocationWith2f(pixelSizeLocation, _pixelSize.x, _pixelSize.y);
    program->setUniformLocationWith4f(coefficientLocation, _samplingRadius, _scale,_cons,_weightSum);
}

void BlurSprite::setBlurSize(float f)
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

class NoiseSprite : public ShaderSprite, public ShaderSpriteCreator<NoiseSprite>
{
public:
    CREATE_FUNC(NoiseSprite);
    NoiseSprite();
    
private:
    GLfloat _resolution[2];
    GLuint _resolutionLoc;
protected:
    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
};

NoiseSprite::NoiseSprite()
{
    _fragSourceFile = "Shaders/example_Noisy.fsh";
}

void NoiseSprite::buildCustomUniforms()
{
    auto program = getShaderProgram();
    _resolutionLoc = program->getUniformLocation("resolution");
}

void NoiseSprite::setCustomUniforms()
{
    _resolution[0] = getTexture()->getContentSizeInPixels().width;
    _resolution[1] = getTexture()->getContentSizeInPixels().height;
    
    getShaderProgram()->setUniformLocationWith2fv(_resolutionLoc, _resolution, 1);
}

class EdgeDetectionSprite : public ShaderSprite, public ShaderSpriteCreator<EdgeDetectionSprite>
{
public:
    CREATE_FUNC(EdgeDetectionSprite);
    EdgeDetectionSprite();
    
private:
    GLfloat _resolution[2];
    GLuint _resolutionLoc;
protected:
    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
};

EdgeDetectionSprite::EdgeDetectionSprite()
{
    _fragSourceFile = "Shaders/example_edgeDetection.fsh";
}

void EdgeDetectionSprite::buildCustomUniforms()
{
    auto program = getShaderProgram();
    _resolutionLoc = program->getUniformLocation("resolution");
}

void EdgeDetectionSprite::setCustomUniforms()
{
    _resolution[0] = getTexture()->getContentSizeInPixels().width;
    _resolution[1] = getTexture()->getContentSizeInPixels().height;
    
    getShaderProgram()->setUniformLocationWith2fv(_resolutionLoc, _resolution, 1);
}

class BloomSprite : public ShaderSprite, public ShaderSpriteCreator<BloomSprite>
{
public:
    CREATE_FUNC(BloomSprite);
    BloomSprite();
    
private:
    GLfloat _resolution[2];
    GLuint _resolutionLoc;
protected:
    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
};

BloomSprite::BloomSprite()
{
    _fragSourceFile = "Shaders/example_bloom.fsh";
}

void BloomSprite::buildCustomUniforms()
{
    auto program = getShaderProgram();
    _resolutionLoc = program->getUniformLocation("resolution");
}

void BloomSprite::setCustomUniforms()
{
    _resolution[0] = getTexture()->getContentSizeInPixels().width;
    _resolution[1] = getTexture()->getContentSizeInPixels().height;
    
    getShaderProgram()->setUniformLocationWith2fv(_resolutionLoc, _resolution, 1);
}

class CelShadingSprite : public ShaderSprite, public ShaderSpriteCreator<CelShadingSprite>
{
public:
    CREATE_FUNC(CelShadingSprite);
    CelShadingSprite();
    
private:
    GLfloat _resolution[2];
    GLuint _resolutionLoc;
protected:
    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
};

CelShadingSprite::CelShadingSprite()
{
    _fragSourceFile = "Shaders/example_celShading.fsh";
}

void CelShadingSprite::buildCustomUniforms()
{
    auto program = getShaderProgram();
    _resolutionLoc = program->getUniformLocation("resolution");
}

void CelShadingSprite::setCustomUniforms()
{
    _resolution[0] = getTexture()->getContentSizeInPixels().width;
    _resolution[1] = getTexture()->getContentSizeInPixels().height;
    
    getShaderProgram()->setUniformLocationWith2fv(_resolutionLoc, _resolution, 1);
}

class LensFlareSprite : public ShaderSprite, public ShaderSpriteCreator<LensFlareSprite>
{
public:
    CREATE_FUNC(LensFlareSprite);
    LensFlareSprite();
    
private:
    GLfloat _resolution[2];
    GLfloat _textureResolution[2];
    GLuint _resolutionLoc;
    GLuint _textureResolutionLoc;
protected:
    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
};

LensFlareSprite::LensFlareSprite()
{
    _fragSourceFile = "Shaders/example_lensFlare.fsh";
}

void LensFlareSprite::buildCustomUniforms()
{
    auto program = getShaderProgram();
    _resolutionLoc = program->getUniformLocation("resolution");
    _textureResolutionLoc = program->getUniformLocation("textureResolution");
}

void LensFlareSprite::setCustomUniforms()
{
    _textureResolution[0] = getTexture()->getContentSizeInPixels().width;
    _textureResolution[1] = getTexture()->getContentSizeInPixels().height;
    
    _resolution[0] = getContentSize().width;
    _resolution[1] = getContentSize().height;
    
    getShaderProgram()->setUniformLocationWith2fv(_resolutionLoc, _resolution, 1);
    getShaderProgram()->setUniformLocationWith2fv(_textureResolutionLoc, _textureResolution, 1);
}

NormalSpriteTest::NormalSpriteTest()
{
    if (ShaderTestDemo2::init())
    {
        auto s = Director::getInstance()->getWinSize();
        NormalSprite* sprite = NormalSprite::createSprite("Images/powered.png");
        sprite->setPosition(Vector2(s.width/2, s.height/2));
        addChild(sprite);
    }
    
}

GreyScaleSpriteTest::GreyScaleSpriteTest()
{
    if (ShaderTestDemo2::init())
    {
        auto s = Director::getInstance()->getWinSize();
        GreyScaleSprite* sprite = GreyScaleSprite::createSprite("Images/powered.png");
        sprite->setPosition(Vector2(s.width * 0.75, s.height/2));
        auto sprite2 = Sprite::create("Images/powered.png");
        sprite2->setPosition(Vector2(s.width * 0.25, s.height/2));
        addChild(sprite);
        addChild(sprite2);
    }
    
}

BlurSpriteTest::BlurSpriteTest()
{
    if (ShaderTestDemo2::init())
    {
        auto s = Director::getInstance()->getWinSize();
        BlurSprite* sprite = BlurSprite::createSprite("Images/powered.png");
        sprite->setPosition(Vector2(s.width * 0.75, s.height/2));
        auto sprite2 = Sprite::create("Images/powered.png");
        sprite2->setPosition(Vector2(s.width * 0.25, s.height/2));
        addChild(sprite);
        addChild(sprite2);
    }
    
}

NoiseSpriteTest::NoiseSpriteTest()
{
    if (ShaderTestDemo2::init())
    {
        auto s = Director::getInstance()->getWinSize();
        NoiseSprite* sprite = NoiseSprite::createSprite("Images/powered.png");
        sprite->setPosition(Vector2(s.width * 0.75, s.height/2));
        auto sprite2 = Sprite::create("Images/powered.png");
        sprite2->setPosition(Vector2(s.width * 0.25, s.height/2));
        addChild(sprite);
        addChild(sprite2);
    }
}

EdgeDetectionSpriteTest::EdgeDetectionSpriteTest()
{
    if (ShaderTestDemo2::init())
    {
        auto s = Director::getInstance()->getWinSize();
        EdgeDetectionSprite* sprite = EdgeDetectionSprite::createSprite("Images/powered.png");
        sprite->setPosition(Vector2(s.width * 0.75, s.height/2));
        auto sprite2 = Sprite::create("Images/powered.png");
        sprite2->setPosition(Vector2(s.width * 0.25, s.height/2));
        addChild(sprite);
        addChild(sprite2);
    }
}

BloomSpriteTest::BloomSpriteTest()
{
    if (ShaderTestDemo2::init())
    {
        auto s = Director::getInstance()->getWinSize();
        BloomSprite* sprite = BloomSprite::createSprite("Images/stone.png");
        sprite->setPosition(Vector2(s.width * 0.75, s.height/2));
        auto sprite2 = Sprite::create("Images/stone.png");
        sprite2->setPosition(Vector2(s.width * 0.25, s.height/2));
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
        sprite->setPosition(Vector2(s.width * 0.75, s.height/2));
        auto sprite2 = Sprite::create("Images/stone.png");
        sprite2->setPosition(Vector2(s.width * 0.25, s.height/2));
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
        sprite->setPosition(Vector2(s.width * 0.5, s.height/2));
        addChild(sprite);
    }
}


class OutlineSprite : public ShaderSprite, public ShaderSpriteCreator<OutlineSprite>
{
public:
    CREATE_FUNC(OutlineSprite);
    OutlineSprite();
    
private:
    GLuint _outlineColorUniformLocation;
    GLuint _thresdholdUniformLocation;
    GLuint _radiusUniformLocation;
protected:
    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
};


OutlineSprite::OutlineSprite()
{
    _fragSourceFile = "Shaders/example_outline.fsh";
    _vertSourceFile = "Shaders/example_outline.vsh";
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
}

void OutlineSprite::buildCustomUniforms()
{
    auto program = getShaderProgram();
    _outlineColorUniformLocation = program->getUniformLocation("u_outlineColor");
    _thresdholdUniformLocation = program->getUniformLocation("u_threshold");
    _radiusUniformLocation = program->getUniformLocation("u_radius");
}

void OutlineSprite::setCustomUniforms()
{
    GLfloat color[3] = {1.0, 0.2, 0.3};
    GLfloat radius = 0.01;
    GLfloat threshold = 1.75;
    
    getShaderProgram()->setUniformLocationWith3fv(_outlineColorUniformLocation, color, 1);
    getShaderProgram()->setUniformLocationWith1f(_radiusUniformLocation, radius);
    getShaderProgram()->setUniformLocationWith1f(_thresdholdUniformLocation, threshold);
}


OutlineShadingSpriteTest::OutlineShadingSpriteTest()
{
    if (ShaderTestDemo2::init()) {
        auto s = Director::getInstance()->getWinSize();
        OutlineSprite* sprite = OutlineSprite::createSprite("Images/grossini_dance_10.png");
        sprite->setPosition(Point(s.width * 0.75, s.height/2));
        auto sprite2 = Sprite::create("Images/grossini_dance_10.png");
        sprite2->setPosition(Point(s.width * 0.25, s.height/2));
        addChild(sprite);
        addChild(sprite2);
    }
}

class UniformSprite : public Sprite
{
public:
    UniformSprite();
    ~UniformSprite();
    CREATE_FUNC(UniformSprite);
    
    virtual void initShader();
   // void setBackgroundNotification();
    
    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;
   // void listenBackToForeground(Ref *obj);
    
protected:
//    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
protected:
    std::string _fragSourceFile;
    std::string _vertSourceFile;
protected:
    CustomCommand _renderCommand;
    void onDraw(const Matrix &transform, bool transformUpdated);

};

UniformSprite::UniformSprite()
{
    _vertSourceFile = "Shaders/example_Heart.vsh";
    _fragSourceFile = "Shaders/example_Heart.fsh";
}

UniformSprite::~UniformSprite()
{
    
}

void UniformSprite::initShader()
{
    auto shader = new GLProgram();
    shader->initWithFilenames(_vertSourceFile, _fragSourceFile);
    shader->link();
    
    shader->updateUniforms();
    
    this->setShaderProgram(shader);
    
//    std::string attribname ="a_position";
//    shader->getAttrib(attribname)->size = 2;
    
    shader->release();
}

void UniformSprite::draw(Renderer *renderer, const Matrix &transform, bool transformUpdated)
{
    _renderCommand.init(_globalZOrder);
	_renderCommand.func = CC_CALLBACK_0(UniformSprite::onDraw, this, transform, transformUpdated);
	renderer->addCommand(&_renderCommand);
}

void UniformSprite::setCustomUniforms()
{
    
    std::string name = "center";
    _shaderProgram->getUniform(name)->setValue(Vector2(480,320));
    name = "resolution";
    _shaderProgram->getUniform(name)->setValue(Vector2(256,256));
}

void UniformSprite::onDraw(const Matrix &transform, bool transformUpdated)
{
    // Set Shader GLProgram
	auto program = getShaderProgram();
	program->use();
    program->setUniformsForBuiltins(transform);
    
    setCustomUniforms();
    //GL::bindTexture2D( getTexture()->getName());

    float w = 256, h = 256;
    GLfloat vertices[12] = {0,0, w,0, w,h, 0,0, 0,h, w,h};
//    program->setVertexAttrib(vertices, true);

	// Draw Call Test
	glDrawArrays(GL_TRIANGLES, 0, 6);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,6);
    
    CHECK_GL_ERROR_DEBUG();
}


UniformShaderTest::UniformShaderTest()
{
    if (ShaderTestDemo2::init()) {
        auto s = Director::getInstance()->getWinSize();
        UniformSprite* sprite = UniformSprite::create();
        setContentSize(Size(256, 256));
        setAnchorPoint(Vector2(0.5f, 0.5f));
        sprite->initShader();
        sprite->setPosition(64,64);
        addChild(sprite);
    }
}


class AttribSprite : public Sprite
{
public:
    AttribSprite();
    ~AttribSprite();
    CREATE_FUNC(AttribSprite);
    
    virtual void initShader();
    // void setBackgroundNotification();
    
    virtual void draw(Renderer *renderer, const Matrix &transform, bool transformUpdated) override;
    // void listenBackToForeground(Ref *obj);
    
protected:
    //    virtual void buildCustomUniforms();
    virtual void setCustomUniforms();
protected:
    std::string _fragSourceFile;
    std::string _vertSourceFile;
protected:
    CustomCommand _renderCommand;
    void onDraw(const Matrix &transform, bool transformUpdated);
};

AttribSprite::AttribSprite()
{
    _fragSourceFile = "Shaders/example_normal.fsh";
    _vertSourceFile = "Shaders/example_normal.vsh";
}

AttribSprite::~AttribSprite()
{
    
}

void AttribSprite::initShader()
{
    auto shader = new GLProgram();

    shader->initWithFilenames(_vertSourceFile, _fragSourceFile);
    shader->link();
    shader->updateUniforms();
    this->setShaderProgram(shader);
    
    shader->release();
}

void AttribSprite::draw(Renderer *renderer, const Matrix &transform, bool transformUpdated)
{
    _renderCommand.init(_globalZOrder);
	_renderCommand.func = CC_CALLBACK_0(AttribSprite::onDraw, this, transform, transformUpdated);
	renderer->addCommand(&_renderCommand);
}

void AttribSprite::setCustomUniforms()
{


}

void AttribSprite::onDraw(const Matrix &transform, bool transformUpdated)
{
    // Set Shader GLProgram
	auto program = getShaderProgram();
	program->use();
    program->setUniformsForBuiltins(transform);
    
    setCustomUniforms();
    
    // Set
    //glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);
    GL::bindTexture2D( getTexture()->getName());
    
    //
    // Attributes
    //
    #define kQuadSize sizeof(_quad.bl)
    size_t offset = (size_t)&_quad;
    size_t stride = kQuadSize;

    int diff = offsetof( V3F_C4B_T2F, vertices);
    program->getVertexAttrib("a_position")->setPointer(3, GL_FLOAT, GL_FALSE, stride, (void*) (offset + diff));

    diff = offsetof( V3F_C4B_T2F, colors);
    program->getVertexAttrib("a_color")->setPointer(4, GL_UNSIGNED_BYTE, GL_TRUE, stride, (void*) (offset + diff));

    diff = offsetof( V3F_C4B_T2F, texCoords);
    program->getVertexAttrib("a_texCoord")->setPointer(2, GL_FLOAT, GL_FALSE, stride, (void*) (offset + diff));

    //program->getUniformValue("u_diffuseColor")->setValue(Vector4(1,1,1,1));
    
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
    
    CHECK_GL_ERROR_DEBUG();
}

AttribShaderTest::AttribShaderTest()
{
    if (ShaderTestDemo2::init())
    {
        auto s = Director::getInstance()->getWinSize();
        AttribSprite* sprite = AttribSprite::create();
        sprite->setTexture("Images/powered.png");
        sprite->initShader();
        sprite->setPosition(Vector2(s.width/2, s.height/2));
        addChild(sprite);
    }
   
}

UniformAttribShaderTest::UniformAttribShaderTest()
{

}
