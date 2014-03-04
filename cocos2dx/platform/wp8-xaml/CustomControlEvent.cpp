#include "CustomControlEvent.h"

namespace PhoneDirect3DXamlAppComponent
{
	CustomControlEvent::CustomControlEvent( Object^ sender, CompletedEventArgs^ args, Windows::Foundation::EventHandler<CompletedEventArgs^>^ handler ):
		m_sender(sender),
		m_args(args),
		m_handler(handler)
	{

	}

	void CustomControlEvent::execute( Cocos2dRenderer ^ renderer )
	{
		m_handler->Invoke(m_sender, m_args);
	}

}