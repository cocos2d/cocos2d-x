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

#ifndef __UILOADINGBAR_H__
#define __UILOADINGBAR_H__

#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {

typedef enum
{
    LoadingBarTypeLeft,
    LoadingBarTypeRight
}LoadingBarType;
/**
*   @js NA
*   @lua NA
*/
class LoadingBar : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Default constructor
     */
    LoadingBar();
    
    /**
     * Default destructor
     */
    virtual ~LoadingBar();
    
    /**
     * Allocates and initializes.
     */
    static LoadingBar* create();
    
    /**
     * create a LoadingBar with a texture and a percentage
     **/
    static LoadingBar* create(const std::string& textureName, int percentage = 0);
    
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
    void loadTexture(const std::string& texture,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
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
    
    bool isScale9Enabled();
    
    /**
     * Sets capinsets for loadingbar, if loadingbar is using scale9 renderer.
     *
     * @param capInsets    capinsets for loadingbar
     */
    void setCapInsets(const Rect &capInsets);
    
    const Rect& getCapInsets();
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    
    //override "getVirtualRendererSize" method of widget.
    virtual const Size& getVirtualRendererSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    virtual void updateTextureColor() override;
    virtual void updateTextureOpacity() override;
    virtual void updateTextureRGBA() override;
    void setScale9Scale();
    void barRendererScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    virtual void adaptRenderers() override;
protected:
    LoadingBarType _barType;
    int _percent;
    float _totalLength;
    Node* _barRenderer;
    TextureResType _renderBarTexType;
    Size _barRendererTextureSize;
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    Rect _capInsets;
    std::string _textureFile;
    bool _barRendererAdaptDirty;
};

}
NS_CC_END
#endif /* defined(__CocoGUI__LoadingBar__) */
