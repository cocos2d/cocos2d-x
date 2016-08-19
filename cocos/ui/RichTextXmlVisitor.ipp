#ifndef _RICHTEXTXMLVISITOR_IPP_
#define _RICHTEXTXMLVISITOR_IPP_
#include "platform/CCSAXParser.h"

USING_NS_CC;

/** @brief parse a XML. */
class RichTextXmlVisitor : public SAXDelegator
{
public:
    /** @brief underline or strikethrough */
    enum class StyleLine {
        NONE,
        UNDERLINE,          /*!< underline */
        STRIKETHROUGH       /*!< a typographical presentation of words with a horizontal line through their center */
    };

    /** @brief outline, shadow or glow */
    enum class StyleEffect {
        NONE,
        OUTLINE,            /*!< outline effect enabled */
        SHADOW,             /*!< shadow effect enabled */
        GLOW                /*!< glow effect enabled @discussion Limiting use to only when the Label created with true type font. */
    };

    /** @brief the attributes of text tag */
    struct Attributes
    {
        std::string face;                       /*!< font name */
        std::string url;                        /*!< url is a attribute of a anchor tag */
        float fontSize;                         /*!< font size */
        Color3B color;                          /*!< font color */
        bool hasColor;                          /*!< or color is specified? */
        bool bold;                              /*!< bold text */
        bool italics;                           /*!< italic text */
        StyleLine line;                         /*!< underline or strikethrough */
        StyleEffect effect;                     /*!< outline, shadow or glow */
        Color3B outlineColor;                   /*!< the color of the outline */
        int outlineSize;                        /*!< the outline effect size value */
        Color3B shadowColor;                    /*!< the shadow effect color value */
        cocos2d::Size shadowOffset;             /*!< shadow effect offset value */
        int shadowBlurRadius;                   /*!< the shadow effect blur radius */
        Color3B glowColor;                      /*!< the glow effect color value */

        void setColor(const Color3B& acolor)
        {
            color = acolor;
            hasColor = true;
        }
        Attributes()
            : bold(false)
            , italics(false)
            , line(StyleLine::NONE)
            , hasColor(false)
            , fontSize(-1)
            , effect(StyleEffect::NONE)
        {
        }
    };

private:
    std::vector<Attributes> _fontElements;

    RichText* _richText;

    struct TagBehavior {
        bool                isFontElement;
        RichText::VisitEnterHandler   handleVisitEnter;
    };
    typedef std::unordered_map<std::string, TagBehavior> TagTables;

    static TagTables        _tagTables;

public:
    explicit RichTextXmlVisitor(RichText* richText);
    virtual ~RichTextXmlVisitor();

    Color3B getColor() const;

    float getFontSize() const;

    std::string getFace() const;

    std::string getURL() const;

    bool getBold() const;

    bool getItalics() const;

    bool getUnderline() const;

    bool getStrikethrough() const;

    std::tuple<bool, Color3B, int> getOutline() const;

    std::tuple<bool, Color3B, cocos2d::Size, int> getShadow() const;

    std::tuple<bool, Color3B> getGlow() const;

    /// Visit an element.
    virtual void startElement(void *ctx, const char *name, const char **atts) override;

    /// Visit an element.
    virtual void endElement(void *ctx, const char *name) override;

    /// Visit a text node.
    virtual void textHandler(void *ctx, const char *s, int len) override;

    void pushBackFontElement(const Attributes& attribs);

    void popBackFontElement();

    void pushBackElement(RichElement* element);

    static void setTagDescription(const std::string& tag, bool isFontElement, RichText::VisitEnterHandler handleVisitEnter);

    static void removeTagDescription(const std::string& tag);

private:
    ValueMap tagAttrMapWithXMLElement(const char ** attrs);
};

RichTextXmlVisitor::TagTables RichTextXmlVisitor::_tagTables;

