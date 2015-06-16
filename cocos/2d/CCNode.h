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
#include "base/CCVector.h"
#include "base/CCProtocols.h"
#include "base/CCScriptSupport.h"
#include "math/CCAffineTransform.h"
#include "math/CCMath.h"

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
class Director;
class GLProgram;
class GLProgramState;
class Material;
#if CC_USE_PHYSICS
class PhysicsBody;
class PhysicsWorld;
#endif

/**
 * @addtogroup _2d
 * @{
 */

enum {
    kNodeOnEnter,
    kNodeOnExit,
    kNodeOnEnterTransitionDidFinish,
    kNodeOnExitTransitionDidStart,
    kNodeOnCleanup
};

bool CC_DLL nodeComparisonLess(Node* n1, Node* n2);

class EventListener;

/** @class Node
* @brief @~english Node is the base element of the Scene Graph. Elements of the Scene Graph must be Node objects or subclasses of it.
 The most common Node objects are: Scene, Layer, Sprite, Menu, Label.

 The main features of a Node are:
 - They can contain other Node objects (`addChild`, `getChildByTag`, `removeChild`, etc)
 - They can schedule periodic callback (`schedule`, `unschedule`, etc)
 - They can execute actions (`runAction`, `stopAction`, etc)

 Subclassing a Node usually means (one/all) of:
 - overriding init to initialize resources and schedule callbacks
 - create callbacks to handle the advancement of time
 - overriding `draw` to render the node

 Properties of Node:
 - position (default: x=0, y=0)
 - scale (default: x=1, y=1)
 - rotation (in degrees, clockwise) (default: 0)
 - anchor point (default: x=0, y=0)
 - contentSize (default: width=0, height=0)
 - visible (default: true)

 Limitations:
 - A Node is a "void" object. If you want to draw something on the screen, you should use a Sprite instead. Or subclass Node and override `draw`.

 @~chinese 节点是场景图的基本元素。场景图的基本元素必须是节点对象或者是节点对象的子类。
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

    enum {
        FLAGS_TRANSFORM_DIRTY = (1 << 0),
        FLAGS_CONTENT_SIZE_DIRTY = (1 << 1),
        FLAGS_RENDER_AS_3D = (1 << 3),

        FLAGS_DIRTY_MASK = (FLAGS_TRANSFORM_DIRTY | FLAGS_CONTENT_SIZE_DIRTY),
    };
    /**
     @{
     @name Properties
     @brief @~english @~chinese 属性
     */

    /** 
     @property
     @~english Default tag used for all the nodes 
     @~chinese 用于所有的节点的默认Tag
     @static
     @const 
     */
    static const int INVALID_TAG = -1;

    /// @} end of properties

    /**
     @{
     @name Constructor, Destructor and Initializers
     @brief @~english 
     @~chinese 构造函数，析构函数和初始化函数
     */

    /**
     * @~english Allocates and initializes a node.
     * @~chinese 分配并且初始化一个节点.
     * @return @~english A initialized node which is marked as "autorelease".
     * @~chinese 一个初始化的节点，该节点会自动被标记为“autorelease”(自动释放).
     */
    static Node * create();

    /**
     * @~english Gets the description string. It makes debugging easier.
     * @~chinese 得到描述性的字符串。这将会使得调试更加简单。
     * @return @~english A string @~chinese 一个字符串
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

    /// @} end of initializers



    /**
     @{
     @name Setters & Getters for Graphic Peroperties
     @brief @~english 
     @~chinese 图形属性值的获取函数和设置函数
     */

    /**
     @~english LocalZOrder is the 'key' used to sort the node relative to its siblings.

     The Node's parent will sort all its children based ont the LocalZOrder value.
     If two nodes have the same LocalZOrder, then the node that was added first to the children's array will be in front of the other node in the array.
     
     Also, the Scene Graph is traversed using the "In-Order" tree traversal algorithm ( http://en.wikipedia.org/wiki/Tree_traversal#In-order )
     And Nodes that have LocalZOder values < 0 are the "left" subtree
     While Nodes with LocalZOder >=0 are the "right" subtree.
     
     @~chinese LocalZOrder是“key”(关键)来分辨节点和它兄弟节点的相关性。
     父节点将会通过LocalZOrder的值来分辨所有的子节点。
     如果两个节点有同样的LocalZOrder,那么先加入子节点数组的节点将会显示在后加入的节点的前面。
     
     同样的，场景图使用“In-Order（按顺序）”遍历数算法来遍历 ( http://en.wikipedia.org/wiki/Tree_traversal#In-order )
     并且拥有小于0的LocalZOrder的值的节点是“left”子树（左子树）
     所以拥有大于0的LocalZOrder的值得节点是“right”子树（右子树）
     
     @see `setGlobalZOrder`
     @see `setVertexZ`
     *
     * @param localZOrder @~english The local Z order value.
     * @~chinese 相邻节点中的顺序值
     */
    virtual void setLocalZOrder(int localZOrder);

    CC_DEPRECATED_ATTRIBUTE virtual void setZOrder(int localZOrder) { setLocalZOrder(localZOrder); }
    
    /* 
     @~english Helper function used by `setLocalZOrder`. Don't use it unless you know what you are doing.
     @~chinese `setLocalZOrder`使用的辅助函数。不要使用它除非你知道你在干什么。
     @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void _setLocalZOrder(int z);

    /**
     * @~english Gets the local Z order of this node.
     * @~chinese 得到这个节点的局部Z顺序
     *
     * @see `setLocalZOrder(int)`
     *
     * @return @~english The local (relative to its siblings) Z order. @~chinese 局部Z轴顺序(相对于兄弟节点)。
     */
    virtual int getLocalZOrder() const { return _localZOrder; }
    CC_DEPRECATED_ATTRIBUTE virtual int getZOrder() const { return getLocalZOrder(); }

    /**
     
     @~english Defines the oder in which the nodes are renderer.
     Nodes that have a Global Z Order lower, are renderer first.
     
     In case two or more nodes have the same Global Z Order, the oder is not guaranteed.
     The only exception if the Nodes have a Global Z Order == 0. In that case, the Scene Graph order is used.
     
     By default, all nodes have a Global Z Order = 0. That means that by default, the Scene Graph order is used to render the nodes.
     
     Global Z Order is useful when you need to render nodes in an order different than the Scene Graph order.
     
     Limitations: Global Z Order can't be used used by Nodes that have SpriteBatchNode as one of their acenstors.
     And if ClippingNode is one of the ancestors, then "global Z order" will be relative to the ClippingNode.
     @~chinese 定义渲染节点的顺序
     拥有全局Z顺序越小的节点，最先渲染
     
     假设两个或者更多的节点拥有相同的全局Z顺序，那么渲染顺序无法保证。
     唯一的例外是如果节点的全局Z顺序为零，那么场景图顺序是可以使用的。 
     
     默认的，所有的节点全局Z顺序都是零。这就是说，默认使用场景图顺序来渲染节点。
     
     全局Z顺序是非常有用的当你需要渲染节点按照不同的顺序而不是场景图顺序。
     
     局限性: 全局Z顺序不能够被拥有继承“SpriteBatchNode”的节点使用。
     并且如果“ClippingNode”是其中之一的上代，那么“global Z order” 将会和“ClippingNode”有关。

     @see `setLocalZOrder()`
     @see `setVertexZ()`

     @since v3.0
     *
     * @param globalZOrder @~english The global Z order value. @~chinese 全局Z轴顺序
     */
    virtual void setGlobalZOrder(float globalZOrder);
    /**
     * @~english Returns the Node's Global Z Order.
     * @~chinese 返回节点的全局Z顺序。
     *
     * @see `setGlobalZOrder(int)`
     *
     * @return @~english The node's global Z order @~chinese 节点的全局Z轴顺序
     */
    virtual float getGlobalZOrder() const { return _globalZOrder; }

    /**
     * @~english Sets the scale (x) of the node.
     *
     * It is a scaling factor that multiplies the width of the node and its children.
     * @~chinese 设置节点的缩放（x）。
     * 
     * 它是一个缩放因子，将会乘以节点的宽以及它的子节点。
     *
     * @param scaleX   @~english The scale factor on X axis. @~chinese X轴的缩放因子. 
     *
     * @warning @~english The physics body doesn't support this. @~chinese 物理节点不支持这个API 
     */
    virtual void setScaleX(float scaleX);
    /**
     * @~english Returns the scale factor on X axis of this node
     * @~chinese 返回该节点的X轴的缩放因子。
     *
     * @see setScaleX(float)
     *
     * @return @~english The scale factor on X axis. @~chinese X轴的缩放因子。
     */
    virtual float getScaleX() const;


    /**
     * @~english Sets the scale (y) of the node.
     *
     * It is a scaling factor that multiplies the height of the node and its children.
     * @~chinese 设置节点的缩放（y）。
     *
     * 它是一个缩放因子，将会乘以节点的宽以及它的子节点。
     *
     * @param scaleY   @~english The scale factor on Y axis. @~chinese Y轴的缩放因子
     *
     * @warning @~english The physics body doesn't support this. @~chinese 物理节点不支持这个API
     */
    virtual void setScaleY(float scaleY);
    /**
     * @~english Returns the scale factor on Y axis of this node
     * @~chinese 返回该节点的Y轴的缩放因子。
     *
     * @see `setScaleY(float)`
     *
     * @return @~english The scale factor on Y axis. @~chinese Y轴的缩放因子
     */
    virtual float getScaleY() const;

    /**
     * @~english Changes the scale factor on Z axis of this node
     *
     * The Default value is 1.0 if you haven't changed it before.
     * @~chinese 改变该节点的Z轴的缩放因子。
     *
     * 如果你之前没有改变过它，那么它的默认值是1.0。
     *
     * @param scaleZ   @~english The scale factor on Z axis. @~chinese Z轴的缩放因子 
     *
     * @warning @~english The physics body doesn't support this.@~chinese 物理节点不支持这个API 
     */
    virtual void setScaleZ(float scaleZ);
    /**
     * @~english Returns the scale factor on Z axis of this node
     * @~chinese 返回该节点的Z轴的缩放因子。
     *
     * @see `setScaleZ(float)`
     *
     * @return @~english The scale factor on Z axis. @~chinese Z轴的缩放因子。 
     */
    virtual float getScaleZ() const;


    /**
     * @~english Sets the scale (x,y,z) of the node.
     *
     * It is a scaling factor that multiplies the width, height and depth of the node and its children.
     * @~chinese 设置几点的缩放（x,y,z）.
     *
     * 缩放因子将会乘以该节点和它子节点的宽，高和深度。
     *
     * @param scale     @~english The scale factor for X, Y and Z axis. @~chinese X,Y,Z轴的缩放因子 
     *
     * @warning @~english The physics body doesn't support this. @~chinese 物理节点不支持这个API 
     */
    virtual void setScale(float scale);
    /**
     * @~english Gets the scale factor of the node,  when X and Y have the same scale factor.
     * @~chinese 得到该节点的缩放因子，当X轴和Y轴有相同的缩放因子时。
     *
     * @warning @~english Assert when `_scaleX != _scaleY` @~chinese 判断 当 `_scaleX != _scaleY` 
     * @see setScale(float)
     *
     * @return @~english The scale factor of the node. @~chinese 该节点的缩放因子 
     */
    virtual float getScale() const;

    /**
     * @~english Sets the scale (x,y) of the node.
     *
     * It is a scaling factor that multiplies the width and height of the node and its children.
     * @~chinese 设置节点的缩放（x,y）.
     *
     * 缩放因子乘以该节点和它子节点的宽与高。
     *
     * @param scaleX     @~english The scale factor on X axis. @~chinese X轴的缩放因子。 
     * @param scaleY     @~english The scale factor on Y axis. @~chinese Y轴的缩放因子。 
     *
     * @warning @~english The physics body doesn't support this. @~chinese 物理节点不支持这个API 
     */
    virtual void setScale(float scaleX, float scaleY);

    /**
     * @~english Sets the position (x,y) of the node in its parent's coordinate system.
     *
     * Usually we use `Vec2(x,y)` to compose Vec2 object.
     * This code snippet sets the node in the center of screen.
     * @~chinese 设置节点的位置在父节点的坐标系系统中。
     *
     * 通常我们使用`Vec2(x,y)` 来组成 Vec2 对象。
     * 这一段代码设置节点在屏幕中间。
     *
     @code
     Size size = Director::getInstance()->getWinSize();
     node->setPosition(size.width/2, size.height/2);
     @endcode
     *
     * @param position  @~english The position (x,y) of the node in OpenGL coordinates. @~chinese 这个节点的位置（x,y）在OpenGL坐标系中。 
     */
    virtual void setPosition(const Vec2 &position);

    /** @~chinese 设置归一化位置坐标(x, y)，使用从0到1的归一化值
    最终像素位置按照如下的逻辑进行转换：
    @~english Sets the position (x,y) using values between 0 and 1.
     The positions in pixels is calculated like the following:

     @code
     // pseudo code
     void setNormalizedPosition(Vec2 pos) {
       Size s = getParent()->getContentSize();
       _position = pos * s;
     }
     @endcode
     *
     * @param position @~english The normalized position (x,y) of the node, using value between 0 and 1. @~chinese 归一化的位置坐标 
     */
    virtual void setNormalizedPosition(const Vec2 &position);

    /**
     * @~english Gets the position (x,y) of the node in its parent's coordinate system.
     * @~chinese 得到在父节点坐标系中节点的位置（x,y）。
     *
     * @see setPosition(const Vec2&)
     *
     * @code
     * In js and lua return value is table which contains x,y.
     * @endcode
     * @return @~english The position (x,y) of the node in OpenGL coordinates. @~chinese 节点在OpenGL坐标系中的位置（x,y)。 
     */
    virtual const Vec2& getPosition() const;

    /** @~english Returns the normalized position.
     * @~chinese 得到在父节点坐标系中节点归一化的位置（x,y）。
     * 
     * @return @~english The normalized position. @~chinese 归一化位置 
     */
    virtual const Vec2& getNormalizedPosition() const;

    /**
     * @~english Sets the position (x,y) of the node in its parent's coordinate system.
     *
     * Passing two numbers (x,y) is much efficient than passing Vec2 object.
     * This method is bound to Lua and JavaScript.
     * Passing a number is 10 times faster than passing a object from Lua to c++.
     * @~chinese 设置节点在它父节点坐标系中的位置（x,y）。
     *
     * 传递两个数字（x,y）比传递Vec2对象更有效率。
     * 这个方法在Lua和JavaScript绑定环境下，
     * 从脚本到C++传递一个数字比传递一个对象快10倍。
     *
     @code
     // sample code in Lua
     local pos  = node::getPosition()  -- returns Vec2 object from C++.
     node:setPosition(x, y)            -- pass x, y coordinate to C++.
     @endcode
     *
     * @param x     @~english X coordinate for position. @~chinese X轴位置 
     * @param y     @~english Y coordinate for position. @~chinese Y轴位置 
     */
    virtual void setPosition(float x, float y);
    /**
     * @~english Gets position in a more efficient way, returns two number instead of a Vec2 object.
     * @~chinese 用一个更有效率的方法获取位置，通过指针参数传递两个数字而不是Vec2对象。
     *
     * @see `setPosition(float, float)`
     *
     * @param x @~english To receive x coordinate for position. @~chinese 用来获取X轴位置的参数 
     * @param y @~english To receive y coordinate for position. @~chinese 用来获取Y轴位置的参数 
     */
    virtual void getPosition(float* x, float* y) const;
    /** @~english Sets the x coordinate of the node in its parent's coordinate system.
     * @~chinese 设置节点在父节点坐标系下的X轴位置
     *
     * @param x @~english The x coordinate of the node. @~chinese X轴坐标 
     */
    virtual void  setPositionX(float x);
    /** @~english Gets the x coordinate of the node in its parent's coordinate system.
     * @~chinese 获取节点在父节点坐标系下的X轴位置
     *
     * @return @~english The x coordinate of the node. @~chinese X轴坐标 
     */
    virtual float getPositionX(void) const;
    /** @~english Sets the y coordinate of the node in its parent's coordinate system.
     * @~chinese 设置节点在父节点坐标系下的Y轴位置
     *
     * @param y @~english The y coordinate of the node. @~chinese Y轴坐标 
     */
    virtual void  setPositionY(float y);
    /** @~english Gets the y coordinate of the node in its parent's coordinate system.
     * @~chinese 获取节点在父节点坐标系下的Y轴位置
     *
     * @return @~english The y coordinate of the node. @~chinese Y轴坐标 
     */
    virtual float getPositionY(void) const;

    /**
     * @~english Sets the position (X, Y, and Z) in its parent's coordinate system.
     * @~chinese 设置节点在父节点坐标系中的位置（x,y,z）。
     * 
     * @param @~english position The position (X, Y, and Z) in its parent's coordinate system. @~chinese 节点在父节点坐标系中的位置（x,y,z） 
     * @js NA
     */
    virtual void setPosition3D(const Vec3& position);
    /**
     * @~english Returns the position (X,Y,Z) in its parent's coordinate system.
     * @~chinese 获取节点在父坐标系的位置（X,Y,Z）。
     *
     * @return @~english The position (X, Y, and Z) in its parent's coordinate system. @~chinese 节点在父坐标系的位置（X,Y,Z） 
     * @js NA
     */
    virtual Vec3 getPosition3D() const;

    /**
     * @~english Sets the 'z' coordinate in the position. It is the OpenGL Z vertex value.
     *
     * The OpenGL depth buffer and depth testing are disabled by default. You need to turn them on.
     * In order to use this property correctly.
     *
     * `setPositionZ()` also sets the `setGlobalZValue()` with the positionZ as value.
     * @~chinese 设置位置的“z”轴坐标系，是OpneGL Z位置。
     *
     * OpenGL深度缓存和深度测试默认值是关闭的，你需要打开它们
     * 来正确的使用这个属性。
     *
     * `setPositionZ()` 同样设置 `setGlobalZValue()` 用“positionZ” 作为值。
     *
     * @see `setGlobalZValue()`
     *
     * @param positionZ  @~english OpenGL Z vertex of this node. @~chinese 该节点的OpenGL Z位置 
     * @js setVertexZ
     */
    virtual void setPositionZ(float positionZ);
    CC_DEPRECATED_ATTRIBUTE virtual void setVertexZ(float vertexZ) { setPositionZ(vertexZ); }

    /**
     * @~english Gets position Z coordinate of this node.
     * @~chinese 得到该节点的Z轴坐标系的位置。
     *
     * @see setPositionZ(float)
     *
     * @return @~english The position Z coordinate of this node. @~chinese 该节点的Z轴坐标系。 
     * @js getVertexZ
     */
    virtual float getPositionZ() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getVertexZ() const { return getPositionZ(); }

    /**
     * @~english Changes the X skew angle of the node in degrees.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality
     * while the second one uses the real skew function.
     *
     * This angle describes the shear distortion in the X direction.
     * Thus, it is the angle between the Y coordinate and the left edge of the shape
     * The default skewX angle is 0. Positive values distort the node in a CW direction.
     * @~chinese 改变该节点X轴的倾斜角，单位是度。
     *
     * `setRotationalSkew()`和 `setSkew()` 的不同时是前一个模拟Flash的倾斜功能。
     * 然而后一个使用真正的倾斜功能。
     *
     * 这个角度描述了在X轴方向的切形变（shear distortion）。
     * 因此，这个角度在Y轴和图形左边之间。
     * 默认值skewX角度是0，负值使该节点按顺时针变形。
     *
     * @param skewX @~english The X skew angle of the node in degrees. @~chinese 该节点的X轴的倾斜角。 
     *
     * @warning @~english The physics body doesn't support this. @~chinese 物理节点不支持这个API 
     */
    virtual void setSkewX(float skewX);
    /**
     * @~english Returns the X skew angle of the node in degrees.
     * @~chinese 返回该节点的X轴倾斜角，单位是度。
     *
     * @see `setSkewX(float)`
     *
     * @return @~english The X skew angle of the node in degrees. @~chinese 该节点的X轴倾斜角。 
     */
    virtual float getSkewX() const;


    /**
     * @~english Changes the Y skew angle of the node in degrees.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality
     * while the second one uses the real skew function.
     *
     * This angle describes the shear distortion in the Y direction.
     * Thus, it is the angle between the X coordinate and the bottom edge of the shape.
     * The default skewY angle is 0. Positive values distort the node in a CCW direction.
     * @~chinese 改变该节点Y轴的倾斜角，单位是度。
     *
     * `setRotationalSkew()`和 `setSkew()` 的不同时是前一个模拟Flash的倾斜功能。
     * 然而后一个使用真正的倾斜功能。
     *
     * 这个角度描述了在Y轴方向的切形变（shear distortion）。
     *  因此，这个角度在X轴和图形底边之间。
     * 默认值skewY角度是0，负值使该节点按顺时针变形。
     *
     * @param skewY    @~english The Y skew angle of the node in degrees. @~chinese 该节点的Y轴的倾斜角。 
     *
     * @warning @~english The physics body doesn't support this. @~chinese 物理节点不支持这个API 
     */
    virtual void setSkewY(float skewY);
    /**
     * @~english Returns the Y skew angle of the node in degrees.
     * @~chinese 返回该节点的Y轴倾斜角，单位是度。
     *
     * @see `setSkewY(float)`
     *
     * @return @~english The Y skew angle of the node in degrees. @~chinese 该节点的Y轴倾斜角。 
     */
    virtual float getSkewY() const;


    /**
     * @~english Sets the anchor point in percent.
     *
     * anchorPoint is the point around which all transformations and positioning manipulations take place.
     * It's like a pin in the node where it is "attached" to its parent.
     * The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the top-right corner.
     * But you can use values higher than (1,1) and lower than (0,0) too.
     * The default anchorPoint is (0.5,0.5), so it starts in the center of the node.
     * @~chinese 设置锚点，用百分比表示。
     *
     * 一个锚点是所有的转换和定位操作发生的点。
     * 它就像在节点上连接其父类的大头针。
     * 锚点是标准化的，就像百分比一样。(0,0)表示左下角，(1,1)表示右上角。
     * 但是你可以使用比（1,1,）更高的值或者比（0,0）更低的值。
     * 默认的锚点是（0.5,0.5），因此它开始于节点的中心位置。
     * @note @~english If node has a physics body, the anchor must be in the middle, you cann't change this to other value. @~chinese 如果节点有物理体，锚点必须在中心，你不能够这个值。 
     *
     * @param anchorPoint   @~english The anchor point of node. @~chinese 节点的锚点。 
     */
    virtual void setAnchorPoint(const Vec2& anchorPoint);
    /**
     * @~english Returns the anchor point in percent.
     * @~chinese 返回用百分比表示的锚点。
     *
     * @see `setAnchorPoint(const Vec2&)`
     *
     * @return @~english The anchor point of node. @~chinese 节点的锚点 
     */
    virtual const Vec2& getAnchorPoint() const;
    /**
     * @~english Returns the anchorPoint in absolute pixels.
     * @~chinese 返回锚点的绝对像素位置
     *
     * @warning @~english You can only read it. If you wish to modify it, use anchorPoint instead. @~chinese 你只能够读取它，如果你想修改它，使用setAnchoPoint。 
     * @see `getAnchorPoint()`
     *
     * @return @~english The anchor point in absolute pixels. @~chinese 绝对像素的锚点。 
     */
    virtual const Vec2& getAnchorPointInPoints() const;


    /**
     * @~english Sets the untransformed size of the node.
     *
     * The contentSize remains the same no matter the node is scaled or rotated.
     * All nodes has a size. Layer and Scene has the same size of the screen.
     * @~chinese 设置不转换节点的大小。
     *
     * contentSize依然是相同的，无论节点是缩放或者旋转。
     * 所有的节点都有大小。图层和场景有相同的屏幕大小。
     *
     * @param contentSize   @~english The untransformed size of the node. @~chinese 未转换节点的大小 
     */
    virtual void setContentSize(const Size& contentSize);
    /**
     * @~english Returns the untransformed size of the node.
     * @~chinese 返回节点未变形状态下的大小。
     *
     * @see `setContentSize(const Size&)`
     *
     * @return @~english The untransformed size of the node. @~chinese 节点未变形状态下的大小 
     */
    virtual const Size& getContentSize() const;


    /**
     * @~english Sets whether the node is visible.
     *
     * The default value is true, a node is default to visible.
     * @~chinese 设置节点是否可见。
     *
     * 默认值是true,一个节点默认是可见的。
     *
     * @param visible   @~english true if the node is visible, false if the node is hidden. @~chinese true 如果节点是可见的，false 如果节点是隐藏的。 
     */
    virtual void setVisible(bool visible);
    /**
     * @~english Determines if the node is visible.
     * @~chinese 判断节点是否可见。
     *
     * @see `setVisible(bool)`
     *
     * @return @~english true if the node is visible, false if the node is hidden. @~chinese true 如果节点是可见的, false 如果节点是隐藏的。 
     */
    virtual bool isVisible() const;


    /**
     * @~english Sets the rotation (angle) of the node in degrees.
     *
     * 0 is the default rotation angle.
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     * @~chinese 设置节点的旋转（angle）角度。
     *
     * 0 是默认的旋转角度。
     * 负数顺时针旋转节点，正数逆时针旋转节点。
     *
     * @param rotation     @~english The rotation of the node in degrees. @~chinese 节点的旋转角度。 
     */
    virtual void setRotation(float rotation);
    /**
     * @~english Returns the rotation of the node in degrees.
     * @~chinese 返回节点的旋转角度。
     *
     * @see `setRotation(float)`
     *
     * @return @~english The rotation of the node in degrees. @~chinese 节点的旋转角度。 
     */
    virtual float getRotation() const;

    /**
     * @~english Sets the rotation (X,Y,Z) in degrees.
     * Useful for 3d rotations.
     * @~chinese 设置（X,Y,Z）旋转角度。
     * 对3d旋转非常有用。
     *
     * @warning @~english The physics body doesn't support this. @~chinese 物理节点不支持这个API 
     *
     * @param rotation @~english The rotation of the node in 3d. @~chinese 3D空间中的旋转角度 
     * @js NA
     */
    virtual void setRotation3D(const Vec3& rotation);
    /**
     * @~english Returns the rotation (X,Y,Z) in degrees.
     * @~chinese 获取（X,Y,Z）的旋转角度。
     * 
     * @return @~english The rotation of the node in 3d. @~chinese 3D空间中的旋转角度 
     * @js NA
     */
    virtual Vec3 getRotation3D() const;
    
    /**
     * @~english Set rotation by quaternion.
     * @~chinese 通过四元数来设置3D空间中的旋转角度
     *
     * @param quat @~english The rotation in quaternion. @~chinese 四元数对象 
     * @js NA
     */
    virtual void setRotationQuat(const Quaternion& quat);
    
    /**
     * @~english Return the rotation by quaternion, Note that when _rotationZ_X == _rotationZ_Y, the returned quaternion equals to RotationZ_X * RotationY * RotationX,
     * @~chinese 获取四元数表达的3D空间旋转角度，当`_rotationZ_X == _rotationZ_Y`的时候，四元数值等于`RotationZ_X * RotationY * RotationX`，否则值等于`RotationY * RotationX`。
     * it equals to RotationY * RotationX otherwise.
     *
     * @return @~english The rotation in quaternion. @~chinese 四元数对象 
     * @js NA
     */
    virtual Quaternion getRotationQuat() const;

    /**
     * @~english Sets the X rotation (angle) of the node in degrees which performs a horizontal rotational skew.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality,
     * while the second one uses the real skew function.
     *
     * 0 is the default rotation angle.
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     * @~chinese 设置节点X轴的旋转角度，表现为水平旋转倾斜。
     *
     * `setRotationalSkew()` 和 `setSkew()`的不同是前一个是模拟Flash的倾斜功能
     * 然而后一个使用真正的倾斜功能。
     *
     * 0 是默认的旋转角度。
     * 负数节点顺时针旋转，正数节点逆时针旋转。
     *
     * @param rotationX    @~english The X rotation in degrees which performs a horizontal rotational skew. @~chinese X轴的旋转角度表现为水平旋转倾斜。 
     *
     * @warning @~english The physics body doesn't support this. @~chinese 物理节点不支持这个API 
     * @js setRotationX
     */
    virtual void setRotationSkewX(float rotationX);
    CC_DEPRECATED_ATTRIBUTE virtual void setRotationX(float rotationX) { return setRotationSkewX(rotationX); }

    /**
     * @~english Gets the X rotation (angle) of the node in degrees which performs a horizontal rotation skew.
     * @~chinese 得到X轴节点的旋转角度，表现为水平旋转倾斜（horizontal rotation skew）.
     *
     * @see `setRotationSkewX(float)`
     *
     * @return @~english The X rotation in degrees. @~chinese X轴的旋转角度。 
     * @js getRotationX 
     */
    virtual float getRotationSkewX() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getRotationX() const { return getRotationSkewX(); }

    /**
     * @~english Sets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
     *
     * The difference between `setRotationalSkew()` and `setSkew()` is that the first one simulate Flash's skew functionality,
     * while the second one uses the real skew function.
     *
     * 0 is the default rotation angle.
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     * @~chinese 设置Y轴节点的旋转角度，表现为垂直旋转倾斜。
     *
     * `setRotationalSkew()` 和`setSkew()` 的不同是前一个使用Flash倾斜功能
     * 后一个使用了真正的倾斜功能。
     *
     * 0 默认的旋转角度。
     * 负数表示顺时针旋转，正数表示逆时针旋转。
     *
     * @param rotationY    @~english The Y rotation in degrees. @~chinese Y轴的旋转角度。 
     *
     * @warning @~english The physics body doesn't support this. @~chinese 物理节点不支持这个API 
     * @js setRotationY
     */
    virtual void setRotationSkewY(float rotationY);
    CC_DEPRECATED_ATTRIBUTE virtual void setRotationY(float rotationY) { return setRotationSkewY(rotationY); }

    /**
     * @~english Gets the Y rotation (angle) of the node in degrees which performs a vertical rotational skew.
     * @~chinese 得到节点Y轴的旋转角度，表现为垂直旋转倾斜（vertical rotational skew.）
     *
     * @see `setRotationSkewY(float)`
     *
     * @return @~english The Y rotation in degrees. @~chinese Y轴旋转角度。 
     * @js getRotationY
     */
    virtual float getRotationSkewY() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getRotationY() const { return getRotationSkewY(); }

    /**
     * @~english Sets the arrival order when this node has a same ZOrder with other children.
     *
     * A node which called addChild subsequently will take a larger arrival order,
     * If two children have the same Z order, the child with larger arrival order will be drawn later.
     * @~chinese 设置到达顺序，当这个节点和其他子节点有相同的ZOrder时。
     *
     * 一个调用了之后调用了addChild函数的节点将会有更大的到达顺序值，
     * 如果两个子对象有相同的Z轴顺序，这个有更大到达顺序的子类将会后画。
     *
     * @warning @~english This method is used internally for localZOrder sorting, don't change this manually @~chinese 这个方法在内部被用于localZOrder排序，不能手动的改变。
     *
     * @param orderOfArrival   @~english The arrival order. @~chinese 到达顺序。 
     */
    void setOrderOfArrival(int orderOfArrival);
    /**
     * @~english Returns the arrival order, indicates which children is added previously.
     * @~chinese 返回到达顺序，指出哪一个子类先被添加。
     *
     * @see `setOrderOfArrival(unsigned int)`
     *
     * @return @~english The arrival order. @~chinese 到达顺序。 
     */
    int getOrderOfArrival() const;


    /** @deprecated No longer needed
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE void setGLServerState(int serverState) { /* ignore */ };
    /** @deprecated No longer needed
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE int getGLServerState() const { return 0; }

    /**
     * @~english Sets whether the anchor point will be (0,0) when you position this node.
     *
     * This is an internal method, only used by Layer and Scene. Don't call it outside framework.
     * The default value is false, while in Layer and Scene are true.
     * @~chinese 设置抹点为（0,0）当你摆放这个节点的时候。
     *
     * 这是一个内部方法，仅仅被Layer和Scene使用。不要在框架外调用。
     * 默认值是false,但是在Layer和Scene中是true.
     *
     * @param ignore    @~english true if anchor point will be (0,0) when you position this node. @~chinese true 如果锚点是（0,0）当你摆放这个节点的时候。 
     * @todo @~english This method should be renamed as setIgnoreAnchorPointForPosition(bool) or something with "set".
     * @~chinese 这个方法应该被命名为setIgnoreAnchorPointForPosition(bool) 或者其他的有“set”的名称。
     */
    virtual void ignoreAnchorPointForPosition(bool ignore);
    /**
     * @~english Gets whether the anchor point will be (0,0) when you position this node.
     * @~chinese 得到节点的锚点是否为（0,0），当你摆放这个节点时。
     *
     * @see `ignoreAnchorPointForPosition(bool)`
     *
     * @return @~english true if the anchor point will be (0,0) when you position this node. @~chinese 如果锚点是 (0,0) 当你摆放这个节点时返回true。 
     */
    virtual bool isIgnoreAnchorPointForPosition() const;

    /// @}  end of Setters & Getters for Graphic Properties


    /// @{
    /// @name Children and Parent
    /// @brief @~english @~chinese 父子节点关系

    /**
     * @~english Adds a child to the container with z-order as 0.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     * @~chinese 添加一个子节点到容器内，z-order是0.
     *
     * 如果子节点被添加到了一个“running（活动着的）”节点，那么'onEnter'喝 'onEnterTransitionDidFinish' 将会立即调用。
     *
     * @param child     @~english A child node. @~chinese 一个子节点。 
     */
    virtual void addChild(Node * child);
    /**
     * @~english Adds a child to the container with a local z-order.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     * @~chinese 添加一个子节点到容器中，参数有一个局部Z轴顺序。
     *
     * 如果子节点被添加到了一个“running（活动着的）”节点，那么'onEnter'喝 'onEnterTransitionDidFinish' 将会立即调用。
     *
     * @param child         @~english A child node. @~chinese 一个子节点。 
     * @param localZOrder   @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`. @~chinese Z轴顺序为了绘画的优先权。 请参考 `setLocalZOrder(int)` 
     */
    virtual void addChild(Node * child, int localZOrder);
    /**
     * @~english Adds a child to the container with z order and tag.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     * @~chinese 添加一个子节点到容器中，有Z轴顺序和一个标记。
     *
     * 如果子节点被添加到了一个“running（活动着的）”节点，那么'onEnter'喝 'onEnterTransitionDidFinish' 将会立即调用。
     *
     * @param child         @~english A child node. @~chinese 一个子节点 
     * @param localZOrder   @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`. @~chinese Z轴顺序为了绘画的优先权。 请参考 `setLocalZOrder(int)` 
     * @param tag           @~english An integer to identify the node easily. Please refer to `setTag(int)`. @~chinese 一个用来更容易分辨节点的整数。请参考 `setTag(int)` 
     * 
     * @~english Please use `addChild(Node* child, int localZOrder, const std::string &name)` instead.
     * @~chinese 请使用`addChild(Node* child, int localZOrder, const std::string &name)`
     */
     virtual void addChild(Node* child, int localZOrder, int tag);
    /**
     * @~english Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     * @~chinese 添加一个子节点到容器中，参数有一个局部Z轴顺序。
     *
     * 如果子节点被添加到了一个“running（活动着的）”节点，那么'onEnter'喝 'onEnterTransitionDidFinish' 将会立即调用。
     *
     * @param child     @~english A child node. @~chinese 一个子节点。 
     * @param localZOrder    @~english Z order for drawing priority. Please refer to `setLocalZOrder(int)`. @~chinese Z轴顺序为了绘画的优先权。 请参考 `setLocalZOrder(int)` 
     * @param name      @~english A string to identify the node easily. Please refer to `setName(int)`. @~chinese 一个用来标记节点的名字，请参考`setName(int)` 
     *
     */
    virtual void addChild(Node* child, int localZOrder, const std::string &name);
    /**
     * @~english Gets a child from the container with its tag.
     * @~chinese 从容器中通过标记得到对应的子节点。
     *
     * @param tag   @~english An identifier to find the child node. @~chinese 一个标识符用于找到子节点。 
     *
     * @return @~english A node object whose tag equals to the input parameter. @~chinese 一个标记与输入的参数相同的节点对象。 
     *
     * Please use `getChildByName()` instead.
     */
     virtual Node * getChildByTag(int tag) const;
    /**
     * @~english Gets a child from the container with its name.
     * @~chinese 从容器中通过名字得到对应的子节点。
     *
     * @param name   @~english An identifier to find the child node. @~chinese 一个名字用于找到子节点。 
     *
     * @return @~english A node object whose name equals to the input parameter. @~chinese 一个名字与输入的参数相同的节点对象。 
     *
     * @since v3.2
     */
    virtual Node* getChildByName(const std::string& name) const;
    /**
     * @~english Gets a child from the container with its name that can be cast to Type T.
     * @~chinese 通过名字获得一个子节点对象，并且这个节点对象可以被转换为类型T。
     *
     * @param name   @~english An identifier to find the child node. @~chinese 一个名字用于找到子节点。 
     *
     * @return @~english A node with the given name that can be cast to Type T. @~chinese 一个名字与输入的参数相同并且可以被转换为类型T的节点对象。 
    */
    template <typename T>
    inline T getChildByName(const std::string& name) const { return static_cast<T>(getChildByName(name)); }
    /** 
     * @~english Search the children of the receiving node to perform processing for nodes which share a name.
     * @~chinese 在子节点中寻找匹配名字或正则表达式的节点并对这些节点执行回调函数。
     *
     * @param name @~english The name to search for, supports c++11 regular expression.
     * @~chinese 用于搜索的搜索字符串，支持C++11正则表达式
     *
     * @~english Search syntax options:
     * - `//`: Can only be placed at the begin of the search string. This indicates that it will search recursively.
     * - `..`: The search should move up to the node's parent. Can only be placed at the end of string.
     * - `/` : When placed anywhere but the start of the search string, this indicates that the search should move to the node's children.
     * @code
     * enumerateChildren("//MyName", ...): This searches the children recursively and matches any node with the name `MyName`.
     * enumerateChildren("[[:alnum:]]+", ...): This search string matches every node of its children.
     * enumerateChildren("A[[:digit:]]", ...): This searches the node's children and returns any child named `A0`, `A1`, ..., `A9`.
     * enumerateChildren("Abby/Normal", ...): This searches the node's grandchildren and returns any node whose name is `Normal`
     * and whose parent is named `Abby`.
     * enumerateChildren("//Abby/Normal", ...): This searches recursively and returns any node whose name is `Normal` and whose
     * parent is named `Abby`.
     * @endcode
     * 
     * @~chinese 搜索语法说明:
     * - `//`: 当搜索字符串以两个斜杠开头的时候，搜索会递归进行，搜索当前节点的整个子节点树。
     * - `..`: 当搜索字符串以两个点结束的时候，搜索会查询当前节点的父节点
     * - `/` : 当搜索字符串内部（不在开头）包含单个斜杠，它将搜索指向其子节点
     * @code
     * enumerateChildren("//MyName", ...): 查询整个子节点树并匹配所有名字为`MyName`的节点。
     * enumerateChildren("[[:alnum:]]+", ...): 这个正则表达式将匹配所有有名字的直接子节点。
     * enumerateChildren("A[[:digit:]]", ...): 这个正则表达式将匹配所有名字为`A0`, `A1`, ..., `A9`的子节点。
     * enumerateChildren("Abby/Normal", ...): 匹配名为Abby的直接子节点的名为Normal的子节点。
     * enumerateChildren("//Abby/Normal", ...): 查询整个子节点树并匹配所有名字为Normal并且父节点名字为Abby的节点。
     * @endcode
     *
     * @warning @~english Only support alphabet or number for name, and not support unicode.
     * @~chinese name参数只支持字母或数字，不支持unicode字符
     *
     * @param callback @~english A callback function to execute on nodes that match the `name` parameter. The function takes the following arguments:
     *  `node` 
     *      A node that matches the name
     *  And returns a boolean result. Your callback can return `true` to terminate the enumeration.
     * @~chinese 回调函数，所有匹配到的节点都会被这个回调函数执行，这个回调函数的参数是`node`：匹配到的节点。并且返回一个布尔值。
     * 开发者可以在自己定义的回调函数中返回`true`来终结enumerateChildren的搜索过程
     * @since v3.2
     */
    virtual void enumerateChildren(const std::string &name, std::function<bool(Node* node)> callback) const;
    /**
     * @~english Returns the array of the node's children.
     * @~chinese 返回所有子节点的数组。
     *
     * @return @~english the array the node's children. @~chinese 子节点数组。 
     */
    virtual Vector<Node*>& getChildren() { return _children; }
    virtual const Vector<Node*>& getChildren() const { return _children; }
    
    /** 
     * @~english Returns the amount of children.
     * @~chinese 返回子节点的总数
     *
     * @return @~english The amount of children. @~chinese 子节点的总数 
     */
    virtual ssize_t getChildrenCount() const;

    /**
     * @~english Sets the parent node.
     * @~chinese 设置节点的父节点
     *
     * @param parent    @~english A pointer to the parent node. @~chinese 指向父节点的指针。 
     */
    virtual void setParent(Node* parent);
    /**
     * @~english Returns a pointer to the parent node.
     * @~chinese 返回指向父节点的指针。
     *
     * @see `setParent(Node*)`
     *
     * @returns @~english A pointer to the parent node. @~chinese 指向父节点的指针。 
     */
    virtual Node* getParent() { return _parent; }
    virtual const Node* getParent() const { return _parent; }


    ////// REMOVES //////

    /**
     * @~english Removes this node itself from its parent node with a cleanup.
     * If the node orphan, then nothing happens.
     * @~chinese 从父节点中删除一个节点，有一个cleanup参数。
     * 如果这个节点是一个孤节点，那么什么都不会发生。
     * @see `removeFromParentAndCleanup(bool)`
     */
    virtual void removeFromParent();
    /**
     * @~english Removes this node itself from its parent node.
     * If the node orphan, then nothing happens.
     * @~chinese 从父节点中删除一个节点
     * 如果这个节点是一个孤节点，那么什么都不会发生。
     * @param cleanup   @~english true if all actions and callbacks on this node should be removed, false otherwise.
     * @~chinese true 在这个节点上所有的动作和回调都会被删除, false 就不会删除。
     * @js removeFromParent
     * @lua removeFromParent
     */
    virtual void removeFromParentAndCleanup(bool cleanup);

    /**
     * @~english Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
     * @~chinese 从容器中删除一个孩子，取决于cleanup参数，同时可能会清除所有的活动的动作。
     *
     * @param child     @~english The child node which will be removed. @~chinese 希望被删除的子节点。 
     * @param cleanup   @~english True if all running actions and callbacks on the child node will be cleanup, false otherwise.
     * @~chinese true 在这个节点上所有的动作和回调都会被删除, false 就不会删除。
     */
    virtual void removeChild(Node* child, bool cleanup = true);

    /**
     * @~english Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter.
     * @~chinese 从一个容器中删除一个孩子通过标记值。取决于cleanup参数同时会清除所有的活动的动作。
     *
     * @param tag       @~english An interger number that identifies a child node. @~chinese 一个用于识别子节点的整数。 
     * @param cleanup   @~english True if all running actions and callbacks on the child node will be cleanup, false otherwise.
     * @~chinese true 在这个节点上所有的动作和回调都会被删除， false 就不会删除。
     *
     * Please use `removeChildByName` instead.
     */
     virtual void removeChildByTag(int tag, bool cleanup = true);
    /**
     * @~english Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter.
     * @~chinese 通过名字删除一个节点，默认会删除所有动作。
     *
     * @param name      @~english A string that identifies a child node. @~chinese 用于标示节点的名字
     * @param cleanup   @~english True if all running actions and callbacks on the child node will be cleanup, false otherwise. 
     * @~chinese true 在这个节点上所有的动作和回调都会被删除， false 就不会删除。
     */
    virtual void removeChildByName(const std::string &name, bool cleanup = true);
    /**
     * @~english Removes all children from the container with a cleanup.
     * @~chinese 从容器中删除所有的孩子，并清除所有动作和回调。
     *
     * @see `removeAllChildrenWithCleanup(bool)`
     */
    virtual void removeAllChildren();
    /**
     * @~english Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     * @~chinese 从容器中删除所有的孩子, 取决于cleanup参数，同时可能会清除所有的活动的动作。
     *
     * @param cleanup   @~english True if all running actions on all children nodes should be cleanup, false oterwise.
     * @~chinese true 在这个节点上所有的动作和回调都会被删除, false 就不会删除。
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup);

    /**
     * @~english Reorders a child according to a new z value.
     * @~chinese 对一个孩子设定一个新的z轴值并重新排序。
     *
     * @param child     @~english An already added child node. It MUST be already added. @~chinese 一个已经被添加的子节点，它必须是已经添加的。 
     * @param localZOrder @~english Z order for drawing priority. Please refer to setLocalZOrder(int).
     * @~chinese Z轴顺序为了绘画优先级，请参考setLocalZOrder(int)。
     */
    virtual void reorderChild(Node * child, int localZOrder);

    /**
     * @~english Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This appraoch can improves the performance massively.
     * @~chinese 在绘画之前，排列所有的孩子数组一次，而不是每次添加或者删除子节点时都排序。
     * 这个方法可以大幅度地提高性能。
     * @note @~english Don't call this manually unless a child added needs to be removed in the same frame.
     * @~chinese 不要手动调用这个方法，除非一个添加过的子节点将要被删除在这个结构内。
     */
    virtual void sortAllChildren();

    /// @} end of Children and Parent
    
    /// @{
    /// @name Tag & User data
    /// @brief @~english @~chinese 标签和用户数据

    /**
     * @~english Returns a tag that is used to identify the node easily.
     * @~chinese 返回一个用来更简单分辨节点的标记。
     *
     * @return @~english An integer that identifies the node. @~chinese 一个分辨节点的整数。 
     *
     * Please use `getTag()` instead.
     */
     virtual int getTag() const;
    /**
     * @~english Changes the tag that is used to identify the node easily.
     *
     * Please refer to getTag for the sample code.
     * @~chinese 改变这个用来分辨节点的标记。
     *
     * 请参考 getTag 的相同代码。
     *
     * @param tag   @~english A integer that identifies the node. @~chinese 一个用来识别节点的整数。 
     *
     * Please use `setName()` instead.
     */
     virtual void setTag(int tag);
    
    /** @~english Returns a string that is used to identify the node.
     * @~chinese 返回用于识别节点的名字。
     * @return @~english A string that identifies the node. @~chinese 用于识别节点的名字。 
     * 
     * @since v3.2
     */
    virtual std::string getName() const;
    /** @~english Changes the name that is used to identify the node easily.
     * @~chinese 设置用于识别节点的名字。
     * @param name @~english A string that identifies the node. @~chinese 用于识别节点的名字 
     *
     * @since v3.2
     */
    virtual void setName(const std::string& name);

    
    /**
     * @~english Returns a custom user data pointer.
     *
     * You can set everything in UserData pointer, a data block, a structure or an object.
     * @~chinese 返回一个用户自定义数据的指针。
     *
     * 你可以随意设置UserData 指针为, 一个数据块, 结构体或者一个对象。
     *
     * @return @~english A custom user data pointer. @~chinese 用户自定义数据的指针。 
     * @lua NA
     */
    virtual void* getUserData() { return _userData; }
    /**
    * @lua NA
    */
    virtual const void* getUserData() const { return _userData; }

    /**
     * @~english Sets a custom user data pointer.
     *
     * You can set everything in UserData pointer, a data block, a structure or an object, etc.
     * @~chinese 设置一个用户自定义数据的指针。
     *
     * 你可以随意设置UserData 指针为, 一个数据块, 结构体或者一个对象，等等。
     * @warning @~english Don't forget to release the memory manually,
     *          especially before you change this data pointer, and before this node is autoreleased.
     * @~chinese 不要忘记要手动释放内存，
     *          特别是在你改变这个数据指针之前，和这个节点被自动释放之前。
     *
     * @param userData  @~english A custom user data pointer. @~chinese 一个用户自定义数据指针。 
     * @lua NA
     */
    virtual void setUserData(void *userData);

    /**
     * @~english Returns a user assigned Object.
     *
     * Similar to userData, but instead of holding a void* it holds an object.
     * @~chinese 返回一个用户设定的对象
     *
     * 和userData类似, 但它只能指向一个Ref类型的对象
     *
     * @return @~english A user assigned Object. @~chinese 一个用户分配的对象。 
     * @lua NA
     */
    virtual Ref* getUserObject() { return _userObject; }
    /**
    * @lua NA
    */
    virtual const Ref* getUserObject() const { return _userObject; }

    /**
     * @~english Returns a user assigned Object.
     *
     * Similar to UserData, but instead of holding a void* it holds an object.
     * The UserObject will be retained once in this method,
     * and the previous UserObject (if existed) will be released.
     * The UserObject will be released in Node's destructor.
     * @~chinese 返回一个用户分配的对象
     *
     * 和userData类似, 但它拥有的是一个对象而不是void*
     * UserObject将会在这个方法中留存一次
     * 然后之前的UserObject （如果存在的话）将会被释放。
     * UserObject 将会在节点的析构函数中释放。
     *
     * @param userObject    @~english A user assigned Object. @~chinese 一个用户分配的对象 
     */
    virtual void setUserObject(Ref *userObject);

    /// @} end of Tag & User Data


    /// @{
    /// @name GLProgram
    /// @brief @~english @~chinese OpenGL着色器程序
    /**
     * @~english Return the GLProgram (shader) currently used for this node.
     * @~chinese 返回当前用于这个节点的着色器程序 (shader) 
     *
     * @return @~english The GLProgram (shader) currently used for this node. @~chinese 当前用于这个节点的GLProgram (shader) 
     */
    GLProgram* getGLProgram() const;
    CC_DEPRECATED_ATTRIBUTE GLProgram* getShaderProgram() const { return getGLProgram(); }
    /**
     * @~english Sets the shader program for this node
     *
     * Since v2.0, each rendering node must set its shader program.
     * It should be set in initialize phase.
     * @~chinese 为这个节点设置着色器程序
     *
     * 自从 v2.0, 每一个渲染的节点必须设置它自己的着色器程序。
     * 它应该在初始化阶段被设置。
     @code
     node->setGLrProgram(GLProgramCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
     @endcode
     *
     * @param glprogram @~english The shader program. @~chinese 着色器程序 
     */
    virtual void setGLProgram(GLProgram *glprogram);
    CC_DEPRECATED_ATTRIBUTE void setShaderProgram(GLProgram *glprogram) { setGLProgram(glprogram); }
    
    /**
     * @~english Return the GLProgramState currently used for this node.
     * @~chinese 返回节点当前使用的OpenGL着色器程序状态
     *
     * @return @~english The GLProgramState currently used for this node.
     * @~chinese 节点当前使用的OpenGL着色器程序状态
     */
    GLProgramState *getGLProgramState() const;
    /**
     * @~english Set the GLProgramState for this node.
     * @~chinese 设置节点当前使用的OpenGL着色器程序状态
     *
     * @param glProgramState @~english The GLProgramState for this node. @~chinese OpenGL着色器程序状态 
     */
    virtual void setGLProgramState(GLProgramState *glProgramState);
    
    /// @} end of Shader Program


    /**
     * @~english Returns whether or not the node is "running".
     *
     * If the node is running it will accept event callbacks like onEnter(), onExit(), update().
     * @~chinese 返回节点是否是“running(活动的)”。
     *
     * 如果节点是活动的，它将会允许事件回调就像onEnter(), onExit(), update()
     *
     * @return @~english Whether or not the node is running. @~chinese 节点是否是“running(活动的)”。 
     */
    virtual bool isRunning() const;

    /**
     * @~english Schedules for lua script.
     * @~chinese Lua script的时间表
     * @js NA
     *
     * @param handler @~english The key to search lua function. @~chinese 用来寻找Lua函数的key 
     * @param priority @~english A given priority value. @~chinese 一个给定的优先级 
     */
    void scheduleUpdateWithPriorityLua(int handler, int priority);

    /// @}  end Script Bindings


    /// @{
    /// @name Event Callbacks
    /// @brief @~english @~chinese 事件回调函数

    /**
     * @~english Event callback that is invoked every time when Node enters the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition starts.
     * During onEnter you can't access a "sister/brother" node.
     * If you override onEnter, you shall call its parent's one, e.g., Node::onEnter().
     * @~chinese 每次当Node进入“stage”时才调用事件回调。
     * 如果Node进入“stage”状态时伴随着一个转换（transition）,那么事件将会在这个转换开始的时候被调用。
     * 在onEnter过程中，你不能够接入“sister/brother”兄妹节点。
     * 如果你重写了onEnter方法，你应该调用它的父类，e.g., Node::onEnter().
     * @lua NA
     */
    virtual void onEnter();

    /** @~chinese 每次当Node进入“stage”时才调用事件回调。
     * 如果Node进入“stage”状态时伴随着一个转换（transition）,那么事件将会在这个转换结束的时候被调用。
     * 如果你重写了onEnterTransitionDidFinish方法 你应该调用它的父类, e.g. Node::onEnterTransitionDidFinish()
     * @~english Event callback that is invoked when the Node enters in the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition finishes.
     * If you override onEnterTransitionDidFinish, you shall call its parent's one, e.g. Node::onEnterTransitionDidFinish()
     * @lua NA
     */
    virtual void onEnterTransitionDidFinish();

    /**
     * @~english Event callback that is invoked every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
     * @~chinese 每次当Node离开“stage”时才调用事件回调。
     * 如果Node离开“stage”状态时伴随着一个转换（transition）, 那么事件将会在这个转换结束的时候被调用。
     * 在onEnter过程中中你不能够接入一个兄妹节点。
     * 如果你重写onExit, 你应该调用它的父类, e.g., Node::onExit().
     * @lua NA
     */
    virtual void onExit();

    /**
     * @~english Event callback that is called every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this callback is called when the transition starts.
     * @~chinese 每次当Node离开“stage”时才调用事件回调。
     * 如果Node离开“stage”状态时伴随着一个转换（transition）, 那么事件将会在这个转换开始的时候被调用。
     * @lua NA
     */
    virtual void onExitTransitionDidStart();

    /// @} end of event callbacks.


    /**
     * @~english Stops and removes all running actions and schedulers
     * @~chinese 停止并移除所有的活动着的动作和调度器。
     */
    virtual void cleanup();

    /**
     * @~english Override this method to draw your own node.
     * The following GL states will be enabled by default:
     * - `glEnableClientState(GL_VERTEX_ARRAY);`
     * - `glEnableClientState(GL_COLOR_ARRAY);`
     * - `glEnableClientState(GL_TEXTURE_COORD_ARRAY);`
     * - `glEnable(GL_TEXTURE_2D);`
     * AND YOU SHOULD NOT DISABLE THEM AFTER DRAWING YOUR NODE
     * But if you enable any other GL state, you should disable it after drawing your node.
     * @~chinese 重写这个方法来绘制你自己的节点。
     * 以下的GL状态是默认开启的：
     * - `glEnableClientState(GL_VERTEX_ARRAY);`
     * - `glEnableClientState(GL_COLOR_ARRAY);`
     * - `glEnableClientState(GL_TEXTURE_COORD_ARRAY);`
     * - `glEnable(GL_TEXTURE_2D);`
     * 并且在绘制完你的节点之后不能够关闭他们。
     * 但是如果你开启了其他的GL状态，那么在绘制完你的节点之后你要关闭他们。
     * 
     * @param renderer A given renderer.
     * @param transform A transform matrix.
     * @param flags Renderer flag.
     */
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    virtual void draw() final;

    /**
     * @~english Visits this node's children and send their render command recursively.
     * @~chinese 遍历所有子节点，并且循环递归得发送它们的渲染指令。
     *
     * @param renderer @~english A given renderer. @~chinese 指定一个渲染器 
     * @param parentTransform @~english A transform matrix. @~chinese 父节点放射变换矩阵 
     * @param parentFlags @~english Renderer flag. @~chinese 渲染器标签 
     */
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);
    virtual void visit() final;


    /** 
     @~english Returns the Scene that contains the Node.
     It returns `nullptr` if the node doesn't belong to any Scene.
     This function recursively calls parent->getScene() until parent is a Scene object. The results are not cached. It is that the user caches the results in case this functions is being used inside a loop.@~chinese 返回包含该节点的场景。
     如果这个节点不属于任何的场景，它将返回`nullptr`。
     这个函数循环递归地调用parent->getScene() 直到父类是一个Scene对象。结果不会被缓存。只有当这个函数被用在一个循环中时，用户才会缓存这个结果。
     *
     * @return @~english The Scene that contains the node. @~chinese 包含该节点的场景 
     */
    virtual Scene* getScene() const;

    /**
     * @~english Returns an AABB (axis-aligned bounding-box) in its parent's coordinate system.
     * @~chinese 返回父坐标系中的一个AABB(轴向包围外框)。
     *
     * @return @~english An AABB (axis-aligned bounding-box) in its parent's coordinate system @~chinese 轴向包围外框 
     */
    virtual Rect getBoundingBox() const;

    /** @deprecated Use getBoundingBox instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual Rect boundingBox() const { return getBoundingBox(); }

    /** @~english Set event dispatcher for node.
     * @~chinese 设置节点的事件分发器
     *
     * @param dispatcher @~english The event dispatcher. @~chinese 事件分发器 
     */
    virtual void setEventDispatcher(EventDispatcher* dispatcher);
    /** @~english Get the event dispatcher.
     * @~chinese 获取节点的事件分发器
     *
     * @return @~english The event dispatcher. @~chinese 事件分发器 
     */
    virtual EventDispatcher* getEventDispatcher() const { return _eventDispatcher; };

    /// @{
    /// @name Actions
    /// @brief @~english @~chinese 动作

    /**
     * @~english Sets the ActionManager object that is used by all actions.
     * @~chinese 设置被所有动作使用的ActionManager对象。
     *
     * @warning @~english If you set a new ActionManager, then previously created actions will be removed.
     * @~chinese 如果你设置了一个新的ActionManager, 那么之前创建的动作将会被删除。
     *
     * @param actionManager     @~english A ActionManager object that is used by all actions. @~chinese ActionManager被所有动作使用。 
     */
    virtual void setActionManager(ActionManager* actionManager);
    /**
     * @~english Gets the ActionManager object that is used by all actions.
     * @~chinese 得到被所有动作使用的ActionManager对象。
     * @see setActionManager(ActionManager*)
     * @return @~english An ActionManager object. @~chinese ActionManager对象。 
     */
    virtual ActionManager* getActionManager() { return _actionManager; }
    virtual const ActionManager* getActionManager() const { return _actionManager; }

    /**
     * @~english Executes an action, and returns the action that is executed.
     *
     * This node becomes the action's target. Refer to Action::getTarget().
     * @~chinese 执行一个动作，并且返回执行的该动作。
     *
     * 这个节点将会变成动作的目标，参考Action::getTarget()
     * @warning @~english Actions don't retain their target. @~chinese 动作不存储它的目标。 
     *
     * @param action @~english An Action pointer. @~chinese 动作对象 
     */
    virtual Action* runAction(Action* action);

    /**
     * @~english Stops and removes all actions from the running action list .
     * @~chinese 停止并且从活动动作列表中删除所有的动作。
     */
    void stopAllActions();

    /**
     * @~english Stops and removes an action from the running action list.
     * @~chinese 停止并且从活动动作列表中删除一个动作。
     *
     * @param action    @~english The action object to be removed. @~chinese 需要被删除的动作 
     */
    void stopAction(Action* action);

    /**
     * @~english Removes an action from the running action list by its tag.
     * @~chinese 通过动作的标记从活动动作列表中删除一个动作。
     *
     * @param tag   @~english A tag that indicates the action to be removed. @~chinese 动作的标记 
     */
    void stopActionByTag(int tag);
    
    /**
     * @~english Removes all actions from the running action list by its tag.
     * @~chinese 通过动作的标记从活动动作列表中删除动作。
     *
     * @param tag   @~english A tag that indicates the action to be removed. @~chinese 动作的标记 
     */
    void stopAllActionsByTag(int tag);

    /**
     * @~english Gets an action from the running action list by its tag.
     * @~chinese 通过动作的标记从活动动作列表中得到一个动作。
     *
     * @see `setTag(int)`, `getTag()`.
     *
     * @return @~english The action object with the given tag. @~chinese 动作的标记 
     */
    Action* getActionByTag(int tag);

    /**
     * @~english Returns the numbers of actions that are running plus the ones that are schedule to run (actions in actionsToAdd and actions arrays).
     *
     * Composable actions are counted as 1 action. Example:
     *    If you are running 1 Sequence of 7 actions, it will return 1.
     *    If you are running 7 Sequences of 2 actions, it will return 7.
     * @~chinese 返回活动着的动作加上正在调度运行的动作的总数 (在actionsToAdd状态的动作和动作数组中的).
     *
     * 组成的动作被记为一个动作。例如：
     *    如果你正在运行7个活动中的1Sequence, 它将返回 1.
     *    如果你正在运行2个动作中的7个Sequencesm,它将返回 7.
     * @todo Rename to getNumberOfRunningActions()
     *
     * @return @~english The number of actions that are running plus the ones that are schedule to run.
     * @~chinese 返回活动着的动作加上正在调度运行的动作的总数
     */
    ssize_t getNumberOfRunningActions() const;

    /** @deprecated Use getNumberOfRunningActions() instead */
    CC_DEPRECATED_ATTRIBUTE ssize_t numberOfRunningActions() const { return getNumberOfRunningActions(); };

    /// @} end of Actions


    /// @{
    /// @name Scheduler and Timer
    /// @brief @~english @~chinese 调度器和计时器

    /**
     * @~english Sets a Scheduler object that is used to schedule all "updates" and timers.
     * @~chinese 设置一个调度器对象来用于调度所有的“update”和定时器。
     *
     * @warning @~english If you set a new Scheduler, then previously created timers/update are going to be removed.
     * @~chinese 如果你设置了一个新的调度器，那么之前创建的timers/update将会被删除。 
     * @param scheduler     @~english A Shdeduler object that is used to schedule all "update" and timers. @~chinese 一个来用于调度所有的“update”和定时器的调度器对象。 
     */
    virtual void setScheduler(Scheduler* scheduler);
    /**
     * @~english Gets a Sheduler object. @~chinese 得到调度器对象。 
     *
     * @see setScheduler(Scheduler*)
     * @return @~english A Scheduler object. @~chinese 调度器对象。 
     */
    virtual Scheduler* getScheduler() { return _scheduler; }
    virtual const Scheduler* getScheduler() const { return _scheduler; }


    /**
     * @~english Checks whether a selector is scheduled. @~chinese 检查一个选择器是否在调度中。 
     *
     * @param selector      @~english A function selector @~chinese 函数选择器 
     * @return @~english Whether the funcion selector is scheduled. @~chinese 函数选择器是否在调度中 
     * @js NA
     * @lua NA
     */
    bool isScheduled(SEL_SCHEDULE selector);

    /**
     * @~english Checks whether a lambda function is scheduled. @~chinese 检查一个lambda函数是否在调度中。 
     *
     * @param key      @~english key of the callback @~chinese lambda回调函数的key 
     * @return @~english Whether the lambda function selector is scheduled. @~chinese 返回lambda函数是否在调度中 
     * @js NA
     * @lua NA
     */
    bool isScheduled(const std::string &key);

    /**
     * @~english Schedules the "update" method.
     *
     * It will use the order number 0. This method will be called every frame.
     * Scheduled methods with a lower order value will be called before the ones that have a higher order value.
     * Only one "update" method could be scheduled per node.
     * @~chinese 调度"update"方法。
     *
     * 它的优先级将会是0，这个方法将会在每一帧都被调用。
     * 拥有较小优先数值的调度方法将会在有拥用较大优先数值的方法之前被调用。
     * 每一个节点只有一"update"能够被调度(你不能够有2个“update”选择器)。
     * @lua NA
     */
    void scheduleUpdate(void);

    /**
     * @~english Schedules the "update" method with a custom priority.
     *
     * This selector will be called every frame.
     * Scheduled methods with a lower priority will be called before the ones that have a higher value.
     * Only one "update" selector could be scheduled per node (You can't have 2 'update' selectors).
     * @~chinese 使用一个自定义优先级调度"update"方法。
     *
     * 这个选择器将会在每一帧被调用。
     * 拥有较小优先数值的调度方法将会在有拥用较大优先数值的方法之前被调用。
     * 每一个节点只有一"update"能够被调度(你不能够有2个“update”选择器)。
     * @lua NA
     *
     * @param priority @~english A given priority value. @~chinese 优先级数值（数值越小优先级越高） 
     */
    void scheduleUpdateWithPriority(int priority);

    /*
     * @~english Unschedules the "update" method. @~chinese 取消调度"update"方法。 
     * @see scheduleUpdate();
     */
    void unscheduleUpdate(void);

    /**
     * @~english Schedules a custom selector.
     *
     * If the selector is already scheduled, then the interval parameter will be updated without scheduling it again.
     * @~chinese 调度一个自定义的选择器。
     *
     * 如果这个选择器已经被调度了，那么内部的参数将会被更新而不会再次调度。
     @code
     // firstly, implement a schedule function
     void MyNode::TickMe(float dt);
     // wrap this function into a selector via schedule_selector marco.
     this->schedule(CC_SCHEDULE_SELECTOR(MyNode::TickMe), 0, 0, 0);
     @endcode
     *
     * @param selector  @~english The SEL_SCHEDULE selector to be scheduled. @~chinese 将被调度的 SEL_SCHEDULE 选择器。 
     * @param interval  @~english Tick interval in seconds. 0 means tick every frame. If interval = 0, it's recommended to use scheduleUpdate() instead.
     * @~chinese 以秒为时间间隔。0代表时间间隔为每帧。如果interval = 0，那就推荐使用scheduleUpdate()来代替。
     * @param repeat    @~english The selector will be excuted (repeat + 1) times, you can use CC_REPEAT_FOREVER for tick infinitely.
     * @~chinese 这个选择器将会被执行的次数（repeat+1）,你可以使用kRepeatForever来无限重复。
     * @param delay     @~english The amount of time that the first tick will wait before execution.
     * @~chinese 第一次调度开始执行前的等待总时间。
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);

    /**
     * @~english Schedules a custom selector with an interval time in seconds.
     * @~chinese 指定一个以秒为单位的时间间隔并调度一个自定义的选择器。
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector      @~english The SEL_SCHEDULE selector to be scheduled. @~chinese 将会被调度的SEL_SCHEDULE选择器。 
     * @param interval      @~english Callback interval time in seconds. 0 means tick every frame,
     * @~chinese 以秒为单位的时间间隔，0代表以每帧都执行。
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector, float interval);

    /**
     * @~english Schedules a selector that runs only once, with a delay of 0 or larger
     * @~chinese 调度一个只运行一次的选择器，伴随着一个0或者更大的延时。
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector      @~english The SEL_SCHEDULE selector to be scheduled. @~chinese 将会被调度的SEL_SCHEDULE选择器。 
     * @param delay         @~english The amount of time that the first tick will wait before execution.
     * @~chinese 第一次调度开始执行前的等待时间。
     * @lua NA
     */
    void scheduleOnce(SEL_SCHEDULE selector, float delay);

    /**
     * @~english Schedules a lambda function that runs only once, with a delay of 0 or larger
     * @~chinese 调度一个只运行一次的lambda回调函数，伴随着一个0或者更大的延时和一个key来标记这个回调。
     *
     * @param callback      @~english The lambda function to be scheduled. @~chinese lambda回调函数 
     * @param delay         @~english The amount of time that the first tick will wait before execution. @~chinese 第一次调度开始执行前的等待时间。 
     * @param key           @~english The key of the lambda function. To be used if you want to unschedule it. @~chinese 用来标记lambda函数的key，可以用来取消调度 
     * @lua NA
     */
    void scheduleOnce(const std::function<void(float)>& callback, float delay, const std::string &key);

    /**
     * @~english Schedules a custom selector, the scheduled selector will be ticked every frame.
     * @~chinese 调度一个自定义的选择器，这个选择器将会每帧被调用。
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      @~english A function wrapped as a selector @~chinese 将会被调度的SEL_SCHEDULE选择器 
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector);

    /**
     * @~english Schedules a lambda function. The scheduled lambda function will be called every frame.
     * @~chinese 调度一个自定义的lambda回调函数，这个回调函数将会每帧被调用。
     *
     * @param callback      @~english The lambda function to be scheduled. @~chinese lambda回调函数 
     * @param key           @~english The key of the lambda function. To be used if you want to unschedule it. @~chinese 用来标记lambda函数的key，可以用来取消调度 
     * @lua NA
     */
    void schedule(const std::function<void(float)>& callback, const std::string &key);

    /**
     * @~english Schedules a lambda function. The scheduled lambda function will be called every "interval" seconds
     * @~chinese 调度一个lambda回调函数，并指定调度的时间间隔（以秒为单位）。
     *
     * @param callback      @~english The lambda function to be scheduled @~chinese lambda回调函数 
     * @param interval      @~english Callback interval time in seconds. 0 means every frame @~chinese 以秒为单位的时间间隔，0代表以每帧都执行。 
     * @param key           @~english The key of the lambda function. To be used if you want to unschedule it @~chinese 用来标记lambda函数的key，可以用来取消调度 
     * @lua NA
     */
    void schedule(const std::function<void(float)>& callback, float interval, const std::string &key);

    /**
     * @~english Schedules a lambda function. @~chinese 调度一个lambda回调函数 
     *
     * @param callback  @~english The lambda function to be schedule. @~chinese lambda回调函数 
     * @param interval  @~english Tick interval in seconds. 0 means tick every frame. @~chinese 以秒为单位的时间间隔，0代表以每帧都执行。 
     * @param repeat    @~english The selector will be executed (repeat + 1) times, you can use CC_REPEAT_FOREVER for tick infinitely.
     * @~chinese 这个选择器将会被执行的次数（repeat+1）,你可以使用kRepeatForever来无限重复。
     * @param delay     @~english The amount of time that the first tick will wait before execution.
     * @~chinese 第一次调度开始执行前的等待时间。
     * @param key       @~english The key of the lambda function. To be used if you want to unschedule it. @~chinese 用来标记lambda函数的key，可以用来取消调度 
     * @lua NA
     */
    void schedule(const std::function<void(float)>& callback, float interval, unsigned int repeat, float delay, const std::string &key);

    /**
     * @~english Unschedules a custom selector. @~chinese 取消调度一个自定义的选择器。 
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector      @~english A function wrapped as a selector. @~chinese SEL_SCHEDULE选择器 
     * @lua NA
     */
    void unschedule(SEL_SCHEDULE selector);

    /**
     * @~english Unschedules a lambda function. @~chinese 取消调度一个lambda回调函数 
     *
     * @param key      @~english The key of the lambda function to be unscheduled. @~chinese lambda回调函数对应的key 
     * @lua NA
     */
    void unschedule(const std::string &key);

    /**
     * @~english Unschedule all scheduled selectors and lambda functions: custom selectors, and the 'update' selector and lambda functions.
     * @~chinese 取消调度所有选择器和回调函数，以及update调度。不会影响动作。
     * Actions are not affected by this method.
     * @lua NA
     */
    void unscheduleAllCallbacks();

    CC_DEPRECATED_ATTRIBUTE void unscheduleAllSelectors() { unscheduleAllCallbacks(); }

    /**
     * @~english Resumes all scheduled selectors, actions and event listeners.
     * This method is called internally by onEnter.
     * @~chinese 恢复所有的调度过的选择器，动作和事件监听器。
     * 这个方法被onEnter方法在内部调用。
     */
    virtual void resume(void);
    /**
     * @~english Pauses all scheduled selectors, actions and event listeners.
     * This method is called internally by onExit.
     * @~chinese 暂停所有的调度过的选择器，动作和事件监听器。
     * 这个方法被onExit方法在内部调用。
     */
    virtual void pause(void);

    /**
     * @~english Resumes all scheduled selectors, actions and event listeners.
     * This method is called internally by onEnter.
     * @~chinese 恢复所有的调度过的选择器，动作和事件监听器。
     * 这个方法被onEnter方法在内部调用。
     */
    CC_DEPRECATED_ATTRIBUTE void resumeSchedulerAndActions();
    /**
     * @~english Pauses all scheduled selectors, actions and event listeners.
     * This method is called internally by onExit.
     * @~chinese 暂停所有的调度过的选择器，动作和事件监听器。
     * 这个方法被onExit方法在内部调用。
     */
    CC_DEPRECATED_ATTRIBUTE void pauseSchedulerAndActions();

    /**
     * @~english Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live".
     * @~chinese 如果"scheduleUpdate"被调用并且这个节点是活跃的话，update方法将会被每帧自动调用。
     * @param delta In seconds.
     */
    virtual void update(float delta);

    /// @} end of Scheduler and Timer

    /// @{
    /// @name Transformations
    /// @brief @~english @~chinese 仿射变换函数

    /**
     * @~english Calls children's updateTransform() method recursively.
     *
     * This method is moved from Sprite, so it's no longer specific to Sprite.
     * As the result, you apply SpriteBatchNode's optimization on your customed Node.
     * e.g., `batchNode->addChild(myCustomNode)`, while you can only addChild(sprite) before.
     * @~chinese 递归的调用孩子的updateTransform()方法。
     *
     * 这个方法是从Sprite类中迁移的，因此它不再只适用于Sprite.
     * 因此，你可以在自定义节点中为SpriteBatchNode进行优化。
     * e.g., `batchNode->addChild(myCustomNode)`, 以前你只可以addChild(sprite)
     */
    virtual void updateTransform();

    /**
     * @~english Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     * @~chinese 返回这个将节点（局部）的空间坐标系转换成父节点的空间坐标系的矩阵。
     * 这个矩阵以像素为单位。
     *
     * @return The transformation matrix.
     */
    virtual const Mat4& getNodeToParentTransform() const;
    virtual AffineTransform getNodeToParentAffineTransform() const;

    /** 
     * @~english Sets the transformation matrix manually.
     * @~chinese 手动设置变换矩阵。
     *
     * @param transform @~english A given transformation matrix. @~chinese 仿射变化矩阵 
     */
    virtual void setNodeToParentTransform(const Mat4& transform);

    /** @deprecated use getNodeToParentTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToParentTransform() const { return getNodeToParentAffineTransform(); }

    /**
     * @~english Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
     * The matrix is in Pixels.
     * @~chinese 返回将父节点的空间坐标系转换成节点（局部）的空间坐标系转的矩阵。
     * 这个矩阵以像素为单位。
     *
     * @return @~english The transformation matrix. @~chinese 仿射变化矩阵 
     */
    virtual const Mat4& getParentToNodeTransform() const;
    virtual AffineTransform getParentToNodeAffineTransform() const;

    /** @deprecated Use getParentToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform parentToNodeTransform() const { return getParentToNodeAffineTransform(); }

    /**
     * @~english Returns the world affine transform matrix. The matrix is in Pixels.
     * @~chinese 返回节点到世界坐标仿射变换矩阵。矩阵单位是像素。
     *
     * @return @~english transformation matrix, in pixels. @~chinese 节点到世界坐标仿射变换矩阵 
     */
    virtual Mat4 getNodeToWorldTransform() const;
    virtual AffineTransform getNodeToWorldAffineTransform() const;

    /** @deprecated Use getNodeToWorldTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToWorldTransform() const { return getNodeToWorldAffineTransform(); }

    /**
     * @~english Returns the inverse world affine transform matrix. The matrix is in Pixels.
     * @~chinese 返回逆节点到世界仿射变换矩阵。矩阵单位是像素。
     *
     * @return @~english The transformation matrix. @~chinese 仿射变换矩阵 
     */
    virtual Mat4 getWorldToNodeTransform() const;
    virtual AffineTransform getWorldToNodeAffineTransform() const;


    /** @deprecated Use getWorldToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform worldToNodeTransform() const { return getWorldToNodeAffineTransform(); }

    /// @} end of Transformations


    /// @{
    /// @name Coordinate Converters
    /// @brief @~english @~chinese 坐标转换

    /**
     * @~english Converts a Vec2 to node (local) space coordinates. The result is in Points.
     * @~chinese 将Vec2 转换成节点 (局部) 空间坐标系。结果以Points为单位。
     *
     * @param worldPoint @~english A given coordinate. @~chinese 一个世界坐标 
     * @return @~english A point in node (local) space coordinates. @~chinese 给定坐标在节点坐标系中的坐标 
     */
    Vec2 convertToNodeSpace(const Vec2& worldPoint) const;

    /**
     * @~english Converts a Vec2 to world space coordinates. The result is in Points.
     * @~chinese 将Vec2转换成世界空间坐标系。结果以Points为单位。
     *
     * @param nodePoint @~english A given coordinate. @~chinese 一个本地坐标 
     * @return @~english A point in world space coordinates. @~chinese 给定坐标在世界坐标系中的坐标 
     */
    Vec2 convertToWorldSpace(const Vec2& nodePoint) const;

    /**
     * @~english Converts a Vec2 to node (local) space coordinates. The result is in Points.
     * treating the returned/received node point as anchor relative.
     * @~chinese 将Vec2转换成节点(局部)空间坐标系. 结果以Points为单位。
     * 坐标按当作相对于锚点来处理。
     *
     * @param worldPoint @~english A given coordinate. @~chinese 一个世界坐标 
     * @return @~english A point in node (local) space coordinates, anchor relative. @~chinese 给定坐标在节点坐标系中的坐标，与锚点相关 
     */
    Vec2 convertToNodeSpaceAR(const Vec2& worldPoint) const;

    /**
     * @~english Converts a local Vec2 to world space coordinates.The result is in Points.
     * treating the returned/received node point as anchor relative.
     * @~chinese 将Vec2转换成世界空间坐标系。结果以Points为单位。
     * 坐标按相对于锚点来处理。
     *
     * @param nodePoint @~english A given coordinate. @~chinese 一个本地坐标 
     * @return @~english A point in world space coordinates, anchor relative. @~chinese 给定坐标在世界坐标系中的坐标，与锚点相关 
     */
    Vec2 convertToWorldSpaceAR(const Vec2& nodePoint) const;

    /**
     * @~english Convenience methods which take a Touch instead of Vec2.
     * @~chinese 将触摸点转换成本地坐标系中位置
     *
     * @param touch @~english A given touch. @~chinese 触摸点对象 
     * @return @~english A point in node space coordinates. @~chinese 本地坐标系中位置 
     */
    Vec2 convertTouchToNodeSpace(Touch * touch) const;

    /**
     * @~english Converts a Touch (world coordinates) into a local coordinate. This method is AR (Anchor Relative).
     * @~chinese 将触点 (世界坐标系) 转换成本地坐标系。坐标按相对于锚点来处理。
     *
     * @param touch @~english A given touch. @~chinese 触摸点对象 
     * @return @~english A point in world space coordinates, anchor relative. @~chinese 本地坐标系中位置，与锚点相关 
     */
    Vec2 convertTouchToNodeSpaceAR(Touch * touch) const;

	/**
     * @~english Sets an additional transform matrix to the node.
     *
     * In order to remove it, call it again with the argument `nullptr`.
     * @~chinese 为节点设置一个附加转换矩阵。
     *
     * 通过传入参数"nullptr"删除它.
     *
     * @note @~english The additional transform will be concatenated at the end of getNodeToParentTransform.
     *        It could be used to simulate `parent-child` relationship between two nodes (e.g. one is in BatchNode, another isn't).
     * @~chinese 这个附加转换将会连接在getNodeToParentTransform之后。
     *        它可以被用于在两个节点之间模拟`parent-child`的关系(e.g. 其中一个在BatchNode中, 另一个却不在).
     *
     * @param additionalTransform An additional transform matrix.
     */
    void setAdditionalTransform(Mat4* additionalTransform);
    void setAdditionalTransform(const AffineTransform& additionalTransform);

    /// @} end of Coordinate Converters

    /// @{
    /// @name component functions
    /// @brief @~english @~chinese 组件系统
    /**
     * @~english Gets a component by its name. @~chinese 通过名字得到组件 
     *
     * @param name @~english A given name of component. @~chinese 组件的名字 
     * @return @~english The Component by name. @~chinese 名字对应的组件 
     */
    Component* getComponent(const std::string& name);

    /**
     * @~english Adds a component. @~chinese 添加一个组件 
     *
     * @param component @~english A given component. @~chinese 一个组件 
     * @return @~english True if added success. @~chinese 如果添加成功返回true，否则返回false 
     */
    virtual bool addComponent(Component *component);

    /**
     * @~english Removes a component by its name. @~chinese 通过名字删除一个组件 
     *
     * @param name @~english A given name of component. @~chinese 组件的名字 
     * @return @~english True if removed success. @~chinese 如果删除成功返回true，否则返回false 
     */
    virtual bool removeComponent(const std::string& name);

    /** 
     * @~english Removes a component by its pointer. @~chinese 通过指针删除一个组件 
     *
     * @param component @~english A given component. @~chinese 组件指针 
     * @return @~english True if removed success. @~chinese 如果删除成功返回true，否则返回false 
     */
    virtual bool removeComponent(Component *component);
    /**
     * @~english Removes all components @~chinese 删除所有组件 
     */
    virtual void removeAllComponents();
    /// @} end of component functions


