#if DEBUG
#define DISPLAY_MEMORY
#endif

using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using Microsoft.Phone.Controls;
using PhoneDirect3DXamlAppComponent;
using System.Threading;
using System.Diagnostics;
using System.Threading.Tasks;
using Microsoft.Phone.Shell;
using Windows.UI.Input;
using System.Windows.Threading;
using Microsoft.Phone.Info;
using Windows.Graphics.Display;
using Microsoft.Phone.Tasks;

namespace PhoneDirect3DXamlAppInterop
{
    public partial class MainPage : PhoneApplicationPage
    {
        private Direct3DInterop m_d3dInterop = null;
        private DispatcherTimer m_timer;

        // event handler for CCEditBox
        private event EventHandler<String> m_receiveHandler;

        // invisible XAML TextBox for Cocos2d-x keyboard input
        TextBox m_textBox = null;

        // Constructor
        public MainPage()
        {
            InitializeComponent();
#if DISPLAY_MEMORY
            StartTimer();
#else
            MemoryDisplay.Visibility = Visibility.Collapsed;
#endif
        }

        override protected void OnOrientationChanged(OrientationChangedEventArgs args)
        {
            base.OnOrientationChanged(args);
            if (m_d3dInterop != null)
            {
                DisplayOrientations orientation = ConvertToNativeOrientation(args.Orientation);
                m_d3dInterop.OnOrientationChanged(orientation);
            }
        }

        private static DisplayOrientations ConvertToNativeOrientation(PageOrientation xamlOrientation)
        {
            switch (xamlOrientation)
            {
                case PageOrientation.Portrait:
                case PageOrientation.PortraitUp:
                    return DisplayOrientations.Portrait;
                case PageOrientation.PortraitDown:
                    return DisplayOrientations.PortraitFlipped;
                case PageOrientation.Landscape:
                case PageOrientation.LandscapeLeft:
                    return DisplayOrientations.Landscape;
                case PageOrientation.LandscapeRight:
                    return DisplayOrientations.LandscapeFlipped;
                default:
                    return DisplayOrientations.Landscape;
            }
        }

        private void DrawingSurfaceBackground_Loaded(object sender, RoutedEventArgs e)
        {
            if (m_d3dInterop == null)
            {
                PageOrientation pageOrientation = (PageOrientation)GetValue(OrientationProperty);
                DisplayOrientations displayOrientation = ConvertToNativeOrientation(pageOrientation);

                m_d3dInterop = new Direct3DInterop(displayOrientation);

                // Set WindowBounds to size of DrawingSurface
                m_d3dInterop.WindowBounds = new Windows.Foundation.Size(
                    (float)Application.Current.Host.Content.ActualWidth,
                    (float)Application.Current.Host.Content.ActualHeight
                    );

                // Hook-up native component to DrawingSurfaceBackgroundGrid
                DrawingSurfaceBackground.SetBackgroundContentProvider(m_d3dInterop.CreateContentProvider());
                DrawingSurfaceBackground.SetBackgroundManipulationHandler(m_d3dInterop);

                // Hook-up Cocos2d-x delegates
                m_d3dInterop.SetCocos2dEventDelegate(OnCocos2dEvent);
                m_d3dInterop.SetCocos2dMessageBoxDelegate(OnCocos2dMessageBoxEvent);
                m_d3dInterop.SetCocos2dEditBoxDelegate(OpenEditBox);
                m_d3dInterop.SetCocos2dOpenURLDelegate(OpenURL);
            }
        }

        // called when the user presses the back button on the device
        protected override void OnBackKeyPress(CancelEventArgs e)
        {
            m_d3dInterop.OnBackKeyPress();
            // cocos2d-x will async send Cocos2dEvent.TerminateApp event if it is time to exit app.
            // We do not want to exit now, so we set e.Cancel to true.
            e.Cancel = true;
        }

