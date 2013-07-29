/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2009      Valentin Milea
 Copyright (c) 2011      Zynga Inc.

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

#ifndef __PLATFORM_CCNODE_H__
#define __PLATFORM_CCNODE_H__

#include "ccMacros.h"
#include "cocoa/CCAffineTransform.h"
#include "cocoa/CCArray.h"
#include "CCGL.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCGLProgram.h"
#include "kazmath/kazmath.h"
#include "script_support/CCScriptSupport.h"
#include "CCProtocols.h"

NS_CC_BEGIN

class Camera;
class GridBase;
class Point;
class Touch;
class Action;
class RGBAProtocol;
class LabelProtocol;
class Scheduler;
class ActionManager;
class Component;
class Dictionary;
class ComponentContainer;

/**
 * @addtogroup base_nodes
 * @{
 */

enum {
    kNodeTagInvalid = -1,
};

enum {
    kNodeOnEnter,
    kNodeOnExit,
    kNodeOnEnterTransitionDidFinish,
    kNodeOnExitTransitionDidStart,
    kNodeOnCleanup
};

/** @brief Node is the main element. Anything that gets drawn or contains things that get drawn is a Node.
 The most popular Nodes are: Scene, Layer, Sprite, Menu.

 The main features of a Node are:
 - They can contain other Node nodes (addChild, getChildByTag, removeChild, etc)
 - They can schedule periodic callback (schedule, unschedule, etc)
 - They can execute actions (runAction, stopAction, etc)

 Some Node nodes provide extra functionality for them or their children.

 Subclassing a Node usually means (one/all) of:
 - overriding init to initialize resources and schedule callbacks
 - create callbacks to handle the advancement of time
 - overriding draw to render the node

 Features of Node:
 - position
 - scale (x, y)
 - rotation (in degrees, clockwise)
 - Camera (an interface to gluLookAt )
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
 - A Node is a "void" object. It doesn't have a texture

 Order in transformations with grid disabled
 -# The node will be translated (position)
 -# The node will be rotated (rotation)
 -# The node will be scaled (scale)
 -# The node will be moved according to the camera values (camera)

 Order in transformations with grid enabled
 -# The node will be translated (position)
 -# The node will be rotated (rotation)
 -# The node will be scaled (scale)
 -# The grid will capture the screen
 -# The node will be moved according to the camera values (camera)
 -# The grid will render the captured screen

 Camera:
 - Each node has a camera. By default it points to the center of the Node.
 */

class CC_DLL Node : public Object
{
public:
    /// @{
    /// @name Constructor, Distructor and Initializers

    /**
     * Allocates and initializes a node.
     * @return A initialized node which is marked as "autorelease".
     */
    static Node * create(void);

    /**
     * Default constructor
     */
    Node(void);
    
    /**
     * Default destructor
     */
    virtual ~Node(void);
    
    /**
     *  Initializes the instance of Node
     *  @return Whether the initialization was successful.
     */
    virtual bool init();

    /**
     * Gets the description string. It makes debugging easier.
     * @return A string terminated with '\0'
     */
    const char* description(void) const;
    
    /// @} end of initializers
    
    
    
    /// @{
    /// @name Setters & Getters for Graphic Peroperties
    
    /**
     * Sets the Z order which stands for the drawing order, and reorder this node in its parent's children array.
     *
     * The Z order of node is relative to its "brothers": children of the same parent.
     * It's nothing to do with OpenGL's z vertex. This one only affects the draw order of nodes in cocos2d.
     * The larger number it is, the later this node will be drawn in each message loop.
     * Please refer to setVertexZ(float) for the difference.
     *
     * @param nZOrder   Z order of this node.
     */
    virtual void setZOrder(int zOrder);
    /**
     * Sets the z order which stands for the drawing order
     *
     * This is an internal method. Don't call it outside the framework.
     * The difference between setZOrder(int) and _setOrder(int) is:
     * - _setZOrder(int) is a pure setter for _ZOrder memeber variable
     * - setZOrder(int) firstly changes _ZOrder, then recorder this node in its parent's chilren array.
     */
    virtual void _setZOrder(int z);
    /**
     * Gets the Z order of this node.
     *
     * @see setZOrder(int)
     *
     * @return The Z order.
     */
    virtual int getZOrder() const;


