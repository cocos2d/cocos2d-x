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

NS_CC_BEGIN

class CCCamera;
class CCGridBase;
class CCPoint;
class CCTouch;
class CCAction;
class CCRGBAProtocol;
class CCLabelProtocol;
class CCScheduler;
class CCActionManager;

/**
 * @addtogroup base_nodes
 * @{
 */

enum {
    kCCNodeTagInvalid = -1,
};

enum {
    kCCNodeOnEnter,
    kCCNodeOnExit,
    kCCNodeOnEnterTransitionDidFinish,
    kCCNodeOnExitTransitionDidStart,
    kCCNodeOnCleanup
};

/** @brief CCNode is the main element. Anything that gets drawn or contains things that get drawn is a CCNode.
 The most popular CCNodes are: CCScene, CCLayer, CCSprite, CCMenu.

 The main features of a CCNode are:
 - They can contain other CCNode nodes (addChild, getChildByTag, removeChild, etc)
 - They can schedule periodic callback (schedule, unschedule, etc)
 - They can execute actions (runAction, stopAction, etc)

 Some CCNode nodes provide extra functionality for them or their children.

 Subclassing a CCNode usually means (one/all) of:
 - overriding init to initialize resources and schedule callbacks
 - create callbacks to handle the advancement of time
 - overriding draw to render the node

 Features of CCNode:
 - position
 - scale (x, y)
 - rotation (in degrees, clockwise)
 - CCCamera (an interface to gluLookAt )
 - CCGridBase (to do mesh transformations)
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
 - A CCNode is a "void" object. It doesn't have a texture

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
 - Each node has a camera. By default it points to the center of the CCNode.
 */

class CC_DLL CCNode : public CCObject
{
protected:
    // rotation angle
    float m_fRotationX, m_fRotationY;
    
    // scaling factors
    float m_fScaleX, m_fScaleY;
    
    // openGL real Z vertex
    float m_fVertexZ;
    
    // position of the node
    CCPoint m_obPosition;
    
    // skew angles
    float m_fSkewX, m_fSkewY;
    
    // anchor point in points
    CCPoint m_obAnchorPointInPoints;
    // anchor point normalized (NOT in points)
    CCPoint m_obAnchorPoint;
    
    // untransformed size of the node
    CCSize m_obContentSize;
    
    // transform
    CCAffineTransform m_sTransform, m_sInverse;
    
    // a Camera
    CCCamera *m_pCamera;
    
    // a Grid
    CCGridBase *m_pGrid;
    
    // z-order value
    int m_nZOrder;
    
    // array of children
    CCArray *m_pChildren;
    
    // weak ref to parent
    CCNode *m_pParent;
    
    // a tag. any number you want to assign to the node
    int m_nTag;
    
    // user data field
    void *m_pUserData;
    CCObject *m_pUserObject;
    
    // Shader
    CCGLProgram *m_pShaderProgram;
    
    // Server side state
    ccGLServerState m_eGLServerState;
    
    // used to preserve sequence while sorting children with the same zOrder
    unsigned int m_uOrderOfArrival;
    
    // scheduler used to schedule timers and updates
    CCScheduler *m_pScheduler;
    
    // ActionManager used to handle all the actions
    CCActionManager *m_pActionManager;
    
    // Is running
    bool m_bRunning;
    
    bool m_bTransformDirty;
    bool m_bInverseDirty;
    
    // is visible
    bool m_bVisible;
    
    // If true, the Anchor Point will be (0,0) when you position the CCNode.
	// Used by CCLayer and CCScene
    bool m_bIgnoreAnchorPointForPosition;

    bool m_bReorderChildDirty;
    
    // Properties for script
    
    // script handler
    int m_nScriptHandler;
    
    // script type, lua or javascript
    ccScriptType m_eScriptType;

public:
    // getter & setter
    
    /** The z order of the node relative to it's "brothers": children of the same parent */
    virtual int getZOrder();
    virtual void setZOrder(int nZOrder);

    /** The real openGL Z vertex.
     Differences between openGL Z vertex and cocos2d Z order:
     - OpenGL Z modifies the Z vertex, and not the Z order in the relation between parent-children
     - OpenGL Z might require to set 2D projection
     - cocos2d Z order works OK if all the nodes uses the same openGL Z vertex. eg: vertexZ = 0
     @warning: Use it at your own risk since it might break the cocos2d parent-children z order
     @since v0.8
     */
    virtual float getVertexZ();
    virtual void setVertexZ(float fVertexZ);

