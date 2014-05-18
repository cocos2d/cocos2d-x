/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2009      Valentin Milea
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCNODE_H__
#define __CCNODE_H__

#include "base/ccMacros.h"
#include "base/CCEventDispatcher.h"
#include "base/CCVector.h"
#include "math/CCAffineTransform.h"
#include "math/CCMath.h"
#include "renderer/ccGLStateCache.h"
#include "2d/CCScriptSupport.h"
#include "2d/CCProtocols.h"
#include "CCGL.h"

NS_CC_BEGIN

class GridBase;
class Touch;
class Action;
class LabelProtocol;
class Scheduler;
class ActionManager;
class Component;
class ComponentContainer;
class EventDispatcher;
class Scene;
class Renderer;
class GLProgram;
class GLProgramState;
#if CC_USE_PHYSICS
class PhysicsBody;
#endif

/**
 * @addtogroup base_nodes
 * @{
 */

enum {
    kNodeOnEnter,
    kNodeOnExit,
    kNodeOnEnterTransitionDidFinish,
    kNodeOnExitTransitionDidStart,
    kNodeOnCleanup
};

bool nodeComparisonLess(Node* n1, Node* n2);

class EventListener;

/** @概要:节点是场景图的基本元素。场景图的基本元素必须是节点对象或者是节点对象的子类。
 一些常用的节点对象：Scene, Layer, Sprite, Menu, Label.

 一个节点的主要特点:
 - 他们可以包含其他的节点对象(`addChild`, `getChildByTag`, `removeChild`, etc)
 - 他们可以安排定期的回调(`schedule`, `unschedule`, etc)
 - 他们可以执行一些动作(`runAction`, `stopAction`, etc)

 子类节点通常意味着(单一的/所有的):
 - 重写初始化资源并且可以安排回调
 - 创建回调来操作进行的时间
 - 重写“draw”来渲染节点

 节点的属性:
 - 位置（默认值：x=0,y=0）
 - 缩放（默认值：x=1,y=1）
 - 旋转（以角度为单位，按顺时针方向）（默认值：0）
 - 锚点（默认值：x=0,y=0）
 - 内容大小（默认值：width=0,heigh=0）
 - 可见性（默认值：true）

 局限性：Limitations:
 - 一个节点类是一个“void”对象。如果你想要在场景中画一些东西，你应该使用精灵类来代替。或者是节点的子类并且重写“draw”.

 */

class CC_DLL Node : public Ref
{
public:
    /// 默认的标记用于所有的节点
    static const int INVALID_TAG = -1;

    /// @{
    /// @命名 构造函数，析构函数和一些初始化

    /**
     * 分配并且初始化一个节点.
     * @返回 一个初始化的节点，该节点被标记为“autorelease”(自动释放).
     */
    static Node * create(void);

    /**
     * 得到描述性的字符串。这将会使得调试更加简单。
     * @返回 一个字符串
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

    /// @} 初始化的结束



    /// @{
    /// @命名 图形属性的设值函数和得值函数

    /**
     LocalZOrder是“key”(关键)来分辨节点和它兄弟节点的相关性。

     父节点将会通过LocalZOrder的值来分辨所有的子节点。
     如果两个节点有同样的LocalZOrder,那么先加入子节点数组的节点将会显示在后加入的节点的前面。
     
     同样的，场景图使用“In-Order（按顺序）”遍历数算法来遍历 ( http://en.wikipedia.org/wiki/Tree_traversal#In-order )
     并且拥有小于0的LocalZOrder的值的节点是“left”子树（左子树）
     所以拥有大于0的LocalZOrder的值得节点是“right”子树（右子树）
     
     @见 `setGlobalZOrder`
     @见 `setVertexZ`
     */
    virtual void setLocalZOrder(int localZOrder);

    CC_DEPRECATED_ATTRIBUTE virtual void setZOrder(int localZOrder) { setLocalZOrder(localZOrder); }
    /* `setLocalZOrder`使用的辅助函数。不要使用它除非你知道你在干什么。 
     */
    virtual void _setLocalZOrder(int z);
    /**
     * 得到这个节点的局部Z顺序
     *
     * @见 `setLocalZOrder(int)`
     *
     * @返回 局部Z顺序(相对于兄弟节点)。
     */
    virtual int getLocalZOrder() const { return _localZOrder; }
    CC_DEPRECATED_ATTRIBUTE virtual int getZOrder() const { return getLocalZOrder(); }

    /**
     定义渲染节点的顺序
     拥有全局Z顺序越小的节点，最先渲染
     
     假设两个或者更多的节点拥有相同的全局Z顺序，那么渲染顺序无法保证。
     唯一的例外是如果节点的全局Z顺序为零，那么场景图顺序是可以使用的。 
     
     默认的，所有的节点全局Z顺序都是零。这就是说，默认使用场景图顺序来渲染节点。
     
     全局Z顺序是非常有用的当你需要渲染节点按照不同的顺序而不是场景图顺序。
     
     局限性: 全局Z顺序不能够被拥有继承“SpriteBatchNode”的节点使用。
     并且如果“ClippingNode”是其中之一的上代，那么“global Z order” 将会和“ClippingNode”有关。
     
     @见 `setLocalZOrder()`
     @见 `setVertexZ()`

     @自从 v3.0
     */
    virtual void setGlobalZOrder(float globalZOrder);
    /**
     * 返回节点的全局Z顺序。
     *
     * @见 `setGlobalZOrder(int)`
     *
     * @返回 节点的全局Z顺序
     */
    virtual float getGlobalZOrder() const { return _globalZOrder; }

