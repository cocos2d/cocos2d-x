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

namespace PhoneDirect3DXamlAppInterop
{
    public partial class MainPage : PhoneApplicationPage
    {
        private Direct3DInterop m_d3dInterop = null;
        TextBox m_textBox = null;

        // Constructor
        public MainPage()
        {
            InitializeComponent();
        }

        private void DrawingSurface_Loaded(object sender, RoutedEventArgs e)
        {
            if (m_d3dInterop == null)
            {
                m_d3dInterop = new Direct3DInterop();

                // Set window bounds in dips
                m_d3dInterop.WindowBounds = new Windows.Foundation.Size(
                    (float)DrawingSurface.ActualWidth,
                    (float)DrawingSurface.ActualHeight
                    );

                // Set native resolution in pixels
                m_d3dInterop.NativeResolution = new Windows.Foundation.Size(
                    (float)Math.Floor(DrawingSurface.ActualWidth * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f),
                    (float)Math.Floor(DrawingSurface.ActualHeight * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f)
                    );

                // Set render resolution to the full native resolution
                m_d3dInterop.RenderResolution = m_d3dInterop.NativeResolution;

                // Hook-up native component to DrawingSurfaceBackgroundGrid
                DrawingSurface.SetContentProvider(m_d3dInterop.CreateContentProvider());
                DrawingSurface.SetManipulationHandler(m_d3dInterop);

                m_d3dInterop.SetCocos2dEventDelegate(OnCocos2dEvent);

            }
        }

        protected override void OnBackKeyPress(CancelEventArgs e)
        {
            e.Cancel = m_d3dInterop.OnBackKeyPress();
        }

        public void OnKeyDown(object sender, KeyEventArgs e)
        {
            ModifierKeys modifiers = Keyboard.Modifiers;

            switch(e.Key)
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

        public void OnCocos2dEvent(Cocos2dEvent theEvent)
        {
            Dispatcher.BeginInvoke(() =>
            {
                switch (theEvent)
                {
                    case Cocos2dEvent.ShowKeyboard:
                        if(m_textBox == null)
                        {
                            m_textBox = new TextBox();
                            m_textBox.Opacity = 0.0;
                            m_textBox.Width = 1;
                            m_textBox.Height = 1;
                            m_textBox.MaxLength = 1;
                            m_textBox.KeyDown += OnKeyDown;
                            m_textBox.KeyUp += OnKeyUp;
                            LayoutRoot.Children.Add(m_textBox);
                        }
                        m_textBox.Focus();
                        break;
                         
                    case Cocos2dEvent.HideKeyboard:
                        if(m_textBox != null)
                        {
                            LayoutRoot.Children.Remove(m_textBox);
                        }
                        m_textBox = null;
                        break;
                }
            });  
        }
    }
}