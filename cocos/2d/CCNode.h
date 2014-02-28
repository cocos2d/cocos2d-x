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

#include "ccMacros.h"
#include "CCAffineTransform.h"
#include "CCArray.h"
#include "CCGL.h"
#include "ccGLStateCache.h"
#include "CCGLProgram.h"
#include "CCScriptSupport.h"
#include "CCProtocols.h"
#include "CCEventDispatcher.h"
#include "CCVector.h"
#include "kazmath/kazmath.h"

NS_CC_BEGIN

class GridBase;
class Point;
class Touch;
class Action;
class LabelProtocol;
class Scheduler;
class ActionManager;
class Component;
class ComponentContainer;
class EventDispatcher;
class Scene;
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

/** @brief Node is the base element of the Scene Graph. Element of the Scene Graph must be Node objects or subclasses of it.
 The most common Node objects are: Scene, Layer, Sprite, Menu.

 The main features of a Node are:
 - They can contain other Node objects (`addChild`, `getChildByTag`, `removeChild`, etc)
 - They can schedule periodic callback (`schedule`, `unschedule`, etc)
 - They can execute actions (`runAction`, `stopAction`, etc)

 Some Node objects provide extra functionality for them or their children.

 Subclassing a Node usually means (one/all) of:
 - overriding init to initialize resources and schedule callbacks
 - create callbacks to handle the advancement of time
 - overriding draw to render the node

 Properties of Node:
 - position
 - scale (x, y)
 - rotation (in degrees, clockwise)
 - GridBase (to do mesh transformations)
 - anchor point
 - size
 - visible
 - z-order
 - openGL z position

 Default values:
 - rotation: 0
 - position: (x=0,y=0)
 - scale: (x=1,y=1)
 - contentSize: (x=0,y=0)
 - anchorPoint: (x=0,y=0)

 Limitations:
 - A Node is a "invisible" object. If you want to draw something on the screen, you should use a Sprite instead. Or subclass Node and override `draw`.

 Order in transformations with grid disabled
 -# The node will be translated (position)
 -# The node will be rotated (rotation)
 -# The node will be scaled (scale)

 Order in transformations with grid enabled
 -# The node will be translated (position)
 -# The node will be rotated (rotation)
 -# The node will be scaled (scale)
 -# The grid will capture the screen
 -# The grid will render the captured screen

 */

class CC_DLL Node : public Ref
{
public:
    /// Default tag used for all the nodes
    static const int INVALID_TAG = -1;

    /// @{
    /// @name Constructor, Destructor and Initializers

    /**
     * Allocates and initializes a node.
     * @return A initialized node which is marked as "autorelease".
     */
    static Node * create(void);

    /**
     * Gets the description string. It makes debugging easier.
     * @return A string
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

    /// @} end of initializers



    /// @{
    /// @name Setters & Getters for Graphic Peroperties

    /**
     LocalZOrder is the 'key' used to sort the node relative to its siblings.

     The Node's parent will sort all its children based ont the LocalZOrder value.
     If two nodes have the same LocalZOrder, then the node that was added first to the children's array will be in front of the other node in the array.
     
     Also, the Scene Graph is traversed using the "In-Order" tree traversal algorithm ( http://en.wikipedia.org/wiki/Tree_traversal#In-order )
     And Nodes that have LocalZOder values < 0 are the "left" subtree
     While Nodes with LocalZOder >=0 are the "right" subtree.
     
     @see `setGlobalZOrder`
     @see `setVertexZ`
     */
    virtual void setLocalZOrder(int localZOrder);

    CC_DEPRECATED_ATTRIBUTE virtual void setZOrder(int localZOrder) { setLocalZOrder(localZOrder); }
    /* Helper function used by `setLocalZOrder`. Don't use it unless you know what you are doing.
     */
    virtual void _setLocalZOrder(int z);
    /**
     * Gets the local Z order of this node.
     *
     * @see `setLocalZOrder(int)`
     *
     * @return The local (relative to its siblings) Z order.
     */
    virtual int getLocalZOrder() const { return _localZOrder; }
    CC_DEPRECATED_ATTRIBUTE virtual int getZOrder() const { return getLocalZOrder(); }

