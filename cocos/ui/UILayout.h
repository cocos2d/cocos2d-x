/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
class StencilStateManager;
struct CC_DLL ResourceData;

namespace ui {
    
class LayoutManager;
class Scale9Sprite;

/**
 *@brief Layout interface for creating LayoutManger and do actual layout.
 * @js NA
 */
class CC_GUI_DLL LayoutProtocol
{
public:
    /**
     *@brief Default constructor.
     */
    LayoutProtocol(){}
    /**
     *@brief Default destructor.
     */
    virtual ~LayoutProtocol(){}

    
    /**
     * @brief Create a custom layout manager.
     *
     * @return A LayoutManager descendants instance.
     */
    virtual LayoutManager* createLayoutManager() = 0;
    
    /**
     * @brief Return the content size of layout.
     *
     * @return A content size in Size.
     */
    virtual Size getLayoutContentSize()const = 0;
    
    /**
     * @brief Get all elements of the layout.
     *
     * @return A vector of Node pointers.
     */
    virtual const Vector<Node*>& getLayoutElements()const = 0;
    
    /**
     * @brief The main function to do the layout job.
     *  Different layout manager should implement its own layout algorithm.
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
 *@brief A container for holding a few child widgets. 
 *
 * The child widgets could be rearranged according to the layout type and it also enables clipping, set background image and color.
 *
 * There are mainly four types of layout:
 * - Absolute layout: This the default layout type, child elements are arranged by their absolute position.
 * - Horizontal layout: child elements are arranged horizontally.
 * - Vertical layout: child elements are arranged vertically.
 * - Relative layout: child elements are arranged relative to certain rules.
 *
 */
class CC_GUI_DLL Layout : public Widget, public LayoutProtocol
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Layout type, default is ABSOLUTE.
     */
    enum class Type
    {
        ABSOLUTE,
        VERTICAL,
        HORIZONTAL,
        RELATIVE
    };
    
    /**
     * Clipping Type, default is STENCIL.
     */
    enum class ClippingType
    {
        STENCIL,
        SCISSOR
    };
    
    /**
     * Background color type, default is NONE.
     */
    enum class BackGroundColorType
    {
        NONE,
        SOLID,
        GRADIENT
    };
    
    /**
     * Default constructor
     * @js ctor
     * @lua new
     */
    Layout();
    
    /**
     * Default destructor
     * @js NA
     * @lua NA
     */
    virtual ~Layout();
    
    /**
     * Create a empty layout.
     */
    static Layout* create();
    
