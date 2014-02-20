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

        public EditBox(EditBoxImpl editboxImpl, String strPlaceholder, String strText, int maxLen, int inputMode, int inputFlag)
        {
            m_editBoxImpl = editboxImpl;
            InitializeComponent();
            m_strText = strText;
            m_strPlaceholder = strPlaceholder;
            SetInputScope(inputMode);
            SetInputFlag(inputFlag);
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

        private void SetInputScope(int inputMode)
        {
            InputScope inputScope = new InputScope();
            InputScopeName name = new InputScopeName();

            switch (inputMode)
            {
                case 0:// kEditBoxInputModeAny
                    name.NameValue = InputScopeNameValue.Default;
                    break;
                case 1:// kEditBoxInputModeEmailAddr
                    name.NameValue = InputScopeNameValue.EmailNameOrAddress;
                    break;
                case 2:// kEditBoxInputModeNumeric
                    name.NameValue = InputScopeNameValue.Number;
                    break;
                case 3:// kEditBoxInputModePhoneNumber
                    name.NameValue = InputScopeNameValue.TelephoneNumber;
                    break;
                case 4:// kEditBoxInputModeUrl
                    name.NameValue = InputScopeNameValue.Url;
                    break;
                case 5:// kEditBoxInputModeDecimal
                    name.NameValue = InputScopeNameValue.Digits;
                    break;
                case 6:// kEditBoxInputModeSingleLine
                    name.NameValue = InputScopeNameValue.Default;
                    break;
                default:
                    name.NameValue = InputScopeNameValue.Default;
                    break;
            }

            inputScope.Names.Add(name);
            this.textinput.InputScope = inputScope;
        }

        private void SetInputFlag(int inputFlag)
        {
            InputScope inputScope = this.textinput.InputScope;
            InputScopeName name = new InputScopeName();
            
            switch (inputFlag)
            {
                case 0:// kEditBoxInputFlagPassword
                    name.NameValue = InputScopeNameValue.Password;
                    break;
                default:
                    name.NameValue = InputScopeNameValue.Default;
                    break;
            }

            inputScope.Names.Add(name);
            this.textinput.InputScope = inputScope;
        }
    }
}
