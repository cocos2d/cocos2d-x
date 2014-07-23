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


NS_CC_EXT_BEGIN

std::map<int, CCArmature *> CCArmature::m_sArmatureIndexDic;

CCArmature *CCArmature::create()
{
    CCArmature *armature = new CCArmature();
    if (armature && armature->init())
    {
        armature->autorelease();
        return armature;
    }
    CC_SAFE_DELETE(armature);
    return NULL;
}


CCArmature *CCArmature::create(const char *name)
{
    CCArmature *armature = new CCArmature();
    if (armature && armature->init(name))
    {
        armature->autorelease();
        return armature;
    }
    CC_SAFE_DELETE(armature);
    return NULL;
}

CCArmature *CCArmature::create(const char *name, CCBone *parentBone)
{
    CCArmature *armature = new CCArmature();
    if (armature && armature->init(name, parentBone))
    {
        armature->autorelease();
        return armature;
    }
    CC_SAFE_DELETE(armature);
    return NULL;
}

CCArmature::CCArmature()
    : m_pArmatureData(NULL)
    , m_pBatchNode(NULL)
    , m_pAtlas(NULL)
    , m_pParentBone(NULL)
    , m_bArmatureTransformDirty(true)
    , m_pBoneDic(NULL)
    , m_pTopBoneList(NULL)
    , m_pAnimation(NULL)
    , m_pTextureAtlasDic(NULL)
{
}


CCArmature::~CCArmature(void)
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
    CC_SAFE_RELEASE_NULL(m_pTextureAtlasDic);
}


bool CCArmature::init()
{
    return init(NULL);
}


bool CCArmature::init(const char *name)
{
    bool bRet = false;
    do
    {
        removeAllChildren();

        CC_SAFE_DELETE(m_pAnimation);
        m_pAnimation = new CCArmatureAnimation();
        m_pAnimation->init(this);

        CC_SAFE_DELETE(m_pBoneDic);
        m_pBoneDic	= new CCDictionary();

        CC_SAFE_DELETE(m_pTopBoneList);
        m_pTopBoneList = new CCArray();
        m_pTopBoneList->init();

        CC_SAFE_DELETE(m_pTextureAtlasDic);
        m_pTextureAtlasDic = new CCDictionary();

        m_sBlendFunc.src = CC_BLEND_SRC;
        m_sBlendFunc.dst = CC_BLEND_DST;


        m_strName = name == NULL ? "" : name;

        CCArmatureDataManager *armatureDataManager = CCArmatureDataManager::sharedArmatureDataManager();

        if(m_strName.length() != 0)
        {
            m_strName = name;

            CCAnimationData *animationData = armatureDataManager->getAnimationData(name);
            CCAssert(animationData, "CCAnimationData not exist! ");

            m_pAnimation->setAnimationData(animationData);


            CCArmatureData *armatureData = armatureDataManager->getArmatureData(name);
            CCAssert(armatureData, "");

            m_pArmatureData = armatureData;


            CCDictElement *_element = NULL;
            CCDictionary *boneDataDic = &armatureData->boneDataDic;
            CCDICT_FOREACH(boneDataDic, _element)
            {
                CCBone *bone = createBone(_element->getStrKey());

                //! init bone's  CCTween to 1st movement's 1st frame
                do
                {

                    CCMovementData *movData = animationData->getMovement(animationData->movementNames.at(0).c_str());
                    CC_BREAK_IF(!movData);

                    CCMovementBoneData *movBoneData = movData->getMovementBoneData(bone->getName().c_str());
                    CC_BREAK_IF(!movBoneData || movBoneData->frameList.count() <= 0);

                    CCFrameData *frameData = movBoneData->getFrameData(0);
                    CC_BREAK_IF(!frameData);

                    bone->getTweenData()->copy(frameData);
                    bone->changeDisplayWithIndex(frameData->displayIndex, false);
                }
                while (0);
            }

            update(0);
            updateOffsetPoint();
        }
        else
        {
            m_strName = "new_armature";
            m_pArmatureData = CCArmatureData::create();
            m_pArmatureData->name = m_strName;

            CCAnimationData *animationData = CCAnimationData::create();
            animationData->name = m_strName;

            armatureDataManager->addArmatureData(m_strName.c_str(), m_pArmatureData);
            armatureDataManager->addAnimationData(m_strName.c_str(), animationData);

            m_pAnimation->setAnimationData(animationData);

        }

        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));

        setCascadeOpacityEnabled(true);
        setCascadeColorEnabled(true);

        bRet = true;
    }
    while (0);

    return bRet;
}

bool CCArmature::init(const char *name, CCBone *parentBone)
{
    m_pParentBone = parentBone;
    return init(name);
}


