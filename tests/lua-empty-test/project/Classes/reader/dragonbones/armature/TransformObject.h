#ifndef DRAGONBONES_TRANSFORM_OBJECT_H
#define DRAGONBONES_TRANSFORM_OBJECT_H

#include "../core/BaseObject.h"
#include "../geom/Matrix.h"
#include "../geom/Transform.h"

DRAGONBONES_NAMESPACE_BEGIN

class Armature;
class Bone;
class Slot;

class TransformObject : public BaseObject // ABSTRACT
{
public:
    void* userData;
    std::string name;
    Matrix* globalTransformMatrix;
    Transform global;
    Transform origin;
    Transform offset;

public:
    /** @private */
    Armature* _armature;
    /** @private */
    Bone* _parent;

protected:
    Matrix _globalTransformMatrix;

public:
    /** @private */
    TransformObject() {}
    /** @private */
    virtual ~TransformObject() {};

protected:
    void _onClear() override
    {
        userData = nullptr;
        name.clear();
        globalTransformMatrix = &_globalTransformMatrix;
        global.identity();
        origin.identity();
        offset.identity();

        _armature = nullptr;
        _parent = nullptr;
        _globalTransformMatrix.identity();
    }

public:
    /** @private */
    virtual void _setArmature(Armature* value)
    {
        _armature = value;
    }

    /** @private */
    virtual void _setParent(Bone* value)
    {
        _parent = value;
    }

public:
    inline Armature* getArmature() const
    {
        return _armature;
    }

    inline Bone* getParent() const
    {
        return _parent;
    }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_TRANSFORM_OBJECT_H
