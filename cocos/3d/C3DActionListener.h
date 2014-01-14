#ifndef ACTIONLISTENER_H_
#define ACTIONLISTENER_H_

#include <vector>
#include <stdlib.h>
#include <functional>

namespace cocos2d
{

class C3DAnimation;
class AnimationValue;

/**
 * Defines a class for Action Event
 */
class C3DActionEvent
{
public:
    /**
     * Constructor.
     */
    C3DActionEvent(std::function<void()> listener, unsigned long eventTime);
    
    /**
     * Constructor.
     */
    C3DActionEvent(const C3DActionEvent& actionEvent);
   
    /**
     * Destructor.
     */
    ~C3DActionEvent();

    bool _finished;
    std::function<void()> _listener;        // This listener to call back when this event is triggered.
    unsigned long _eventTime;   // The time at which the listener will be called back at during the playback of the AnimationClip.
};
}
#endif
