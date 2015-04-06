#include "cocos2d.h"

#include "ImagePicker.h"
#include "ImagePickerImpl.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "2d/platform/android/jni/JniHelper.h"

using namespace cocos2d;

extern "C" {
    void Java_org_cocos2dx_cpp_Cocos2dxActivity_ImagePickerResult(JNIEnv *env, jobject thiz, jbyteArray array)
    {
        jbyte* bufferPtr = env->GetByteArrayElements(array, NULL);
        jsize lengthOfArray = env->GetArrayLength(array);
        if(lengthOfArray > 1){
            Image *imf =new Image();
            imf->initWithImageData((unsigned char*)bufferPtr, lengthOfArray);
            imf->autorelease();
    
            Texture2D* pTexture = new Texture2D();
            pTexture->initWithImage(imf);
            pTexture->autorelease();

            ImagePicker::getInstance()->finishImage(pTexture);
        }
        else{
            ImagePicker::getInstance()->finishImage(nullptr);
        }
        env->ReleaseByteArrayElements(array, bufferPtr, 0);  
    }
}
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#ifndef GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#ifndef GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WGL
#endif
#include "glfw3native.h"
#endif

void ImagePickerImpl::openImage()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    bool result = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/Cocos2dxActivity", "openImage", "()V");
    if (result)
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    else
        ImagePicker::getInstance()->finishImage(nullptr);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	GLView *glView = Director::getInstance()->getOpenGLView();
	GLFWwindow *glfwWindow = glView->getWindow();
    //GLFWwindow *glfwWindow = glView->getWindow();
    //HWND hwnd = glfwGetWin32Window(glfwWindow);
    // ccx 3.5 new API
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
#else
    ImagePicker::getInstance()->finishImage(nullptr);
#endif
}
