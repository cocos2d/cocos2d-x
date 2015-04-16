#include "App.xaml.h"
#include "OpenGLESPage.xaml.h"

using namespace cocos2d;

App::App()
{
    InitializeComponent();
}

void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
    if (mPage == nullptr)
    {
        mPage = ref new OpenGLESPage(&mOpenGLES);
    }

    // Place the page in the current window and ensure that it is active.
    Windows::UI::Xaml::Window::Current->Content = mPage;
    Windows::UI::Xaml::Window::Current->Activate();
}

#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#include "extensions/ImagePicker/ImagePicker.h"
#include <ppltasks.h>

using namespace concurrency;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;

void App::OnActivated(Windows::ApplicationModel::Activation::IActivatedEventArgs ^ args)
{
	Application::OnActivated(args);
	if (args->Kind == Windows::ApplicationModel::Activation::ActivationKind::PickFileContinuation)
	{
		auto args2 = dynamic_cast<Windows::ApplicationModel::Activation::FileOpenPickerContinuationEventArgs^>(args);
		if (args2->Files == nullptr || args2->Files->Size == 0)
		{
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
				ImagePicker::getInstance()->finishImage(nullptr);
			});
			return;
		}
		auto file = args2->Files->GetAt(0);
		auto dataReader = std::make_shared<DataReader^>(nullptr);
		create_task(file->OpenAsync(Windows::Storage::FileAccessMode::Read)).then([dataReader](Windows::Storage::Streams::IRandomAccessStream^ fileStream)
		{
			*dataReader = ref new DataReader(fileStream->GetInputStreamAt(0));
			return (*dataReader)->LoadAsync(fileStream->Size);
		}).then([dataReader](unsigned int bytes)
		{
			unsigned char* bufferPtr = new unsigned char[bytes];
			(*dataReader)->ReadBytes(ArrayReference<unsigned char>(bufferPtr, bytes));
			Image *image = new Image();
			image->initWithImageData((unsigned char*)bufferPtr, bytes);
			delete[] bufferPtr;

			Director::getInstance()->getScheduler()->performFunctionInCocosThread([image]{
				Texture2D* texture = new Texture2D();
				texture->initWithImage(image);
				texture->autorelease();
				image->release();

				ImagePicker::getInstance()->finishImage(texture);
			});
		});
	}
}
#endif