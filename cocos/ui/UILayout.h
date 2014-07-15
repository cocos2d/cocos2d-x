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
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"

NS_CC_BEGIN

class DrawNode;
class LayerColor;
class LayerGradient;

namespace ui {
    
class LayoutManager;


class LayoutProtocol
{
public:
    LayoutProtocol(){}
    virtual ~LayoutProtocol(){}
    
    virtual LayoutManager* createLayoutManager() = 0;
    virtual Size getLayoutContentSize()const = 0;
    virtual const Vector<Node*>& getLayoutElements()const = 0;
    virtual void doLayout() = 0;
};

/**
 *  @js NA
 *  @lua NA
 */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef RELATIVE
#undef RELATIVE
#endif
#endif

class Layout : public Widget, public LayoutProtocol
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class Type
    {
        ABSOLUTE,
        VERTICAL,
        HORIZONTAL,
        RELATIVE
    };
    
    enum class ClippingType
    {
        STENCIL,
        SCISSOR
    };
    
    enum class BackGroundColorType
    {
        NONE,
        SOLID,
        GRADIENT
    };
    
    /**
     * Default constructor
     */
    Layout();
    
    /**
     * Default destructor
     */
    virtual ~Layout();
    
    /**
     * Allocates and initializes a layout.
     */
    static Layout* create();
    
