/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCDisplayFactory.h"
#include "../CCBone.h"
#include "../CCArmature.h"
#include "../display/CCSkin.h"
#include "../utils/CCSpriteFrameCacheHelper.h"
#include "../utils/CCArmatureDataManager.h"
#include "../utils/CCTransformHelp.h"

NS_CC_EXT_BEGIN

void CCDisplayFactory::addDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, CCDisplayData *displayData)
{
    switch(displayData->displayType)
    {
    case CS_DISPLAY_SPRITE:
        addSpriteDisplay(bone, decoDisplay, displayData);
        break;
    case  CS_DISPLAY_PARTICLE:
        addParticleDisplay(bone, decoDisplay, displayData);
        break;
    case  CS_DISPLAY_ARMATURE:
        addArmatureDisplay(bone, decoDisplay, displayData);
        break;
    default:
        break;
    }
}

void CCDisplayFactory::createDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay)
{
    switch(decoDisplay->getDisplayData()->displayType)
    {
    case CS_DISPLAY_SPRITE:
        createSpriteDisplay(bone, decoDisplay);
        break;
    case CS_DISPLAY_PARTICLE:
        createParticleDisplay(bone, decoDisplay);
        break;
    case CS_DISPLAY_ARMATURE:
        createArmatureDisplay(bone, decoDisplay);
        break;
    default:
        break;
    }
}

void CCDisplayFactory::updateDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, float dt, bool dirty)
{
    CS_RETURN_IF(!decoDisplay);

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    if (dirty)
    {
        CCColliderDetector *detector = decoDisplay->getColliderDetector();
        if (detector)
        {
			CCNode *node = decoDisplay->getDisplay();
			CCAffineTransform displayTransform = node->nodeToParentTransform();
			CCPoint anchorPoint =  node->getAnchorPointInPoints();
			anchorPoint = CCPointApplyAffineTransform(anchorPoint, displayTransform);
			displayTransform.tx = anchorPoint.x;
			displayTransform.ty = anchorPoint.y;
            CCAffineTransform t = CCAffineTransformConcat(displayTransform, bone->getArmature()->nodeToParentTransform());
            detector->updateTransform(t);
        }
    }
#endif

	CCNode *display = decoDisplay->getDisplay();

	if (dynamic_cast<CCSkin*>(display) != NULL)
	{
		updateSpriteDisplay(bone, display, dt, dirty);
	}
	else if (dynamic_cast<CCParticleSystem*>(display) != NULL)
	{
		updateParticleDisplay(bone, display, dt, dirty);
	}
	else if (dynamic_cast<CCArmature*>(display) != NULL)
	{
		updateArmatureDisplay(bone, display, dt, dirty);
	}
}



void CCDisplayFactory::addSpriteDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, CCDisplayData *displayData)
{
    CCSpriteDisplayData *sdp = CCSpriteDisplayData::create();
    sdp->copy((CCSpriteDisplayData *)displayData);
    decoDisplay->setDisplayData(sdp);
    createSpriteDisplay(bone, decoDisplay);
}

void CCDisplayFactory::createSpriteDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay)
{
    CCSkin *skin = NULL;

    CCSpriteDisplayData *displayData = (CCSpriteDisplayData *)decoDisplay->getDisplayData();

    //! remove .xxx
    std::string textureName = displayData->displayName;
    size_t startPos = textureName.find_last_of(".");

    if(startPos != std::string::npos)
    {
        textureName = textureName.erase(startPos);
    }

    //! create display
    if(textureName.length() == 0)
    {
        skin = CCSkin::create();
    }
    else
    {
        skin = CCSkin::createWithSpriteFrameName((textureName + ".png").c_str());
    }

    CCTextureAtlas *atlas = CCSpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->getTextureAtlasWithDisplayName((textureName + ".png").c_str());
    skin->setTextureAtlas(atlas);

    CCTextureData *textureData = CCArmatureDataManager::sharedArmatureDataManager()->getTextureData(textureName.c_str());
    if(textureData)
    {
        //! Init display anchorPoint, every Texture have a anchor point
        skin->setAnchorPoint(ccp( textureData->pivotX, textureData->pivotY));
    }

    skin->setBone(bone);

	CCArmature *armature = bone->getArmature();
	if (armature)
	{
		if (armature->getArmatureData()->dataVersion >= VERSION_COMBINED)
		{
			skin->setSkinData(displayData->skinData);
		}
		else
		{
			skin->setSkinData(*bone->getBoneData());
		}
	}

    decoDisplay->setDisplay(skin);

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    if (textureData && textureData->contourDataList.count() > 0)
    {

        //! create ContourSprite
        CCColliderDetector *colliderDetector = CCColliderDetector::create(bone);
        colliderDetector->addContourDataList(&textureData->contourDataList);

        decoDisplay->setColliderDetector(colliderDetector);
    }
#endif
}

void CCDisplayFactory::updateSpriteDisplay(CCBone *bone, CCNode *display, float dt, bool dirty)
{
    CCSkin *skin = (CCSkin *)display;
    skin->updateArmatureTransform();
}


void CCDisplayFactory::addArmatureDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, CCDisplayData *displayData)
{
    CCArmatureDisplayData *adp = CCArmatureDisplayData::create(); ;
    adp->copy((CCArmatureDisplayData *)displayData);
    decoDisplay->setDisplayData(adp);

    createArmatureDisplay(bone, decoDisplay);
}
void CCDisplayFactory::createArmatureDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay)
{
    CCArmatureDisplayData *displayData = (CCArmatureDisplayData *)decoDisplay->getDisplayData();

    CCArmature *armature = CCArmature::create(displayData->displayName.c_str(), bone);

    /*
     *  because this bone have called this name, so armature should change it's name, or it can't add to
     *  CCArmature's bone children.
     */
    armature->setName((bone->getName() + "_armatureChild").c_str());

    decoDisplay->setDisplay(armature);
}
void CCDisplayFactory::updateArmatureDisplay(CCBone *bone, CCNode *display, float dt, bool dirty)
{
    CS_RETURN_IF(!dirty);

    CCArmature *armature = (CCArmature*)display;
    if(armature)
    {
        armature->sortAllChildren();
        armature->update(dt);
    }
}



void CCDisplayFactory::addParticleDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, CCDisplayData *displayData)
{
    CCParticleDisplayData *adp = CCParticleDisplayData::create(); ;
    adp->copy((CCParticleDisplayData *)displayData);
    decoDisplay->setDisplayData(adp);

    createParticleDisplay(bone, decoDisplay);
}
void CCDisplayFactory::createParticleDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay)
{
    CCParticleDisplayData *displayData = (CCParticleDisplayData *)decoDisplay->getDisplayData();
    CCParticleSystem *system = CCParticleSystemQuad::create(displayData->plist.c_str());
    decoDisplay->setDisplay(system);
}
void CCDisplayFactory::updateParticleDisplay(CCBone *bone, CCNode *display, float dt, bool dirty)
{
    CCParticleSystem *system = (CCParticleSystem *)display;
    CCBaseData node;
    CCTransformHelp::matrixToNode(bone->nodeToArmatureTransform(), node);
    system->setPosition(node.x, node.y);
    system->setScaleX(node.scaleX);
    system->setScaleY(node.scaleY);
    system->update(dt);
}


NS_CC_EXT_END
