
#include "C3DActionListener.h"


namespace cocos2d
{

C3DActionEvent::C3DActionEvent(std::function<void()> listener, unsigned long eventTime)
{
    _listener = listener;
    _eventTime = eventTime;

    _finished = false;
}

C3DActionEvent::C3DActionEvent(const C3DActionEvent& actionEvent)
{
    _finished = actionEvent._finished;

	_listener = actionEvent._listener;

    _eventTime = actionEvent._eventTime; 

}

C3DActionEvent::~C3DActionEvent()
{
    _listener = nullptr;
}

}
