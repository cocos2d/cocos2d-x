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

#ifndef __UILABEL_H__
#define __UILABEL_H__

#include "../BaseClasses/UIWidget.h"

NS_CC_EXT_BEGIN
/**
*   @js NA
*   @lua NA
*/
class UILabel : public UIWidget
{
public:
    /**
     * Default constructor
     */
    UILabel();
    
    /**
     * Default destructor
     */
    virtual ~UILabel();
    
    /**
     * Allocates and initializes.
     */
    static UILabel* create();
    
    /**
     * Changes the string value of label.
     *
     * @param text  string value.
     */
    void setText(const char* text);
    
    /**
     * Gets the string value of label.
     *
     * @return text  string value.
     */
    const char* getStringValue();
    
    /**
     * Gets the string length of label.
     *
     * @return  string length.
     */
    int getStringLength();
    
    /**
     * Sets the font size of label.
     *
     * @param  font size.
     */
    void setFontSize(int size);
    
    /**
     * Sets the font name of label.
     *
     * @param  font name.
     */
    void setFontName(const char* name);
    
    /**
     * Sets the touch scale enabled of label.
     *
     * @param  touch scale enabled of label.
     */
    void setTouchScaleChangeEnabled(bool enabled);
    
    /**
     * Gets the touch scale enabled of label.
     *
     * @return  touch scale enabled of label.
     */
    bool isTouchScaleChangeEnabled();

    //override "setFlipX" method of widget.
    virtual void setFlipX(bool flipX);
    
    //override "setFlipY" method of widget.
    virtual void setFlipY(bool flipY);
    
    //override "isFlipX" method of widget.
    virtual bool isFlipX();
    
    //override "isFlipY" method of widget.
    virtual bool isFlipY();
    
    //override "setAnchorPoint" method of widget.
    virtual void setAnchorPoint(const CCPoint &pt);
    
    //override "getContentSize" method of widget.
    virtual const CCSize& getContentSize() const;
    
    //override "getVirtualRenderer" method of widget.
    virtual CCNode* getVirtualRenderer();
    
    /**
     * Changes both X and Y scale factor of the widget.
     *
     * 1.0 is the default scale factor. It modifies the X and Y scale at the same time.
     *
     * @param scale     The scale factor for both X and Y axis.
     */
    virtual void setScale(float fScale);
    
    /**
     * Changes the scale factor on X axis of this widget
     *
     * The deafult value is 1.0 if you haven't changed it before
     *
     * @param fScaleX   The scale factor on X axis.
     */
    virtual void setScaleX(float fScaleX);
    
    /**
     * Changes the scale factor on Y axis of this widget
     *
     * The Default value is 1.0 if you haven't changed it before.
     *
     * @param fScaleY   The scale factor on Y axis.
     */
    virtual void setScaleY(float fScaleY);
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
    
    void setTextAreaSize(const CCSize &size);
    void setTextHorizontalAlignment(CCTextAlignment alignment);
    void setTextVerticalAlignment(CCVerticalTextAlignment alignment);

    
    void setTouchScaleChangeAble(bool able){setTouchScaleChangeEnabled(able);};
    bool getTouchScaleChangeAble(){return isTouchScaleChangeEnabled();};
protected:
    virtual bool init();
    virtual void initRenderer();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
    virtual void onSizeChanged();
    void clickScale(float scaleX, float scaleY);
    void labelScaleChangedWithSize();
    virtual UIWidget* createCloneInstance();
    virtual void copySpecialProperties(UIWidget* model);
protected:
    bool m_bTouchScaleChangeEnabled;
    float m_fNormalScaleValueX;
    float m_fNormalScaleValueY;
    std::string m_sFontName;
    int m_nFontSize;
    float m_fOnSelectedScaleOffset;
    CCLabelTTF* m_pLabelRenderer;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__Label__) */
