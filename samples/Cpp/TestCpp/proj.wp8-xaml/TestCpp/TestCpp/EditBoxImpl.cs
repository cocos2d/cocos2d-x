/****************************************************************************
Copyright (c) 2014 cocos2d-x.org

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

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PhoneDirect3DXamlAppComponent;
using System.Windows;

namespace PhoneDirect3DXamlAppInterop
{
    public class EditBoxImpl : IEditBoxCallback
    {
        private event EventHandler<String> m_receiveHandler;
        private MainPage m_mainPage = null;
        private Direct3DInterop m_d3dInterop = null;

        public void setMainPage(MainPage page)
        {
            m_mainPage = page;
        }

        public void setD3dInterop(Direct3DInterop d3dInterop)
        {
            m_d3dInterop = d3dInterop;
        }

        public void openEditBox(String strPlaceHolder, string strText, int maxLength, int inputMode, int inputFlag, EventHandler<String> receiveHandler)
        {
            m_receiveHandler = receiveHandler;
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                EditBox editbox = new EditBox(this, strPlaceHolder, strText, maxLength, inputMode, inputFlag);   
                if (m_mainPage != null)
                {
                    m_mainPage.PresentUserControl(editbox);
                }
            });            
        }

        public void OnSelectText(object sender, String str)
        {
            if (m_d3dInterop != null && m_receiveHandler != null)
            {
                m_d3dInterop.OnEditboxEvent(sender, str, m_receiveHandler);
            }
        }
    }
}
