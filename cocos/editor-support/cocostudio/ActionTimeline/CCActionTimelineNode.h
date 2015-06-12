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

#ifndef __COCOSSTUDIO_CCACTIONTIMELINENODE_H__
#define __COCOSSTUDIO_CCACTIONTIMELINENODE_H__

#include "CCActionTimeline.h"
#include "CCTimelineMacro.h"
#include "cocostudio/CocosStudioExport.h"

NS_TIMELINE_BEGIN

class ActionTimeline;

class CC_STUDIO_DLL ActionTimelineNode : public cocos2d::Node
{
public:
    static ActionTimelineNode* create(cocos2d::Node* root, ActionTimeline* action);
    
    ActionTimelineNode();
    ~ActionTimelineNode();
    
    bool init() override;

    /** @~english Initialize with root node and actiontimeline.
    *   @~chinese 使用根节点和时间轴动画初始化。
    * @param root @~english Root node.
    * @~chinese 根节点。
    * @param action @~english Action time line.
    * @~chinese 时间轴动画。
    * @return @~english Is init succeed.
    * @~chinese 是否初始化成功。
    */
    bool init(cocos2d::Node* root, ActionTimeline* action);
    
    /** @~english Set root node.
    *   @~chinese 设置根节点。
    * @param root @~english Root node.
    * @~chinese 根节点。
    */
    virtual void setRoot(cocos2d::Node* root);
    /** @~english Get root node.
    *   @~chinese 获取根节点。
    * @return @~english Root node.
    * @~chinese 根节点。
    */
    virtual cocos2d::Node* getRoot();
    
    /** @~english Set action time line.
    *   @~chinese 设置时间轴动画。
    * @param action @~english Action time line.
    * @~chinese 时间轴动画。
    */
    virtual void setActionTimeline(ActionTimeline* action);
    /** @~english Get action time line.
    *   @~chinese 获取时间轴动画。
    * @return @~english Action time line.
    * @~chinese 时间轴动画。
    */
    virtual ActionTimeline* getActionTimeline();
    
protected:
    cocos2d::Node* _root;
    ActionTimeline* _action;
};

NS_TIMELINE_END


#endif /*__COCOSSTUDIO_CCACTIONTIMELINENODE_H__*/