    /**
     * Sets the real OpenGL Z vertex.
     *
     * Differences between openGL Z vertex and cocos2d Z order:
     * - OpenGL Z modifies the Z vertex, and not the Z order in the relation between parent-children
     * - OpenGL Z might require to set 2D projection
     * - cocos2d Z order works OK if all the nodes uses the same openGL Z vertex. eg: vertexZ = 0
     *
     * @warning Use it at your own risk since it might break the cocos2d parent-children z order
     *
     * @param fVertexZ  OpenGL Z vertex of this node.
     */
    virtual void setVertexZ(float vertexZ);
    /**
     * Gets OpenGL Z vertex of this node.
     *
     * @see setVertexZ(float)
     *
     * @return OpenGL Z vertex of this node
     */
    virtual float getVertexZ() const;


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
     * @see setScaleY(float)
     *
     * @return The scale factor on Y axis. 
     */
    virtual float getScaleY() const;

    
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
     * @warning Assert when _scaleX != _scaleY.
     * @see setScale(float)
     *
     * @return The scale factor of the node.
     */
    virtual float getScale() const;
    
    
    /**
     * Changes the position (x,y) of the node in OpenGL coordinates
     *
     * Usually we use Point(x,y) to compose Point object.
     * The original point (0,0) is at the left-bottom corner of screen.
     * For example, this codesnip sets the node in the center of screen.
     * @code
     * Size size = Director::getInstance()->getWinSize();
     * node->setPosition( Point(size.width/2, size.height/2) )
     * @endcode
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
     */
    virtual const Point& getPosition() const;
    /**
     * Sets position in a more efficient way.
     *
     * Passing two numbers (x,y) is much efficient than passing Point object.
     * This method is binded to lua and javascript. 
     * Passing a number is 10 times faster than passing a object from lua to c++
     *
     * @code
     * // sample code in lua
     * local pos  = node::getPosition()  -- returns Point object from C++
     * node:setPosition(x, y)            -- pass x, y coordinate to C++
     * @endcode
     *
     * @param x     X coordinate for position
     * @param y     Y coordinate for position
     */
    virtual void setPosition(float x, float y);
    /**
     * Gets position in a more efficient way, returns two number instead of a Point object
     *
     * @see setPosition(float, float)
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
     * Changes the X skew angle of the node in degrees.
     *
     * This angle describes the shear distortion in the X direction.
     * Thus, it is the angle between the Y axis and the left edge of the shape
     * The default skewX angle is 0. Positive values distort the node in a CW direction.
     *
     * @param fSkewX The X skew angle of the node in degrees.
     */
    virtual void setSkewX(float fSkewX);
    /**
     * Returns the X skew angle of the node in degrees.
     *
     * @see setSkewX(float)
     *
     * @return The X skew angle of the node in degrees.
     */
    virtual float getSkewX() const;

    
    /**
     * Changes the Y skew angle of the node in degrees.
     *
     * This angle describes the shear distortion in the Y direction.
     * Thus, it is the angle between the X axis and the bottom edge of the shape
     * The default skewY angle is 0. Positive values distort the node in a CCW direction.
     *
     * @param fSkewY    The Y skew angle of the node in degrees.
     */
    virtual void setSkewY(float fSkewY);
    /**
     * Returns the Y skew angle of the node in degrees.
     *
     * @see setSkewY(float)
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
     * @see setAnchorPoint(const Point&)
     *
     * @return The anchor point of node.
     */
    virtual const Point& getAnchorPoint() const;
    /**
     * Returns the anchorPoint in absolute pixels.
     * 
     * @warning You can only read it. If you wish to modify it, use anchorPoint instead.
     * @see getAnchorPoint()
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
     * @see setContentSize(const Size&)
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
     * @see setVisible(bool)
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
     * @see setRotation(float)
     *
     * @return The rotation of the node in degrees.
     */
    virtual float getRotation() const;

    
    /** 
     * Sets the X rotation (angle) of the node in degrees which performs a horizontal rotational skew.
     * 
     * 0 is the default rotation angle. 
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     * 
     * @param fRotationX    The X rotation in degrees which performs a horizontal rotational skew.
     */
    virtual void setRotationX(float rotaionX);
    /**
     * Gets the X rotation (angle) of the node in degrees which performs a horizontal rotation skew.
     *
     * @see setRotationX(float)
     *
     * @return The X rotation in degrees.
     */
    virtual float getRotationX() const;

    
    /** 
     * Sets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
     * 
     * 0 is the default rotation angle. 
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     *
     * @param fRotationY    The Y rotation in degrees.
     */
    virtual void setRotationY(float rotationY);
    /**
     * Gets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
     *
     * @see setRotationY(float)
     *
     * @return The Y rotation in degrees.
     */
    virtual float getRotationY() const;

    
    /**
     * Sets the arrival order when this node has a same ZOrder with other children.
     *
     * A node which called addChild subsequently will take a larger arrival order,
     * If two children have the same Z order, the child with larger arrival order will be drawn later.
     *
     * @warning This method is used internally for zOrder sorting, don't change this manually
     *
     * @param orderOfArrival   The arrival order.
     */
    virtual void setOrderOfArrival(int orderOfArrival);
    /**
     * Returns the arrival order, indecates which children is added previously.
     *
     * @see setOrderOfArrival(unsigned int)
     *
     * @return The arrival order.
     */
    virtual int getOrderOfArrival() const;
    
    
    /** @deprecated No longer needed */
    CC_DEPRECATED_ATTRIBUTE void setGLServerState(int serverState) { /* ignore */ };
    /** @deprecated No longer needed */
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
     * @see ignoreAnchorPointForPosition(bool)
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
     * Adds a child to the container with a z-order
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setZOrder(int)
     */
    virtual void addChild(Node * child, int zOrder);
    /** 
     * Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setZOrder(int)
     * @param tag       A interger to identify the node easily. Please refer to setTag(int)
     */
    virtual void addChild(Node* child, int zOrder, int tag);
    /**
     * Gets a child from the container with its tag
     *
     * @param tag   An identifier to find the child node.
     *
     * @return a Node object whose tag equals to the input parameter
     */
    Node * getChildByTag(int tag);
    /**
     * Return an array of children
     *
     * Composing a "tree" structure is a very important feature of Node
     * Here's a sample code of traversing children array:
     * @code
     * Node* node = NULL;
     * CCARRAY_FOREACH(parent->getChildren(), node)
     * {
     *     node->setPosition(0,0);
     * }
     * @endcode
     * This sample code traverses all children nodes, and set theie position to (0,0)
     *
     * @return An array of children
     */
    virtual Array* getChildren() { return _children; }
    virtual const Array *getChildren() const { return _children; }
    
