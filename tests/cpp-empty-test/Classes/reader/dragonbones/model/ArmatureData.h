#ifndef DRAGONBONES_ARMATURE_DATA_H
#define DRAGONBONES_ARMATURE_DATA_H

#include "../core/BaseObject.h"
#include "../geom/Transform.h"
#include "../geom/Point.h"
#include "../geom/ColorTransform.h"
#include "../textures/TextureData.h"
#include "AnimationData.h"

DRAGONBONES_NAMESPACE_BEGIN

class DragonBonesData;
class ArmatureData;

class BoneData : public BaseObject 
{
    BIND_CLASS_TYPE(BoneData);

public:
    /** @private */
    bool inheritTranslation;
    /** @private */
    bool inheritRotation;
    /** @private */
    bool inheritScale;
    /** @private */
    bool bendPositive;
    /** @private */
    unsigned chain;
    /** @private */
    int chainIndex;
    /** @private */
    float weight;
    /** @private */
    float length;

    std::string name;

    BoneData* parent;
    /** @private */
    BoneData* ik;
    /** @private */
    Transform transform;

    /** @private */
    BoneData();
    /** @private */
    ~BoneData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(BoneData);

protected:
    virtual void _onClear() override;
};

class SlotData : public BaseObject
{
    BIND_CLASS_TYPE(SlotData);

public:
    /** @private */
    static ColorTransform DEFAULT_COLOR;
    /** @private */
    static ColorTransform* generateColor();

public:
    /** @private */
    int displayIndex;
    /** @private */
    int zOrder;
    /** @private */
    BlendMode blendMode;

    std::string name;

    BoneData* parent;
    /** @private */
    ColorTransform* color;
    /** @private */
    std::vector<ActionData*> actions;

    /** @private */
    SlotData();
    /** @private */
    ~SlotData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(SlotData);

protected:
    void _onClear() override;
};

/** 
 * @private
 */
class MeshData final : public BaseObject
{
    BIND_CLASS_TYPE(MeshData);

public:
    bool skinned;
    Matrix slotPose;

    std::vector<float> uvs;
    std::vector<float> vertices;
    std::vector<unsigned short> vertexIndices;

    std::vector<std::vector<unsigned short>> boneIndices;
    std::vector<std::vector<float>> weights;
    std::vector<std::vector<float>> boneVertices;

    std::vector<BoneData*> bones;
    std::vector<Matrix> inverseBindPose;

    MeshData();
    ~MeshData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(MeshData);

protected:
    void _onClear() override;
};

/**
 * @private
 */
class DisplayData final : public BaseObject
{
    BIND_CLASS_TYPE(DisplayData);

public:
    bool isRelativePivot;
    DisplayType type;
    std::string name;
    TextureData* texture;
    ArmatureData* armature;
    MeshData* mesh;
    Point pivot;
    Transform transform;

    DisplayData();
    ~DisplayData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(DisplayData);

protected:
    void _onClear() override;
};

/**
 * @private
 */
class SlotDisplayDataSet final : public BaseObject
{
    BIND_CLASS_TYPE(SlotDisplayDataSet);

public:
    SlotData* slot;
    std::vector<DisplayData*> displays;

    SlotDisplayDataSet();
    ~SlotDisplayDataSet();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(SlotDisplayDataSet);

protected:
    void _onClear() override;
};

class SkinData final : public BaseObject
{
    BIND_CLASS_TYPE(SkinData);

public:
    std::string name;
    /** @private */
    std::map<std::string, SlotDisplayDataSet*> slots;

    /** @private */
    SkinData();
    /** @private */
    ~SkinData();

protected:
    void _onClear() override;

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(SkinData);

public:
    /** @private */
    void addSlot(SlotDisplayDataSet* value);

    /** @private */
    inline SlotDisplayDataSet* getSlot(const std::string& theName) const
    {
        return mapFind(slots, theName);
    }
};

class ArmatureData : public BaseObject
{
    BIND_CLASS_TYPE(ArmatureData);

private:
    static bool _onSortSlots(const SlotData* a, const SlotData* b);

public:
    unsigned frameRate;
    ArmatureType type;
    std::string name;
    Rectangle aabb;
    DragonBonesData* parent;
    std::map<std::string, BoneData*> bones;
    std::map<std::string, SlotData*> slots;
    std::map<std::string, SkinData*> skins;
    std::map<std::string, AnimationData*> animations;
    /** @private */
    std::vector<ActionData*> actions;

    /** @private */
    unsigned cacheFrameRate;
    /** @private */
    float scale;

private:
    bool _boneDirty;
    bool _slotDirty;
    SkinData* _defaultSkin;
    AnimationData* _defaultAnimation;
    std::vector<BoneData*> _sortedBones;
    std::vector<SlotData*> _sortedSlots;
    std::map<std::string, std::vector<BoneData*>> _bonesChildren;

public:
    /** @private */
    ArmatureData();
    /** @private */
    ~ArmatureData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(ArmatureData);

    void _sortBones();
    void _sortSlots();

protected:
    void _onClear() override;

public:
    /** @private */
    void cacheFrames(unsigned value);
    /** @private */
    void addBone(BoneData* value, const std::string& parentName = "");
    /** @private */
    void addSlot(SlotData* value);
    /** @private */
    void addSkin(SkinData* value);
    /** @private */
    void addAnimation(AnimationData* value);

    inline BoneData* getBone(const std::string& theName) const
    {
        return mapFind(bones, theName);
    }

    inline SlotData* getSlot(const std::string& theName) const
    {
        return mapFind(slots, theName);
    }

    inline SkinData* getSkin(const std::string& theName) const
    {
        if (theName.empty())
        {
            return _defaultSkin;
        }

        return mapFind(skins, theName);
    }

    inline AnimationData* getAnimation(const std::string& theName) const
    {
        if (theName.empty())
        {
            return _defaultAnimation;
        }

        return mapFind(animations, theName);
    }

    inline const std::vector<BoneData*>& getSortedBones() // const
    {
        if (_boneDirty)
        {
            _boneDirty = false;
            _sortBones();
        }

        return _sortedBones;
    }

    inline const std::vector<SlotData*>& getSortedSlots() // const
    {
        if (_slotDirty)
        {
            _slotDirty = false;
            _sortSlots();
        }

        return _sortedSlots;
    }

    inline SkinData* getDefaultSkin() const
    {
        return _defaultSkin;
    }

    inline AnimationData* getDefaultAnimation() const
    {
        return _defaultAnimation;
    }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_ARMATURE_DATA_H
