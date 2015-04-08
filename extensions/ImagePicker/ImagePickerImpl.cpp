#include "cocos2d.h"

#include "ImagePicker.h"
#include "ImagePickerImpl.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "jni/JniHelper.h"

using namespace cocos2d;

extern "C" {
    void Java_org_cocos2dx_lib_Cocos2dxActivity_ImagePickerResult(JNIEnv *env, jobject thiz, jbyteArray array)
    {
        jbyte* bufferPtr = env->GetByteArrayElements(array, NULL);
        jsize lengthOfArray = env->GetArrayLength(array);
        if(lengthOfArray > 1){
            Image *image =new Image();
            image->initWithImageData((unsigned char*)bufferPtr, lengthOfArray);

            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([image]{
                // GL texture should be ensured context
                Texture2D* texture = new Texture2D();
                texture->initWithImage(image);

                ImagePicker::getInstance()->finishImage(texture);
            });
        }
        else{
            ImagePicker::getInstance()->finishImage(nullptr);
        }
        env->ReleaseByteArrayElements(array, bufferPtr, 0);  
    }
}
#endif

void ImagePickerImpl::openImage()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    bool result = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "openImage", "()V");
    if (result)
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    else
        ImagePicker::getInstance()->finishImage(nullptr);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto glView = cocos2d::Director::getInstance()->getOpenGLView();
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
        
		cocos2d::Texture2D* texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(std::string(temp));
		ImagePicker::getInstance()->finishImage(texture);
	}
	else{
		ImagePicker::getInstance()->finishImage(nullptr);
	}
#else
    ImagePicker::getInstance()->finishImage(nullptr);
#endif
}
