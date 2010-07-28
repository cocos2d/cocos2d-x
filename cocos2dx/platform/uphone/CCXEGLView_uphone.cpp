/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCXEGLView_uphone.h"

#include "TG3.h"

namespace cocos2d {

CCXEGLView::CCXEGLView(TApplication * pApp)
: TWindow(pApp)
, m_bOpenGLReady(false)
, m_pDelegate(NULL)
{

}

CCXEGLView::~CCXEGLView()
{

}

Boolean CCXEGLView::EventHandler(TApplication * pApp, EventType * pEvent)
{
    Boolean bHandled = FALSE;
    switch(pEvent->eType)
    {
    case EVENT_PenDown:
        {
            bHandled = TRUE;
        }
        break;

    case EVENT_PenMove:
        {
            bHandled = TRUE;
        }
        break;

    case EVENT_PenUp:
        {
        }
        break;
    }

    if (bHandled)
    {
        return bHandled;
    }
    else
    {
        return TWindow::EventHandler(pApp, pEvent);
    }
}

CGSize CCXEGLView::getSize()
{
    TRectangle rc;
    GetBounds(&rc);
    return CGSize((float)rc.Width(), (float)rc.Height());
}

bool CCXEGLView::isOpenGLReady()
{
    return m_bOpenGLReady;
}

void CCXEGLView::release()
{
    CloseWindow();
}

void CCXEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
    m_pDelegate = pDelegate;
}

void CCXEGLView::swapBuffers()
{

}

}