#if CC_USE_PHYSICS
    /**
     * @~english Set the PhysicsBody that let the sprite effect with physics. @~chinese 设置PhysicsBody来让精灵sprite有物理世界机能。 
     * @note @~english This method will set anchor point to Vec2::ANCHOR_MIDDLE if body not null, and you cann't change anchor point if node has a physics body.
     * @~chinese 如果body非空，这个方法将会设置锚点为Vec2::ANCHOR_MIDDLE, 并且当有物理body存在的情况下你不可以改变这个锚点。
     *
     * @param body @~english A given physics body. @~chinese 附加给节点的物理body 
     */
    void setPhysicsBody(PhysicsBody* body);

    /**
     * @~english Get the PhysicsBody the sprite have. @~chinese 得到精灵拥有的物理body 
     *
     * @return @~english The PhysicsBody the sprite have. @~chinese 精灵的物理body 
     */
    PhysicsBody* getPhysicsBody() const { return _physicsBody; }
    
    /**
     * @~english Remove this node from physics world. it will remove all the physics bodies in it's children too.
     * @~chinese 从物理世界中删除这个节点的物理body，并且会删除它子节点中的所有物理body
     */
    void removeFromPhysicsWorld();
    
    /** 
     * @~english Update the transform matrix from physics. @~chinese 从物理世界中同步变换矩阵 
     */
    void updateTransformFromPhysics(const Mat4& parentTransform, uint32_t parentFlags);

    /** 
     * @~english Update physics body transform matrix. @~chinese 将节点的变化矩阵同步到物理body上 
     */
    virtual void updatePhysicsBodyTransform(const Mat4& parentTransform, uint32_t parentFlags, float parentScaleX, float parentScaleY);
