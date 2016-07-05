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

#include "ui/UIRichText.h"

#include <sstream>
#include <vector>
#include <locale>

#include "tinyxml2.h"
#include "platform/CCFileUtils.h"
#include "platform/CCApplication.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"
#include "base/CCDirector.h"
#include "2d/CCLabel.h"
#include "2d/CCSprite.h"
#include "base/ccUTF8.h"
#include "ui/UIHelper.h"

USING_NS_CC;
using namespace cocos2d::ui;

class ListenerComponent : public Component
{
public:
    static const std::string COMPONENT_NAME;    /*!< component name */

    static ListenerComponent* create(Node* parent, const std::string& url, const RichText::OpenUrlHandler handleOpenUrl = nullptr)
    {
        auto component = new (std::nothrow) ListenerComponent(parent, url, handleOpenUrl);
        component->autorelease();
        return component;
    }

    explicit ListenerComponent(Node* parent, const std::string& url, const RichText::OpenUrlHandler handleOpenUrl)
    : _parent(parent)
    , _url(url)
    , _handleOpenUrl(handleOpenUrl)
    {
        setName(ListenerComponent::COMPONENT_NAME);
        
        _touchListener = cocos2d::EventListenerTouchAllAtOnce::create();
        _touchListener->onTouchesEnded = CC_CALLBACK_2(ListenerComponent::onTouchesEnded, this);

        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, _parent);
        _touchListener->retain();
    }

    virtual ~ListenerComponent()
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListener);
        _touchListener->release();
    }

    void onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
    {
        for (const auto& touch: touches)
        {
            // FIXME: Node::getBoundBox() doesn't return it in local coordinates... so create one manually.
            Rect localRect = Rect(Vec2::ZERO, _parent->getContentSize());
            if (localRect.containsPoint(_parent->convertTouchToNodeSpace(touch))) {
                if (_handleOpenUrl) {
                    _handleOpenUrl(_url);
                }
            }
        }
    }
    
    void setOpenUrlHandler(const RichText::OpenUrlHandler& handleOpenUrl)
    {
        _handleOpenUrl = handleOpenUrl;
    }

private:
    Node* _parent;      // weak ref.
    std::string _url;
    RichText::OpenUrlHandler _handleOpenUrl;
    EventDispatcher* _eventDispatcher;  // weak ref.
    EventListenerTouchAllAtOnce* _touchListener;    // strong ref.
};
const std::string ListenerComponent::COMPONENT_NAME("cocos2d_ui_UIRichText_ListenerComponent");

bool RichElement::init(int tag, const Color3B &color, GLubyte opacity)
{
    _tag = tag;
    _color = color;
    _opacity = opacity;
    return true;
}

bool RichElement::equalType(Type type)
{
    return (_type == type);
}

void RichElement::setColor(const Color3B& color)
{
    _color = color;
}