    /** 
     * Get the amount of children.
     *
     * @return The amount of children.
     */
    unsigned int getChildrenCount() const;
    
    /**
     * Sets the parent node
     *
     * @param parent    A pointer to the parnet node
     */
    virtual void setParent(Node* parent);
    /**
     * Returns a pointer to the parent node
     * 
     * @see setParent(Node*)
     *
     * @returns A pointer to the parnet node
     */
    virtual Node* getParent() { return _parent; }
    virtual const Node* getParent() const { return _parent; }

    
    ////// REMOVES //////
    
    /** 
     * Removes this node itself from its parent node with a cleanup.
     * If the node orphan, then nothing happens.
     * @see removeFromParentAndCleanup(bool)
     */
    virtual void removeFromParent();
    /** 
     * Removes this node itself from its parent node. 
     * If the node orphan, then nothing happens.
     * @param cleanup   true if all actions and callbacks on this node should be removed, false otherwise.
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
     * @see removeAllChildrenWithCleanup(bool)
     */
    virtual void removeAllChildren();
    /** 
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @param cleanup   true if all running actions on all children nodes should be cleanup, false oterwise.
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup);
    
    /** 
     * Reorders a child according to a new z value.
     *
     * @param child     An already added child node. It MUST be already added.
     * @param zOrder    Z order for drawing priority. Please refer to setZOrder(int)
     */
    virtual void reorderChild(Node * child, int zOrder);
    
