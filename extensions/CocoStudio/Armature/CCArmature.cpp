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

#include "CCArmature.h"
#include "utils/CCArmatureDataManager.h"
#include "utils/CCArmatureDefine.h"
#include "utils/CCDataReaderHelper.h"
#include "datas/CCDatas.h"
#include "display/CCSkin.h"

#if ENABLE_PHYSICS_BOX2D_DETECT
#include "Box2D/Box2D.h"
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "chipmunk.h"
#endif


NS_CC_EXT_ARMATURE_BEGIN

std::map<int, Armature *> Armature::m_sArmatureIndexDic;

Armature *Armature::create()
{
    Armature *armature = new Armature();
    if (armature && armature->init())
    {
        armature->autorelease();
        return armature;
    }
    CC_SAFE_DELETE(armature);
    return NULL;
}


Armature *Armature::create(const char *name)
{
    Armature *armature = new Armature();
    if (armature && armature->init(name))
    {
        armature->autorelease();
        return armature;
    }
    CC_SAFE_DELETE(armature);
    return NULL;
}

Armature *Armature::create(const char *name, Bone *parentBone)
{
    Armature *armature = new Armature();
    if (armature && armature->init(name, parentBone))
    {
        armature->autorelease();
        return armature;
    }
    CC_SAFE_DELETE(armature);
    return NULL;
}

Armature::Armature()
    : m_pArmatureData(NULL)
    , m_pBatchNode(NULL)
    , m_pAtlas(NULL)
    , m_pParentBone(NULL)
    , m_bArmatureTransformDirty(true)
    , m_pBoneDic(NULL)
    , m_pTopBoneList(NULL)
    , m_pAnimation(NULL)
{
}


Armature::~Armature(void)
{
    if(NULL != m_pBoneDic)
    {
        m_pBoneDic->removeAllObjects();
        CC_SAFE_DELETE(m_pBoneDic);
    }
    if (NULL != m_pTopBoneList)
    {
        m_pTopBoneList->removeAllObjects();
        CC_SAFE_DELETE(m_pTopBoneList);
    }
    CC_SAFE_DELETE(m_pAnimation);
}


bool Armature::init()
{
    return init(NULL);
}