    /**
     * 设置节点的缩放（x）。
     *
     * 它是一个缩放因子，将会乘以节点的宽以及它的子节点。
     *
     * @参数 scaleX   X轴的缩放因子.
     */
    virtual void setScaleX(float scaleX);
    /**
     * 返回该节点的X轴的缩放因子。
     *
     * @见 setScaleX(float)。
     *
     * @返回 X轴的缩放因子。
     */
    virtual float getScaleX() const;


    /**
     * 设置节点的缩放（y）。
     *
     * 它是一个缩放因子，将会乘以节点的宽以及它的子节点。
     *
     * @参数 scaleY   Y轴的缩放因子
     */
    virtual void setScaleY(float scaleY);
    /**
     * 返回该节点的Y轴的缩放因子。
     *
     * @见 `setScaleY(float)`
     *
     * @返回 Y轴的缩放因子
     */
    virtual float getScaleY() const;

    /**
     * 改变该节点的Z轴的缩放因子。
     *
     * 如果你之前没有改变过它，那么它的默认值是1.0。
     *
     * @参数 scaleY   Z轴的缩放因子
     */
    virtual void setScaleZ(float scaleZ);
    /**
     * 返回该节点的梓州的缩放因子。
     *
     * @见 `setScaleZ(float)`
     *
     * @返回 Z轴的缩放因子。
     */
    virtual float getScaleZ() const;


    /**
     * 设置几点的缩放（x,y,z）.
     *
     * 缩放因子将会乘以该节点和它子节点的宽，高和深度。
     *
     * @参数 scale    X轴和Y轴的缩放因子
     */
    virtual void setScale(float scale);
    /**
     * 得到该节点的缩放因子，当X轴和Y轴有相同的缩放因子时。
     *
     * @警告 判断 当 `_scaleX != _scaleY`
     * @见 setScale(float)
     *
     * @返回 该节点的缩放因子
     */
    virtual float getScale() const;

     /**
     * 设置节点的缩放（x,y）.
     *
     * 缩放因子乘以该节点和它子节点的宽与高。
     *
     * @参数 scaleX     X轴的缩放因子。
     * @参数 scaleY     Y轴的缩放因子。
     */
    virtual void setScale(float scaleX, float scaleY);

    /**
     * 设置节点的位置在父节点的坐标系系统中。
     *
     * 通常我们使用`Vec2(x,y)` 来组成 Vec2 对象。
     * 这一段代码设置节点在屏幕中间。
     @代码
     Size size = Director::getInstance()->getWinSize();
     node->setPosition( Vec2(size.width/2, size.height/2) )
     @代码结束
     *
     * @参数 position  这个节点的位置（x,y）在OpenGL坐标系中。
     */
    virtual void setPosition(const Vec2 &position);
    /**
     * 得到在父节点坐标系中节点的位置（x,y）。
     *
     * @见 setPosition(const Vec2&)
     *
     * @返回 节点在OpenGL坐标系中的位置（x,y)。
     * @代码
     * In js and lua return value is table which contains x,y
     * @代码结束
     */
    virtual const Vec2& getPosition() const;
    /**
     * 设置节点在它父节点坐标系中的位置（x,y）。
     *
     * 传递两个数字（x,y）比传递Vec2对象更有效率。
     * 这个方法要在Lua和JavaScript下。
     * 从Lua到C++传递一个数字比传递一个对象快10倍。
     *
     @代码
     // sample code in Lua
     local pos  = node::getPosition()  -- returns Vec2 object from C++
     node:setPosition(x, y)            -- pass x, y coordinate to C++
     @代码结束
     *
     * @参数 x     位置的X轴坐标系
     * @参数 y     位置的Y轴坐标系
     */
    virtual void setPosition(float x, float y);
    /**
     * 用一个更有效率的方法设置位置，返回两个数字而不是Vec2对象。
     *
     * @见 `setPosition(float, float)`
     * In js,out value not return
     */
    virtual void getPosition(float* x, float* y) const;
    /**
     * 分别得到或者设置位置的X或者Y轴坐标系
     * 这些方法被绑定使用在在Lua和JavaScript。
     */
    virtual void  setPositionX(float x);
    virtual float getPositionX(void) const;
    virtual void  setPositionY(float y);
    virtual float getPositionY(void) const;

    /**
     * 设置在父节点坐标系中的位置（x,y,z）。
     */
    virtual void setPosition3D(const Vec3& position);
    /**
     * 返回父坐标系的位置（X,Y,Z）。
     */
    virtual Vec3 getPosition3D() const;

    /**
     * 设置位置的“z”轴坐标系，是OpneGL Z 定点值。
     *
     * OpenGL深度缓存和深度测试默认值是关闭的，你需要打开它们
     * 来正确的使用这个属性。
     *
     * `setPositionZ()` 同样设置 `setGlobalZValue()` 用“positionZ” 作为值。
     *
     * @见 `setGlobalZValue()`
     *
     * @参数 vertexZ  该节点的penGL Z 定点。
     */
    virtual void setPositionZ(float positionZ);
    CC_DEPRECATED_ATTRIBUTE virtual void setVertexZ(float vertexZ) { setPositionZ(vertexZ); }

    /**
     * 得到该节点的Z轴坐标系的位置。
     *
     * @见 setPositionZ(float)
     *
     * @返回 该节点的Z轴坐标系。
     */
    virtual float getPositionZ() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getVertexZ() const { return getPositionZ(); }

