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

#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"

/**
 * @addtogroup ui
 * @{
 */

NS_CC_BEGIN

class DrawNode;
class LayerColor;
class LayerGradient;


namespace ui {
    
class LayoutManager;
class Scale9Sprite;

/**
 * @brief @~english Layout interface for creating LayoutManger and do actual layout.
 * @~chinese 布局界面，用于创建LayoutManger布局。
 * @js NA
 */
class CC_GUI_DLL LayoutProtocol
{
public:
    /**
     * @brief @~english Default constructor.
     * @~chinese 默认构造函数。
     */
    LayoutProtocol(){}

    /**
     * @brief @~english Default destructor.
     * @~chinese 默认的析构函数。
     */
    virtual ~LayoutProtocol(){}

    /**
     * @brief @~english Create a custom layout manager.
     * @~chinese 创建一个布局管理器。
     * 
     * @return @~english A LayoutManager descendants instance.
     * @~chinese LayoutManager后代实例。
     */
    virtual LayoutManager* createLayoutManager() = 0;
    
    /**
     * @brief @~english Return the content size of layout.
     * @~chinese 返回Layout的content大小。
     * 
     * @return @~english A content size in Size.
     * @~chinese 一个content尺寸。
     */
    virtual Size getLayoutContentSize()const = 0;
    
    /**
     * @brief @~english Get all elements of the layout.
     * @~chinese 获取Layout内所有的元素。
     * 
     * @return @~english A vector of Node pointers.
     * @~chinese 一个包含节点的指针的数组。
     */
    virtual const Vector<Node*>& getLayoutElements()const = 0;
    
    /**
     * @brief @~english The main function to do the layout job.
     *  Different layout manager should implement its own layout algorithm.
     *
     * @~chinese 布局功能的主要函数。
     * 不同的布局管理器应该实现自己的布局算法。
     * 
     */
    virtual void doLayout() = 0;
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef RELATIVE
#undef RELATIVE
#endif
#endif

/**
 * @brief @~english A container for holding a few child widgets.
 * The child widgets could be rearranged according to the layout type and it also enables clipping, set background image and color.
 *
 * There are mainly four types of layout:
 * - Absolute layout: This the default layout type, child elements are arranged by their absolute position.
 * - Horizontal layout: child elements are arranged horizontally.
 * - Vertical layout: child elements are arranged vertically.
 * - Relative layout: child elements are arranged relative to certain rules.
 *
 * @~chinese 一个包含控件的容器。
 * 子节点可以根据布局类型重新排序,它还可以开启剪裁,设置背景图像和颜色。
 * 
 * 主要有四种类型的布局:
 * - 绝对布局:这个默认的布局类型、子元素按照绝对位置排列。
 * - 水平布局:子元素水平排列。
 * - 垂直布局:子元素垂直排列。
 * - 相对布局:子元素相对于一定的规则排列。
 * 
 */
class CC_GUI_DLL Layout : public Widget, public LayoutProtocol
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * @~english
     * Layout type, default is ABSOLUTE.
     * @~chinese 
     * 布局类型,默认是绝对(ABSOLUTE)布局。
     */
    enum class Type
    {
        ABSOLUTE,
        VERTICAL,
        HORIZONTAL,
        RELATIVE
    };
    
    /**
     * @~english
     * Clipping Type, default is STENCIL.
     * @~chinese 
     * 剪裁类型,默认是STENCIL。
     */
    enum class ClippingType
    {
        STENCIL,
        SCISSOR
    };
    
    /**
     * @~english
     * Background color type, default is NONE.
     * @~chinese 
     * 背景颜色类型, 默认是NONE.
     */
    enum class BackGroundColorType
    {
        NONE,
        SOLID,
        GRADIENT
    };
    
    /**
     * @~english
     * Default constructor
     * @~chinese 
     * 默认构造函数
     * @js ctor
     * @lua new
     */
    Layout();
    
    /**
     * @~english
     * Default destructor
     * @~chinese 
     * 默认的析构函数
     * @js NA
     * @lua NA
     */
    virtual ~Layout();
    
