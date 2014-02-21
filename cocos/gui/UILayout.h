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

#include "gui/UIWidget.h"

NS_CC_BEGIN

namespace gui {

typedef enum
{
    LAYOUT_COLOR_NONE,
    LAYOUT_COLOR_SOLID,
    LAYOUT_COLOR_GRADIENT
}LayoutBackGroundColorType;

typedef enum
{
    LAYOUT_ABSOLUTE,
    LAYOUT_LINEAR_VERTICAL,
    LAYOUT_LINEAR_HORIZONTAL,
    LAYOUT_RELATIVE
}LayoutType;

typedef enum {
    LAYOUT_CLIPPING_STENCIL,
    LAYOUT_CLIPPING_SCISSOR
}LayoutClippingType;

/**
 *  @js NA
 *  @lua NA
 */
class Layout : public Widget
{
public:
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
     * @param texType @see TextureResType. UI_TEX_TYPE_LOCAL means local file, UI_TEX_TYPE_PLIST means sprite frame.
     */
    void setBackGroundImage(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Sets a background image capinsets for layout, if the background image is a scale9 render.
     *
     * @param capinsets of background image.
     *
     */
    void setBackGroundImageCapInsets(const Rect& capInsets);
    
    /**
     * Sets Color Type for layout.
     *
     * @param type   @see LayoutBackGroundColorType.
     */
    void setBackGroundColorType(LayoutBackGroundColorType type);
    
    /**
     * Sets background iamge use scale9 renderer.
     *
     * @param enabled   true that use scale9 renderer, false otherwise.
     */
    void setBackGroundImageScale9Enabled(bool enabled);
    
    /**
     * Sets background color for layout, if color type is LAYOUT_COLOR_SOLID
     *
     * @param color
     */
    void setBackGroundColor(const Color3B &color);
    
    /**
     * Sets background color for layout, if color type is LAYOUT_COLOR_GRADIENT
     *
     * @param start color
     *
     * @param end color
     */
    void setBackGroundColor(const Color3B &startColor, const Color3B &endColor);
    
    /**
     * Sets background opacity layout.
     *
     * @param opacity
     */
    void setBackGroundColorOpacity(int opacity);
    
    /**
     * Sets background color vector for layout, if color type is LAYOUT_COLOR_GRADIENT
     *
     * @param vector
     */
    void setBackGroundColorVector(const Point &vector);
    
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
    
    void setClippingType(LayoutClippingType type);
    
    /**
     * Gets if layout is clipping enabled.
     *
     * @return if layout is clipping enabled.
     */
    virtual bool isClippingEnabled();
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
    
    /**
     * Sets LayoutType.
     *
     * @see LayoutType
     *
     * @param LayoutType
     */
    virtual void setLayoutType(LayoutType type);
    
    /**
     * Gets LayoutType.
     *
     * @see LayoutType
     *
     * @return LayoutType
     */
    virtual LayoutType getLayoutType() const;

    virtual void addChild(Node * child) override;
    /**
     * Adds a child to the container with a z-order
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setLocalZOrder(int)
     */
    virtual void addChild(Node * child, int zOrder) override;
    /**
     * Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setLocalZOrder(int)
     * @param tag       A interger to identify the node easily. Please refer to setTag(int)
     */
    virtual void addChild(Node* child, int zOrder, int tag) override;
    
    virtual void visit();
    
    virtual void sortAllChildren() override;
    
    void requestDoLayout();
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual bool hitTest(const Point &pt);
protected:
    //override "init" method of widget.
    virtual bool init() override;
        
    //override "onSizeChanged" method of widget.
    virtual void onSizeChanged() override;
    
    //init background image renderer.
    void addBackGroundImage();
    
    void supplyTheLayoutParameterLackToChild(Widget* child);
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void copyClonedWidgetChildren(Widget* model) override;
    
    void stencilClippingVisit();
    void scissorClippingVisit();
    
    void setStencilClippingSize(const Size& size);
    const Rect& getClippingRect();
    virtual void doLayout();
    
    //clipping
    void onBeforeVisitStencil();
    void onAfterDrawStencil();
    void onAfterVisitStencil();
    
    void onBeforeVisitScissor();
    void onAfterVisitScissor();
protected:
    bool _clippingEnabled;
    
    //background
    bool _backGroundScale9Enabled;
    Node* _backGroundImage;
    std::string _backGroundImageFileName;
    Rect _backGroundImageCapInsets;
    LayoutBackGroundColorType _colorType;
    TextureResType _bgImageTexType;
    LayerColor* _colorRender;
    LayerGradient* _gradientRender;
    Color3B _cColor;
    Color3B _gStartColor;
    Color3B _gEndColor;
    Point _alongVector;
    int _cOpacity;
    Size _backGroundImageTextureSize;
    LayoutType _layoutType;
    LayoutClippingType _clippingType;
    DrawNode* _clippingStencil;
    bool _scissorRectDirty;
    Rect _clippingRect;
    Layout* _clippingParent;
    bool _doLayoutDirty;
    
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
};
    
}
NS_CC_END
#endif /* defined(__Layout__) */
