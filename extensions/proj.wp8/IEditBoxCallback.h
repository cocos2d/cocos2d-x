
#ifndef __IEditBoxCALLBACK_H__
#define __IEditBoxCALLBACK_H__

using namespace Platform;

namespace PhoneDirect3DXamlAppComponent
{
	public interface class IEditBoxCallback
	{
	public:
		void openEditBox(String^ strPlaceHolder, String^ strText, int maxLength);
		event Windows::Foundation::EventHandler<Platform::String^>^ OnReceivedText;
	};
}

#endif
