#pragma once

#include "IEditBoxCallback.h"

namespace PhoneDirect3DXamlAppComponent
{
	public ref class EditBoxDelegate sealed
	{
	public:
		EditBoxDelegate(void);
		void SetCallback(IEditBoxCallback^ callback);

		property static IEditBoxCallback^ GlobalCallback;
	};
	
}