RichElementText* RichElementText::create(int tag, const Color3B &color, GLubyte opacity, const std::string& text,
                                         const std::string& fontName, float fontSize, uint32_t flags, const std::string& url,
                                         const Color3B& outlineColor, int outlineSize ,
                                         const Color3B& shadowColor, const cocos2d::Size& shadowOffset, int shadowBlurRadius,
                                         const Color3B& glowColor)
{
    RichElementText* element = new (std::nothrow) RichElementText();
    if (element && element->init(tag, color, opacity, text, fontName, fontSize, flags, url,
                                 outlineColor, outlineSize, shadowColor, shadowOffset, shadowBlurRadius, glowColor))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementText::init(int tag, const Color3B &color, GLubyte opacity, const std::string& text,
                           const std::string& fontName, float fontSize, uint32_t flags, const std::string& url,
                           const Color3B& outlineColor, int outlineSize ,
                           const Color3B& shadowColor, const cocos2d::Size& shadowOffset, int shadowBlurRadius,
                           const Color3B& glowColor)
{
    if (RichElement::init(tag, color, opacity))
    {
        _text = text;
        _fontName = fontName;
        _fontSize = fontSize;
        _flags = flags;
        _url = url;
        _outlineColor = outlineColor;
        _outlineSize = outlineSize;
        _shadowColor = shadowColor;
        _shadowOffset = shadowOffset;
        _shadowBlurRadius = shadowBlurRadius;
        _glowColor = glowColor;
        return true;
    }
    return false;
}

RichElementImage* RichElementImage::create(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath, const std::string& url)
{
    RichElementImage* element = new (std::nothrow) RichElementImage();
    if (element && element->init(tag, color, opacity, filePath, url))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementImage::init(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath, const std::string& url)
{
    if (RichElement::init(tag, color, opacity))
    {
        _filePath = filePath;
        _width = -1;
        _height = -1;
        _url = url;
        return true;
    }
    return false;
}

void RichElementImage::setWidth(int width)
{
    _width = width;
}

void RichElementImage::setHeight(int height)
{
    _height = height;
}

void RichElementImage::setUrl(const std::string& url)
{
    _url = url;
}

RichElementCustomNode* RichElementCustomNode::create(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
{
    RichElementCustomNode* element = new (std::nothrow) RichElementCustomNode();
    if (element && element->init(tag, color, opacity, customNode))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementCustomNode::init(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
{
    if (RichElement::init(tag, color, opacity))
    {
        _customNode = customNode;
        _customNode->retain();
        return true;
    }
    return false;
}
    
RichElementNewLine* RichElementNewLine::create(int tag, const Color3B& color, GLubyte opacity)
{
    RichElementNewLine* element = new (std::nothrow) RichElementNewLine();
    if (element && element->init(tag, color, opacity))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}

/** @brief parse a XML. */
class MyXMLVisitor: public tinyxml2::XMLVisitor
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
    explicit MyXMLVisitor(RichText* richText);
    virtual ~MyXMLVisitor();
    
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
    virtual bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute );
    
    /// Visit an element.
    virtual bool VisitExit( const tinyxml2::XMLElement& element );
    
    /// Visit a text node.
    virtual bool Visit(const tinyxml2::XMLText& text);
    
    void pushBackFontElement(const Attributes& attribs);
    
    void popBackFontElement();
    
    void pushBackElement(RichElement* element);
    
    static void setTagDescription(const std::string& tag, bool isFontElement, RichText::VisitEnterHandler handleVisitEnter);
    
    static void removeTagDescription(const std::string& tag);
    
private:
    ValueMap tagAttrMapWithXMLElement(const tinyxml2::XMLElement& element);
};

MyXMLVisitor::TagTables MyXMLVisitor::_tagTables;

MyXMLVisitor::MyXMLVisitor(RichText* richText)
: _richText(richText)
, _fontElements(20)
{
    MyXMLVisitor::setTagDescription("font", true, [](const ValueMap& tagAttrValueMap) {
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
    
    MyXMLVisitor::setTagDescription("b", true, [](const ValueMap& tagAttrValueMap) {
        // no supported attributes
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_TEXT_BOLD] = true;
        return make_pair(attrValueMap, nullptr);
    });
    
    MyXMLVisitor::setTagDescription("i", true, [](const ValueMap& tagAttrValueMap) {
        // no supported attributes
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_TEXT_ITALIC] = true;
        return make_pair(attrValueMap, nullptr);
    });
    
    MyXMLVisitor::setTagDescription("del", true, [](const ValueMap& tagAttrValueMap) {
        // no supported attributes
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_TEXT_LINE] = RichText::VALUE_TEXT_LINE_DEL;
        return make_pair(attrValueMap, nullptr);
    });
    
    MyXMLVisitor::setTagDescription("u", true, [](const ValueMap& tagAttrValueMap) {
        // no supported attributes
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_TEXT_LINE] = RichText::VALUE_TEXT_LINE_UNDER;
        return make_pair(attrValueMap, nullptr);
    });
    
    MyXMLVisitor::setTagDescription("small", true, [](const ValueMap& tagAttrValueMap) {
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_FONT_SMALL] = true;
        return make_pair(attrValueMap, nullptr);
    });
    
    MyXMLVisitor::setTagDescription("big", true, [](const ValueMap& tagAttrValueMap) {
        ValueMap attrValueMap;
        attrValueMap[RichText::KEY_FONT_BIG] = true;
        return make_pair(attrValueMap, nullptr);
    });
    
    MyXMLVisitor::setTagDescription("img", false, [](const ValueMap& tagAttrValueMap) {
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
    
    MyXMLVisitor::setTagDescription("a", true, [](const ValueMap& tagAttrValueMap) {
        // supported attributes:
        ValueMap attrValueMap;
        
        if (tagAttrValueMap.find("href") != tagAttrValueMap.end()) {
            attrValueMap[RichText::KEY_URL] = tagAttrValueMap.at("href").asString();
        }
        return make_pair(attrValueMap, nullptr);
    });
    
    MyXMLVisitor::setTagDescription("br", false, [](const ValueMap& tagAttrValueMap)  {
        RichElementNewLine* richElement = RichElementNewLine::create(0, Color3B::WHITE, 255);
        return make_pair(ValueMap(), richElement);
    });
    
    MyXMLVisitor::setTagDescription("outline", true, [](const ValueMap& tagAttrValueMap) {
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
    
    MyXMLVisitor::setTagDescription("shadow", true, [](const ValueMap& tagAttrValueMap) {
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
    
    MyXMLVisitor::setTagDescription("glow", true, [](const ValueMap& tagAttrValueMap) {
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

MyXMLVisitor::~MyXMLVisitor()
{
}

Color3B MyXMLVisitor::getColor() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->hasColor)
            return i->color;
    }
    return Color3B::WHITE;
}

float MyXMLVisitor::getFontSize() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->fontSize != -1)
            return i->fontSize;
    }
    return 12;
}

std::string MyXMLVisitor::getFace() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->face.size() != 0)
            return i->face;
    }
    return "fonts/Marker Felt.ttf";
}

std::string MyXMLVisitor::getURL() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->url.size() != 0)
            return i->url;
    }
    return "";
}

bool MyXMLVisitor::getBold() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->bold)
            return true;
    }
    return false;
}

bool MyXMLVisitor::getItalics() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->italics)
            return true;
    }
    return false;
}

bool MyXMLVisitor::getUnderline() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->line == StyleLine::UNDERLINE)
            return true;
    }
    return false;
}

bool MyXMLVisitor::getStrikethrough() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->line == StyleLine::STRIKETHROUGH)
            return true;
    }
    return false;
}

std::tuple<bool, Color3B, int> MyXMLVisitor::getOutline() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->effect == StyleEffect::OUTLINE)
            return std::make_tuple(true, i->outlineColor, i->outlineSize);
    }
    return std::make_tuple(false, Color3B::WHITE, -1);
}

std::tuple<bool, Color3B, cocos2d::Size, int> MyXMLVisitor::getShadow() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->effect == StyleEffect::SHADOW)
            return std::make_tuple(true, i->shadowColor, i->shadowOffset, i->shadowBlurRadius);
    }
    return std::make_tuple(false, Color3B::BLACK, Size(2.0, -2.0), 0);
}

std::tuple<bool, Color3B> MyXMLVisitor::getGlow() const
{
    for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
    {
        if (i->effect == StyleEffect::GLOW)
            return std::make_tuple(true, i->glowColor);
    }
    return std::make_tuple(false, Color3B::WHITE);
}

