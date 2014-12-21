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

#ifndef __LUA_TOUCH_EVENT_MANAGER_H__
#define __LUA_TOUCH_EVENT_MANAGER_H__

#include <string>
#include <set>
#include <unordered_map>
#include "LuaEventNode.h"
#include "base/CCEventListenerTouch.h"
#include "platform/CCStdC.h"

NS_CC_BEGIN

class LuaTouchTargetNode;

#define CCTOUCHBEGAN        0
#define CCTOUCHMOVED        1
#define CCTOUCHENDED        2
#define CCTOUCHCANCELLED    3
#define CCTOUCHADDED        4
#define CCTOUCHREMOVED      5
#define ccTouchMax          6


class LuaTouchEventManager : public Node
{
public:
    /** returns a shared instance of the LuaTouchEventManager */
    static LuaTouchEventManager* getInstance();

    /**
     *  Destroys the instance of LuaTouchEventManager.
     */
    static void destroyInstance();


    void addTouchableNode(LuaEventNode *node);
    void removeTouchableNode(LuaEventNode *node);

    void onTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event *pEvent);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent);
    void onTouchesCancelled(const std::vector<Touch*>& touches, Event *pEvent);

    virtual void cleanup(void);

    using Node::addChild;
    virtual std::string getDescription() const override;

CC_CONSTRUCTOR_ACCESS:
    LuaTouchEventManager();
    ~LuaTouchEventManager();

    bool init();
    bool initWithSize(const Size& size);

protected:
    friend class Node;

    std::set<int> m_touchingIds;
    Vector<LuaEventNode*> _touchableNodes;
    Vector<LuaTouchTargetNode*> _touchingTargets;
    bool m_touchDispatchingEnabled;
    EventListenerTouchAllAtOnce *_touchListener;

    void sortAllTouchableNodes(Vector<LuaEventNode*>&nodes);
    void enableTouchDispatching();
    void disableTouchDispatching();

    void dispatchingTouchEvent(const std::vector<Touch*>& touches, Event *pEvent, int event);
    void dispatchingTouchEventReal(const std::vector<Touch*>& touches, Event *pEvent, int event);
    
	void cleanDisabledNode();


    /** Walks though scene graph to get the draw order for each node, it's called before sorting event listener with scene graph priority */
    void visitTarget(Node* node, bool isRootNode);

    /** The map of node and LuaEventNode */
    std::unordered_map<Node*, LuaEventNode*> _nodeLuaEventNodeMap;

    /** The map of node and its event priority */
    std::unordered_map<Node*, int> _nodePriorityMap;

    /** key: Global Z Order, value: Sorted Nodes */
    std::unordered_map<float, std::vector<Node*>> _globalZOrderNodeMap;

    int _nodePriorityIndex;

	bool _bDispatching;
};

// end of LuaTouchEventManager group
/// @}

NS_CC_END

#endif // __LUA_TOUCH_EVENT_MANAGER_H__
