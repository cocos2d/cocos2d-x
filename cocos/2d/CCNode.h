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
     * @return 一个字符串
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
     * 每次当Node进入“stage”时才调用事件回调。
     * 如果Node进入“stage”状态时伴随着一个转换（transition）,那么事件将会在这个转换开始的时候被调用。
     * 在onEnter过程中，你不能够接入“sister/brother”兄妹节点。
     * 如果你重写了onEnter方法，你应该调用它的父类，e.g., Node::onEnter().
     * @js NA
     * @lua NA
     */
    virtual void onEnter();

    /** 每次当Node进入“stage”时才调用事件回调。
     * 如果Node进入“stage”状态时伴随着一个转换（transition）,那么事件将会在这个转换结束的时候被调用。
     * 如果你重写了onEnterTransitionDidFinish方法 你应该调用它的父类, e.g. Node::onEnterTransitionDidFinish()
     * @js NA
     * @lua NA
     */
    virtual void onEnterTransitionDidFinish();

    /**
     * 每次当Node离开“stage”时才调用事件回调。
     * 如果Node离开“stage”状态时伴随着一个转换（transition）, 那么事件将会在这个转换结束的时候被调用。
     * 在onEnter过程中中你不能够接入一个兄妹节点。
     * 如果你重写onExit, 你应该调用它的父类, e.g., Node::onExit().
     * @js NA
     * @lua NA
     */
    virtual void onExit();

    /**
     * 每次当Node离开“stage”时才调用事件回调。
     * 如果Node离开“stage”状态时伴随着一个转换（transition）, 那么事件将会在这个转换开始的时候被调用。
     * @js NA
     * @lua NA
     */
    virtual void onExitTransitionDidStart();

    /// @} end of event callbacks.


    /**
     * 暂停所有的活动着的动作和调度器。
     */
    virtual void cleanup();

    /**
     * 重写这个方法来绘制你自己的节点。
     * 以下的GL状态是默认开启的：
     * - `glEnableClientState(GL_VERTEX_ARRAY);`
     * - `glEnableClientState(GL_COLOR_ARRAY);`
     * - `glEnableClientState(GL_TEXTURE_COORD_ARRAY);`
     * - `glEnable(GL_TEXTURE_2D);`
     * 并且你不能够关闭他们在绘制完你的节点之后。
     * 但是如果你开启了其他的GL状态，那么你要关闭他们在绘制完你的节点之后。
     */
    virtual void draw(Renderer *renderer, const Mat4& transform, bool transformUpdated);
    virtual void draw() final;

    /**
     * 访问节点的孩子，并且循环递归的绘制它们。
     */
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated);
    virtual void visit() final;


    /** 返回包含Node(节点)的Scene（场景）。
     如果这个节点不属于任何的场景，它将返回`nullptr`。
     这个函数循环递归地调用parent->getScene() 直到父类是一个Scene对象。结果不会被缓存。只有当这个函数被用在一个循环中时，用户才会缓存这个结果。
     */
    virtual Scene* getScene();

    /**
     * 返回 一个AABB(轴向包围盒)在它的父坐标系中。
     *
     * @return 一个AABB(轴向包围盒)在它的父坐标系中。
     */
    virtual Rect getBoundingBox() const;

    /** @deprecated 使用 getBoundingBox 来代替 */
    CC_DEPRECATED_ATTRIBUTE inline virtual Rect boundingBox() const { return getBoundingBox(); }

    virtual void setEventDispatcher(EventDispatcher* dispatcher);
    virtual EventDispatcher* getEventDispatcher() const { return _eventDispatcher; };

    /// @{
    /// @name Actions

    /**
     * 设置被所有动作使用的ActionManager对象。
     *
     * @warning 如果你设置了一个新的ActionManager, 那么之前创建的动作将会被删除。
     *
     * @param actionManager     ActionManager被所有动作使用。
     */
    virtual void setActionManager(ActionManager* actionManager);
    /**
     * 得到被所有动作使用的ActionManager对象。
     * @see setActionManager(ActionManager*)
     * @return ActionManager对象。
     */
    virtual ActionManager* getActionManager() { return _actionManager; }
    virtual const ActionManager* getActionManager() const { return _actionManager; }

    /**
     * 执行一个动作，并且返回执行的该动作。
     *
     * 这个节点将会变成动作的目标，参考Action::getTarget()
     * @warning Actions（动作）不存储它的目标。
     *
     * @return Action（动作）指针
     */
    Action* runAction(Action* action);

    /**
     * 停止并且删除所有的动作从活动动作列表中。
     */
    void stopAllActions();

    /**
     * 停止并且删除所有的动作从活动动作列表中。
     *
     * @param action    将要被删除的动作对象。
     */
    void stopAction(Action* action);

    /**
     * 通过动作的标记从活动动作列表中删除一个动作。
     *
     * @param tag   一个指示将要被删除的动作的标记。
     */
    void stopActionByTag(int tag);

    /**
     * 通过动作的标记从活动动作列表中得到一个动作。
     *
     * @see `setTag(int)`, `getTag()`.
     *
     * @return 动作对象拥有给定的标记。
     */
    Action* getActionByTag(int tag);

    /**
     * 返回活动着的动作加上正在调度运行的动作的总数 (在actionsToAdd状态的动作和动作数组中的).
     *
     * 组成的动作被记为一个动作。例如：
     *    如果你正在运行7个活动中的1Sequence, 它将返回 1.
     *    如果你正在运行2个动作中的7个Sequencesm,它将返回 7.
     * @todo Rename to getNumberOfRunningActions()
     *
     * @return 返回活动着的动作加上正在调度运行的动作的总数
     */
    ssize_t getNumberOfRunningActions() const;

    /** @deprecated Use getNumberOfRunningActions() instead */
    CC_DEPRECATED_ATTRIBUTE ssize_t numberOfRunningActions() const { return getNumberOfRunningActions(); };

    /// @} end of Actions


    /// @{
    /// @name Scheduler and Timer

    /**
     * 设置一个调度器对象来用于调度所有的“update”和定时器。
     *
     * @warning 如果你设置了一个新的调度器，那么之前创建的timers/update将会被删除。
     * @param scheduler     一个调度器对象来用于调度所有的“update”和定时器。
     */
    virtual void setScheduler(Scheduler* scheduler);
    /**
     * 得到调度器对象。
     *
     * @see setScheduler(Scheduler*)
     * @return 一个调度器对象。
     */
    virtual Scheduler* getScheduler() { return _scheduler; }
    virtual const Scheduler* getScheduler() const { return _scheduler; }


    /**
     * 检查是否一个选择器是预定的。
     *
     * @param selector      函数选择器。
     * @return 是否函数选择器是预定的。
     * @js NA
     * @lua NA
     */
    bool isScheduled(SEL_SCHEDULE selector);

    /**
     * 调度“update”方法。
     *
     * 它将会使用顺序数字0，这个方法将会在每一帧都被调用。
     * 拥有低顺序值的调度方法将会在有用高顺序值的方法之前被调用。
     * 只有一“update" 能够被调度，在每一个节点。
     * @js NA
     * @lua NA
     */
    void scheduleUpdate(void);

    /**
     * 调度这个"update"方法伴随着一个自定义优先级。
     *
     * 这个选择器将会在每一帧被调用。
     * 拥有低顺序值的调度方法将会在有用高顺序值的方法之前被调用。
     * 只有一“update" 能够被调度，在每一个节点(你不能够有2个“update”选择器).
     * @js NA
     * @lua NA
     */
    void scheduleUpdateWithPriority(int priority);

    /*
     * 不调度"update" 方法。
     * @see scheduleUpdate();
     */
    void unscheduleUpdate(void);

    /**
     * 调度一个自定义的选择器。
     *
     * 如果这个选择器已经被调度了，那么内部的参数将会被更新而不用再次调度一遍。
     @code
     // 首先，实现一个调度方法。
     void MyNode::TickMe(float dt);
     // 将这个方法添加到选择器中通过schedule_selector宏。
     this->schedule(schedule_selector(MyNode::TickMe), 0, 0, 0);
     @endcode
     *
     * @param selector  将被调度的 SEL_SCHEDULE 选择器。
     * @param interval  以秒为时间间隔。0代表时间间隔为每帧。如果interval = 0,那就需要使用 scheduleUpdate()来代替。
     * @param repeat    这个选择器将会被执行的次数（repeat+1）,你可以使用kRepeatForever来无限重复。
     * @param delay     第一个时间间隔开始执行前的等待总时间。
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);

    /**
     * 调度一个自定义的选择器伴随着一个以秒为单位的内部时间。
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector      将会被调度的SEL_SCHEDULE选择器。
     * @param interval      回调以秒为单位的内部时间，0代表以每帧为时间间隔。
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector, float interval);

    /**
     * 调度一个只运行一次的选择器，伴随着一个0或者更大的延期。
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector      将会被调度的SEL_SCHEDULE选择器。
     * @param delay         第一个时间间隔开始执行前的等待总时间。
     * @lua NA
     */
    void scheduleOnce(SEL_SCHEDULE selector, float delay);

    /**
     * 调度一个自定义的选择器，这个调度后的选择器将会以每帧为时间间隔。
     * @see schedule(SEL_SCHEDULE, float, unsigned int, float)
     *
     * @param selector      作为选择器的一个函数。
     * @lua NA
     */
    void schedule(SEL_SCHEDULE selector);

    /**
     * 不调度一个自定义的选择器。
     * @see `schedule(SEL_SCHEDULE, float, unsigned int, float)`
     *
     * @param selector     作为选择器的一个函数。
     * @lua NA
     */
    void unschedule(SEL_SCHEDULE selector);

    /**
     * 不调度所有的调度过的选择器： 自定义选择器, 和 'update' 选择器。
     * 动作不受这个方法的影响。
     * @lua NA
     */
    void unscheduleAllSelectors(void);

    /**
     * 恢复所有的调度过的选择器，动作和事件监听器。
     * 这个方法被onEnter方法在内部调用。
     */
    void resume(void);
    /**
     * 暂停所有的调度过的选择器，动作和事件监听器。
     * 这个方法被onExit方法在内部调用。
     */
    void pause(void);

    /**
     * 恢复所有的调度过的选择器，动作和事件监听器。
     * 这个方法被onEnter方法在内部调用。
     */
    CC_DEPRECATED_ATTRIBUTE void resumeSchedulerAndActions(void);
    /**
     * 暂停所有的调度过的选择器，动作和事件监听器。
     * 这个方法被onExit方法在内部调用。
     */
    CC_DEPRECATED_ATTRIBUTE void pauseSchedulerAndActions(void);

    /*
     * 更新方法将会被自动调用如果"scheduleUpdate"每帧都被调用的话, 并且这个节点是"live"
     */
    virtual void update(float delta);

    /// @} end of Scheduler and Timer

    /// @{
    /// @name Transformations

    /**
     * 递归的调用孩子的updateTransform()方法。
     *
     * 这个方法从Sprite类中删除，因此它不再适用于Sprite.
     * 因此，你应该提供SpriteBatchNode的最佳化在你自定义的节点上。
     * e.g., `batchNode->addChild(myCustomNode)`, 以前你可以只addChild(sprite)
     */
    virtual void updateTransform();

    /**
     * 返回这个将节点（局部）的空间坐标系转换成父节点的空间坐标系的矩阵。
     * 这个矩阵以像素为单位。
     */
    virtual const Mat4& getNodeToParentTransform() const;
    virtual AffineTransform getNodeToParentAffineTransform() const;

    /** 
     * 手动设置变换矩阵。
     */
    virtual void setNodeToParentTransform(const Mat4& transform);

    /** @deprecated use getNodeToParentTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToParentTransform() const { return getNodeToParentAffineTransform(); }

    /**
     * 返回这个将父节点的空间坐标系转换成节点（局部）的空间坐标系转的矩阵。
     * 这个矩阵以像素为单位。
     */
    virtual const Mat4& getParentToNodeTransform() const;
    virtual AffineTransform getParentToNodeAffineTransform() const;

    /** @deprecated Use getParentToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform parentToNodeTransform() const { return getParentToNodeAffineTransform(); }

    /**
     * 返回世界仿射变换矩阵。矩阵单位是像素。
     */
    virtual Mat4 getNodeToWorldTransform() const;
    virtual AffineTransform getNodeToWorldAffineTransform() const;

    /** @deprecated Use getNodeToWorldTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform nodeToWorldTransform() const { return getNodeToWorldAffineTransform(); }

    /**
     * 返回逆世界仿射变换矩阵。矩阵单位是像素。
     */
    virtual Mat4 getWorldToNodeTransform() const;
    virtual AffineTransform getWorldToNodeAffineTransform() const;


    /** @deprecated Use getWorldToNodeTransform() instead */
    CC_DEPRECATED_ATTRIBUTE inline virtual AffineTransform worldToNodeTransform() const { return getWorldToNodeAffineTransform(); }

    /// @} end of Transformations


    /// @{
    /// @name Coordinate Converters

    /**
     * 将Vec2 转换成节点 (局部) 空间坐标系。结果按以Points为单位。
     */
    Vec2 convertToNodeSpace(const Vec2& worldPoint) const;

    /**
     * 将Vec2转换成世界空间坐标系。结果按以Points为单位。
     */
    Vec2 convertToWorldSpace(const Vec2& nodePoint) const;

    /**
     * 将Vec2转换成节点(局部)空间坐标系. 结果按以Points为单位。
     * 将returned/received节点的point当作相对应的锚点。
     */
    Vec2 convertToNodeSpaceAR(const Vec2& worldPoint) const;

    /**
     * 将局部的Vec2转换成世界空间坐标系。结果按以Points为单位。
     * 将returned/received节点的point当作相对应的锚点。
     */
    Vec2 convertToWorldSpaceAR(const Vec2& nodePoint) const;

    /**
     * 一个方便的方法将触摸转换成Vec2
     */
    Vec2 convertTouchToNodeSpace(Touch * touch) const;

    /**
     * 将Touch (世界坐标系) 转换成局部坐标系。这个方法是AR (相对的锚点).
     */
    Vec2 convertTouchToNodeSpaceAR(Touch * touch) const;

	/**
     *  为节点设置一个附加转换矩阵。
     *
     *  为了删除它，再一次调用它通过传入参数“nullptr”.
     *
     *  @note 这个附加转换将会连接在getNodeToParentTransform之后。
     *        它将被用于模拟`parent-child`的关系在两个节点之间(e.g. 其中一个在BatchNode中, 另一个却不在).
     */
    void setAdditionalTransform(Mat4* additionalTransform);
    void setAdditionalTransform(const AffineTransform& additionalTransform);

    /// @} end of Coordinate Converters

      /// @{
    /// @name component functions
    /**
     *   通过名字得到组件
     */
    Component* getComponent(const std::string& pName);

    /**
     *   添加一个组件
     */
    virtual bool addComponent(Component *pComponent);

    /**
     *   通过名字删除一个组件
     */
    virtual bool removeComponent(const std::string& pName);

    /**
     *   删除所有组件
     */
    virtual void removeAllComponents();
    /// @} end of component functions


