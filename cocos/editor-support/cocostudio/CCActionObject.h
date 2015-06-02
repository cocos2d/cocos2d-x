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

#include "cocostudio/CCActionNode.h"
#include "2d/CCActionInstant.h"
#include "cocostudio/DictionaryHelper.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

class CocoLoader;
struct stExpCocoNode;
    
/**
*  @js NA
*  @lua NA
*/
class CC_STUDIO_DLL ActionObject : public cocos2d::Ref
{
public:

	/**
    * @~english Default constructor.
    * @~chinese 默认构造函数.
    */
	ActionObject();

	/**
    * @~english Default destructor.
    * @~chinese 默认析构函数.
    */
	virtual ~ActionObject();

	/**
	* @~english Sets name for object
    * @~chinese 设定对象名称
    *
	* @param name    @~english name of object @~chinese 对象名称
	*/
	void setName(const char* name);

	/**
	* @~english Gets name of object
    * @~chinese 获取对象名称
    *
	* @return @~english name of object @~chinese 对象名称
	*/
	const char* getName();

	/**
	* @~english Sets if the action will loop play.
    * @~chinese 摄动动作是否循环播放.
    *
	* @param bLoop     @~english that if the action will loop play @~chinese 动作是否循环播放
	*/
	void setLoop(bool bLoop);

	/**
	* @~english Gets if the action will loop play.
    * @~chinese 获取动作是否循环播放.
    *
	* @return   @~english that if the action will loop play @~chinese 动作是否循环播放
	*/
	bool getLoop();

	/**
	* @~english Sets the time interval of frame.
    * @~chinese 设定帧间隔时间.
    *
	* @param fTime   @~english the time interval of frame @~chinese 帧间隔时间
	*/
	void setUnitTime(float fTime);

	/**
	* @~english Gets the time interval of frame.
    * @~chinese 获取帧间隔时间.
    *
	* @return @~english the time interval of frame @~chinese 帧间隔时间
	*/
	float getUnitTime();

	/**
	* @~english Sets the current time of frame.
    * @~chinese 设定帧动画当前时间.
    *
	* @param fTime   @~english the current time of frame @~chinese 当前时间
	*/
	void setCurrentTime(float fTime);

	/**
	* @~english Gets the current time of frame.
    * @~chinese 获取帧动画当前时间.
    *
	* @return @~english the current time of frame @~chinese 当前时间
	*/
	float getCurrentTime();

	/**
	* @~english Gets the total time of frame.
    * @~chinese 获取帧动画总时长.
    *
	* @return @~english the total time of frame @~chinese 帧动画总时长
	*/
	float getTotalTime();

	/**
	* @~english Return if the action is playing.
    * @~chinese 获取动作是否正在播放.
    *
	* @return @~english true if the action is playing, false the otherwise @~chinese 正在播放返回true，否则返回false
	*/
	bool isPlaying();

	/**
	* @~english Play the action.
    * @~chinese 播放动作.
    */
	void play();

	/**
	* @~english Play the action.
    * @~chinese 播放动作.
    *
	* @param func  @~english Action Call Back @~chinese 动作回调函数
	*/
	void play(cocos2d::CallFunc* func);

	/** 
	* @~english Pause the action.
    * @~chinese 暂停动作.
    */
	void pause();

	/**
	* @~english Stop the action.
    * @~chinese 停止动作.
    */
	void stop();

	/**
	* @~english Adds a ActionNode to play the action.
    * @~chinese 在节点列表中添加一个动作节点.
    *
	* @param node    @~english the ActionNode which will play the action @~chinese 将添加的动作节点
	*/
	void addActionNode(ActionNode* node);

	/**
	* @~english Removes a ActionNode which play the action.
    * @~chinese 从节点列表中删除一个节点.
    *
	* @param node    @~english the ActionNode which play the action @~chinese 将删除的动作节点
	*/
	void removeActionNode(ActionNode* node);

	/** 
    * @~english update frame action to special time
    * @~chinese 更新动作到指定时间点
    */
	void updateToFrameByTime(float fTime);

    /**
    * @~english init properties with a json dictionary
    * @~chinese 使用json字典初始化属性值
    */
    void initWithDictionary(const rapidjson::Value& dic, cocos2d::Ref* root);
    /**
    * @~english init properties with binary file
    * @~chinese 使用二进制数据初始化属性值
    */
    void initWithBinary(CocoLoader* cocoLoader, stExpCocoNode*	pCocoNode, cocos2d::Ref* root);


	/**
    * @~english scheduler update function
    * @~chinese 状态更新回调函数
    */
	void simulationActionUpdate(float dt);
protected:
    int valueToInt(const std::string& value);
    bool valueToBool(const std::string& value);
    float valueToFloat(const std::string& value);
    
	cocos2d::Vector<ActionNode*> _actionNodeList;
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
