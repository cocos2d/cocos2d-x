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

NS_CC_EXT_ARMATURE_BEGIN

void DisplayFactory::addDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData)
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

void DisplayFactory::createDisplay(Bone *bone, DecorativeDisplay *decoDisplay)
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

void DisplayFactory::updateDisplay(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty)
{
    CS_RETURN_IF(!decoDisplay);

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    if (dirty)
    {
        ColliderDetector *detector = decoDisplay->getColliderDetector();
        if (detector)
        {
            do
            {
                CC_BREAK_IF(!detector->getBody());

                Node *node = decoDisplay->getDisplay();
                AffineTransform displayTransform = node->getNodeToParentTransform();
                Point anchorPoint =  node->getAnchorPointInPoints();
                anchorPoint = PointApplyAffineTransform(anchorPoint, displayTransform);
                displayTransform.tx = anchorPoint.x;
                displayTransform.ty = anchorPoint.y;
                AffineTransform t = AffineTransformConcat(displayTransform, bone->getArmature()->getNodeToParentTransform());
                detector->updateTransform(t);
            }
            while (0);
        }
    }
#endif

    Node *display = decoDisplay->getDisplay();

    switch(decoDisplay->getDisplayData()->displayType)
    {
    case CS_DISPLAY_SPRITE:
        updateSpriteDisplay(bone, display, dt, dirty);
        break;
    case CS_DISPLAY_PARTICLE:
        updateParticleDisplay(bone, display, dt, dirty);
        break;
    case CS_DISPLAY_ARMATURE:
        updateArmatureDisplay(bone, display, dt, dirty);
        break;
    default:
    {
        display->setAdditionalTransform(bone->getNodeToArmatureTransform());
    }
    break;
    }
}



void DisplayFactory::addSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData)
{
    SpriteDisplayData *sdp = SpriteDisplayData::create();
    sdp->copy((SpriteDisplayData *)displayData);
    decoDisplay->setDisplayData(sdp);
    createSpriteDisplay(bone, decoDisplay);
}

void DisplayFactory::createSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay)
{
    Skin *skin = NULL;

    SpriteDisplayData *displayData = (SpriteDisplayData *)decoDisplay->getDisplayData();

    std::string textureName = displayData->displayName;
    size_t startPos = textureName.find_last_of(".");

    if(startPos != std::string::npos)
    {
        textureName = textureName.erase(startPos);
    }

    //! create display
    if(textureName.length() == 0)
    {
        skin = Skin::create();
    }
    else
    {
        skin = Skin::createWithSpriteFrameName((textureName + ".png").c_str());
    }

    skin->setBone(bone);

    initSpriteDisplay(bone, decoDisplay, displayData->displayName.c_str(), skin);

    Armature *armature = bone->getArmature();
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

}

void DisplayFactory::initSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay, const char *displayName, Skin *skin)
{
    //! remove .xxx
    std::string textureName = displayName;
    size_t startPos = textureName.find_last_of(".");

    if(startPos != std::string::npos)
    {
        textureName = textureName.erase(startPos);
    }

    TextureData *textureData = ArmatureDataManager::getInstance()->getTextureData(textureName.c_str());
    if(textureData)
    {
        //! Init display anchorPoint, every Texture have a anchor point
        skin->setAnchorPoint(Point( textureData->pivotX, textureData->pivotY));
    }


#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    if (textureData && textureData->contourDataList.count() > 0)
    {

        //! create ContourSprite
        ColliderDetector *colliderDetector = ColliderDetector::create(bone);
        colliderDetector->addContourDataList(&textureData->contourDataList);

        decoDisplay->setColliderDetector(colliderDetector);
    }
#endif
}

void DisplayFactory::updateSpriteDisplay(Bone *bone, Node *display, float dt, bool dirty)
{
    CS_RETURN_IF(!dirty);
    Skin *skin = (Skin *)display;
    skin->updateArmatureTransform();
}


void DisplayFactory::addArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData)
{
    ArmatureDisplayData *adp = ArmatureDisplayData::create(); ;
    adp->copy((ArmatureDisplayData *)displayData);
    decoDisplay->setDisplayData(adp);

    createArmatureDisplay(bone, decoDisplay);
}
void DisplayFactory::createArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay)
{
    ArmatureDisplayData *displayData = (ArmatureDisplayData *)decoDisplay->getDisplayData();

    Armature *armature = Armature::create(displayData->displayName.c_str(), bone);

    /*
     *  because this bone have called this name, so armature should change it's name, or it can't add to
     *  Armature's bone children.
     */
    armature->setName((bone->getName() + "_armatureChild").c_str());

    decoDisplay->setDisplay(armature);
}
void DisplayFactory::updateArmatureDisplay(Bone *bone, Node *display, float dt, bool dirty)
{
    Armature *armature = (Armature *)display;
    if(armature)
    {
        armature->sortAllChildren();
        armature->update(dt);
    }
}



void DisplayFactory::addParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData)
{
    ParticleDisplayData *adp = ParticleDisplayData::create(); ;
    adp->copy((ParticleDisplayData *)displayData);
    decoDisplay->setDisplayData(adp);

    createParticleDisplay(bone, decoDisplay);
}
void DisplayFactory::createParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay)
{
    ParticleDisplayData *displayData = (ParticleDisplayData *)decoDisplay->getDisplayData();
    ParticleSystem *system = ParticleSystemQuad::create(displayData->plist.c_str());
    decoDisplay->setDisplay(system);
}
void DisplayFactory::updateParticleDisplay(Bone *bone, Node *display, float dt, bool dirty)
{
    ParticleSystem *system = (ParticleSystem *)display;
    BaseData node;
    TransformHelp::matrixToNode(bone->getNodeToArmatureTransform(), node);
    system->setPosition(node.x, node.y);
    system->setScaleX(node.scaleX);
    system->setScaleY(node.scaleY);
    system->update(dt);
}


NS_CC_EXT_ARMATURE_END
