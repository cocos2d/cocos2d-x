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
        public event EventHandler<String> OnReceivedText;
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

        public void openEditBox(String strPlaceHolder, string strText, int maxLength)
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                EditBox editbox = new EditBox(this, strPlaceHolder, strText, maxLength);   
                if (m_mainPage != null)
                {
                    m_mainPage.PresentUserControl(editbox);
                }
            });            
        }

        public void OnSelectText(object sender, String str)
        {
            if (m_d3dInterop != null && OnReceivedText != null)
            {
                m_d3dInterop.OnEditboxEvent(sender, str, OnReceivedText);
            }
        }
    }
}
