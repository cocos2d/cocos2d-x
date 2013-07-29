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


#ifndef CCEGLVIEW_QT5_H
#define CCEGLVIEW_QT5_H

#include "platform/CCCommon.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"

NS_CC_BEGIN

class Cocos2DQt5OpenGLIntegration;

class EGLView : public EGLViewProtocol {
    public:
        EGLView();
        virtual ~EGLView();

        static EGLView *getInstance();

        /** @deprecated Use getInstance() instead */
        CC_DEPRECATED_ATTRIBUTE static EGLView *sharedOpenGLView();

        virtual bool isOpenGLReady() { return (m_integration != NULL); }

        virtual void setFrameSize(float width, float height);
        virtual void swapBuffers();
        virtual void setIMEKeyboardState(bool bOpen);
        virtual void end();

    private:
        Cocos2DQt5OpenGLIntegration *m_integration;
};

NS_CC_END

#endif /* CCEGLVIEW_QT5_H */
