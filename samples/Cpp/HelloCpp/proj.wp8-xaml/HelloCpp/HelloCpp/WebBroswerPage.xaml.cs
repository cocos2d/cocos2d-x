using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;

namespace PhoneDirect3DXamlAppInterop
{
    public partial class WebBroswerPage : PhoneApplicationPage
    {
        public WebBroswerPage()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.GoBack();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            this.MiniBroswer.Navigate(new Uri(this.URLField.Text, UriKind.Absolute));
        }
    }
}