bool Armature::init(const char *name)
{
    bool bRet = false;
    do
    {
        removeAllChildren();

        CC_SAFE_DELETE(m_pAnimation);
        m_pAnimation = new ArmatureAnimation();
        m_pAnimation->init(this);

        CC_SAFE_DELETE(m_pBoneDic);
        m_pBoneDic	= new Dictionary();

        CC_SAFE_DELETE(m_pTopBoneList);
        m_pTopBoneList = new Array();
        m_pTopBoneList->init();


        m_sBlendFunc.src = CC_BLEND_SRC;
        m_sBlendFunc.dst = CC_BLEND_DST;


        m_strName = name == NULL ? "" : name;

        ArmatureDataManager *armatureDataManager = ArmatureDataManager::sharedArmatureDataManager();

        if(m_strName.length() != 0)
        {
            m_strName = name;

            AnimationData *animationData = armatureDataManager->getAnimationData(name);
            CCAssert(animationData, "AnimationData not exist! ");

            m_pAnimation->setAnimationData(animationData);


            ArmatureData *armatureData = armatureDataManager->getArmatureData(name);
            CCAssert(armatureData, "");

            m_pArmatureData = armatureData;


            DictElement *_element = NULL;
            Dictionary *boneDataDic = &armatureData->boneDataDic;
            CCDICT_FOREACH(boneDataDic, _element)
            {
                Bone *bone = createBone(_element->getStrKey());

                //! init bone's  Tween to 1st movement's 1st frame
                do
                {

                    MovementData *movData = animationData->getMovement(animationData->movementNames.at(0).c_str());
                    CC_BREAK_IF(!movData);

                    MovementBoneData *movBoneData = movData->getMovementBoneData(bone->getName().c_str());
                    CC_BREAK_IF(!movBoneData || movBoneData->frameList.count() <= 0);

                    FrameData *frameData = movBoneData->getFrameData(0);
                    CC_BREAK_IF(!frameData);

                    bone->getTweenData()->copy(frameData);
                    bone->changeDisplayByIndex(frameData->displayIndex, false);
                }
                while (0);
            }

            update(0);
            updateOffsetPoint();
        }
        else
        {
            m_strName = "new_armature";
            m_pArmatureData = ArmatureData::create();
            m_pArmatureData->name = m_strName;

            AnimationData *animationData = AnimationData::create();
            animationData->name = m_strName;

            armatureDataManager->addArmatureData(m_strName.c_str(), m_pArmatureData);
            armatureDataManager->addAnimationData(m_strName.c_str(), animationData);

            m_pAnimation->setAnimationData(animationData);

        }

        setShaderProgram(CCShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

        unscheduleUpdate();
        scheduleUpdate();

        setCascadeOpacityEnabled(true);
        setCascadeColorEnabled(true);

        bRet = true;
    }
    while (0);

    return bRet;
}

bool Armature::init(const char *name, Bone *parentBone)
{
    m_pParentBone = parentBone;
    return init(name);
}


Bone *Armature::createBone(const char *boneName)
{
    Bone *existedBone = getBone(boneName);
    if(existedBone != NULL)
        return existedBone;

    BoneData *boneData = (BoneData *)m_pArmatureData->getBoneData(boneName);
    std::string parentName = boneData->parentName;

    Bone *bone = NULL;

    if( parentName.length() != 0 )
    {
        createBone(parentName.c_str());
        bone = Bone::create(boneName);
        addBone(bone, parentName.c_str());
    }
    else
    {
        bone = Bone::create(boneName);
        addBone(bone, "");
    }

    bone->setBoneData(boneData);
    bone->getDisplayManager()->changeDisplayByIndex(-1, false);

    return bone;
}


void Armature::addBone(Bone *bone, const char *parentName)
{
    CCAssert( bone != NULL, "Argument must be non-nil");
    CCAssert(m_pBoneDic->objectForKey(bone->getName()) == NULL, "bone already added. It can't be added again");

    if (NULL != parentName)
    {
        Bone *boneParent = (Bone *)m_pBoneDic->objectForKey(parentName);
        if (boneParent)
        {
            boneParent->addChildBone(bone);
        }
        else
        {
            if (m_pParentBone)
                m_pParentBone->addChildBone(bone);
            else
                m_pTopBoneList->addObject(bone);
        }
    }
    else
    {
        if (m_pParentBone)
            m_pParentBone->addChildBone(bone);
        else
            m_pTopBoneList->addObject(bone);
    }

    bone->setArmature(this);

    m_pBoneDic->setObject(bone, bone->getName());
    addChild(bone);
}


void Armature::removeBone(Bone *bone, bool recursion)
{
    CCAssert(bone != NULL, "bone must be added to the bone dictionary!");

    bone->setArmature(NULL);
    bone->removeFromParent(recursion);

    if (m_pTopBoneList->containsObject(bone))
    {
        m_pTopBoneList->removeObject(bone);
    }
    m_pBoneDic->removeObjectForKey(bone->getName());
    removeChild(bone, true);
}


Bone *Armature::getBone(const char *name) const
{
    return (Bone *)m_pBoneDic->objectForKey(name);
}


void Armature::changeBoneParent(Bone *bone, const char *parentName)
{
    CCAssert(bone != NULL, "bone must be added to the bone dictionary!");

    if(bone->getParentBone())
    {
        bone->getParentBone()->getChildren()->removeObject(bone);
        bone->setParentBone(NULL);
    }

    if (parentName != NULL)
    {
        Bone *boneParent = (Bone *)m_pBoneDic->objectForKey(parentName);

        if (boneParent)
        {
            boneParent->addChildBone(bone);
            if (m_pTopBoneList->containsObject(bone))
            {
                m_pTopBoneList->removeObject(bone);
            }
        }
        else
        {
            m_pTopBoneList->addObject(bone);
        }
    }
}

Dictionary *Armature::getBoneDic()
{
    return m_pBoneDic;
}

const AffineTransform& Armature::getNodeToParentTransform() const
{
    if (_transformDirty)
    {
        m_bArmatureTransformDirty = true;

        // Translate values
        float x = _position.x;
        float y = _position.y;

        if (_ignoreAnchorPointForPosition)
        {
            x += _anchorPointInPoints.x;
            y += _anchorPointInPoints.y;
        }

        // Rotation values
        // Change rotation code to handle X and Y
        // If we skew with the exact same value for both x and y then we're simply just rotating
        float cx = 1, sx = 0, cy = 1, sy = 0;
        if (_rotationX || _rotationY)
        {
            float radiansX = -CC_DEGREES_TO_RADIANS(_rotationX);
            float radiansY = -CC_DEGREES_TO_RADIANS(_rotationY);
            cx = cosf(radiansX);
            sx = sinf(radiansX);
            cy = cosf(radiansY);
            sy = sinf(radiansY);
        }

        // Add offset point
        x += cy * m_pOffsetPoint.x * _scaleX + -sx * m_pOffsetPoint.y * _scaleY;
        y += sy * m_pOffsetPoint.x * _scaleX + cx * m_pOffsetPoint.y * _scaleY;

        bool needsSkewMatrix = ( _skewX || _skewY );

        // optimization:
        // inline anchor point calculation if skew is not needed
        // Adjusted transform calculation for rotational skew
        if (! needsSkewMatrix && !_anchorPointInPoints.equals(Point::ZERO))
        {
            x += cy * -_anchorPointInPoints.x * _scaleX + -sx * -_anchorPointInPoints.y * _scaleY;
            y += sy * -_anchorPointInPoints.x * _scaleX +  cx * -_anchorPointInPoints.y * _scaleY;
        }


        // Build Transform Matrix
        // Adjusted transform calculation for rotational skew
        _transform = AffineTransformMake( cy * _scaleX,  sy * _scaleX,
                                              -sx * _scaleY, cx * _scaleY,
                                              x, y );

        // XXX: Try to inline skew
        // If skew is needed, apply skew and then anchor point
        if (needsSkewMatrix)
        {
            AffineTransform skewMatrix = AffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(_skewY)),
                                           tanf(CC_DEGREES_TO_RADIANS(_skewX)), 1.0f,
                                           0.0f, 0.0f );
            _transform = AffineTransformConcat(skewMatrix, _transform);

            // adjust anchor point
            if (!_anchorPointInPoints.equals(Point::ZERO))
            {
                _transform = AffineTransformTranslate(_transform, -_anchorPointInPoints.x, -_anchorPointInPoints.y);
            }
        }

        if (_additionalTransformDirty)
        {
            _transform = AffineTransformConcat(_transform, _additionalTransform);
            _additionalTransformDirty = false;
        }

        _transformDirty = false;
    }

    return _transform;
}

