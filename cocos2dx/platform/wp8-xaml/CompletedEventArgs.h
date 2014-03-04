#pragma once

namespace PhoneDirect3DXamlAppComponent
{
	// An asynchronous completed event argument
	public ref class CompletedEventArgs sealed
	{
	public:
		CompletedEventArgs(bool ReturnValue, int ErrorCode, Platform::String^ ErrorMessage)
		{
			this->ReturnValue = ReturnValue;
			this->ErrorCode = ErrorCode;
			this->ErrorMessage = ErrorMessage;
		}

		property bool ReturnValue;
		property int ErrorCode;
		property Platform::String^ ErrorMessage;
	};
}