    /**
     * @~english
     * Create a empty layout.
     * @~chinese 
     * 创建一个空的layout。
     */
    static Layout* create();
    
    /**
     * @~english
     * Sets a background image for layout.
     * @~chinese 
     * 设置layout的背景图像。
     * 
     * @param fileName @~english image file path.
     * @~chinese 图像文件路径。
     * @param texType @see TextureResType. 
     */
    void setBackGroundImage(const std::string& fileName,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * @~english
     * Sets a background image capInsets for layout, it only affects the scale9 enabled background image
     * @~chinese 
     * 设置layout背景的capInsets,它只在开启scale9后影响背景图的渲染
     * 
     * @param capInsets @~english The capInsets in Rect.
     * @~chinese capInsets的矩形。
     * 
     */
    void setBackGroundImageCapInsets(const Rect& capInsets);
    
    /**
     * @~english
     * Query background image's capInsets size.
     * @~chinese 
     * 查询背景图像的capInsets。
     * @return @~english The background image capInsets.
     * @~chinese 背景图像的capInsets。
     */
    const Rect& getBackGroundImageCapInsets()const;
    
    /**
     * @~english
     * Sets Color Type for layout's background
     * @~chinese 
     * 设置布局的背景颜色类型
     * 
     * @param type   @see `BackGroundColorType`
     */
    void setBackGroundColorType(BackGroundColorType type);
    
    /**
     * @~english
     * Query the layout's background color type.
     * @~chinese 
     * 查询布局的背景颜色类型。
     * @return @~english The layout's background color type.
     * @~chinese 布局的背景颜色类型。
     */
    BackGroundColorType getBackGroundColorType()const;
    
    /**
     * @~english
     * Enable background image scale9 rendering.
     * @~chinese 
     * 开启背景图像scale9的渲染模式。
     * 
     * @param enabled @~english True means enable scale9 rendering for background image, false otherwise.
     * @~chinese 传入true则开启，false则关闭scale9渲染
     */
    void setBackGroundImageScale9Enabled(bool enabled);
    
    /**
     * @~english
     * Query background image scale9 enable status.
     * @~chinese 
     * 查询背景图像scale9启用状态。
     * @return @~english Whether background image is scale9 enabled or not.
     * @~chinese 是否启用scale9背景图像。
     */
    bool isBackGroundImageScale9Enabled()const;
    
    /**
     * @~english
     * Set background color for layout
     * The color only applies to layout when it's color type is BackGroundColorType::SOLID
     *
     * @~chinese 
     * 设置layout的背景颜色
     * 仅当颜色类型为BackGroundColorType::SOLID的时候，才会影响Layout
     * 
     * @param color @~english Color in Color3B.
     * @~chinese Color3B类型的颜色。
     */
    void setBackGroundColor(const Color3B &color);
    
    /**
     * @~english
     * Query the layout's background color.
     * @~chinese 
     * 查询布局的背景颜色。
     *
     * @return @~english Background color in Color3B.
     * @~chinese Color3B类型的背景颜色。
     */
    const Color3B& getBackGroundColor()const;
    
    /**
     * @~english
     * Set start and end background color for layout.
     * This setting only take effect when the layout's  color type is BackGroundColorType::GRADIENT
     * @~chinese 
     * 为布局设置开始和结束的背景颜色。
     * 该设置只当布局的颜色类型是BackGroundColorType::GRADIENT时生效
     * 
     * @param startColor @~english Color value in Color3B.
     * @~chinese Color3B类型的颜色。
     * @param endColor @~english Color value in Color3B.
     * @~chinese Color3B类型的颜色。
     */
    void setBackGroundColor(const Color3B &startColor, const Color3B &endColor);
    
    /**
     * @~english
     * Get the gradient background start color.
     * @~chinese 
     * 获取渐变背景颜色开始的值。
     * @return @~english Gradient background start color value.
     * @~chinese 渐变背景颜色开始的值。
     */
    const Color3B& getBackGroundStartColor()const;
    
    /**
     * @~english
     * Get the gradient background end color.
     * @~chinese 
     * 获取渐变背景颜色的结束值。
     * @return @~english Gradient background end color value.
     * @~chinese 渐变背景颜色结束的值。
     */
    const Color3B& getBackGroundEndColor()const;
    
    /**
     * @~english
     * Sets background color opacity of layout.
     * @~chinese 
     * 设置布局的背景颜色不透明度。
     * 
     * @param opacity @~english The opacity in `GLubyte`.
     * @~chinese “GLubyte”不透明度。
     */
    void setBackGroundColorOpacity(GLubyte opacity);
    
    /**
     * @~english
     * Get the layout's background color opacity.
     * @~chinese 
     * 获取布局的背景颜色不透明度。
     * @return @~english Background color opacity value.
     * @~chinese 背景颜色的不透明值。
     */
    GLubyte getBackGroundColorOpacity()const;
    
    /**
     * @~english
     * Sets background color vector for layout.
     * This setting only take effect when layout's color type is BackGroundColorType::GRADIENT
     * @~chinese 
     * 设置布局的背景颜色矢量。
     * 该设置只当布局的颜色类型是BackGroundColorType::GRADIENT时生效
     * 
     * @param vector @~english The color vector in `Vec2`.
     * @~chinese Vec2类型的颜色向量。
     */
    void setBackGroundColorVector(const Vec2 &vector);
    
    /**
     * @~english
     * Get the layout's background color vector.
     * @~chinese 
     * 获取layout的背景颜色向量。
     * @return @~english Background color vector.
     * @~chinese 背景颜色向量。
     */
    const Vec2& getBackGroundColorVector()const;
    
    /**
     * @~english
     * Set layout's background image color.
     * @~chinese 
     * 设置layout背景图像的颜色。
     * @param color @~english Background color value in `Color3B`.
     * @~chinese Color3B类型的背景颜色值。
     */
    void setBackGroundImageColor(const Color3B& color);
    
    /**
     * @~english
     * Set opacity of background image.
     * @~chinese 
     * 设置背景图像的不透明度。
     * @param opacity @~english Background image opacity in GLubyte.
     * @~chinese 背景图像在GLubyte的不透明度。
     */
    void setBackGroundImageOpacity(GLubyte opacity);
    
    /**
     * @~english
     * Get color of layout's background image.
     * @~chinese 
     * 得到layout的背景图像颜色。
     *
     * @return @~english Layout's background image color.
     * @~chinese layout的背景图像的颜色。
     */
    const Color3B& getBackGroundImageColor()const;
    
    /**
     * @~english
     * Get the opacity of layout's background image.
     * @~chinese 
     * 获取layout的背景图像不透明度。
     *
     * @return @~english The opacity of layout's background image.
     * @~chinese layout背景图片的不透明度.
     */
    GLubyte getBackGroundImageOpacity()const;
    
    /**
     * @~english
     * Remove the background image of layout.
     * @~chinese 
     * 删除layout的背景图像。
     */
    void removeBackGroundImage();
    
    /**
     * @~english
     * Gets background image texture size.
     * @~chinese 
     * 获取背景图像纹理大小。
     * 
     * @return @~english background image texture size.
     * @~chinese 背景图像纹理大小。
     */
    const Size& getBackGroundImageTextureSize() const;
    
    /**
     * @~english
     * Toggle layout clipping.
     * If you do need clipping, you pass true to this function.
     * @~chinese 
     * 切换布局剪裁。
     * 如果你需要裁剪,你需要传递true给这个函数。
     * 
     * @param enabled @~english Pass true to enable clipping, false otherwise.
     * @~chinese 传入true则开启裁剪模式，false则关闭
     */
    virtual void setClippingEnabled(bool enabled);
    
    
    /**
     * @~english
     * Change the clipping type of layout.
     * On default, the clipping type is `ClippingType::STENCIL`.
     * @~chinese 
     * 改变layout的剪裁类型。
     * 在默认情况下,剪切类型是“ClippingType:STENCIL”。
     * @see `ClippingType`
     * @param type @~english The clipping type of .
     * @~chinese layout的剪裁类型。
     */
    void setClippingType(ClippingType type);

    /**
     * @see `setClippingType(ClippingType)`
     */
    ClippingType getClippingType()const;
    
    /**
     * @~english
     * Gets if layout is clipping enabled.
     * @~chinese 
     * 获取layout是否开启了剪裁。
     * 
     * @return @~english if layout is clipping enabled.
     * @~chinese 是否启用了布局是剪裁。
     */
    virtual bool isClippingEnabled()const;
    
    /**
     * @~english
     * Returns the "class name" of widget.
     * @~chinese 
     * 返回组件的类名
     */
    virtual std::string getDescription() const override;
    
    /**
     * @~english
     * Change the layout type.
     * @~chinese 
     * 改变布局类型。
     *@param type @~english Layout type.
     * @~chinese 布局类型。
     */
    virtual void setLayoutType(Type type);
    
    /**
     * @~english
     * Query layout type.
     * @~chinese 
     * 查询layout类型。
     * @return @~english Get the layout type.
     * @~chinese layout类型
     */
    virtual  Type getLayoutType() const;

    
    virtual void addChild(Node* child)override;
    virtual void addChild(Node * child, int localZOrder)override;
    /**
     * @~english
     * Adds a child to the container with z order and tag
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @~chinese 
     * 根据z order和标签添加一个子节点到容器
     * 如果子节点被添加到一个正在运行的节点,“onEnter”和“onEnterTransitionDidFinish”将立即被执行。
     * 
     * @param child @~english A child node
     * @~chinese 一个子节点
     * @param localZOrder @~english Z order for drawing priority. Please refer to setLocalZOrder(int)
     * @~chinese z order绘制优先级。请参阅setLocalZOrder(int)
     * @param tag @~english A integer  to identify the node easily. Please refer to setTag(int)
     * @~chinese 一个整数，用于识别节点。请参阅setTag(int)
     */
    virtual void addChild(Node* child, int localZOrder, int tag) override;
    virtual void addChild(Node* child, int localZOrder, const std::string &name) override;
    
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

    virtual void removeChild(Node* child, bool cleanup = true) override;
    
    /**
     * @~english
     * Removes all children from the container with a cleanup.
     *
     * @~chinese 
     * 从容器中删除所有的子节点。
     * 
     * @see `removeAllChildrenWithCleanup(bool)`
     */
    virtual void removeAllChildren() override;

    /**
     * @~english
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @~chinese 
     * 从容器中删除所有子节点，并做对应的清理工作 - 根据不同的参数，清理所有正在运行的actions。
     * 
     * @param cleanup @~english true if all running actions on all children nodes should be cleanup, false otherwise.
     * @~chinese 如果传入true则清理所有子节点的actions，false则不清理
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;

    /**
     * @~english
     * force refresh widget layout
     * @~chinese 
     * 强制刷新控件的布局
     */
    virtual void forceDoLayout();
    
    /**
     * @~english
     * request to refresh widget layout
     * @~chinese 
     * 请求刷新控件的布局
     */
    virtual void requestDoLayout();
    
    /**
     * @lua NA
     */
    virtual void onEnter() override;
    
    /**
     * @lua NA
     */
    virtual void onExit() override;
    
    /**
     * @~english
     * If a layout is loop focused which means that the focus movement will be inside the layout
     * @~chinese 
     * 如果一个布局是循环获取焦点，这意味着焦点在layout中移动
     * @param loop @~english pass true to let the focus movement loop inside the layout
     * @~chinese 传入true则设置内部焦点可以循环传递
     */
    void setLoopFocus(bool loop);
    
    /**
     * @return @~english If focus loop is enabled, then it will return true, otherwise it returns false. The default value is false.
     * @~chinese 如果启用了焦点循环,那么它将返回true,否则返回false。默认值是false。
     */
    bool isLoopFocus()const;
    
    /**
     * @param pass @~english To specify whether the layout pass its focus to its child
     * @~chinese 要指定layout是否传递焦点到它的子节点上
     */
    void setPassFocusToChild(bool pass);
    
    /**
     * @return @~english To query whether the layout will pass the focus to its children or not. The default value is true
     * @~chinese 查询布局是否会传递焦点到子节点上。默认值为true
     */
    bool isPassFocusToChild()const;
    
    /**
     * @~english
     *  When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.
     *  If the widget is not in a layout, it will return itself
     * @~chinese 
     * 当一个控件是在layout中，你可以调用这个方法来获得指定的方向中的下一个焦点控件。
     * 如果没有在布局控件,它将返回自己
     * @param direction @~english the direction to look for the next focused widget in a layout
     * @~chinese 寻找下一个方向上的焦点控件
     * @param current  @~english the current focused widget
     * @~chinese 当前的焦点控件
     * @return @~english the next focused widget in a layout
     * @~chinese layout中的下一个焦点控件
     */
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current) override;
    