bool MyXMLVisitor::VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute )
{
    auto elementName = element.Value();
    auto it = _tagTables.find(elementName);
    if (it != _tagTables.end()) {
        auto tagBehavior = it->second;
        if (tagBehavior.handleVisitEnter != nullptr) {
            ValueMap&& tagAttrValueMap = tagAttrMapWithXMLElement(element);
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
    return true;
}

bool MyXMLVisitor::VisitExit( const tinyxml2::XMLElement& element )
{
    auto elementName = element.Value();
    auto it = _tagTables.find(elementName);
    if (it != _tagTables.end()) {
        auto tagBehavior = it->second;
        if (tagBehavior.isFontElement) {
            popBackFontElement();
        }
    }
    return true;
}

bool MyXMLVisitor::Visit(const tinyxml2::XMLText& text)
{
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
    
    auto element = RichElementText::create(0, color, 255, text.Value(), face, fontSize, flags, url,
                                           std::get<1>(outline), std::get<2>(outline),
                                           std::get<1>(shadow), std::get<2>(shadow), std::get<3>(shadow),
                                           std::get<1>(glow));
    _richText->pushBackElement(element);
    return true;
}

void MyXMLVisitor::pushBackFontElement(const MyXMLVisitor::Attributes& attribs)
{
    _fontElements.push_back(attribs);
}

void MyXMLVisitor::popBackFontElement()
{
    _fontElements.pop_back();
}

void MyXMLVisitor::pushBackElement(RichElement* element)
{
    _richText->pushBackElement(element);
}

void MyXMLVisitor::setTagDescription(const std::string& tag, bool isFontElement, RichText::VisitEnterHandler handleVisitEnter)
{
    MyXMLVisitor::_tagTables[tag] = {isFontElement, handleVisitEnter};
}

void MyXMLVisitor::removeTagDescription(const std::string& tag)
{
    MyXMLVisitor::_tagTables.erase(tag);
}

ValueMap MyXMLVisitor::tagAttrMapWithXMLElement(const tinyxml2::XMLElement& element)
{
    ValueMap tagAttrValueMap;
    for (const tinyxml2::XMLAttribute* attr = element.FirstAttribute(); attr != nullptr; attr = attr->Next()) {
        if (attr->Name() && attr->Value()) {
            tagAttrValueMap[std::string(attr->Name())] = std::string(attr->Value());
        }
    }
    return tagAttrValueMap;
}

const std::string RichText::KEY_VERTICAL_SPACE("KEY_VERTICAL_SPACE");
const std::string RichText::KEY_WRAP_MODE("KEY_WRAP_MODE");
const std::string RichText::KEY_FONT_COLOR_STRING("KEY_FONT_COLOR_STRING");
const std::string RichText::KEY_FONT_SIZE("KEY_FONT_SIZE");
const std::string RichText::KEY_FONT_SMALL("KEY_FONT_SMALL");
const std::string RichText::KEY_FONT_BIG("KEY_FONT_BIG");
const std::string RichText::KEY_FONT_FACE("KEY_FONT_FACE");
const std::string RichText::KEY_TEXT_BOLD("KEY_TEXT_BOLD");
const std::string RichText::KEY_TEXT_ITALIC("KEY_TEXT_ITALIC");
const std::string RichText::KEY_TEXT_LINE("KEY_TEXT_LINE");
const std::string RichText::VALUE_TEXT_LINE_NONE("VALUE_TEXT_LINE_NONE");
const std::string RichText::VALUE_TEXT_LINE_DEL("VALUE_TEXT_LINE_DEL");
const std::string RichText::VALUE_TEXT_LINE_UNDER("VALUE_TEXT_LINE_UNDER");
const std::string RichText::KEY_TEXT_STYLE("KEY_TEXT_STYLE");
const std::string RichText::VALUE_TEXT_STYLE_NONE("VALUE_TEXT_STYLE_NONE");
const std::string RichText::VALUE_TEXT_STYLE_OUTLINE("VALUE_TEXT_STYLE_OUTLINE");
const std::string RichText::VALUE_TEXT_STYLE_SHADOW("VALUE_TEXT_STYLE_SHADOW");
const std::string RichText::VALUE_TEXT_STYLE_GLOW("VALUE_TEXT_STYLE_GLOW");
const std::string RichText::KEY_TEXT_OUTLINE_COLOR("KEY_TEXT_OUTLINE_COLOR");
const std::string RichText::KEY_TEXT_OUTLINE_SIZE("KEY_TEXT_OUTLINE_SIZE");
const std::string RichText::KEY_TEXT_SHADOW_COLOR("KEY_TEXT_SHADOW_COLOR");
const std::string RichText::KEY_TEXT_SHADOW_OFFSET_WIDTH("KEY_TEXT_SHADOW_OFFSET_WIDTH");
const std::string RichText::KEY_TEXT_SHADOW_OFFSET_HEIGHT("KEY_TEXT_SHADOW_OFFSET_HEIGHT");
const std::string RichText::KEY_TEXT_SHADOW_BLUR_RADIUS("KEY_TEXT_SHADOW_BLUR_RADIUS");
const std::string RichText::KEY_TEXT_GLOW_COLOR("KEY_TEXT_GLOW_COLOR");
const std::string RichText::KEY_URL("KEY_URL");
const std::string RichText::KEY_ANCHOR_FONT_COLOR_STRING("KEY_ANCHOR_FONT_COLOR_STRING");
const std::string RichText::KEY_ANCHOR_TEXT_BOLD("KEY_ANCHOR_TEXT_BOLD");
const std::string RichText::KEY_ANCHOR_TEXT_ITALIC("KEY_ANCHOR_TEXT_ITALIC");
const std::string RichText::KEY_ANCHOR_TEXT_LINE("KEY_ANCHOR_TEXT_LINE");
const std::string RichText::KEY_ANCHOR_TEXT_STYLE("KEY_ANCHOR_TEXT_STYLE");
const std::string RichText::KEY_ANCHOR_TEXT_OUTLINE_COLOR("KEY_ANCHOR_TEXT_OUTLINE_COLOR");
const std::string RichText::KEY_ANCHOR_TEXT_OUTLINE_SIZE("KEY_ANCHOR_TEXT_OUTLINE_SIZE");
const std::string RichText::KEY_ANCHOR_TEXT_SHADOW_COLOR("KEY_ANCHOR_TEXT_SHADOW_COLOR");
const std::string RichText::KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH("KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH");
const std::string RichText::KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT("KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT");
const std::string RichText::KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS("KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS");
const std::string RichText::KEY_ANCHOR_TEXT_GLOW_COLOR("KEY_ANCHOR_TEXT_GLOW_COLOR");

RichText::RichText()
    : _formatTextDirty(true)
    , _leftSpaceWidth(0.0f)
{
    _defaults[KEY_VERTICAL_SPACE] = 0.0f;
    _defaults[KEY_WRAP_MODE] = static_cast<int>(WrapMode::WRAP_PER_WORD);
    _defaults[KEY_FONT_COLOR_STRING] = "#ffffff";
    _defaults[KEY_FONT_SIZE] = 12.0f;
    _defaults[KEY_FONT_FACE] = "Verdana";
    _defaults[KEY_ANCHOR_FONT_COLOR_STRING] = "#0000FF";
    _defaults[KEY_ANCHOR_TEXT_BOLD] = false;
    _defaults[KEY_ANCHOR_TEXT_ITALIC] = false;
    _defaults[KEY_ANCHOR_TEXT_LINE] = VALUE_TEXT_LINE_NONE;
    _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_NONE;
}
    
RichText::~RichText()
{
    _richElements.clear();
}
    
RichText* RichText::create()
{
    RichText* widget = new (std::nothrow) RichText();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

RichText* RichText::createWithXML(const std::string& xml, const ValueMap& defaults, const OpenUrlHandler& handleOpenUrl)
{
    RichText* widget = new (std::nothrow) RichText();
    if (widget && widget->initWithXML(xml, defaults, handleOpenUrl))
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool RichText::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}

bool RichText::initWithXML(const std::string& origxml, const ValueMap& defaults, const OpenUrlHandler& handleOpenUrl)
{
    static std::function<std::string(RichText*)> startTagFont = [](RichText* richText) {
        std::string fontFace = richText->getFontFace();
        std::stringstream ss;
        ss << richText->getFontSize();
        std::string fontSize = ss.str();
        std::string fontColor = richText->getFontColor();
        return "<font face=\"" + fontFace + "\" size=\"" + fontSize + "\" color=\"" + fontColor + "\">";
    };
    if (Widget::init())
    {
        setDefaults(defaults);
        setOpenUrlHandler(handleOpenUrl);
        
        tinyxml2::XMLDocument document;

        // solves to issues:
        //  - creates defaults values
        //  - makes sure that the xml well formed and starts with an element
        std::string xml = startTagFont(this);
        xml += origxml;
        xml += "</font>";

        auto error = document.Parse(xml.c_str(), xml.length());
        if (error == tinyxml2::XML_SUCCESS)
        {
            MyXMLVisitor visitor(this);
            document.Accept(&visitor);
            return true;
        }
        CCLOG("cocos2d: UI::RichText: Error parsing xml: %s, %s", document.GetErrorStr1(), document.GetErrorStr2());
    }
    return false;
}
    
void RichText::initRenderer()
{
}

void RichText::insertElement(RichElement *element, int index)
{
    _richElements.insert(index, element);
    _formatTextDirty = true;
}
    
void RichText::pushBackElement(RichElement *element)
{
    _richElements.pushBack(element);
    _formatTextDirty = true;
}
    
void RichText::removeElement(int index)
{
    _richElements.erase(index);
    _formatTextDirty = true;
}
    
void RichText::removeElement(RichElement *element)
{
    _richElements.eraseObject(element);
    _formatTextDirty = true;
}

RichText::WrapMode RichText::getWrapMode() const
{
    return static_cast<RichText::WrapMode>(_defaults.at(KEY_WRAP_MODE).asInt());
}

void RichText::setWrapMode(RichText::WrapMode wrapMode)
{
    if (static_cast<RichText::WrapMode>(_defaults.at(KEY_WRAP_MODE).asInt()) != wrapMode)
    {
        _defaults[KEY_WRAP_MODE] = static_cast<int>(wrapMode);
        _formatTextDirty = true;
    }
}

void RichText::setFontColor(const std::string& color)
{
    _defaults[KEY_FONT_COLOR_STRING] = color;
}

std::string RichText::getFontColor()
{
    return _defaults.at(KEY_FONT_COLOR_STRING).asString();
}

cocos2d::Color3B RichText::getFontColor3B()
{
    return color3BWithString(getFontColor());
}

void RichText::setFontSize(float size)
{
    _defaults[KEY_FONT_SIZE] = size;
}

float RichText::getFontSize()
{
    return _defaults.at(KEY_FONT_SIZE).asFloat();
}

void RichText::setFontFace(const std::string& face)
{
    _defaults[KEY_FONT_FACE] = face;
}

std::string RichText::getFontFace()
{
    return _defaults.at(KEY_FONT_FACE).asString();
}

void RichText::setAnchorFontColor(const std::string& color)
{
    _defaults[KEY_ANCHOR_FONT_COLOR_STRING] = color;
}

std::string RichText::getAnchorFontColor()
{
    return _defaults.at(KEY_ANCHOR_FONT_COLOR_STRING).asString();
}

cocos2d::Color3B RichText::getAnchorFontColor3B()
{
    return color3BWithString(getAnchorFontColor());
}

void RichText::setAnchorTextBold(bool enable)
{
    _defaults[KEY_ANCHOR_TEXT_BOLD] = enable;
}

bool RichText::isAnchorTextBoldEnabled()
{
    return _defaults[KEY_ANCHOR_TEXT_BOLD].asBool();
}

void RichText::setAnchorTextItalic(bool enable)
{
    _defaults[KEY_ANCHOR_TEXT_ITALIC] = enable;
}

bool RichText::isAnchorTextItalicEnabled()
{
    return _defaults[KEY_ANCHOR_TEXT_ITALIC].asBool();
}

void RichText::setAnchorTextDel(bool enable)
{
    if (enable)
        _defaults[KEY_ANCHOR_TEXT_LINE] = VALUE_TEXT_LINE_DEL;
    else if (_defaults[KEY_ANCHOR_TEXT_LINE].asString() == VALUE_TEXT_LINE_DEL)
        _defaults[KEY_ANCHOR_TEXT_LINE] = VALUE_TEXT_LINE_NONE;
}

bool RichText::isAnchorTextDelEnabled()
{
    return (_defaults[KEY_ANCHOR_TEXT_LINE].asString() == VALUE_TEXT_LINE_DEL);
}

void RichText::setAnchorTextUnderline(bool enable)
{
    if (enable)
        _defaults[KEY_ANCHOR_TEXT_LINE] = VALUE_TEXT_LINE_UNDER;
    else if (_defaults[KEY_ANCHOR_TEXT_LINE].asString() == VALUE_TEXT_LINE_UNDER)
        _defaults[KEY_ANCHOR_TEXT_LINE] = VALUE_TEXT_LINE_NONE;
}

bool RichText::isAnchorTextUnderlineEnabled()
{
    return (_defaults[KEY_ANCHOR_TEXT_LINE].asString() == VALUE_TEXT_LINE_UNDER);
}

void RichText::setAnchorTextOutline(bool enable, const Color3B& outlineColor, int outlineSize)
{
    if (enable)
        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_OUTLINE;
    else if (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_OUTLINE)
        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_NONE;
    _defaults[KEY_ANCHOR_TEXT_OUTLINE_COLOR] = stringWithColor3B(outlineColor);
    _defaults[KEY_ANCHOR_TEXT_OUTLINE_SIZE] = outlineSize;
}

bool RichText::isAnchorTextOutlineEnabled()
{
    return (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_OUTLINE);
}

Color3B RichText::getAnchorTextOutlineColor3B()
{
    if (_defaults.find(KEY_ANCHOR_TEXT_OUTLINE_COLOR) != _defaults.end()) {
        return color3BWithString(_defaults.at(KEY_ANCHOR_TEXT_OUTLINE_COLOR).asString());
    }
    return Color3B();
}

int RichText::getAnchorTextOutlineSize()
{
    if (_defaults.find(KEY_ANCHOR_TEXT_OUTLINE_SIZE) != _defaults.end()) {
        return _defaults.at(KEY_ANCHOR_TEXT_OUTLINE_SIZE).asInt();
    }
    return -1;
}

void RichText::setAnchorTextShadow(bool enable, const Color3B& shadowColor, const Size& offset, int blurRadius)
{
    if (enable)
        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_SHADOW;
    else if (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_SHADOW)
        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_NONE;
    _defaults[KEY_ANCHOR_TEXT_SHADOW_COLOR] = stringWithColor3B(shadowColor);
    _defaults[KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH] = offset.width;
    _defaults[KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT] = offset.height;
    _defaults[KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS] = blurRadius;
}

bool RichText::isAnchorTextShadowEnabled()
{
    return (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_SHADOW);
}

Color3B RichText::getAnchorTextShadowColor3B()
{
    if (_defaults.find(KEY_ANCHOR_TEXT_SHADOW_COLOR) != _defaults.end()) {
        return color3BWithString(_defaults.at(KEY_ANCHOR_TEXT_SHADOW_COLOR).asString());
    }
    return Color3B();
}

Size RichText::getAnchorTextShadowOffset()
{
    float width = 2.0f;
    float height = -2.0f;
    if (_defaults.find(KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH) != _defaults.end()) {
        width = _defaults.at(KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH).asFloat();
    }
    if (_defaults.find(KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT) != _defaults.end()) {
        height = _defaults.at(KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT).asFloat();
    }
    return Size(width, height);
}

int RichText::getAnchorTextShadowBlurRadius()
{
    if (_defaults.find(KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS) != _defaults.end()) {
        return _defaults.at(KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS).asInt();
    }
    return 0;
}

void RichText::setAnchorTextGlow(bool enable, const Color3B& glowColor)
{
    if (enable)
        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_GLOW;
    else if (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_GLOW)
        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_NONE;
    _defaults[KEY_ANCHOR_TEXT_GLOW_COLOR] = stringWithColor3B(glowColor);
}

bool RichText::isAnchorTextGlowEnabled()
{
    return (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_GLOW);
}

Color3B RichText::getAnchorTextGlowColor3B()
{
    if (_defaults.find(KEY_ANCHOR_TEXT_GLOW_COLOR) != _defaults.end()) {
        return color3BWithString(_defaults.at(KEY_ANCHOR_TEXT_GLOW_COLOR).asString());
    }
    return Color3B();
}

void RichText::setDefaults(const ValueMap& defaults)
{
    if (defaults.find(KEY_VERTICAL_SPACE) != defaults.end()) {
        _defaults[KEY_VERTICAL_SPACE] = defaults.at(KEY_VERTICAL_SPACE).asFloat();
    }
    if (defaults.find(KEY_WRAP_MODE) != defaults.end()) {
        _defaults[KEY_WRAP_MODE] = defaults.at(KEY_WRAP_MODE).asInt();
    }
    if (defaults.find(KEY_FONT_COLOR_STRING) != defaults.end()) {
        _defaults[KEY_FONT_COLOR_STRING] = defaults.at(KEY_FONT_COLOR_STRING).asString();
    }
    if (defaults.find(KEY_FONT_SIZE) != defaults.end()) {
        _defaults[KEY_FONT_SIZE] = defaults.at(KEY_FONT_SIZE).asFloat();
    }
    if (defaults.find(KEY_FONT_FACE) != defaults.end()) {
        _defaults[KEY_FONT_FACE] = defaults.at(KEY_FONT_FACE).asString();
    }
    if (defaults.find(KEY_ANCHOR_FONT_COLOR_STRING) != defaults.end()) {
        _defaults[KEY_ANCHOR_FONT_COLOR_STRING] = defaults.at(KEY_ANCHOR_FONT_COLOR_STRING).asString();
    }
    if (defaults.find(KEY_ANCHOR_TEXT_BOLD) != defaults.end()) {
        _defaults[KEY_ANCHOR_TEXT_BOLD] = defaults.at(KEY_ANCHOR_TEXT_BOLD).asBool();
    }
    if (defaults.find(KEY_ANCHOR_TEXT_ITALIC) != defaults.end()) {
        _defaults[KEY_ANCHOR_TEXT_ITALIC] = defaults.at(KEY_ANCHOR_TEXT_ITALIC).asBool();
    }
    if (defaults.find(KEY_ANCHOR_TEXT_LINE) != defaults.end()) {
        _defaults[KEY_ANCHOR_TEXT_LINE] = defaults.at(KEY_ANCHOR_TEXT_LINE).asString();
    }
    if (defaults.find(KEY_ANCHOR_TEXT_STYLE) != defaults.end()) {
        _defaults[KEY_ANCHOR_TEXT_STYLE] = defaults.at(KEY_ANCHOR_TEXT_STYLE).asString();
    }
    if (defaults.find(KEY_ANCHOR_TEXT_OUTLINE_COLOR) != defaults.end()) {
        _defaults[KEY_ANCHOR_TEXT_OUTLINE_COLOR] = defaults.at(KEY_ANCHOR_TEXT_OUTLINE_COLOR).asString();
    }
    if (defaults.find(KEY_ANCHOR_TEXT_OUTLINE_SIZE) != defaults.end()) {
        _defaults[KEY_ANCHOR_TEXT_OUTLINE_SIZE] = defaults.at(KEY_ANCHOR_TEXT_OUTLINE_SIZE).asInt();
    }
    if (defaults.find(KEY_ANCHOR_TEXT_SHADOW_COLOR) != defaults.end()) {
        _defaults[KEY_ANCHOR_TEXT_SHADOW_COLOR] = defaults.at(KEY_ANCHOR_TEXT_SHADOW_COLOR).asString();
    }
    if (defaults.find(KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH) != defaults.end()) {
        _defaults[KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH] = defaults.at(KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH).asFloat();
    }
    if (defaults.find(KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT) != defaults.end()) {
        _defaults[KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT] = defaults.at(KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT).asFloat();
    }
    if (defaults.find(KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS) != defaults.end()) {
        _defaults[KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS] = defaults.at(KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS).asInt();
    }
    if (defaults.find(KEY_ANCHOR_TEXT_GLOW_COLOR) != defaults.end()) {
        _defaults[KEY_ANCHOR_TEXT_GLOW_COLOR] = defaults.at(KEY_ANCHOR_TEXT_GLOW_COLOR).asString();
    }
}

ValueMap RichText::getDefaults() const
{
    ValueMap defaults;
    return defaults;
}

cocos2d::Color3B RichText::color3BWithString(const std::string& color)
{
    if (color.length() == 4) {
        int r, g, b;
        sscanf(color.c_str(), "%*c%1x%1x%1x", &r, &g, &b);
        r += r * 16;
        g += g * 16;
        b += b * 16;
        return Color3B(r, g, b);
    }
    else if (color.length() == 7) {
        int r, g, b;
        sscanf(color.c_str(), "%*c%2x%2x%2x", &r, &g, &b);
        return Color3B(r, g, b);
    }
    else if (color.length() == 9) {
        int r, g, b, a;
        sscanf(color.c_str(), "%*c%2x%2x%2x%2x", &r, &g, &b, &a);
        return Color3B(r, g, b);
    }
    return Color3B::WHITE;
}

std::string RichText::stringWithColor3B(const cocos2d::Color3B& color3b)
{
    int r = color3b.r;
    int g = color3b.g;
    int b = color3b.b;
    char buf[8];
    snprintf(buf, sizeof(buf), "#%02x%02x%02x", r, g, b);
    return std::string(buf, 7);
}

std::string RichText::stringWithColor4B(const cocos2d::Color4B& color4b)
{
    int r = color4b.r;
    int g = color4b.g;
    int b = color4b.b;
    int a = color4b.a;
    char buf[10];
    snprintf(buf, sizeof(buf), "#%02x%02x%02x%02x", r, g, b, a);
    return std::string(buf, 9);
}

void RichText::setTagDescription(const std::string& tag, bool isFontElement, VisitEnterHandler handleVisitEnter)
{
    MyXMLVisitor::setTagDescription(tag, isFontElement, handleVisitEnter);
}

void RichText::removeTagDescription(const std::string& tag)
{
    MyXMLVisitor::removeTagDescription(tag);
}

void RichText::openUrl(const std::string& url)
{
    if (_handleOpenUrl) {
        _handleOpenUrl(url);
    }
    else {
        Application::getInstance()->openURL(url);
    }
}

void RichText::setOpenUrlHandler(const OpenUrlHandler& handleOpenUrl)
{
    _handleOpenUrl = handleOpenUrl;
}

void RichText::formatText()
{
    if (_formatTextDirty)
    {
        this->removeAllProtectedChildren();
        _elementRenders.clear();
        if (_ignoreSize)
        {
            addNewLine();
            for (ssize_t i=0; i<_richElements.size(); i++)
            {
                RichElement* element = _richElements.at(i);
                Node* elementRenderer = nullptr;
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        Label* label;
                        if (FileUtils::getInstance()->isFileExist(elmtText->_fontName))
                        {
                             label = Label::createWithTTF(elmtText->_text, elmtText->_fontName, elmtText->_fontSize);
                        }
                        else
                        {
                            label = Label::createWithSystemFont(elmtText->_text, elmtText->_fontName, elmtText->_fontSize);
                        }
                        if (elmtText->_flags & RichElementText::ITALICS_FLAG)
                            label->enableItalics();
                        if (elmtText->_flags & RichElementText::BOLD_FLAG)
                            label->enableBold();
                        if (elmtText->_flags & RichElementText::UNDERLINE_FLAG)
                            label->enableUnderline();
                        if (elmtText->_flags & RichElementText::STRIKETHROUGH_FLAG)
                            label->enableStrikethrough();
                        if (elmtText->_flags & RichElementText::URL_FLAG)
                            label->addComponent(ListenerComponent::create(label, elmtText->_url,
                                                                          std::bind(&RichText::openUrl, this, std::placeholders::_1)));
                        if (elmtText->_flags & RichElementText::OUTLINE_FLAG) {
                            label->enableOutline(Color4B(elmtText->_outlineColor), elmtText->_outlineSize);
                        }
                        if (elmtText->_flags & RichElementText::SHADOW_FLAG) {
                            label->enableShadow(Color4B(elmtText->_shadowColor),
                                                elmtText->_shadowOffset,
                                                elmtText->_shadowBlurRadius);
                        }
                        if (elmtText->_flags & RichElementText::GLOW_FLAG) {
                            label->enableGlow(Color4B(elmtText->_glowColor));
                        }
                        elementRenderer = label;
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        elementRenderer = Sprite::create(elmtImage->_filePath);
                        if (elementRenderer && (elmtImage->_height != -1 || elmtImage->_width != -1))
                        {
                            auto currentSize = elementRenderer->getContentSize();
                            if (elmtImage->_width != -1)
                                elementRenderer->setScaleX(elmtImage->_width / currentSize.width);
                            if (elmtImage->_height != -1)
                                elementRenderer->setScaleY(elmtImage->_height / currentSize.height);
                            elementRenderer->setContentSize(Size(currentSize.width * elementRenderer->getScaleX(),
                                                                 currentSize.height * elementRenderer->getScaleY()));
                            elementRenderer->addComponent(ListenerComponent::create(elementRenderer,
                                                                                    elmtImage->_url,
                                                                                    std::bind(&RichText::openUrl, this, std::placeholders::_1)));
                        }
                        break;
                    }
                    case RichElement::Type::CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        elementRenderer = elmtCustom->_customNode;
                        break;
                    }
                    case RichElement::Type::NEWLINE:
                    {
                        addNewLine();
                        break;
                    }
                    default:
                        break;
                }

                if (elementRenderer)
                {
                    elementRenderer->setColor(element->_color);
                    elementRenderer->setOpacity(element->_opacity);
                    pushToContainer(elementRenderer);
                }
            }
        }
        else
        {
            addNewLine();
            for (ssize_t i=0; i<_richElements.size(); i++)
            {
                RichElement* element = static_cast<RichElement*>(_richElements.at(i));
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        handleTextRenderer(elmtText->_text, elmtText->_fontName, elmtText->_fontSize, elmtText->_color,
                                           elmtText->_opacity, elmtText->_flags, elmtText->_url,
                                           elmtText->_outlineColor, elmtText->_outlineSize,
                                           elmtText->_shadowColor, elmtText->_shadowOffset, elmtText->_shadowBlurRadius,
                                           elmtText->_glowColor);
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        handleImageRenderer(elmtImage->_filePath, elmtImage->_color, elmtImage->_opacity, elmtImage->_width, elmtImage->_height, elmtImage->_url);
                        break;
                    }
                    case RichElement::Type::CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        handleCustomRenderer(elmtCustom->_customNode);
                        break;
                    }
                    case RichElement::Type::NEWLINE:
                    {
                        addNewLine();
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        formarRenderers();
        _formatTextDirty = false;
    }
}

static int getPrevWord(const std::string& text, int idx)
{
    // start from idx-1
    for (int i=idx-1; i>=0; --i)
    {
		if (!std::isalnum(text[i], std::locale()))
            return i;
    }
    return -1;
}

static bool isWrappable(const std::string& text)
{
    for (size_t i = 0; i < text.length(); ++i)
    {
        if (!std::isalnum(text[i], std::locale()))
            return true;
    }
    return false;
}

int RichText::findSplitPositionForWord(cocos2d::Label* label, const std::string& text)
{
    auto originalLeftSpaceWidth = _leftSpaceWidth + label->getContentSize().width;

    bool startingNewLine = (_customSize.width == originalLeftSpaceWidth);
    if (!isWrappable(text))
    {
        if (startingNewLine)
            return (int) text.length();
        return 0;
    }

    for(int idx = (int)text.size()-1; idx >=0; )
    {
        int newidx = getPrevWord(text, idx);
        if (newidx >=0)
        {
            idx = newidx;
            auto leftStr = Helper::getSubStringOfUTF8String(text, 0, idx);
            label->setString(leftStr);
            if (label->getContentSize().width <= originalLeftSpaceWidth)
                return idx;
        }
        else
        {
            if (startingNewLine)
                return idx;
            return 0;
        }
    }

    // no spaces... return the original label + size
    label->setString(text);
    return (int)text.size();
}


int RichText::findSplitPositionForChar(cocos2d::Label* label, const std::string& text)
{
    float textRendererWidth = label->getContentSize().width;

    float overstepPercent = (-_leftSpaceWidth) / textRendererWidth;
    std::string curText = text;
    size_t stringLength = StringUtils::getCharacterCountInUTF8String(text);

    // rough estimate
    int leftLength = stringLength * (1.0f - overstepPercent);

    // The adjustment of the new line position
    auto originalLeftSpaceWidth = _leftSpaceWidth + textRendererWidth;
    auto leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
    label->setString(leftStr);
    auto leftWidth = label->getContentSize().width;
    if (originalLeftSpaceWidth < leftWidth) {
        // Have protruding
        for (;;) {
            leftLength--;
            leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
            label->setString(leftStr);
            leftWidth = label->getContentSize().width;
            if (leftWidth <= originalLeftSpaceWidth) {
                break;
            }
            else if (leftLength <= 0) {
                break;
            }
        }
    }
    else if (leftWidth < originalLeftSpaceWidth) {
        // A wide margin
        for (;;) {
            leftLength++;
            leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
            label->setString(leftStr);
            leftWidth = label->getContentSize().width;
            if (originalLeftSpaceWidth < leftWidth) {
                leftLength--;
                break;
            }
            else if (static_cast<int>(stringLength) <= leftLength) {
                break;
            }
        }
    }

    if (leftLength < 0)
        leftLength = (int)text.size()-1;
    return leftLength;
}

void RichText::handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B &color,
                                  GLubyte opacity, uint32_t flags, const std::string& url,
                                  const Color3B& outlineColor, int outlineSize ,
                                  const Color3B& shadowColor, const cocos2d::Size& shadowOffset, int shadowBlurRadius,
                                  const Color3B& glowColor)
{
    auto fileExist = FileUtils::getInstance()->isFileExist(fontName);
    Label* textRenderer = nullptr;
    if (fileExist)
    {
        textRenderer = Label::createWithTTF(text, fontName, fontSize);
    } 
    else
    {
        textRenderer = Label::createWithSystemFont(text, fontName, fontSize);
    }
    if (flags & RichElementText::ITALICS_FLAG)
        textRenderer->enableItalics();
    if (flags & RichElementText::BOLD_FLAG)
        textRenderer->enableBold();
    if (flags & RichElementText::UNDERLINE_FLAG)
        textRenderer->enableUnderline();
    if (flags & RichElementText::STRIKETHROUGH_FLAG)
        textRenderer->enableStrikethrough();
    if (flags & RichElementText::URL_FLAG)
        textRenderer->addComponent(ListenerComponent::create(textRenderer,
                                                             url,
                                                             std::bind(&RichText::openUrl, this, std::placeholders::_1)));
    if (flags & RichElementText::OUTLINE_FLAG) {
        textRenderer->enableOutline(Color4B(outlineColor), outlineSize);
    }
    if (flags & RichElementText::SHADOW_FLAG) {
        textRenderer->enableShadow(Color4B(shadowColor), shadowOffset, shadowBlurRadius);
    }
    if (flags & RichElementText::GLOW_FLAG) {
        textRenderer->enableGlow(Color4B(glowColor));
    }

    float textRendererWidth = textRenderer->getContentSize().width;
    _leftSpaceWidth -= textRendererWidth;
    if (_leftSpaceWidth < 0.0f)
    {
        int leftLength = 0;
        if (static_cast<RichText::WrapMode>(_defaults.at(KEY_WRAP_MODE).asInt()) == WRAP_PER_WORD)
            leftLength = findSplitPositionForWord(textRenderer, text);
        else
            leftLength = findSplitPositionForChar(textRenderer, text);

        //The minimum cut length is 1, otherwise will cause the infinite loop.
//        if (0 == leftLength) leftLength = 1;
        std::string leftWords = Helper::getSubStringOfUTF8String(text, 0, leftLength);
        int rightStart = leftLength;
        if (std::isspace(text[rightStart], std::locale()))
            rightStart++;
        std::string cutWords = Helper::getSubStringOfUTF8String(text, rightStart, text.length() - leftLength);
        if (leftLength > 0)
        {
            Label* leftRenderer = nullptr;
            if (fileExist)
            {
                leftRenderer = Label::createWithTTF(Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), fontName, fontSize);
            }
            else
            {
                leftRenderer = Label::createWithSystemFont(Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), fontName, fontSize);
            }
            if (leftRenderer)
            {
                leftRenderer->setColor(color);
                leftRenderer->setOpacity(opacity);
                pushToContainer(leftRenderer);

                if (flags & RichElementText::ITALICS_FLAG)
                    leftRenderer->enableItalics();
                if (flags & RichElementText::BOLD_FLAG)
                    leftRenderer->enableBold();
                if (flags & RichElementText::UNDERLINE_FLAG)
                    leftRenderer->enableUnderline();
                if (flags & RichElementText::STRIKETHROUGH_FLAG)
                    leftRenderer->enableStrikethrough();
                if (flags & RichElementText::URL_FLAG)
                    leftRenderer->addComponent(ListenerComponent::create(leftRenderer,
                                                                         url,
                                                                         std::bind(&RichText::openUrl, this, std::placeholders::_1)));
                if (flags & RichElementText::OUTLINE_FLAG) {
                    leftRenderer->enableOutline(Color4B(outlineColor), outlineSize);
                }
                if (flags & RichElementText::SHADOW_FLAG) {
                    leftRenderer->enableShadow(Color4B(shadowColor), shadowOffset, shadowBlurRadius);
                }
                if (flags & RichElementText::GLOW_FLAG) {
                    leftRenderer->enableGlow(Color4B(glowColor));
                }
            }
        }

        addNewLine();
        handleTextRenderer(cutWords, fontName, fontSize, color, opacity, flags, url,
                           outlineColor, outlineSize,
                           shadowColor, shadowOffset, shadowBlurRadius,
                           glowColor);
    }
    else
    {
        textRenderer->setColor(color);
        textRenderer->setOpacity(opacity);
        pushToContainer(textRenderer);
    }
}
    
