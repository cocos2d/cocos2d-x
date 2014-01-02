#include "Base.h"
#include "C3DLayer.h"
#include "C3DAnimationClip.h"
#include "C3DAnimation.h"

#include "C3DAnimationChannel.h"
#include "AnimationValue.h"
#include "C3DAnimationCurve.h"

#include "C3DActionListener.h"
#include "C3DBone.h"


namespace cocos2d
{

C3DAnimationClip::C3DAnimationClip(const char* id, C3DAnimation* animation, unsigned long startTime, unsigned long endTime)
    : _id(id), _animation(animation), _startTime(startTime), _endTime(endTime), _duration(_endTime - _startTime), 
      _stateBits(0x00), _repeatCount(1.0f), _activeDuration(_duration * _repeatCount), _speed(1.0f), _timeStarted(0), 
      _elapsedTime(0), _blendWeight(1.0f), _crossFadeToClip(nullptr), _crossFadeOutElapsed(0), _crossFadeOutDuration(0)

{
    assert(0 <= startTime && startTime <= animation->_duration && 0 <= endTime && endTime <= animation->_duration);
       
    _frameCount = ((float)_duration / animation->_duration) * animation->getFrameCount();
    _value = new AnimationValue(10);

    _actionEvents = nullptr;
}

C3DAnimationClip::~C3DAnimationClip()
{
    SAFE_DELETE(_value);    

    if (_actionEvents)
    {
        std::list<C3DActionEvent*>::iterator iter = _actionEvents->begin();        
        while (iter != _actionEvents->end())
        {
            C3DActionEvent* lEvt = *iter;
            SAFE_DELETE(lEvt);
            ++iter;
        }
        SAFE_DELETE(_actionEvents);
    }
}

const char* C3DAnimationClip::getID() const
{
    return _id.c_str();
}

unsigned long C3DAnimationClip::getStartTime() const
{
    return _startTime;
}

unsigned long C3DAnimationClip::getEndTime() const
{
    return _endTime;
}

unsigned long C3DAnimationClip::getElaspedTime() const
{
    return _elapsedTime;
}

void C3DAnimationClip::setRepeatCount(float repeatCount)
{
    assert(repeatCount == 0 || repeatCount > 0.0f);

    _repeatCount = repeatCount;

    if (repeatCount == 0)
    {
        _activeDuration = _duration;
    }
    else
    {
        _activeDuration = _repeatCount * _duration;
    }
}

float C3DAnimationClip::getRepeatCount() const
{
    return _repeatCount;
}


unsigned long C3DAnimationClip::getDuration() const
{
    return _duration;
}

void C3DAnimationClip::setSpeed(float speed)
{
    _speed = speed;
}

float C3DAnimationClip::getSpeed() const
{
    return _speed;
}

void C3DAnimationClip::setBlendWeight(float blendWeight)
{
    _blendWeight = blendWeight;
}

float C3DAnimationClip::getBlendWeight() const
{
    return _blendWeight;
}

bool C3DAnimationClip::isPlaying() const
{
    return hasState(CLIP_IS_PLAYING);
}

bool C3DAnimationClip::isPaused() const
{
    return hasState(CLIP_IS_PAUSED);
}

bool C3DAnimationClip::isResumed() const
{
    return hasState(CLIP_IS_RESTARTED);
}

void C3DAnimationClip::play()
{
    if (hasState(CLIP_IS_PLAYING))
    {
         // If paused, reset the bit and return.
        if (hasState(CLIP_IS_PAUSED))
        {
            resetState(CLIP_IS_PAUSED);
            return;
        }

        // If the clip is set to be removed, reset the flag.
        if (hasState(CLIP_IS_MARKED_FOR_REMOVAL))
            resetState(CLIP_IS_MARKED_FOR_REMOVAL);

        setState(CLIP_IS_RESTARTED);
    }
    else
    {
        setState(CLIP_IS_PLAYING);       
        _animation->addRunClip(this);
        
    }

    _timeStarted = C3DLayer::getGameTime();

   
}

void C3DAnimationClip::crossFade(C3DAnimationClip* clip, unsigned long duration)
{
    assert(clip);


    if (clip->hasState(CLIP_IS_FADING_OUT) && clip->_crossFadeToClip == this)
    {
        clip->resetState(CLIP_IS_FADING_OUT);
        clip->_crossFadeToClip->resetState(CLIP_IS_FADING_IN);
        SAFE_RELEASE(clip->_crossFadeToClip);
    }

    if (_crossFadeToClip)
    {
        SAFE_RELEASE(_crossFadeToClip);
    }

    // fade in
    _crossFadeToClip = clip;
    _crossFadeToClip->retain();
    _crossFadeToClip->setState(CLIP_IS_FADING_IN);
    _crossFadeToClip->_blendWeight = 0.0f;
    
    //fade out
    setState(CLIP_IS_FADING_OUT_STARTED);
    setState(CLIP_IS_FADING_OUT);
    _crossFadeOutElapsed = 0L;
    _crossFadeOutDuration = duration;

    if (!hasState(CLIP_IS_PLAYING))
        play();
    

    _crossFadeToClip->play(); 
}

void C3DAnimationClip::stop()
{
    _stateBits = CLIP_IS_MARKED_FOR_REMOVAL;
}

void C3DAnimationClip::pause()
{
    _stateBits = CLIP_IS_PAUSED;
}

void C3DAnimationClip::resume()
{
    _stateBits = CLIP_IS_RESTARTED;
}


unsigned short C3DAnimationClip::update(unsigned long elapsedTime)
{
    if(_repeatCount != 0)
    {
        return updateOnce(elapsedTime);
    }
    else
    {
        return updateLoop(elapsedTime);
    }    
   
}

unsigned short C3DAnimationClip::updateLoop(unsigned long elapsedTime)
{
    if (hasState(CLIP_IS_PAUSED))
    {
        return CLIP_IS_PAUSED;
    }
    else if (hasState(CLIP_IS_MARKED_FOR_REMOVAL))
    {   
        _blendWeight = 1.0f;
        _stateBits = CLIP_IS_NONE;
        
        return CLIP_IS_MARKED_FOR_REMOVAL;
    }
    else if(hasState(CLIP_IS_RESTARTED))
    {
        _blendWeight = 1.0f;
        _stateBits = CLIP_IS_PLAYING;

        return CLIP_IS_RESTARTED;
    }
    else if (!hasState(CLIP_IS_STARTED))
    {
        _elapsedTime = (C3DLayer::getGameTime() - _timeStarted) * _speed;
        
        setState(CLIP_IS_STARTED);
    }
    else if (hasState(CLIP_IS_FADING_OUT))
    {
        if (hasState(CLIP_IS_FADING_OUT_STARTED)) // Calculate elapsed time since the fade out begin.
        {
            _crossFadeOutElapsed = (C3DLayer::getGameTime() - _crossFadeToClip->_timeStarted) * abs(_speed); 
            resetState(CLIP_IS_FADING_OUT_STARTED);
        }
        else
        {
            _crossFadeOutElapsed += elapsedTime * abs(_speed);
        }

        if (_crossFadeOutElapsed < _crossFadeOutDuration)
        {
            _blendWeight = (float) (_crossFadeOutDuration - _crossFadeOutElapsed) / (float) _crossFadeOutDuration;
            
            _crossFadeToClip->_blendWeight = (1.0f - _blendWeight);
                
        }
        else
        {   // Fade is done.

            _blendWeight = 0.0f;

            _crossFadeToClip->_blendWeight = 1.0f;

            resetState(CLIP_IS_STARTED);            
            resetState(CLIP_IS_FADING_OUT);

            _crossFadeToClip->resetState(CLIP_IS_FADING_IN);
            SAFE_RELEASE(_crossFadeToClip);
        }
    }
    else
    {
        _elapsedTime += elapsedTime * _speed;

        if (_repeatCount == 0 && _elapsedTime <= 0)
            _elapsedTime = _activeDuration + _elapsedTime;
    }

    unsigned long currentTime = 0L;
    int counter = 0;
    // Check to see if clip is complete.
    if (_repeatCount != 0 && ((_speed >= 0.0f && _elapsedTime >= (long) _activeDuration) || (_speed <= 0.0f && _elapsedTime <= 0L)))
    {             
        resetState(CLIP_IS_STARTED);
        if (_speed >= 0.0f)
        {
            // If _duration == 0, we have a "pose". Just set currentTime to 0.
            if (_duration == 0)
            {
                currentTime = 0L;
            }
            else
            {
                currentTime = _activeDuration % _duration; // Get's the fractional part of the final repeat.
                if (currentTime == 0L)
                    currentTime = _duration;
            }
        }
        else
        {
            currentTime = 0L; // If we are negative speed, the end value should be 0.
        }
        
    }
    else
    {
        
        // If _duration == 0, we have a "pose". Just set currentTime to 0.
        if (_duration == 0)
            currentTime = 0L;
        else // Gets portion/fraction of the repeat.
        {
            currentTime = _elapsedTime % _duration;
            counter = _elapsedTime/_duration;
        }        
    }

    // Notify any listeners of Animation events.
    if (_actionEvents)
    {
        C3DActionEvent* evt;
        if (_speed >= 0.0f)
        {
            std::list<C3DActionEvent*>::iterator iter = _actionEvents->begin();
            while (iter != _actionEvents->end())
            {
                evt = *iter;
                if(_elapsedTime == 0)
                {
                    if( _elapsedTime>=((counter-1)*(long)_duration + (long)evt->_eventTime))
                    {
						if (evt->_listener)
                            evt->_listener();
                    }
                }
                else
                {
                    if(currentTime == 0)
                    {                        
                        if( _elapsedTime>=((counter-1)*(long)_duration + (long)evt->_eventTime)/* && evt->_finished == false*/)
                        {
                            if (evt->_listener)
                                evt->_listener(); 
                        }                        
                        
                    }
                    else
                    {                        
                        if( _elapsedTime>=(counter*(long)_duration + (long)evt->_eventTime)/* && evt->_finished == false*/)
                        {
                            if (evt->_listener)
                                evt->_listener(); 
                        }                        
                    }
                }                
                            
                iter++;
            }            
        }
        else
        {
            
            if(_actionEvents->empty())
                return CLIP_IS_NONE;
            std::list<C3DActionEvent*>::iterator iter = _actionEvents->end();
            iter--;
            
            while (iter != _actionEvents->begin())
            {
                evt = *iter;
                if( _elapsedTime<=(long)evt->_eventTime && evt->_finished == false)
                {
                    if (evt->_listener)
                        evt->_listener(); 
                }                
                iter--;
            }      

        }
    }
    
        
   
    float percentComplete = (float)(_startTime + currentTime) / (float) _animation->_duration;

  //   Evaluate this clip.
    C3DAnimationChannel* channel = nullptr;
    C3DBone* bone = nullptr;
    unsigned int channelCount = _animation->_channels.size();
    for (unsigned int i = 0; i < channelCount; i++)
    {
        channel = _animation->_channels[i];        
        bone = channel->_bone;        

        // Evaluate the point on Curve
        channel->getCurve()->evaluate(percentComplete, _value->_value);
        // Set the animation value on the target property.
        bone->setAnimationValue(_value, _blendWeight);
    }
        

     // When ended. Probably should move to it's own method so we can call it when the clip is ended early.
    if (!hasState(CLIP_IS_STARTED))
    {
        _blendWeight = 1.0f;
        _stateBits = CLIP_IS_NONE;
    
        if (_actionEvents)
        {            
            std::list<C3DActionEvent*>::iterator iter = _actionEvents->begin();
            while (iter != _actionEvents->end())
            {
            //    (*iter)->_finished = false;                                
                iter++;
            }            
        }        

        return CLIP_IS_MARKED_FOR_REMOVAL;
    }

    return CLIP_IS_PLAYING;
}


unsigned short C3DAnimationClip::updateOnce(unsigned long elapsedTime)
{
    if (hasState(CLIP_IS_PAUSED))
    {
        return CLIP_IS_PAUSED;
    }
    else if (hasState(CLIP_IS_MARKED_FOR_REMOVAL))
    {   
        _blendWeight = 1.0f;
        _stateBits = CLIP_IS_NONE;
        
        return CLIP_IS_MARKED_FOR_REMOVAL;
    }
    else if(hasState(CLIP_IS_RESTARTED))
    {
        _blendWeight = 1.0f;
        _stateBits = CLIP_IS_PLAYING;

        return CLIP_IS_RESTARTED;
    }
    else if (!hasState(CLIP_IS_STARTED))
    {
        _elapsedTime = (C3DLayer::getGameTime() - _timeStarted) * _speed;
        
        setState(CLIP_IS_STARTED);
    }
    else if (hasState(CLIP_IS_FADING_OUT))
    {
        if (hasState(CLIP_IS_FADING_OUT_STARTED)) // Calculate elapsed time since the fade out begin.
        {
            _crossFadeOutElapsed = (C3DLayer::getGameTime() - _crossFadeToClip->_timeStarted) * abs(_speed); 
            resetState(CLIP_IS_FADING_OUT_STARTED);
        }
        else
        {
            _crossFadeOutElapsed += elapsedTime * abs(_speed);
        }

        if (_crossFadeOutElapsed < _crossFadeOutDuration)
        {
            _blendWeight = (float) (_crossFadeOutDuration - _crossFadeOutElapsed) / (float) _crossFadeOutDuration;
            
            _crossFadeToClip->_blendWeight = (1.0f - _blendWeight);
                
        }
        else
        {   // Fade is done.

            _blendWeight = 0.0f;

            _crossFadeToClip->_blendWeight = 1.0f;

            resetState(CLIP_IS_STARTED);            
            resetState(CLIP_IS_FADING_OUT);

            _crossFadeToClip->resetState(CLIP_IS_FADING_IN);
            SAFE_RELEASE(_crossFadeToClip);
        }
    }
    else
    {
        _elapsedTime += elapsedTime * _speed;

        if (_repeatCount == 0 && _elapsedTime <= 0)
            _elapsedTime = _activeDuration + _elapsedTime;
    }

    unsigned long currentTime = 0L;    
    
    // Check to see if clip is complete.
    if (_repeatCount != 0 && ((_speed >= 0.0f && _elapsedTime >= (long) _activeDuration) || (_speed <= 0.0f && _elapsedTime <= 0L)))
    {      
        resetState(CLIP_IS_STARTED);
        if (_speed >= 0.0f)
        {
            // If _duration == 0, we have a "pose". Just set currentTime to 0.
            if (_duration == 0)
            {
                currentTime = 0L;
            }
            else
            {
                currentTime = _activeDuration % _duration; // Get's the fractional part of the final repeat.
                if (currentTime == 0L)
                    currentTime = _duration;
            }
        }
        else
        {
            currentTime = 0L; // If we are negative speed, the end value should be 0.
        }
        
    }
    else
    {
        // If _duration == 0, we have a "pose". Just set currentTime to 0.
        if (_duration == 0)
            currentTime = 0L;
        else // Gets portion/fraction of the repeat.
            currentTime = _elapsedTime % _duration;        
        
    }

    // Notify any listeners of Animation events.
    if (_actionEvents)
    {
        C3DActionEvent* evt;
        if (_speed >= 0.0f)
        {
            std::list<C3DActionEvent*>::iterator iter = _actionEvents->begin();
            while (iter != _actionEvents->end())
            {
                evt = *iter;
                if( _elapsedTime>=(long)evt->_eventTime && evt->_finished == false)
                {
                    if (evt->_listener)
                        evt->_listener(); 
                    evt->_finished = true;
                }                
                iter++;
            }            
        }
        else
        {
            if(_actionEvents->empty())
                return CLIP_IS_NONE;
            std::list<C3DActionEvent*>::iterator iter = _actionEvents->end();
            iter--;
            
            while (iter != _actionEvents->begin())
            {
                evt = *iter;
                if( _elapsedTime<=(long)evt->_eventTime && evt->_finished == false)
                {
                    if (evt->_listener)
                        evt->_listener();
                    evt->_finished = true;
                }                
                iter--;
            }
        }
    }
    
        
   
    float percentComplete = (float)(_startTime + currentTime) / (float) _animation->_duration;

  //   Evaluate this clip.
    C3DAnimationChannel* channel = nullptr;
    C3DBone* bone = nullptr;
    unsigned int channelCount = _animation->_channels.size();
    for (unsigned int i = 0; i < channelCount; i++)
    {
        channel = _animation->_channels[i];        
        bone = channel->_bone;        

        // Evaluate the point on Curve
        channel->getCurve()->evaluate(percentComplete, _value->_value);
        // Set the animation value on the target property.
        bone->setAnimationValue(_value, _blendWeight);
    }
        

     // When ended. Probably should move to it's own method so we can call it when the clip is ended early.
    if (!hasState(CLIP_IS_STARTED))
    {
        _blendWeight = 1.0f;
        _stateBits = CLIP_IS_NONE;
    
        if (_actionEvents)
        {            
            std::list<C3DActionEvent*>::iterator iter = _actionEvents->begin();
            while (iter != _actionEvents->end())
            {
                (*iter)->_finished = false;                                
                iter++;
            }            
        }        

        return CLIP_IS_MARKED_FOR_REMOVAL;
    }

    return CLIP_IS_PLAYING;
}

bool C3DAnimationClip::hasState(unsigned short bit) const
{
    return (_stateBits & bit) == bit;
}

void C3DAnimationClip::setState(unsigned short bit)
{
    _stateBits |= bit;
}

void C3DAnimationClip::resetState(unsigned short bit)
{
    _stateBits &= ~bit;
}


void C3DAnimationClip::addActionEvent(std::function<void()> listener, unsigned long eventTime)
{
    assert(listener);
    assert(eventTime <= _activeDuration);

    C3DActionEvent* actionEvent = new C3DActionEvent(listener, eventTime);

    if (!_actionEvents)
    {
        _actionEvents = new std::list<C3DActionEvent*>;
        _actionEvents->push_back(actionEvent);
    }
    else
    {
        std::list<C3DActionEvent*>::iterator iter = _actionEvents->begin();
        while (iter != _actionEvents->end())
        {
            if (eventTime < (*iter)->_eventTime)
            {
                iter = _actionEvents->insert(iter, actionEvent);
                return;
            }                                            
            iter++;
        }
            
        _actionEvents->push_back(actionEvent);
    }
}

void C3DAnimationClip::addActionEvent(C3DActionEvent* actionEvent)
{
    assert(actionEvent);
    

    if (!_actionEvents)
    {
        _actionEvents = new std::list<C3DActionEvent*>;
        _actionEvents->push_back(actionEvent);
    }
    else
    {
        std::list<C3DActionEvent*>::iterator iter = _actionEvents->begin();
        while (iter != _actionEvents->end())
        {
            if (actionEvent->_eventTime < (*iter)->_eventTime)
            {
                iter = _actionEvents->insert(iter, actionEvent);
                return;
            }                                            
            iter++;
        }
            
        _actionEvents->push_back(actionEvent);
    }
}


void C3DAnimationClip::clearActionEvent()
{
    if (_actionEvents)
    {
        std::list<C3DActionEvent*>::iterator iter = _actionEvents->begin();        
        while (iter != _actionEvents->end())
        {
            C3DActionEvent* lEvt = *iter;
            SAFE_DELETE(lEvt);
            ++iter;
        }
        SAFE_DELETE(_actionEvents);
    }
}


int C3DAnimationClip::getFrameCount()
{
    return _frameCount;
}

void C3DAnimationClip::setCurrentFrame(int nFrame)
{
    _elapsedTime = ((float)nFrame / _frameCount) *  _duration;
}

int C3DAnimationClip::getCurrentFrame()
{
    float tElapsed = ( _elapsedTime %  _duration );
    return tElapsed / _duration * _frameCount;
}

C3DAnimationClip* C3DAnimationClip::clone(C3DAnimation* animation)
{
    C3DAnimationClip* clip = new C3DAnimationClip(_id.c_str(), animation, _startTime, _endTime);
        
    clip->setSpeed(getSpeed());    
    clip->setRepeatCount(getRepeatCount());

    if (_actionEvents)
    {
        std::list<C3DActionEvent*>::iterator iter = _actionEvents->begin();        
        while (iter != _actionEvents->end())
        {
            C3DActionEvent* srcEvent = *iter;

            C3DActionEvent* objEvent = new C3DActionEvent(*srcEvent);
            
            clip->addActionEvent(objEvent);
            ++iter;
        }            
    }
    
    clip->autorelease();
  
    return clip;
}


}
