#ifndef ACTIONLISTENER_H_
#define ACTIONLISTENER_H_

#include <vector>
#include "stdlib.h"

namespace cocos2d
{

class C3DAnimation;
class AnimationValue;


/**
 * The runtime interface to represent an Object Listener.
 */
class ListenerObject
{
};

typedef void (ListenerObject::*ListenerFunction)();

/**
* Interface for listening to Action events.
*/
class  C3DActionListener
{
public:
    /**
     * Constructor.
     */
    C3DActionListener();

    /**
     * Constructor.
     */
    C3DActionListener(const C3DActionListener& actionListener);
      
    /**
     * Destructor.
     */
    virtual ~C3DActionListener();
      
    /**
    * The method for creating C3DActionListener.
    */
    static C3DActionListener * create(ListenerObject* object, ListenerFunction function);  
    
    /**
    * Do the listener's action.
    */
    void action();

    /**
    * Get the callback function.
    */
    ListenerObject* getTargetCallback()
    {
        return _object;
    }

    /**
    * Set the callback function.
    */
    void setTargetCallback(ListenerObject* object)
    {
        _object = object;         
    }

protected:  
   ListenerObject*   _object;   
   ListenerFunction  _function;
    
    
};

/**
 * Defines a class for Action Event
 */
class C3DActionEvent
{
public:
    /**
     * Constructor.
     */
    C3DActionEvent(C3DActionListener* listener, unsigned long eventTime);
    
    /**
     * Constructor.
     */
    C3DActionEvent(const C3DActionEvent& actionEvent);
   
    /**
     * Destructor.
     */
    ~C3DActionEvent();

    bool _finished;
    C3DActionListener* _listener;        // This listener to call back when this event is triggered.
    unsigned long _eventTime;   // The time at which the listener will be called back at during the playback of the AnimationClip.
};
}
#endif