#if CC_USE_PHYSICS
    /**
     *   设置PhysicsBody来让精灵sprite有物理效应。
     * @note 这个方法将会设置Vec2::ANCHOR_MIDDLE锚点如果身体非空, 并且你不可以改变这个锚点如果节点有物理身体。
     */
    void setPhysicsBody(PhysicsBody* body);

    /**
     *   得到精灵拥有的PhysicsBody
     */
    PhysicsBody* getPhysicsBody() const;

#endif
    
    // 重写
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
    // 节点应该被创建通过使用create();
    Node();
    virtual ~Node();

    virtual bool init();

protected:
    /// 较慢的分配
    void childrenAlloc(void);
    
    /// 记录孩子的助手
    void insertChild(Node* child, int z);

    /// 删除一个孩子，调用child->onExit(), 从子数列中做清理，并删除它。
    void detachChild(Node *child, ssize_t index, bool doCleanup);

    ///转换cocos2d 坐标系到用户界面窗口坐标
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

    float _rotationX;               ///< X轴的旋转
    float _rotationY;               ///< Y轴的旋转

    // 旋转Z轴被分成2个用来模拟Flash动画倾斜。
    float _rotationZ_X;             ///< 旋转角度在Z轴，组件X轴
    float _rotationZ_Y;             ///< 旋转角度在Z轴，组件Y轴

    float _scaleX;                  ///< X轴的缩放因子
    float _scaleY;                  ///< Y轴的缩放因子
    float _scaleZ;                  ///< Z轴的缩放因子

    Vec2 _position;                ///< 节点的位置
    float _positionZ;               ///< OpenGL 真正Z轴坐标位置

    float _skewX;                   ///< X轴的倾斜角
    float _skewY;                   ///< Y轴的倾斜角

    Vec2 _anchorPointInPoints;     ///< 锚点以points为单位
    Vec2 _anchorPoint;             ///< 正常的锚点(不是以points为单位的)

    Size _contentSize;              ///< 未转换节点的大小

    Mat4 _modelViewTransform;    ///< 节点的模型视图变换

    // "cache" 可以是可变的
    mutable Mat4 _transform;      ///< 变换
    mutable bool _transformDirty;   ///< transform dirty flag
    mutable Mat4 _inverse;        ///< 逆变换
    mutable bool _inverseDirty;     ///< inverse transform dirty flag
    mutable Mat4 _additionalTransform; ///< 变换
    bool _useAdditionalTransform;   ///< The flag to check whether the additional transform is dirty
    bool _transformUpdated;         ///< 是否Transform 对象在最后一帧更新了

    int _localZOrder;               ///< Local 顺序 (和兄妹节点相关) 被用于节点的排序
    float _globalZOrder;            ///< Global 顺序 用于节点的排序

    Vector<Node*> _children;        ///< 子节点数列
    Node *_parent;                  ///< 父节点的弱引用

    int _tag;                         ///<一个标记. 你可以定义任何的数字来分辨这个节点
    
    std::string _name;               ///<一个字符串标签, 一个用户定义的字符串来分辨这个节点

    void *_userData;                ///< 一个用户分配的空指针，能够指向任何cpp对象
    Ref *_userObject;               ///< 一个用户分配的对象

    GLProgramState *_glProgramState; ///< OpenGL Program State

    int _orderOfArrival;            ///< 用于保存序列当对有相同localZOrder的子节点进行排序

    Scheduler *_scheduler;          ///< 调度器用于调度定时器和更新

    ActionManager *_actionManager;  ///< 一个指向ActionManager singleton模式的指针, 用于操作所有的动作。

    EventDispatcher* _eventDispatcher;  ///< 事件调度器使用调度各种事件

    bool _running;                  ///< 活动中

    bool _visible;                  ///< 节点可见

    bool _ignoreAnchorPointForPosition; ///< true 如果锚点 Vec2 是 (0,0) 当你拜访节点时, false则不是（0，0）
                                          ///< 被Layer和Scene使用

    bool _reorderChildDirty;          ///< children order dirty flag
    bool _isTransitionFinished;       ///< 一个表明转换是否完成的标记

#if CC_ENABLE_SCRIPT_BINDING
    int _scriptHandler;               ///< 对onEnter()和onExit()的脚本处理器，用于Javascript binding和Lua binding.
    int _updateScriptHandler;         ///< 对update() 每帧回调的脚本处理器，从 lua和javascript中调用。
    ccScriptType _scriptType;         ///< 脚本绑定的类型, lua 或者javascript
#endif
    
    ComponentContainer *_componentContainer;        ///< Dictionary of components

#if CC_USE_PHYSICS
    PhysicsBody* _physicsBody;        ///< 节点拥有的physicsBody
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

/** NodeRGBA是节点的子类，实现RGBAProtocol协议。
 
 节点的所有特点都是有效的，加上如下的一些新特点：
 - opacity
 - RGB colors
 
 Opacity/Color 传播到符合RGBAProtocol协议的孩子中，如果cascadeOpacity/cascadeColor 是可行的。
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
