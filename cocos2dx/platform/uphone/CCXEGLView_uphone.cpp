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

#include "cocoa/NSSet.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"

namespace cocos2d {

CCXEGLView::CCXEGLView(TApplication * pApp)
: TWindow(pApp)
, m_bOpenGLReady(false)
, m_bCaptured(false)
, m_pDelegate(NULL)
{
    m_pTouch    = new CCTouch;
    m_pSet      = new NSSet;
}

CCXEGLView::~CCXEGLView()
{
    delete m_pSet;
    delete m_pTouch;
}

Boolean CCXEGLView::EventHandler(TApplication * pApp, EventType * pEvent)
{
    Boolean bHandled = FALSE;
    if (m_pDelegate && m_pTouch && m_pSet)
    {
        switch(pEvent->eType)
        {
        case EVENT_PenDown:
            if (SetCaptureEx(-1, TRUE))
            {
                m_bCaptured = true;
//                 SS_printf("Down    %4d    %4d\n", pEvent->sParam1, pEvent->sParam2);
                m_pTouch->SetTouchInfo(0, (float)pEvent->sParam1, (float)pEvent->sParam2);
                m_pSet->addObject(m_pTouch);
                m_pDelegate->touchesBegan(m_pSet, NULL);
                bHandled = TRUE;
            }
            break;

        case EVENT_PenMove:
            if (m_bCaptured)
            {
                TRectangle rc;
                GetBounds(&rc);
                if (rc.IsInRect(pEvent->sParam1, pEvent->sParam2))
                {
//                     SS_printf("Move    %4d    %4d\n", pEvent->sParam1, pEvent->sParam2);
                    m_pTouch->SetTouchInfo(0, (float)pEvent->sParam1, (float)pEvent->sParam2);
                    m_pDelegate->touchesMoved(m_pSet, NULL);
                    bHandled = TRUE;
                }
            }
            break;

        case EVENT_PenUp:
            if (m_bCaptured)
            {
                ReleaseCapture();
//                 SS_printf("Up      %4d    %4d\n", pEvent->sParam1, pEvent->sParam2);
                m_pTouch->SetTouchInfo(0, (float)pEvent->sParam1, (float)pEvent->sParam2);
                m_pDelegate->touchesEnded(m_pSet, NULL);
                bHandled = TRUE;
            }
            break;
        }
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
