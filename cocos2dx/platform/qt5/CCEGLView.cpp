/**
 *
 * Cocos2D-X Qt 5 Platform
 *
 * Copyright (C) 2013 Jolla Ltd.
 * Contact: Thomas Perl <thomas.perl@jollamobile.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **/


#include "CCEGLView.h"
#include "CCGL.h"

#include "ccMacros.h"
#include "CCDirector.h"

#include "event_dispatcher/CCTouch.h"
#include "event_dispatcher/CCEventDispatcher.h"
#include "event_dispatcher/CCEventKeyboard.h"
#include "text_input_node/CCIMEDispatcher.h"

#include <QGuiApplication>
#include <QWindow>

#include <QOpenGLContext>
#include <QEvent>
#include <QTouchEvent>
#include <QKeyEvent>
#include <QMouseEvent>

#include <QInputMethod>

NS_CC_BEGIN

class Cocos2DQt5OpenGLIntegration : public QWindow {
    public:
        Cocos2DQt5OpenGLIntegration(EGLView *view, int width, int height);
        ~Cocos2DQt5OpenGLIntegration();

        void touchEvent(QTouchEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        void keyReleaseEvent(QKeyEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        bool event(QEvent *event) override;

        void swapBuffers();

    private:
        static const int MOUSE_TOUCH_ID = 0;
        static const int PITCH_FIRST_TOUCH_ID = 0;
        static const int PITCH_SECOND_TOUCH_ID = 1;

        enum class MouseState {
            Default,
            LeftPressed,
            RightPressed
        };

        EventKeyboard::KeyCode keycodeForQtEvent(QKeyEvent *event);

        EGLView *m_egl_view;
        QOpenGLContext *m_context;
        MouseState m_mouseState;
        QPointF m_pitchStartPos;
};

Cocos2DQt5OpenGLIntegration::Cocos2DQt5OpenGLIntegration(EGLView *view, int width, int height)
    : m_egl_view(view)
    , m_context(NULL)
    , m_mouseState(MouseState::Default)
{
    setSurfaceType(QSurface::OpenGLSurface);
    resize(width, height);
    //showFullScreen();
    show();

    m_context = new QOpenGLContext(this);
    m_context->create();
    m_context->makeCurrent(this);
}

Cocos2DQt5OpenGLIntegration::~Cocos2DQt5OpenGLIntegration()
{
    delete m_context;
}

void
Cocos2DQt5OpenGLIntegration::touchEvent(QTouchEvent *event)
{
    foreach (QTouchEvent::TouchPoint point, event->touchPoints()) {
        int id = point.id();
        QPointF pos = point.pos();
        float x = pos.x();
        float y = pos.y();
        Qt::TouchPointState state = point.state();

        switch (state) {
            case Qt::TouchPointPressed:
                m_egl_view->handleTouchesBegin(1, &id, &x, &y);
                break;
            case Qt::TouchPointMoved:
                m_egl_view->handleTouchesMove(1, &id, &x, &y);
                break;
            case Qt::TouchPointStationary:
                // Do nothing
                break;
            case Qt::TouchPointReleased:
                m_egl_view->handleTouchesEnd(1, &id, &x, &y);
                break;
            default:
                // Do nothing
                break;
        }
    }
}

void Cocos2DQt5OpenGLIntegration::keyPressEvent(QKeyEvent *event)
{
    EventKeyboard::KeyCode code = keycodeForQtEvent(event);
    if (code != EventKeyboard::KeyCode::KEY_NONE) {
        EventKeyboard event(code, /*isPressed*/ true);
        EventDispatcher::getInstance()->dispatchEvent(&event);
    } else {
        CCLOG("Unknown key pressed, Qt key code: %d.", event->key());
    }
}

void Cocos2DQt5OpenGLIntegration::keyReleaseEvent(QKeyEvent *event)
{
    EventKeyboard::KeyCode code = keycodeForQtEvent(event);
    if (code != EventKeyboard::KeyCode::KEY_NONE) {
        EventKeyboard event(code, /*isPressed*/ false);
        EventDispatcher::getInstance()->dispatchEvent(&event);
    } else {
        CCLOG("Unknown key released, Qt key code: %d.", event->key());
    }
}

void Cocos2DQt5OpenGLIntegration::mouseMoveEvent(QMouseEvent *event)
{
    if (m_mouseState == MouseState::LeftPressed) {
        const QPointF pos = event->localPos();
        int id = MOUSE_TOUCH_ID;
        float x = pos.x();
        float y = pos.y();
        m_egl_view->handleTouchesMove(1, &id, &x, &y);
    } else if (m_mouseState == MouseState::RightPressed) {
        const QPointF pos1 = event->localPos();
        const QPointF pos2 = 2.0f * m_pitchStartPos - pos1;
        int id[2] = {PITCH_FIRST_TOUCH_ID, PITCH_SECOND_TOUCH_ID};
        float x[2] = {(float)pos1.x(), (float)pos2.x()};
        float y[2] = {(float)pos1.y(), (float)pos2.y()};
        m_egl_view->handleTouchesMove(2, id, x, y);
    }
}

//  Mouse used to touch and Android/BlackBerry keypad emulation.
//  - When left button pressed, mouse emulates touches.
//  - When right button pressed, mouse emulates pitch gesture.
//  - When back button pressed, mouse emulates keypad back button.
void Cocos2DQt5OpenGLIntegration::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::BackButton: {
        EventKeyboard event(EventKeyboard::KeyCode::KEY_BACKSPACE, /*isPressed*/ true);
        EventDispatcher::getInstance()->dispatchEvent(&event);
    }
        break;
    case Qt::LeftButton:
        if (m_mouseState == MouseState::Default) {
            m_mouseState = MouseState::LeftPressed;
            const QPointF pos = event->localPos();
            int id = MOUSE_TOUCH_ID;
            float x = pos.x();
            float y = pos.y();
            m_egl_view->handleTouchesBegin(1, &id, &x, &y);
        }
        break;
    case Qt::RightButton:
        if (m_mouseState == MouseState::Default) {
            m_mouseState = MouseState::RightPressed;
            const QPointF pos = event->localPos();
            m_pitchStartPos = pos;
            int id[2] = {PITCH_FIRST_TOUCH_ID, PITCH_SECOND_TOUCH_ID};
            float x[2] = {(float)pos.x(), (float)pos.x()};
            float y[2] = {(float)pos.y(), (float)pos.y()};
            m_egl_view->handleTouchesBegin(2, id, x, y);
        }
        break;
    default:
        break;
    }
}