#endif
    
    // overrides
    virtual GLubyte getOpacity() const;
    virtual GLubyte getDisplayedOpacity() const;
    virtual void setOpacity(GLubyte opacity);
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    virtual bool isCascadeOpacityEnabled() const;
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    
    virtual const Color3B& getColor() const;
    virtual const Color3B& getDisplayedColor() const;
    virtual void setColor(const Color3B& color);
    virtual void updateDisplayedColor(const Color3B& parentColor);
    virtual bool isCascadeColorEnabled() const;
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);
    
    virtual void setOpacityModifyRGB(bool value) {CC_UNUSED_PARAM(value);}
    virtual bool isOpacityModifyRGB() const { return false; };

    void setOnEnterCallback(const std::function<void()>& callback) { _onEnterCallback = callback; }
    const std::function<void()>& getOnEnterCallback() const { return _onEnterCallback; }   
    void setOnExitCallback(const std::function<void()>& callback) { _onExitCallback = callback; }
    const std::function<void()>& getOnExitCallback() const { return _onExitCallback; }   
    void setonEnterTransitionDidFinishCallback(const std::function<void()>& callback) { _onEnterTransitionDidFinishCallback = callback; }
    const std::function<void()>& getonEnterTransitionDidFinishCallback() const { return _onEnterTransitionDidFinishCallback; }   
    void setonExitTransitionDidStartCallback(const std::function<void()>& callback) { _onExitTransitionDidStartCallback = callback; }
    const std::function<void()>& getonExitTransitionDidStartCallback() const { return _onExitTransitionDidStartCallback; }
    
    /** get & set camera mask, the node is visible by the camera whose camera flag & node's camera mask is true */
    unsigned short getCameraMask() const { return _cameraMask; }
    virtual void setCameraMask(unsigned short mask, bool applyChildren = true);

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
    uint32_t processParentFlags(const Mat4& parentTransform, uint32_t parentFlags);

    virtual void updateCascadeOpacity();
    virtual void disableCascadeOpacity();
    virtual void updateCascadeColor();
    virtual void disableCascadeColor();
    virtual void updateColor() {}
    
    bool doEnumerate(std::string name, std::function<bool (Node *)> callback) const;
    bool doEnumerateRecursive(const Node* node, const std::string &name, std::function<bool (Node *)> callback) const;
    
    //check whether this camera mask is visible by the current visiting camera
    bool isVisitableByVisitingCamera() const;
    
    // update quaternion from Rotation3D
    void updateRotationQuat();
    // update Rotation3D from quaternion
    void updateRotation3D();
    
