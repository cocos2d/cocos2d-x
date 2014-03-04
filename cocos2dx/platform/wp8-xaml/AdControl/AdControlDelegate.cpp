#include "AdControlDelegate.h"

namespace PhoneDirect3DXamlAppComponent
{
	namespace AdControlHelper
	{
		AdControlDelegate::AdControlDelegate( void )
		{

		}

		void AdControlDelegate::SetCallback( ICallback^ callback )
		{
			GlobalCallback = callback;
		}

	}
}
