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
#include "ui/GUIExport.h"

NS_CC_BEGIN

namespace ui {
    class Scale9Sprite;
/**
*   @js NA
*   @lua NA
*/
class CC_GUI_DLL LoadingBar : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    enum class Direction
    {
        LEFT,
        RIGHT
    };
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
    static LoadingBar* create(const std::string& textureName, float percentage = 0);
    
    static LoadingBar* create(const std::string& textureName,
                              TextureResType texType,
                              float percentage = 0);
    
    /**
     * Changes the progress direction of loadingbar.
     *
     * @see Direction  LEFT means progress left to right, RIGHT otherwise.
     *
     * @param direction Direction
     */
    void setDirection(Direction direction);
    
    /**
     * Gets the progress direction of loadingbar.
     *
     * @see Direction  LEFT means progress left to right, RIGHT otherwise.
     *
     * @return Direction
     */
    Direction getDirection()const;
    
    /**
     * Load texture for loadingbar.
     *
     * @param texture   file name of texture.
     *
     * @param texType    @see TextureResType
     */
    void loadTexture(const std::string& texture,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Changes the progress direction of loadingbar.
     *
     * @param percent    percent value from 1 to 100.
     */
    void setPercent(float percent);
    
    /**
     * Gets the progress direction of loadingbar.
     *
     * @return percent value from 1 to 100.
     */
    float getPercent() const;
    
    /**
     * Sets if loadingbar is using scale9 renderer.
     *
     * @param enabled true that using scale9 renderer, false otherwise.
     */
    void setScale9Enabled(bool enabled);
    
    bool isScale9Enabled()const;
    
    /**
     * Sets capinsets for loadingbar, if loadingbar is using scale9 renderer.
     *
     * @param capInsets    capinsets for loadingbar
     */
    void setCapInsets(const Rect &capInsets);
    
    const Rect& getCapInsets()const;
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    
    //override "getVirtualRendererSize" method of widget.
    virtual Size getVirtualRendererSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
   
    void setScale9Scale();
    void barRendererScaleChangedWithSize();
    
    virtual void adaptRenderers() override;
    
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    Direction _direction;
    float _percent;
    float _totalLength;
    Scale9Sprite* _barRenderer;
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