    /** The scale factor of the node. 1.0 is the default scale factor. It only modifies the X scale factor. */
    virtual float getScaleX();
    virtual void setScaleX(float fScaleX);

    /** The scale factor of the node. 1.0 is the default scale factor. It only modifies the Y scale factor. */
    virtual float getScaleY();
    virtual void setScaleY(float fScaleY);

    /** Position (x,y) of the node in OpenGL coordinates. (0,0) is the left-bottom corner. */
    virtual CCPoint getPosition();
    virtual void setPosition(const CCPoint &position);
    
    /** The X skew angle of the node in degrees.
     This angle describes the shear distortion in the X direction.
     Thus, it is the angle between the Y axis and the left edge of the shape
     The default skewX angle is 0. Positive values distort the node in a CW direction.
     */
    virtual float getSkewX();
    virtual void setSkewX(float fSkewX);
    
    /** The Y skew angle of the node in degrees.
     This angle describes the shear distortion in the Y direction.
     Thus, it is the angle between the X axis and the bottom edge of the shape
     The default skewY angle is 0. Positive values distort the node in a CCW direction.
     */
    virtual float getSkewY();
    virtual void setSkewY(float fSkewY);
    
    virtual CCArray* getChildren();
    
    /** A CCCamera object that lets you move the node using a gluLookAt
     */
    virtual CCCamera* getCamera();
    
    /** A CCGrid object that is used when applying effects */
    virtual CCGridBase* getGrid();
    virtual void setGrid(CCGridBase *pGrid);
    
    /** A tag used to identify the node easily */
    virtual int getTag();
    virtual void setTag(int nTag);
    
    /** A custom user data pointer */
    virtual void* getUserData();
    virtual void setUserData(void *pUserData);
    
    /** Similar to userData, but instead of holding a void* it holds an id */
    virtual CCObject* getUserObject();
    virtual void setUserObject(CCObject *pUserObject); //retain
    
    /** Shader Program
     @since v2.0
     */
    virtual CCGLProgram* getShaderProgram();
    virtual void setShaderProgram(CCGLProgram *pShaderProgram);
    
    /** used internally for zOrder sorting, don't change this manually */
    virtual unsigned int getOrderOfArrival();
    virtual void setOrderOfArrival(unsigned int uOrderOfArrival);
    
    /** GL server side state
     @since v2.0
     */
    virtual ccGLServerState getGLServerState();
    virtual void setGLServerState(ccGLServerState glServerState);
    
    /** CCActionManager used by all the actions.
     IMPORTANT: If you set a new CCActionManager, then previously created actions are going to be removed.
     @since v2.0
     */
    virtual CCActionManager* getActionManager();
    virtual void setActionManager(CCActionManager *pActionManager);
    
    /** CCScheduler used to schedule all "updates" and timers.
     IMPORTANT: If you set a new CCScheduler, then previously created timers/update are going to be removed.
     @since v2.0
     */
    virtual CCScheduler* getScheduler();
    virtual void setScheduler(CCScheduler *pScheduler);
    
    /** A weak reference to the parent */
    virtual CCNode* getParent();
    virtual void setParent(CCNode *pParent);
    
    /** anchorPoint is the point around which all transformations and positioning manipulations take place.
     It's like a pin in the node where it is "attached" to its parent.
     The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the top-right corner.
     But you can use values higher than (1,1) and lower than (0,0) too.
     The default anchorPoint is (0.5,0.5), so it starts in the center of the node.
     @since v0.8
     */
    virtual CCPoint getAnchorPoint();
    virtual void setAnchorPoint(const CCPoint &anchorPoint);
    
    /** The anchorPoint in absolute pixels.
     Since v0.8 you can only read it. If you wish to modify it, use anchorPoint instead
     */
    virtual CCPoint getAnchorPointInPoints();
    
    /** The untransformed size of the node.
     The contentSize remains the same no matter the node is scaled or rotated.
     All nodes has a size. Layer and Scene has the same size of the screen.
     @since v0.8
     */
    virtual CCSize getContentSize();
    virtual void setContentSize(const CCSize &contentSize);