    /**
     * @~english
     * To specify a user-defined functor to decide which child widget of the layout should get focused
     * @~chinese 
     * 要指定一个用户定义的函来决定哪些布局的子节点控件应该得到焦点
     * @param FocusDirection @~english the finding direction
     * @~chinese 查找的方向
     * @param this @~english previous focused widget
     * @~chinese 之前的焦点控件
     * @return @~english return the index of widget in the layout
     * @~chinese 返回找到的控件
     */
    std::function<int(FocusDirection, Widget*)> onPassFocusToChild;
    
    /** 
     * Override function. Set camera mask, the node is visible by the camera whose camera flag & node's camera mask is true. 
     * @param mask Mask being set
     * @param applyChildren If true call this function recursively from this node to its children.
     */
    virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;

CC_CONSTRUCTOR_ACCESS:
    //override "init" method of widget.
    virtual bool init() override;
    
protected:
    //override "onSizeChanged" method of widget.
    virtual void onSizeChanged() override;
    
    //init background image renderer.
    void addBackGroundImage();
    
    void supplyTheLayoutParameterLackToChild(Widget* child);
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    
    void stencilClippingVisit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags);
    void scissorClippingVisit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags);
    
    void setStencilClippingSize(const Size& size);
    const Rect& getClippingRect();
    
    virtual void doLayout()override;
    virtual LayoutManager* createLayoutManager()override;
    virtual Size getLayoutContentSize()const override;
    virtual const Vector<Node*>& getLayoutElements()const override;
    
    //clipping
    void onBeforeVisitStencil();
    void onAfterDrawStencil();
    void onAfterVisitStencil();

    /**
     * @~english draw fullscreen quad to clear stencil bits
     * @~chinese 绘制屏幕四个角去清除模板
     */
    void drawFullScreenQuadClearStencil();
    
    void onBeforeVisitScissor();
    void onAfterVisitScissor();
    void updateBackGroundImageColor();
    void updateBackGroundImageOpacity();
    void updateBackGroundImageRGBA();
    
    /**
     * @~english
     * get the content size of the layout, it will accumulate all its children's content size
     * @~chinese 
     * 获得layout的内容的大小，它将包含其所有子节点的内容大小
     */
    Size getLayoutAccumulatedSize() const;
    
    /**
     * @~english
     * When the layout get focused, it the layout pass the focus to its child, it will use this method to determine which child 
     * will get the focus.  The current algorithm to determine which child will get focus is nearest-distance-priority algorithm
     * @~chinese 
     * 当layout得到焦点，它会用这种方法来确定传递焦点到哪些子节点
     * 将得到的焦点。目前是依据距离优先算法来确定哪些子节点将得到焦点
     * @param dir @~english next focused widget direction
     * @~chinese 接下来查找焦点的方向
     * @return @~english The index of child widget in the container
     * @~chinese 子控件在容器中的索引
     */
     int findNearestChildWidgetIndex(FocusDirection direction, Widget* baseWidget);
    
    /**
     * @~english
     * When the layout get focused, it the layout pass the focus to its child, it will use this method to determine which child
     * will get the focus.  The current algorithm to determine which child will get focus is farthest-distance-priority algorithm
     * @~chinese 
     * 当layout得到焦点，它会用这种方法来确定传递焦点到哪些子节点
     * 将得到的焦点。目前是依据距离优先算法来确定哪些子节点将得到焦点
     * @param dir @~english next focused widget direction
     * @~chinese 接下来查找焦点的方向
     * @return @~english The index of child widget in the container
     * @~chinese 子控件在容器中的索引
     */
    int findFarthestChildWidgetIndex(FocusDirection direction, Widget* baseWidget);
    
    /**
     * @~english
     * calculate the nearest distance between the baseWidget and the children of the layout
     * @~chinese 
     * 计算基本控件和layout的子节点之间的最近距离
     *
     * @param the @~english base widget which will be used to calculate the distance between the layout's children and itself
     * @~chinese 将被用于计算layout的子节点和自身之间的距离的基本控件
     *
     * @return @~english return the nearest distance between the baseWidget and the layout's children
     * @~chinese 返回基本控件和最近的layout的子节点之间的距离
     */
    float calculateNearestDistance(Widget* baseWidget);
    
    /**
     * @~english
     * calculate the farthest distance between the baseWidget and the children of the layout
     * @~chinese 
     * 计算基本控件和layout的子节点之间的最近距离
     *
     * @param the @~english base widget which will be used to calculate the distance between the layout's children and itself
     * @~chinese 将被用于计算layout的子节点和自身之间的距离的基本控件
     *
     * @return @~english return the farthest distance between the baseWidget and the layout's children
     * @~chinese 返回基本控件和最近的layout的子节点之间的距离
     */
    float calculateFarthestDistance(Widget* baseWidget);
    
    /**
     * @~english
     *  when a layout pass the focus to it's child, use this method to determine which algorithm to use, nearest or farthest distance algorithm or not
     * @~chinese 
     * 当一个布局将焦点传递给它的子节点,则会使用这种方法来确定使用哪个算法传递（最近或最远的距离算法）
     */
    void findProperSearchingFunctor(FocusDirection dir, Widget* baseWidget);
    
    /**
     * @~english
     * find the first non-layout widget in this layout
     * @~chinese 
     * 查找这个布局中第一个不是 layout 类型的控件
     */
    Widget *findFirstNonLayoutWidget();
    
    /**
     * @~english
     * find the first focus enabled widget index in the layout, it will recursive searching the child widget
     * @~chinese 
     * 发现在layout中的第一个启用焦点的控件索引，它会递归搜索子控件
     */
    int findFirstFocusEnabledWidgetIndex();
    
    /**@~english
     * find a focus enabled child Widget in the layout by index
     * @~chinese 
     * 按索引找到一个启用焦点的子控件
     */
    Widget* findFocusEnabledChildWidgetByIndex(ssize_t index);
    
    /**
     * @~english
     * get the center point of a widget in world space
     * @~chinese 
     * 得到一个控件在世界空间中心点
     */
    Vec2 getWorldCenterPoint(Widget* node)const;
    
    /**
     * @~english
     * this method is called internally by nextFocusedWidget. When the dir is Right/Down, then this method will be called
     * @~chinese 
     * nextFocusedWidget内部调用此方法。当dir是向右/向下，则此方法将被调用
     * @param dir  @~english the direction.
     * @~chinese 方向。
     * @param current  @~english the current focused widget
     * @~chinese 当前焦点的控件
     * @return @~english the next focused widget
     * @~chinese 下一个焦点控件
     */
    Widget* getNextFocusedWidget(FocusDirection direction,Widget *current);
    
    /**
     * @~english
     * this method is called internally by nextFocusedWidget. When the dir is Left/Up, then this method will be called
     * @~chinese 
     * nextFocusedWidget内部调用此方法。当dir是左/上，那么这个方法会被调用
     * @param dir  @~english the direction.
     * @~chinese 方向。
     *@param current  @~english the current focused widget
     * @~chinese 当前焦点控件
     *@return @~english the next focused widget
     * @~chinese 下一个焦点控件
     */
    Widget* getPreviousFocusedWidget(FocusDirection direction, Widget *current);
    
    /**
     * @~english
     * find the nth element in the _children array. Only the Widget descendant object will be returned
     * @~chinese 
     * 找到_children第n个元素。只有继承自Widget的对象会被返回
     * @param index  @~english The index of a element in the _children array
     * @~chinese _children数组中的一个元素的索引
     */
    Widget* getChildWidgetByIndex(ssize_t index)const;

    /**
     * @~english
     * whether it is the last element according to all their parents
     * @~chinese 
     * 是否是其父节点的最后一个元素
     */
    bool  isLastWidgetInContainer(Widget* widget, FocusDirection direction)const;
    
    /**
     * @~english Lookup any parent widget with a layout type as the direction,
     * if the layout is loop focused, then return true, otherwise
     * It returns false
     * @~chinese 查找任何父控件的布局类型、方向,
     * 如果开启了循环焦点,则返回true,否则返回false
     */
    bool  isWidgetAncestorSupportLoopFocus(Widget* widget, FocusDirection direction)const;
    
    /**
     * @~english
     * pass the focus to the layout's next focus enabled child
     * @~chinese 
     * 传递焦点给下一个获取焦点的子节点
     */
    Widget* passFocusToChild(FocusDirection direction, Widget* current);
    
    /**
     * @~english
     * If there are no focus enabled child in the layout, it will return false, otherwise it returns true
     * @~chinese 
     * 如果有layout中焦点启用的子节点没有焦点，则返回false，否则返回true
     */
    bool checkFocusEnabledChild()const;
    