    /**
     * Sets a background image for layout.
     *
     * @param fileName image file path.
     * @param texType @see TextureResType. 
     */
    void setBackGroundImage(const std::string& fileName,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Sets a background image capinsets for layout, it only affects the scale9 enabled background image
     *
     * @param capInsets  The capInsets in Rect.
     *
     */
    void setBackGroundImageCapInsets(const Rect& capInsets);
    
    /**
     * Query background image's capInsets size.
     *@return The background image capInsets.
     */
    const Rect& getBackGroundImageCapInsets()const;
    
    /**
     * Sets Color Type for layout's background
     *
     * @param type   @see `BackGroundColorType`
     */
    void setBackGroundColorType(BackGroundColorType type);
    
    /**
     * Query the layout's background color type.
     *@return The layout's background color type.
     */
    BackGroundColorType getBackGroundColorType()const;
    
    /**
     * Enable background image scale9 rendering.
     *
     * @param enabled  True means enable scale9 rendering for background image, false otherwise.
     */
    void setBackGroundImageScale9Enabled(bool enabled);
    
    /**
     * Query background image scale9 enable status.
     *@return Whether background image is scale9 enabled or not.
     */
    bool isBackGroundImageScale9Enabled()const;
    
    /**
     * Set background color for layout
     * The color only applies to layout when it's color type is BackGroundColorType::SOLIDE
     *
     * @param color Color in Color3B.
     */
    void setBackGroundColor(const Color3B &color);
    
    /**
     * Query the layout's background color.
     *@return Background color in Color3B.
     */
    const Color3B& getBackGroundColor()const;
    
    /**
     * Set start and end background color for layout.
     * This setting only take effect when the layout's  color type is BackGroundColorType::GRADIENT
     *
     * @param startColor Color value in Color3B.
     * @param endColor Color value in Color3B.
     */
    void setBackGroundColor(const Color3B &startColor, const Color3B &endColor);
    
    /**
     * Get the gradient background start color.
     *@return  Gradient background start color value.
     */
    const Color3B& getBackGroundStartColor()const;
    
    /**
     * Get the gradient background end color.
     * @return Gradient background end color value.
     */
    const Color3B& getBackGroundEndColor()const;
    
    /**
     * Sets background color opacity of layout.
     *
     * @param opacity The opacity in `GLubyte`.
     */
    void setBackGroundColorOpacity(GLubyte opacity);
    
    /**
     * Get the layout's background color opacity.
     *@return Background color opacity value.
     */
    GLubyte getBackGroundColorOpacity()const;
    
    /**
     * Sets background color vector for layout.
     * This setting only take effect when layout's color type is BackGroundColorType::GRADIENT
     *
     * @param vector The color vector in `Vec2`.
     */
    void setBackGroundColorVector(const Vec2 &vector);
    
    /**
     * Get the layout's background color vector.
     *@return Background color vector.
     */
    const Vec2& getBackGroundColorVector()const;
    
    /**
     * Set layout's background image color.
     *@param color Background color value in `Color3B`.
     */
    void setBackGroundImageColor(const Color3B& color);
    
    /**
     * Set opacity of background image.
     *@param opacity Background image opacity in GLubyte.
     */
    void setBackGroundImageOpacity(GLubyte opacity);
    
    /**
     * Get color of layout's background image.
     *@return Layout's background image color.
     */
    const Color3B& getBackGroundImageColor()const;
    
    /**
     * Get the opacity of layout's background image.
     * @return The opacity of layout's background image.
     */
    GLubyte getBackGroundImageOpacity()const;
    
    /**
     * Remove the background image of layout.
     */
    void removeBackGroundImage();
    
    /**
     * Gets background image texture size.
     *
     * @return background image texture size.
     */
    const Size& getBackGroundImageTextureSize() const;
    
    /**
     * Toggle layout clipping.
     *
     * If you do need clipping, you pass true to this function.
     *
     * @param enabled Pass true to enable clipping, false otherwise.
     */
    virtual void setClippingEnabled(bool enabled);
    
    
    /**
     * Change the clipping type of layout.
     * On default, the clipping type is `ClippingType::STENCIL`.
     * @see `ClippingType`
     *@param type The clipping type of layout.
     */
    void setClippingType(ClippingType type);

    /**
     *
     * @see `setClippingType(ClippingType)`
     */
    ClippingType getClippingType()const;
    
    /**
     * Gets if layout is clipping enabled.
     *
     * @return if layout is clipping enabled.
     */
    virtual bool isClippingEnabled()const;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
    
    /**
     * Change the layout type.
     *@param type Layout type.
     */
    virtual void setLayoutType(Type type);
    
    /**
     * Query layout type.
     *@return Get the layout type.
     */
    virtual  Type getLayoutType() const;

    
    virtual void addChild(Node* child)override;
    virtual void addChild(Node * child, int localZOrder)override;
    /**
     * Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param localZOrder    Z order for drawing priority. Please refer to setLocalZOrder(int)
     * @param tag       A integer to identify the node easily. Please refer to setTag(int)
     */
    virtual void addChild(Node* child, int localZOrder, int tag) override;
    virtual void addChild(Node* child, int localZOrder, const std::string &name) override;
    
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;

    virtual void removeChild(Node* child, bool cleanup = true) override;
    
    /**
     * Removes all children from the container with a cleanup.
     *
     * @see `removeAllChildrenWithCleanup(bool)`
     */
    virtual void removeAllChildren() override;
    /**
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @param cleanup   true if all running actions on all children nodes should be cleanup, false otherwise.
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;

    /**
     * force refresh widget layout
     */
    virtual void forceDoLayout();
    
    /**
     * request to refresh widget layout
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
    
    virtual void setGlobalZOrder(float globalZOrder) override;
    
    /**
     * If a layout is loop focused which means that the focus movement will be inside the layout
     *@param loop  pass true to let the focus movement loop inside the layout
     */
    void setLoopFocus(bool loop);
    
    /**
     *@return If focus loop is enabled, then it will return true, otherwise it returns false. The default value is false.
     */
    bool isLoopFocus()const;
    
    /**
     *@param pass To specify whether the layout pass its focus to its child
     */
    void setPassFocusToChild(bool pass);
    
    /**
     * @return To query whether the layout will pass the focus to its children or not. The default value is true
     */
    bool isPassFocusToChild()const;
    
    /**
     *  When a widget is in a layout, you could call this method to get the next focused widget within a specified direction.
     *  If the widget is not in a layout, it will return itself
     *@param direction the direction to look for the next focused widget in a layout
     *@param current  the current focused widget
     *@return the next focused widget in a layout
     */
    virtual Widget* findNextFocusedWidget(FocusDirection direction, Widget* current) override;
    
    /**
     * To specify a user-defined functor to decide which child widget of the layout should get focused
     * @param FocusDirection the finding direction
     * @param this previous focused widget
     * @return return the index of widget in the layout
     */
    std::function<int(FocusDirection, Widget*)> onPassFocusToChild;
    
    /** 
     * Override function. Set camera mask, the node is visible by the camera whose camera flag & node's camera mask is true. 
     * @param mask Mask being set
     * @param applyChildren If true call this function recursively from this node to its children.
     */
    virtual void setCameraMask(unsigned short mask, bool applyChildren = true) override;

    ResourceData getRenderFile();

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
    
    void onBeforeVisitScissor();
    void onAfterVisitScissor();
    void updateBackGroundImageColor();
    void updateBackGroundImageOpacity();
    void updateBackGroundImageRGBA();
    
    /**
     *get the content size of the layout, it will accumulate all its children's content size
     */
    Size getLayoutAccumulatedSize() const;
    
    /**
     * When the layout get focused, it the layout pass the focus to its child, it will use this method to determine which child 
     * will get the focus.  The current algorithm to determine which child will get focus is nearest-distance-priority algorithm
     *@param direction The next focused widget direction
     *@return The index of child widget in the container
     */
     int findNearestChildWidgetIndex(FocusDirection direction, Widget* baseWidget);
    
    /**
     * When the layout get focused, it the layout pass the focus to its child, it will use this method to determine which child
     * will get the focus.  The current algorithm to determine which child will get focus is farthest-distance-priority algorithm
     *@param direction The next focused widget direction
     *@return The index of child widget in the container
     */
    int findFarthestChildWidgetIndex(FocusDirection direction, Widget* baseWidget);
    
    /**
     * calculate the nearest distance between the baseWidget and the children of the layout
     *@param the base widget which will be used to calculate the distance between the layout's children and itself
     *@return return the nearest distance between the baseWidget and the layout's children
     */
    float calculateNearestDistance(Widget* baseWidget);
    
    /**
     * calculate the farthest distance between the baseWidget and the children of the layout
     *@param the base widget which will be used to calculate the distance between the layout's children and itself
     *@return return the farthest distance between the baseWidget and the layout's children
     */

    float calculateFarthestDistance(Widget* baseWidget);
    
    /**
     *  when a layout pass the focus to it's child, use this method to determine which algorithm to use, nearest or farthest distance algorithm or not
     */
    void findProperSearchingFunctor(FocusDirection dir, Widget* baseWidget);
    
    /**
     * find the first non-layout widget in this layout
     */
    Widget *findFirstNonLayoutWidget();
    
    /**
     * find the first focus enabled widget index in the layout, it will recursive searching the child widget
     */
    int findFirstFocusEnabledWidgetIndex();
    
    /**
     * find a focus enabled child Widget in the layout by index
     */
    Widget* findFocusEnabledChildWidgetByIndex(ssize_t index);
    
    /**
     * get the center point of a widget in world space
     */
    Vec2 getWorldCenterPoint(Widget* node)const;
    
    /**
     * this method is called internally by nextFocusedWidget. When the dir is Right/Down, then this method will be called
     *@param direction  the direction.
     *@param current  the current focused widget
     *@return the next focused widget
     */
    Widget* getNextFocusedWidget(FocusDirection direction,Widget *current);
    
    /**
     * this method is called internally by nextFocusedWidget. When the dir is Left/Up, then this method will be called
     *@param direction  the direction.
     *@param current  the current focused widget
     *@return the next focused widget
     */
    Widget* getPreviousFocusedWidget(FocusDirection direction, Widget *current);
    
    /**
     * find the nth element in the _children array. Only the Widget descendant object will be returned
     *@param index  The index of a element in the _children array
     */
    Widget* getChildWidgetByIndex(ssize_t index)const;
    /**
     * whether it is the last element according to all their parents
     */
    bool  isLastWidgetInContainer(Widget* widget, FocusDirection direction)const;
    
    /**Lookup any parent widget with a layout type as the direction,
     * if the layout is loop focused, then return true, otherwise
     * It returns false
     */
    bool  isWidgetAncestorSupportLoopFocus(Widget* widget, FocusDirection direction)const;
    
    /**
     * pass the focus to the layout's next focus enabled child
     */
    Widget* passFocusToChild(FocusDirection direction, Widget* current);
    
    /**
     * If there are no focus enabled child in the layout, it will return false, otherwise it returns true
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
    StencilStateManager *_stencilStateManager;

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
