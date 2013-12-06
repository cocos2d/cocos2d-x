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

                // Set window bounds in dips
                // since this is a Landscape only app we need to swap width and height
                m_d3dBackground.WindowBounds = new Windows.Foundation.Size(
                    (float)Application.Current.Host.Content.ActualHeight,
                    (float)Application.Current.Host.Content.ActualWidth
                   );

                // Set native resolution in pixels
                m_d3dBackground.NativeResolution = new Windows.Foundation.Size(
                    (float)Math.Floor(Application.Current.Host.Content.ActualWidth * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f),
                    (float)Math.Floor(Application.Current.Host.Content.ActualHeight * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f)
                    );

                // Set render resolution to the full native resolution
                m_d3dBackground.RenderResolution = m_d3dBackground.NativeResolution;

                // Hook-up native component to DrawingSurfaceBackgroundGrid
                DrawingSurfaceBackground.SetBackgroundContentProvider(m_d3dBackground.CreateContentProvider());
                DrawingSurfaceBackground.SetBackgroundManipulationHandler(m_d3dBackground);
            }
        }

        private void PhoneApplicationPage_OrientationChanged(object sender, OrientationChangedEventArgs e)
        {
            float width = (float)Application.Current.Host.Content.ActualWidth;
            float heigth = (float)Application.Current.Host.Content.ActualHeight;


            // Switch the placement of the buttons based on an orientation change.
            if ((e.Orientation & PageOrientation.Portrait) == (PageOrientation.Portrait))
            {
                m_d3dBackground.WindowBounds = new Windows.Foundation.Size(width, heigth);

            }
            // If not in portrait, move buttonList content to visible row and column.
            else
            {
                m_d3dBackground.WindowBounds = new Windows.Foundation.Size(heigth, width);

            }

            m_d3dBackground.OrientationChanged = true;
        } 

    }
}