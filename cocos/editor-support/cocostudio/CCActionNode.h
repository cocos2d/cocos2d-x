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

#ifndef __ActionNODE_H__
#define __ActionNODE_H__

#include "cocostudio/CCActionFrame.h"
#include "cocostudio/DictionaryHelper.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {
    
class CocoLoader;
struct stExpCocoNode;
/**
*  @js NA
*  @lua NA
*/
class CC_STUDIO_DLL ActionNode : public cocos2d::Ref
{
public:

	/**
    * @~english Default constructor.
    * @~chinese 默认构造函数.
    */
	ActionNode();

	/**
    * @~english Default destructor.
    * @~chinese 默认析构函数.
    */
	virtual ~ActionNode();
	/**
	* @~english Sets the time interval of frame.
    * @~chinese 设置帧的间隔时间.
    *
	* @param fTime   @~english the time interval of frame @~chinese 帧间隔时间
	*/
	void setUnitTime(float fTime);

	/**
	* @~english Gets the time interval of frame.
    * @~chinese 获取帧的间隔时间.
    *
	* @return fTime   @~english the time interval of frame @~chinese 帧间隔时间
	*/
	float getUnitTime();
	/**
	* @~english Sets tag for ActionNode
    * @~chinese 设置动作节点的Tag
    *
	* @param tag    @~english tag of ActionNode @~chinese 动作节点的Tag
	*/
	void setActionTag(int tag);

	/**
	* @~english Gets tag for ActionNode
    * @~chinese 获取动作节点的Tag
    *
	* @return tag    @~english tag of ActionNode @~chinese 动作节点的Tag
	*/
	int getActionTag();

	/**
	* @~english Sets node which will run a action.
    * @~chinese 设置将要执行动作的节点.
    *
	* @param  @~english node which will run a action @~chinese 将要执行动作的节点
	*/
	void setObject(cocos2d::Ref* node);

	/**
	* @~english Gets node which will run a action.
    * @~chinese 获取将要执行动作的节点.
    *
	* @return  @~english node which will run a action @~chinese 将要执行动作的节点
	*/
	cocos2d::Ref* getObject();

	/**
	* @~english Inserts a ActionFrame to ActionNode.
    * @~chinese 向动作节点插入一个动作帧.
	*
	* @param index  @~english the index of ActionFrame @~chinese 动作帧的索引值
	*
	* @param frame  @~english the ActionFrame which will be inserted @~chinese 将要添加的动作帧
	*/
	void insertFrame(int index, ActionFrame* frame);

	/**
	* @~english Pushs back a ActionFrame to ActionNode.
    * @~chinese 在动作节点的动作序列队尾插入一个动作帧.
	*
	* @param frame  @~english the ActionFrame which will be added @~chinese 将要添加的动作帧
	*/
	void addFrame(ActionFrame* frame);

	/**
	* @~english Remove a ActionFrame from ActionNode.
    * @~chinese 从动作节点的动作序列中删除一个动作帧.
    *
	* @param frame  the ActionFrame which will be removed @~chinese 将要删除的动作帧
	*/
	void deleteFrame(ActionFrame* frame);

	/**
	* @~english Remove all ActionFrames from ActionNode.
    * @~chinese 删除动作节点下的所有动作帧.
    */
	void clearAllFrame();

	/**
	* @~english Gets index of first ActionFrame.
    * @~chinese 获取第一个动作帧的索引值.
    *
	* @return  @~english index of first ActionFrame @~chinese 第一个动作帧的索引值
	*/
	int getFirstFrameIndex();

	/**
	* @~english Gets index of last ActionFrame.
    * @~chinese 获取最后一个动作帧的索引值.
    *
	* @return  @~english index of last ActionFrame @~chinese 最后一个动作帧的索引值
	*/
	int getLastFrameIndex();

	/**
	* @~english Updates action states to some time.
	* @~chinese 在指定时间更新动作状态.
	* @param fTime   @~english the time when need to update @~chinese 需要更新的时间
	*/
	virtual bool updateActionToTimeLine(float fTime);

	/**
	*  @~english Play the action.
    *  @~chinese 播放动画.
    */
	virtual void playAction();

	/**
	*  @~english Stop the action.
    *  @~chinese 停止动画.
    */
	virtual void stopAction();

	/** 
    * @~english init properties with a json dictionary
    * @~chinese 使用json字典初始化属性值
    */
	virtual void initWithDictionary(const rapidjson::Value& dic, cocos2d::Ref* root);
    /** 
    * @~english init properties with binary file
    * @~chinese 使用二进制数据初始化属性值
    */
    virtual void initWithBinary(CocoLoader* cocoLoader, stExpCocoNode*	pCocoNode, Ref* root);

	/**
	* @~english Gets if the action is done once time.
    * @~chinese 获取动画是否已经完成过一次播放.
    *
	* @return   @~english that if the action is done once time @~chinese 动画是否已经完成过一次播放
	*/
	virtual bool isActionDoneOnce();
protected:
    int valueToInt(const std::string& value);
    bool valueToBool(const std::string& value);
    float valueToFloat(const std::string& value);
    
	int _currentFrameIndex;
	int _destFrameIndex;

	float _fUnitTime;

	int _actionTag;
	cocos2d::Spawn * _actionSpawn;
	cocos2d::Action* _action;
	cocos2d::Ref* _object;

	std::vector<cocos2d::Vector<ActionFrame*>*> _frameArray;
	int _frameArrayNum;

protected:
	virtual cocos2d::Node* getActionNode();
	virtual cocos2d::Spawn * refreshActionProperty();
	virtual void runAction();
	virtual void initActionNodeFromRoot(cocos2d::Ref* root);
	virtual void easingToFrame(float duration,float delayTime,ActionFrame* srcFrame,ActionFrame* destFrame);
};

}

#endif
