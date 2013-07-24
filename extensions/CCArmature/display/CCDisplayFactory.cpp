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
#include "../display/CCShaderNode.h"
#include "../utils/CCSpriteFrameCacheHelper.h"
#include "../utils/CCArmatureDataManager.h"
#include "../utils/CCTransformHelp.h"

namespace cocos2d { namespace extension { namespace armature {

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

#if ENABLE_PHYSICS_DETECT
    if (dirty)
    {
        ColliderDetector *detector = decoDisplay->getColliderDetector();
        if (detector)
        {
            AffineTransform t = AffineTransformConcat(bone->nodeToArmatureTransform(), bone->getArmature()->getNodeToWorldTransform());
            detector->updateTransform(t);
        }
    }
#endif


    switch(decoDisplay->getDisplayData()->displayType)
    {
    case CS_DISPLAY_SPRITE:
        updateSpriteDisplay(bone, decoDisplay, dt, dirty);
        break;
    case CS_DISPLAY_PARTICLE:
        updateParticleDisplay(bone, decoDisplay, dt, dirty);
        break;
    case CS_DISPLAY_ARMATURE:
        updateArmatureDisplay(bone, decoDisplay, dt, dirty);
        break;
    default:
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
        skin = Skin::create();
    }
    else
    {
        skin = Skin::createWithSpriteFrameName((textureName + ".png").c_str());
    }

    TextureAtlas *atlas = SpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()->getTextureAtlas((textureName + ".png").c_str());
    skin->setTextureAtlas(atlas);

    TextureData *textureData = ArmatureDataManager::sharedArmatureDataManager()->getTextureData(textureName.c_str());
    if(textureData)
    {
        //! Init display anchorPoint, every Texture have a anchor point
        skin->setAnchorPoint(Point( textureData->pivotX, textureData->pivotY));
    }

    skin->setBone(bone);
    skin->setSkinData(*bone->getBoneData());

    decoDisplay->setDisplay(skin);

#if ENABLE_PHYSICS_DETECT
    if (textureData && textureData->contourDataList.count() > 0)
    {

        //! create ContourSprite
        ColliderDetector *colliderDetector = ColliderDetector::create(bone);
        colliderDetector->addContourDataList(&textureData->contourDataList);

        decoDisplay->setColliderDetector(colliderDetector);
    }
#endif
}

void DisplayFactory::updateSpriteDisplay(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty)
{
    Skin *skin = (Skin *)decoDisplay->getDisplay();
    skin->updateTransform();
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
void DisplayFactory::updateArmatureDisplay(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty)
{
    CS_RETURN_IF(!dirty);

    Armature *armature = bone->getChildArmature();
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
void DisplayFactory::updateParticleDisplay(Bone *bone, DecorativeDisplay *decoDisplay, float dt, bool dirty)
{
    ParticleSystem *system = (ParticleSystem *)decoDisplay->getDisplay();
    BaseData node;
    TransformHelp::matrixToNode(bone->nodeToArmatureTransform(), node);
    system->setPosition(node.x, node.y);
    system->setScaleX(node.scaleX);
    system->setScaleY(node.scaleY);
    system->update(dt);
}



void DisplayFactory::addShaderDisplay(Bone *bone, DecorativeDisplay *decoDisplay, DisplayData *displayData)
{
    ShaderDisplayData *sdp = ShaderDisplayData::create();
    sdp->copy((ShaderDisplayData *)displayData);
    decoDisplay->setDisplayData(sdp);

    createShaderDisplay(bone, decoDisplay);
}
void DisplayFactory::createShaderDisplay(Bone *bone, DecorativeDisplay *decoDisplay)
{
    ShaderDisplayData *displayData = (ShaderDisplayData *)decoDisplay->getDisplayData();
    ShaderNode *sn = ShaderNode::shaderNodeWithVertex(displayData->vert.c_str(), displayData->frag.c_str());
    decoDisplay->setDisplay(sn);
}

}}} // namespace cocos2d { namespace extension { namespace armature {