    /**
     Defines the oder in which the nodes are renderer.
     Nodes that have a Global Z Order lower, are renderer first.
     
     In case two or more nodes have the same Global Z Order, the oder is not guaranteed.
     The only exception if the Nodes have a Global Z Order == 0. In that case, the Scene Graph order is used.
     
     By default, all nodes have a Global Z Order = 0. That means that by default, the Scene Graph order is used to render the nodes.
     
     Global Z Order is useful when you need to render nodes in an order different than the Scene Graph order.
     
     Limitations: Global Z Order can't be used used by Nodes that have SpriteBatchNode as one of their acenstors.
     And if ClippingNode is one of the ancestors, then "global Z order" will be relative to the ClippingNode.

     @see `setLocalZOrder()`
     @see `setVertexZ()`

     @since v3.0
     */
    virtual void setGlobalZOrder(float globalZOrder);
    /**
     * Returns the Node's Global Z Order.
     *
     * @see `setGlobalZOrder(int)`
     *
     * @return The node's global Z order
     */
    virtual float getGlobalZOrder() const { return _globalZOrder; }

    /**
     * Changes the scale factor on X axis of this node
     *
     * The deafult value is 1.0 if you haven't changed it before
     *
     * @param scaleX   The scale factor on X axis.
     */
    virtual void setScaleX(float scaleX);
    /**
     * Returns the scale factor on X axis of this node
     *
     * @see setScaleX(float)
     *
     * @return The scale factor on X axis.
     */
    virtual float getScaleX() const;


    /**
     * Changes the scale factor on Y axis of this node
     *
     * The Default value is 1.0 if you haven't changed it before.
     *
     * @param scaleY   The scale factor on Y axis.
     */
    virtual void setScaleY(float scaleY);
    /**
     * Returns the scale factor on Y axis of this node
     *
     * @see `setScaleY(float)`
     *
     * @return The scale factor on Y axis.
     */
    virtual float getScaleY() const;

    /**
     * Changes the scale factor on Z axis of this node
     *
     * The Default value is 1.0 if you haven't changed it before.
     *
     * @param scaleY   The scale factor on Y axis.
     */
    virtual void setScaleZ(float scaleZ);
    /**
     * Returns the scale factor on Z axis of this node
     *
     * @see `setScaleZ(float)`
     *
     * @return The scale factor on Z axis.
     */
    virtual float getScaleZ() const;


    /**
     * Changes both X and Y scale factor of the node.
     *
     * 1.0 is the default scale factor. It modifies the X and Y scale at the same time.
     *
     * @param scale     The scale factor for both X and Y axis.
     */
    virtual void setScale(float scale);
    /**
     * Gets the scale factor of the node,  when X and Y have the same scale factor.
     *
     * @warning Assert when `_scaleX != _scaleY`
     * @see setScale(float)
     *
     * @return The scale factor of the node.
     */
    virtual float getScale() const;

     /**
     * Changes both X and Y scale factor of the node.
     *
     * 1.0 is the default scale factor. It modifies the X and Y scale at the same time.
     *
     * @param scaleX     The scale factor on X axis.
     * @param scaleY     The scale factor on Y axis.
     */
    virtual void setScale(float scaleX,float scaleY);

