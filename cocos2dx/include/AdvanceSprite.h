//
//  AdvanceSprite.h
//  FlyingFreak
//
//  Created by varadharaj on 16/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

//#include "cocos2d.h"
//using namespace cocos2d;

#ifndef _AdvanceSprite_H
#define _AdvanceSprite_H

#include "CCSprite.h"
#include "CCMutableArray.h"
namespace   cocos2d {
    
class AdvanceSprite : public CCSprite
{
    CCMutableArray<CCSpriteFrame *> *m_AnimationFrames;
    //Indexing variable.
    int m_StartingIndex, m_EndingIndex, m_CurrentIndex, m_IncrementValue;
    
    //Loopoing variable.
    int m_RunningLoop, m_NumberOfLoop;
    
    //Frame Rate.
    float m_FrameRate;
    
    //Callback funciton pointer.
    SEL_CallFunc m_pfnSelectorDelegate;
    SelectorProtocol *m_pTarget;
    
    //Frame Rate Calculation variable.
    ccTime m_ElaspeTime;
    
    //Animation mode variable.
    bool m_NeedToRunReverseAnimation, m_AnimationMode, m_isPlistLoaded;
    bool m_isAnimationRunning;
    bool m_NeedToDeleteItself;
    //Local funciton.
    float calculateFrameRate(int number_frames){return 1.0f / number_frames;}
    void increaseCurrentIndex();
    
    void removeObjectItself();
    
    virtual void update(ccTime dt);
public:
    //
    AdvanceSprite();
    ~AdvanceSprite();
    
    //Add Frames to run Animation.
    void addFrames(const char* pList); // Has Texture file name in pList.
    void addFrames(const char* pList, const char* textureFileName);
    void addFrames(CCMutableArray<CCSpriteFrame*> *frames);
    void addFrames(CCMutableArray<CCSpriteFrame*> *frames, int displayTextureIndex);
    
    //Sets Frame Rate for running Animation
    void setFrameRate(int NumberOfFramesPerSecond){m_FrameRate = calculateFrameRate(NumberOfFramesPerSecond);}
    void setFrameRate(float frameRate){ m_FrameRate = frameRate;}
    
    /***************************  Animation Function *************************
    
     startInd - Starting index of loaded array for running Animation
     endInd - Ending index of loaded array for running Animation
     number_Loop - Number of Loop that Animaiton to run.
     pfnSelectorDelegate - Function pointer for Notification.
     pTarget - Class pointer for calling Funciton notification.
     NumberOfFramesPerSecond - Number of Frames to run per Second.
     NeedToRunReverseAnimation - Needs to run reverse Animation.
     NeedToDeleteItself - Needs the object to delete after finish the animation.
     
    ***************************************************************************/
    
    void startAnimation(int startInd, int endInd, int number_Loop, SEL_CallFunc pfnSelectorDelegate, SelectorProtocol *pTarget,int NumberOfFramesPerSecond, bool NeedToRunReverseAnimation, bool NeedToDeleteItself);
    
    //Running Animation from Current index to Parameter Index.
    void moveTo(int index){ startAnimation(m_CurrentIndex, index, 1, m_pfnSelectorDelegate, m_pTarget, -1, false, m_NeedToDeleteItself);}
    
    //Controller for Animation.
    void pauseAnimation(){pauseSchedulerAndActions(); }
    void resumeAnimation(){resumeSchedulerAndActions(); }
    void stopAnimaiton();
};
}//namespace   cocos2d 

#endif