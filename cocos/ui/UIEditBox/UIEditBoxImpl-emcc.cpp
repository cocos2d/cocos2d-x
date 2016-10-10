#include "UIEditBoxImpl-emcc.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN)

#include "UIEditBox.h"
#include "base/CCDirector.h"
#include "2d/CCLabel.h"

#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerKeyboard.h"

#include <emscripten/emscripten.h>

NS_CC_BEGIN

extern "C"
{
    int UIEditBox_init(bool isMultiLine);
    void UIEditBox_setContentSize(int id, int x, int y, int width, int height);
    void UIEditBox_setColor(int id, int r, int g, int b);
    void UIEditBox_setPlaceholderColor(int id, int r, int g, int b);
    void UIEditBox_setFont(int id, const char* fontName, int size);
    void UIEditBox_setText(int id, const char* str);
    void UIEditBox_setPlaceholder(int id, const char* str);
    void UIEditBox_setInputType(int id, int type);
    void UIEditBox_setMaxLength(int id, int length);
    void UIEditBox_setVisible(int id, bool visible);
    const char* UIEditBox_getText(int id);
    bool UIEditBox_isFocused(int id);
    void UIEditBox_close(int id);
    
    typedef void (*on_enter_callback)(void *userData);
    void UIEditBox_setOnEnterCalback(int id, void *userData, on_enter_callback callback);
}

namespace ui {

EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
    return new EditBoxImplEmcc(pEditBox);
}

EditBoxImplEmcc::EditBoxImplEmcc(EditBox* pEditText)
: EditBoxImpl(pEditText)
, _anchorPoint(Vec2(0.5f, 0.5f))
{
}

EditBoxImplEmcc::~EditBoxImplEmcc()
{
}
    
bool EditBoxImplEmcc::initWithSize(const Size& size)
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    float factor = cocos2d::Director::getInstance()->getContentScaleFactor();

    _contentSize = size;
    _isDirty = true;
    _fontSize = ((_contentSize.height * glview->getScaleY()) / factor) * 2 / 3;
    _color = Color4B(255, 255, 255, 255);
    _placeholderColor = Color4B(255, 255, 255, 255);
    _inputFlag = EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS;
    _inputMode = EditBox::InputMode::ANY;
    return true;
}
    
void EditBoxImplEmcc::setFont(const char* pFontName, int fontSize)
{
    if (fontSize == -1)
    {
        fontSize = _contentSize.height * 2 / 3;
    }
    else
    {
        auto glview = cocos2d::Director::getInstance()->getOpenGLView();
        float scaleFactor = glview->getScaleX();

        fontSize = fontSize * scaleFactor;
    }
    
    std::string fontName(pFontName);
    size_t pos = fontName.rfind(".");
    if (pos != std::string::npos)
        fontName = fontName.substr(0, pos);
    
    pos = fontName.rfind("/");
    if (pos != std::string::npos)
        fontName = fontName.substr(pos + 1, fontName.length() - (pos + 1));
    _fontName = fontName;
    _fontSize = fontSize;
    _isDirty = true;
}

void EditBoxImplEmcc::onEnterCallback(void *userData)
{
    EditBoxImplEmcc *editBoxEmcc = static_cast<EditBoxImplEmcc*>(userData);
    
    if (editBoxEmcc->_delegate)
    {
        editBoxEmcc->_delegate->editBoxReturn(editBoxEmcc->_editBox);
        editBoxEmcc->_delegate->editBoxEditingDidEnd(editBoxEmcc->_editBox);
    }
}
    
void EditBoxImplEmcc::setFontColor(const Color4B& color)
{
    _color = color;
    _isDirty = true;
}

void EditBoxImplEmcc::setPlaceholderFont(const char* pFontName, int fontSize)
{
    //TODO::
}

void EditBoxImplEmcc::setPlaceholderFontColor(const Color4B& color)
{
    _placeholderColor = color;
    _isDirty = true;
}

void EditBoxImplEmcc::setInputMode(EditBox::InputMode inputMode)
{
    _inputMode = inputMode;
    _isDirty = true;
}

void EditBoxImplEmcc::setInputFlag(EditBox::InputFlag inputFlag)
{
    _inputFlag = inputFlag;
    _isDirty = true;
}
    
void EditBoxImplEmcc::setMaxLength(int maxLength)
{
    _maxTextLength = maxLength;
    _isDirty = true;
}

int EditBoxImplEmcc::getMaxLength()
{
    return _maxTextLength;
}

void EditBoxImplEmcc::setReturnType(EditBox::KeyboardReturnType returnType)
{
}
    
bool EditBoxImplEmcc::isEditing()
{
    return UIEditBox_isFocused(_id);
}
    