    /**
     * 改变该节点X轴的倾斜角，单位是度。
     *
     * `setRotationalSkew()`和 `setSkew()` 的不同时是前一个模拟Flash的倾斜功能。
     * 然而后一个使用真正的倾斜功能。
     *
     * 这个角度描述了在X轴方向的切形变（shear distortion）。
     * 因此，这个角度在Y轴和图形左边之间。
     * 默认值skewX角度是0，负值使该节点按顺时针变形。
     *
     * @参数 skewX 该节点的X轴的倾斜角。
     */
    virtual void setSkewX(float skewX);
    /**
     * 返回该节点的X轴倾斜角，单位是度。
     *
     * @见 `setSkewX(float)`
     *
     * @返回 该节点的X轴倾斜角。
     */
    virtual float getSkewX() const;


    /**
     * 改变该节点Y轴的倾斜角，单位是度。
     *
     * `setRotationalSkew()`和 `setSkew()` 的不同时是前一个模拟Flash的倾斜功能。
     * while the second one uses the real skew function.
     *
     * This angle describes the shear distortion in the Y direction.
     * Thus, it is the angle between the X coordinate and the bottom edge of the shape
     * The default skewY angle is 0. Positive values distort the node in a CCW direction.
     *
     * @param skewY    The Y skew angle of the node in degrees.
     */
    virtual void setSkewY(float skewY);
    /**
     * Returns the Y skew angle of the node in degrees.
     *
     * @see `setSkewY(float)`
     *
     * @return The Y skew angle of the node in degrees.
     */
    virtual float getSkewY() const;


    /**
     * Sets the anchor point in percent.
     *
     * anchorPoint is the point around which all transformations and positioning manipulations take place.
     * It's like a pin in the node where it is "attached" to its parent.
     * The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the top-right corner.
     * But you can use values higher than (1,1) and lower than (0,0) too.
     * The default anchorPoint is (0.5,0.5), so it starts in the center of the node.
     * @note If node has a physics body, the anchor must be in the middle, you cann't change this to other value.
     *
     * @param anchorPoint   The anchor point of node.
     */
    virtual void setAnchorPoint(const Vec2& anchorPoint);
    /**
     * Returns the anchor point in percent.
     *
     * @see `setAnchorPoint(const Vec2&)`
     *
     * @return The anchor point of node.
     */
    virtual const Vec2& getAnchorPoint() const;
    /**
     * Returns the anchorPoint in absolute pixels.
     *
     * @warning You can only read it. If you wish to modify it, use anchorPoint instead.
     * @see `getAnchorPoint()`
     *
     * @return The anchor point in absolute pixels.
     */
    virtual const Vec2& getAnchorPointInPoints() const;


    /**
     * Sets the untransformed size of the node.
     *
     * The contentSize remains the same no matter the node is scaled or rotated.
     * All nodes has a size. Layer and Scene has the same size of the screen.
     *
     * @param contentSize   The untransformed size of the node.
     */
    virtual void setContentSize(const Size& contentSize);
    /**
     * Returns the untransformed size of the node.
     *
     * @see `setContentSize(const Size&)`
     *
     * @return The untransformed size of the node.
     */
    virtual const Size& getContentSize() const;


    /**
     * Sets whether the node is visible
     *
     * The default value is true, a node is default to visible
     *
     * @param visible   true if the node is visible, false if the node is hidden.
     */
    virtual void setVisible(bool visible);
    /**
     * Determines if the node is visible
     *
     * @see `setVisible(bool)`
     *
     * @return true if the node is visible, false if the node is hidden.
     */
    virtual bool isVisible() const;


    /**
     * Sets the rotation (angle) of the node in degrees.
     *
     * 0 is the default rotation angle.
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     *
     * @param rotation     The rotation of the node in degrees.
     */
    virtual void setRotation(float rotation);
    /**
     * Returns the rotation of the node in degrees.
     *
     * @see `setRotation(float)`
     *
     * @return The rotation of the node in degrees.
     */
    virtual float getRotation() const;

    /**
     * Sets the rotation (X,Y,Z) in degrees.
     * Useful for 3d rotations
     */
    virtual void setRotation3D(const Vec3& rotation);
    /**
     * returns the rotation (X,Y,Z) in degrees.
     */
    virtual Vec3 getRotation3D() const;

    /**
     * Sets the X rotation (angle) of the node in degrees which performs a horizontal rotational skew.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality
     * while the second one uses the real skew function.
     *
     * 0 is the default rotation angle.
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     *
     * @param rotationX    The X rotation in degrees which performs a horizontal rotational skew.
     */
    virtual void setRotationSkewX(float rotationX);
    CC_DEPRECATED_ATTRIBUTE virtual void setRotationX(float rotationX) { return setRotationSkewX(rotationX); }

    /**
     * Gets the X rotation (angle) of the node in degrees which performs a horizontal rotation skew.
     *
     * @see `setRotationSkewX(float)`
     *
     * @return The X rotation in degrees.
     */
    virtual float getRotationSkewX() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getRotationX() const { return getRotationSkewX(); }

    /**
     * Sets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality
     * while the second one uses the real skew function.
     *
     * 0 is the default rotation angle.
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     *
     * @param rotationY    The Y rotation in degrees.
     */
    virtual void setRotationSkewY(float rotationY);
    CC_DEPRECATED_ATTRIBUTE virtual void setRotationY(float rotationY) { return setRotationSkewY(rotationY); }

    /**
     * Gets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
     *
     * @see `setRotationSkewY(float)`
     *
     * @return The Y rotation in degrees.
     */
    virtual float getRotationSkewY() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getRotationY() const { return getRotationSkewY(); }

    /**
     * Sets the arrival order when this node has a same ZOrder with other children.
     *
     * A node which called addChild subsequently will take a larger arrival order,
     * If two children have the same Z order, the child with larger arrival order will be drawn later.
     *
     * @warning This method is used internally for localZOrder sorting, don't change this manually
     *
     * @param orderOfArrival   The arrival order.
     */
    void setOrderOfArrival(int orderOfArrival);
    /**
     * Returns the arrival order, indicates which children is added previously.
     *
     * @see `setOrderOfArrival(unsigned int)`
     *
     * @return The arrival order.
     */
    int getOrderOfArrival() const;


