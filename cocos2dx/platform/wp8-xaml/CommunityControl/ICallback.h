#include "CompletedEventArgs.h"

namespace PhoneDirect3DXamlAppComponent
{
	namespace CommunityControlHelper
	{
		// A callback interface for C# code to implement.
		public interface class ICallback
		{
			// Submit a score completed event.
			event Windows::Foundation::EventHandler<CompletedEventArgs^>^ OnBannerRefreshed;
			event Windows::Foundation::EventHandler<CompletedEventArgs^>^ OnBannerReceivedFailed;
			
			//share Link with other
			void ShareLinkToOther();
			//... other event and other function
		};
	}
}