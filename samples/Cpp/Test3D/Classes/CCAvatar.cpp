#include "CCAvatar.h"

#include <map>

#include "C3DViewport.h"
#include "C3DMatrix.h"
#include "C3DMaterial.h"
#include "C3DTechnique.h"
#include "C3DPass.h"
#include "MaterialParameter.h"
#include "C3DSampler.h"


using namespace std;

MaterialTestLayer::MaterialTestLayer()
{

}

MaterialTestLayer::~MaterialTestLayer()
{
    SAFE_RELEASE(_fish);
    SAFE_RELEASE(_sm);
}

bool MaterialTestLayer::init()
{
    bool r = C3DLayer::init();

    setUpCamera();
    setUpLight();
    setUpScene();   

    return r;
}

void MaterialTestLayer::update( float dt )
{
    long elapsedTime = (long)(dt*1000.0f+0.5f);
    C3DLayer::update(elapsedTime);
}

void MaterialTestLayer::draw()
{
    C3DLayer::draw();
}

void MaterialTestLayer::setUpScene()
{

    _sm = C3DStaticObj::create("1");
    
    _sm->loadFromFile("scene/1/1.ckb");

    _sm->setMaterial("scene/1/1_nolight.material");
    _sm->translate(0, 0, 0);
    //sm->rotateX(0.8f);
    _sm->scale(50, 50, 50);

    _scene->addChild(_sm);
    _sm->retain();

	
    //create fish
	_fish = NULL;
	_fish = C3DSprite::create("shayu");
	_fish->loadFromFile("fish/shayu.ckb", true);
	_fish->setScale(2.0f);
	C3DAnimationClip* idleClip = _fish->addAnimationClip("idle",0,600,0,1.0f);
	_fish->playAnimationClip("idle");
	_fish->setPosition(15.0f, 10.0f, 0.0f);
	_scene->addChild(_fish);
   
   
	//////////////////////////////////////////////////////////////////////////
}

void MaterialTestLayer::setUpCamera()
{
    C3DCamera* camera = C3DCamera::createPerspective(45, 0.75f, 1, 1000);
    //camera->setPosition(0,0,100);
    camera->lookAt(Vector3(0,50,100), Vector3(0, 1, 0), Vector3(0, 0, 0));
    //camera->rotateX(MATH_DEG_TO_RAD(-20.0f));

    _scene->addChild(camera);
    _scene->setActiveCamera(0);
}

void MaterialTestLayer::setUpLight()
{

}

void MaterialTestLayer::touchEvent(TouchEvent evt, float x, float y, unsigned int contactIndex)
{
    switch (evt)
    {
    case TouchEvent_PRESS:
        {
            _touched = true;
            _touchX = x;
            _touchY = y;
        }
        break;
    case TouchEvent_RELEASE:
        {
            _touched = false;
            _touchX = 0;
            _touchY = 0;
        }
        break;
    case TouchEvent_MOVE:
        {
            int deltaX = x - _touchX;
            _touchX = x;

            int deltaY = y - _touchY;
            _touchY = y;

            {				
                C3DCamera* camera = _scene->getActiveCamera();
                if (camera)
                    camera->rotateAlong(Vector3(0, 0, 0), Vector3(0, 1, 0), MATH_DEG_TO_RAD(deltaX * 0.5f));

            }	
        }
        break;
    default:
        break;
    };
}
	

void MaterialTestLayer::onTouchesBegan( const std::vector<Touch*>& touches, Event *unused_event )
{
    Touch *pTouch;
	std::vector<Touch*>::const_iterator iter;
	for (iter = touches.begin(); iter != touches.end(); ++iter)
    {
        pTouch = (Touch *)(*iter);		
        Point touchPoint = pTouch->getLocationInView();
        
        touchEvent(TouchEvent_PRESS, touchPoint.x , touchPoint.y , pTouch->getID());
    }    

}

	

void MaterialTestLayer::onTouchesMoved( const std::vector<Touch*>& touches, Event *unused_event )
{
    Touch *pTouch;    
	std::vector<Touch*>::const_iterator iter;
    for (iter = touches.begin(); iter != touches.end(); ++iter)
    {
        pTouch = (Touch *)(*iter);	
        Point touchPoint = pTouch->getLocationInView();
        
        touchEvent(TouchEvent_MOVE, touchPoint.x , touchPoint.y , pTouch->getID());


    }

}
	

void MaterialTestLayer::onTouchesEnded( const std::vector<Touch*>& touches, Event *unused_event )
{
    Touch *pTouch;    
	std::vector<Touch*>::const_iterator iter;
    for (iter = touches.begin(); iter != touches.end(); ++iter)
    {
        pTouch = (Touch *)(*iter);	
        Point touchPoint = pTouch->getLocationInView();
        
        touchEvent(TouchEvent_RELEASE, touchPoint.x , touchPoint.y , pTouch->getID());
    }

}


void MaterialTestLayer::onTouchesCancelled( const std::vector<Touch*>&touches, Event *unused_event )
{

}