    /** @deprecated No longer needed
    * @js NA
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE void setGLServerState(int serverState) { /* ignore */ };
    /** @deprecated No longer needed
    * @js NA
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE int getGLServerState() const { return 0; }

    /**
     * Sets whether the anchor point will be (0,0) when you position this node.
     *
     * This is an internal method, only used by Layer and Scene. Don't call it outside framework.
     * The default value is false, while in Layer and Scene are true
     *
     * @param ignore    true if anchor point will be (0,0) when you position this node
     * @todo This method should be renamed as setIgnoreAnchorPointForPosition(bool) or something with "set"
     */
    virtual void ignoreAnchorPointForPosition(bool ignore);
    /**
     * Gets whether the anchor point will be (0,0) when you position this node.
     *
     * @see `ignoreAnchorPointForPosition(bool)`
     *
     * @return true if the anchor point will be (0,0) when you position this node.
     */
    virtual bool isIgnoreAnchorPointForPosition() const;

    /// @}  end of Setters & Getters for Graphic Properties


    /// @{
    /// @name Children and Parent

    /**
     * Adds a child to the container with z-order as 0.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child A child node
     */
    virtual void addChild(Node * child);
    /**
     * Adds a child to the container with a local z-order
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     */
    virtual void addChild(Node * child, int localZOrder);
    /**
     * Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to `setLocalZOrder(int)`
     * @param tag       An integer to identify the node easily. Please refer to `setTag(int)`
     */
    virtual void addChild(Node* child, int localZOrder, int tag);
    /**
     * Gets a child from the container with its tag
     *
     * @param tag   An identifier to find the child node.
     *
     * @return a Node object whose tag equals to the input parameter
     */
    virtual Node * getChildByTag(int tag);
    /**
     * Returns the array of the node's children
     *
     * @return the array the node's children
     */
    virtual Vector<Node*>& getChildren() { return _children; }
    virtual const Vector<Node*>& getChildren() const { return _children; }
    
    /** 
     * Returns the amount of children
     *
     * @return The amount of children.
     */
    virtual ssize_t getChildrenCount() const;

    /**
     * Sets the parent node
     *
     * @param parent    A pointer to the parent node
     */
    virtual void setParent(Node* parent);
    /**
     * Returns a pointer to the parent node
     *
     * @see `setParent(Node*)`
     *
     * @returns A pointer to the parent node
     */
    virtual Node* getParent() { return _parent; }
    virtual const Node* getParent() const { return _parent; }


    ////// REMOVES //////

    /**
     * Removes this node itself from its parent node with a cleanup.
     * If the node orphan, then nothing happens.
     * @see `removeFromParentAndCleanup(bool)`
     */
    virtual void removeFromParent();
    /**
     * Removes this node itself from its parent node.
     * If the node orphan, then nothing happens.
     * @param cleanup   true if all actions and callbacks on this node should be removed, false otherwise.
     * @js removeFromParent
     * @lua removeFromParent
     */
    virtual void removeFromParentAndCleanup(bool cleanup);

    /**
     * Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
     *
     * @param child     The child node which will be removed.
     * @param cleanup   true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     */
    virtual void removeChild(Node* child, bool cleanup = true);

    /**
     * Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter
     *
     * @param tag       An interger number that identifies a child node
     * @param cleanup   true if all running actions and callbacks on the child node will be cleanup, false otherwise.
     */
    virtual void removeChildByTag(int tag, bool cleanup = true);
    /**
     * Removes all children from the container with a cleanup.
     *
     * @see `removeAllChildrenWithCleanup(bool)`
     */
    virtual void removeAllChildren();
    /**
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @param cleanup   true if all running actions on all children nodes should be cleanup, false oterwise.
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup);

    /**
     * Reorders a child according to a new z value.
     *
     * @param child     An already added child node. It MUST be already added.
     * @param localZOrder Z order for drawing priority. Please refer to setLocalZOrder(int)
     */
    virtual void reorderChild(Node * child, int localZOrder);

    /**
     * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This appraoch can improves the performance massively.
     * @note Don't call this manually unless a child added needs to be removed in the same frame
     */
    virtual void sortAllChildren();

    /// @} end of Children and Parent
    
    /// @{
    /// @name Tag & User data

    /**
     * Returns a tag that is used to identify the node easily.
     *
     * @return An integer that identifies the node.
     */
    virtual int getTag() const;
    /**
     * Changes the tag that is used to identify the node easily.
     *
     * Please refer to getTag for the sample code.
     *
     * @param tag   A integer that identifies the node.
     */
    virtual void setTag(int tag);

    
    /**
     * Returns a custom user data pointer
     *
     * You can set everything in UserData pointer, a data block, a structure or an object.
     *
     * @return A custom user data pointer
     * @js NA
     * @lua NA
     */
    virtual void* getUserData() { return _userData; }
    /**
    * @js NA
    * @lua NA
    */
    virtual const void* getUserData() const { return _userData; }

    /**
     * Sets a custom user data pointer
     *
     * You can set everything in UserData pointer, a data block, a structure or an object, etc.
     * @warning Don't forget to release the memory manually,
     *          especially before you change this data pointer, and before this node is autoreleased.
     *
     * @param userData  A custom user data pointer
     * @js NA
     * @lua NA
     */
    virtual void setUserData(void *userData);

    /**
     * Returns a user assigned Object
     *
     * Similar to userData, but instead of holding a void* it holds an object
     *
     * @return A user assigned Object
     * @js NA
     * @lua NA
     */
    virtual Ref* getUserObject() { return _userObject; }
    /**
    * @js NA
    * @lua NA
    */
    virtual const Ref* getUserObject() const { return _userObject; }

    /**
     * Returns a user assigned Object
     *
     * Similar to UserData, but instead of holding a void* it holds an object.
     * The UserObject will be retained once in this method,
     * and the previous UserObject (if existed) will be released.
     * The UserObject will be released in Node's destructor.
     *
     * @param userObject    A user assigned Object
     */
    virtual void setUserObject(Ref *userObject);

    /// @} end of Tag & User Data


    /// @{
    /// @name GLProgram
    /**
     * Return the GLProgram (shader) currently used for this node
     *
     * @return The GLProgram (shader) currently used for this node
     */
    GLProgram* getGLProgram();
    CC_DEPRECATED_ATTRIBUTE GLProgram* getShaderProgram() { return getGLProgram(); }

    GLProgramState *getGLProgramState();
    void setGLProgramState(GLProgramState *glProgramState);

    /**
     * Sets the shader program for this node
     *
     * Since v2.0, each rendering node must set its shader program.
     * It should be set in initialize phase.
     @code
     node->setGLrProgram(GLProgramCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
     @endcode
     *
     * @param shaderProgram The shader program
     */
    void setGLProgram(GLProgram *glprogram);
    CC_DEPRECATED_ATTRIBUTE void setShaderProgram(GLProgram *glprogram) { setGLProgram(glprogram); }
    /// @} end of Shader Program


    /**
     * Returns whether or not the node is "running".
     *
     * If the node is running it will accept event callbacks like onEnter(), onExit(), update()
     *
     * @return Whether or not the node is running.
     */
    virtual bool isRunning() const;

    /**
     * Schedules for lua script.
     * @js NA
     */
    void scheduleUpdateWithPriorityLua(int handler, int priority);

    /// @}  end Script Bindings


    /// @{
    /// @name Event Callbacks

    /**
     * Event callback that is invoked every time when Node enters the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition starts.
     * During onEnter you can't access a "sister/brother" node.
     * If you override onEnter, you shall call its parent's one, e.g., Node::onEnter().
     * @js NA
     * @lua NA
     */
    virtual void onEnter();

    /** Event callback that is invoked when the Node enters in the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition finishes.
     * If you override onEnterTransitionDidFinish, you shall call its parent's one, e.g. Node::onEnterTransitionDidFinish()
     * @js NA
     * @lua NA
     */
    virtual void onEnterTransitionDidFinish();

    /**
     * Event callback that is invoked every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
     * @js NA
     * @lua NA
     */
    virtual void onExit();

    /**
     * Event callback that is called every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this callback is called when the transition starts.
     * @js NA
     * @lua NA
     */
    virtual void onExitTransitionDidStart();

    /// @} end of event callbacks.


    /**
     * Stops all running actions and schedulers
     */
    virtual void cleanup();

    /**
     * Override this method to draw your own node.
     * The following GL states will be enabled by default:
     * - `glEnableClientState(GL_VERTEX_ARRAY);`
     * - `glEnableClientState(GL_COLOR_ARRAY);`
     * - `glEnableClientState(GL_TEXTURE_COORD_ARRAY);`
     * - `glEnable(GL_TEXTURE_2D);`
     * AND YOU SHOULD NOT DISABLE THEM AFTER DRAWING YOUR NODE
     * But if you enable any other GL state, you should disable it after drawing your node.
     */
    virtual void draw(Renderer *renderer, const Mat4& transform, bool transformUpdated);
    virtual void draw() final;

    /**
     * Visits this node's children and draw them recursively.
     */
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated);
    virtual void visit() final;


    /** Returns the Scene that contains the Node.
     It returns `nullptr` if the node doesn't belong to any Scene.
     This function recursively calls parent->getScene() until parent is a Scene object. The results are not cached. It is that the user caches the results in case this functions is being used inside a loop.
     */
    virtual Scene* getScene();

    /**
     * Returns an AABB (axis-aligned bounding-box) in its parent's coordinate system.
     *
     * @return An AABB (axis-aligned bounding-box) in its parent's coordinate system
     */
    virtual Rect getBoundingBox() const;

    /** @deprecated Use getBoundingBox instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual Rect boundingBox() const { return getBoundingBox(); }

    virtual void setEventDispatcher(EventDispatcher* dispatcher);
    virtual EventDispatcher* getEventDispatcher() const { return _eventDispatcher; };

    /// @{
    /// @name Actions

    /**
     * Sets the ActionManager object that is used by all actions.
     *
     * @warning If you set a new ActionManager, then previously created actions will be removed.
     *
     * @param actionManager     A ActionManager object that is used by all actions.
     */
    virtual void setActionManager(ActionManager* actionManager);
    /**
     * Gets the ActionManager object that is used by all actions.
     * @see setActionManager(ActionManager*)
     * @return A ActionManager object.
     */
    virtual ActionManager* getActionManager() { return _actionManager; }
    virtual const ActionManager* getActionManager() const { return _actionManager; }

    /**
     * Executes an action, and returns the action that is executed.
     *
     * This node becomes the action's target. Refer to Action::getTarget()
     * @warning Actions don't retain their target.
     *
     * @return An Action pointer
     */
    Action* runAction(Action* action);

    /**
     * Stops and removes all actions from the running action list .
     */
    void stopAllActions();

    /**
     * Stops and removes an action from the running action list.
     *
     * @param action    The action object to be removed.
     */
    void stopAction(Action* action);

    /**
     * Removes an action from the running action list by its tag.
     *
     * @param tag   A tag that indicates the action to be removed.
     */
    void stopActionByTag(int tag);

    /**
     * Gets an action from the running action list by its tag.
     *
     * @see `setTag(int)`, `getTag()`.
     *
     * @return The action object with the given tag.
     */
    Action* getActionByTag(int tag);

    /**
     * Returns the numbers of actions that are running plus the ones that are schedule to run (actions in actionsToAdd and actions arrays).
     *
     * Composable actions are counted as 1 action. Example:
     *    If you are running 1 Sequence of 7 actions, it will return 1.
     *    If you are running 7 Sequences of 2 actions, it will return 7.
     * @todo Rename to getNumberOfRunningActions()
     *
     * @return The number of actions that are running plus the ones that are schedule to run
     */
    ssize_t getNumberOfRunningActions() const;

    /** @deprecated Use getNumberOfRunningActions() instead */
    CC_DEPRECATED_ATTRIBUTE ssize_t numberOfRunningActions() const { return getNumberOfRunningActions(); };

    /// @} end of Actions


    /// @{
    /// @name Scheduler and Timer

    /**
     * Sets a Scheduler object that is used to schedule all "updates" and timers.
     *
     * @warning If you set a new Scheduler, then previously created timers/update are going to be removed.
     * @param scheduler     A Shdeduler object that is used to schedule all "update" and timers.
     */
    virtual void setScheduler(Scheduler* scheduler);
    /**
     * Gets a Sheduler object.
     *
     * @see setScheduler(Scheduler*)
     * @return A Scheduler object.
     */
    virtual Scheduler* getScheduler() { return _scheduler; }
    virtual const Scheduler* getScheduler() const { return _scheduler; }


    /**
     * Checks whether a selector is scheduled.
     *
     * @param selector      A function selector
     * @return Whether the funcion selector is scheduled.
     * @js NA
     * @lua NA
     */
    bool isScheduled(SEL_SCHEDULE selector);

    /**
     * Schedules the "update" method.
     *
     * It will use the order number 0. This method will be called every frame.
     * Scheduled methods with a lower order value will be called before the ones that have a higher order value.
     * Only one "update" method could be scheduled per node.
     * @js NA
     * @lua NA
     */
    void scheduleUpdate(void);

    /**
     * Schedules the "update" method with a custom priority.
     *
     * This selector will be called every frame.
     * Scheduled methods with a lower priority will be called before the ones that have a higher value.
     * Only one "update" selector could be scheduled per node (You can't have 2 'update' selectors).
     * @js NA
     * @lua NA
     */
    void scheduleUpdateWithPriority(int priority);

    /*
     * Unschedules the "update" method.
     * @see scheduleUpdate();
     */
    void unscheduleUpdate(void);

    /**
     * Schedules a custom selector.
     *
     * If the selector is already scheduled, then the interval parameter will be updated without scheduling it again.
     @code
     // firstly, implement a schedule function
     void MyNode::TickMe(float dt);
     // wrap this function into a selector via schedule_selector marco.
     this->schedule(schedule_selector(MyNode::TickMe), 0, 0, 0);
     @endcode
     *
     * @param selector  The SEL_SCHEDULE selector to be scheduled.
     * @param interval  Tick interval in seconds. 0 means tick every frame. If interval = 0, it's recommended to use scheduleUpdate() instead.
     * @param repeat    The selector will be excuted (repeat + 1) times, you can use kRepeatForever for tick infinitely.
     * @param delay     The amount of time that the first tick will wait before execution.
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);

    /**
     * Schedules a custom selector with an interval time in seconds.
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector      The SEL_SCHEDULE selector to be scheduled.
     * @param interval      Callback interval time in seconds. 0 means tick every frame,
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector, float interval);

    /**
     * Schedules a selector that runs only once, with a delay of 0 or larger
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector      The SEL_SCHEDULE selector to be scheduled.
     * @param delay         The amount of time that the first tick will wait before execution.
     * @lua NA
     */
    void scheduleOnce(SEL_SCHEDULE selector, float delay);

    /**
     * Schedules a custom selector, the scheduled selector will be ticked every frame
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      A function wrapped as a selector
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector);

    /**
     * Unschedules a custom selector.
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector      A function wrapped as a selector
     * @lua NA
     */
    void unschedule(SEL_SCHEDULE selector);

    /**
     * Unschedule all scheduled selectors: custom selectors, and the 'update' selector.
     * Actions are not affected by this method.
     * @lua NA
     */
    void unscheduleAllSelectors(void);

    /**
     * Resumes all scheduled selectors, actions and event listeners.
     * This method is called internally by onEnter
     */
    void resume(void);
    /**
     * Pauses all scheduled selectors, actions and event listeners..
     * This method is called internally by onExit
     */
    void pause(void);

    /**
     * Resumes all scheduled selectors, actions and event listeners.
     * This method is called internally by onEnter
     */
    CC_DEPRECATED_ATTRIBUTE void resumeSchedulerAndActions(void);
    /**
     * Pauses all scheduled selectors, actions and event listeners..
     * This method is called internally by onExit
     */
    CC_DEPRECATED_ATTRIBUTE void pauseSchedulerAndActions(void);

    /*
     * Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live"
     */
    virtual void update(float delta);

    /// @} end of Scheduler and Timer

    /// @{
    /// @name Transformations

    /**
     * Calls children's updateTransform() method recursively.
     *
     * This method is moved from Sprite, so it's no longer specific to Sprite.
     * As the result, you apply SpriteBatchNode's optimization on your customed Node.
     * e.g., `batchNode->addChild(myCustomNode)`, while you can only addChild(sprite) before.
     */
    virtual void updateTransform();

    /**
     * Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     */
    virtual const Mat4& getNodeToParentTransform() const;
    virtual AffineTransform getNodeToParentAffineTransform() const;

    /** 
     * Sets the Transformation matrix manually.
     */
    virtual void setNodeToParentTransform(const Mat4& transform);

    /** @deprecated use getNodeToParentTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToParentTransform() const { return getNodeToParentAffineTransform(); }

    /**
     * Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
     * The matrix is in Pixels.
     */
    virtual const Mat4& getParentToNodeTransform() const;
    virtual AffineTransform getParentToNodeAffineTransform() const;

    /** @deprecated Use getParentToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform parentToNodeTransform() const { return getParentToNodeAffineTransform(); }

    /**
     * Returns the world affine transform matrix. The matrix is in Pixels.
     */
    virtual Mat4 getNodeToWorldTransform() const;
    virtual AffineTransform getNodeToWorldAffineTransform() const;

    /** @deprecated Use getNodeToWorldTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToWorldTransform() const { return getNodeToWorldAffineTransform(); }

    /**
     * Returns the inverse world affine transform matrix. The matrix is in Pixels.
     */
    virtual Mat4 getWorldToNodeTransform() const;
    virtual AffineTransform getWorldToNodeAffineTransform() const;


    /** @deprecated Use getWorldToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform worldToNodeTransform() const { return getWorldToNodeAffineTransform(); }

    /// @} end of Transformations


    /// @{
    /// @name Coordinate Converters

    /**
     * Converts a Vec2 to node (local) space coordinates. The result is in Points.
     */
    Vec2 convertToNodeSpace(const Vec2& worldPoint) const;

    /**
     * Converts a Vec2 to world space coordinates. The result is in Points.
     */
    Vec2 convertToWorldSpace(const Vec2& nodePoint) const;

    /**
     * Converts a Vec2 to node (local) space coordinates. The result is in Points.
     * treating the returned/received node point as anchor relative.
     */
    Vec2 convertToNodeSpaceAR(const Vec2& worldPoint) const;

    /**
     * Converts a local Vec2 to world space coordinates.The result is in Points.
     * treating the returned/received node point as anchor relative.
     */
    Vec2 convertToWorldSpaceAR(const Vec2& nodePoint) const;

    /**
     * convenience methods which take a Touch instead of Vec2
     */
    Vec2 convertTouchToNodeSpace(Touch * touch) const;

    /**
     * converts a Touch (world coordinates) into a local coordinate. This method is AR (Anchor Relative).
     */
    Vec2 convertTouchToNodeSpaceAR(Touch * touch) const;

	/**
     *  Sets an additional transform matrix to the node.
     *
     *  In order to remove it, call it again with the argument `nullptr`
     *
     *  @note The additional transform will be concatenated at the end of getNodeToParentTransform.
     *        It could be used to simulate `parent-child` relationship between two nodes (e.g. one is in BatchNode, another isn't).
     */
    void setAdditionalTransform(Mat4* additionalTransform);
    void setAdditionalTransform(const AffineTransform& additionalTransform);

    /// @} end of Coordinate Converters

      /// @{
    /// @name component functions
    /**
     *   gets a component by its name
     */
    Component* getComponent(const std::string& pName);

    /**
     *   adds a component
     */
    virtual bool addComponent(Component *pComponent);

    /**
     *   removes a component by its name
     */
    virtual bool removeComponent(const std::string& pName);

    /**
     *   removes all components
     */
    virtual void removeAllComponents();
    /// @} end of component functions


