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

NS_CC_EXT_BEGIN

std::map<int, CCArmature *> CCArmature::_armatureIndexDic;

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


CCArmature *CCArmature::create(const char *_name)
{
    CCArmature *armature = new CCArmature();
    if (armature && armature->init(_name))
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
    : _animation(NULL)
	, _armatureData(NULL)
	, _batchNode(NULL)
    , _atlas(NULL)
	, _parentBone(NULL)
	, _boneDic(NULL)
    , _topBoneList(NULL)
{
}


CCArmature::~CCArmature(void)
{
    if(NULL != _boneDic)
    {
        _boneDic->removeAllObjects();
        CC_SAFE_DELETE(_boneDic);
    }
    if (NULL != _topBoneList)
    {
        _topBoneList->removeAllObjects();
        CC_SAFE_DELETE(_topBoneList);
    }
    CC_SAFE_DELETE(_animation);
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

        CC_SAFE_DELETE(_animation);
        _animation = new CCArmatureAnimation();
        _animation->init(this);

        CC_SAFE_DELETE(_boneDic);
        _boneDic	= new CCDictionary();

        CC_SAFE_DELETE(_topBoneList);
        _topBoneList = new CCArray();
        _topBoneList->init();


        _blendFunc.src = CC_BLEND_SRC;
        _blendFunc.dst = CC_BLEND_DST;


        _name = name == NULL ? "" : name;

        CCArmatureDataManager *armatureDataManager = CCArmatureDataManager::sharedArmatureDataManager();

        if(_name.length() != 0)
        {
            _name = name;

            CCAnimationData *animationData = armatureDataManager->getAnimationData(name);
            CCAssert(animationData, "CCAnimationData not exist! ");

            _animation->setAnimationData(animationData);


            CCArmatureData *armatureData = armatureDataManager->getArmatureData(name);
            CCAssert(armatureData, "");

            _armatureData = armatureData;


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
                    bone->changeDisplayByIndex(frameData->displayIndex, false);
                }
                while (0);
            }

            update(0);
            updateOffsetPoint();
        }
        else
        {
            _name = "new_armature";
            _armatureData = CCArmatureData::create();
            _armatureData->name = _name;

            CCAnimationData *animationData = CCAnimationData::create();
            animationData->name = _name;

            armatureDataManager->addArmatureData(_name.c_str(), _armatureData);
            armatureDataManager->addAnimationData(_name.c_str(), animationData);

            _animation->setAnimationData(animationData);

        }

        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));

        unscheduleUpdate();
        scheduleUpdate();

        setCascadeOpacityEnabled(true);
        setCascadeColorEnabled(true);

        bRet = true;
    }
    while (0);

    return bRet;
}

bool CCArmature::init(const char *name, CCBone *parentBone)
{
    _parentBone = parentBone;
    return init(name);
}


CCBone *CCArmature::createBone(const char *boneName)
{
    CCBone *existedBone = getBone(boneName);
    if(existedBone != NULL)
        return existedBone;

    CCBoneData *boneData = (CCBoneData *)_armatureData->getBoneData(boneName);
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
    bone->getDisplayManager()->changeDisplayByIndex(-1, false);

    return bone;
}


void CCArmature::addBone(CCBone *bone, const char *parentName)
{
    CCAssert( bone != NULL, "Argument must be non-nil");
    CCAssert(_boneDic->objectForKey(bone->getName()) == NULL, "bone already added. It can't be added again");

    if (NULL != parentName)
    {
        CCBone *boneParent = (CCBone *)_boneDic->objectForKey(parentName);
        if (boneParent)
        {
            boneParent->addChildBone(bone);
        }
        else
        {
            if (_parentBone)
                _parentBone->addChildBone(bone);
            else
                _topBoneList->addObject(bone);
        }
    }
    else
    {
        if (_parentBone)
            _parentBone->addChildBone(bone);
        else
            _topBoneList->addObject(bone);
    }

    bone->setArmature(this);

    _boneDic->setObject(bone, bone->getName());
    addChild(bone);
}


void CCArmature::removeBone(CCBone *bone, bool recursion)
{
    CCAssert(bone != NULL, "bone must be added to the bone dictionary!");

    bone->setArmature(NULL);
    bone->removeFromParent(recursion);

    if (_topBoneList->containsObject(bone))
    {
        _topBoneList->removeObject(bone);
    }
    _boneDic->removeObjectForKey(bone->getName());
    removeChild(bone, true);
}


CCBone *CCArmature::getBone(const char *_name) const
{
    return (CCBone *)_boneDic->objectForKey(_name);
}


void CCArmature::changeBoneParent(CCBone *bone, const char *parentName)
{
    CCAssert(bone != NULL, "bone must be added to the bone dictionary!");

    bone->getParentBone()->getChildren()->removeObject(bone);
    bone->setParentBone(NULL);

    if (parentName != NULL)
    {
        CCBone *boneParent = (CCBone *)_boneDic->objectForKey(parentName);

        if (boneParent)
        {
            boneParent->addChildBone(bone);
        }
    }
}

CCDictionary *CCArmature::getBoneDic()
{
    return _boneDic;
}