    virtual bool isVisible();
    virtual void setVisible(bool visible);
    
    /** Get the scale factor of the node.
     @warning: Assert when m_fScaleX != m_fScaleY.
     */
    virtual float getScale();
    /** The scale factor of the node. 1.0 is the default scale factor. It modifies the X and Y scale at the same time. */
    virtual void setScale(float scale);
    
    /** The rotation (angle) of the node in degrees. 0 is the default rotation angle. Positive values rotate node CW. */
    virtual float getRotation();
    virtual void setRotation(float fRotation);
    
    /** The rotation (angle) of the node in degrees. 0 is the default rotation angle. Positive values rotate node CW. It only modifies the X rotation performing a horizontal rotational skew . */
    virtual float getRotationX();
    virtual void setRotationX(float fRotaionX);
    /** The rotation (angle) of the node in degrees. 0 is the default rotation angle. Positive values rotate node CW. It only modifies the Y rotation performing a vertical rotational skew . */
    virtual float getRotationY();
    virtual void setRotationY(float fRotationY);

    /** whether or not the node is running */
    virtual bool isRunning();

    // If true, the Anchor Point will be (0,0) when you position the CCNode.
	// Used by CCLayer and CCScene
    virtual bool isIgnoreAnchorPointForPosition();
    virtual void ignoreAnchorPointForPosition(bool isIgnoreAnchorPointForPosition);

    /** Get children count */
    unsigned int getChildrenCount(void);
    
    inline int getScriptHandler() { return m_nScriptHandler; };
    
    /** get/set Position for Lua (pass number faster than CCPoint object)
     
     lua code:
     local pos  = node:getPositionLua() -- return CCPoint object from C++
     local x, y = node:getPosition()    -- return x, y values from C++
     local x    = node:getPositionX()
     local y    = node:getPositionY()
     node:setPosition(x, y)             -- pass x, y values to C++
     node:setPositionX(x)
     node:setPositionY(y)
     node:setPositionInPixels(x, y)     -- pass x, y values to C++
     */
    const CCPoint& getPositionLua(void);
    void getPosition(float* x, float* y);
    float getPositionX(void);
    float getPositionY(void);
    void setPositionX(float x);
    void setPositionY(float y);
    void setPosition(float x, float y);
    void _setZOrder(int z);

public:
    CCNode(void);

    virtual ~CCNode(void);

    const char* description(void);

    /** allocates and initializes a node.
     The node will be created as "autorelease".
	 @deprecated: This interface will be deprecated sooner or later.
     */
    CC_DEPRECATED_ATTRIBUTE static CCNode * node(void);

	/** allocates and initializes a node.
     The node will be created as "autorelease".
     */
    static CCNode * create(void);

    //scene management

    /** callback that is called every time the CCNode enters the 'stage'.
     If the CCNode enters the 'stage' with a transition, this callback is called when the transition starts.
     During onEnter you can't a "sister/brother" node.
     */
    virtual void onEnter();

    /** callback that is called when the CCNode enters in the 'stage'.
     If the CCNode enters the 'stage' with a transition, this callback is called when the transition finishes.
     @since v0.8
     */
    virtual void onEnterTransitionDidFinish();

    /** callback that is called every time the CCNode leaves the 'stage'.
     If the CCNode leaves the 'stage' with a transition, this callback is called when the transition finishes.
     During onExit you can't access a sibling node.
     */
    virtual void onExit();

    /** callback that is called every time the CCNode leaves the 'stage'.
     If the CCNode leaves the 'stage' with a transition, this callback is called when the transition starts.
     */
    virtual void onExitTransitionDidStart();

    /** Register onEnter/onExit handler script function
     
     Script handler auto unregister after onEnter().
     */
    virtual void registerScriptHandler(int nHandler);
    virtual void unregisterScriptHandler(void);

    // composition: ADD

    /** Adds a child to the container with z-order as 0.
     If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     @since v0.7.1
     */
    virtual void addChild(CCNode * child);

    /** Adds a child to the container with a z-order
     If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     @since v0.7.1
     */
    virtual void addChild(CCNode * child, int zOrder);

    /** Adds a child to the container with z order and tag
     If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     @since v0.7.1
     */
    virtual void addChild(CCNode * child, int zOrder, int tag);

    // composition: REMOVE

