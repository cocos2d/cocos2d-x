
#include "C3DActionListener.h"


namespace cocos2d
{

C3DActionListener::C3DActionListener(): _object(nullptr),_function(nullptr)
{
}

C3DActionListener::C3DActionListener(const C3DActionListener& actionListener)
{
    _object = actionListener._object;
    _function = actionListener._function;
}

C3DActionListener::~C3DActionListener()
{
    _object = nullptr;
    _function = nullptr;
}    
   

C3DActionListener * C3DActionListener::create(ListenerObject* object, ListenerFunction function) 
{
    C3DActionListener *res = new C3DActionListener();
       
    res->_object = object;

    res->_function = function;

    return res;  

}

void C3DActionListener::action() 
{
    if (_function) 
    {
        (_object->*_function)();
    }
}

C3DActionEvent::C3DActionEvent(C3DActionListener* listener, unsigned long eventTime)
{
    _listener = listener;
    _eventTime = eventTime;

    _finished = false;
}

C3DActionEvent::C3DActionEvent(const C3DActionEvent& actionEvent)
{
    _finished = actionEvent._finished;

    _listener = new C3DActionListener(*actionEvent._listener);

    _eventTime = actionEvent._eventTime; 

}

C3DActionEvent::~C3DActionEvent()
{
    delete _listener;
    _listener = nullptr;

}

}
