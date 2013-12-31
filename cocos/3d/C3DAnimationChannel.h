#ifndef ANIMATIONCHANNEL_H_
#define ANIMATIONCHANNEL_H_



namespace cocos2d
{

class C3DAnimationCurve;

/**
* Defines a channel which holds the target Animation.
*/
class C3DAnimationChannel
{
    friend class C3DAnimationClip;
    friend class C3DAnimation;
    friend class C3DBone;

private:
    /**
     * Constructor.
     */
    C3DAnimationChannel(C3DAnimation* animation, C3DBone* bone,C3DAnimationCurve* curve, unsigned long duration);
       
    /**
     * Desstructor.
     */
    ~C3DAnimationChannel();
   
    /**
     * Get C3DAnimationCurve.
     */
    C3DAnimationCurve* getCurve() const;

    C3DAnimation* _animation;                
    
    C3DBone* _bone;
      
    C3DAnimationCurve* _curve;              
    unsigned long _duration;              
};

}

#endif
