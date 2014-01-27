/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "CCActionNode.h"
#include "cocostudio/DictionaryHelper.h"

namespace cocostudio {

/**
*  @js NA
*  @lua NA
*/
class ActionObject:public cocos2d::Object
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
	void play(cocos2d::CallFunc* func);

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
	void initWithDictionary(const rapidjson::Value& dic,Object* root);

	/*scheduler update function*/
	void simulationActionUpdate(float dt);
protected:
	cocos2d::Vector<ActionNode*> _actionNodeList;/*actionnode*/
	std::string _name;
	bool _loop;
	bool _bPause;
	bool _bPlaying;
	float _fUnitTime;
	float _currentTime;
	cocos2d::Scheduler *_pScheduler;
	cocos2d::CallFunc *_CallBack;
	float _fTotalTime;
};

}

#endif