RichTextXmlVisitor::RichTextXmlVisitor(RichText* richText)
    : _richText(richText)
    , _fontElements(20)
{
    RichTextXmlVisitor::setTagDescription("font", true, [](const ValueMap& tagAttrValueMap) {
        // supported attributes:
        // size, color, align, face
        ValueMap attrValueMap;

        if (tagAttrValueMap.find("size") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_FONT_SIZE] = tagAttrValueMap.at("size").asString();
        }
        if (tagAttrValueMap.find("color") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_FONT_COLOR_STRING] = tagAttrValueMap.at("color").asString();
        }
        if (tagAttrValueMap.find("face") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_FONT_FACE] = tagAttrValueMap.at("face").asString();
        }

        return make_pair(attrValueMap, nullptr);
    });

    RichTextXmlVisitor::setTagDescription("b", true, [](const ValueMap& tagAttrValueMap) {
        // no supported attributes
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_TEXT_BOLD] = true;
        return make_pair(attrValueMap, nullptr);
    });

    RichTextXmlVisitor::setTagDescription("i", true, [](const ValueMap& tagAttrValueMap) {
        // no supported attributes
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_TEXT_ITALIC] = true;
        return make_pair(attrValueMap, nullptr);
    });

    RichTextXmlVisitor::setTagDescription("del", true, [](const ValueMap& tagAttrValueMap) {
        // no supported attributes
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_TEXT_LINE] = RichText::VALUE_TEXT_LINE_DEL;
        return make_pair(attrValueMap, nullptr);
    });

    RichTextXmlVisitor::setTagDescription("u", true, [](const ValueMap& tagAttrValueMap) {
        // no supported attributes
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_TEXT_LINE] = RichText::VALUE_TEXT_LINE_UNDER;
        return make_pair(attrValueMap, nullptr);
    });

    RichTextXmlVisitor::setTagDescription("small", true, [](const ValueMap& tagAttrValueMap) {
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_FONT_SMALL] = true;
        return make_pair(attrValueMap, nullptr);
    });

    RichTextXmlVisitor::setTagDescription("big", true, [](const ValueMap& tagAttrValueMap) {
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_FONT_BIG] = true;
        return make_pair(attrValueMap, nullptr);
    });

    RichTextXmlVisitor::setTagDescription("img", false, [](const ValueMap& tagAttrValueMap) {
        // supported attributes:
        // src, height, width
        std::string src;
        int height = -1;
        int width = -1;

        if (tagAttrValueMap.find("src") != tagAttrValueMap.end()) {
            src = tagAttrValueMap.at("src").asString();
        }
        if (tagAttrValueMap.find("height") != tagAttrValueMap.end()) {
            height = tagAttrValueMap.at("height").asInt();
        }
        if (tagAttrValueMap.find("width") != tagAttrValueMap.end()) {
            width = tagAttrValueMap.at("width").asInt();
        }

        RichElementImage* elementImg = nullptr;
        if (src.length()) {
            elementImg = RichElementImage::create(0, Color3B::WHITE, 255, src);
            if (0 <= height) elementImg->setHeight(height);
            if (0 <= width)  elementImg->setWidth(width);
        }
        return make_pair(ValueMap(), elementImg);
    });

    RichTextXmlVisitor::setTagDescription("a", true, [](const ValueMap& tagAttrValueMap) {
        // supported attributes:
        ValueMap attrValueMap;

        if (tagAttrValueMap.find("href") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_URL] = tagAttrValueMap.at("href").asString();
        }
        return make_pair(attrValueMap, nullptr);
    });

    RichTextXmlVisitor::setTagDescription("br", false, [](const ValueMap& tagAttrValueMap)  {
        RichElementNewLine* richElement = RichElementNewLine::create(0, Color3B::WHITE, 255);
        return make_pair(ValueMap(), richElement);
    });

    RichTextXmlVisitor::setTagDescription("outline", true, [](const ValueMap& tagAttrValueMap) {
        // supported attributes:
        // color, size
        ValueMap attrValueMap;

        attrValueMap[RichText::KEY_TEXT_STYLE] = RichText::VALUE_TEXT_STYLE_OUTLINE;
        if (tagAttrValueMap.find("color") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_TEXT_OUTLINE_COLOR] = tagAttrValueMap.at("color").asString();
        }
        if (tagAttrValueMap.find("size") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_TEXT_OUTLINE_SIZE] = tagAttrValueMap.at("size").asString();
        }
        return make_pair(attrValueMap, nullptr);
    });

    RichTextXmlVisitor::setTagDescription("shadow", true, [](const ValueMap& tagAttrValueMap) {
        // supported attributes:
        // color, offsetWidth, offsetHeight, blurRadius
        ValueMap attrValueMap;

        attrValueMap[RichText::KEY_TEXT_STYLE] = RichText::VALUE_TEXT_STYLE_SHADOW;
        if (tagAttrValueMap.find("color") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_TEXT_SHADOW_COLOR] = tagAttrValueMap.at("color").asString();
        }
        if (tagAttrValueMap.find("offsetWidth") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_TEXT_SHADOW_OFFSET_WIDTH] = tagAttrValueMap.at("offsetWidth").asString();
        }
        if (tagAttrValueMap.find("offsetHeight") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_TEXT_SHADOW_OFFSET_HEIGHT] = tagAttrValueMap.at("offsetHeight").asString();
        }
        if (tagAttrValueMap.find("blurRadius") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_TEXT_SHADOW_BLUR_RADIUS] = tagAttrValueMap.at("blurRadius").asString();
        }
        return make_pair(attrValueMap, nullptr);
    });

    RichTextXmlVisitor::setTagDescription("glow", true, [](const ValueMap& tagAttrValueMap) {
        // supported attributes:
        // color
        ValueMap attrValueMap;

        attrValueMap[RichText::KEY_TEXT_STYLE] = RichText::VALUE_TEXT_STYLE_GLOW;
        if (tagAttrValueMap.find("color") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_TEXT_GLOW_COLOR] = tagAttrValueMap.at("color").asString();
        }
        return make_pair(attrValueMap, nullptr);
    });
}