void Armature::updateOffsetPoint()
{
    // Set contentsize and Calculate anchor point.
    Rect rect = boundingBox();
    setContentSize(rect.size);
    m_pOffsetPoint = Point(-rect.origin.x,  -rect.origin.y);
    if (rect.size.width != 0 && rect.size.height != 0)
    {
        setAnchorPoint(Point(m_pOffsetPoint.x / rect.size.width, m_pOffsetPoint.y / rect.size.height));
    }
}

void Armature::setAnimation(ArmatureAnimation *animation)
{
    m_pAnimation = animation;
}

ArmatureAnimation *Armature::getAnimation()
{
    return m_pAnimation;
}

bool Armature::getArmatureTransformDirty()
{
    return m_bArmatureTransformDirty;
}

void Armature::update(float dt)
{
    m_pAnimation->update(dt);

    Object *object = NULL;
    CCARRAY_FOREACH(m_pTopBoneList, object)
    {
        ((Bone *)object)->update(dt);
    }

    m_bArmatureTransformDirty = false;
}

void Armature::draw()
{
    if (m_pParentBone == NULL)
    {
        CC_NODE_DRAW_SETUP();
        GL::blendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
    }

    Object *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        if (Bone *bone = dynamic_cast<Bone *>(object))
        {
            DisplayManager *displayManager = bone->getDisplayManager();
            Node *node = displayManager->getDisplayRenderNode();

            if (NULL == node)
                continue;

            switch (displayManager->getCurrentDecorativeDisplay()->getDisplayData()->displayType)
            {
            case CS_DISPLAY_SPRITE:
            {
                Skin *skin = (Skin *)node;

                TextureAtlas *textureAtlas = skin->getTextureAtlas();
                BlendType blendType = bone->getBlendType();
                if(m_pAtlas != textureAtlas || blendType != BLEND_NORMAL)
                {
                    if (m_pAtlas)
                    {
                        m_pAtlas->drawQuads();
                        m_pAtlas->removeAllQuads();
                    }
                }

                m_pAtlas = textureAtlas;
                if (m_pAtlas->getCapacity() == m_pAtlas->getTotalQuads() && !m_pAtlas->resizeCapacity(m_pAtlas->getCapacity() * 2))
                    return;

                skin->updateTransform();

                if (blendType != BLEND_NORMAL)
                {
                    updateBlendType(blendType);
                    m_pAtlas->drawQuads();
                    m_pAtlas->removeAllQuads();
                    GL::blendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
                }
            }
            break;
            case CS_DISPLAY_ARMATURE:
            {
                Armature *armature = (Armature *)(node);

                TextureAtlas *textureAtlas = armature->getTextureAtlas();
                if(m_pAtlas != textureAtlas)
                {
                    if (m_pAtlas)
                    {
                        m_pAtlas->drawQuads();
                        m_pAtlas->removeAllQuads();
                    }
                }
                armature->draw();
            }
            break;
            default:
            {
                if (m_pAtlas)
                {
                    m_pAtlas->drawQuads();
                    m_pAtlas->removeAllQuads();
                }
                node->visit();

                CC_NODE_DRAW_SETUP();
                GL::blendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
            }
            break;
            }
        }
        else if(Node *node = dynamic_cast<Node *>(object))
        {
            if (m_pAtlas)
            {
                m_pAtlas->drawQuads();
                m_pAtlas->removeAllQuads();
            }
            node->visit();

            CC_NODE_DRAW_SETUP();
            GL::blendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
        }
    }

    if(m_pAtlas && !m_pBatchNode && m_pParentBone == NULL)
    {
        m_pAtlas->drawQuads();
        m_pAtlas->removeAllQuads();
    }
}


