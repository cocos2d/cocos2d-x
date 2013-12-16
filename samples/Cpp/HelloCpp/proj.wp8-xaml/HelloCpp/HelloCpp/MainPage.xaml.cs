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

namespace PhoneDirect3DXamlAppInterop
{
    public partial class MainPage : PhoneApplicationPage
    {
        private Direct3DInterop m_d3dInterop = null;

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
            }
        }

        protected override void OnBackKeyPress(CancelEventArgs e)
        {
            e.Cancel = m_d3dInterop.OnBackKeyPress();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            ((App)Application.Current).RootFrame.Obscured += ObscuredHandler;
            ((App)Application.Current).RootFrame.Unobscured += UnobscuredHandler;
            SystemTray.IsVisible = false;

            if (m_d3dInterop != null)
            {
                m_d3dInterop.OnFocusChange(true);
                m_d3dInterop.OnResuming();
            }
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            ((App)Application.Current).RootFrame.Obscured -= ObscuredHandler;
            ((App)Application.Current).RootFrame.Unobscured -= UnobscuredHandler;

            AutoResetEvent autoEvent = new AutoResetEvent(false);

            // Block UI thread while native component asynchronously saves the
            // game state.
            Thread t = new Thread(async () =>
            {
                m_d3dInterop.OnFocusChange(false);
                await m_d3dInterop.OnSuspending();
                autoEvent.Set();
            });
            t.Start();
            autoEvent.WaitOne();
        }


        void ObscuredHandler(Object sender, EventArgs e)
        {
            m_d3dInterop.OnFocusChange(false);
        }

        void UnobscuredHandler(Object sender, EventArgs e)
        {
            m_d3dInterop.OnFocusChange(true);
        }
    }
}