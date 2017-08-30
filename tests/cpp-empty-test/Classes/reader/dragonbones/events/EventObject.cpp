#include "EventObject.h"

DRAGONBONES_NAMESPACE_BEGIN

const char* EventObject::START = "start";
const char* EventObject::LOOP_COMPLETE = "loopComplete";
const char* EventObject::COMPLETE = "complete";

const char* EventObject::FADE_IN = "fadeIn";
const char* EventObject::FADE_IN_COMPLETE = "fadeInComplete";
const char* EventObject::FADE_OUT = "fadeOut";
const char* EventObject::FADE_OUT_COMPLETE = "fadeOutComplete";

const char* EventObject::FRAME_EVENT = "frameEvent";
const char* EventObject::SOUND_EVENT = "soundEvent";

IEventDispatcher* EventObject::_soundEventManager = nullptr;

EventObject::EventObject()
{
    _onClear();
}

EventObject::~EventObject()
{
    _onClear();
}

void EventObject::_onClear()
{
    type.clear();
    name.clear();
    //data = null;
    userData = nullptr;
    armature = nullptr;
    bone = nullptr;
    slot = nullptr;
    animationState = nullptr;
    frame = nullptr;
}

DRAGONBONES_NAMESPACE_END