CCAffineTransform CCArmature::nodeToParentTransform()
{
    if (_transformDirty)
    {
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
        x += cy * _offsetPoint.x * _scaleX + -sx * _offsetPoint.y * _scaleY;
        y += sy * _offsetPoint.x * _scaleX + cx * _offsetPoint.y * _scaleY;

        bool needsSkewMatrix = ( _skewX || _skewY );

        // optimization:
        // inline anchor point calculation if skew is not needed
        // Adjusted transform calculation for rotational skew
        if (! needsSkewMatrix && !_anchorPointInPoints.equals(CCPointZero))
        {
            x += cy * -_anchorPointInPoints.x * _scaleX + -sx * -_anchorPointInPoints.y * _scaleY;
            y += sy * -_anchorPointInPoints.x * _scaleX +  cx * -_anchorPointInPoints.y * _scaleY;
        }


        // Build Transform Matrix
        // Adjusted transform calculation for rotational skew
        _transform = CCAffineTransformMake( cy * _scaleX,  sy * _scaleX,
                                              -sx * _scaleY, cx * _scaleY,
                                              x, y );

        // XXX: Try to inline skew
        // If skew is needed, apply skew and then anchor point
        if (needsSkewMatrix)
        {
            CCAffineTransform skewMatrix = CCAffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(_skewY)),
                                           tanf(CC_DEGREES_TO_RADIANS(_skewX)), 1.0f,
                                           0.0f, 0.0f );
            _transform = CCAffineTransformConcat(skewMatrix, _transform);

            // adjust anchor point
            if (!_anchorPointInPoints.equals(CCPointZero))
            {
                _transform = CCAffineTransformTranslate(_transform, -_anchorPointInPoints.x, -_anchorPointInPoints.y);
            }
        }

        if (_additionalTransformDirty)
        {
            _transform = CCAffineTransformConcat(_transform, _additionalTransform);
            _additionalTransformDirty = false;
        }

        _transformDirty = false;
    }

    return _transform;
}

void CCArmature::updateOffsetPoint()
{
    // Set contentsize and Calculate anchor point.
    CCRect rect = boundingBox();
    setContentSize(rect.size);
    _offsetPoint = ccp(-rect.origin.x,  -rect.origin.y);
    setAnchorPoint(ccp(_offsetPoint.x / rect.size.width, _offsetPoint.y / rect.size.height));
}


void CCArmature::update(float dt)
{
    _animation->update(dt);

    CCObject *object = NULL;
    CCARRAY_FOREACH(_topBoneList, object)
    {
        ((CCBone *)object)->update(dt);
    }
}

void CCArmature::draw()
{
    if (_parentBone == NULL)
    {
        CC_NODE_DRAW_SETUP();
        ccGLBlendFunc(_blendFunc.src, _blendFunc.dst);
    }

    CCObject *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        CCBone *bone = (CCBone *)object;

        CCDisplayManager *displayManager = bone->getDisplayManager();
        CCNode *node = displayManager->getDisplayRenderNode();

        if (NULL == node)
            continue;

        if(CCSkin *skin = dynamic_cast<CCSkin *>(node))
        {
            CCTextureAtlas *textureAtlas = skin->getTextureAtlas();
            if(_atlas != textureAtlas)
            {
                if (_atlas)
                {
                    _atlas->drawQuads();
                    _atlas->removeAllQuads();
                }
            }

            _atlas = textureAtlas;
            if (_atlas->getCapacity() == _atlas->getTotalQuads() && !_atlas->resizeCapacity(_atlas->getCapacity() * 2))
                return;

            skin->draw();
        }
        else if(CCArmature *armature = dynamic_cast<CCArmature *>(node))
        {
            CCTextureAtlas *textureAtlas = armature->getTextureAtlas();

            if(_atlas != textureAtlas)
            {
                if (_atlas)
                {
                    _atlas->drawQuads();
                    _atlas->removeAllQuads();
                }
            }
            armature->draw();
        }
        else
        {
            if (_atlas)
            {
                _atlas->drawQuads();
                _atlas->removeAllQuads();
            }
            node->visit();

            CC_NODE_DRAW_SETUP();
            ccGLBlendFunc(_blendFunc.src, _blendFunc.dst);
        }
    }

    if(_atlas && !_batchNode && _parentBone == NULL)
    {
        _atlas->drawQuads();
        _atlas->removeAllQuads();
    }
}

void CCArmature::visit()
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

CCRect CCArmature::boundingBox()
{
    float minx, miny, maxx, maxy = 0;

    bool first = true;

    CCRect boundingBox = CCRectMake(0, 0, 0, 0);

    CCObject *object = NULL;
    CCARRAY_FOREACH(_children, object)
    {
        CCBone *bone = (CCBone *)object;
        CCRect r = bone->getDisplayManager()->getBoundingBox();

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

    return boundingBox;
}

CCBone *CCArmature::getBoneAtPoint(float x, float y)
{
    int length = _children->data->num;
    CCBone **bs = (CCBone **)_children->data->arr;

    for(int i = length - 1; i >= 0; i--)
    {
        if(bs[i]->getDisplayManager()->containPoint(x, y))
        {
            return bs[i];
        }
    }
    return NULL;
}

NS_CC_EXT_END
