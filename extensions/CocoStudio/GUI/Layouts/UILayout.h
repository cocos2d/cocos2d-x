/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "../BaseClasses/UIWidget.h"

NS_CC_BEGIN

namespace ui {

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
    
    DECLARE_CLASS_GUI_INFO
    
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
    void setBackGroundImageCapInsets(const CCRect& capInsets);
    
    const CCRect& getBackGroundImageCapInsets();
    
    /**
     * Sets Color Type for layout.
     *
     * @param type   @see LayoutBackGroundColorType.
     */
    void setBackGroundColorType(LayoutBackGroundColorType type);
    
    LayoutBackGroundColorType getBackGroundColorType();
    
    /**
     * Sets background iamge use scale9 renderer.
     *
     * @param enabled   true that use scale9 renderer, false otherwise.
     */
    void setBackGroundImageScale9Enabled(bool enabled);
    
    bool isBackGroundImageScale9Enabled();
    
    /**
     * Sets background color for layout, if color type is LAYOUT_COLOR_SOLID
     *
     * @param color
     */
    void setBackGroundColor(const ccColor3B &color);
    
    const ccColor3B& getBackGroundColor();
    
    /**
     * Sets background color for layout, if color type is LAYOUT_COLOR_GRADIENT
     *
     * @param start color
     *
     * @param end color
     */
    void setBackGroundColor(const ccColor3B &startColor, const ccColor3B &endColor);
    
    const ccColor3B& getBackGroundStartColor();
    
    const ccColor3B& getBackGroundEndColor();
    
    /**
     * Sets background opacity layout.
     *
     * @param opacity
     */
    void setBackGroundColorOpacity(GLubyte opacity);
    
    GLubyte getBackGroundColorOpacity();
    
    /**
     * Sets background color vector for layout, if color type is LAYOUT_COLOR_GRADIENT
     *
     * @param vector
     */
    void setBackGroundColorVector(const CCPoint &vector);
    
    const CCPoint& getBackGroundColorVector();
    
    void setBackGroundImageColor(const ccColor3B& color);
    
    void setBackGroundImageOpacity(GLubyte opacity);
    
    const ccColor3B& getBackGroundImageColor();
    
    GLubyte getBackGroundImageOpacity();
    
    /**
     * Remove the background image of layout.
     */
    void removeBackGroundImage();
    
    /**
     * Gets background image texture size.
     *
     * @return background image texture size.
     */
    const CCSize& getBackGroundImageTextureSize() const;
    
    /**
     * Changes if layout can clip it's content and child.
     *
     * If you really need this, please enable it. But it would reduce the rendering efficiency. 
     *
     * @param clipping enabled.
     */
    virtual void setClippingEnabled(bool enabled);
    
    void setClippingType(LayoutClippingType type);
    
    LayoutClippingType getClippingType();
    
    /**
     * Gets if layout is clipping enabled.
     *
     * @return if layout is clipping enabled.
     */
    virtual bool isClippingEnabled();
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const;
    
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

    virtual void addChild(CCNode * child);
    /**
     * Adds a child to the container with a z-order
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setZOrder(int)
     */
    virtual void addChild(CCNode * child, int zOrder);
    /**
     * Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node
     * @param zOrder    Z order for drawing priority. Please refer to setZOrder(int)
     * @param tag       A interger to identify the node easily. Please refer to setTag(int)
     */
    virtual void addChild(CCNode* child, int zOrder, int tag);
    
    virtual void removeChild(CCNode* child);
    
    virtual void removeChild(CCNode* widget, bool cleanup);
    
    virtual void removeAllChildren();
    
    virtual void removeAllChildrenWithCleanup(bool cleanup);
    
    virtual void visit();
    
    virtual void sortAllChildren();
    
    void requestDoLayout();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool hitTest(const CCPoint &pt);
protected:
    //override "init" method of widget.
    virtual bool init();
        
    //override "onSizeChanged" method of widget.
    virtual void onSizeChanged();
    
    //init background image renderer.
    void addBackGroundImage();
    
    void supplyTheLayoutParameterLackToChild(Widget* child);
    virtual Widget* createCloneInstance();
    virtual void copySpecialProperties(Widget* model);
    virtual void copyClonedWidgetChildren(Widget* model);
    
    void stencilClippingVisit();
    void scissorClippingVisit();
    
    void setStencilClippingSize(const CCSize& size);
    const CCRect& getClippingRect();
    virtual void doLayout();
    void updateBackGroundImageColor();
    void updateBackGroundImageOpacity();
    void updateBackGroundImageRGBA();
protected:
    bool _clippingEnabled;
    
    //background
    bool _backGroundScale9Enabled;
    CCNode* _backGroundImage;
    std::string _backGroundImageFileName;
    CCRect _backGroundImageCapInsets;
    LayoutBackGroundColorType _colorType;
    TextureResType _bgImageTexType;
    CCLayerColor* _colorRender;
    CCLayerGradient* _gradientRender;
    ccColor3B _cColor;
    ccColor3B _gStartColor;
    ccColor3B _gEndColor;
    CCPoint _alongVector;
    GLubyte _cOpacity;
    CCSize _backGroundImageTextureSize;
    LayoutType _layoutType;
    LayoutClippingType _clippingType;
    CCDrawNode* _clippingStencil;
    bool _handleScissor;
    bool _scissorRectDirty;
    CCRect _clippingRect;
    Layout* _clippingParent;
    bool _doLayoutDirty;
    bool _clippingRectDirty;
    ccColor3B _backGroundImageColor;
    GLubyte _backGroundImageOpacity;
};
    
}
NS_CC_END
#endif /* defined(__Layout__) */
