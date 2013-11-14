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

#include "gui/UIWidget.h"

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


/**
 *  @js NA
 *  @lua NA
 */
class UILayout : public UIWidget
{
public:
    /**
     * Default constructor
     */
    UILayout();
    
    /**
     * Default destructor
     */
    virtual ~UILayout();
    
    /**
     * Allocates and initializes a layout.
     */
    static UILayout* create();
    
    //override "hitTest" method of widget.
    virtual bool hitTest(const cocos2d::Point &pt) override;
    
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
    void setBackGroundImageCapInsets(const cocos2d::Rect& capInsets);
    
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
    void setBackGroundColor(const cocos2d::Color3B &color);
    
    /**
     * Sets background color for layout, if color type is LAYOUT_COLOR_GRADIENT
     *
     * @param start color
     *
     * @param end color
     */
    void setBackGroundColor(const cocos2d::Color3B &startColor, const cocos2d::Color3B &endColor);
    
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
    void setBackGroundColorVector(const cocos2d::Point &vector);
    
    //override "setColor" method of widget.
    virtual void setColor(const cocos2d::Color3B &color) override;
    
    //override "setOpacity" method of widget.
    virtual void setOpacity(int opacity) override;
    
    /**
     * Remove the background image of layout.
     */
    void removeBackGroundImage();
    
    /**
     * Gets background image texture size.
     *
     * @return background image texture size.
     */
    const cocos2d::Size& getBackGroundImageTextureSize() const;
    
    /**
     * Changes if layout can clip it's content and child.
     *
     * If you really need this, please enable it. But it would reduce the rendering efficiency. 
     *
     * @param clipping enabled.
     */
    virtual void setClippingEnabled(bool enabled);
    
    /**
     * Gets if layout is clipping enabled.
     *
     * @return if layout is clipping enabled.
     */
    virtual bool isClippingEnabled();
    
    /**
     * Gets the content size of widget.
     *
     * Content size is widget's texture size.
     */
    virtual const cocos2d::Size& getContentSize() const override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const override;
    
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
    
    virtual void doLayout();
    
    /**
     * Adds a child to the container.
     *
     * @param child A child widget
     */
    virtual bool addChild(UIWidget* child) override;
    
protected:
    //override "init" method of widget.
    virtual bool init() override;
    
    //override "initRenderer" method of widget.
    virtual void initRenderer() override;
    
    //override "onSizeChanged" method of widget.
    virtual void onSizeChanged() override;
    
    //init background image renderer.
    void addBackGroundImage();
    
    void supplyTheLayoutParameterLackToChild(UIWidget* child);
    virtual UIWidget* createCloneInstance() override;
    virtual void copySpecialProperties(UIWidget* model) override;
    virtual void copyClonedWidgetChildren(UIWidget* model) override;
protected:
    bool _clippingEnabled;
    
    //background
    bool _backGroundScale9Enabled;
    cocos2d::Node* _backGroundImage;
    std::string _backGroundImageFileName;
    cocos2d::Rect _backGroundImageCapInsets;
    LayoutBackGroundColorType _colorType;
    TextureResType _bgImageTexType;
    cocos2d::LayerColor* _colorRender;
    cocos2d::LayerGradient* _gradientRender;
    cocos2d::Color3B _cColor;
    cocos2d::Color3B _gStartColor;
    cocos2d::Color3B _gEndColor;
    cocos2d::Point _alongVector;
    int _cOpacity;
    cocos2d::Size _backGroundImageTextureSize;
    LayoutType _layoutType;
};
/**
 *  @js NA
 *  @lua NA
 */
class UIRectClippingNode : public cocos2d::ClippingNode
{
public:
    virtual ~UIRectClippingNode();
    virtual bool init();
    static UIRectClippingNode* create();
    void setClippingSize(const cocos2d::Size& size);
    void setClippingEnabled(bool enabled);
    virtual void visit();
    void setEnabled(bool enabled);
    bool isEnabled() const;
protected:
    cocos2d::DrawNode* _innerStencil;
    bool _enabled;
private:
    UIRectClippingNode();
    cocos2d::Point rect[4];
    cocos2d::Size _clippingSize;
    bool _clippingEnabled;
};

}

#endif /* defined(__Layout__) */