#if CC_USE_PHYSICS
    /**
     *   set the PhysicsBody that let the sprite effect with physics
     * @note This method will set anchor point to Vec2::ANCHOR_MIDDLE if body not null, and you cann't change anchor point if node has a physics body.
     */
    void setPhysicsBody(PhysicsBody* body);

    /**
     *   get the PhysicsBody the sprite have
     */
    PhysicsBody* getPhysicsBody() const;

#endif
    
    // overrides
    virtual GLubyte getOpacity() const;
    virtual GLubyte getDisplayedOpacity() const;
    virtual void setOpacity(GLubyte opacity);
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    virtual bool isCascadeOpacityEnabled() const;
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    
    virtual const Color3B& getColor(void) const;
    virtual const Color3B& getDisplayedColor() const;
    virtual void setColor(const Color3B& color);
    virtual void updateDisplayedColor(const Color3B& parentColor);
    virtual bool isCascadeColorEnabled() const;
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);
    
    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB() const { return false; };
    
CC_CONSTRUCTOR_ACCESS:
    // Nodes should be created using create();
    Node();
    virtual ~Node();

    virtual bool init();

protected:
    /// lazy allocs
    void childrenAlloc(void);
    
    /// helper that reorder a child
    void insertChild(Node* child, int z);

    /// Removes a child, call child->onExit(), do cleanup, remove it from children array.
    void detachChild(Node *child, ssize_t index, bool doCleanup);

    /// Convert cocos2d coordinates to UI windows coordinate.
    Vec2 convertToWindowSpace(const Vec2& nodePoint) const;

    Mat4 transform(const Mat4 &parentTransform);

    virtual void updateCascadeOpacity();
    virtual void disableCascadeOpacity();
    virtual void updateCascadeColor();
    virtual void disableCascadeColor();
    virtual void updateColor() {}
    