    /** Remove itself from its parent node forcing a cleanup.
     If the node orphan, then nothing happens.
     @since v2.1
     */
    virtual void removeFromParent();

    /** Remove itself from its parent node. If cleanup is true, then also remove all actions and callbacks.
     If the node orphan, then nothing happens.
     @since v0.99.3
     */
    virtual void removeFromParentAndCleanup(bool cleanup);

    /** Removes a child from the container forcing a cleanup
     @since v2.1
     */
    virtual void removeChild(CCNode* child);

    /** Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
     @since v0.7.1
     */
    virtual void removeChild(CCNode* child, bool cleanup);

    /** Removes a child from the container by tag value forcing a cleanup.
     @since v2.1
     */
    virtual void removeChildByTag(int tag);

    /** Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter
     @since v0.7.1
     */
    virtual void removeChildByTag(int tag, bool cleanup);

    /** Removes all children from the container forcing a cleanup.
     @since v2.1
     */
    virtual void removeAllChildren();

    /** Removes all children from the container and do a cleanup all running actions depending on the cleanup parameter.
     @since v0.7.1
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup);

    // composition: GET
    /** Gets a child from the container given its tag
     @return returns a CCNode object
     @since v0.7.1
     */
    CCNode * getChildByTag(int tag);

    /** Reorders a child according to a new z value.
     * The child MUST be already added.
     */
    virtual void reorderChild(CCNode * child, int zOrder);

    /** performance improvement, Sort the children array once before drawing, instead of every time when a child is added or reordered
     don't call this manually unless a child added needs to be removed in the same frame */
    virtual void sortAllChildren();

    /** Stops all running actions and schedulers
     @since v0.8
     */
    virtual void cleanup(void);

    // draw

    /** Override this method to draw your own node.
     The following GL states will be enabled by default:
     - glEnableClientState(GL_VERTEX_ARRAY);
     - glEnableClientState(GL_COLOR_ARRAY);
     - glEnableClientState(GL_TEXTURE_COORD_ARRAY);
     - glEnable(GL_TEXTURE_2D);

     AND YOU SHOULD NOT DISABLE THEM AFTER DRAWING YOUR NODE

     But if you enable any other GL state, you should disable it after drawing your node.
     */
    virtual void draw(void);

    /** recursive method that visit its children and draw them */
    virtual void visit(void);

    // transformations
    // MARMALADE ADDED THIS... SO IT IS NO LONGER SPECIFIC TO CCSprite
    /** updates the quad according the the rotation, position, scale values. */
    virtual void updateTransform(void);

    /** performs OpenGL view-matrix transformation based on position, scale, rotation and other attributes. */
    void transform(void);

    /** performs OpenGL view-matrix transformation of it's ancestors.
     Generally the ancestors are already transformed, but in certain cases (eg: attaching a FBO)
     it's necessary to transform the ancestors again.
     @since v0.7.2
     */
    void transformAncestors(void);

    /** returns a "local" axis aligned bounding box of the node.
     The returned box is relative only to its parent.

     @since v0.8.2
     */
    CCRect boundingBox(void);

    // actions

    /** Executes an action, and returns the action that is executed.
     The node becomes the action's target.
     @warning Starting from v0.8 actions don't retain their target anymore.
     @since v0.7.1
     @return An Action pointer
     */

    CCAction* runAction(CCAction* action);

    /** Removes all actions from the running action list */
    void stopAllActions(void);

    /** Removes an action from the running action list */
    void stopAction(CCAction* action);

    /** Removes an action from the running action list given its tag
     @since v0.7.1
     */
    void stopActionByTag(int tag);

    /** Gets an action from the running action list given its tag
     @since v0.7.1
     @return the Action the with the given tag
     */
    CCAction* getActionByTag(int tag);

    /** Returns the numbers of actions that are running plus the ones that are schedule to run (actions in actionsToAdd and actions arrays).
     * Composable actions are counted as 1 action. Example:
     *    If you are running 1 Sequence of 7 actions, it will return 1.
     *    If you are running 7 Sequences of 2 actions, it will return 7.
     */
    unsigned int numberOfRunningActions(void);


    // timers

    /** check whether a selector is scheduled. */
    bool isScheduled(SEL_SCHEDULE selector);