    /**
     * Changes the position (x,y) of the node in OpenGL coordinates
     *
     * Usually we use `Point(x,y)` to compose Point object.
     * The original point (0,0) is at the left-bottom corner of screen.
     * For example, this codesnip sets the node in the center of screen.
     @code
     Size size = Director::getInstance()->getWinSize();
     node->setPosition( Point(size.width/2, size.height/2) )
     @endcode
     *
     * @param position  The position (x,y) of the node in OpenGL coordinates
     */
    virtual void setPosition(const Point &position);
    /**
     * Gets the position (x,y) of the node in OpenGL coordinates
     *
     * @see setPosition(const Point&)
     *
     * @return The position (x,y) of the node in OpenGL coordinates
     * @code
     * In js and lua return value is table which contains x,y
     * @endcode
     */
    virtual const Point& getPosition() const;
    /**
     * Sets position in a more efficient way.
     *
     * Passing two numbers (x,y) is much efficient than passing Point object.
     * This method is binded to lua and javascript.
     * Passing a number is 10 times faster than passing a object from lua to c++
     *
     @code
     // sample code in lua
     local pos  = node::getPosition()  -- returns Point object from C++
     node:setPosition(x, y)            -- pass x, y coordinate to C++
     @endcode
     *
     * @param x     X coordinate for position
     * @param y     Y coordinate for position
     */
    virtual void setPosition(float x, float y);
    /**
     * Gets position in a more efficient way, returns two number instead of a Point object
     *
     * @see `setPosition(float, float)`
     * In js,out value not return
     */
    virtual void getPosition(float* x, float* y) const;
    /**
     * Gets/Sets x or y coordinate individually for position.
     * These methods are used in Lua and Javascript Bindings
     */
    virtual void  setPositionX(float x);
    virtual float getPositionX(void) const;
    virtual void  setPositionY(float y);
    virtual float getPositionY(void) const;

    /**
     * Sets the X, Y, and Z axis position
     */
    virtual void setPosition3D(const Vertex3F& position);
    /**
     * returns the X, Y and Z axis position
     */
    virtual Vertex3F getPosition3D() const;

    /**
     * Sets the 'z' axis in the position. It is the OpenGL Z vertex value.
     *
     * The OpenGL depth buffer and depth testing are disabled by default. You need to turn them on
     * in order to use this property correctly.
     *
     * `setPositionZ()` also sets the `setGlobalZValue()` with the positionZ as value.
     *
     * @see `setGlobalZValue()`
     *
     * @param vertexZ  OpenGL Z vertex of this node.
     */
    virtual void setPositionZ(float positionZ);
    CC_DEPRECATED_ATTRIBUTE virtual void setVertexZ(float vertexZ) { setPositionZ(vertexZ); }

    /**
     * Gets position Z axis of this node.
     *
     * @see setPositionZ(float)
     *
     * @return the position Z axis of this node.
     */
    virtual float getPositionZ() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getVertexZ() const { return getPositionZ(); }

    /** Sets the position using normalized coordinates.
     - (0,0) means bottom,left corner
     - (1,1) means top,right corner
     - (0.5,0.5) means center
     */
    virtual void setNormalizedPosition(const Point& position);
    /** returns the normalized position */
    const Point& getNormalizedPosition() const;

    /**
     * Changes the X skew angle of the node in degrees.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality
     * while the second one uses the real skew funciton.
     *
     * This angle describes the shear distortion in the X direction.
     * Thus, it is the angle between the Y axis and the left edge of the shape
     * The default skewX angle is 0. Positive values distort the node in a CW direction.
     *
     * @param skewX The X skew angle of the node in degrees.
     */
    virtual void setSkewX(float skewX);
    /**
     * Returns the X skew angle of the node in degrees.
     *
     * @see `setSkewX(float)`
     *
     * @return The X skew angle of the node in degrees.
     */
    virtual float getSkewX() const;


    /**
     * Changes the Y skew angle of the node in degrees.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality
     * while the second one uses the real skew funciton.
     *
     * This angle describes the shear distortion in the Y direction.
     * Thus, it is the angle between the X axis and the bottom edge of the shape
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
     *
     * @param anchorPoint   The anchor point of node.
     */
    virtual void setAnchorPoint(const Point& anchorPoint);
    /**
     * Returns the anchor point in percent.
     *
     * @see `setAnchorPoint(const Point&)`
     *
     * @return The anchor point of node.
     */
    virtual const Point& getAnchorPoint() const;
    /**
     * Returns the anchorPoint in absolute pixels.
     *
     * @warning You can only read it. If you wish to modify it, use anchorPoint instead.
     * @see `getAnchorPoint()`
     *
     * @return The anchor point in absolute pixels.
     */
    virtual const Point& getAnchorPointInPoints() const;


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
     * Sets the X, Y and Z axis rotation
     * Useful for 3d rotations
     */
    virtual void setRotation3D(const Vertex3F& rotation);
    /**
     * returns the X, Y and Z axis rotation
     */
    virtual Vertex3F getRotation3D() const;