RichTextXmlVisitor::~RichTextXmlVisitor()
{
}

Color3B RichTextXmlVisitor::getColor() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->hasColor)
            return i->color;
    }
    return Color3B::WHITE;
}

float RichTextXmlVisitor::getFontSize() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->fontSize != -1)
            return i->fontSize;
    }
    return 12;
}

std::string RichTextXmlVisitor::getFace() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->face.size() != 0)
            return i->face;
    }
    return "fonts/Marker Felt.ttf";
}

std::string RichTextXmlVisitor::getURL() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->url.size() != 0)
            return i->url;
    }
    return "";
}

bool RichTextXmlVisitor::getBold() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->bold)
            return true;
    }
    return false;
}

bool RichTextXmlVisitor::getItalics() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->italics)
            return true;
    }
    return false;
}

bool RichTextXmlVisitor::getUnderline() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->line == StyleLine::UNDERLINE)
            return true;
    }
    return false;
}

bool RichTextXmlVisitor::getStrikethrough() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->line == StyleLine::STRIKETHROUGH)
            return true;
    }
    return false;
}

std::tuple<bool, Color3B, int> RichTextXmlVisitor::getOutline() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->effect == StyleEffect::OUTLINE)
            return std::make_tuple(true, i->outlineColor, i->outlineSize);
    }
    return std::make_tuple(false, Color3B::WHITE, -1);
}

std::tuple<bool, Color3B, cocos2d::Size, int> RichTextXmlVisitor::getShadow() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->effect == StyleEffect::SHADOW)
            return std::make_tuple(true, i->shadowColor, i->shadowOffset, i->shadowBlurRadius);
    }
    return std::make_tuple(false, Color3B::BLACK, Size(2.0, -2.0), 0);
}

std::tuple<bool, Color3B> RichTextXmlVisitor::getGlow() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->effect == StyleEffect::GLOW)
            return std::make_tuple(true, i->glowColor);
    }
    return std::make_tuple(false, Color3B::WHITE);
}