void Armature::updateBlendType(BlendType blendType)
{
    BlendFunc blendFunc;
    switch (blendType)
    {
    case BLEND_NORMAL:
    {
        blendFunc.src = CC_BLEND_SRC;
        blendFunc.dst = CC_BLEND_DST;
    }
    break;
    case BLEND_ADD:
    {
        blendFunc.src = GL_SRC_ALPHA;
        blendFunc.dst = GL_ONE;
    }
    break;
    case BLEND_MULTIPLY:
    {
        blendFunc.src = GL_DST_COLOR;
        blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
    }
    break;
    case BLEND_SCREEN:
    {
        blendFunc.src = GL_ONE;
        blendFunc.dst = GL_ONE_MINUS_SRC_COLOR;
    }
    break;
    default:
    {
        blendFunc.src = CC_BLEND_SRC;
        blendFunc.dst = CC_BLEND_DST;
    }
    break;
    }
    GL::blendFunc(blendFunc.src, blendFunc.dst);
}



void Armature::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }
    kmGLPushMatrix();

    if (_grid && _grid->isActive())
    {
        _grid->beforeDraw();
    }

    transform();
    sortAllChildren();
    draw();

    // reset for next frame
    _orderOfArrival = 0;

    if (_grid && _grid->isActive())
    {
        _grid->afterDraw(this);
    }

    kmGLPopMatrix();
}