    /** 
     * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This appraoch can improves the performance massively.
     * @note Don't call this manually unless a child added needs to be removed in the same frame 
     */
    virtual void sortAllChildren();

    /// @} end of Children and Parent
    

    
    /// @{
    /// @name Grid object for effects
    
    /**
     * Returns a grid object that is used when applying effects
     * 
     * @return A Grid object that is used when applying effects
     */
    virtual GridBase* getGrid() { return _grid; }
    virtual const GridBase* getGrid() const { return _grid; }

    /**
     * Changes a grid object that is used when applying effects
     *
     * @param A Grid object that is used when applying effects
     */
    virtual void setGrid(GridBase *grid);
    
    /// @} end of Grid
    
    
    /// @{
    /// @name Tag & User data
    
    /**
     * Returns a tag that is used to identify the node easily.
     *
     * You can set tags to node then identify them easily.
     * @code
     * #define TAG_PLAYER  1
     * #define TAG_MONSTER 2
     * #define TAG_BOSS    3
     * // set tags
     * node1->setTag(TAG_PLAYER);
     * node2->setTag(TAG_MONSTER);
     * node3->setTag(TAG_BOSS);
     * parent->addChild(node1);
     * parent->addChild(node2);
     * parent->addChild(node3);
     * // identify by tags
     * Node* node = NULL;
     * CCARRAY_FOREACH(parent->getChildren(), node)
     * {
     *     switch(node->getTag())
     *     {
     *         case TAG_PLAYER:
     *             break;
     *         case TAG_MONSTER:
     *             break;
     *         case TAG_BOSS:
     *             break;
     *     }
     * }
     * @endcode
     *
     * @return A interger that identifies the node.
     */
    virtual int getTag() const;
    /**
     * Changes the tag that is used to identify the node easily.
     *
     * Please refer to getTag for the sample code.
     *
     * @param A interger that indentifies the node.
     */
    virtual void setTag(int tag);
    
    /**
     * Returns a custom user data pointer
     *
     * You can set everything in UserData pointer, a data block, a structure or an object.
     * 
     * @return A custom user data pointer
     */
    virtual void* getUserData() { return _userData; }
    virtual const void* getUserData() const { return _userData; }

    /**
     * Sets a custom user data pointer
     *
     * You can set everything in UserData pointer, a data block, a structure or an object, etc.
     * @warning Don't forget to release the memroy manually, 
     *          especially before you change this data pointer, and before this node is autoreleased.
     *
     * @param A custom user data pointer
     */
    virtual void setUserData(void *userData);
    
    /** 
     * Returns a user assigned Object
     * 
     * Similar to userData, but instead of holding a void* it holds an object
     *
     * @return A user assigned Object
     */
    virtual Object* getUserObject() { return _userObject; }
    virtual const Object* getUserObject() const { return _userObject; }

