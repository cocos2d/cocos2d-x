/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "editor-support/cocostudio/CCDisplayFactory.h"
#include "editor-support/cocostudio/CCBone.h"
#include "editor-support/cocostudio/CCArmature.h"
#include "editor-support/cocostudio/CCSkin.h"
#include "editor-support/cocostudio/CCArmatureDataManager.h"
#include "editor-support/cocostudio/CCTransformHelp.h"

#include "2d/CCParticleSystemQuad.h"

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
        Mat4 transform = bone->getNodeToArmatureTransform();
        display->setAdditionalTransform(&transform);
    }
    break;
    }


#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    if (dirty)
    {
        DecorativeDisplay *decoDisplay = bone->getDisplayManager()->getCurrentDecorativeDisplay();
        ColliderDetector *detector = decoDisplay->getColliderDetector();
        if (detector)
        {
            do
            {
#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
                CC_BREAK_IF(!detector->getBody());
#endif

                Mat4 displayTransform = display->getNodeToParentTransform();
                Vec2 anchorPoint =  display->getAnchorPointInPoints();
                anchorPoint = PointApplyTransform(anchorPoint, displayTransform);
                displayTransform.m[12] = anchorPoint.x;
                displayTransform.m[13] = anchorPoint.y;
                Mat4 t = TransformConcat( bone->getArmature()->getNodeToParentTransform(),displayTransform);
                detector->updateTransform(t);
            }
            while (0);
        }
    }
#endif
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
    if(textureName.empty())
    {
        skin = Skin::create();
    }
    else
    {
        skin = Skin::createWithSpriteFrameName((textureName + ".png"));
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

    TextureData *textureData = ArmatureDataManager::getInstance()->getTextureData(textureName);
    if(textureData)
    {
        //! Init display anchorPoint, every Texture have a anchor point
        skin->setAnchorPoint(Vec2( textureData->pivotX, textureData->pivotY));
    }


#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT || ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX
    if (textureData && textureData->contourDataList.size() > 0)
    {

        //! create ContourSprite
        ColliderDetector *colliderDetector = ColliderDetector::create(bone);
        colliderDetector->addContourDataList(textureData->contourDataList);

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

    Armature *armature = Armature::create(displayData->displayName, bone);

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
    ParticleSystem *system = ParticleSystemQuad::create(displayData->displayName);

    system->removeFromParent();
    system->cleanup();
    
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
