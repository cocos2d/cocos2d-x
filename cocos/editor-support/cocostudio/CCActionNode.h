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

#include "editor-support/cocostudio/CCActionFrame.h"
#include "editor-support/cocostudio/DictionaryHelper.h"
#include "editor-support/cocostudio/CocosStudioExport.h"

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
    void setObject(cocos2d::Ref* node);

    /**
    * Gets node which will run a action.
    *
    * @return  node which will run a action
    */
    cocos2d::Ref* getObject();

    /**
    * Insets a ActionFrame to ActionNode.
    *
    * @param index  the index of ActionFrame
    *
    * @param frame  the ActionFrame which will be inserted
    */
    void insertFrame(int index, ActionFrame* frame);

    /**
    * Pushes back a ActionFrame to ActionNode.
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
    virtual void initWithDictionary(const rapidjson::Value& dic, cocos2d::Ref* root);
    virtual void initWithBinary(CocoLoader* cocoLoader, stExpCocoNode*    pCocoNode, Ref* root);

    /**
    * Gets if the action is done once time.
    *
    * @return   that if the action is done once time
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
