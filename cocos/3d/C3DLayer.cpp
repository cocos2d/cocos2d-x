#include "C3DLayer.h"

#include "C3DSprite.h"
#include "C3DVector2.h"
#include "C3DScene.h"

#include "touch_dispatcher/CCTouch.h"

#include <map>

#include "C3DCamera.h"
#include "C3DLight.h"

#include "Base.h"

#include "Rectangle.h"
#include "C3DVector4.h"
#include "C3DScene.h"

#include "C3DRenderSystem.h"

#include "cocos2d.h"
#include "C3DRenderState.h"
#include "C3DEffect.h"
#include "C3DMaterial.h"

GLenum __gl_error_code = GL_NO_ERROR;
#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
namespace cocos3d
{

static C3DLayer* __mainLayer = NULL;



C3DLayer::C3DLayer()   
{	
    if (!__mainLayer)
        __mainLayer = this;

    _initialized = false;
    _state = UNINITIALIZED; 

    _renderSystem = NULL;
    _scene = NULL;
        
    _2DState = NULL;

	_statRender = NULL;
}


C3DLayer::~C3DLayer()
{
    exit();

    if (__mainLayer == this)
        __mainLayer = NULL;

    CC_SAFE_RELEASE(_2DState);
}

bool C3DLayer::init()
{
    return CCLayer::init()  && init3D();
}


bool C3DLayer::init3D()
{	
    initialize();	
        
    // Update the aspect ratio for our scene's camera to match the current device resolution 
	cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getWinSize();//cocos2d::CCDirector::sharedDirector()->getWinSizeInPixels();
    setSize(size.width, size.height);
    setPosition(size.width / 2, size.height / 2);
    // set searching path
    cocos2d::CCFileUtils::sharedFileUtils()->addSearchPath("res");	
    
    _2DState = C3DStateBlock::create();
    
    // Start up game systems.
    if (!startup())
    {
        shutdown();
        return false;
    }
    

    return true;
}

void C3DLayer::onEnter()
{
    setTouchEnabled( true );
    
//    cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);

    this->scheduleUpdate();

    CCLayer::onEnter();
}


void C3DLayer::onExit()
{
    _scene->removeAllNode();

	CCLayer::onExit();

}

void C3DLayer::draw(void)
{
    beginRender();
    //render 3d objects
    render(0);
    
    endRender();
}


long C3DLayer::getAbsoluteTime()
{
    struct cocos2d::cc_timeval now;
    if (cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL) != 0)
    {
        return 0 ;
    }


    return now.tv_sec*1000;
}

long C3DLayer::getGameTime()
{
    struct cocos2d::cc_timeval now;
    if (cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL) != 0)
    {
        return 0 ;
    }


    return now.tv_sec*1000;
}



void C3DLayer::initialize()
{	
    _scene = cocos3d::C3DScene::createScene(this);
	
    _initialized = true;
	
	_statRender = new C3DStatRender(this);
}


void C3DLayer::finalize()
{	
	SAFE_DELETE(_statRender);

    SAFE_DELETE(_scene);
}

bool C3DLayer::startup()
{
    if (_state != UNINITIALIZED)
        return false;
      

    _renderSystem = C3DRenderSystem::create();
    _renderSystem->retain();
       
    
    _state = RUNNING;

    return true;
}

void C3DLayer::shutdown()
{
    // Call user finalization.
    if (_state != UNINITIALIZED)
    {      
        finalize();
		     

        SAFE_RELEASE(_renderSystem);
        
        _state = UNINITIALIZED;
    }
}

void C3DLayer::pause()
{
    if (_state == RUNNING)
    {
        _state = PAUSED;      
    }
}

void C3DLayer::resume()
{
    if (_state == PAUSED)
    {
        _state = RUNNING;        
    }
}

void C3DLayer::exit()
{
    shutdown();
}

void C3DLayer::update(long elapsedTime)
{
    if (!_initialized)
    {        
        initialize();        
        _initialized = true;
    }

    _scene->update(elapsedTime);
    // Update the scheduled and running animations.
    
    if (this == __mainLayer)
    {
        _renderSystem->update(elapsedTime);
    }

	_statRender->update(elapsedTime);
}

void C3DLayer::beginRender()
{
    //backup cocos2d opengl state, sync 3d cached opengl state 
    _2DState->backUpGLState();

    glGetVertexAttribiv(cocos2d::kCCVertexAttrib_Position, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &_enablePos);
    glGetVertexAttribiv(cocos2d::kCCVertexAttrib_Color, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &_enableColor);
    glGetVertexAttribiv(cocos2d::kCCVertexAttrib_TexCoords, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &_enableTex);
    glGetIntegerv(GL_ACTIVE_TEXTURE, &_texture);
    glGetIntegerv(GL_VIEWPORT, _oldViewport);
//	glGetFloatv(GL_COLOR_CLEAR_VALUE, _oldClearColor);

    //sync active texture
    C3DRenderState::activeTexture(_texture);

    _renderSystem->setViewport(/*point1.x, point1.y, point2.x - point1.x, point2.y - point1.y*/);
    
    cocos2d::ccGLBindVAO(0);
}

void C3DLayer::endRender()
{
    // restore cocos2d opengl state
    cocos2d::ccGLUseProgram(0);

    _2DState->restoreGLState(false);
    C3DRenderState::activeTexture(_texture);
    glViewport(_oldViewport[0], _oldViewport[1], _oldViewport[2], _oldViewport[3]);
    if (_enablePos)
        glEnableVertexAttribArray(cocos2d::kCCVertexAttrib_Position);
    if (_enableColor)
        glEnableVertexAttribArray(cocos2d::kCCVertexAttrib_Color);
    if (_enableTex)
        glEnableVertexAttribArray(cocos2d::kCCVertexAttrib_TexCoords);

//	glClearColor(_oldClearColor[0], _oldClearColor[1], _oldClearColor[2], _oldClearColor[3]);
	
}

void C3DLayer::render(long elapsedTime)
{
    /*if(_renderSystem == NULL)
        return;

    _renderSystem->Render();*/
    if (_scene == NULL)
        return;
	
	glClearColor(_envConfig._clearColor.x, _envConfig._clearColor.y, _envConfig._clearColor.z, _envConfig._clearColor.w);
	//glClear(GL_COLOR_BUFFER_BIT);

    _scene->preDraw();
    _scene->draw();
    _scene->postDraw();
    _scene->drawDebug();
    
}

unsigned int C3DLayer::getWidth() const
{
    return _width;
}

unsigned int C3DLayer::getHeight() const
{
    return _height;
}

void C3DLayer::showBoundingBox(bool bShow)
{
    this->getScene()->showBoundingBox(bShow);
}

C3DLayer* C3DLayer::getMainLayer()
{
    return __mainLayer;
}

void C3DLayer::setAsMainLayer()
{
    __mainLayer = this;
}

void C3DLayer::setSize(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
}

const C3DViewport* C3DLayer::getViewport() const
{
	return _renderSystem->getViewport();
}

}









