#pragma once

#include "InputEvent.h"
#include "CompletedEventArgs.h"

using namespace Platform;

namespace PhoneDirect3DXamlAppComponent
{
	class CustomControlEvent : public InputEvent
	{
	public:
		CustomControlEvent(Object^ sender, CompletedEventArgs^ args, Windows::Foundation::EventHandler<CompletedEventArgs^>^ handler);
		virtual void execute(Cocos2dRenderer ^ renderer);

	private:
		Object^ m_sender;
		CompletedEventArgs^ m_args;
		Windows::Foundation::EventHandler<CompletedEventArgs^>^ m_handler;
	};
}