CCBone *CCArmature::createBone(const char *boneName)
{
    CCBone *existedBone = getBone(boneName);
    if(existedBone != NULL)
        return existedBone;

    CCBoneData *boneData = (CCBoneData *)m_pArmatureData->getBoneData(boneName);
    std::string parentName = boneData->parentName;

    CCBone *bone = NULL;

    if( parentName.length() != 0 )
    {
        createBone(parentName.c_str());
        bone = CCBone::create(boneName);
        addBone(bone, parentName.c_str());
    }
    else
    {
        bone = CCBone::create(boneName);
        addBone(bone, "");
    }

    bone->setBoneData(boneData);
    bone->getDisplayManager()->changeDisplayWithIndex(-1, false);

    return bone;
}


void CCArmature::addBone(CCBone *bone, const char *parentName)
{
    CCAssert( bone != NULL, "Argument must be non-nil");
    CCAssert(m_pBoneDic->objectForKey(bone->getName()) == NULL, "bone already added. It can't be added again");

    if (NULL != parentName)
    {
        CCBone *boneParent = (CCBone *)m_pBoneDic->objectForKey(parentName);
        if (boneParent)
        {
            boneParent->addChildBone(bone);
        }
        else
        {
            m_pTopBoneList->addObject(bone);
        }
    }
    else
    {
        m_pTopBoneList->addObject(bone);
    }

    bone->setArmature(this);

    m_pBoneDic->setObject(bone, bone->getName());
    addChild(bone);
}


void CCArmature::removeBone(CCBone *bone, bool recursion)
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


CCBone *CCArmature::getBone(const char *name) const
{
    return (CCBone *)m_pBoneDic->objectForKey(name);
}


void CCArmature::changeBoneParent(CCBone *bone, const char *parentName)
{
    CCAssert(bone != NULL, "bone must be added to the bone dictionary!");

    if(bone->getParentBone())
    {
        bone->getParentBone()->getChildren()->removeObject(bone);
        bone->setParentBone(NULL);
    }

    if (parentName != NULL)
    {
        CCBone *boneParent = (CCBone *)m_pBoneDic->objectForKey(parentName);

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

CCDictionary *CCArmature::getBoneDic()
{
    return m_pBoneDic;
}

CCAffineTransform CCArmature::nodeToParentTransform()
{
    if (m_bTransformDirty)
    {
        m_bArmatureTransformDirty = true;

        // Translate values
        float x = m_obPosition.x;
        float y = m_obPosition.y;

        if (m_bIgnoreAnchorPointForPosition)
        {
            x += m_obAnchorPointInPoints.x;
            y += m_obAnchorPointInPoints.y;
        }

        // Rotation values
        // Change rotation code to handle X and Y
        // If we skew with the exact same value for both x and y then we're simply just rotating
        float cx = 1, sx = 0, cy = 1, sy = 0;
        if (m_fRotationX || m_fRotationY)
        {
            float radiansX = -CC_DEGREES_TO_RADIANS(m_fRotationX);
            float radiansY = -CC_DEGREES_TO_RADIANS(m_fRotationY);
            cx = cosf(radiansX);
            sx = sinf(radiansX);
            cy = cosf(radiansY);
            sy = sinf(radiansY);
        }

        // Add offset point
        x += cy * m_pOffsetPoint.x * m_fScaleX + -sx * m_pOffsetPoint.y * m_fScaleY;
        y += sy * m_pOffsetPoint.x * m_fScaleX + cx * m_pOffsetPoint.y * m_fScaleY;

        bool needsSkewMatrix = ( m_fSkewX || m_fSkewY );

        // optimization:
        // inline anchor point calculation if skew is not needed
        // Adjusted transform calculation for rotational skew
        if (! needsSkewMatrix && !m_obAnchorPointInPoints.equals(CCPointZero))
        {
            x += cy * -m_obAnchorPointInPoints.x * m_fScaleX + -sx * -m_obAnchorPointInPoints.y * m_fScaleY;
            y += sy * -m_obAnchorPointInPoints.x * m_fScaleX +  cx * -m_obAnchorPointInPoints.y * m_fScaleY;
        }


        // Build Transform Matrix
        // Adjusted transform calculation for rotational skew
        m_sTransform = CCAffineTransformMake( cy * m_fScaleX,  sy * m_fScaleX,
                                              -sx * m_fScaleY, cx * m_fScaleY,
                                              x, y );

        // XXX: Try to inline skew
        // If skew is needed, apply skew and then anchor point
        if (needsSkewMatrix)
        {
            CCAffineTransform skewMatrix = CCAffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(m_fSkewY)),
                                           tanf(CC_DEGREES_TO_RADIANS(m_fSkewX)), 1.0f,
                                           0.0f, 0.0f );
            m_sTransform = CCAffineTransformConcat(skewMatrix, m_sTransform);

            // adjust anchor point
            if (!m_obAnchorPointInPoints.equals(CCPointZero))
            {
                m_sTransform = CCAffineTransformTranslate(m_sTransform, -m_obAnchorPointInPoints.x, -m_obAnchorPointInPoints.y);
            }
        }

        if (m_bAdditionalTransformDirty)
        {
            m_sTransform = CCAffineTransformConcat(m_sTransform, m_sAdditionalTransform);
            m_bAdditionalTransformDirty = false;
        }

        m_bTransformDirty = false;
    }

    return m_sTransform;
}