void Cocos2DQt5OpenGLIntegration::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::BackButton: {
        EventKeyboard event(EventKeyboard::KeyCode::KEY_BACKSPACE, /*isPressed*/ false);
        EventDispatcher::getInstance()->dispatchEvent(&event);
    }
        break;
    case Qt::LeftButton:
        if (m_mouseState == MouseState::LeftPressed) {
            m_mouseState = MouseState::Default;
            const QPointF pos = event->localPos();
            int id = MOUSE_TOUCH_ID;
            float x = pos.x();
            float y = pos.y();
            m_egl_view->handleTouchesEnd(1, &id, &x, &y);
        }
        break;
    case Qt::RightButton:
        if (m_mouseState == MouseState::RightPressed) {
            m_mouseState = MouseState::Default;
            const QPointF pos1 = event->localPos();
            const QPointF pos2 = 2.0f * m_pitchStartPos - pos1;
            int id[2] = {PITCH_FIRST_TOUCH_ID, PITCH_SECOND_TOUCH_ID};
            float x[2] = {(float)pos1.x(), (float)pos2.x()};
            float y[2] = {(float)pos1.y(), (float)pos2.y()};
            m_egl_view->handleTouchesEnd(2, id, x, y);
        }
        break;
    default:
        break;
    }
}

