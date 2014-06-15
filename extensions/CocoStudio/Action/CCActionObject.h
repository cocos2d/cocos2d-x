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

#ifndef __ActionObject_H__
#define __ActionObject_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "../Json/rapidjson/document.h"

NS_CC_EXT_BEGIN

class CocoLoader;
struct stExpCocoNode;

class ActionNode;
/**
*   @js NA
*   @lua NA
*/
class CC_EX_DLL ActionObject:public CCObject
{
public:

	/**
	* Default constructor
	*/
	ActionObject();

	/**
	* Default destructor
	*/
	virtual ~ActionObject();

	/**
	* Sets name for object
	*
	* @param name    name of object
	*/
	void setName(const char* name);

	/**
	* Sets name for object
	*
	* @return name of object
	*/
	const char* getName();

	/**
	* Sets if the action will loop play.
	*
	* @param bLoop     that if the action will loop play
	*/
	void setLoop(bool bLoop);

	/**
	* Gets if the action will loop play.
	*
	* @return   that if the action will loop play
	*/
	bool getLoop();

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
	* Sets the current time of frame.
	*
	* @param fTime   the current time of frame
	*/
	void setCurrentTime(float fTime);

	/**
	* Gets the current time of frame.
	*
	* @return fTime   the current time of frame
	*/
	float getCurrentTime();

	/**
	* Gets the total time of frame.
	*
	* @return fTime   the current time of frame
	*/
	float getTotalTime();
	/**
	* Return if the action is playing.
	*
	* @return true if the action is playing, false the otherwise
	*/
	bool isPlaying();

	/**
	* Play the action.
	*/
	void play();

	/**
	* Play the action.
	*
	* @ Action Call Back
	*/
	void play(CCCallFunc* func);

	/**
	* Pause the action.
	*/
	void pause();

	/**
	* Stop the action.
	*/
	void stop();

	/**
	* Adds a ActionNode to play the action.
	*
	* @node    the ActionNode which will play the action
	*/
	void addActionNode(ActionNode* node);

	/**
	* Removes a ActionNode which play the action.
	*
	* @node    the ActionNode which play the action
	*/
	void removeActionNode(ActionNode* node);

	/*update frame method*/
	void updateToFrameByTime(float fTime);

	/*init properties with a json dictionary*/
	void initWithDictionary(const rapidjson::Value& dic,CCObject* root);
    void initWithBinary(CocoLoader* pCocoLoader, stExpCocoNode*	pCocoNode, CCObject* root);

	void simulationActionUpdate(float dt);

protected:
    int valueToInt(std::string& value);
    bool valueToBool(std::string& value);
    float valueToFloat(std::string& value);
    
	CCArray* m_ActionNodeList;/*actionnode*/
	std::string m_name;
	bool m_loop;
	bool m_bPause;
	bool m_bPlaying;
	float m_fUnitTime;
	float m_CurrentTime;
	CCScheduler *m_pScheduler;
	CCCallFunc *m_CallBack;
	float m_fTotalTime;
};

NS_CC_EXT_END

#endif