#if CC_USE_PHYSICS
    virtual void updatePhysicsBodyPosition(Scene* layer);
    virtual void updatePhysicsBodyRotation(Scene* layer);
#endif // CC_USE_PHYSICS

    float _rotationX;               ///< rotation on the X-axis
    float _rotationY;               ///< rotation on the Y-axis

    // rotation Z is decomposed in 2 to simulate Skew for Flash animations
    float _rotationZ_X;             ///< rotation angle on Z-axis, component X
    float _rotationZ_Y;             ///< rotation angle on Z-axis, component Y

    float _scaleX;                  ///< scaling factor on x-axis
    float _scaleY;                  ///< scaling factor on y-axis
    float _scaleZ;                  ///< scaling factor on z-axis

    Vec2 _position;                ///< position of the node
    float _positionZ;               ///< OpenGL real Z position

    float _skewX;                   ///< skew angle on x-axis
    float _skewY;                   ///< skew angle on y-axis

    Vec2 _anchorPointInPoints;     ///< anchor point in points
    Vec2 _anchorPoint;             ///< anchor point normalized (NOT in points)

    Size _contentSize;              ///< untransformed size of the node

    Mat4 _modelViewTransform;    ///< ModelView transform of the Node.

    // "cache" variables are allowed to be mutable
    mutable Mat4 _transform;      ///< transform
    mutable bool _transformDirty;   ///< transform dirty flag
    mutable Mat4 _inverse;        ///< inverse transform
    mutable bool _inverseDirty;     ///< inverse transform dirty flag
    mutable Mat4 _additionalTransform; ///< transform
    bool _useAdditionalTransform;   ///< The flag to check whether the additional transform is dirty
    bool _transformUpdated;         ///< Whether or not the Transform object was updated since the last frame

    int _localZOrder;               ///< Local order (relative to its siblings) used to sort the node
    float _globalZOrder;            ///< Global order used to sort the node

    Vector<Node*> _children;        ///< array of children nodes
    Node *_parent;                  ///< weak reference to parent node

    int _tag;                         ///< a tag. Can be any number you assigned just to identify this node
    
    std::string _name;               ///<a string label, an user defined string to identify this node

    void *_userData;                ///< A user assingned void pointer, Can be point to any cpp object
    Ref *_userObject;               ///< A user assigned Object

    GLProgramState *_glProgramState; ///< OpenGL Program State

    int _orderOfArrival;            ///< used to preserve sequence while sorting children with the same localZOrder

    Scheduler *_scheduler;          ///< scheduler used to schedule timers and updates

    ActionManager *_actionManager;  ///< a pointer to ActionManager singleton, which is used to handle all the actions

    EventDispatcher* _eventDispatcher;  ///< event dispatcher used to dispatch all kinds of events

    bool _running;                  ///< is running

    bool _visible;                  ///< is this node visible

    bool _ignoreAnchorPointForPosition; ///< true if the Anchor Vec2 will be (0,0) when you position the Node, false otherwise.
                                          ///< Used by Layer and Scene.

    bool _reorderChildDirty;          ///< children order dirty flag
    bool _isTransitionFinished;       ///< flag to indicate whether the transition was finished