void RichText::handleImageRenderer(const std::string& filePath, const Color3B &color, GLubyte opacity, int width, int height, const std::string& url)
{
    Sprite* imageRenderer = Sprite::create(filePath);
    if (imageRenderer)
    {
        auto currentSize = imageRenderer->getContentSize();
        if (width != -1)
            imageRenderer->setScaleX(width / currentSize.width);
        if (height != -1)
            imageRenderer->setScaleY(height / currentSize.height);
        imageRenderer->setContentSize(Size(currentSize.width * imageRenderer->getScaleX(),
                                             currentSize.height * imageRenderer->getScaleY()));

        handleCustomRenderer(imageRenderer);
        imageRenderer->addComponent(ListenerComponent::create(imageRenderer,
                                                              url,
                                                              std::bind(&RichText::openUrl, this, std::placeholders::_1)));
    }
}

void RichText::handleCustomRenderer(cocos2d::Node *renderer)
{
    Size imgSize = renderer->getContentSize();
    _leftSpaceWidth -= imgSize.width;
    if (_leftSpaceWidth < 0.0f)
    {
        addNewLine();
        pushToContainer(renderer);
        _leftSpaceWidth -= imgSize.width;
    }
    else
    {
        pushToContainer(renderer);
    }
}
    
void RichText::addNewLine()
{
    _leftSpaceWidth = _customSize.width;
    _elementRenders.push_back(new Vector<Node*>());
}
    
