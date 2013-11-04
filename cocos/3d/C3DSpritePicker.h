#ifndef ENTITYPICKER_H_
#define ENTITYPICKER_H_


#include <string>

namespace cocos3d
{
class C3DSprite;
class C3DScene;


/**
*Defines a sprite picker through the intersects between a obb and a ray. 
*/
class C3DSpritePicker
{

public:

	C3DSpritePicker(C3DScene* scene);
	virtual ~C3DSpritePicker();
	void update(long elapsedTime);
	
	C3DSprite* pick( float x,float y );
private:
	C3DScene* _scene;  
};


}

#endif
