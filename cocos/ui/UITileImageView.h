/****************************************************************************
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#ifndef __UITILEIMAGEVIEW_H__
#define __UITILEIMAGEVIEW_H__

#include "2d/CCSprite.h"
#include "ui/UIWidget.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

struct CC_DLL ResourceData;

namespace ui {
/**
 * @brief A widget to display images.
 */
class CC_GUI_DLL TileImageView : public Widget
{
    
    DECLARE_CLASS_GUI_INFO
    
public:
    /**
     * Default constructor
     * @js ctor
     * @lua new
     */
    TileImageView();

    /**
     * Default destructor
     * @js NA
     * @lua NA
     */
    virtual ~TileImageView();

    /**
     * Create a empty ImageView.
     */
    static TileImageView* create();
    
    /**
     * Create a  imageview  with a image name.
     *
     * @param imageFileName   file name of texture.
     * @param texType    @see `Widget::TextureResType`
     * @return A ImageView instance.
     */
    static TileImageView* create(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);
    

    /**
     * Load texture for imageview.
     *
     * @param fileName   file name of texture.
     * @param texType    @see `Widget::TextureResType`
     */
    void loadTexture(const std::string& fileName, TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Sets image internal scale.
     * @return internal image scale.
     */
    void setImageScale(float scale);
    
    /**
     * Get image internal scale.
     * @param scale image internal scale
     */
    float getImageScale() const;
    
    //override methods.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual std::string getDescription() const override;
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;

    ResourceData getRenderFile();

    virtual void setGLProgram(GLProgram* glProgram) override;
    virtual void setGLProgramState(cocos2d::GLProgramState* glProgramState) override;
CC_CONSTRUCTOR_ACCESS:
    //initializes state of widget.
    virtual bool init() override;
    virtual bool init(const std::string& imageFileName, TextureResType texType = TextureResType::LOCAL);

protected:
    virtual void initRenderer() override;
    virtual void onSizeChanged() override;
    
    virtual void adaptRenderers() override;
    void loadTexture(SpriteFrame* spriteframe);
    void setupTexture();
    
    void imageTextureScaleChangedWithSize();
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    
    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    
    void updatePoly();
    
protected:
    bool _dirty;
    bool _prevIgnoreSize;
    Sprite* _imageRenderer;
    TextureResType _imageTexType;
    Size _imageTextureSize;
    bool _imageRendererAdaptDirty;
    std::string _textureFile;
    float _imageScale;
};

}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__CocoGUI__ImageView__) */
