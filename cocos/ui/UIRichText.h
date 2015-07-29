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

#ifndef __UIRICHTEXT_H__
#define __UIRICHTEXT_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"

NS_CC_BEGIN
/**
 * @addtogroup ui
 * @{
 */

namespace ui {
    
/**
 *@brief Rich text element base class.
 * It defines the basic common properties for all rich text element.
 */
class CC_GUI_DLL RichElement : public Ref
{
public:
    /**
     *@brief Rich element type.
     */
    enum class Type
    {
        TEXT,
        IMAGE,
        CUSTOM
    };
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     */
    RichElement(){};
    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichElement(){};

    
    /**
     * @brief Initialize a rich element with different arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in @see `Color3B`.
     * @param opacity A opacity value in `GLubyte`.
     * @return True if initialize success, false otherwise.
     */
    bool init(int tag, const Color3B& color, GLubyte opacity);
protected:
    Type _type;
    int _tag;
    Color3B _color;
    GLubyte _opacity;
    friend class RichText;
};
    
/**
 *@brief Rich element for displaying text.
 */
class CC_GUI_DLL RichElementText : public RichElement
{
public:
    
    /**
     *@brief Default constructor.
     * @js ctor
     * @lua new
     */
    RichElementText(){_type = Type::TEXT;};

    
    /**
     *@brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichElementText(){};
    
    /**
     * @brief Initialize a RichElementText with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param text Content string.
     * @param fontName Content font name.
     * @param fontSize Content font size.
     * @return True if initialize scucess, false otherwise.
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);

    
    /**
     * @brief Create a RichElementText with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param text Content string.
     * @param fontName Content font name.
     * @param fontSize Content font size.
     * @return RichElementText instance.
     */
    static RichElementText* create(int tag, const Color3B& color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize);
protected:
    std::string _text;
    std::string _fontName;
    float _fontSize;
    friend class RichText;
    
};
    
/**
 *@brief Rich element for displaying images.
 */
class CC_GUI_DLL RichElementImage : public RichElement
{
public:
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     *
     */
    RichElementImage(){_type = Type::IMAGE;};

    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichElementImage(){};

    
    /**
     * @brief Initialize a RichElementImage with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param filePath A image file name.
     * @return True if initialize success, false otherwise.
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);

    
    /**
     * @brief Create a RichElementImage with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param filePath A image file name.
     * @return A RichElementImage instance.
     */
    static RichElementImage* create(int tag, const Color3B& color, GLubyte opacity, const std::string& filePath);
protected:
    std::string _filePath;
    Rect _textureRect;
    int _textureType;
    friend class RichText;
};
    
/**
 *@brief Rich element for displaying custom node type.
 */
class CC_GUI_DLL RichElementCustomNode : public RichElement
{
public:
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     */
    RichElementCustomNode(){_type = Type::CUSTOM;};

    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichElementCustomNode(){CC_SAFE_RELEASE(_customNode);};

    
    /**
     * @brief Initialize a RichElementCustomNode with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param customNode A custom node pointer.
     * @return True if initialize success, false otherwise.
     */
    bool init(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
    
    /**
     * @brief Create a RichElementCustomNode with various arguments.
     *
     * @param tag A integer tag value.
     * @param color A color in Color3B.
     * @param opacity A opacity in GLubyte.
     * @param customNode A custom node pointer.
     * @return A RichElementCustomNode instance.
     */
    static RichElementCustomNode* create(int tag, const Color3B& color, GLubyte opacity, Node* customNode);
protected:
    Node* _customNode;
    friend class RichText;
};
    
/**
 *@brief A container for displaying various RichElements.
 * We could use it to display texts with images easily.
 */
class CC_GUI_DLL RichText : public Widget
{
public:
    
    /**
     * @brief Default constructor.
     * @js ctor
     * @lua new
     */
    RichText();
    
    /**
     * @brief Default destructor.
     * @js NA
     * @lua NA
     */
    virtual ~RichText();
    
    /**
     * @brief Create a empty RichText.
     *
     * @return RichText instance.
     */
    static RichText* create();
    
    /**
     * @brief Insert a RichElement at a given index.
     *
     * @param element A RichElement type.
     * @param index A given index.
     */
    void insertElement(RichElement* element, int index);
    
    /**
     * @brief Add a RichElement at the end of RichText.
     *
     * @param element A RichElement instance.
     */
    void pushBackElement(RichElement* element);
    
    /**
     * @brief Remove a RichElement at a given index.
     *
     * @param index A integer index value.
     */
    void removeElement(int index);
    
    /**
     * @brief Remove specific RichElement.
     *
     * @param element A RichElement type.
     */
    void removeElement(RichElement* element);
    
    /**
     * @brief Set vertical space between each RichElement.
     *
     * @param space Point in float.
     */
    void setVerticalSpace(float space);
    
    /**
     * @brief Rearrange all RichElement in the RichText.
     * It's usually called internally.
     */
    void formatText();

    //override functions.
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual std::string getDescription() const override;
    
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    
protected:
    virtual void adaptRenderers() override;

    virtual void initRenderer() override;
    void pushToContainer(Node* renderer);
    void handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B& color, GLubyte opacity);
    void handleImageRenderer(const std::string& fileParh, const Color3B& color, GLubyte opacity);
    void handleCustomRenderer(Node* renderer);
    void formarRenderers();
    void addNewLine();
protected:
    bool _formatTextDirty;
    Vector<RichElement*> _richElements;
    std::vector<Vector<Node*>*> _elementRenders;
    float _leftSpaceWidth;
    float _verticalSpace;
};
    
}

// end of ui group
/// @}
NS_CC_END

#endif /* defined(__UIRichText__) */
