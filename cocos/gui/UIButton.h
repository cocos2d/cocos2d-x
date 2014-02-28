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

#ifndef __UIBUTTON_H__
#define __UIBUTTON_H__

#include "gui/UIWidget.h"

NS_CC_BEGIN

namespace ui{

/**
*   @js NA
*   @lua NA
*/
class Button : public Widget
{
public:
    /**
     * Default constructor
     */
    Button();
    
    /**
     * Default destructor
     */
    virtual ~Button();
    
    /**
     * Allocates and initializes.
     */
    static Button* create();
    
    /**
     * Load textures for button.
     *
     * @param normal    normal state texture.
     *
     * @param selected    selected state texture.
     *
     * @param disabled    dark state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextures(const char* normal,const char* selected,const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL);

    /**
     * Load textures for button.
     *
     * @param normal    normal state texture.
     *
     * @param selected    selected state texture.
     *
     * @param disabled    dark state texture.
     *
     */
    void loadTextures(cocos2d::SpriteFrame* normal, cocos2d::SpriteFrame* selected, cocos2d::SpriteFrame* disabled);
    
    /**
     * Load normal state texture for button.
     *
     * @param normal    normal state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureNormal(const char* normal, TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load selected state texture for button.
     *
     * @param selected    selected state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTexturePressed(const char* selected, TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Load dark state texture for button.
     *
     * @param disabled    dark state texture.
     *
     * @param texType    @see UI_TEX_TYPE_LOCAL
     */
    void loadTextureDisabled(const char* disabled, TextureResType texType = UI_TEX_TYPE_LOCAL);

    /**
     * Load normal state texture for button.
     *
     * @param normal    normal state texture.
     *
     */
    void loadTextureNormal(cocos2d::SpriteFrame *normal);
    
    /**
     * Load selected state texture for button.
     *
     * @param selected    selected state texture.
     *
     */
    void loadTexturePressed(cocos2d::SpriteFrame *selected);
    
    /**
     * Load dark state texture for button.
     *
     * @param disabled    dark state texture.
     *
     */
    void loadTextureDisabled(cocos2d::SpriteFrame *disabled);
    
    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsets(const Rect &capInsets);

    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsetsNormalRenderer(const Rect &capInsets);
    
    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsetsPressedRenderer(const Rect &capInsets);
    
    /**
     * Sets capinsets for button, if button is using scale9 renderer.
     *
     * @param capInsets    capinsets for button
     */
    void setCapInsetsDisabledRenderer(const Rect &capInsets);
    
    //override "setAnchorPoint" of widget.
    virtual void setAnchorPoint(const Point &pt) override;
    
    /**
     * Sets if button is using scale9 renderer.
     *
     * @param true that using scale9 renderer, false otherwise.
     */
    virtual void setScale9Enabled(bool able);
    
    //override "setFlipX" of widget.
    virtual void setFlipX(bool flipX) override;
    
    //override "setFlipY" of widget.
    virtual void setFlipY(bool flipY) override;
    
    //override "isFlipX" of widget.
    virtual bool isFlipX() override;
    
    //override "isFlipY" of widget.
    virtual bool isFlipY() override;
    
    /**
     * Changes if button can be clicked zoom effect.
     *
     * @param true that can be clicked zoom effect, false otherwise.
     */
    void setPressedActionEnabled(bool enabled);
    
    //override "ignoreContentAdaptWithSize" method of widget.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    
    //override "getContentSize" method of widget.
    virtual const Size& getContentSize() const override;
    
    //override "getVirtualRenderer" method of widget.
    virtual Node* getVirtualRenderer() override;
    
    /**
     * Sets color to widget
     *
     * It default change the color of widget's children.
     *
     * @param color
     */
    virtual void setColor(const Color3B &color) override;
    
    /**
     * Returns the "class name" of widget.
     */
    virtual std::string getDescription() const override;
    
    void setTitleText(const std::string& text);
    const std::string& getTitleText() const;
    void setTitleColor(const Color3B& color);
    const Color3B& getTitleColor() const;
    void setTitleFontSize(float size);
    float getTitleFontSize() const;
    void setTitleFontName(const char* fontName);
    const char* getTitleFontName() const;
    
protected:
    struct ButtonState {
        enum class TexType { LOCAL, PLIST, SPRITE_FRAME };
        SpriteFrame* sprite;
        Node *renderer;
        std::string fileName;
        Rect capInsets;
        TexType texType;
        Size textureSize;
        Point textureScaleInSize;
        bool textureLoaded;
        
        void setTexType(TextureResType t) {
            switch (t) {
                case UI_TEX_TYPE_LOCAL:
                    texType = TexType::LOCAL;
                    break;
                case UI_TEX_TYPE_PLIST:
                    texType = TexType::PLIST;
                    break;
            }
        }

        ButtonState():
        sprite(nullptr),
        renderer(nullptr),
        capInsets(Rect::ZERO),
        texType(TexType::LOCAL),
        textureSize(Size::ZERO),
        textureScaleInSize(1,1),
        textureLoaded(false) {
        }
        
        ButtonState& operator=(const ButtonState &rhs) {
            CC_SAFE_RELEASE_NULL(sprite);
            sprite = rhs.sprite;
            CC_SAFE_RETAIN(sprite);

            fileName = rhs.fileName;
            capInsets = rhs.capInsets;
            texType = rhs.texType;
            textureSize = rhs.textureSize;
            textureScaleInSize = rhs.textureScaleInSize;
            textureLoaded = false;
            
            return *this;
        }

        ~ButtonState() {
            CC_SAFE_RELEASE(sprite);
        }
    };

protected:
    virtual bool init() override;
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;
    
    void load(ButtonState &b);
    void textureScaleChangedWithSize(ButtonState &b);
    void setCapInsets(ButtonState &s, const Rect &capInsets);
    
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    ButtonState _normalState, _pressedState, _disabledState;
    LabelTTF* _titleRenderer;
    bool _prevIgnoreSize;
    bool _scale9Enabled;
    bool _pressedActionEnabled;
    Color3B _titleColor;
};

}

NS_CC_END

#endif /* defined(__CocoGUI__Button__) */
