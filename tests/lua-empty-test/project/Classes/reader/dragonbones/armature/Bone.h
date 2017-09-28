#ifndef DRAGONBONES_BONE_H
#define DRAGONBONES_BONE_H

#include "TransformObject.h"

DRAGONBONES_NAMESPACE_BEGIN

class Bone final : public TransformObject
{
    BIND_CLASS_TYPE(Bone);

public:
    /** @private */
    enum class BoneTransformDirty
    {
        None = 0,
        Self = 1,
        All = 2
    };

    bool inheritTranslation;
    bool inheritRotation;
    bool inheritScale;
    bool ikBendPositive;
    float ikWeight;
    float length;

public:
    /** @private */
    BoneTransformDirty _transformDirty;
    /** @private */
    int _blendIndex;
    /** @private */
    std::vector<Matrix*>* _cacheFrames;
    /** @private */
    Transform _animationPose;

private:
    bool _visible;
    unsigned _ikChain;
    int _ikChainIndex;
    Bone* _ik;
    mutable std::vector<Bone*> _bones;
    mutable std::vector<Slot*> _slots;

public:
    Bone();
    ~Bone();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(Bone);

    void _updateGlobalTransformMatrix();
    void _computeIKA();
    void _computeIKB();

protected:
    void _onClear() override;

public:
    /** @private */
    virtual void _setArmature(Armature* value) override;
    /** @private */
    void _setIK(Bone* value, unsigned chain, int chainIndex);
    /** @private */
    void _update(int cacheFrameIndex);

public:
    bool contains(const TransformObject* child) const;
    void setVisible(bool value);
    const std::vector<Bone*>& getBones() const;
    const std::vector<Slot*>& getSlots() const;

    inline void invalidUpdate()
    {
        _transformDirty = BoneTransformDirty::All;
    }

    inline unsigned getIKChain() const
    {
        return _ikChain;
    }

    inline unsigned getIKChainIndex() const
    {
        return _ikChainIndex;
    }

    inline Bone* getIK() const
    {
        return _ik;
    }

    inline bool getVisible() const
    {
        return _visible;
    }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_BONE_H