private:
    void addChildHelper(Node* child, int localZOrder, int tag, const std::string &name, bool setTag);
    
protected:

    float _rotationX;               ///< rotation on the X-axis
    float _rotationY;               ///< rotation on the Y-axis

    // rotation Z is decomposed in 2 to simulate Skew for Flash animations
    float _rotationZ_X;             ///< rotation angle on Z-axis, component X
    float _rotationZ_Y;             ///< rotation angle on Z-axis, component Y
    
    Quaternion _rotationQuat;      ///rotation using quaternion, if _rotationZ_X == _rotationZ_Y, _rotationQuat = RotationZ_X * RotationY * RotationX, else _rotationQuat = RotationY * RotationX

    float _scaleX;                  ///< scaling factor on x-axis
    float _scaleY;                  ///< scaling factor on y-axis
    float _scaleZ;                  ///< scaling factor on z-axis

    Vec2 _position;                ///< position of the node
    float _positionZ;               ///< OpenGL real Z position
    Vec2 _normalizedPosition;
    bool _usingNormalizedPosition;
    bool _normalizedPositionDirty;

    float _skewX;                   ///< skew angle on x-axis
    float _skewY;                   ///< skew angle on y-axis

    Vec2 _anchorPointInPoints;     ///< anchor point in points
    Vec2 _anchorPoint;             ///< anchor point normalized (NOT in points)

    Size _contentSize;              ///< untransformed size of the node
    bool _contentSizeDirty;         ///< whether or not the contentSize is dirty

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
    Director* _director;            //cached director pointer to improve rendering performance
    int _tag;                         ///< a tag. Can be any number you assigned just to identify this node
    
    std::string _name;               ///<a string label, an user defined string to identify this node
    size_t _hashOfName;            ///<hash value of _name, used for speed in getChildByName

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
    float _physicsScaleStartX;         ///< the scale x value when setPhysicsBody
    float _physicsScaleStartY;         ///< the scale y value when setPhysicsBody
    float _physicsRotation;
    bool _physicsTransformDirty;
    bool _updateTransformFromPhysics;

    PhysicsWorld* _physicsWorld; /** The PhysicsWorld associated with the node.*/
    int _physicsBodyAssociatedWith;  /** The count of PhysicsBody associated with the node and children.*/
    float _physicsRotationOffset;  /** Record the rotation value when invoke Node::setPhysicsBody.*/

    float _offsetX;
    float _offsetY;
