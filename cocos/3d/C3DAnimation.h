#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <string>
#include<list>
#include<vector>
#include "cocos2d.h"

namespace cocos2d
{

class C3DAnimationChannel;
class C3DAnimationClip;
class C3DActionListener;
class C3DAnimationCurve;
class C3DAnimationChannel;
class C3DBone;

/**
 * Defines structure to describe a generic property animation.
 */
class C3DAnimation : public cocos2d::CCObject
{
    friend class C3DAnimationClip;
    friend class C3DBone;
    friend class C3DAnimationChannel;
    friend class C3DResourceLoader;

public:
    /**
     * Creates C3DAnimation.
     */
    static C3DAnimation* create(const char* id);

    /**
     * Gets the animation's ID.
     */
    const char* getId() const;
    
    /**
     * Gets the animation's duration.
     */
    unsigned long getDuration() const;

    /**
     * Adds an animation clip to current animation.
     *
     * @param name The name of the target animation clip.
     * @param startFrame The start frame.
     * @param endFrame The end frame.
     * @param repeatCount repeat count.
     * @param speed The speed of the animation clip play.
     */
    C3DAnimationClip* addClip(const char* name,unsigned int startFrame,unsigned int endFrame,float repeatCount,float speed);

    /**
     * Replaces an animation clip from the current Animation.
     *
     * @param name The name of the target animation clip.
     * @param startFrame The start frame.
     * @param endFrame The end frame.
     * @param repeatCount repeat count.
     * @param speed The speed of the animation clip.
     */
    bool replaceClip(const char* name,unsigned int startFrame,unsigned int endFrame,float repeatCount,float speed);

    /**
     * Removes an animation clip from the current Animation.
     *
     * @param name The name of the target animation clip.
     */
    bool removeClip(const char* name);
    
    /**
     * Gets target animation clip by the specifiedID.
     *
     * @param clipId The ID of the target animation clip.
     */
    C3DAnimationClip* getClip(const char* clipId = nullptr);

    /**
     * Gets target animation clip by the specified index.
     *
     * @param index The index of the target animation clip.
     */
    C3DAnimationClip* getClip(unsigned int index) const;

    /**
     * Gets the count of the animation clip.
     */
    unsigned int getClipCount() const;
    
    /**
     * Plays the animation clip by the specified id.
     *
     * @param clipId The ID of the target animation clip.
     */
    void play(const char* clipId = nullptr);

    /**
     * Plays the target animation clip.
     */
    void play(C3DAnimationClip* clip);

    /**
     * Stops the target animation clip by the specified ID.
     *
     * @param clipId The ID of the target animation clip.
     */
    void stop(const char* clipId = nullptr);

    /**
     * Pauses the animation clip by the specified ID.
     *
     * @param clipId The ID of the target animation clip.
     */
    void pause(const char* clipId = nullptr);

    /**
     * Resumes the animation clip by the specified ID.
     *
     * @param clipId The ID of the target animation clip.
     */
    void resume(const char* clipId = nullptr);

    /**
     * Sets the animation's frame count
     *
     * @param frameCount frame count
     */
    void setFrameCount(unsigned int frameCount);

    /**
     * Gets the animation's frame count
     */
    unsigned int getFrameCount();
    
    /**
     * Gets the current animation clip
     */
    C3DAnimationClip* getCurAnimationClip() { return _currentClip; }

    /**
     * clone
     */
    C3DAnimation* clone();
    
public:

    enum State
    {
        RUNNING,
        IDLE,
        PAUSED,
        STOPPED
    };

    /**
     * Stops all animation clip
     */
    void stopAll();

    /**
     * Resumes all animation clip
     */
    void resumeAll();    

    /**
     * Pauses all animation clip
     */
    void pauseAll();

    /**
     * Gets current animation state
     */
    State getState() const;

    /**
     * Adds target animation clip to runing animation clip list
     */
    void addRunClip(C3DAnimationClip* clip);

    /**
     * Removes target animation clip from runing animation clip list
     */
    void removeRunClip(C3DAnimationClip* clip);
    
    /**
     * Called per frame to update this animation when it is active.
     */
    void update(long elapsedTime);


private:
    /**
     * Constructor.
     */
    C3DAnimation(const char* id);
   
    /**
     * Destructor.
     */
    ~C3DAnimation();
    
    /**
     * Creates animation clip by default param.
     */
    void createDefaultClip();    
    
    /**
     * Creates a new animation clip.
     *
     * @param id The ID of the animation clip.
     * @param start The start frame.
     * @param end The end frame.
     */
    C3DAnimationClip* createClip(const char* id, unsigned long start, unsigned long end);
    
    /**
     * Adds a animation clip.
     */
    void addClip(C3DAnimationClip* clip);

    /**
     * Finds the animation clip by the specified id.
     */
    C3DAnimationClip* findClip(const char* id) const;

    /**
     * Creates AnimationChannel.
     */
    C3DAnimationChannel* createChannel(C3DBone* bone, unsigned int keyCount, unsigned long* keyTimes, float* keyValues);
    
    /**
     * Creates AnimationChannel.
     */
    C3DAnimationChannel* createChannel(C3DBone* bone, C3DAnimationCurve* animationcurve);

    /**
     * Adds AnimationChannel.
     */
    void addChannel(C3DAnimationChannel* channel);

    /**
     * Removes AnimationChannel.
     */
    void removeChannel(C3DAnimationChannel* channel);

    std::string _id;                       
    unsigned long _duration;                // length(in milliseconds).
    unsigned int _frameCount;
    std::vector<C3DAnimationChannel*> _channels;    
    C3DAnimationClip* _defaultClip;           
    std::vector<C3DAnimationClip*>* _clips;

    C3DAnimationClip* _currentClip;

    State _state;
    std::list<C3DAnimationClip*> _runningClips;
    
};

}

#endif