void EditBoxImplEmcc::setText(const char* pText)
{
    _text = pText;
    UIEditBox_setText(_id, pText);
}

const char* EditBoxImplEmcc::getText(void)
{
    const char *textPtr = UIEditBox_getText(_id);
    _text = textPtr ? textPtr : "";
    free((void*)textPtr);
    return _text.c_str();
}

void EditBoxImplEmcc::setPlaceHolder(const char* pText)
{
    _placeholderText = pText;
    _isDirty = true;
}

void EditBoxImplEmcc::setPosition(const Vec2& pos)
{
    _position = pos;
    adjustTextFieldPositionAndSize();
}

void EditBoxImplEmcc::setVisible(bool visible)
{
    UIEditBox_setVisible(_id, visible);
}

void EditBoxImplEmcc::setContentSize(const Size& size)
{
    _contentSize = size;
    adjustTextFieldPositionAndSize();
}
    
void EditBoxImplEmcc::setAnchorPoint(const Vec2& anchorPoint)
{
    _anchorPoint = anchorPoint;
    setPosition(_position);
}
    
void EditBoxImplEmcc::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (_isDirty)
    {
        _isDirty = false;
        
        if (_isCreate)
        {
            _isCreate = false;
            _text = getText();
            UIEditBox_close(_id);
        }
        
        createFromJS();
    }
}
    
void EditBoxImplEmcc::doAnimationWhenKeyboardMove(float duration, float distance)
{
}
    
void EditBoxImplEmcc::openKeyboard()
{
}

void EditBoxImplEmcc::closeKeyboard()
{
    UIEditBox_close(_id);
}

void EditBoxImplEmcc::updatePosition(float dt)
{
    adjustTextFieldPositionAndSize();
}
    
void EditBoxImplEmcc::onEnter(void)
{
    adjustTextFieldPositionAndSize();
}

void EditBoxImplEmcc::createFromJS()
{
    _isCreate = true;
    bool isMultiLine = _inputMode == EditBox::InputMode::ANY;
    _id = UIEditBox_init(isMultiLine);
    UIEditBox_setColor(_id, _color.r, _color.g, _color.b);
    UIEditBox_setFont(_id, _fontName.c_str(), _fontSize);
    UIEditBox_setMaxLength(_id, _maxTextLength);
    UIEditBox_setPlaceholderColor(_id, _placeholderColor.r, _placeholderColor.g, _placeholderColor.b);
    UIEditBox_setOnEnterCalback(_id, static_cast<void*>(this), &EditBoxImplEmcc::onEnterCallback);
    
    if (!_text.empty())
        UIEditBox_setText(_id, _text.c_str());
    
    if (!_placeholderText.empty())
        UIEditBox_setPlaceholder(_id, _placeholderText.c_str());
    
    switch (_inputFlag)
    {
        case EditBox::InputFlag::PASSWORD:
            UIEditBox_setInputType(_id, 1);
            break;
        case EditBox::InputFlag::INITIAL_CAPS_WORD:
            UIEditBox_setInputType(_id, 2);
            break;
        case EditBox::InputFlag::INITIAL_CAPS_SENTENCE:
            CCLOG("INITIAL_CAPS_SENTENCE not implemented");
            break;
        case EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS:
            UIEditBox_setInputType(_id, 3);
            break;
        case EditBox::InputFlag::SENSITIVE:
            CCLOG("SENSITIVE not implemented");
            break;
        default:
            break;
    }
    
    adjustTextFieldPositionAndSize();
}

void EditBoxImplEmcc::adjustTextFieldPositionAndSize()
{
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    float factor = cocos2d::Director::getInstance()->getContentScaleFactor();
    const Size &winSize = cocos2d::Director::getInstance()->getWinSize();
    
    Size contentSize = _editBox->getContentSize();
    Rect rect = Rect(0, 0, contentSize.width, contentSize.height);
    rect = RectApplyAffineTransform(rect, _editBox->getNodeToWorldAffineTransform());

    Vec2 designCoord = Vec2(rect.origin.x, rect.origin.y + rect.size.height);
    Vec2 visiblePos = Vec2(designCoord.x * glview->getScaleX(), designCoord.y * glview->getScaleY());
    Vec2 screenGLPos = visiblePos + glview->getViewPortRect().origin;

    rect.size = Size(rect.size.width * glview->getScaleX(), rect.size.height * glview->getScaleY());
    float newPositionY = (winSize.height * glview->getScaleX()) - screenGLPos.y;
    UIEditBox_setContentSize(_id, screenGLPos.x, newPositionY, rect.size.width, rect.size.height);
}
}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) */


 
