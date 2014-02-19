#ifndef __EditBoxEVENT_H__
#define __EditBoxEVENT_H__

#include "platform/wp8-xaml/InputEvent.h"
using namespace Platform;

namespace PhoneDirect3DXamlAppComponent
{
	class EditBoxEvent : public InputEvent
	{
	public:
		EditBoxEvent(Object^ sender, Platform::String^ arg, Windows::Foundation::EventHandler<Platform::String^>^ handle);

		virtual void execute(Cocos2dRenderer ^ renderer);

	private:
		Object^ m_sender;
		Platform::String^ m_args;
		Windows::Foundation::EventHandler<Platform::String^>^ m_handler;
	};
}

#endif