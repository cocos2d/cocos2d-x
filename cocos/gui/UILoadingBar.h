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

#ifndef __UILOADINGBAR_H__
#define __UILOADINGBAR_H__

#include "gui/UIWidget.h"

namespace gui {

typedef enum
{
    LoadingBarTypeLeft,
    LoadingBarTypeRight
}LoadingBarType;
/**
*   @js NA
*   @lua NA
*/
class UILoadingBar : public UIWidget
{
public:
    /**
     * Default constructor
     */
    UILoadingBar();
    
    /**
     * Default destructor
     */
    virtual ~UILoadingBar();
    
    /**
     * Allocates and initializes.
     */
    static UILoadingBar* create();
    
    /**
     * Changes the progress direction of loadingbar.
     *
     * @see LoadingBarType  LoadingBarTypeLeft means progress left to right, LoadingBarTypeRight otherwise.
     *
     * @param LoadingBarType
     */
    void setDirection(LoadingBarType dir);
    
    /**
     * Gets the progress direction of loadingbar.
     *
     * @see LoadingBarType  LoadingBarTypeLeft means progress left to right, LoadingBarTypeRight otherwise.
     *
     * @param LoadingBarType
     */
    int getDirection();
    
    /**
     * Load texture for loadingbar.
     *
     * @param fileName   file name of texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTexture(const char* texture,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Changes the progress direction of loadingbar.
     *
     * @param percent    percent value from 1 to 100.
     */
    void setPercent(int percent);
    
    /**
     * Gets the progress direction of loadingbar.
     *
     * @return percent    percent value from 1 to 100.
     */
    int getPercent();
    
    /**
     * Sets if loadingbar is using scale9 renderer.
     *
     * @param true that using scale9 renderer, false otherwise.
     */
    void setScale9Enabled(bool enabled);
    
    /**
     * Sets capinsets for loadingbar, if loadingbar is using scale9 renderer.
     *
     * @param capInsets    capinsets for loadingbar
     */
    void setCapInsets(const cocos2d::Rect &capInsets);
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    
    //override "getContentSize" method of widget.
    virtual const cocos2d::Size& getContentSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual cocos2d::Node* getVirtualRenderer() override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const override;
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    void setScale9Scale();
    void barRendererScaleChangedWithSize();
    virtual UIWidget* createCloneInstance() override;
    virtual void copySpecialProperties(UIWidget* model) override;
protected:
    LoadingBarType _barType;
    int _percent;
    float _totalLength;
    cocos2d::Node* _barRenderer;
    TextureResType _renderBarTexType;
    cocos2d::Size _barRendererTextureSize;
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    cocos2d::Rect _capInsets;
    std::string _textureFile;
};

}

#endif /* defined(__CocoGUI__UILoadingBar__) */
