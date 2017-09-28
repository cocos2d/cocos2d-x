#include "Armature.h"
#include "Bone.h"
#include "Slot.h"
#include "../model/TimelineData.h"

DRAGONBONES_NAMESPACE_BEGIN

Bone::Bone()
{
    _onClear();
}
Bone::~Bone()
{
    _onClear();
}

void Bone::_onClear()
{
    TransformObject::_onClear();

    inheritTranslation = false;
    inheritRotation = false;
    inheritScale = false;
    ikBendPositive = false;
    ikWeight = 0.f;
    length = 0.f;

    _transformDirty = BoneTransformDirty::All;
    _blendIndex = 0;
    _cacheFrames = nullptr;
    _animationPose.identity();

    _visible = true;
    _ikChain = 0;
    _ikChainIndex = 0;
    _ik = nullptr;

    _bones.clear();
    _slots.clear();
}

void Bone::_updateGlobalTransformMatrix()
{
    if (this->_parent)
    {
        const auto parentRotation = this->_parent->global.skewY;
        const auto& parentMatrix = *this->_parent->globalTransformMatrix;

        if (inheritScale)
        {
            if (!inheritRotation)
            {
                this->global.skewX -= parentRotation;
                this->global.skewY -= parentRotation;
            }

            this->global.toMatrix(*this->globalTransformMatrix);
            this->globalTransformMatrix->concat(parentMatrix);

            if (!inheritTranslation)
            {
                this->globalTransformMatrix->tx = this->global.x;
                this->globalTransformMatrix->ty = this->global.y;
            }

            this->global.fromMatrix(*this->globalTransformMatrix);
        }
        else
        {
            if (inheritTranslation)
            {
                const auto x = this->global.x;
                const auto y = this->global.y;
                this->global.x = parentMatrix.a * x + parentMatrix.c * y + parentMatrix.tx;
                this->global.y = parentMatrix.d * y + parentMatrix.b * x + parentMatrix.ty;
            }

            if (inheritRotation)
            {
                this->global.skewX += parentRotation;
                this->global.skewY += parentRotation;
            }

            this->global.toMatrix(*this->globalTransformMatrix);
        }
    }
    else
    {
        this->global.toMatrix(*this->globalTransformMatrix);
    }
}

void Bone::_computeIKA()
{
    const auto& ikGlobal = _ik->global;
    const auto x = this->globalTransformMatrix->a * length;
    const auto y = this->globalTransformMatrix->b * length;

    const auto ikRadian =
        (
            std::atan2(ikGlobal.y - this->global.y, ikGlobal.x - this->global.x) + 
            this->offset.skewY -
            this->global.skewY * 2.f + 
            std::atan2(y, x)
        ) * ikWeight;

    this->global.skewX += ikRadian;
    this->global.skewY += ikRadian;
    this->global.toMatrix(*this->globalTransformMatrix);
}

void Bone::_computeIKB()
{
    auto& parentGlobal = this->_parent->global;
    const auto& ikGlobal = _ik->global;

    const auto x = this->globalTransformMatrix->a * length;
    const auto y = this->globalTransformMatrix->b * length;

    const auto lLL = x * x + y * y;
    const auto lL = std::sqrt(lLL);

    auto dX = this->global.x - parentGlobal.x;
    auto dY = this->global.y - parentGlobal.y;
    const auto lPP = dX * dX + dY * dY;
    const auto lP = std::sqrt(lPP);

    dX = ikGlobal.x - parentGlobal.x;
    dY = ikGlobal.y - parentGlobal.y;
    const auto lTT = dX * dX + dY * dY;
    const auto lT = std::sqrt(lTT);

    auto ikRadianA = 0.f;
    if (lL + lP <= lT || lT + lL <= lP || lT + lP <= lL)
    {
        ikRadianA = std::atan2(ikGlobal.y - parentGlobal.y, ikGlobal.x - parentGlobal.x) + this->_parent->offset.skewY;
        if (lL + lP <= lT)
        {
        }
        else if (lP < lL)
        {
            ikRadianA += PI;
        }
    }
    else
    {
        const auto h = (lPP - lLL + lTT) / (2.f * lTT);
        const auto r = std::sqrt(lPP - h * h * lTT) / lT;
        const auto hX = parentGlobal.x + (dX * h);
        const auto hY = parentGlobal.y + (dY * h);
        const auto rX = -dY * r;
        const auto rY = dX * r;

        if (ikBendPositive)
        {
            this->global.x = hX - rX;
            this->global.y = hY - rY;
        }
        else
        {
            this->global.x = hX + rX;
            this->global.y = hY + rY;
        }

        ikRadianA = std::atan2(this->global.y - parentGlobal.y, this->global.x - parentGlobal.x) + this->_parent->offset.skewY;
    }

    ikRadianA = (ikRadianA - parentGlobal.skewY) * ikWeight;

    parentGlobal.skewX += ikRadianA;
    parentGlobal.skewY += ikRadianA;
    parentGlobal.toMatrix(*this->_parent->globalTransformMatrix);

    this->global.x = parentGlobal.x + std::cos(parentGlobal.skewY) * lP;
    this->global.y = parentGlobal.y + std::sin(parentGlobal.skewY) * lP;

    const auto ikRadianB =
        (
            std::atan2(ikGlobal.y - this->global.y, ikGlobal.x - this->global.x) + this->offset.skewY -
            this->global.skewY * 2.f + std::atan2(y, x)
        ) * ikWeight;

    this->global.skewX += ikRadianB;
    this->global.skewY += ikRadianB;

    this->global.toMatrix(*this->globalTransformMatrix);
}