bool Cocos2DQt5OpenGLIntegration::event(QEvent *event)
{
    if (event->type() == QEvent::Close) {
        Director::getInstance()->end();
    }

    return QWindow::event(event);
}

void Cocos2DQt5OpenGLIntegration::swapBuffers()
{
    m_context->swapBuffers(this);
    m_context->makeCurrent(this);
}

#define CC_LETTER_CASE(letter) \
    case Qt::Key_##letter: { \
        if (event->text() == #letter) \
            return EventKeyboard::KeyCode::KEY_CAPITAL_##letter; \
        return EventKeyboard::KeyCode::KEY_##letter; \
    } break

// Not handled: KEY_BREAK, KEY_GRAVE, KEY_EURO, KEY_MIDDLE_DOT, KEY_SEARCH
EventKeyboard::KeyCode Cocos2DQt5OpenGLIntegration::keycodeForQtEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Pause: return EventKeyboard::KeyCode::KEY_PAUSE;
    case Qt::Key_ScrollLock: return EventKeyboard::KeyCode::KEY_SCROLL_LOCK;
    case Qt::Key_Print: return EventKeyboard::KeyCode::KEY_PRINT;
    case Qt::Key_SysReq: return EventKeyboard::KeyCode::KEY_SYSREQ;
    case Qt::Key_Escape: return EventKeyboard::KeyCode::KEY_ESCAPE;
    case Qt::Key_Backspace: return EventKeyboard::KeyCode::KEY_BACKSPACE;
    case Qt::Key_Tab: return EventKeyboard::KeyCode::KEY_TAB;
    case Qt::Key_Backtab: return EventKeyboard::KeyCode::KEY_BACK_TAB;
    case Qt::Key_Return: return EventKeyboard::KeyCode::KEY_RETURN;
    case Qt::Key_CapsLock: return EventKeyboard::KeyCode::KEY_CAPS_LOCK;
    case Qt::Key_Shift: return EventKeyboard::KeyCode::KEY_SHIFT;
    case Qt::Key_Control: return EventKeyboard::KeyCode::KEY_CTRL;
    case Qt::Key_Alt: return EventKeyboard::KeyCode::KEY_ALT;
    case Qt::Key_Menu: return EventKeyboard::KeyCode::KEY_MENU;
    case Qt::Key_Hyper_L: return EventKeyboard::KeyCode::KEY_HYPER;
    case Qt::Key_Hyper_R: return EventKeyboard::KeyCode::KEY_HYPER;
    case Qt::Key_Insert: return EventKeyboard::KeyCode::KEY_INSERT;
    case Qt::Key_Home: return EventKeyboard::KeyCode::KEY_HOME;
    case Qt::Key_PageUp: return EventKeyboard::KeyCode::KEY_PG_UP;
    case Qt::Key_Delete: return EventKeyboard::KeyCode::KEY_DELETE;
    case Qt::Key_End: return EventKeyboard::KeyCode::KEY_END;
    case Qt::Key_PageDown: return EventKeyboard::KeyCode::KEY_PG_DOWN;
    case Qt::Key_Left: return EventKeyboard::KeyCode::KEY_LEFT_ARROW;
    case Qt::Key_Right: return EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
    case Qt::Key_Up: return EventKeyboard::KeyCode::KEY_UP_ARROW;
    case Qt::Key_Down: return EventKeyboard::KeyCode::KEY_DOWN_ARROW;
    case Qt::Key_NumLock: return EventKeyboard::KeyCode::KEY_NUM_LOCK;
    case Qt::Key_multiply: return EventKeyboard::KeyCode::KEY_KP_MULTIPLY;
    case Qt::Key_division: return EventKeyboard::KeyCode::KEY_KP_DIVIDE;
    case Qt::Key_Enter: return EventKeyboard::KeyCode::KEY_KP_ENTER;
    case Qt::Key_F1: return EventKeyboard::KeyCode::KEY_F1;
    case Qt::Key_F2: return EventKeyboard::KeyCode::KEY_F2;
    case Qt::Key_F3: return EventKeyboard::KeyCode::KEY_F3;
    case Qt::Key_F4: return EventKeyboard::KeyCode::KEY_F4;
    case Qt::Key_F5: return EventKeyboard::KeyCode::KEY_F5;
    case Qt::Key_F6: return EventKeyboard::KeyCode::KEY_F6;
    case Qt::Key_F7: return EventKeyboard::KeyCode::KEY_F7;
    case Qt::Key_F8: return EventKeyboard::KeyCode::KEY_F8;
    case Qt::Key_F9: return EventKeyboard::KeyCode::KEY_F9;
    case Qt::Key_F10: return EventKeyboard::KeyCode::KEY_F10;
    case Qt::Key_F11: return EventKeyboard::KeyCode::KEY_F11;
    case Qt::Key_F12: return EventKeyboard::KeyCode::KEY_F12;
    case Qt::Key_Space: return EventKeyboard::KeyCode::KEY_SPACE;
    case Qt::Key_Exclam: return EventKeyboard::KeyCode::KEY_EXCLAM;
    case Qt::Key_QuoteDbl: return EventKeyboard::KeyCode::KEY_QUOTE;
    case Qt::Key_NumberSign: return EventKeyboard::KeyCode::KEY_NUMBER;
    case Qt::Key_Dollar: return EventKeyboard::KeyCode::KEY_DOLLAR;
    case Qt::Key_Percent: return EventKeyboard::KeyCode::KEY_PERCENT;
    case Qt::Key_AsciiCircum: return EventKeyboard::KeyCode::KEY_CIRCUMFLEX;
    case Qt::Key_Ampersand: return EventKeyboard::KeyCode::KEY_AMPERSAND;
    case Qt::Key_Apostrophe: return EventKeyboard::KeyCode::KEY_APOSTROPHE;
    case Qt::Key_ParenLeft: return EventKeyboard::KeyCode::KEY_LEFT_PARENTHESIS;
    case Qt::Key_ParenRight: return EventKeyboard::KeyCode::KEY_RIGHT_PARENTHESIS;
    case Qt::Key_Asterisk: return EventKeyboard::KeyCode::KEY_ASTERISK;
    case Qt::Key_Plus: return EventKeyboard::KeyCode::KEY_PLUS;
    case Qt::Key_Comma: return EventKeyboard::KeyCode::KEY_COMMA;
    case Qt::Key_Minus: return EventKeyboard::KeyCode::KEY_MINUS;
    case Qt::Key_Period: return EventKeyboard::KeyCode::KEY_PERIOD;
    case Qt::Key_Slash: return EventKeyboard::KeyCode::KEY_SLASH;
    case Qt::Key_0: return EventKeyboard::KeyCode::KEY_0;
    case Qt::Key_1: return EventKeyboard::KeyCode::KEY_1;
    case Qt::Key_2: return EventKeyboard::KeyCode::KEY_2;
    case Qt::Key_3: return EventKeyboard::KeyCode::KEY_3;
    case Qt::Key_4: return EventKeyboard::KeyCode::KEY_4;
    case Qt::Key_5: return EventKeyboard::KeyCode::KEY_5;
    case Qt::Key_6: return EventKeyboard::KeyCode::KEY_6;
    case Qt::Key_7: return EventKeyboard::KeyCode::KEY_7;
    case Qt::Key_8: return EventKeyboard::KeyCode::KEY_8;
    case Qt::Key_9: return EventKeyboard::KeyCode::KEY_9;
    case Qt::Key_Colon: return EventKeyboard::KeyCode::KEY_COLON;
    case Qt::Key_Semicolon: return EventKeyboard::KeyCode::KEY_SEMICOLON;
    case Qt::Key_Less: return EventKeyboard::KeyCode::KEY_LESS_THAN;
    case Qt::Key_Equal: return EventKeyboard::KeyCode::KEY_EQUAL;
    case Qt::Key_Greater: return EventKeyboard::KeyCode::KEY_GREATER_THAN;
    case Qt::Key_Question: return EventKeyboard::KeyCode::KEY_QUESTION;
    case Qt::Key_At: return EventKeyboard::KeyCode::KEY_AT;
    case Qt::Key_BracketLeft: return EventKeyboard::KeyCode::KEY_LEFT_BRACKET;
    case Qt::Key_Backslash: return EventKeyboard::KeyCode::KEY_BACK_SLASH;
    case Qt::Key_BracketRight: return EventKeyboard::KeyCode::KEY_RIGHT_BRACKET;
    case Qt::Key_Underscore: return EventKeyboard::KeyCode::KEY_UNDERSCORE;
    case Qt::Key_BraceLeft: return EventKeyboard::KeyCode::KEY_LEFT_BRACE;
    case Qt::Key_Bar: return EventKeyboard::KeyCode::KEY_BAR;
    case Qt::Key_BraceRight: return EventKeyboard::KeyCode::KEY_RIGHT_BRACE;
    case Qt::Key_AsciiTilde: return EventKeyboard::KeyCode::KEY_TILDE;
    case Qt::Key_sterling: return EventKeyboard::KeyCode::KEY_POUND;
    case Qt::Key_yen: return EventKeyboard::KeyCode::KEY_YEN;
        CC_LETTER_CASE(A);
        CC_LETTER_CASE(B);
        CC_LETTER_CASE(C);
        CC_LETTER_CASE(D);
        CC_LETTER_CASE(E);
        CC_LETTER_CASE(F);
        CC_LETTER_CASE(G);
        CC_LETTER_CASE(H);
        CC_LETTER_CASE(I);
        CC_LETTER_CASE(J);
        CC_LETTER_CASE(K);
        CC_LETTER_CASE(L);
        CC_LETTER_CASE(M);
        CC_LETTER_CASE(N);
        CC_LETTER_CASE(O);
        CC_LETTER_CASE(P);
        CC_LETTER_CASE(Q);
        CC_LETTER_CASE(R);
        CC_LETTER_CASE(S);
        CC_LETTER_CASE(T);
        CC_LETTER_CASE(U);
        CC_LETTER_CASE(V);
        CC_LETTER_CASE(W);
        CC_LETTER_CASE(X);
        CC_LETTER_CASE(Y);
        CC_LETTER_CASE(Z);
    default: break;
    }

    return EventKeyboard::KeyCode::KEY_NONE;
}

