using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using Microsoft.Phone.Controls;
using PhoneDirect3DXamlAppComponent;
using Windows.Graphics.Display;

namespace PhoneDirect3DXamlAppInterop
{
    public partial class MainPage : PhoneApplicationPage
    {
        private Direct3DBackground m_d3dBackground = null;

        // Constructor
        public MainPage()
        {
            InitializeComponent();
        }

        private void DrawingSurfaceBackground_Loaded(object sender, RoutedEventArgs e)
        {
            if (m_d3dBackground == null)
            {
                m_d3dBackground = new Direct3DBackground();

                // Set native resolution in pixels
                m_d3dBackground.RenderResolution = new Windows.Foundation.Size(
                    (float)Math.Floor(Application.Current.Host.Content.ActualWidth * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f),
                    (float)Math.Floor(Application.Current.Host.Content.ActualHeight * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f)
                    );

                // Hook-up native component to DrawingSurfaceBackgroundGrid
                DrawingSurfaceBackground.SetBackgroundContentProvider(m_d3dBackground.CreateContentProvider());
                DrawingSurfaceBackground.SetBackgroundManipulationHandler(m_d3dBackground);


                m_d3dBackground.WindowOrientation = DisplayOrientations.Landscape;
            }
        }
    }
}