void CCArmature::onEnter()
{
    CCNode::onEnter();
    scheduleUpdate();
}

void CCArmature::onExit()
{
    CCNode::onExit();
    unscheduleUpdate();
}

void CCArmature::updateOffsetPoint()
{
    // Set contentsize and Calculate anchor point.
    CCRect rect = boundingBox();
    setContentSize(rect.size);
    m_pOffsetPoint = ccp(-rect.origin.x,  -rect.origin.y);
    if (rect.size.width != 0 && rect.size.height != 0)
    {
        setAnchorPoint(ccp(m_pOffsetPoint.x / rect.size.width, m_pOffsetPoint.y / rect.size.height));
    }
}

void CCArmature::setAnimation(CCArmatureAnimation *animation)
{
    m_pAnimation = animation;
}

CCArmatureAnimation *CCArmature::getAnimation()
{
    return m_pAnimation;
}

void CCArmature::update(float dt)
{
    m_pAnimation->update(dt);

    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pTopBoneList, object)
    {
        ((CCBone *)object)->update(dt);
    }

    m_bArmatureTransformDirty = false;
}

void CCArmature::draw()
{
    if (m_pParentBone == NULL && m_pBatchNode == NULL)
    {
        CC_NODE_DRAW_SETUP();
        ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
    }

    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pChildren, object)
    {
        if (CCBone *bone = dynamic_cast<CCBone *>(object))
        {
            CCNode *node = bone->getDisplayRenderNode();

            if (NULL == node)
                continue;

            switch (bone->getDisplayRenderNodeType())
            {
            case CS_DISPLAY_SPRITE:
            {
                CCSkin *skin = (CCSkin *)node;

                CCTextureAtlas *textureAtlas = skin->getTextureAtlas();

                ccBlendFunc func = bone->getBlendFunc();
                bool blendDirty = func.src != CC_BLEND_SRC || func.dst != CC_BLEND_DST;

                if(m_pAtlas != textureAtlas || blendDirty)
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

                if (blendDirty)
                {
                    ccGLBlendFunc(func.src, func.dst);

                    m_pAtlas->drawQuads();
                    m_pAtlas->removeAllQuads();

                    ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
                }
            }
            break;
            case CS_DISPLAY_ARMATURE:
            {
                CCArmature *armature = (CCArmature *)(node);

                CCTextureAtlas *textureAtlas = armature->getTextureAtlas();
                if(m_pAtlas != textureAtlas)
                {
                    if (m_pAtlas)
                    {
                        m_pAtlas->drawQuads();
                        m_pAtlas->removeAllQuads();
                    }
                }
                armature->draw();

                m_pAtlas = armature->getTextureAtlas();
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
                ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
            }
            break;
            }
        }
        else if(CCNode *node = dynamic_cast<CCNode *>(object))
        {
            if (m_pAtlas)
            {
                m_pAtlas->drawQuads();
                m_pAtlas->removeAllQuads();
            }
            node->visit();

            CC_NODE_DRAW_SETUP();
            ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
        }
    }

    if(m_pAtlas && !m_pBatchNode && m_pParentBone == NULL)
    {
        m_pAtlas->drawQuads();
        m_pAtlas->removeAllQuads();
    }
}


void CCArmature::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!m_bVisible)
    {
        return;
    }
    kmGLPushMatrix();

    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
    }

    transform();
    sortAllChildren();
    draw();

    // reset for next frame
    m_uOrderOfArrival = 0;

    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->afterDraw(this);
    }

    kmGLPopMatrix();
}