    //background
    /**
     * Sets a background image for layout
     *
     * @param fileName image file path.
     *
     * @param texType @see TextureResType. TextureResType::LOCAL means local file, TextureResType::PLIST means sprite frame.
     */
    void setBackGroundImage(const std::string& fileName,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Sets a background image capinsets for layout, if the background image is a scale9 render.
     *
     * @param capinsets of background image.
     *
     */
    void setBackGroundImageCapInsets(const Rect& capInsets);
    
    const Rect& getBackGroundImageCapInsets()const;
    
    /**
     * Sets Color Type for layout.
     *
     * @param type   @see LayoutBackGroundColorType.
     */
    void setBackGroundColorType(BackGroundColorType type);
    
    BackGroundColorType getBackGroundColorType()const;
    
    /**
     * Sets background iamge use scale9 renderer.
     *
     * @param enabled   true that use scale9 renderer, false otherwise.
     */
    void setBackGroundImageScale9Enabled(bool enabled);
    
    bool isBackGroundImageScale9Enabled()const;
    
    /**
     * Sets background color for layout, if color type is BackGroundColorType::SOLIDE
     *
     * @param color
     */
    void setBackGroundColor(const Color3B &color);
    
    const Color3B& getBackGroundColor()const;
    
    /**
     * Sets background color for layout, if color type is BackGroundColorType::GRADIENT
     *
     * @param start color
     *
     * @param end color
     */
    void setBackGroundColor(const Color3B &startColor, const Color3B &endColor);
    
    const Color3B& getBackGroundStartColor()const;
    
    const Color3B& getBackGroundEndColor()const;
    
    /**
     * Sets background opacity layout.
     *
     * @param opacity
     */
    void setBackGroundColorOpacity(GLubyte opacity);
    
    GLubyte getBackGroundColorOpacity()const;
    
    /**
     * Sets background color vector for layout, if color type is BackGroundColorType::GRADIENT
     *
     * @param vector
     */
    void setBackGroundColorVector(const Vec2 &vector);
    
    const Vec2& getBackGroundColorVector()const;
    
    void setBackGroundImageColor(const Color3B& color);
    
    void setBackGroundImageOpacity(GLubyte opacity);
    
    const Color3B& getBackGroundImageColor()const;
    
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
     * Changes if layout can clip it's content and child.
     *
     * If you really need this, please enable it. But it would reduce the rendering efficiency. 
     *
     * @param clipping enabled.
     */
    virtual void setClippingEnabled(bool enabled);
    
    void setClippingType(ClippingType type);
    
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
    

    virtual void setLayoutType(Type type);
    
    virtual  Type getLayoutType() const;

    /**
     * Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setLocalZOrder(int)
     * @param tag       A interger to identify the node easily. Please refer to setTag(int)
     */
    virtual void addChild(Node* child)override;
    virtual void addChild(Node * child, int localZOrder)override;
    virtual void addChild(Node* child, int zOrder, int tag) override;
    virtual void addChild(Node* child, int zOrder, const std::string &name) override;
    
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
     * @param cleanup   true if all running actions on all children nodes should be cleanup, false oterwise.
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;

    
    void requestDoLayout();
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
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
     *@param dir the direction to look for the next focused widget in a layout
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
    /**draw fullscreen quad to clear stencil bits
     */
    void drawFullScreenQuadClearStencil();
    
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
     *@param dir next focused widget direction
     *@return The index of child widget in the container
     */
     int findNearestChildWidgetIndex(FocusDirection direction, Widget* baseWidget);
    
    /**
     * When the layout get focused, it the layout pass the focus to its child, it will use this method to determine which child
     * will get the focus.  The current algorithm to determine which child will get focus is farthest-distance-priority algorithm
     *@param dir next focused widget direction
     *@return The index of child widget in the container
     */
    int findFarthestChildWidgetIndex(FocusDirection direction, Widget* baseWidget);
    
    /**
     * caculate the nearest distance between the baseWidget and the children of the layout
     *@param the base widget which will be used to caculate the distance between the layout's children and itself
     *@return return the nearest distance between the baseWidget and the layout's children
     */
    float calculateNearestDistance(Widget* baseWidget);
    
    /**
     * caculate the farthest distance between the baseWidget and the children of the layout
     *@param the base widget which will be used to caculate the distance between the layout's children and itself
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
     * find the fisrt focus enabled widget index in the layout, it will recusive searching the child widget
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
     *@param dir  the direction.
     *@param current  the current focused widget
     *@return the next focused widget
     */
    Widget* getNextFocusedWidget(FocusDirection direction,Widget *current);
    
    /**
     * this method is called internally by nextFocusedWidget. When the dir is Left/Up, then this method will be called
     *@param dir  the direction.
     *@param current  the current focused widget
     *@return the next focused widget
     */
    Widget* getPreviousFocusedWidget(FocusDirection direction, Widget *current);
    
    /**
     * find the nth elment in the _children array. Only the Widget descendant object will be returned
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
    bool _clippingEnabled;
    
    //background
    bool _backGroundScale9Enabled;
    Node* _backGroundImage;
    std::string _backGroundImageFileName;
    Rect _backGroundImageCapInsets;
    BackGroundColorType _colorType;
    TextureResType _bgImageTexType;
    LayerColor* _colorRender;
    LayerGradient* _gradientRender;
    Color3B _cColor;
    Color3B _gStartColor;
    Color3B _gEndColor;
    Vec2 _alongVector;
    GLubyte _cOpacity;
    Size _backGroundImageTextureSize;
    Type _layoutType;
    ClippingType _clippingType;
    DrawNode* _clippingStencil;
    bool _scissorRectDirty;
    Rect _clippingRect;
    Layout* _clippingParent;
    bool _doLayoutDirty;
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
    
    
    Color3B _backGroundImageColor;
    GLubyte _backGroundImageOpacity;
    
    GLint _mask_layer_le;
    GroupCommand _groupCommand;
    CustomCommand _beforeVisitCmdStencil;
    CustomCommand _afterDrawStencilCmd;
    CustomCommand _afterVisitCmdStencil;
    CustomCommand _beforeVisitCmdScissor;
    CustomCommand _afterVisitCmdScissor;
    
    //whether enable loop focus or not
    bool _loopFocus;
    //on default, it will pass the focus to the next nearest widget
    bool _passFocusToChild;
     //when finding the next focused widget, use this variable to pass focus between layout & widget
    bool _isFocusPassing;
};
    
}
NS_CC_END
#endif /* defined(__Layout__) */
