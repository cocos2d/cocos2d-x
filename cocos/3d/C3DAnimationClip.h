#ifndef ANIMATIONCLIP_H_
#define ANIMATIONCLIP_H_

#include <string>

#include <vector>
#include "cocos2d.h"

namespace cocos2d
{

class C3DAnimation;
class AnimationValue;
class C3DActionListener;
class C3DActionEvent;

/**
 * Defines the structure of an Animation to be played.
 */
class C3DAnimationClip : public cocos2d::CCObject
{
   // friend class C3DAnimationController;
    friend class C3DAnimation;
    friend class C3DAnimationChannel;

public:
    /**
     * Gets ID.
     */
    const char* getID() const;

    /**
     * Gets start time.
     */
    unsigned long getStartTime() const;

    /**
     * Gets end time.
     */
    unsigned long getEndTime() const;

    /**
     * Gets elasped time.
     */
    unsigned long getElaspedTime() const;

    /**
     * Sets repeat count.
     */
    void setRepeatCount(float repeatCount);

    /**
     * Gets repeat count.
     */
    float getRepeatCount() const;
       
    /**
     * Gets duration.
     */
    unsigned long getDuration() const;

    /**
     * Sets speed.
     */
    void setSpeed(float speed);

    /**
     * Gets speed.
     */
    float getSpeed() const;

    /**
     * Sets blend weight.
     */
    void setBlendWeight(float blendWeight);

    /**
     * Gets blend weight.
     */
    float getBlendWeight() const;

    /**
     *  Is Playeing?.
     */
    bool isPlaying() const;
    
    /**
     *  Is Paused.
     */
    bool isPaused() const;

    /**
     *  Do play.
     */
    void play();

    /**
     * Fades this clip out, and the specified clip in over the given duration.
     *
     * @param clip The clip to fade into.
     * @param duration The duration of the fade.
     */
    void crossFade(C3DAnimationClip* clip, unsigned long duration);

    /**
     *  Do stop.
     */
    void stop();
    
    /**
     *  Do pause.
     */
    void pause();

    /**
     *  Do resume.
     */
    void resume();   

    /**
     *  Check Resumed.
     */
    bool isResumed() const;

    /**
     *  Adds an action Event.
     */
    void addActionEvent(C3DActionListener* listener, unsigned long eventTime);
    void addActionEvent(C3DActionEvent* actionEvent);

    void clearActionEvent();

    /**
     *  Get Frame Count.
     */
    int getFrameCount();

    /**
    * Sets Current Frame
    */
    void setCurrentFrame(int nFrame);

    /**
    * Gets Current Frame
    */
    int getCurrentFrame();
    
    /**
    * clone
    */
    C3DAnimationClip* clone(C3DAnimation* animation);

private:
    
    static const unsigned short CLIP_IS_NONE = 0;
    static const unsigned short CLIP_IS_PLAYING = 0x01;             
    static const unsigned short CLIP_IS_STARTED = 0x02;            
    static const unsigned short CLIP_IS_MARKED_FOR_REMOVAL = 0x04; 
    static const unsigned short CLIP_IS_RESTARTED = 0x08;  

    static const unsigned short CLIP_IS_PAUSED = 0x10;
    static const unsigned short CLIP_IS_FADING_OUT = 0x20;  
    static const unsigned short CLIP_IS_FADING_OUT_STARTED = 0x40;         
    static const unsigned short CLIP_IS_FADING_IN = 0x80;  

    static const unsigned short CLIP_IS_RESUME= 0x100;

    static const unsigned short CLIP_IS_ALL = 0xFFFF;

    /**
     * Constructor.
     */
    C3DAnimationClip(const char* id, C3DAnimation* animation, unsigned long startTime, unsigned long endTime);
   
    /**
     * Destructor.
     */
    ~C3DAnimationClip();

    /**
    * Update
    */
    unsigned short update(unsigned long elapsedTime);

    unsigned short update_loop(unsigned long elapsedTime);

    unsigned short update_once(unsigned long elapsedTime);

    /**
    * Is have target state
    */
    bool isState(unsigned short bit) const;

    /**
    * Set state
    */
    void setState(unsigned short bit);

    /**
    * Reset state
    */
    void resetState(unsigned short bit);

    std::string _id;                                 
    C3DAnimation* _animation;                              // The C3DAnimation this clip is created from.
    unsigned long _startTime;                           // Start time of the clip.
    unsigned long _endTime;                             // End time of the clip.
    unsigned long _duration;                            // The total duration.
    unsigned long _activeDuration;                      // The active duration of the clip.

    unsigned short _stateBits;                           // Bit flag used to keep track of the clip's current state.

    float _repeatCount;                                 // The clip's repeat count.

    float _speed;                                       // The speed that the clip is playing. Default is 1.0. Negative goes in reverse.
    unsigned long _timeStarted;                         // The game time when this clip was actually started.

    long _elapsedTime;                                  // Time elapsed while the clip is running.

    float _blendWeight;                                 // The clip's blendweight.

    AnimationValue* _value;        

    C3DAnimationClip* _crossFadeToClip;                    // The clip to cross fade to.
    unsigned long _crossFadeOutElapsed;                 // The amount of time that has elapsed for the crossfade.
    unsigned long _crossFadeOutDuration;                // The duration of the cross fade.
        
    std::list<C3DActionEvent*>* _actionEvents;

    unsigned int _frameCount;// 
  
};

}
#endif