protected:
    
    //background
    bool _backGroundScale9Enabled;
    Scale9Sprite* _backGroundImage;
    std::string _backGroundImageFileName;
    Rect _backGroundImageCapInsets;
    BackGroundColorType _colorType;
    TextureResType _bgImageTexType;
    Size _backGroundImageTextureSize;
    Color3B _backGroundImageColor;
    GLubyte _backGroundImageOpacity;

    LayerColor* _colorRender;
    LayerGradient* _gradientRender;
    Color3B _cColor;
    Color3B _gStartColor;
    Color3B _gEndColor;
    Vec2 _alongVector;
    GLubyte _cOpacity;
    
    //clipping
    bool _clippingEnabled;
    Type _layoutType;
    ClippingType _clippingType;
    DrawNode* _clippingStencil;
    bool _scissorOldState;
    Rect _clippingOldRect;
    Rect _clippingRect;
    Layout* _clippingParent;
    bool _clippingRectDirty;
    
    //clipping

    GLboolean _currentStencilEnabled;
    GLuint _currentStencilWriteMask;
    GLenum _currentStencilFunc;
    GLint _currentStencilRef;
    GLuint _currentStencilValueMask;
    GLenum _currentStencilFail;
    GLenum _currentStencilPassDepthFail;
    GLenum _currentStencilPassDepthPass;
    GLboolean _currentDepthWriteMask;
    
    GLboolean _currentAlphaTestEnabled;
    GLenum _currentAlphaTestFunc;
    GLclampf _currentAlphaTestRef;
 
    
    GLint _mask_layer_le;
    GroupCommand _groupCommand;
    CustomCommand _beforeVisitCmdStencil;
    CustomCommand _afterDrawStencilCmd;
    CustomCommand _afterVisitCmdStencil;
    CustomCommand _beforeVisitCmdScissor;
    CustomCommand _afterVisitCmdScissor;
    
    bool _doLayoutDirty;
    bool _isInterceptTouch;
    
    //whether enable loop focus or not
    bool _loopFocus;
    //on default, it will pass the focus to the next nearest widget
    bool _passFocusToChild;
     //when finding the next focused widget, use this variable to pass focus between layout & widget
    bool _isFocusPassing;
};
    
}
NS_CC_END
// end of ui group
/// @}
#endif /* defined(__Layout__) */
