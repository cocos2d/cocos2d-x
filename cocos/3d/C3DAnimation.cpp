#include "C3DAnimation.h"
#include "Base.h"
#include "C3DAnimationClip.h"

#include "C3DAnimationChannel.h"
#include "C3DAnimationCurve.h"

namespace cocos2d
{


C3DAnimation::C3DAnimation(const char* id)
    : _id(id), _duration(0),
     _defaultClip(nullptr), _clips(nullptr),_currentClip(nullptr), _state(STOPPED)
{

}

C3DAnimation::~C3DAnimation()
{
    _channels.clear();

    if (_defaultClip)
    {
        SAFE_RELEASE(_defaultClip);
    }

    if(_runningClips.size() > 0)
    {
        std::list<C3DAnimationClip*>::iterator clipIter = _runningClips.begin();
    
        while (clipIter != _runningClips.end())
        {   
            C3DAnimationClip* clip = *clipIter;
            SAFE_RELEASE(clip);
            clipIter++;
        }
        _runningClips.clear();
    }
    

    if (_clips)
    {
        std::vector<C3DAnimationClip*>::iterator clipIter = _clips->begin();
    
        while (clipIter != _clips->end())
        {   
            C3DAnimationClip* clip = *clipIter;
            SAFE_RELEASE(clip);
            clipIter++;
        }
        _clips->clear();
    }
    SAFE_DELETE(_clips);
}

C3DAnimation* C3DAnimation::create(const char* id)
{
    C3DAnimation* animation = new C3DAnimation(id);
    animation->autorelease();
    return animation;
}


const char* C3DAnimation::getId() const
{
    return _id.c_str();
}

unsigned long C3DAnimation::getDuration() const
{
    return _duration;
}


C3DAnimationClip* C3DAnimation::createClip(const char* id, unsigned long start, unsigned long end)
{
    C3DAnimationClip* clip = new C3DAnimationClip(id, this, start, end);

    clip->autorelease();
  
    return clip;
}

C3DAnimationClip* C3DAnimation::getClip(const char* id)
{
    // If id is nullptr return the default clip.
    if (id == nullptr)
    {
        if (_defaultClip == nullptr)
            createDefaultClip();

        return _defaultClip;
    }
    else
    {
        return findClip(id);
    }
}

C3DAnimationClip* C3DAnimation::getClip(unsigned int index) const
{
    if (_clips)
        return _clips->at(index);

    return nullptr;
}

unsigned int C3DAnimation::getClipCount() const
{
    return _clips ? _clips->size() : 0;
}

void C3DAnimation::setFrameCount(unsigned int frameCount)
{
    _frameCount = frameCount;
}

unsigned int C3DAnimation::getFrameCount()
{
    return _frameCount;
}

void C3DAnimation::play(C3DAnimationClip* clip)
{
    if (_currentClip && _currentClip->getRepeatCount()==1 && _currentClip->isPlaying())
        return;

    if (clip == _currentClip && clip->isPlaying())
        return;

    if(clip == _currentClip && clip->isPaused())
        return;

    if(clip == _currentClip && clip->isResumed())
        return;
        
    else if(_currentClip != nullptr && clip != _currentClip && _currentClip->isPaused())
    {
        _currentClip->resetState(C3DAnimationClip::CLIP_IS_PAUSED);
        removeRunClip(_currentClip);
        clip->play();
    }
    else if(_currentClip != nullptr && _currentClip->isPlaying())
    {
        _currentClip->crossFade(clip, 100);
    }
    else
    {
        clip->play();
    }

    _currentClip = clip;
}

void C3DAnimation::play(const char* clipId)
{
    // If id is nullptr, play the default clip.
    if (clipId == nullptr)
    {
        if (_defaultClip == nullptr)
            createDefaultClip();
        
        play(_defaultClip);
       
    }
    else
    {
        // Find animation clip.. and play.
        C3DAnimationClip* clip = findClip(clipId);
        if(clip != nullptr)
            play(clip);

       
    }
}

void C3DAnimation::stop(const char* clipId)
{
    // If id is nullptr, play the default clip.
    if (clipId == nullptr)
    {
        if (_defaultClip)
            _defaultClip->stop();
    }
    else
    {
        // Find animation clip.. and play.
        C3DAnimationClip* clip = findClip(clipId);
        if (clip != nullptr)
            clip->stop();
    }
}

void C3DAnimation::pause(const char * clipId)
{
    if (clipId == nullptr)
    {
        if (_defaultClip)
            _defaultClip->pause();
    }
    else
    {
        C3DAnimationClip* clip = findClip(clipId);
        if (clip != nullptr)
            clip->pause();
    }
}


void C3DAnimation::resume(const char * clipId)
{
    if (clipId == nullptr)
    {
        if (_defaultClip)
            _defaultClip->pause();
    }
    else
    {
        C3DAnimationClip* clip = findClip(clipId);
        if (clip != nullptr)
            clip->resume();
    }
}

void C3DAnimation::createDefaultClip()
{
    _defaultClip = new C3DAnimationClip("default_clip", this, 0.0f, _duration);
}


C3DAnimationClip* C3DAnimation::addClip(const char* name,unsigned int startFrame,unsigned int endFrame,float repeatCount,float speed)
{    
    if (name == nullptr)
        return nullptr;

    C3DAnimationClip* clip = findClip(name);
    if (clip)return nullptr;

    clip = createClip(name, ((float) startFrame / _frameCount) * _duration, ((float) endFrame / _frameCount) * _duration);
        
    clip->setRepeatCount(repeatCount);
    clip->setSpeed(speed);  
    
    addClip(clip);
    
    return clip;

}

bool C3DAnimation::replaceClip(const char* name,unsigned int startFrame,unsigned int endFrame,float repeatCount,float speed)
{
    removeClip(name);
    C3DAnimationClip* clip = addClip(name, startFrame, endFrame, repeatCount, speed);
    if (clip) 
        return true;
    else 
        return false;
}

bool C3DAnimation::removeClip(const char* name)
{
    C3DAnimationClip* clip = findClip(name);
    std::vector<C3DAnimationClip*>::iterator clipIter = _clips->begin();
    while (clipIter != _clips->end())
    {  
        C3DAnimationClip* clip = *clipIter;
        if (strcmp(clip->getID(), name) == 0)
        {
            _clips->erase(clipIter);
            SAFE_DELETE(clip);
            return true;
        }
        clipIter++;
    }
    return false;
}

void C3DAnimation::addClip(C3DAnimationClip* clip)
{
    if (_clips == nullptr)
        _clips = new std::vector<C3DAnimationClip*>;

    clip->retain();

    _clips->push_back(clip);
}

C3DAnimationClip* C3DAnimation::findClip(const char* id) const
{
    if (_clips)
    {
        C3DAnimationClip* clip = nullptr;
        unsigned int clipCount = _clips->size();
        for (unsigned int i = 0; i < clipCount; i++)
        {
            clip = _clips->at(i);
            if (clip->_id.compare(id) == 0)
            {
                return _clips->at(i);
            }
        }
    }
    return nullptr;
}

C3DAnimationChannel* C3DAnimation::createChannel(C3DBone* bone, unsigned int keyCount, unsigned long* keyTimes, float* keyValues)
{
    setFrameCount(keyCount);      

    C3DAnimationCurve* curve = C3DAnimationCurve::create(keyCount, 10);


    unsigned long lowest = keyTimes[0];
    unsigned long duration = keyTimes[keyCount-1] - lowest;

    float keytime;

    keytime = 0.0f;
    curve->setPoint(0, keytime, keyValues);

    unsigned int pointOffset = 10;
    unsigned int i = 1;
    for (; i < keyCount - 1; i++)
    {
        keytime = (float) (keyTimes[i] - lowest) / (float) duration;
        curve->setPoint(i, keytime, (keyValues + pointOffset));
        pointOffset += 10;
    }
    i = keyCount - 1;
    keytime = 1.0f;
    curve->setPoint(i, keytime, keyValues + pointOffset);
       
    curve->_dur = duration;

    C3DAnimationChannel* channel = new C3DAnimationChannel(this, bone,curve, duration);   
    addChannel(channel);
    return channel;
}
    
C3DAnimationChannel* C3DAnimation::createChannel(C3DBone* bone, C3DAnimationCurve* curve)
{
    setFrameCount(curve->getPointCount());
                
    C3DAnimationChannel* channel = new C3DAnimationChannel(this, bone,curve, curve->getDruationTime());
    addChannel(channel);
    return channel;
        
}

void C3DAnimation::addChannel(C3DAnimationChannel* channel)
{
    _channels.push_back(channel);
    
    if (channel->_duration > _duration)
        _duration = channel->_duration;
}

void C3DAnimation::removeChannel(C3DAnimationChannel* channel)
{
    std::vector<C3DAnimationChannel*>::iterator itr = _channels.begin();
    while (itr != _channels.end())
    {
        C3DAnimationChannel* chan = *itr;
        if (channel == chan) 
        {
            _channels.erase(itr);
            return;
        }
        else
        {
            itr++;
        }
    }
}

C3DAnimation* C3DAnimation::clone()
{
  
    C3DAnimation* animation = new C3DAnimation(getId());

    animation->_duration = _duration;
    animation->_frameCount = _frameCount;

    for( unsigned int k = 0; k < getClipCount(); k++)
    {
        C3DAnimationClip* clipSource = getClip(k);
        C3DAnimationClip* clip = clipSource->clone(animation);
        
        animation->addClip(clip);
                
    }

    std::list<C3DAnimationClip*>::iterator clipIter = _runningClips.begin();
    while (clipIter != _runningClips.end())
    {
        C3DAnimationClip* srcClip = *clipIter;
        C3DAnimationClip* dstClip = animation->findClip(srcClip->getID());
        if(dstClip != nullptr)
        {
            animation->addRunClip(dstClip);
        }
        clipIter++;
    }

    animation->autorelease();
    
    return animation;
}


//.....controller start....
void C3DAnimation::stopAll() 
{
    std::list<C3DAnimationClip*>::iterator clipIter = _runningClips.begin();
    while (clipIter != _runningClips.end())
    {
        C3DAnimationClip* clip = *clipIter;
        clip->stop();
        clipIter++;
    }
}

C3DAnimation::State C3DAnimation::getState() const
{
    return _state;
}

void C3DAnimation::resumeAll()
{
    if (_runningClips.empty())
        _state = IDLE;
    else
        _state = RUNNING;
}

void C3DAnimation::pauseAll()
{
    _state = PAUSED;
}

void C3DAnimation::addRunClip(C3DAnimationClip* clip)
{
    if (_runningClips.empty())
    {
        _state = RUNNING;
    }

    clip->retain();
    _runningClips.push_back(clip);
}

void C3DAnimation::removeRunClip(C3DAnimationClip* clip)
{

    std::list<C3DAnimationClip*>::iterator clipItr = _runningClips.begin();
    while (clipItr != _runningClips.end())
    {
        C3DAnimationClip* rClip = (*clipItr);
        if (rClip == clip)
        {
            _runningClips.erase(clipItr);
            SAFE_RELEASE(clip);
            break;
        }
        clipItr++;
    }

    if (_runningClips.empty())
        _state = IDLE;
}

void C3DAnimation::update(long elapsedTime)
{
    if (_state != RUNNING)
        return;

    std::list<C3DAnimationClip*>::iterator clipIter = _runningClips.begin();
    while (clipIter != _runningClips.end())
    {
        C3DAnimationClip* clip = (*clipIter);

        unsigned short res = clip->update(elapsedTime);

        if(res == C3DAnimationClip::CLIP_IS_MARKED_FOR_REMOVAL)
        {
            SAFE_RELEASE(clip);
            clipIter = _runningClips.erase(clipIter);
        }
        else if(res == C3DAnimationClip::CLIP_IS_PAUSED)
        {
            clipIter++;
        }
        else if(res == C3DAnimationClip::CLIP_IS_RESUME)
        {
        }
        else if(res == C3DAnimationClip::CLIP_IS_RESTARTED)
        {
            clipIter++;
        }
        else
        {
            clipIter++;
        }
    }

    if (_runningClips.empty())
        _state = IDLE;
}

}
