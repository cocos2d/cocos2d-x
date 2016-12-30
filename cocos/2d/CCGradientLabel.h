//
//  CCGradientLabel.h
//
//  Created by vitaly on 29.12.16.
//
//

#ifndef _COCOS2D_CCGRADIENTLABEL_H_
#define _COCOS2D_CCGRADIENTLABEL_H_

#include "2d/CCLabel.h"
//#include "renderer/CCCustomCommand.h"
//#include "renderer/CCQuadCommand.h"
//#include "base/ccTypes.h"

NS_CC_BEGIN

/**
 * @brief GradientLabel is a subclass of Label that knows how to render gradient text labels.
 *
 * GradientLabel can be created with:
 * - A true type font file.
 * - A bitmap font file.
 * - A char map file.
 * - The built in system font.
 * @js NA
 */
class CC_DLL GradientLabel : public Label
{
public:
    /// @name Creators
    /// @{

    /**
    * Allocates and initializes a GradientLabel, with default settings.
    *
    * @return An automatically released GradientLabel object.
    */
    static GradientLabel* create();

    /**
     * Allocates and initializes a GradientLabel, base on platform-dependent API.
     *
     * @param text The initial text.
     * @param font A font file or a font family name.
     * @param fontSize The font size. This value must be > 0.
     * @param dimensions
     * @param hAlignment The text horizontal alignment.
     * @param vAlignment The text vertical alignment.
     *
     * @warning It will generate texture by the platform-dependent code.
     *
     * @return An automatically released GradientLabel object.
     */
    static GradientLabel* createWithSystemFont(const std::string& text, const std::string& font, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /**
    * Allocates and initializes a GradientLabel, base on FreeType2.
    *
    * @param text The initial text.
    * @param fontFilePath A font file.
    * @param fontSize The font size. This value must be > 0.
    * @param dimensions
    * @param hAlignment The text horizontal alignment.
    * @param vAlignment The text vertical alignment.
    *
    * @return An automatically released GradientLabel object.
    */
    static GradientLabel * createWithTTF(const std::string& text, const std::string& fontFilePath, float fontSize,
        const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
        TextVAlignment vAlignment = TextVAlignment::TOP);

    /**
    * Allocates and initializes a GradientLabel, base on FreeType2.
    *
    * @param ttfConfig A pointer to a TTFConfig object.
    * @param text The initial text.
    * @param hAlignment The text horizontal alignment.
    * @param maxLineWidth The max line width.
    *
    * @return An automatically released GradientLabel object.
    * @see TTFConfig setTTFConfig setMaxLineWidth
    */
    static GradientLabel* createWithTTF(const TTFConfig& ttfConfig, const std::string& text,
        TextHAlignment hAlignment = TextHAlignment::LEFT, int maxLineWidth = 0);

    /**
    * Allocates and initializes a GradientLabel, with a bitmap font file.
    *
    * @param bmfontPath A bitmap font file, it's a FNT format.
    * @param text The initial text.
    * @param hAlignment Text horizontal alignment.
    * @param maxLineWidth The max line width.
    * @param imageOffset
    *
    * @return An automatically released GradientLabel object.
    * @see setBMFontFilePath setMaxLineWidth
    */
    static GradientLabel* createWithBMFont(const std::string& bmfontPath, const std::string& text,
        const TextHAlignment& hAlignment = TextHAlignment::LEFT, int maxLineWidth = 0,
        const Vec2& imageOffset = Vec2::ZERO);

    /**
    * Allocates and initializes a GradientLabel, with char map configuration.
    *
    * @param charMapFile A char map file, it's a PNG format.
    * @param itemWidth The width in points of each element.
    * @param itemHeight The height in points of each element.
    * @param startCharMap The starting char of the char map.
    *
    * @return An automatically released GradientLabel object.
    */
    static GradientLabel * createWithCharMap(const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);

    /**
    * Allocates and initializes a GradientLabel, with char map configuration.
    *
    * @param texture A pointer to an existing Texture2D object.
    * @param itemWidth The width in points of each element.
    * @param itemHeight The height in points of each element.
    * @param startCharMap The starting char of the char map.
    *
    * @return An automatically released GradientLabel object.
    */
    static GradientLabel * createWithCharMap(Texture2D* texture, int itemWidth, int itemHeight, int startCharMap);

    /**
    * Allocates and initializes a GradientLabel, with char map configuration.
    *
    * @param plistFile A configuration file of char map.
    *
    * @return An automatically released GradientLabel object.
    */
    static GradientLabel * createWithCharMap(const std::string& plistFile);

    
    CC_DEPRECATED_ATTRIBUTE static GradientLabel* create(const std::string& text, const std::string& font, float fontSize,
                                                         const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
                                                         TextVAlignment vAlignment = TextVAlignment::TOP);
    //  end of creators group
    /// @}
    
    virtual std::string getDescription() const override;
    
    /**
    * Set colors for horizontal and vertical gradients
    *
    * @param leftTop start left top color
    * @param rightTop end right top color
    * @param leftBottom start left bottom color
    * @param rightBottom end right bottom color
    *
    */
    void setGradientColor(const Color4B &leftTop, const Color4B &rightTop, const Color4B &leftBottom, const Color4B &rightBottom);
    
    /**
    * Set colors for horizontal gradients
    *
    * @param color1 start color
    * @param color2 end color
    *
    */
    void setHGradientColor(const Color4B &color1, const Color4B &color2);
    
    /**
    * Set colors for vertical gradients
    *
    * @param color1 start color
    * @param color2 end color
    *
    */
    void setVGradientColor(const Color4B &color1, const Color4B &color2);
    
    /**
    * Return the user define left top color.
    *
    * @return Color4B for left top point.
    */
    const Color4B &getLeftTopColor() const;
    
    /**
    * Return the user define right top color.
    *
    * @return Color4B for right top point.
    */
    const Color4B &getRightTopColor() const;
    
    /**
    * Return the user define left bottom color.
    *
    * @return Color4B for left bottom point.
    */
    const Color4B &getLeftBottomColor() const;
    
    /**
    * Return the user define right bottom color.
    *
    * @return Color4B for right bottom point.
    */
    const Color4B &getRightBottomTopColor() const;

CC_CONSTRUCTOR_ACCESS:
    /**
     * Constructor of GradientLabel.
     * @js NA
     */
    GradientLabel(TextHAlignment hAlignment = TextHAlignment::LEFT,
      TextVAlignment vAlignment = TextVAlignment::TOP);

    /**
     * Destructor of GradientLabel.
     * @js NA
     * @lua NA
     */
    virtual ~GradientLabel();
    
protected:
    virtual void onDraw(const Mat4& transform, bool transformUpdated) override;
    
    virtual void updateShaderProgram() override;
    
    virtual void reset() override;

private:
    Color4B _leftTopColor = Color4B::WHITE;
    Color4B _rightTopColor = Color4B::WHITE;
    
    Color4B _leftBottomColor = Color4B::WHITE;
    Color4B _rightBottomColor = Color4B::WHITE;
    
    Color4F _leftTopColorF;
    Color4F _rightTopColorF;
    
    Color4F _leftBottomColorF;
    Color4F _rightBottomColorF;
    
    GLint _textSize = -1;
    GLint _leftTopUniform = -1;
    GLint _rightTopUniform = -1;
    GLint _leftBottomUniform = -1;
    GLint _rightBottomUniform = -1;

    
    CC_DISALLOW_COPY_AND_ASSIGN(GradientLabel);
};

// end group
/// @}

NS_CC_END

#endif /*__COCOS2D_CCGRADIENTLABEL_H */