void RichTextXmlVisitor::startElement(void *ctx, const char *elementName, const char **atts)
{
    auto it = _tagTables.find(elementName);
    if (it != _tagTables.end()) {
        auto tagBehavior = it->second;
        if (tagBehavior.handleVisitEnter != nullptr) {
            ValueMap&& tagAttrValueMap = tagAttrMapWithXMLElement(atts);
            auto result = tagBehavior.handleVisitEnter(tagAttrValueMap);
            ValueMap& attrValueMap = result.first;
            RichElement* richElement = result.second;
            if (!attrValueMap.empty()) {
                Attributes attributes;

                if (attrValueMap.find(RichText::KEY_FONT_SIZE) != attrValueMap.end()) {
                    attributes.fontSize = attrValueMap.at(RichText::KEY_FONT_SIZE).asFloat();
                }
                if (attrValueMap.find(RichText::KEY_FONT_SMALL) != attrValueMap.end()) {
                    attributes.fontSize = getFontSize() * 0.8f;
                }
                if (attrValueMap.find(RichText::KEY_FONT_BIG) != attrValueMap.end()) {
                    attributes.fontSize = getFontSize() * 1.25f;
                }
                if (attrValueMap.find(RichText::KEY_FONT_COLOR_STRING) != attrValueMap.end()) {
                    attributes.setColor(_richText->color3BWithString(attrValueMap.at(RichText::KEY_FONT_COLOR_STRING).asString()));
                }
                if (attrValueMap.find(RichText::KEY_FONT_FACE) != attrValueMap.end()) {
                    attributes.face = attrValueMap.at(RichText::KEY_FONT_FACE).asString();
                }
                if (attrValueMap.find(RichText::KEY_TEXT_BOLD) != attrValueMap.end()) {
                    attributes.bold = true;
                }
                if (attrValueMap.find(RichText::KEY_TEXT_ITALIC) != attrValueMap.end()) {
                    attributes.italics = true;
                }
                if (attrValueMap.find(RichText::KEY_TEXT_LINE) != attrValueMap.end()) {
                    auto keyTextLine = attrValueMap.at(RichText::KEY_TEXT_LINE).asString();
                    if (keyTextLine == RichText::VALUE_TEXT_LINE_DEL) {
                        attributes.line = StyleLine::STRIKETHROUGH;
                    }
                    else if (keyTextLine == RichText::VALUE_TEXT_LINE_UNDER) {
                        attributes.line = StyleLine::UNDERLINE;
                    }
                }
                if (attrValueMap.find(RichText::KEY_URL) != attrValueMap.end()) {
                    attributes.url = attrValueMap.at(RichText::KEY_URL).asString();
                    attributes.setColor(_richText->getAnchorFontColor3B());
                    if (_richText->isAnchorTextBoldEnabled()) {
                        attributes.bold = true;
                    }
                    if (_richText->isAnchorTextItalicEnabled()) {
                        attributes.italics = true;
                    }
                    if (_richText->isAnchorTextUnderlineEnabled()) {
                        attributes.line = StyleLine::UNDERLINE;
                    }
                    if (_richText->isAnchorTextDelEnabled()) {
                        attributes.line = StyleLine::STRIKETHROUGH;
                    }
                    if (_richText->isAnchorTextOutlineEnabled()) {
                        attributes.effect = StyleEffect::OUTLINE;
                        attributes.outlineColor = _richText->getAnchorTextOutlineColor3B();
                        attributes.outlineSize = _richText->getAnchorTextOutlineSize();
                    }
                    if (_richText->isAnchorTextShadowEnabled()) {
                        attributes.effect = StyleEffect::SHADOW;
                        attributes.shadowColor = _richText->getAnchorTextShadowColor3B();
                        attributes.shadowOffset = _richText->getAnchorTextShadowOffset();
                        attributes.shadowBlurRadius = _richText->getAnchorTextShadowBlurRadius();
                    }
                    if (_richText->isAnchorTextGlowEnabled()) {
                        attributes.effect = StyleEffect::GLOW;
                        attributes.glowColor = _richText->getAnchorTextGlowColor3B();
                    }
                }
                if (attrValueMap.find(RichText::KEY_TEXT_STYLE) != attrValueMap.end()) {
                    auto keyTextStyle = attrValueMap.at(RichText::KEY_TEXT_STYLE).asString();
                    if (keyTextStyle == RichText::VALUE_TEXT_STYLE_OUTLINE) {
                        attributes.effect = StyleEffect::OUTLINE;
                        if (attrValueMap.find(RichText::KEY_TEXT_OUTLINE_COLOR) != attrValueMap.end()) {
                            attributes.outlineColor = _richText->color3BWithString(attrValueMap.at(RichText::KEY_TEXT_OUTLINE_COLOR).asString());
                        }
                        if (attrValueMap.find(RichText::KEY_TEXT_OUTLINE_SIZE) != attrValueMap.end()) {
                            attributes.outlineSize = attrValueMap.at(RichText::KEY_TEXT_OUTLINE_SIZE).asInt();
                        }
                    }
                    else if (keyTextStyle == RichText::VALUE_TEXT_STYLE_SHADOW) {
                        attributes.effect = StyleEffect::SHADOW;
                        if (attrValueMap.find(RichText::KEY_TEXT_SHADOW_COLOR) != attrValueMap.end()) {
                            attributes.shadowColor = _richText->color3BWithString(attrValueMap.at(RichText::KEY_TEXT_SHADOW_COLOR).asString());
                        }
                        if ((attrValueMap.find(RichText::KEY_TEXT_SHADOW_OFFSET_WIDTH) != attrValueMap.end())
                            && (attrValueMap.find(RichText::KEY_TEXT_SHADOW_OFFSET_HEIGHT) != attrValueMap.end())) {
                            attributes.shadowOffset = Size(attrValueMap.at(RichText::KEY_TEXT_SHADOW_OFFSET_WIDTH).asFloat(),
                                attrValueMap.at(RichText::KEY_TEXT_SHADOW_OFFSET_HEIGHT).asFloat());
                        }
                        if (attrValueMap.find(RichText::KEY_TEXT_SHADOW_BLUR_RADIUS) != attrValueMap.end()) {
                            attributes.shadowBlurRadius = attrValueMap.at(RichText::KEY_TEXT_SHADOW_BLUR_RADIUS).asInt();
                        }
                    }
                    else if (keyTextStyle == RichText::VALUE_TEXT_STYLE_GLOW) {
                        attributes.effect = StyleEffect::GLOW;
                        if (attrValueMap.find(RichText::KEY_TEXT_GLOW_COLOR) != attrValueMap.end()) {
                            attributes.glowColor = _richText->color3BWithString(attrValueMap.at(RichText::KEY_TEXT_GLOW_COLOR).asString());
                        }
                    }
                }

                pushBackFontElement(attributes);
            }
            if (richElement) {
                if (richElement->equalType(RichElement::Type::IMAGE)) {
                    richElement->setColor(getColor());
                    auto* richElementImage = static_cast<RichElementImage*>(richElement);
                    richElementImage->setUrl(getURL());
                }
                else if (richElement->equalType(RichElement::Type::NEWLINE)) {
                    richElement->setColor(getColor());
                }
                pushBackElement(richElement);
            }
        }
    }
}

