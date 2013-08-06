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

#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"

#include <QGuiApplication>
#include <QWindow>

#include <QOpenGLContext>
#include <QEvent>
#include <QTouchEvent>

#include <QInputMethod>

NS_CC_BEGIN

class Cocos2DQt5OpenGLIntegration : public QWindow {
    public:
        Cocos2DQt5OpenGLIntegration(EGLView *view, int width, int height);
        ~Cocos2DQt5OpenGLIntegration();

        virtual void touchEvent(QTouchEvent *event);
        virtual bool event(QEvent *event);

        void swapBuffers();

    private:
        EGLView *m_egl_view;
        QOpenGLContext *m_context;
};

Cocos2DQt5OpenGLIntegration::Cocos2DQt5OpenGLIntegration(EGLView *view, int width, int height)
    : m_egl_view(view)
    , m_context(NULL)
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

bool
Cocos2DQt5OpenGLIntegration::event(QEvent *event)
{
    if (event->type() == QEvent::Close) {
        Director::getInstance()->end();
    }

    return QWindow::event(event);
}

void
Cocos2DQt5OpenGLIntegration::swapBuffers()
{
    m_context->swapBuffers(this);
    m_context->makeCurrent(this);
}


/* Global EGLView singleton for this module */
static EGLView *
egl_view = NULL;


/** @deprecated Use getInstance() instead */
EGLView *
EGLView::sharedOpenGLView()
{
    return getInstance();
}

EGLView *
EGLView::getInstance()
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
