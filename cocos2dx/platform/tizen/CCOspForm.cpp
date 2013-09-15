/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2013 Lee, Jae-Hong

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

#include "CCOspForm.h"
#include "CCDirector.h"
#include "CCEGLView.h"
#include "text_input_node/CCIMEDispatcher.h"
#include <FBase.h>
#include <FText.h>

USING_NS_CC;
using namespace Tizen::Base;
using namespace Tizen::Text;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

OspForm::OspForm()
    : __pKeypad(null)
    , _editTextCallback(null)
    , _ctx(null)
{
}

OspForm::~OspForm()
{
}

result
OspForm::OnInitializing(void)
{
    AddTouchEventListener(*this);
    SetMultipointTouchEnabled(true);

    return E_SUCCESS;
}

result
OspForm::OnTerminating(void)
{
    result r = E_SUCCESS;

    if (__pKeypad)
        __pKeypad->Destroy();

    Director::getInstance()->getAccelerometer()->stopSensor();

    return r;
}

void
OspForm:: OnTouchDoublePressed(const Control& source, const  Tizen::Graphics::Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
OspForm:: OnTouchFocusIn(const Control& source, const  Tizen::Graphics::Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
OspForm::OnTouchFocusOut(const Control& source, const  Tizen::Graphics::Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
OspForm::OnTouchLongPressed(const Control& source, const  Tizen::Graphics::Point& currentPosition, const TouchEventInfo& touchInfo)
{
}

void
OspForm::OnTouchMoved(const Control& source, const  Tizen::Graphics::Point& currentPosition, const TouchEventInfo& touchInfo)
{
    int id = touchInfo.GetPointId();
    float x = currentPosition.x;
    float y = currentPosition.y;
    Director::getInstance()->getOpenGLView()->handleTouchesMove(1, &id, &x, &y);
}

void
OspForm::OnTouchPressed(const Control& source, const  Tizen::Graphics::Point& currentPosition, const TouchEventInfo& touchInfo)
{
    int id = touchInfo.GetPointId();
    float x = currentPosition.x;
    float y = currentPosition.y;
    Director::getInstance()->getOpenGLView()->handleTouchesBegin(1, &id, &x, &y);
}

void
OspForm::OnTouchReleased(const Control& source, const  Tizen::Graphics::Point& currentPosition, const TouchEventInfo& touchInfo)
{
    int id = touchInfo.GetPointId();
    float x = currentPosition.x;
    float y = currentPosition.y;
    Director::getInstance()->getOpenGLView()->handleTouchesEnd(1, &id, &x, &y);
}

void OspForm::OnTextValueChanged(const Tizen::Ui::Control& source)
{
    Tizen::Base::String text = __pKeypad->GetText();
    Utf8Encoding utf8;
    ByteBuffer* buffer = utf8.GetBytesN(text);
    const char* pText = "";
    if (buffer)
        pText = (const char *)buffer->GetPointer();

    if (_editTextCallback)
    {
        _editTextCallback(pText, _ctx);
    }
    else
    {
        const char* pContentText = IMEDispatcher::sharedDispatcher()->getContentText();

        for (unsigned int i = strlen(pContentText); i > 0; i--)
        {
            IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
        }

        std::string text("");
        if (pText != null)
        {
            text = pText;
            if (text.compare("") == 0)
            {
                text = "\n";
            }

            if (text.at(text.length() - 1) != '\n')
            {
                text += '\n';
            }
        }

        IMEDispatcher::sharedDispatcher()->dispatchInsertText(text.c_str(), text.length());
    }

    if (buffer)
        delete buffer;
}

void OspForm::OnTextValueChangeCanceled(const Tizen::Ui::Control& source)
{
    if (_editTextCallback)
    {
        _editTextCallback("", _ctx);
    }
    else
    {
        const char* pContentText = IMEDispatcher::sharedDispatcher()->getContentText();

        for (unsigned int i = strlen(pContentText); i > 0; i--)
        {
            IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
        }
    }
}

void
OspForm::ShowKeypad(const char* pMessage, KeypadStyle keypadStyle, KeypadInputModeCategory keypadCategory, bool bSingleLineEnabled, bool bTextPrediction, int nMaxLength, EditTextCallback pfEditTextCallback, void* pCtx)
{
    _editTextCallback = pfEditTextCallback;
    _ctx = pCtx;

    if (__pKeypad)
    {
        __pKeypad->RemoveTextEventListener(*this);
        __pKeypad->Destroy();
        __pKeypad = null;
    }

    if (nMaxLength > 100)
        nMaxLength = 100;
    else if (nMaxLength == -1)
        nMaxLength = 100;

    __pKeypad = new Keypad();
    __pKeypad->Construct(keypadStyle, keypadCategory, nMaxLength);
    __pKeypad->AddTextEventListener(*this);

    __pKeypad->SetTextPredictionEnabled(bTextPrediction);
    __pKeypad->SetSingleLineEnabled(bSingleLineEnabled);
    __pKeypad->SetText(Tizen::Base::String(pMessage));
    __pKeypad->SetShowState(true);
    __pKeypad->Show();
}

void
OspForm::ShowKeypad()
{
    ShowKeypad(
        IMEDispatcher::sharedDispatcher()->getContentText(),
        KEYPAD_STYLE_NORMAL,
        KEYPAD_MODE_ALPHA,
        true,
        true,
        100,
        null,
        null);
}

void
OspForm::CloseKeypad()
{
    __pKeypad->SetShowState(false);
    Invalidate(true);
}

