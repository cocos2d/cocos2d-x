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

/** @brief:节点是场景图的基本元素。场景图的基本元素必须是节点对象或者是节点对象的子类。
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
    /// @name 构造函数，析构函数和一些初始化

    /**
     * 分配并且初始化一个节点.
     * @return 一个初始化的节点，该节点被标记为“autorelease”(自动释放).
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
    /// @name 图形属性的设值函数和得值函数

    /**
     LocalZOrder是“key”(关键)来分辨节点和它兄弟节点的相关性。

     父节点将会通过LocalZOrder的值来分辨所有的子节点。
     如果两个节点有同样的LocalZOrder,那么先加入子节点数组的节点将会显示在后加入的节点的前面。
     
     同样的，场景图使用“In-Order（按顺序）”遍历数算法来遍历 ( http://en.wikipedia.org/wiki/Tree_traversal#In-order )
     并且拥有小于0的LocalZOrder的值的节点是“left”子树（左子树）
     所以拥有大于0的LocalZOrder的值得节点是“right”子树（右子树）
     
     @see `setGlobalZOrder`
     @see `setVertexZ`
     */
    virtual void setLocalZOrder(int localZOrder);

    CC_DEPRECATED_ATTRIBUTE virtual void setZOrder(int localZOrder) { setLocalZOrder(localZOrder); }
    /* `setLocalZOrder`使用的辅助函数。不要使用它除非你知道你在干什么。 
     */
    virtual void _setLocalZOrder(int z);
    /**
     * 得到这个节点的局部Z顺序
     *
     * @see `setLocalZOrder(int)`
     *
     * @return 局部Z顺序(相对于兄弟节点)。
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
     
     @see `setLocalZOrder()`
     @see `setVertexZ()`

     @since v3.0
     */
    virtual void setGlobalZOrder(float globalZOrder);
    /**
     * 返回节点的全局Z顺序。
     *
     * @see `setGlobalZOrder(int)`
     *
     * @see 节点的全局Z顺序
     */
    virtual float getGlobalZOrder() const { return _globalZOrder; }

    /**
     * 设置节点的缩放（x）。
     *
     * 它是一个缩放因子，将会乘以节点的宽以及它的子节点。
     *
     * @param scaleX   X轴的缩放因子.
     */
    virtual void setScaleX(float scaleX);
    /**
     * 返回该节点的X轴的缩放因子。
     *
     * @see setScaleX(float)。
     *
     * @return X轴的缩放因子。
     */
    virtual float getScaleX() const;


    /**
     * 设置节点的缩放（y）。
     *
     * 它是一个缩放因子，将会乘以节点的宽以及它的子节点。
     *
     * @param scaleY   Y轴的缩放因子
     */
    virtual void setScaleY(float scaleY);
    /**
     * 返回该节点的Y轴的缩放因子。
     *
     * @see `setScaleY(float)`
     *
     * @return Y轴的缩放因子
     */
    virtual float getScaleY() const;

    /**
     * 改变该节点的Z轴的缩放因子。
     *
     * 如果你之前没有改变过它，那么它的默认值是1.0。
     *
     * @param scaleY   Z轴的缩放因子
     */
    virtual void setScaleZ(float scaleZ);
    /**
     * 返回该节点的梓州的缩放因子。
     *
     * @see `setScaleZ(float)`
     *
     * @return Z轴的缩放因子。
     */
    virtual float getScaleZ() const;


    /**
     * 设置几点的缩放（x,y,z）.
     *
     * 缩放因子将会乘以该节点和它子节点的宽，高和深度。
     *
     * @param scale    X轴和Y轴的缩放因子
     */
    virtual void setScale(float scale);
    /**
     * 得到该节点的缩放因子，当X轴和Y轴有相同的缩放因子时。
     *
     * @warning 判断 当 `_scaleX != _scaleY`
     * @see setScale(float)
     *
     * @return 该节点的缩放因子
     */
    virtual float getScale() const;

     /**
     * 设置节点的缩放（x,y）.
     *
     * 缩放因子乘以该节点和它子节点的宽与高。
     *
     * @param scaleX     X轴的缩放因子。
     * @param scaleY     Y轴的缩放因子。
     */
    virtual void setScale(float scaleX, float scaleY);

    /**
     * 设置节点的位置在父节点的坐标系系统中。
     *
     * 通常我们使用`Vec2(x,y)` 来组成 Vec2 对象。
     * 这一段代码设置节点在屏幕中间。
     @code
     Size size = Director::getInstance()->getWinSize();
     node->setPosition( Vec2(size.width/2, size.height/2) )
     @endcode
     *
     * @param position  这个节点的位置（x,y）在OpenGL坐标系中。
     */
    virtual void setPosition(const Vec2 &position);
    /**
     * 得到在父节点坐标系中节点的位置（x,y）。
     *
     * @see setPosition(const Vec2&)
     *
     * @return 节点在OpenGL坐标系中的位置（x,y)。
     * @code
     * In js and lua return value is table which contains x,y
     * @endcode
     */
    virtual const Vec2& getPosition() const;
    /**
     * 设置节点在它父节点坐标系中的位置（x,y）。
     *
     * 传递两个数字（x,y）比传递Vec2对象更有效率。
     * 这个方法要在Lua和JavaScript下。
     * 从Lua到C++传递一个数字比传递一个对象快10倍。
     *
     @code
     // sample code in Lua
     local pos  = node::getPosition()  -- returns Vec2 object from C++
     node:setPosition(x, y)            -- pass x, y coordinate to C++
     @endcode
     *
     * @param x     位置的X轴坐标系
     * @param y     位置的Y轴坐标系
     */
    virtual void setPosition(float x, float y);
    /**
     * 用一个更有效率的方法设置位置，返回两个数字而不是Vec2对象。
     *
     * @see `setPosition(float, float)`
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
     * @see `setGlobalZValue()`
     *
     * @param vertexZ  该节点的penGL Z 定点。
     */
    virtual void setPositionZ(float positionZ);
    CC_DEPRECATED_ATTRIBUTE virtual void setVertexZ(float vertexZ) { setPositionZ(vertexZ); }

    /**
     * 得到该节点的Z轴坐标系的位置。
     *
     * @see setPositionZ(float)
     *
     * @return 该节点的Z轴坐标系。
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
     * @param skewX 该节点的X轴的倾斜角。
     */
    virtual void setSkewX(float skewX);
    /**
     * 返回该节点的X轴倾斜角，单位是度。
     *
     * @see `setSkewX(float)`
     *
     * @return 该节点的X轴倾斜角。
     */
    virtual float getSkewX() const;


    /**
     * 改变该节点Y轴的倾斜角，单位是度。
     *
     * `setRotationalSkew()`和 `setSkew()` 的不同时是前一个模拟Flash的倾斜功能。
     * 然而后一个使用真正的倾斜功能。
     *
     * 这个角度描述了在Y轴方向的切形变（shear distortion）。
     *  因此，这个角度在X轴和图形底边之间。
     * 默认值skewY角度是0，负值使该节点按顺时针变形。
     *
     * @param skewY    该节点的Y轴的倾斜角。
     */
    virtual void setSkewY(float skewY);
    /**
     * 返回该节点的Y轴倾斜角，单位是度。
     *
     * @see `setSkewY(float)`
     *
     * @return 该节点的Y轴倾斜角。
     */
    virtual float getSkewY() const;


    /**
     * 设置锚点，用百分比表示。
     *
     * 一个锚点是所有的转换和定位操作发生的点。
     * 它就像在节点上连接其父类的大头针。
     * 锚点是标准化的，就像百分比一样。(0,0)表示左下角，(1,1)表示右上角。
     * 但是你可以使用比（1,1,）更高的值或者比（0,0）更低的值。
     * 默认的锚点是（0.5,0.5），因此它开始于节点的中心位置。
     * @note 如果节点有物理体，锚点必须在中心，你不能够这个值。
     *
     * @param anchorPoint   节点的锚点。
     */
    virtual void setAnchorPoint(const Vec2& anchorPoint);
    /**
     * 返回用百分比表示的锚点。
     *
     * @see `setAnchorPoint(const Vec2&)`
     *
     * @return 节点的锚点
     */
    virtual const Vec2& getAnchorPoint() const;
    /**
     * 返回绝对像素的锚点
     *
     * @warning 你只能够读取它，如果你想修改它，使用setAnchoPoint。
     * @see `getAnchorPoint()`
     *
     * @return 绝对像素的锚点。
     */
    virtual const Vec2& getAnchorPointInPoints() const;


    /**
     * 设置不转换节点的大小。
     *
     * contentSize依然是相同的，无论节点是缩放或者旋转。
     * 所有的节点都有大小。图层和场景有相同的屏幕大小。
     *
     * @param contentSize   未转换节点的大小
     */
    virtual void setContentSize(const Size& contentSize);
    /**
     * 返回未转换节点的大小。
     *
     * @see `setContentSize(const Size&)`
     *
     * @return 未转换节点的大小
     */
    virtual const Size& getContentSize() const;


    /**
     * 设置节点是否可见。
     *
     * 默认值是true,一个节点默认是可见的。
     *
     * @param visible   true 如果节点是可见的，false 如果节点是隐藏的。
     */
    virtual void setVisible(bool visible);
    /**
     * 决定节点是否可见。
     *
     * @see `setVisible(bool)`
     *
     * @return true 如果节点是可见的, false 如果节点是隐藏的。
     */
    virtual bool isVisible() const;


    /**
     * 设置节点的旋转（angle）角度。
     *
     * 0 是默认的旋转角度。
     * 负数顺时针旋转节点，正数逆时针旋转节点。
     *
     * @param rotation     节点的旋转角度。
     */
    virtual void setRotation(float rotation);
    /**
     * 返回节点的旋转角度。
     *
     * @see `setRotation(float)`
     *
     * @return 节点的旋转角度。
     */
    virtual float getRotation() const;

    /**
     * 设置（X,Y,Z）旋转角度。
     * 对3d旋转非常有用。
     */
    virtual void setRotation3D(const Vec3& rotation);
    /**
     * 返回（X,Y,Z）的旋转角度。
     */
    virtual Vec3 getRotation3D() const;

    /**
     * 设置节点X轴的旋转角度，表现为水平旋转倾斜。
     *
     * `setRotationalSkew()` 和 `setSkew()`的不同是前一个是模拟Flash的倾斜功能
     * 然而后一个使用真正的倾斜功能。
     *
     * 0 是默认的旋转角度。
     * 负数节点顺时针旋转，正数节点逆时针旋转。
     *
     * @param rotationX    X轴的旋转角度表现为水平旋转倾斜。
     */
    virtual void setRotationSkewX(float rotationX);
    CC_DEPRECATED_ATTRIBUTE virtual void setRotationX(float rotationX) { return setRotationSkewX(rotationX); }

    /**
     * 得到X轴节点的旋转角度，表现为水平旋转倾斜（horizontal rotation skew）.
     *
     * @see `setRotationSkewX(float)`
     *
     * @return X轴的旋转角度。
     */
    virtual float getRotationSkewX() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getRotationX() const { return getRotationSkewX(); }

    /**
     * 设置Y轴节点的旋转角度，表现为垂直旋转倾斜。
     *
     * `setRotationalSkew()` 和`setSkew()` 的不同是前一个使用Flash倾斜功能
     * 后一个使用了真正的倾斜功能。
     *
     * 0 默认的旋转角度。
     * 负数表示顺时针旋转，正数表示逆时针旋转。
     *
     * @param rotationY    Y轴的旋转角度。
     */
    virtual void setRotationSkewY(float rotationY);
    CC_DEPRECATED_ATTRIBUTE virtual void setRotationY(float rotationY) { return setRotationSkewY(rotationY); }

    /**
     * 得到节点Y轴的旋转角度，表现为垂直旋转倾斜（vertical rotational skew.）
     *
     * @see `setRotationSkewY(float)`
     *
     * @return Y轴旋转角度。
     */
    virtual float getRotationSkewY() const;
    CC_DEPRECATED_ATTRIBUTE virtual float getRotationY() const { return getRotationSkewY(); }

    /**
     * 设置到达顺序，当这个节点和其他子节点有相同的ZOrder时。
     *
     * 一个调用了之后调用了addChild函数的节点将会有更大的到达顺序值，
     * 如果两个子对象有相同的Z轴顺序，这个有更大到达顺序的子类将会后画。
     *
     * @warning 这个方法在内部被用于localZOrder排序，不能手动的改变。
     *
     * @param orderOfArrival   到达顺序。
     */
    void setOrderOfArrival(int orderOfArrival);
    /**
     * 返回到达顺序，指出哪一个子类先被添加。
     *
     * @see `setOrderOfArrival(unsigned int)`
     *
     * @return 到达顺序。
     */
    int getOrderOfArrival() const;


    /** @deprecated 不再需要
    * @js NA
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE void setGLServerState(int serverState) { /* ignore */ };
    /** @deprecated 不再需要。
    * @js NA
    * @lua NA
    */
    CC_DEPRECATED_ATTRIBUTE int getGLServerState() const { return 0; }

    /**
     * 设置抹点为（0,0）当你摆放这个节点的时候。
     *
     * 这是一个内部方法，仅仅被Layer和Scene使用。不要在框架外调用。
     * 默认值是false,但是在Layer和Scene中是true.
     *
     * @param ignore    true 如果锚点是（0,0）当你摆放这个节点的时候。
     * @todo 这个方法应该被命名为setIgnoreAnchorPointForPosition(bool) 或者其他的有“set”的名称。
     */
    virtual void ignoreAnchorPointForPosition(bool ignore);
    /**
     * 得到节点的锚点是否为（0,0），当你摆放这个节点时。
     *
     * @see `ignoreAnchorPointForPosition(bool)`
     *
     * @return true 如果锚点是 (0,0) 当你摆放这个节点时。
     */
    virtual bool isIgnoreAnchorPointForPosition() const;

    /// @}  end of Setters & Getters for Graphic Properties


    /// @{
    /// @name Children and Parent

    /**
     * 添加一个子节点到容器内，z-order是0.
     *
     * 如果子节点被添加到了一个“running（活动着的）”节点，那么'onEnter'喝 'onEnterTransitionDidFinish' 将会立即调用。
     *
     * @param child 一个子节点。
     */
    virtual void addChild(Node * child);
    /**
     * 添加一个子节点到容器中，参数有一个局部Z轴顺序。
     *
     * 如果子节点被添加到了一个“running（活动着的）”节点，那么'onEnter'喝 'onEnterTransitionDidFinish' 将会立即调用。
     *
     * @param child     一个子节点。
     * @param zOrder    Z轴顺序为了绘画的优先权。 请参考 `setLocalZOrder(int)`
     */
    virtual void addChild(Node * child, int localZOrder);
    /**
     * 添加一个子节点到容器中，有Z轴顺序和一个标记。
     *
     * 如果子节点被添加到了一个“running（活动着的）”节点，那么'onEnter'喝 'onEnterTransitionDidFinish' 将会立即调用。
     *
     * @param child    一个子节点
     * @param zOrder    Z轴顺序为了绘画的优先权。 请参考 `setLocalZOrder(int)`
     * @param tag       一个用来更容易分辨节点的整数。请参考 `setTag(int)`
     */
    virtual void addChild(Node* child, int localZOrder, int tag);
    /**
     * 从容器中得到一个子节点通过它的标记。
     *
     * @param tag   一个标识符用于找到子节点。
     *
     * @return 一个标记与输入的参数相同的节点对象。
     */
    virtual Node * getChildByTag(int tag);
    /**
     * 返回子节点数组。
     *
     * @return 子节点数组。
     */
    virtual Vector<Node*>& getChildren() { return _children; }
    virtual const Vector<Node*>& getChildren() const { return _children; }
    
    /** 
     * 返回子节点的总数
     *
     * @return 子节点的总数
     */
    virtual ssize_t getChildrenCount() const;

    /**
     * 设置父节点Sets the parent node
     *
     * @param parent    指向父节点的指针。
     */
    virtual void setParent(Node* parent);
    /**
     * 返回指向父节点的指针。
     *
     * @see `setParent(Node*)`
     *
     * @returns 指向父节点的指针。
     */
    virtual Node* getParent() { return _parent; }
    virtual const Node* getParent() const { return _parent; }


    ////// REMOVES //////

    /**
     * 从父节点中删除一个节点，有一个cleanup参数。
     * 如果这个节点是一个孤节点，那么什么都不会发生。
     * @see `removeFromParentAndCleanup(bool)`
     */
    virtual void removeFromParent();
    /**
     * 从父节点中删除一个节点
     * 如果这个节点是一个孤节点，那么什么都不会发生。
     * @param cleanup   true 在这个节点上所有的动作和回调都会被删除, false 就不会删除。
     * @js removeFromParent
     * @lua removeFromParent
     */
    virtual void removeFromParentAndCleanup(bool cleanup);

    /**
     * 从容器中删除一个孩子，取决于cleanup参数同时会清除所有的活动的动作。
     *
     * @param child     被删除的子节点。
     * @param cleanup   true 在这个节点上所有的动作和回调都会被删除, false 就不会删除。
     */
    virtual void removeChild(Node* child, bool cleanup = true);

    /**
     * 从一个容器中删除一个孩子通过标记值。取决于cleanup参数同时会清除所有的活动的动作。
     *
     * @param tag       一个用于识别子节点的整数。
     * @param cleanup   true 在这个节点上所有的动作和回调都会被删除， false 就不会删除。
     */
    virtual void removeChildByTag(int tag, bool cleanup = true);
    /**
     * 从容器中删除所有的孩子，with a cleanup。
     *
     * @see `removeAllChildrenWithCleanup(bool)`
     */
    virtual void removeAllChildren();
    /**
     * 从容器中删除所有的孩子, 取决于cleanup参数同时会清除所有的活动的动作。
     *
     * @param cleanup   true 在这个节点上所有的动作和回调都会被删除, false 就不会删除。
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup);

    /**
     * 对一个孩子重新排序，设定一个新的z轴的值。
     *
     * @param child     一个已经被添加的子节点，它必须是已经添加的。
     * @param localZOrder Z轴顺序为了绘画优先级，请参考setLocalZOrder(int)
     */
    virtual void reorderChild(Node * child, int localZOrder);

    /**
     * 在绘画之前，排列所有的孩子数组一次，而不是每次添加或者删除子节点时都排序。
     * 这个方法可以大量地提高性能。
     * @note 不要手动调用这个方法，除非一个添加过的子节点将要被删除在这个结构内。
     */
    virtual void sortAllChildren();

    /// @} end of Children and Parent
    
    /// @{
    /// @name Tag & User 数据

    /**
     * 返回一个用来更简单分辨节点的标记。
     *
     * @return 一个分辨节点的整数。
     */
    virtual int getTag() const;
    /**
     * 改变这个用来更容易分辨节点的标记。
     *
     * 请参考 getTag 的相同代码。
     *
     * @param tag   一个分辨节点的整数。
     */
    virtual void setTag(int tag);

    
    /**
     * 返回一个自定义用户数据的指针。
     *
     * 你可以随意设置UserData 指针为, 一个数据块, 结构体或者一个对象。
     *
     * @return 自定义用户数据的指针。
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
     * 设置一个自定义用户数据的指针。
     *
     * 你可以随意设置UserData 指针为, 一个数据块, 结构体或者一个对象，等等。
     * @warning 不要忘记要手动释放内存，Don't forget to release the memory manually,
     *          特别是在你改变这个数据指针之前，和这个节点被自动释放之前。
     *
     * @param userData  一个自定义用户数据指针。
     * @js NA
     * @lua NA
     */
    virtual void setUserData(void *userData);

    /**
     * 返回一个用户分配的对象
     *
     * 和userData类似, 但它拥有的是一个对象而不是void*
     *
     * @return 一个用户分配的对象。
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
     * 返回一个用户分配的对象
     *
     * 和userData类似, 但它拥有的是一个对象而不是void*
     * UserObject将会在这个方法中留存一次
     * 然后之前的UserObject （如果存在的话）将会被释放。
     * UserObject 将会在节点的析构函数中释放。
     *
     * @param userObject    一个用户分配的对象
     */
    virtual void setUserObject(Ref *userObject);

    /// @} end of Tag & User Data


    /// @{
    /// @name GLProgram
    /**
     * 返回当前用于这个节点的GLProgram (shader) 
     *
     * @return 当前用于这个节点的GLProgram (shader)
     */
    GLProgram* getGLProgram();
    CC_DEPRECATED_ATTRIBUTE GLProgram* getShaderProgram() { return getGLProgram(); }

    GLProgramState *getGLProgramState();
    void setGLProgramState(GLProgramState *glProgramState);

    /**
     * 为这个节点设置着色器程序
     *
     * 自从 v2.0, 每一个渲染的节点必须设置它自己的着色器程序。
     * 它应该在初始化阶段被设置。
     @code
     node->setGLrProgram(GLProgramCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
     @endcode
     *
     * @param shaderProgram 着色器程序
     */
    void setGLProgram(GLProgram *glprogram);
    CC_DEPRECATED_ATTRIBUTE void setShaderProgram(GLProgram *glprogram) { setGLProgram(glprogram); }
    /// @} end of Shader Program


    /**
     * 返回节点是否是“running(活动的)”。
     *
     * 如果节点是活动的，它将会允许事件回调就像onEnter(), onExit(), update()
     *
     * @return 节点是否是“running(活动的)”。
     */
    virtual bool isRunning() const;

    /**
     * lua script的时间表
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
