#ifndef __MATERIAL_TEST_LAYER_H__
#define __MATERIAL_TEST_LAYER_H__

#include "cocos2d.h"
#include "cocos3d.h"
#include <vector>

USING_NS_CC;

enum TouchEvent
{
    TouchEvent_PRESS,
    TouchEvent_RELEASE,
    TouchEvent_MOVE
};

class  MaterialTestLayer :  public C3DLayer
{  

public:
    MaterialTestLayer();
    virtual ~MaterialTestLayer();   
	virtual bool init();   
		
	virtual void update(float dt);

	virtual void draw(void);//render the 3d contents

	CREATE_FUNC(MaterialTestLayer);

	void setUpScene();

    // setup initialize camera
    void setUpCamera();
    //setup initialize light
    void setUpLight();
	
    virtual void touchEvent(TouchEvent evt, float x, float y, unsigned int contactIndex);

    // optional
	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
	virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);

    void menuCallback(CCObject * pSender);
	   

protected:
	bool _touched;
	int _touchX;
	int _touchY;
    
    C3DStaticObj* _sm;
    C3DSprite* _fish;
};
#endif 