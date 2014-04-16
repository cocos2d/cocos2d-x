#include "MarketplaceControllerDelegate.h"

namespace PhoneDirect3DXamlAppComponent
{
	namespace CommunityControlHelper
	{
		MarketplaceControllerDelegate::MarketplaceControllerDelegate(void)
		{

		}

		void MarketplaceControllerDelegate::SetCallback(ICallback^ callback)
		{
			GlobalCallback = callback;
		}

	}
}