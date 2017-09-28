#ifndef DRAGONBONES_EVENT_OBJECT_H
#define DRAGONBONES_EVENT_OBJECT_H

#include "../core/BaseObject.h"

DRAGONBONES_NAMESPACE_BEGIN

class IEventDispatcher;
class Armature;
class Bone;
class Slot;
class AnimationState;
class AnimationFrameData;

class EventObject final : public BaseObject
{
    BIND_CLASS_TYPE(EventObject);

public:
    static const char* START;
    static const char* LOOP_COMPLETE;
    static const char* COMPLETE;

    static const char* FADE_IN;
    static const char* FADE_IN_COMPLETE;
    static const char* FADE_OUT;
    static const char* FADE_OUT_COMPLETE;

    static const char* FRAME_EVENT;
    static const char* SOUND_EVENT;

public:
    /** @private */
    static IEventDispatcher* _soundEventManager;

public:
    std::string type;
    std::string name;
    //void* data; // TODO
    void* userData;
    Armature* armature;
    Bone* bone;
    Slot* slot;
    AnimationState* animationState;
    AnimationFrameData* frame;

public:
    EventObject();
    ~EventObject();

protected:
    void _onClear() override;

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(EventObject);
};

class IEventDispatcher
{
protected:
    IEventDispatcher() {};
    virtual ~IEventDispatcher() {};

public:
    /** @private */
    virtual void _onClear() = 0;
    /** @private */
    virtual void _dispatchEvent(EventObject* value) = 0;

    virtual bool hasEvent(const std::string& type) const = 0;
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_EVENT_OBJECT_H