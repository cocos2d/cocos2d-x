#ifndef DRAGONBONES_ARMATURE_H
#define DRAGONBONES_ARMATURE_H

#include "../core/BaseObject.h"
#include "../model/ArmatureData.h"
#include "../animation/IAnimateble.h"
#include "../events/EventObject.h"
#include "IArmatureDisplay.h"

DRAGONBONES_NAMESPACE_BEGIN

class Bone;
class Slot;
class Animation;

class Armature : public BaseObject, public IAnimateble
{
    BIND_CLASS_TYPE(Armature);

public:
    void* userData;

public: // private
    /** @private */
    bool _bonesDirty;
    /** @private */
    int _cacheFrameIndex;
    /** @private */
    float _delayAdvanceTime;
    /** @private */
    ArmatureData* _armatureData;
    /** @private */
    SkinData* _skinData;
    /** @private */
    Animation* _animation;
    /** @private */
    IArmatureDisplay* _display;
    /** @private */
    void* _replacedTexture;
    /** @private */
    Slot* _parent;

protected:
    bool _delayDispose;
    bool _lockDispose;
    bool _lockActionAndEvent;
    bool _slotsDirty;
    std::vector<Bone*> _bones;
    std::vector<Slot*> _slots;
    std::vector<ActionData*> _actions;
    std::vector<EventObject*> _events;

public:
    /** @private */
    Armature();
    /** @private */
    ~Armature();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(Armature);
    void _sortBones();
    void _sortSlots();
    void _doAction(const ActionData& value);

protected:
    void _onClear() override;

public:
    /** @private */
    void _addBoneToBoneList(Bone* value);
    /** @private */
    void _removeBoneFromBoneList(Bone* value);
    /** @private */
    void _addSlotToSlotList(Slot* value);
    /** @private */
    void _removeSlotFromSlotList(Slot* value);
    /** @private */
    void _bufferAction(ActionData* value);
    /** @private */
    void _bufferEvent(EventObject* value, const std::string& type);

public:
    void dispose();
    void advanceTime(float passedTime) override;
    void invalidUpdate(const std::string& boneName = "", bool updateSlotDisplay = false);
    Slot* getSlot(const std::string& name) const;
    Slot* getSlotByDisplay(void* display) const;
    void addSlot(Slot* value, const std::string& boneName);
    void removeSlot(Slot* value);
    Bone* getBone(const std::string& name) const;
    Bone* getBoneByDisplay(void* display) const;
    void addBone(Bone* value, const std::string& parentName = "");
    void removeBone(Bone* value);
    void replaceTexture(void* texture);

    inline const std::vector<Bone*>& getBones() const
    {
        return _bones;
    }

    inline const std::vector<Slot*>& getSlots() const
    {
        return _slots;
    }

    inline const std::string& getName() const
    {
        if(_armatureData)
        {
            return _armatureData->name;
        }

        static const std::string DEFAULT_NAME = "";
        return DEFAULT_NAME;
    }

    inline const ArmatureData& getArmatureData() const
    {
        return *_armatureData;
    }

    inline IArmatureDisplay* getDisplay() const
    {
        return _display;
    }

    inline Slot* getParent() const
    {
        return _parent;
    }

    inline Animation& getAnimation() const
    {
        return *_animation;
    }

    inline unsigned getCacheFrameRate()
    {
        return _armatureData->cacheFrameRate;
    }
    void setCacheFrameRate(unsigned value);
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_ARMATURE_H
