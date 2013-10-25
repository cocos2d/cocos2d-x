#include "C3DSpritePicker.h"

#include "C3DSprite.h"

#include "C3DTransform.h"
#include "C3DMatrix.h"
#include "C3DScene.h"
#include "C3DCamera.h"

#include "BoundingBox.h"
#include "C3DRay.h"
#include "C3DRenderSystem.h"

namespace cocos3d
{

C3DSpritePicker::C3DSpritePicker(C3DScene* scene) : _scene(scene) 
{
	
}

C3DSpritePicker::~C3DSpritePicker()
{
	
}

C3DSprite* C3DSpritePicker::pick( float x,float y )
{
	std::map<std::string,C3DSprite*>* entities = _scene->getSpriteNodes();
			

    C3DRay* ray = new C3DRay();
	_scene->getActiveCamera()->getAxes(C3DRenderSystem::getInstance()->getViewport(),x,y,ray);

	for( std::map<std::string,C3DSprite*>::const_iterator iter = entities->begin(); iter != entities->end(); ++iter )
	{
		C3DSprite * pCurr = iter->second;		

	//	BoundingBox* bb = pCurr->getBoundingBox();
		C3DOBB* obb = pCurr->getOBB();		

	//	bool res = ray->intersects(bb);
		bool res = ray->intersects(obb);
		if(res == true)
		{
            SAFE_DELETE(ray);
			return pCurr;
		}
		
	}
    SAFE_DELETE(ray);
	return NULL;

	
}

void C3DSpritePicker::update(long elapsedTime)
{
	
}



}