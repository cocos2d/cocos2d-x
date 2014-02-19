#include "EditBoxEvent.h"

namespace PhoneDirect3DXamlAppComponent
{
	EditBoxEvent::EditBoxEvent( Object^ sender, Platform::String^ arg, Windows::Foundation::EventHandler<Platform::String^>^ handle ):
		m_sender(sender),
		m_args(arg),
		m_handler(handle)
	{

	}

	void EditBoxEvent::execute( Cocos2dRenderer ^ renderer )
	{
		m_handler->Invoke(m_sender, m_args);
	}


}
