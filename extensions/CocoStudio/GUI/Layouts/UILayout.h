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

NS_CC_EXT_BEGIN

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
    virtual bool hitTest(const CCPoint &pt);
    
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
    void setBackGroundColor(const ccColor3B &color);
    
    /**
     * Sets background color for layout, if color type is LAYOUT_COLOR_GRADIENT
     *
     * @param start color
     *
     * @param end color
     */
    void setBackGroundColor(const ccColor3B &startColor, const ccColor3B &endColor);
    
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
    void setBackGroundColorVector(const CCPoint &vector);
    
    //override "setColor" method of widget.
    virtual void setColor(const ccColor3B &color);
    
    //override "setOpacity" method of widget.
    virtual void setOpacity(int opacity);
    
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
    virtual void setClippingEnabled(bool able);
    
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
    virtual const CCSize& getContentSize() const;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
    
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
    virtual bool addChild(UIWidget* child);
    
    /*Compatible*/
    /**
     * These methods will be removed
     */
    void setBackGroundImageScale9Enable(bool is){setBackGroundImageScale9Enabled(is);};
    virtual void setClippingEnable(bool is){setClippingEnabled(is);};
    /************/

protected:
    //override "init" method of widget.
    virtual bool init();
    
    //override "initRenderer" method of widget.
    virtual void initRenderer();
    
    //override "onSizeChanged" method of widget.
    virtual void onSizeChanged();
    
    //init background image renderer.
    void addBackGroundImage();
    
    void supplyTheLayoutParameterLackToChild(UIWidget* child);
    virtual UIWidget* createCloneInstance();
    virtual void copySpecialProperties(UIWidget* model);
    virtual void copyClonedWidgetChildren(UIWidget* model);
protected:
    bool m_bClippingEnabled;
    
    //background
    bool m_bBackGroundScale9Enabled;
    CCNode* m_pBackGroundImage;
    std::string m_strBackGroundImageFileName;
    CCRect m_backGroundImageCapInsets;
    LayoutBackGroundColorType m_colorType;
    TextureResType m_eBGImageTexType;
    CCLayerColor* m_pColorRender;
    CCLayerGradient* m_pGradientRender;
    ccColor3B m_cColor;
    ccColor3B m_gStartColor;
    ccColor3B m_gEndColor;
    CCPoint m_AlongVector;
    int m_nCOpacity;
    CCSize m_backGroundImageTextureSize;
    LayoutType m_eLayoutType;
};
/**
 *  @js NA
 *  @lua NA
 */
class UIRectClippingNode : public CCClippingNode
{
public:
    virtual ~UIRectClippingNode();
    virtual bool init();
    static UIRectClippingNode* create();
    void setClippingSize(const CCSize& size);
    void setClippingEnabled(bool enabled);
    virtual void visit();
    void setEnabled(bool enabled);
    bool isEnabled() const;
protected:
    CCDrawNode* m_pInnerStencil;
    bool m_bEnabled;
private:
    UIRectClippingNode();
    CCPoint rect[4];
    CCSize m_clippingSize;
    bool m_bClippingEnabled;
};

NS_CC_EXT_END

#endif /* defined(__Layout__) */