#if CC_ENABLE_SCRIPT_BINDING
    int _scriptHandler;               ///< script handler for onEnter() & onExit(), used in Javascript binding and Lua binding.
    int _updateScriptHandler;         ///< script handler for update() callback per frame, which is invoked from lua & javascript.
    ccScriptType _scriptType;         ///< type of script binding, lua or javascript
#endif
    
    ComponentContainer *_componentContainer;        ///< Dictionary of components

#if CC_USE_PHYSICS
    PhysicsBody* _physicsBody;        ///< the physicsBody the node have
#endif
    
    // opacity controls
    GLubyte		_displayedOpacity;
    GLubyte     _realOpacity;
    Color3B	    _displayedColor;
    Color3B     _realColor;
    bool		_cascadeColorEnabled;
    bool        _cascadeOpacityEnabled;

    static int s_globalOrderOfArrival;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Node);
    
#if CC_USE_PHYSICS
    friend class Layer;
#endif //CC_USTPS
};

// NodeRGBA

/** NodeRGBA is a subclass of Node that implements the RGBAProtocol protocol.
 
 All features from Node are valid, plus the following new features:
 - opacity
 - RGB colors
 
 Opacity/Color propagates into children that conform to the RGBAProtocol if cascadeOpacity/cascadeColor is enabled.
 @since v2.1
 */
