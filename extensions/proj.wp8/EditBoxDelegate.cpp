#include "EditBoxDelegate.h"

namespace PhoneDirect3DXamlAppComponent
{
	EditBoxDelegate::EditBoxDelegate(void)
	{
	}

	void EditBoxDelegate::SetCallback( IEditBoxCallback^ callback )
	{
		GlobalCallback = callback;
	}


}