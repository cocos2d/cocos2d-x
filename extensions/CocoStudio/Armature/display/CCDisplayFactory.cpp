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

void CCDisplayFactory::updateDisplay(CCBone *bone, float dt, bool dirty)
{
    CCNode *display = bone->getDisplayRenderNode();
    CS_RETURN_IF(!display);

    switch(bone->getDisplayRenderNodeType())
    {
    case CS_DISPLAY_SPRITE:
        if (dirty)
        {
            (static_cast<CCSkin*>(display))->updateArmatureTransform();
        }
        break;
    case CS_DISPLAY_PARTICLE:
        updateParticleDisplay(bone, display, dt);
        break;
    case CS_DISPLAY_ARMATURE:
        updateArmatureDisplay(bone, display, dt);
        break;
    default:
        display->setAdditionalTransform(bone->nodeToArmatureTransform());
        break;
    }

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    if (dirty)
    {
        CCDecorativeDisplay *decoDisplay = bone->getDisplayManager()->getCurrentDecorativeDisplay();
        CCColliderDetector *detector = decoDisplay->getColliderDetector();
        if (detector)
        {
            do
            {
#if ENABLE_PHYSICS_BOX2D_DETECT
                CC_BREAK_IF(!detector->getBody());
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
                CC_BREAK_IF(!detector->getBody());
#endif

                CCAffineTransform displayTransform = display->nodeToParentTransform();
                CCPoint anchorPoint =  display->getAnchorPointInPoints();
                anchorPoint = CCPointApplyAffineTransform(anchorPoint, displayTransform);
                displayTransform.tx = anchorPoint.x;
                displayTransform.ty = anchorPoint.y;
                CCAffineTransform t = CCAffineTransformConcat(displayTransform, bone->getArmature()->nodeToParentTransform());
                detector->updateTransform(t);
            }
            while (0);
        }
    }
#endif
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

    decoDisplay->setDisplay(skin);

    if (skin == NULL)
    {
        return;
    }

    skin->setBone(bone);

    initSpriteDisplay(bone, decoDisplay, displayData->displayName.c_str(), skin);

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
}

void CCDisplayFactory::initSpriteDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, const char *displayName, CCSkin *skin)
{
    //! remove .xxx
    std::string textureName = displayName;
    size_t startPos = textureName.find_last_of(".");

    if(startPos != std::string::npos)
    {
        textureName = textureName.erase(startPos);
    }

    CCTextureData *textureData = CCArmatureDataManager::sharedArmatureDataManager()->getTextureData(textureName.c_str());
    if(textureData)
    {
        //! Init display anchorPoint, every Texture have a anchor point
        skin->setAnchorPoint(ccp( textureData->pivotX, textureData->pivotY));
    }


#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    if (textureData && textureData->contourDataList.count() > 0)
    {

        //! create ContourSprite
        CCColliderDetector *colliderDetector = CCColliderDetector::create(bone);
        colliderDetector->addContourDataList(&textureData->contourDataList);

        decoDisplay->setColliderDetector(colliderDetector);
    }
#endif
}


void CCDisplayFactory::addArmatureDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, CCDisplayData *displayData)
{
    CCArmatureDisplayData *adp = CCArmatureDisplayData::create();
    adp->copy((CCArmatureDisplayData *)displayData);
    decoDisplay->setDisplayData(adp);

    createArmatureDisplay(bone, decoDisplay);
}
void CCDisplayFactory::createArmatureDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay)
{
    CCArmatureDisplayData *displayData = (CCArmatureDisplayData *)decoDisplay->getDisplayData();

    CCArmature *armature = CCArmature::create(displayData->displayName.c_str(), bone);

    decoDisplay->setDisplay(armature);
}
void CCDisplayFactory::updateArmatureDisplay(CCBone *bone, CCNode *display, float dt)
{
    CCArmature *armature = (CCArmature *)display;
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

    CCParticleSystem *system = CCParticleSystemQuad::create(displayData->displayName.c_str());
    
    system->removeFromParent();
    
    CCArmature *armature = bone->getArmature();
    if (armature)
    {
        system->setParent(bone->getArmature());
    }

    decoDisplay->setDisplay(system);
}
void CCDisplayFactory::updateParticleDisplay(CCBone *bone, CCNode *display, float dt)
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
