
#include "platform/win32/CCNativeWin32.h"
#include "platform/win32/CCNativeWin32def.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include "glfw3native.h"
// for mac address
#include <WinSock2.h>
#include <Iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")

NativeWin32* NativeWin32::s_sharedInstance = NULL;

NativeWin32* NativeWin32::sharedInstance(void)
{
	if (!s_sharedInstance)
    {
		s_sharedInstance = new NativeWin32();
    }
    return s_sharedInstance;
}

NativeWin32::NativeWin32(void)
{
}


void NativeWin32::showActivityIndicator(void)
{
}

void NativeWin32::hideActivityIndicator(void)
{
}


void NativeWin32::createAlertView(const char* title, const char *message, const char* cancelButtonTitle)
{
	m_alertViewTitle = string(title ? title : "");
	m_alertViewMessage = string(message ? message : "");
}

int NativeWin32::addAlertButton(const char* buttonTitle)
{
	return 0;
}

void NativeWin32::showAlertViewWithDelegate(AlertViewDelegate *delegate)
{
	/*
	wstring title(m_alertViewTitle.begin(), m_alertViewTitle.end());
	wstring message(m_alertViewMessage.begin(), m_alertViewMessage.end());
	int button = MessageBox(NULL, message.c_str(), title.c_str(), MB_OKCANCEL);
	*/
	// 显示unicode编码的字符  by zhanglei0321@gmail.com
	WCHAR *wszTitleBuf;
        WCHAR *wszMessageBuf;

        int titleBufLen = MultiByteToWideChar(CP_UTF8, 0, m_alertViewTitle.c_str(), -1, NULL, 0);
        int messageBufLen = MultiByteToWideChar(CP_UTF8, 0, m_alertViewMessage.c_str(), -1, NULL, 0);

        wszTitleBuf = new WCHAR[titleBufLen+1];
        wszMessageBuf = new WCHAR[messageBufLen+1];

        memset(wszTitleBuf, 0, sizeof(WCHAR)*(titleBufLen + 1) );

        memset(wszMessageBuf, 0, sizeof(WCHAR)*(messageBufLen + 1) );
        MultiByteToWideChar(CP_UTF8, 0, m_alertViewTitle.c_str(), -1, wszTitleBuf, titleBufLen);
        MultiByteToWideChar(CP_UTF8, 0, m_alertViewMessage.c_str(),-1, wszMessageBuf, messageBufLen);

        int button = MessageBoxW(NULL, wszMessageBuf, wszTitleBuf, MB_OKCANCEL);

        delete [] wszTitleBuf;
        delete [] wszMessageBuf;

	if (button == IDOK || button == IDYES)
	{
		delegate->alertViewClickedButtonAtIndex(0);
	}
	else
	{
		delegate->alertViewClickedButtonAtIndex(1);
	}
}

void NativeWin32::removeAlertView(void)
{
}

void NativeWin32::cancelAlertView(void)
{
}

#if CC_LUA_ENGINE_ENABLED > 0
void NativeWin32::showAlertViewWithLuaListener(LUA_FUNCTION listener)
{
	/*
	wstring title(m_alertViewTitle.begin(), m_alertViewTitle.end());
	wstring message(m_alertViewMessage.begin(), m_alertViewMessage.end());
	int button = MessageBox(NULL, message.c_str(), title.c_str(), MB_OKCANCEL);
	*/
	// 显示unicode编码的字符  by zhanglei0321@gmail.com
	WCHAR *wszTitleBuf;
        WCHAR *wszMessageBuf;

        int titleBufLen = MultiByteToWideChar(CP_UTF8, 0, m_alertViewTitle.c_str(), -1, NULL, 0);
        int messageBufLen = MultiByteToWideChar(CP_UTF8, 0, m_alertViewMessage.c_str(), -1, NULL, 0);

        wszTitleBuf = new WCHAR[titleBufLen+1];
        wszMessageBuf = new WCHAR[messageBufLen+1];

        memset(wszTitleBuf, 0, sizeof(WCHAR)*(titleBufLen + 1) );

        memset(wszMessageBuf, 0, sizeof(WCHAR)*(messageBufLen + 1) );
        MultiByteToWideChar(CP_UTF8, 0, m_alertViewTitle.c_str(), -1, wszTitleBuf, titleBufLen);
        MultiByteToWideChar(CP_UTF8, 0, m_alertViewMessage.c_str(),-1, wszMessageBuf, messageBufLen);

        int button = MessageBoxW(NULL, wszMessageBuf, wszTitleBuf, MB_OKCANCEL);

        delete [] wszTitleBuf;
        delete [] wszMessageBuf;

    LuaValueDict event;
    event["action"] = LuaValue::stringValue("clicked");
	if (button == IDOK || button == IDYES)
	{
		event["buttonIndex"] = LuaValue::intValue(1);
	}
	else
	{
		event["buttonIndex"] = LuaValue::intValue(2);
	}

	LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(listener, 1);
}

void NativeWin32::removeAlertViewLuaListener(void)
{
}
#endif

const string NativeWin32::getInputText(const char* title, const char* message, const char* defaultValue)
{
    //HWND handle = glfwGetWin32Window(Director::getInstance()->getOpenGLView()->getWindow());
    HWND handle = Director::getInstance()->getOpenGLView()->getWin32Window();

	NativeWin32InputBoxStruct inputbox;
	inputbox.title = string(title ? title : "INPUT TEXT");
	inputbox.message = string(message ? message : "INPUT TEXT, PRESS ENTER");
	inputbox.value = string(defaultValue ? defaultValue : "");
	SendMessage(handle, WM_CUT, 998, (LPARAM)&inputbox);
	return inputbox.value;
}

//
//
static bool getMacAddress(string& macstring)
{
    bool ret = false;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
    if (pAdapterInfo == NULL)
    {
        return false;
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
        if (pAdapterInfo == NULL)
        {
            return false;
        }
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR)
    {
        for (PIP_ADAPTER_INFO pAdapter = pAdapterInfo; pAdapter != NULL; pAdapter = pAdapter->Next)
        {
            if (pAdapter->Type != MIB_IF_TYPE_ETHERNET)
            {
                continue;
            }

            if (pAdapter->AddressLength != 6)
            {
                continue;
            }

            char macBuf[32];
            sprintf(macBuf, "%02X-%02X-%02X-%02X-%02X-%02X",
                int(pAdapter->Address[0]),
                int(pAdapter->Address[1]),
                int(pAdapter->Address[2]),
                int(pAdapter->Address[3]),
                int(pAdapter->Address[4]),
                int(pAdapter->Address[5]));
            macstring = macBuf;
            ret = true;
            break;
        }
    }

    free(pAdapterInfo);
    return ret;
}

const string NativeWin32::getUDID()
{
    if (m_macAddress.length() <= 0)
    {
        if (!getMacAddress(m_macAddress))
        {
            m_macAddress = "udid-fixed-1234567890";
        }
    }

    return m_macAddress;
}
