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

#ifndef __ActionNODE_H__
#define __ActionNODE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCActionFrame.h"
#include "../Json/DictionaryHelper.h"
#include "../Json/rapidjson/document.h"
NS_CC_EXT_BEGIN

class CocoLoader;
struct stExpCocoNode;


/**
*   @js NA
*   @lua NA
*/
class CC_EX_DLL ActionNode:public CCObject
{
public:
    
    /**
     * Default constructor
     */
    ActionNode();
    
    /**
     * Default destructor
     */
    virtual ~ActionNode();
    /**
     * Sets the time interval of frame.
     *
	 * @param fTime   the time interval of frame
     */
	void setUnitTime(float fTime);
    
    /**
     * Gets the time interval of frame.
     *
	 * @return fTime   the time interval of frame
     */
	float getUnitTime();
    /**
     * Sets tag for ActionNode
     *
     * @param tag    tag of ActionNode
     */
	void setActionTag(int tag);
    
    /**
     * Gets tag for ActionNode
     *
     * @return tag    tag of ActionNode
     */
	int getActionTag();

    /**
     * Sets node which will run a action.
     *
     * @param  node which will run a action
     */
	void setObject(CCObject* node);
    
    /**
     * Gets node which will run a action.
     *
     * @return  node which will run a action
     */
	CCObject* getObject();

    /**
     * Insets a ActionFrame to ActionNode.
     *
     * @param index  the index of ActionFrame
     *
     * @param frame  the ActionFrame which will be inserted
     */
	void insertFrame(int index, ActionFrame* frame);
    
    /**
     * Pushs back a ActionFrame to ActionNode.
     *
     * @param frame  the ActionFrame which will be added
     */
	void addFrame(ActionFrame* frame);
    
    /**
     * Remove a ActionFrame from ActionNode.
     *
     * @param frame  the ActionFrame which will be removed
     */
	void deleteFrame(ActionFrame* frame );
    
    /**
     * Remove all ActionFrames from ActionNode.
     */
	void clearAllFrame();

    /**
     * Gets index of first ActionFrame.
     *
     * @return  index of first ActionFrame
     */
	int getFirstFrameIndex();
    
    /**
     * Gets index of last ActionFrame.
     *
     * @return  index of last ActionFrame
     */
	int getLastFrameIndex();

    /**
     * Updates action states to some time.
     *
     * @param fTime   the time when need to update
     */
	virtual bool updateActionToTimeLine(float fTime);

    /**
     * Play the action.
     */
	virtual void playAction();

    /**
     * Stop the action.
     */
	virtual void stopAction();
	
    /*init properties with a json dictionary*/
	virtual void initWithDictionary(const rapidjson::Value& dic,CCObject* root);
    virtual void initWithBinary(CocoLoader* pCocoLoader, stExpCocoNode*	pCocoNode, CCObject* root);
    /**
     * Gets if the action is done once time.
     *
	 * @return   that if the action is done once time
     */
	virtual bool isActionDoneOnce();
protected:
    int valueToInt(std::string& value);
    bool valueToBool(std::string& value);
    float valueToFloat(std::string& value);
    
	int currentFrameIndex;
	int destFrameIndex;
	
	float m_fUnitTime;
    
	int m_ActionTag;
	CCObject* m_Object;
    CCSpawn * m_actionSpawn;
	CCAction* m_action;
	CCArray* m_FrameArray;
	int frameArrayNum;

protected:
	virtual CCNode* getActionNode();
	virtual CCSpawn * refreshActionProperty();
	virtual void runAction();
	virtual void initActionNodeFromRoot(CCObject* root);
	virtual void easingToFrame(float duration,float delayTime,ActionFrame* srcFrame,ActionFrame* destFrame);
};

NS_CC_EXT_END

#endif