        public void OnKeyDown(object sender, KeyEventArgs e)
        {
            ModifierKeys modifiers = Keyboard.Modifiers;

            switch (e.Key)
            {
                case Key.Escape:
                    m_d3dInterop.OnCocos2dKeyEvent(Cocos2dKeyEvent.Escape);
                    e.Handled = true;
                    break;
                case Key.Back:
                    m_d3dInterop.OnCocos2dKeyEvent(Cocos2dKeyEvent.Back);
                    e.Handled = true;
                    break;
                case Key.Enter:
                    m_d3dInterop.OnCocos2dKeyEvent(Cocos2dKeyEvent.Enter);
                    e.Handled = true;
                    break;
                default:
                    break;
            }
        }

        public void OnKeyUp(object sender, KeyEventArgs e)
        {
            m_d3dInterop.OnCocos2dKeyEvent(Cocos2dKeyEvent.Text, m_textBox.Text);
            m_textBox.Text = "";
        }

        public void OnTextChanged(object sender, TextChangedEventArgs e)
        {
            m_d3dInterop.OnCocos2dKeyEvent(Cocos2dKeyEvent.Text, m_textBox.Text);
        }

        // Called by the Cocos2d-x C++ engine to display a MessageBox
        public void OnCocos2dMessageBoxEvent(String title, String text)
        {
            Dispatcher.BeginInvoke(() =>
            {
                MessageBox.Show(text, title, MessageBoxButton.OK);
            });
        }

        // events called by the Cocos2d-x C++ engine to be handled by C#
        public void OnCocos2dEvent(Cocos2dEvent theEvent, String text)
        {
            Dispatcher.BeginInvoke(() =>
            {
                switch (theEvent)
                {
                    case Cocos2dEvent.TerminateApp:
                        Application.Current.Terminate();
                        break;

                    case Cocos2dEvent.ShowKeyboard:
                        if (m_textBox == null)
                        {
                            m_textBox = new TextBox();
                            m_textBox.Opacity = 0.0;
                            m_textBox.Width = 1;
                            m_textBox.Height = 1;
                            m_textBox.KeyDown += OnKeyDown;
                            m_textBox.TextChanged += OnTextChanged;
                            DrawingSurfaceBackground.Children.Add(m_textBox);
                        }
                        m_textBox.Text = text;
                        m_textBox.SelectionLength = 0;
                        m_textBox.SelectionStart = int.MaxValue;
                        m_textBox.Focus();
                        break;

                    case Cocos2dEvent.HideKeyboard:
                        if (m_textBox != null)
                        {
                            DrawingSurfaceBackground.Children.Remove(m_textBox);
                        }
                        m_textBox = null;
                        break;
                }
            });
        }

        // Called by the Cocos2d-x C++ engine to display a CCEditBox
        public void OpenEditBox(String strPlaceHolder, string strText, int maxLength, int inputMode, int inputFlag, EventHandler<String> receiveHandler)
        {
            m_receiveHandler = receiveHandler;
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                EditBox editbox = new EditBox(this, strPlaceHolder, strText, maxLength, inputMode, inputFlag);
                DrawingSurfaceBackground.Children.Add(editbox);
            });
        }

        public void OnSelectText(object sender, String str)
        {
            if (m_d3dInterop != null && m_receiveHandler != null)
            {
                m_d3dInterop.OnCocos2dEditboxEvent(sender, str, m_receiveHandler);
            }
        }

        public void OpenURL(String url)
        {
            WebBrowserTask webBrowserTask = new WebBrowserTask();
            webBrowserTask.Uri = new Uri(url, UriKind.Absolute);
            webBrowserTask.Show();
        }

        private void StartTimer()
        {
            m_timer = new DispatcherTimer();
            m_timer.Interval = new TimeSpan(0, 0, 1);
            m_timer.Tick += new EventHandler(TimerTick);
            m_timer.Start();
        }

        private void TimerTick(object sender, EventArgs e)
        {
            try
            {
                // These are TextBlock controls that are created in the page’s XAML file.  
                float value = DeviceStatus.ApplicationCurrentMemoryUsage / (1024.0f * 1024.0f);
                MemoryTextBlock.Text = value.ToString();
                value = DeviceStatus.ApplicationPeakMemoryUsage / (1024.0f * 1024.0f);
                PeakMemoryTextBlock.Text = value.ToString();
            }
            catch (Exception ex)
            {
                MemoryTextBlock.Text = ex.Message;
            }
        }
    }
}