    /**
     * Sets the X rotation (angle) of the node in degrees which performs a horizontal rotational skew.
     *
     * The difference between setRotationalSkew() and setSkew() is that the first one simulate Flash's skew functionality
     * while the second one uses the real skew funciton.
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
     * The difference between setRotationalSkew() and setSkew() is that the first one simulate Flash's skew functionality
     * while the second one uses the real skew funciton.
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
     * Returns the arrival order, indecates which children is added previously.
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
     * @todo This method shoud be renamed as setIgnoreAnchorPointForPosition(bool) or something with "set"
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

    /// @}  end of Setters & Getters for Graphic Peroperties


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
     * @param zOrder    Z order for drawing priority. Please refer to setLocalZOrder(int)
     * @param tag       A interger to identify the node easily. Please refer to setTag(int)
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
     * Return an array of children
     *
     * Composing a "tree" structure is a very important feature of Node
     * Here's a sample code of traversing children array:
     @code
     Node* node = nullptr;
     CCARRAY_FOREACH(parent->getChildren(), node)
     {
        node->setPosition(0,0);
     }
     @endcode
     * This sample code traverses all children nodes, and set their position to (0,0)
     *
     * @return An array of children
     */
    virtual Vector<Node*>& getChildren() { return _children; }
    virtual const Vector<Node*>& getChildren() const { return _children; }
    
    /** 
     * Get the amount of children.
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
     * You can set tags to node then identify them easily.
     @code
     #define TAG_PLAYER  1
     #define TAG_MONSTER 2
     #define TAG_BOSS    3
     // set tags
     node1->setTag(TAG_PLAYER);
     node2->setTag(TAG_MONSTER);
     node3->setTag(TAG_BOSS);
     parent->addChild(node1);
     parent->addChild(node2);
     parent->addChild(node3);
     // identify by tags
     Node* node = nullptr;
     CCARRAY_FOREACH(parent->getChildren(), node)
     {
         switch(node->getTag())
         {
             case TAG_PLAYER:
                 break;
             case TAG_MONSTER:
                 break;
             case TAG_BOSS:
                 break;
         }
     }
     @endcode
     *
     * @return A interger that identifies the node.
     */
    virtual int getTag() const;
    /**
     * Changes the tag that is used to identify the node easily.
     *
     * Please refer to getTag for the sample code.
     *
     * @param tag   A interger that indentifies the node.
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
     * and the previous UserObject (if existed) will be relese.
     * The UserObject will be released in Node's destructure.
     *
     * @param userObject    A user assigned Object
     */
    virtual void setUserObject(Ref *userObject);

    /// @} end of Tag & User Data


    /// @{
    /// @name Shader Program
    /**
     * Return the shader program currently used for this node
     *
     * @return The shader program currelty used for this node
     */
    virtual GLProgram* getShaderProgram() { return _shaderProgram; }
    virtual const GLProgram* getShaderProgram() const { return _shaderProgram; }

    /**
     * Sets the shader program for this node
     *
     * Since v2.0, each rendering node must set its shader program.
     * It should be set in initialize phase.
     @code
     node->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
     @endcode
     *
     * @param shaderProgram The shader program which fetchs from ShaderCache.
     */
    virtual void setShaderProgram(GLProgram *shaderProgram);
    /// @} end of Shader Program


    /**
     * Returns whether or not the node accepts event callbacks.
     *
     * Running means the node accept event callbacks like onEnter(), onExit(), update()
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
    virtual void draw();

    /**
     * Visits this node's children and draw them recursively.
     */
    virtual void visit();

    /** Returns the Scene that contains the Node.
     It returns `nullptr` if the node doesn't belong to any Scene.
     This function recursively calls parent->getScene() until parent is a Scene object. The results are not cached. It is that the user caches the results in case this functions is being used inside a loop.
     */
    virtual Scene* getScene();