void RichText::formarRenderers()
{
    if (_ignoreSize)
    {
        float newContentSizeWidth = 0.0f;
        float nextPosY = 0.0f;
        for (auto& element: _elementRenders)
        {
            Vector<Node*>* row = element;
            float nextPosX = 0.0f;
            float maxY = 0.0f;
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                l->setAnchorPoint(Vec2::ZERO);
                l->setPosition(nextPosX, nextPosY);
                this->addProtectedChild(l, 1);
                Size iSize = l->getContentSize();
                newContentSizeWidth += iSize.width;
                nextPosX += iSize.width;
                maxY = MAX(maxY, iSize.height);
            }
            nextPosY -= maxY;
        }
        this->setContentSize(Size(newContentSizeWidth, -nextPosY));
    }
    else
    {
        float newContentSizeHeight = 0.0f;
        float *maxHeights = new (std::nothrow) float[_elementRenders.size()];
        
        for (size_t i=0; i<_elementRenders.size(); i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float maxHeight = 0.0f;
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                maxHeight = MAX(l->getContentSize().height, maxHeight);
            }
            maxHeights[i] = maxHeight;
            newContentSizeHeight += maxHeights[i];
        }
        
        float nextPosY = _customSize.height;
        for (size_t i=0; i<_elementRenders.size(); i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float nextPosX = 0.0f;
            nextPosY -= (maxHeights[i] + _defaults.at(KEY_VERTICAL_SPACE).asFloat());
            
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                l->setAnchorPoint(Vec2::ZERO);
                l->setPosition(nextPosX, nextPosY);
                this->addProtectedChild(l, 1);
                nextPosX += l->getContentSize().width;
            }
        }
        delete [] maxHeights;
    }
    
    size_t length = _elementRenders.size();
    for (size_t i = 0; i<length; i++)
	{
        Vector<Node*>* l = _elementRenders[i];
        l->clear();
        delete l;
	}    
    _elementRenders.clear();
    
    if (_ignoreSize)
    {
        Size s = getVirtualRendererSize();
        this->setContentSize(s);
    }
    else
    {
        this->setContentSize(_customSize);
    }
    updateContentSizeWithTextureSize(_contentSize);
}
    
void RichText::adaptRenderers()
{
    this->formatText();
}
    
void RichText::pushToContainer(cocos2d::Node *renderer)
{
    if (_elementRenders.size() <= 0)
    {
        return;
    }
    _elementRenders[_elementRenders.size()-1]->pushBack(renderer);
}
    
void RichText::setVerticalSpace(float space)
{
    _defaults[KEY_VERTICAL_SPACE] = space;
}

void RichText::ignoreContentAdaptWithSize(bool ignore)
{
    if (_ignoreSize != ignore)
    {
        _formatTextDirty = true;
        Widget::ignoreContentAdaptWithSize(ignore);
    }
}
    
std::string RichText::getDescription() const
{
    return "RichText";
}