CCRect CCArmature::boundingBox()
{
    float minx, miny, maxx, maxy = 0;

    bool first = true;

    CCRect boundingBox = CCRectMake(0, 0, 0, 0);

    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pChildren, object)
    {
        if (CCBone *bone = dynamic_cast<CCBone *>(object))
        {
            CCRect r = bone->getDisplayManager()->getBoundingBox();
            if (r.size.width == 0 || r.size.height == 0) 
                continue;

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

    return CCRectApplyAffineTransform(boundingBox, nodeToParentTransform());
}

CCBone *CCArmature::getBoneAtPoint(float x, float y)
{
    int length = m_pChildren->data->num;
    CCBone **bs = (CCBone **)m_pChildren->data->arr;

    for(int i = length - 1; i >= 0; i--)
    {
        if(bs[i]->getDisplayManager()->containPoint(x, y))
        {
            return bs[i];
        }
    }
    return NULL;
}

CCTextureAtlas *CCArmature::getTexureAtlasWithTexture(CCTexture2D *texture)
{
    int key = texture->getName();

    if (m_pParentBone && m_pParentBone->getArmature())
    {
        return m_pParentBone->getArmature()->getTexureAtlasWithTexture(texture);
    }
    else if (m_pBatchNode)
    {
        m_pBatchNode->getTexureAtlasWithTexture(texture);
    }

    CCTextureAtlas *atlas = (CCTextureAtlas *)m_pTextureAtlasDic->objectForKey(key);
    if (atlas == NULL)
    {
        atlas = CCTextureAtlas::createWithTexture(texture, 4);
        m_pTextureAtlasDic->setObject(atlas, key);
    }
    return atlas;
}

void CCArmature::setParentBone(CCBone *parentBone)
{
    m_pParentBone = parentBone;

    CCDictElement *element = NULL;
    CCDICT_FOREACH(m_pBoneDic, element)
    {
        CCBone *bone = (CCBone*)element->getObject();
        bone->setArmature(this);
    }
}

CCBone *CCArmature::getParentBone()
{
    return m_pParentBone;
}


#if ENABLE_PHYSICS_BOX2D_DETECT || ENABLE_PHYSICS_CHIPMUNK_DETECT
void CCArmature::setColliderFilter(CCColliderFilter *filter)
{
    CCDictElement *element = NULL;
    CCDICT_FOREACH(m_pBoneDic, element)
    {
        CCBone *bone = static_cast<CCBone*>(element->getObject());
        bone->setColliderFilter(filter);
    }
}
#elif ENABLE_PHYSICS_SAVE_CALCULATED_VERTEX

void CCArmature::drawContour()
{
    CCDictElement *element = NULL;
    CCDICT_FOREACH(m_pBoneDic, element)
    {
        CCBone *bone = static_cast<CCBone*>(element->getObject());
        CCArray *bodyList = bone->getColliderBodyList();

        CCObject *object = NULL;
        CCARRAY_FOREACH(bodyList, object)
        {
            ColliderBody *body = static_cast<ColliderBody*>(object);
            CCArray *vertexList = body->getCalculatedVertexList();

            int length = vertexList->count();
            CCPoint *points = new CCPoint[length];
            for (int i = 0; i<length; i++)
            {
                CCContourVertex2 *vertex = static_cast<CCContourVertex2*>(vertexList->objectAtIndex(i));
                points[i].x = vertex->x;
                points[i].y = vertex->y;
            }
            ccDrawPoly( points, length, true );
            delete points;
        }
    }
}

#endif


#if ENABLE_PHYSICS_BOX2D_DETECT
b2Body *CCArmature::getBody()
{
    return m_pBody;
}

void CCArmature::setBody(b2Body *body)
{
    if (m_pBody == body)
    {
        return;
    }

    m_pBody = body;
    m_pBody->SetUserData(this);

    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pChildren, object)
    {
        if (CCBone *bone = dynamic_cast<CCBone *>(object))
        {
            CCArray *displayList = bone->getDisplayManager()->getDecorativeDisplayList();

            CCObject *displayObject = NULL;
            CCARRAY_FOREACH(displayList, displayObject)
            {
                CCColliderDetector *detector = ((CCDecorativeDisplay *)displayObject)->getColliderDetector();
                if (detector != NULL)
                {
                    detector->setBody(m_pBody);
                }
            }
        }
    }
}

b2Fixture *CCArmature::getShapeList()
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
cpBody *CCArmature::getBody()
{
    return m_pBody;
}

void CCArmature::setBody(cpBody *body)
{
    if (m_pBody == body)
    {
        return;
    }

    m_pBody = body;
    m_pBody->data = this;

    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pChildren, object)
    {
        if (CCBone *bone = dynamic_cast<CCBone *>(object))
        {
            CCArray *displayList = bone->getDisplayManager()->getDecorativeDisplayList();

            CCObject *displayObject = NULL;
            CCARRAY_FOREACH(displayList, displayObject)
            {
                CCColliderDetector *detector = ((CCDecorativeDisplay *)displayObject)->getColliderDetector();
                if (detector != NULL)
                {
                    detector->setBody(m_pBody);
                }
            }
        }
    }
}

cpShape *CCArmature::getShapeList()
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


NS_CC_EXT_END