void RichTextXmlVisitor::endElement(void *ctx, const char *name)
{
    auto elementName = name;
    auto it = _tagTables.find(elementName);
    if (it != _tagTables.end()) {
        auto tagBehavior = it->second;
        if (tagBehavior.isFontElement) {
            popBackFontElement();
        }
    }
}

void RichTextXmlVisitor::textHandler(void *ctx, const char *str, int len)
{
    std::string text(str, len);
    auto color = getColor();
    auto face = getFace();
    auto fontSize = getFontSize();
    auto italics = getItalics();
    auto underline = getUnderline();
    auto strikethrough = getStrikethrough();
    auto bold = getBold();
    auto url = getURL();
    auto outline = getOutline();
    auto shadow = getShadow();
    auto glow = getGlow();

    uint32_t flags = 0;
    if (italics)
        flags |= RichElementText::ITALICS_FLAG;
    if (bold)
        flags |= RichElementText::BOLD_FLAG;
    if (underline)
        flags |= RichElementText::UNDERLINE_FLAG;
    if (strikethrough)
        flags |= RichElementText::STRIKETHROUGH_FLAG;
    if (url.size() > 0)
        flags |= RichElementText::URL_FLAG;
    if (std::get<0>(outline))
        flags |= RichElementText::OUTLINE_FLAG;
    if (std::get<0>(shadow))
        flags |= RichElementText::SHADOW_FLAG;
    if (std::get<0>(glow))
        flags |= RichElementText::GLOW_FLAG;

    auto element = RichElementText::create(0, color, 255, text, face, fontSize, flags, url,
        std::get<1>(outline), std::get<2>(outline),
        std::get<1>(shadow), std::get<2>(shadow), std::get<3>(shadow),
        std::get<1>(glow));
    _richText->pushBackElement(element);
}

void RichTextXmlVisitor::pushBackFontElement(const RichTextXmlVisitor::Attributes& attribs)
{
    _fontElements.push_back(attribs);
}

void RichTextXmlVisitor::popBackFontElement()
{
    _fontElements.pop_back();
}

void RichTextXmlVisitor::pushBackElement(RichElement* element)
{
    _richText->pushBackElement(element);
}

void RichTextXmlVisitor::setTagDescription(const std::string& tag, bool isFontElement, RichText::VisitEnterHandler handleVisitEnter)
{
    RichTextXmlVisitor::_tagTables[tag] = { isFontElement, handleVisitEnter };
}

void RichTextXmlVisitor::removeTagDescription(const std::string& tag)
{
    RichTextXmlVisitor::_tagTables.erase(tag);
}

ValueMap RichTextXmlVisitor::tagAttrMapWithXMLElement(const char ** attrs)
{
    ValueMap tagAttrValueMap;
    for (const char** attr = attrs; *attr != nullptr; attr = (attrs += 2)) {
        if (attr[0] && attr[1]) {
            tagAttrValueMap[attr[0]] = attr[1];
        }
    }
    return tagAttrValueMap;
}

#endif
