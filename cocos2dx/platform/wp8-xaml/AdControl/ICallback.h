#include "CompletedEventArgs.h"

namespace PhoneDirect3DXamlAppComponent
{
	namespace AdControlHelper
	{
		// A callback interface for C# code to implement.
		public interface class ICallback
		{
			// Submit a score completed event.
			event Windows::Foundation::EventHandler<CompletedEventArgs^>^ OnBannerRefreshed;
			event Windows::Foundation::EventHandler<CompletedEventArgs^>^ OnBannerReceivedFailed;
			void CreateMicroBannerAd();
			void CreateInMobiAd();

			// switch bottombar in mainpage to add or remove panel
			void SwitchBottomBar();

			// close ad
			void CloseAd();
			
			// purchase product from market
			void PurchaseProduct();
			//... other event and other function

			bool GetIsTrial();
		};
	}
}