#include "CommControlDelegate.h"

namespace PhoneDirect3DXamlAppComponent
{
	namespace CommunityControlHelper
	{
		CommunityControlDelegate::CommunityControlDelegate( void )
		{

		}

		void CommunityControlDelegate::SetCallback( ICallback^ callback )
		{
			GlobalCallback = callback;
		}

	}
}