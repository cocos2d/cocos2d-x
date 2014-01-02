#include "C3DBone.h"

#include "Base.h"

#include "C3DAnimation.h"
#include "C3DAnimationChannel.h"
#include "C3DAnimationCurve.h"
#include "AnimationValue.h"
#include "C3DAnimationClip.h"

namespace cocos2d
{

C3DBone::C3DBone(const char* id)
    : C3DNode(id), _jointMatrixDirty(true), _skinCount(0), _bSelect(false)/*, _animTarget(nullptr)*/
{
    _animationChannels = nullptr;
}

C3DBone::~C3DBone()
{
    //SAFE_RELEASE(_animTarget);

    if (_animationChannels)
    {
        std::vector<C3DAnimationChannel*>::iterator itr = _animationChannels->begin();
        while (itr != _animationChannels->end())
        {
            C3DAnimationChannel* channel = (*itr);
            channel->_animation->removeChannel(channel);
            SAFE_DELETE(channel);
            itr++;
        }
        _animationChannels->clear();
        SAFE_DELETE(_animationChannels);
    }
}

C3DBone* C3DBone::create(const char* id)
{
    return new C3DBone(id);
}



C3DNode::Type C3DBone::getType() const
{
    return C3DNode::NodeType_Bone;
}

void C3DBone::transformChanged()
{
    C3DNode::transformChanged();
    _jointMatrixDirty = true;
}

void C3DBone::updateJointMatrix(const Matrix& bindShape, Vector4* matrixPalette)
{
    // Note: If more than one C3DMeshSkin influences this Joint, we need to skip
    // the _jointMatrixDirty optimization since updateJointMatrix() may be
    // called multiple times a frame with different bindShape matrices (and
    // different matrixPallete pointers).
    if (_skinCount > 1 || _jointMatrixDirty)
    {
        _jointMatrixDirty = false;

        static Matrix t;
        Matrix::multiply(C3DNode::getWorldMatrix(), getInverseBindPose(), &t);
        Matrix::multiply(t, bindShape, &t);

        matrixPalette[0].set(t.m[0], t.m[4], t.m[8], t.m[12]);
        matrixPalette[1].set(t.m[1], t.m[5], t.m[9], t.m[13]);
        matrixPalette[2].set(t.m[2], t.m[6], t.m[10], t.m[14]);
    }
}

const Matrix& C3DBone::getInverseBindPose()
{
    return _bindPose;
}

void C3DBone::setInverseBindPose(const Matrix& m)
{
    _bindPose = m;
    _jointMatrixDirty = true;
}


C3DAnimation* C3DBone::getAnimation(const char* id)
{    
   if (_animationChannels)
    {
        std::vector<C3DAnimationChannel*>::iterator itr = _animationChannels->begin();

        if (id == nullptr)
            return (*itr)->_animation;

        C3DAnimationChannel* channel = nullptr;
        for (; itr != _animationChannels->end(); itr++)
        {
            channel = (C3DAnimationChannel*)(*itr);
            if (channel->_animation->_id.compare(id) == 0)
            {
                return channel->_animation;
            }
        }
    }

    return nullptr;
}

void C3DBone::setAnimationValue( AnimationValue* value, float blendWeight)
{

    assert(blendWeight >= 0.0f && blendWeight <= 1.0f);

    if(blendWeight == 0.0f)
        return;
    else if(blendWeight == 1.0f)
    {
        setScale(value->getFloat(0), value->getFloat(1), value->getFloat(2));
        applyAnimationValueRotation(value, 3, 1.0f);
        setPosition(value->getFloat(7), value->getFloat(8), value->getFloat(9));
    }
    else
    {
        setScale(C3DAnimationCurve::lerp(blendWeight, getScaleX(), value->getFloat(0)), C3DAnimationCurve::lerp(blendWeight, getScaleY(), value->getFloat(1)), C3DAnimationCurve::lerp(blendWeight, getScaleZ(), value->getFloat(2)));
        applyAnimationValueRotation(value, 3, blendWeight);
        setPosition(C3DAnimationCurve::lerp(blendWeight, getPositionX(), value->getFloat(7)), C3DAnimationCurve::lerp(blendWeight, getPositionY(), value->getFloat(8)), C3DAnimationCurve::lerp(blendWeight, getPositionZ(), value->getFloat(9)));
    }
          
}

void C3DBone::applyAnimationValueRotation(AnimationValue* value, unsigned int index, float blendWeight)
{
    Quaternion q(value->getFloat(index), value->getFloat(index + 1), value->getFloat(index + 2), value->getFloat(index + 3));
    Quaternion::slerp(_rotation, q, blendWeight, &q);
    setRotation(q);
}


void C3DBone::addChannel(C3DAnimationChannel* channel)
{
    if (_animationChannels == nullptr)
        _animationChannels = new std::vector<C3DAnimationChannel*>;

    _animationChannels->push_back(channel);
}

void C3DBone::removeChannel(C3DAnimationChannel* channel)
{
    if (_animationChannels)
    {
        std::vector<C3DAnimationChannel*>::iterator itr = _animationChannels->begin();
        for ( ; itr != _animationChannels->end(); itr++)
        {
            C3DAnimationChannel* temp = *itr;
            if (channel == temp)
            {
                _animationChannels->erase(itr);

                if (_animationChannels->empty())
                    SAFE_DELETE(_animationChannels);

                return;
            }
        }
    }
}

C3DAnimationChannel* C3DBone::getChannel(const char* id) const
{
    if (_animationChannels)
    {
        std::vector<C3DAnimationChannel*>::iterator itr = _animationChannels->begin();

        if (id == nullptr)
            return (*itr);

        C3DAnimationChannel* channel = nullptr;
        for (; itr != _animationChannels->end(); itr++)
        {
            channel = (C3DAnimationChannel*)(*itr);
            if (channel->_animation->_id.compare(id) == 0)
            {
                return channel;
            }
        }
    }

    return nullptr;
}

    
void C3DBone::copyFrom(const Transform* other, C3DNode::CloneContext& context)
{
    if (this == other)
        return;
        
    C3DNode::copyFrom(other, context);
    const C3DBone* otherNode = static_cast<const C3DBone*>(other);
    /*std::string strid = otherNode->_id;
    setId(strid.c_str());*/

    _id = otherNode->_id;;
    
    _bindPose = otherNode->_bindPose;
    _jointMatrixDirty = true;
    _skinCount = 0;
    if (otherNode->_animationChannels)
    {    
        C3DAnimationChannel* channel = nullptr;

        std::vector<C3DAnimationChannel*>::iterator itr = otherNode->_animationChannels->begin();
        for (; itr != otherNode->_animationChannels->end(); itr++)
        {
            channel = (C3DAnimationChannel*)(*itr);
        
            C3DAnimation* animation = nullptr;
            std::map<const C3DAnimation*, C3DAnimation*>::iterator itor = context.clonedAnim.find(channel->_animation);
            if (itor == context.clonedAnim.end())
            {
                animation = channel->_animation->clone();
                context.clonedAnim[channel->_animation] = animation;
            }
            else
                animation = itor->second;
            C3DAnimationChannel* channelcopy = new C3DAnimationChannel(animation, this, channel->_curve, channel->_duration);
            animation->addChannel(channelcopy);
        }
    
    }

}
    
C3DNode* C3DBone::clone(C3DNode::CloneContext& context) const
{
    C3DBone* other = new C3DBone(nullptr);
    other->copyFrom(this, context);
    other->autorelease();
    return other;
}


}
