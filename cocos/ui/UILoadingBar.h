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

#ifndef __UILOADINGBAR_H__
#define __UILOADINGBAR_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

struct CC_DLL ResourceData;

namespace ui {
    class Scale9Sprite;

/**
 *@brief Visual indicator of progress in some operation.
 * Displays a bar to the user representing how far the operation has progressed.
 *
 */
class CC_GUI_DLL LoadingBar : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Loading bar progress direction.
     */
    enum class Direction
    {
        LEFT,
        RIGHT
    };

    /**
     * Default constructor.
     * @js ctor
     * @lua new
     */
    LoadingBar();
    
    /**
     * Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~LoadingBar();
    
    /**
     * Create an empty LoadingBar.
     *@return A LoadingBar instance.
     */
    static LoadingBar* create();
    
     
    /**
     * @brief Create a LoadingBar with a texture name and a predefined progress value.
     *
     * @param textureName LoadingBar background texture name.
     * @param percentage A percentage in float.
     * @return A LoadingBar instance.
     */
    static LoadingBar* create(const std::string& textureName, float percentage = 0);
    
    
    /**
     * @brief Create a LoadingBar with a texture name along with its texture type and a predefined progress value.
     *
     * @param textureName LoadingBar background texture name.
     * @param texType LoadingBar background texture type.
     * @param percentage A percentage in float, default value is 0.
     * @return A LoadingBar instance.
     */
    static LoadingBar* create(const std::string& textureName,
                              TextureResType texType,
                              float percentage = 0);
    
    /**
     * Change the progress direction of LoadingBar.
     *
     * @see Direction  `LEFT` means progress left to right, `RIGHT` otherwise.
     * @param direction Direction
     */
    void setDirection(Direction direction);
    
    /**
     * Get the progress direction of LoadingBar.
     *
     * @see Direction  `LEFT` means progress left to right, `RIGHT` otherwise.
     * @return LoadingBar progress direction.
     */
    Direction getDirection()const;
    
    /**
     * Load texture for LoadingBar.
     *
     * @param texture   File name of texture.
     * @param texType   Texture resource type,@see TextureResType.
     */
    void loadTexture(const std::string& texture,TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Changes the progress value of LoadingBar.
     *
     * @param percent   Percent value from 1 to 100.
     */
    void setPercent(float percent);
    
    /**
     * Get the progress value of LoadingBar.
     *
     * @return Progress value from 1 to 100.
     */
    float getPercent() const;
    
    /**
     * Enable scale9 renderer.
     *
     * @param enabled Set to true will use scale9 renderer, false otherwise.
     */
    void setScale9Enabled(bool enabled);
    
    
    /**
     * @brief Query whether LoadingBar is using scale9 renderer or not.
     * @return Whether LoadingBar uses scale9 renderer or not.
     */
    bool isScale9Enabled()const;
    
    /**
     * Set capInsets for LoadingBar.
     * This setting only take effect when enable scale9 renderer.
     * @param capInsets CapInset in `Rect`.
     */
    void setCapInsets(const Rect &capInsets);
    
    
    /**
     * @brief Query LoadingBar's capInsets.
     * @return CapInsets of LoadingBar.
     */
    const Rect& getCapInsets()const;
    
    //override methods.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    virtual std::string getDescription() const override;

    ResourceData getRenderFile(); 

protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
   
    void setScale9Scale();
    void updateProgressBar();
    void barRendererScaleChangedWithSize();

    void setupTexture();
    void handleSpriteFlipX();
    void loadTexture(SpriteFrame* spriteframe);
    
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
    Rect _originalRect;
    bool _scale9Enabled;
    bool _prevIgnoreSize;
    Rect _capInsets;
    bool _barRendererAdaptDirty;
    std::string _textureFile;
};

}
// end of ui group
/// @}
NS_CC_END
#endif /* defined(__CocoGUI__LoadingBar__) */