#undef CC_LETTER_CASE

/* Global EGLView singleton for this module */
static EGLView *egl_view = NULL;


/** @deprecated Use getInstance() instead */
EGLView *EGLView::sharedOpenGLView()
{
    return getInstance();
}

EGLView *EGLView::getInstance()
{
    if (egl_view == NULL) {
        egl_view = new EGLView;
    }

    return egl_view;
}


EGLView::EGLView()
    : m_integration(NULL)
{
}

EGLView::~EGLView()
{
    if (m_integration) {
        delete m_integration;
    }
}

void
EGLView::setFrameSize(float width, float height)
{
    if (m_integration == NULL) {
        m_integration = new Cocos2DQt5OpenGLIntegration(this,
                (int)width, (int)height);
    } else {
        m_integration->resize(width, height);
    }

    EGLViewProtocol::setFrameSize(width, height);
}

void
EGLView::swapBuffers()
{
    if (m_integration != NULL) {
        m_integration->swapBuffers();
    }
}

void
EGLView::setIMEKeyboardState(bool bOpen)
{
    QGuiApplication *app = static_cast<QGuiApplication*>(QGuiApplication::instance());
    app->inputMethod()->setVisible(bOpen);
}

void
EGLView::end()
{
    QGuiApplication::exit(0);
}

NS_CC_END