    /**
     * Returns a "local" axis aligned bounding box of the node.
     * The returned box is relative only to its parent.
     *
     * @note This method returns a temporaty variable, so it can't returns const Rect&
     * @todo Rename to `getBoundingBox()` in the future versions.
     *
     * @return A "local" axis aligned boudning box of the node.
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
     * Performs OpenGL view-matrix transformation based on position, scale, rotation and other attributes.
     */
    void transform();
    /**
     * Performs OpenGL view-matrix transformation of it's ancestors.
     * Generally the ancestors are already transformed, but in certain cases (eg: attaching a FBO)
     * It's necessary to transform the ancestors again.
     */
    void transformAncestors();
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
    virtual const kmMat4& getNodeToParentTransform() const;
    virtual AffineTransform getNodeToParentAffineTransform() const;

    /** 
     * Sets the Transformation matrix manually.
     */
    virtual void setNodeToParentTransform(const kmMat4& transform);

    /** @deprecated use getNodeToParentTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToParentTransform() const { return getNodeToParentAffineTransform(); }

    /**
     * Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
     * The matrix is in Pixels.
     */
    virtual const kmMat4& getParentToNodeTransform() const;
    virtual AffineTransform getParentToNodeAffineTransform() const;

    /** @deprecated Use getParentToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform parentToNodeTransform() const { return getParentToNodeAffineTransform(); }

    /**
     * Returns the world affine transform matrix. The matrix is in Pixels.
     */
    virtual kmMat4 getNodeToWorldTransform() const;
    virtual AffineTransform getNodeToWorldAffineTransform() const;

    /** @deprecated Use getNodeToWorldTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToWorldTransform() const { return getNodeToWorldAffineTransform(); }

    /**
     * Returns the inverse world affine transform matrix. The matrix is in Pixels.
     */
    virtual kmMat4 getWorldToNodeTransform() const;
    virtual AffineTransform getWorldToNodeAffineTransform() const;


    /** @deprecated Use worldToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform worldToNodeTransform() const { return getWorldToNodeAffineTransform(); }

    /// @} end of Transformations


    /// @{
    /// @name Coordinate Converters

    /**
     * Converts a Point to node (local) space coordinates. The result is in Points.
     */
    Point convertToNodeSpace(const Point& worldPoint) const;

    /**
     * Converts a Point to world space coordinates. The result is in Points.
     */
    Point convertToWorldSpace(const Point& nodePoint) const;

    /**
     * Converts a Point to node (local) space coordinates. The result is in Points.
     * treating the returned/received node point as anchor relative.
     */
    Point convertToNodeSpaceAR(const Point& worldPoint) const;

    /**
     * Converts a local Point to world space coordinates.The result is in Points.
     * treating the returned/received node point as anchor relative.
     */
    Point convertToWorldSpaceAR(const Point& nodePoint) const;

    /**
     * convenience methods which take a Touch instead of Point
     */
    Point convertTouchToNodeSpace(Touch * touch) const;

    /**
     * converts a Touch (world coordinates) into a local coordinate. This method is AR (Anchor Relative).
     */
    Point convertTouchToNodeSpaceAR(Touch * touch) const;

	/**
     *  Sets an additional transform matrix to the node.
     *
     *  In order to remove it, set the Identity Matrix to the additional transform.
     *
     *  @note The additional transform will be concatenated at the end of getNodeToParentTransform.
     *        It could be used to simulate `parent-child` relationship between two nodes (e.g. one is in BatchNode, another isn't).
     @code
     // create a batchNode
     SpriteBatchNode* batch= SpriteBatchNode::create("Icon-114.png");
     this->addChild(batch);

     // create two sprites, spriteA will be added to batchNode, they are using different textures.
     Sprite* spriteA = Sprite::createWithTexture(batch->getTexture());
     Sprite* spriteB = Sprite::create("Icon-72.png");

     batch->addChild(spriteA);

     // We can't make spriteB as spriteA's child since they use different textures. So just add it to layer.
     // But we want to simulate `parent-child` relationship for these two node.
     this->addChild(spriteB);

     //position
     spriteA->setPosition(Point(200, 200));

     // Gets the spriteA's transform.
     auto t = spriteA->getNodeToParentTransform();

     // Sets the additional transform to spriteB, spriteB's postion will based on its pseudo parent i.e. spriteA.
     spriteB->setAdditionalTransform(t);

     //scale
     spriteA->setScale(2);

     // Gets the spriteA's transform.
     t = spriteA->getNodeToParentTransform();

     // Sets the additional transform to spriteB, spriteB's scale will based on its pseudo parent i.e. spriteA.
     spriteB->setAdditionalTransform(t);

     //rotation
     spriteA->setRotation(20);

     // Gets the spriteA's transform.
     t = spriteA->getNodeToParentTransform();

     // Sets the additional transform to spriteB, spriteB's rotation will based on its pseudo parent i.e. spriteA.
     spriteB->setAdditionalTransform(t);
     @endcode
     */
    void setAdditionalTransform(const AffineTransform& additionalTransform);
    void setAdditionalTransform(const kmMat4& additionalTransform);

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

protected:
    // Nodes should be created using create();
    Node();
    virtual ~Node();
    virtual bool init();

