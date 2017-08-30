#ifndef DRAGONBONES_SLOT_H
#define DRAGONBONES_SLOT_H

#include "TransformObject.h"
#include "../model/ArmatureData.h"
#include "Bone.h"

DRAGONBONES_NAMESPACE_BEGIN

class Slot : public TransformObject
{
public:
    bool inheritAnimation;
    std::string displayController;

public: // private friend class
    /** @private */
    bool _colorDirty;
    /** @private */
    bool _ffdDirty;
    /** @private */
    int _blendIndex;
    /** @private */
    int _zOrder;
    /** @private */
    BlendMode _blendMode;
    /** @private */
    float _pivotX;
    /** @private */
    float _pivotY;
    /** @private */
    SlotDisplayDataSet* _displayDataSet;
    /** @private */
    MeshData* _meshData;
    /** @private */
    std::vector<Matrix*>* _cacheFrames;
    /** @private */
    void* _rawDisplay;
    /** @private */
    void* _meshDisplay;
    /** @private */
    ColorTransform _colorTransform;
    /** @private */
    std::vector<float> _ffdVertices;
    /** @private */
    std::vector<DisplayData*> _replacedDisplayDataSet;

protected:
    bool _displayDirty;
    bool _blendModeDirty;
    bool _originDirty;
    bool _transformDirty;
    int _displayIndex;
    void* _display;
    Armature* _childArmature;
    Matrix _localMatrix;
    std::vector<std::pair<void*, DisplayType>> _displayList;
    std::vector<Bone*> _meshBones;

public:
    /** @private */
    Slot();
    /** @private */
    virtual ~Slot() = 0;

protected:
    void _onClear() override;

    virtual void _initDisplay(void* value) = 0;
    virtual void _disposeDisplay(void* value) = 0;
    virtual void _onUpdateDisplay() = 0;
    virtual void _addDisplay() = 0;
    virtual void _replaceDisplay(void* value, bool isArmatureDisplayContainer) = 0;
    virtual void _removeDisplay() = 0;
    virtual void _updateColor() = 0;
    virtual void _updateFilters() = 0;
    virtual void _updateFrame() = 0;
    virtual void _updateMesh() = 0;
    virtual void _updateTransform() = 0;
    void _updateDisplay();

    inline bool _isMeshBonesUpdate() const
    {
        for (auto bone : _meshBones)
        {
            if (bone->_transformDirty != Bone::BoneTransformDirty::None)
            {
                return true;
            }
        }

        return false;
    }

    inline void _updateLocalTransformMatrix()
    {
        this->global = this->origin;
        this->global.add(this->offset).toMatrix(_localMatrix);
    }

    inline void _updateGlobalTransformMatrix()
    {
        *this->globalTransformMatrix = _localMatrix; // copy
        this->globalTransformMatrix->concat(*this->_parent->globalTransformMatrix);
        this->global.fromMatrix(*this->globalTransformMatrix);
    }

public:
    /** @private */
    virtual void _updateVisible() = 0;
    /** @private */
    virtual void _updateBlendMode() = 0;

    /** @private */
    virtual void _setArmature(Armature* value) override;
    /** @private */
    void _updateMeshData(bool isTimelineUpdate);
    /** @private */
    void _update(int cacheFrameIndex);
    /** @private */
    bool _setDisplayList(const std::vector<std::pair<void*, DisplayType>>& value);
    /** @private */
    bool _setDisplayIndex(int value);
    /** @private */
    bool _setBlendMode(BlendMode value);
    /** @private */
    bool _setColor(const ColorTransform& value);

public:
    inline void invalidUpdate() 
    {
        _displayDirty = true;
    }

    inline void* getRawDisplay() const
    {
        return _rawDisplay;
    }

    inline void* getMeshDisplay() const
    {
        return _meshDisplay;
    }

    inline int getDisplayIndex() const
    {
        return _displayIndex;
    }
    void setDisplayIndex(int value);

    inline const std::vector<std::pair<void*, DisplayType>>& getDisplayList() const
    {
        return _displayList;
    }
    void setDisplayList(const std::vector<std::pair<void*, DisplayType>>& value);

    inline void* getDisplay() const
    {
        return _display;
    }
    void setDisplay(void* value, DisplayType displayType);
    
    inline Armature* getChildArmature() const
    {
        return _childArmature;
    }
    void setChildArmature(Armature* value);
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_SLOT_H