class CC_DLL __NodeRGBA : public Node, public __RGBAProtocol
{
public:
    // overrides
    virtual GLubyte getOpacity() const override { return Node::getOpacity(); }
    virtual GLubyte getDisplayedOpacity() const  override { return Node::getDisplayedOpacity(); }
    virtual void setOpacity(GLubyte opacity) override { return Node::setOpacity(opacity); }
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override { return Node::updateDisplayedOpacity(parentOpacity); }
    virtual bool isCascadeOpacityEnabled() const  override { return Node::isCascadeOpacityEnabled(); }
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) override { return Node::setCascadeOpacityEnabled(cascadeOpacityEnabled); }

    virtual const Color3B& getColor(void) const override { return Node::getColor(); }
    virtual const Color3B& getDisplayedColor() const override { return Node::getDisplayedColor(); }
    virtual void setColor(const Color3B& color) override { return Node::setColor(color); }
    virtual void updateDisplayedColor(const Color3B& parentColor) override { return Node::updateDisplayedColor(parentColor); }
    virtual bool isCascadeColorEnabled() const override { return Node::isCascadeColorEnabled(); }
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) override { return Node::setCascadeColorEnabled(cascadeColorEnabled); }

    virtual void setOpacityModifyRGB(bool bValue) override { return Node::setOpacityModifyRGB(bValue); }
    virtual bool isOpacityModifyRGB() const override { return Node::isOpacityModifyRGB(); }

protected:
    __NodeRGBA();
    virtual ~__NodeRGBA() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__NodeRGBA);
};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCNODE_H__