Rect Armature::getBoundingBox() const
{
    float minx, miny, maxx, maxy = 0;

    bool first = true;

    Rect boundingBox = Rect(0, 0, 0, 0);

    Object *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        if (Bone *bone = dynamic_cast<Bone *>(object))
        {
            Rect r = bone->getDisplayManager()->getBoundingBox();

            if(first)
            {
                minx = r.getMinX();
                miny = r.getMinY();
                maxx = r.getMaxX();
                maxy = r.getMaxY();

                first = false;
            }
            else
            {
                minx = r.getMinX() < boundingBox.getMinX() ? r.getMinX() : boundingBox.getMinX();
                miny = r.getMinY() < boundingBox.getMinY() ? r.getMinY() : boundingBox.getMinY();
                maxx = r.getMaxX() > boundingBox.getMaxX() ? r.getMaxX() : boundingBox.getMaxX();
                maxy = r.getMaxY() > boundingBox.getMaxY() ? r.getMaxY() : boundingBox.getMaxY();
            }

            boundingBox.setRect(minx, miny, maxx - minx, maxy - miny);
        }
    }

    return boundingBox;
}

Bone *Armature::getBoneAtPoint(float x, float y)
{
    int length = _children->data->num;
    Bone **bs = (Bone **)_children->data->arr;

    for(int i = length - 1; i >= 0; i--)
    {
        if(bs[i]->getDisplayManager()->containPoint(x, y))
        {
            return bs[i];
        }
    }
    return NULL;
}

#if ENABLE_PHYSICS_BOX2D_DETECT
b2Body *Armature::getBody()
{
    return m_pBody;
}

void Armature::setBody(b2Body *body)
{
    if (m_pBody == body)
    {
        return;
    }

    m_pBody = body;
    m_pBody->SetUserData(this);

    Object *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        if (Bone *bone = dynamic_cast<Bone *>(object))
        {
            Array *displayList = bone->getDisplayManager()->getDecorativeDisplayList();

            Object *displayObject = NULL;
            CCARRAY_FOREACH(displayList, displayObject)
            {
                ColliderDetector *detector = ((DecorativeDisplay *)displayObject)->getColliderDetector();
                if (detector != NULL)
                {
                    detector->setBody(m_pBody);
                }
            }
        }
    }
}

b2Fixture *Armature::getShapeList()
{
    if (m_pBody)
    {
        return m_pBody->GetFixtureList();
    }
    else
    {
        return NULL;
    }
}

#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
cpBody *Armature::getBody()
{
    return m_pBody;
}

void Armature::setBody(cpBody *body)
{
    if (m_pBody == body)
    {
        return;
    }

    m_pBody = body;
    m_pBody->data = this;

    Object *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        if (Bone *bone = dynamic_cast<Bone *>(object))
        {
            Array *displayList = bone->getDisplayManager()->getDecorativeDisplayList();

            Object *displayObject = NULL;
            CCARRAY_FOREACH(displayList, displayObject)
            {
                ColliderDetector *detector = ((DecorativeDisplay *)displayObject)->getColliderDetector();
                if (detector != NULL)
                {
                    detector->setBody(m_pBody);
                }
            }
        }
    }
}

cpShape *Armature::getShapeList()
{
    if (m_pBody)
    {
        return m_pBody->shapeList_private;
    }
    else
    {
        return NULL;
    }
}
#endif


NS_CC_EXT_ARMATURE_END
