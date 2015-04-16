// Image Picker for cocos2d-x
// @Author: Kanglai Qian
// @url: https://github.com/qiankanglai/ImagePicker

#include "ImagePicker.h"
#include "ImagePickerImpl.h"

#include "cocos2d.h"

using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "jni/JniHelper.h"

extern "C" {
    void Java_org_cocos2dx_lib_Cocos2dxImagePicker_ImagePickerResult(JNIEnv *env, jobject thiz, jbyteArray array)
    {
        if(array != NULL){
        	jsize lengthOfArray = env->GetArrayLength(array);
        	jbyte* bufferPtr = env->GetByteArrayElements(array, NULL);
            Image *image = new Image();
            image->initWithImageData((unsigned char*)bufferPtr, lengthOfArray);
        	env->ReleaseByteArrayElements(array, bufferPtr, 0);  

            Director::getInstance()->getScheduler()->performFunctionInCocosThread([image]{
                Texture2D* texture = new Texture2D();
                texture->initWithImage(image);
                texture->autorelease();
                image->release();

                ImagePicker::getInstance()->finishImage(texture);
            });
        }
        else{
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
                ImagePicker::getInstance()->finishImage(nullptr);
            });
        }
    }
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include <ppltasks.h>

using namespace concurrency;
using namespace Platform;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Core;

#endif

void ImagePickerImpl::openImage()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    bool result = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxImagePicker", "openImage", "()V");
    if (result)
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    else
        ImagePicker::getInstance()->finishImage(nullptr);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto glView = Director::getInstance()->getOpenGLView();
    HWND hwnd = glView->getWin32Window();
    
	OPENFILENAME ofn;       // common dialog box structure
	WCHAR szFile[256] = {0};       // buffer for filename
    
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Images\0*.png;*.jpeg;*.jpg\0"
    L"All\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if(GetOpenFileName(&ofn)){
		char temp[256];
		const char DefChar = ' ';
		WideCharToMultiByte(CP_ACP,0,szFile,-1, temp,256, &DefChar, NULL);
        
		Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(std::string(temp));
		ImagePicker::getInstance()->finishImage(texture);
	}
	else{
		ImagePicker::getInstance()->finishImage(nullptr);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(
		CoreDispatcherPriority::High,
		ref new DispatchedHandler([]()
	{
		// **ATTANTION**: direct call `PickSingleFileAsync` in render loop will crash
		//http://sertacozercan.com/2013/10/fixing-element-not-found-exception-from-hresult-0x80070490-error-in-windows-8-x/
		FileOpenPicker^ openPicker = ref new FileOpenPicker();
		openPicker->ViewMode = PickerViewMode::Thumbnail;
		openPicker->SuggestedStartLocation = PickerLocationId::PicturesLibrary;
		openPicker->FileTypeFilter->Append(".png");
		openPicker->FileTypeFilter->Append(".jpg");
		openPicker->FileTypeFilter->Append(".jpeg");
#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
		openPicker->PickSingleFileAndContinue();
#else
		auto dataReader = std::make_shared<DataReader^>(nullptr);
		create_task(openPicker->PickSingleFileAsync()).then([](StorageFile^ file)
		{
			if (file == nullptr)
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
					ImagePicker::getInstance()->finishImage(nullptr);
				});
				cancel_current_task();
			}
			return file->OpenAsync(Windows::Storage::FileAccessMode::Read);
		}).then([dataReader](Windows::Storage::Streams::IRandomAccessStream^ fileStream)
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
#endif
	}));
#else
    CCLOG("ImagePickerImpl: unsupported yet");
    ImagePicker::getInstance()->finishImage(nullptr);
#endif
}
