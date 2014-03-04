#pragma once

#include "ICallback.h"

namespace PhoneDirect3DXamlAppComponent
{
	namespace CommunityControlHelper
	{
		public ref class CommunityControlDelegate sealed
		{
		public:
			CommunityControlDelegate(void);

			void SetCallback(ICallback^ callback);

			property static ICallback^ GlobalCallback;
		};
	}

}