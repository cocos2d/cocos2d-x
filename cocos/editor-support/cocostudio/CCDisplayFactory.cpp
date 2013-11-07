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

#include "cocostudio/CCDisplayFactory.h"
#include "cocostudio/CCBone.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CCSkin.h"
#include "cocostudio/CCSpriteFrameCacheHelper.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCTransformHelp.h"

using namespace cocos2d;

namespace cocostudio {

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

void DisplayFactory::updateDisplay(Bone *bone, float dt, bool dirty)
{
    Node *display = bone->getDisplayRenderNode();
    CS_RETURN_IF(!display);

#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
    if (dirty)
    {
        DecorativeDisplay *decoDisplay = bone->getDisplayManager()->getCurrentDecorativeDisplay();
        ColliderDetector *detector = decoDisplay->getColliderDetector();
        if (detector)
        {
            do
            {
                CC_BREAK_IF(!detector->getBody());

                AffineTransform displayTransform = display->getNodeToParentTransform();
                Point anchorPoint =  display->getAnchorPointInPoints();
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

    switch(bone->getDisplayRenderNodeType())
    {
    case CS_DISPLAY_SPRITE:
        if (dirty)
        {
            static_cast<Skin*>(display)->updateArmatureTransform();
        }
        break;
    case CS_DISPLAY_PARTICLE:
        updateParticleDisplay(bone, display, dt);
        break;
    case CS_DISPLAY_ARMATURE:
        updateArmatureDisplay(bone, display, dt);
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
    Skin *skin = nullptr;

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

    decoDisplay->setDisplay(skin);

    if (skin == nullptr)
    {
        return;
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



void DisplayFactory::addArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData)
{
    ArmatureDisplayData *adp = ArmatureDisplayData::create();
    adp->copy((ArmatureDisplayData *)displayData);
    decoDisplay->setDisplayData(adp);

    createArmatureDisplay(bone, decoDisplay);
}
void DisplayFactory::createArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay)
{
    ArmatureDisplayData *displayData = (ArmatureDisplayData *)decoDisplay->getDisplayData();

    Armature *armature = Armature::create(displayData->displayName.c_str(), bone);

    decoDisplay->setDisplay(armature);
}
void DisplayFactory::updateArmatureDisplay(Bone *bone, Node *display, float dt)
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
    ParticleDisplayData *adp = ParticleDisplayData::create();
    adp->copy((ParticleDisplayData *)displayData);
    decoDisplay->setDisplayData(adp);

    createParticleDisplay(bone, decoDisplay);
}
void DisplayFactory::createParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay)
{
    ParticleDisplayData *displayData = (ParticleDisplayData *)decoDisplay->getDisplayData();
    ParticleSystem *system = ParticleSystemQuad::create(displayData->plist.c_str());

    system->removeFromParent();
    
    Armature *armature = bone->getArmature();
    if (armature)
    {
        system->setParent(armature);
    }

    decoDisplay->setDisplay(system);
}
void DisplayFactory::updateParticleDisplay(Bone *bone, Node *display, float dt)
{
    ParticleSystem *system = (ParticleSystem *)display;
    BaseData node;
    TransformHelp::matrixToNode(bone->getNodeToArmatureTransform(), node);
    system->setPosition(node.x, node.y);
    system->setScaleX(node.scaleX);
    system->setScaleY(node.scaleY);
    system->update(dt);
}


}