    /** schedules the "update" method. It will use the order number 0. This method will be called every frame.
     Scheduled methods with a lower order value will be called before the ones that have a higher order value.
     Only one "update" method could be scheduled per node.

     @since v0.99.3
     */
    void scheduleUpdate(void);

    /** schedules the "update" selector with a custom priority. This selector will be called every frame.
     Scheduled selectors with a lower priority will be called before the ones that have a higher value.
     Only one "update" selector could be scheduled per node (You can't have 2 'update' selectors).

     @since v0.99.3
     */
    void scheduleUpdateWithPriority(int priority);

    /* unschedules the "update" method.

     @since v0.99.3
     */
    void unscheduleUpdate(void);

    /** schedules a selector.
     The scheduled selector will be ticked every frame
     */
    void schedule(SEL_SCHEDULE selector);

    /** schedules a custom selector with an interval time in seconds.
     If time is 0 it will be ticked every frame.
     If time is 0, it is recommended to use 'scheduleUpdate' instead.
     If the selector is already scheduled, then the interval parameter
     will be updated without scheduling it again.
     */
    void schedule(SEL_SCHEDULE selector, float interval);

    /**
     repeat will execute the action repeat + 1 times, for a continues action use kCCRepeatForever
     delay is the amount of time the action will wait before execution
     */
    void schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);

    /**
     Schedules a selector that runs only once, with a delay of 0 or larger
    */
    void scheduleOnce(SEL_SCHEDULE selector, float delay);

    /** unschedules a custom selector.*/
    void unschedule(SEL_SCHEDULE selector);

    /** unschedule all scheduled selectors: custom selectors, and the 'update' selector.
     Actions are not affected by this method.
     @since v0.99.3
     */
    void unscheduleAllSelectors(void);

    /** resumes all scheduled selectors and actions.
     Called internally by onEnter
     */
    void resumeSchedulerAndActions(void);
    /** pauses all scheduled selectors and actions.
     Called internally by onExit
     */
    void pauseSchedulerAndActions(void);
    
    /* Update will be called automatically every frame if "scheduleUpdate" is called, and the node is "live"
     */
    virtual void update(float fDelta);

    // transformation methods

    /** Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     The matrix is in Pixels.
     @since v0.7.1
     */
    virtual CCAffineTransform nodeToParentTransform(void);

    /** Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
     The matrix is in Pixels.
     @since v0.7.1
     */
    virtual CCAffineTransform parentToNodeTransform(void);

    /** Returns the world affine transform matrix. The matrix is in Pixels.
     @since v0.7.1
     */
    virtual CCAffineTransform nodeToWorldTransform(void);

    /** Returns the inverse world affine transform matrix. The matrix is in Pixels.
     @since v0.7.1
     */
    virtual CCAffineTransform worldToNodeTransform(void);

    /** Converts a Point to node (local) space coordinates. The result is in Points.
     @since v0.7.1
     */
    CCPoint convertToNodeSpace(const CCPoint& worldPoint);
    /** Converts a Point to world space coordinates. The result is in Points.
     @since v0.7.1
     */
    CCPoint convertToWorldSpace(const CCPoint& nodePoint);
    /** Converts a Point to node (local) space coordinates. The result is in Points.
     treating the returned/received node point as anchor relative.
     @since v0.7.1
     */
    CCPoint convertToNodeSpaceAR(const CCPoint& worldPoint);
    /** Converts a local Point to world space coordinates.The result is in Points.
     treating the returned/received node point as anchor relative.
     @since v0.7.1
     */
    CCPoint convertToWorldSpaceAR(const CCPoint& nodePoint);

    /** convenience methods which take a CCTouch instead of CCPoint
     @since v0.7.1
     */
    CCPoint convertTouchToNodeSpace(CCTouch * touch);

    /** converts a CCTouch (world coordinates) into a local coordinate. This method is AR (Anchor Relative).
     @since v0.7.1
     */
    CCPoint convertTouchToNodeSpaceAR(CCTouch * touch);
    
private:
    //! lazy allocs
    void childrenAlloc(void);
    
    //! helper that reorder a child
    void insertChild(CCNode* child, int z);
    
    void detachChild(CCNode *child, bool doCleanup);
    
    CCPoint convertToWindowSpace(const CCPoint& nodePoint);
};

// end of base_node group
/// @}

NS_CC_END

#endif // __PLATFORM_CCNODE_H__