    /**
     * Returns a user assigned Object
     *
     * Similar to UserData, but instead of holding a void* it holds an object.
     * The UserObject will be retained once in this method,
     * and the previous UserObject (if existed) will be relese.
     * The UserObject will be released in Node's destructure.
     *
     * @param A user assigned Object
     */
    virtual void setUserObject(Object *userObject);
    
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
     * @code
     * node->setShaderProgram(ShaderCache::getInstance()->programForKey(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
     * @endcode
     * 
     * @param The shader program which fetchs from ShaderCache.
     */
    virtual void setShaderProgram(GLProgram *shaderProgram);
    /// @} end of Shader Program
    
    
    /**
     * Returns a camera object that lets you move the node using a gluLookAt
     *
     * @code
     * Camera* camera = node->getCamera();
     * camera->setEyeXYZ(0, 0, 415/2);
     * camera->setCenterXYZ(0, 0, 0);
     * @endcode
     *
     * @return A Camera object that lets you move the node using a gluLookAt
     */
    virtual Camera* getCamera();
    
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
     */
    virtual void onEnter();

    /** Event callback that is invoked when the Node enters in the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition finishes.
     * If you override onEnterTransitionDidFinish, you shall call its parent's one, e.g. Node::onEnterTransitionDidFinish()
     */
    virtual void onEnterTransitionDidFinish();

    /** 
     * Event callback that is invoked every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
     */
    virtual void onExit();

    /** 
     * Event callback that is called every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this callback is called when the transition starts.
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
     * - glEnableClientState(GL_VERTEX_ARRAY);
     * - glEnableClientState(GL_COLOR_ARRAY);
     * - glEnableClientState(GL_TEXTURE_COORD_ARRAY);
     * - glEnable(GL_TEXTURE_2D);
     * AND YOU SHOULD NOT DISABLE THEM AFTER DRAWING YOUR NODE
     * But if you enable any other GL state, you should disable it after drawing your node.
     */
    virtual void draw();

    /** 
     * Visits this node's children and draw them recursively.
     */
    virtual void visit();

    
    /** 
     * Returns a "local" axis aligned bounding box of the node.
     * The returned box is relative only to its parent.
     *
     * @note This method returns a temporaty variable, so it can't returns const Rect&
     * @todo Rename to getBoundingBox() in the future versions.
     * 
     * @return A "local" axis aligned boudning box of the node.
     */
    virtual Rect getBoundingBox() const;

    /** @deprecated Use getBoundingBox instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual Rect boundingBox() const { return getBoundingBox(); }

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
     * @param An action object to be removed.
     */
    void stopAction(Action* action);

    /** 
     * Removes an action from the running action list by its tag.
     *
     * @param A tag that indicates the action to be removed.
     */
    void stopActionByTag(int tag);

    /** 
     * Gets an action from the running action list by its tag.
     *
     * @see setTag(int), getTag().
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
    unsigned int getNumberOfRunningActions() const;

    /** @deprecated Use getNumberOfRunningActions() instead */
    CC_DEPRECATED_ATTRIBUTE unsigned int numberOfRunningActions() const { return getNumberOfRunningActions(); };

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
     */
    bool isScheduled(SEL_SCHEDULE selector);

    /** 
     * Schedules the "update" method. 
     *
     * It will use the order number 0. This method will be called every frame.
     * Scheduled methods with a lower order value will be called before the ones that have a higher order value.
     * Only one "update" method could be scheduled per node.
     */
    void scheduleUpdate(void);

    /** 
     * Schedules the "update" method with a custom priority. 
     *
     * This selector will be called every frame.
     * Scheduled methods with a lower priority will be called before the ones that have a higher value.
     * Only one "update" selector could be scheduled per node (You can't have 2 'update' selectors).
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
     * @code
     * // firstly, implement a schedule function
     * void MyNode::TickMe(float dt);
     * // wrap this function into a selector via schedule_selector marco.
     * this->schedule(schedule_selector(MyNode::TickMe), 0, 0, 0);
     * @endcode
     *
     * @param interval  Tick interval in seconds. 0 means tick every frame. If interval = 0, it's recommended to use scheduleUpdate() instead.
     * @param repeat    The selector will be excuted (repeat + 1) times, you can use kRepeatForever for tick infinitely.
     * @param delay     The amount of time that the first tick will wait before execution.
     */
    void schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);
    
    /**
     * Schedules a custom selector with an interval time in seconds.
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      A function wrapped as a selector
     * @param interval      Callback interval time in seconds. 0 means tick every frame,
     */
    void schedule(SEL_SCHEDULE selector, float interval);
    
    /**
     * Schedules a selector that runs only once, with a delay of 0 or larger
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      A function wrapped as a selector
     * @param delay         The amount of time that the first tick will wait before execution.
     */
    void scheduleOnce(SEL_SCHEDULE selector, float delay);
    
    /**
     * Schedules a custom selector, the scheduled selector will be ticked every frame
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      A function wrapped as a selector
     */
    void schedule(SEL_SCHEDULE selector);
    
    /** 
     * Unschedules a custom selector.
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      A function wrapped as a selector
     */
    void unschedule(SEL_SCHEDULE selector);

    /** 
     * Unschedule all scheduled selectors: custom selectors, and the 'update' selector.
     * Actions are not affected by this method.
     */
    void unscheduleAllSelectors(void);

    /** 
     * Resumes all scheduled selectors and actions.
     * This method is called internally by onEnter
     */
    void resumeSchedulerAndActions(void);
    /** 
     * Pauses all scheduled selectors and actions.
     * This method is called internally by onExit
     */
    void pauseSchedulerAndActions(void);
    
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
     * e.g., batchNode->addChild(myCustomNode), while you can only addChild(sprite) before.
     */
    virtual void updateTransform();
    
    /** 
     * Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     */
    virtual AffineTransform getNodeToParentTransform() const;

    /** @deprecated use getNodeToParentTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToParentTransform() const { return getNodeToParentTransform(); }

    /** 
     * Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
     * The matrix is in Pixels.
     */
    virtual AffineTransform getParentToNodeTransform() const;

    /** @deprecated Use getParentToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform parentToNodeTransform() const { return getParentToNodeTransform(); }

    /** 
     * Returns the world affine transform matrix. The matrix is in Pixels.
     */
    virtual AffineTransform getNodeToWorldTransform() const;

    /** @deprecated Use getNodeToWorldTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToWorldTransform() const { return getNodeToWorldTransform(); }

    /** 
     * Returns the inverse world affine transform matrix. The matrix is in Pixels.
     */
    virtual AffineTransform getWorldToNodeTransform() const;

    /** @deprecated Use worldToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform worldToNodeTransform() const { return getWorldToNodeTransform(); }

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
     *  Sets the additional transform.
     *
     *  @note The additional transform will be concatenated at the end of getNodeToParentTransform.
     *        It could be used to simulate `parent-child` relationship between two nodes (e.g. one is in BatchNode, another isn't).
     *  @code
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
        AffineTransform t = spriteA->getNodeToParentTransform();
     
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
     *  @endcode
     */
    void setAdditionalTransform(const AffineTransform& additionalTransform);
    
    /// @} end of Coordinate Converters

      /// @{
    /// @name component functions
    /** 
     *   gets a component by its name
     */
    Component* getComponent(const char *pName);
    
    /** 
     *   adds a component
     */
    virtual bool addComponent(Component *pComponent);
    
    /** 
     *   removes a component by its name      
     */
    virtual bool removeComponent(const char *pName);
    
    /**
     *   removes all components
     */
    virtual void removeAllComponents();
    /// @} end of component functions

private:
    /// lazy allocs
    void childrenAlloc(void);
    
    /// helper that reorder a child
    void insertChild(Node* child, int z);
    
    /// Removes a child, call child->onExit(), do cleanup, remove it from children array.
    void detachChild(Node *child, bool doCleanup);
    
    /// Convert cocos2d coordinates to UI windows coordinate.
    Point convertToWindowSpace(const Point& nodePoint) const;

protected:
    float _rotationX;                 ///< rotation angle on x-axis
    float _rotationY;                 ///< rotation angle on y-axis
    
    float _scaleX;                    ///< scaling factor on x-axis
    float _scaleY;                    ///< scaling factor on y-axis
    
    float _vertexZ;                   ///< OpenGL real Z vertex
    
    Point _position;               ///< position of the node
    
    float _skewX;                     ///< skew angle on x-axis
    float _skewY;                     ///< skew angle on y-axis
    
    Point _anchorPointInPoints;    ///< anchor point in points
    Point _anchorPoint;            ///< anchor point normalized (NOT in points)
    
    Size _contentSize;             ///< untransformed size of the node
    
    // "cache" variables are allowed to be mutable
    mutable AffineTransform _additionalTransform; ///< transform
    mutable AffineTransform _transform;     ///< transform
    mutable AffineTransform _inverse;       ///< inverse transform
    mutable bool _additionalTransformDirty;   ///< The flag to check whether the additional transform is dirty
    mutable bool _transformDirty;             ///< transform dirty flag
    mutable bool _inverseDirty;               ///< inverse transform dirty flag

    Camera *_camera;                ///< a camera
    
    GridBase *_grid;                ///< a grid
    
    int _ZOrder;                      ///< z-order value that affects the draw order
    
    Array *_children;               ///< array of children nodes
    Node *_parent;                  ///< weak reference to parent node
    
    int _tag;                         ///< a tag. Can be any number you assigned just to identify this node
    
    void *_userData;                  ///< A user assingned void pointer, Can be point to any cpp object
    Object *_userObject;            ///< A user assigned Object
    
    GLProgram *_shaderProgram;      ///< OpenGL shader

    int _orderOfArrival;            ///< used to preserve sequence while sorting children with the same zOrder
    
    Scheduler *_scheduler;          ///< scheduler used to schedule timers and updates
    
    ActionManager *_actionManager;  ///< a pointer to ActionManager singleton, which is used to handle all the actions
    
    bool _running;                    ///< is running
    
    bool _visible;                    ///< is this node visible
    
    bool _ignoreAnchorPointForPosition; ///< true if the Anchor Point will be (0,0) when you position the Node, false otherwise.
                                          ///< Used by Layer and Scene.
    
    bool _reorderChildDirty;          ///< children order dirty flag
    bool _isTransitionFinished;       ///< flag to indicate whether the transition was finished
    
    int _scriptHandler;               ///< script handler for onEnter() & onExit(), used in Javascript binding and Lua binding.
    int _updateScriptHandler;         ///< script handler for update() callback per frame, which is invoked from lua & javascript.
    ccScriptType _scriptType;         ///< type of script binding, lua or javascript
    
    ComponentContainer *_componentContainer;        ///< Dictionary of components

};

//#pragma mark - NodeRGBA

/** NodeRGBA is a subclass of Node that implements the RGBAProtocol protocol.
 
 All features from Node are valid, plus the following new features:
 - opacity
 - RGB colors
 
 Opacity/Color propagates into children that conform to the RGBAProtocol if cascadeOpacity/cascadeColor is enabled.
 @since v2.1
 */
class CC_DLL NodeRGBA : public Node, public RGBAProtocol
{
public:
    NodeRGBA();
    virtual ~NodeRGBA();
    
    virtual bool init();

    // overrides
    virtual GLubyte getOpacity() const override;
    virtual GLubyte getDisplayedOpacity() const  override;
    virtual void setOpacity(GLubyte opacity) override;
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
    virtual bool isCascadeOpacityEnabled() const  override;
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) override;
    
    virtual const Color3B& getColor(void) const override;
    virtual const Color3B& getDisplayedColor() const override;
    virtual void setColor(const Color3B& color) override;
    virtual void updateDisplayedColor(const Color3B& parentColor) override;
    virtual bool isCascadeColorEnabled() const override;
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) override;
    
    virtual void setOpacityModifyRGB(bool bValue) override {CC_UNUSED_PARAM(bValue);};
    virtual bool isOpacityModifyRGB() const override { return false; };

protected:
	GLubyte		_displayedOpacity;
    GLubyte     _realOpacity;
	Color3B	    _displayedColor;
    Color3B     _realColor;
	bool		_cascadeColorEnabled;
    bool        _cascadeOpacityEnabled;
};

// end of base_node group
/// @}

NS_CC_END

#endif // __PLATFORM_CCNODE_H__