void Bone::_setArmature(Armature* value)
{
    if (this->_armature == value)
    {
        return;
    }

    std::vector<Slot*> oldSlots;
    std::vector<Bone*> oldBones;

    _ik = nullptr;

    if (this->_armature)
    {
        oldSlots = getSlots();
        oldBones = getBones();
        this->_armature->_removeBoneFromBoneList(this);
    }

    this->_armature = value;

    if (this->_armature)
    {
        this->_armature->_addBoneToBoneList(this);
    }

    if (!oldSlots.empty()) {
        for (const auto slot : oldSlots) 
        {
            if (slot->getParent() == this) 
            {
                slot->_setArmature(this->_armature);
            }
        }
    }

    if (!oldBones.empty()) {
        for (const auto bone : oldBones)
        {
            if (bone->getParent() == this)
            {
                bone->_setArmature(this->_armature);
            }
        }
    }
}

void Bone::_setIK(Bone* value, unsigned chain, int chainIndex)
{
    if (value)
    {
        if (chain == chainIndex)
        {
            auto chainEnd = this->_parent;
            if (chain && chainEnd)
            {
                chain = 1;
            }
            else
            {
                chain = 0;
                chainIndex = 0;
                chainEnd = this;
            }

            if (chainEnd == value || chainEnd->contains(value))
            {
                value = nullptr;
                chain = 0;
                chainIndex = 0;
            }
            else
            {
                auto ancestor = value;
                while (ancestor->getIK() && ancestor->getIKChain())
                {
                    if (chainEnd->contains(ancestor->getIK()))
                    {
                        value = nullptr;
                        chain = 0;
                        chainIndex = 0;
                        break;
                    }

                    ancestor = ancestor->getParent();
                }
            }
        }
    }
    else
    {
        chain = 0;
        chainIndex = 0;
    }

    _ik = value;
    _ikChain = chain;
    _ikChainIndex = chainIndex;

    if (this->_armature)
    {
        this->_armature->_bonesDirty = true;
    }
}

void Bone::_update(int cacheFrameIndex)
{
    _blendIndex = 0;

    if (cacheFrameIndex >= 0)
    {
        const auto cacheFrame = (*_cacheFrames)[cacheFrameIndex];

        if (this->globalTransformMatrix == cacheFrame)
        {
            _transformDirty = BoneTransformDirty::None;
        }
        else if (cacheFrame)
        {
            _transformDirty = BoneTransformDirty::All;
            this->globalTransformMatrix = cacheFrame;
        }
        else if (
            _transformDirty == BoneTransformDirty::All ||
            (this->_parent && this->_parent->_transformDirty != BoneTransformDirty::None) ||
            (_ik && _ik->_transformDirty != BoneTransformDirty::None)
            )
        {
            _transformDirty = BoneTransformDirty::All;
            this->globalTransformMatrix = &this->_globalTransformMatrix;
        }
        else if (this->globalTransformMatrix != &this->_globalTransformMatrix)
        {
            _transformDirty = BoneTransformDirty::None;
            (*_cacheFrames)[cacheFrameIndex] = this->globalTransformMatrix;
        }
        else
        {
            _transformDirty = BoneTransformDirty::All;
            this->globalTransformMatrix = &this->_globalTransformMatrix;
        }
    }
    else if (
        _transformDirty == BoneTransformDirty::All ||
        (this->_parent && this->_parent->_transformDirty != BoneTransformDirty::None) ||
        (_ik && _ik->_transformDirty != BoneTransformDirty::None)
        )
    {
        _transformDirty = BoneTransformDirty::All;
        this->globalTransformMatrix = &this->_globalTransformMatrix;
    }

    if (_transformDirty != BoneTransformDirty::None)
    {
        if (_transformDirty == BoneTransformDirty::All)
        {
            _transformDirty = BoneTransformDirty::Self;

            if (this->globalTransformMatrix == &this->_globalTransformMatrix)
            {
                this->global = this->origin; // copy
                this->global.add(this->offset).add(_animationPose);

                _updateGlobalTransformMatrix();

                if (_ik && _ikChainIndex == _ikChain  && ikWeight > 0.f)
                {
                    if (this->inheritTranslation && _ikChain > 0 && this->_parent)
                    {
                        _computeIKB();
                    }
                    else
                    {
                        _computeIKA();
                    }
                }

                if (cacheFrameIndex >= 0 && !(*_cacheFrames)[cacheFrameIndex])
                {
                    this->globalTransformMatrix = BoneTimelineData::cacheFrame(*_cacheFrames, cacheFrameIndex, this->_globalTransformMatrix);
                }
            }
        }
        else
        {
            _transformDirty = BoneTransformDirty::None;
        }
    }
}

bool Bone::contains(const TransformObject* child) const
{
    if (child)
    {
        if (child == this)
        {
            return false;
        }

        auto ancestor = child;
        while (ancestor != this && ancestor)
        {
            ancestor = ancestor->getParent();
        }

        return ancestor == this;
    }
    
    return false;
}

void Bone::setVisible(bool value)
{
    if (_visible == value)
    {
        return;
    }

    _visible = value;

    for (const auto slot : this->_armature->getSlots())
    {
        if (slot->_parent == this)
        {
            slot->_updateVisible();
        }
    }
}

const std::vector<Bone*>& Bone::getBones() const
{
    _bones.clear();

    for (const auto bone : _armature->getBones())
    {
        if (bone->getParent() == this)
        {
            _bones.push_back(bone);
        }
    }

    return _bones;
}

const std::vector<Slot*>& Bone::getSlots() const
{
    _slots.clear();

    for (const auto slot : _armature->getSlots())
    {
        if (slot->getParent() == this)
        {
            _slots.push_back(slot);
        }
    }

    return _slots;
}

DRAGONBONES_NAMESPACE_END