#endif
    
    // opacity controls
    GLubyte		_displayedOpacity;
    GLubyte     _realOpacity;
    Color3B	    _displayedColor;
    Color3B     _realColor;
    bool		_cascadeColorEnabled;
    bool        _cascadeOpacityEnabled;

    static int s_globalOrderOfArrival;
    
    // camera mask, it is visible only when _cameraMask & current camera' camera flag is true
    unsigned short _cameraMask;
    
    std::function<void()> _onEnterCallback;
    std::function<void()> _onExitCallback;
    std::function<void()> _onEnterTransitionDidFinishCallback;
    std::function<void()> _onExitTransitionDidStartCallback;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Node);
    
#if CC_USE_PHYSICS
    friend class Scene;
#endif //CC_USTPS
};

// NodeRGBA

/** @class __NodeRGBA
 * @brief __NodeRGBA is a subclass of Node that implements the RGBAProtocol protocol.
 
 All features from Node are valid, plus the following new features:
 - opacity
 - RGB colors
 
 Opacity/Color propagates into children that conform to the RGBAProtocol if cascadeOpacity/cascadeColor is enabled.
 @since v2.1
 @js NA
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

CC_CONSTRUCTOR_ACCESS:
    __NodeRGBA();
    virtual ~__NodeRGBA() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__NodeRGBA);
};

// end of _2d group
/// @}

NS_CC_END

#endif // __CCNODE_H__