    /// lazy allocs
    void childrenAlloc(void);
    
    /// helper that reorder a child
    void insertChild(Node* child, int z);

    /// Removes a child, call child->onExit(), do cleanup, remove it from children array.
    void detachChild(Node *child, ssize_t index, bool doCleanup);

    /// Convert cocos2d coordinates to UI windows coordinate.
    Point convertToWindowSpace(const Point& nodePoint) const;
    
    virtual void updateCascadeOpacity();
    virtual void disableCascadeOpacity();
    virtual void updateCascadeColor();
    virtual void disableCascadeColor();
    virtual void updateColor() {}

    float _rotationX;               ///< rotation on the X-axis
    float _rotationY;               ///< rotation on the Y-axis

    // rotation Z is decomposed in 2 to simulate Skew for Flash animations
    float _rotationZ_X;             ///< rotation angle on Z-axis, component X
    float _rotationZ_Y;             ///< rotation angle on Z-axis, component Y

    float _scaleX;                  ///< scaling factor on x-axis
    float _scaleY;                  ///< scaling factor on y-axis
    float _scaleZ;                  ///< scaling factor on z-axis

    Point _position;                ///< position of the node
    float _positionZ;               ///< OpenGL real Z position
    Point _normalizedPosition;      ///< position in normalized coordinates

    float _skewX;                   ///< skew angle on x-axis
    float _skewY;                   ///< skew angle on y-axis

    Point _anchorPointInPoints;    ///< anchor point in points
    Point _anchorPoint;            ///< anchor point normalized (NOT in points)

    Size _contentSize;             ///< untransformed size of the node

    kmMat4  _modelViewTransform;    ///< ModelView transform of the Node.

    // "cache" variables are allowed to be mutable
    mutable kmMat4 _additionalTransform; ///< transform
    mutable kmMat4 _transform;     ///< transform
    mutable kmMat4 _inverse;       ///< inverse transform
    bool _useAdditionalTransform;   ///< The flag to check whether the additional transform is dirty
    mutable bool _transformDirty;             ///< transform dirty flag
    mutable bool _inverseDirty;               ///< inverse transform dirty flag


    int _localZOrder;                   ///< Local order (relative to its siblings) used to sort the node
    float _globalZOrder;                ///< Global order used to sort the node

    Vector<Node*> _children;               ///< array of children nodes
    Node *_parent;                  ///< weak reference to parent node

    int _tag;                         ///< a tag. Can be any number you assigned just to identify this node

    void *_userData;                  ///< A user assingned void pointer, Can be point to any cpp object
    Ref *_userObject;            ///< A user assigned Object

    GLProgram *_shaderProgram;      ///< OpenGL shader

    int _orderOfArrival;            ///< used to preserve sequence while sorting children with the same localZOrder

    Scheduler *_scheduler;          ///< scheduler used to schedule timers and updates

    ActionManager *_actionManager;  ///< a pointer to ActionManager singleton, which is used to handle all the actions

    EventDispatcher* _eventDispatcher;  ///< event dispatcher used to dispatch all kinds of events

    bool _running;                    ///< is running

    bool _visible;                    ///< is this node visible

    bool _ignoreAnchorPointForPosition; ///< true if the Anchor Point will be (0,0) when you position the Node, false otherwise.
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

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Node);
};

//#pragma mark - NodeRGBA

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
