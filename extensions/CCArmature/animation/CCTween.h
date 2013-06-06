/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/


#ifndef __CCTWEEN_H__
#define __CCTWEEN_H__

#include "CCProcessBase.h"
#include "../utils/CCTweenFunction.h"

NS_CC_EXT_BEGIN

class CCBone;
class CCAnimation;

class  CCTween : public CCProcessBase
{
public:
    /**
	 * Create with a CCBone
     * @param bone the CCBone CCTween will bind to
     */
	static CCTween* create(CCBone *bone);
public:
	CCTween(void);
	virtual ~CCTween(void);

    /**
	 * Init with a CCBone
     * @param bone the CCBone CCTween will bind to
     */
	virtual bool init(CCBone *bone);
	
    /**
	 * Start the Process
     *
     * @param  movementBoneData  the MovementBoneData include all frame datas
     * @param  durationTo the frames between two animation changing-over.
     *         It's meaning is changing to this animation need how many frames
     *
     *         -1 : use the value from MovementData get from flash design panel
     * @param  durationTween  the frame count you want to play in the game.
     *         if  _durationTween is 80, then the animation will played 80 frames in a loop
     *
     *         -1 : use the value from MovementData get from flash design panel
     *
     * @param  loop   whether the animation is loop
     *
     *         loop < 0 : use the value from MovementData get from flash design panel
     *         loop = 0 : this animation is not loop
     *         loop > 0 : this animation is loop
     *
     * @param  tweenEasing    tween easing is used for calculate easing effect
     *
     *         TWEEN_EASING_MAX : use the value from MovementData get from flash design panel
     *         -1 : fade out
     *         0  : line
     *         1  : fade in
     *         2  : fade in and out
     *
     */
	virtual void play(MovementBoneData *movementBoneData, int durationTo, int durationTween,  int loop, int tweenEasing);

protected:
    
    /**
	 * Update(float dt) will call this handler, you can handle your logic here
     */
	virtual void updateHandler();
    
    /**
	 * Calculate which frame arrived, and if current frame have event, then call the event listener
     */
    virtual float updateFrameData(float currentPrecent, bool activeFrame = false);
    
    /**
	 * Calculate the between value of _from and _to, and give it to between frame data
     */
	virtual void setBetween(FrameData *from, FrameData *to);
    
    /**
	 * According to the percent to calculate current FrameData with tween effect
     */
	virtual FrameData *tweenNodeTo(float percent, FrameData *node = NULL);
    
	/**
	 * Update display index and process the key frame event when arrived a key frame
     */
    virtual void arriveKeyFrame(FrameData *keyFrameData);
protected:
	//! A weak reference to the current MovementBoneData. The data is in the data pool
	CC_SYNTHESIZE(MovementBoneData*, m_pMovementBoneData, MovementBoneData)

	FrameData *m_pTweenData;		//! The computational tween frame data, //! A weak reference to the CCBone's tweenData
	FrameData *m_pFrom;				//! From frame data, used for calculate between value
    FrameData *m_pTo;				//! To frame data, used for calculate between value
	FrameData *m_pBetween;			//! Between frame data, used for calculate current FrameData(m_pNode) value

    FrameData *m_pCurrentKeyFrame;	//! A weak reference to the current FrameData. The data is in the data pool
    
	CCBone *m_pBone;					//! A weak reference to the CCBone

	CCTweenType m_eFrameTweenEasing;	//! Dedermine which tween effect current frame use 

	bool m_bIsTweenKeyFrame;
    
    
	int betweenDuration;			//! Current key frame will last betweenDuration frames
	int m_iTotalDuration;			


	int m_iFromIndex;				//! The current frame index in FrameList of MovementBoneData, it's different from m_iFrameIndex
	int m_iToIndex;					//! The next frame index in FrameList of MovementBoneData, it's different from m_iFrameIndex


	FrameData *m_pEditKeyFrame;
    
	CCAnimation *m_pAnimation;
};

NS_CC_EXT_END

#endif /*__CCTWEEN_H__*/