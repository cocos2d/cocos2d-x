using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using PhoneDirect3DXamlAppComponent;
using System.Windows.Media;
using System.Windows.Input;

namespace PhoneDirect3DXamlAppInterop
{
    public partial class EditBox : UserControl
    {
        private EditBoxImpl m_editBoxImpl = null;
        private String m_strText = "";
        private String m_strPlaceholder = "";
        private bool bIsFocus = false;

        public EditBox(EditBoxImpl editboxImpl, String strPlaceholder, String strText, int maxLen)
        {
            m_editBoxImpl = editboxImpl;
            InitializeComponent();
            m_strText = strText;
            m_strPlaceholder = strPlaceholder;
            this.textinput.TabIndex = 0;
            this.textinput.MaxLength = maxLen < 0 ? 0 : maxLen;
            this.textinput.GotFocus += textinput_GotFocus;
            this.textinput.LostFocus += textinput_LostFocus;
            this.Loaded += EditBox_Loaded;
        }

        void EditBox_Loaded(object sender, RoutedEventArgs e)
        {
            this.textinput.Focus();
        }

        void textinput_LostFocus(object sender, RoutedEventArgs e)
        {
            bIsFocus = false;
            m_strText = this.textinput.Text;
            if (this.textinput.Text == "")
            {
                this.textinput.Text = m_strPlaceholder;
            }                
        }

        void textinput_GotFocus(object sender, RoutedEventArgs e)
        {
            bIsFocus = true;
            this.textinput.Text = m_strText;
            this.textinput.Select(this.textinput.Text.Length, 0);
        }

        private void OnKeyDownHandler(object sender, System.Windows.Input.KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Enter:
                    Done_Click(sender, null);
                    e.Handled = true;
                    break;
                default:
                    break;
            }
        }

        private void Done_Click(object sender, RoutedEventArgs e)
        {
            m_editBoxImpl.OnSelectText(sender, m_strText);
            ((Grid)this.Parent).Children.Remove(this);
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            ((Grid)this.Parent).Children.Remove(this);
        }

        private void textinput_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (bIsFocus)
                m_strText = this.textinput.Text;
        }
    }
}
