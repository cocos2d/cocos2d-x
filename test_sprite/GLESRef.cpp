#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "GLES\gl.h"
#include "EGL\egl.h"
#include <math.h>
#include "ImgSprite.h"

bool  g_keys[256];               // Array Used For The Keyboard Routine
bool  g_active=TRUE;             // Window Active Flag Set To TRUE By Default

#define EGL_CHECK(x) \
	x; \
	{ \
	EGLint eglError = eglGetError(); \
	if(eglError != EGL_SUCCESS) { \
	return 0; \
	} \
	}

EGLDisplay g_sEGLDisplay;
EGLContext g_sEGLContext;
EGLSurface g_sEGLSurface;

ImgSprite * m_pImg = NULL;
CCTextureCache * m_pTexCache = NULL;

HWND g_hWnd = NULL;
HDC g_hDC = NULL;

GLubyte *g_pixels = NULL;
int g_nBitmapWidth = 0;
int g_nBitmapHeight = 0;

LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int CreateWind( int width, int height );
void BackupBuffers();

void SetupMatrix();

int GLES_Init()
{
	if (!CreateWind(320, 480))
	{
		return 0;
	}

	g_hDC = GetWindowDC(g_hWnd);
	//ShowWindow(g_hWnd, SW_SHOW);

	const EGLint pi32ConfigAttribs[] =
	{
		EGL_LEVEL,				0,
		EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
		EGL_NATIVE_RENDERABLE,	EGL_FALSE,
		EGL_DEPTH_SIZE,			EGL_DONT_CARE,
		EGL_NONE
	};

	g_sEGLDisplay = EGL_CHECK(eglGetDisplay(g_hDC));
	if (g_sEGLDisplay == EGL_NO_DISPLAY)
		g_sEGLDisplay = EGL_CHECK(eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY));

	EGLint iMajorVersion, iMinorVersion;
	EGLBoolean bret = EGL_CHECK(eglInitialize(g_sEGLDisplay, &iMajorVersion, &iMinorVersion));

	EGL_CHECK(eglBindAPI(EGL_OPENGL_ES_API));

	int cEGLConfigs;
	EGLConfig aEGLConfigs	= 0;
	EGL_CHECK(eglChooseConfig(g_sEGLDisplay, pi32ConfigAttribs, &aEGLConfigs, 1, &cEGLConfigs));
	if (cEGLConfigs == 0) {
		return 0;
	}

	g_sEGLSurface = EGL_CHECK(eglCreateWindowSurface(g_sEGLDisplay, aEGLConfigs, (NativeWindowType)g_hWnd, 0));
	if (g_sEGLSurface == EGL_NO_SURFACE)
		g_sEGLSurface = EGL_CHECK(eglCreateWindowSurface(g_sEGLDisplay, aEGLConfigs, 0, 0));

	EGLint aEGLContextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	g_sEGLContext = EGL_CHECK(eglCreateContext(g_sEGLDisplay, aEGLConfigs, EGL_NO_CONTEXT, aEGLContextAttributes));

	EGL_CHECK(eglMakeCurrent(g_sEGLDisplay, g_sEGLSurface, g_sEGLSurface, g_sEGLContext));

    SetupMatrix();

    // 初始化一个 ImgSprite 实例对象
    m_pTexCache = CCTextureCache::sharedTextureCache();
    m_pImg = ImgSprite::CreateWithTexture(m_pTexCache->addImage("/NEWPLUS/TDA_DATA/UserData/EndButton.bmp"));

	return 1;
}

void GLES_UnInit(void)
{
	if (g_sEGLDisplay != EGL_NO_DISPLAY)
	{
		eglMakeCurrent( EGL_NO_DISPLAY, EGL_NO_SURFACE,
			EGL_NO_SURFACE, EGL_NO_CONTEXT );
		eglDestroyContext( g_sEGLDisplay, g_sEGLContext );
		eglDestroySurface( g_sEGLDisplay, g_sEGLSurface );
		eglTerminate( g_sEGLDisplay );
		g_sEGLDisplay = EGL_NO_DISPLAY;
	}
	if (g_hDC)
	{
		ReleaseDC(g_hWnd, g_hDC);
	}
	if (g_hWnd)
	{
		CloseWindow(g_hWnd);
	}
}

int GLES_Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CC_ENABLE_DEFAULT_GL_STATES();
    m_pImg->draw();

	/*
	Swap Buffers.
	Brings to the native display the current render surface.
	*/
	EGL_CHECK(eglSwapBuffers(g_sEGLDisplay, g_sEGLSurface));

	BackupBuffers();
	
	return 1;
}

void SetupMatrix()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
	glClearDepthf(0.0f);

	glDisable(GL_BLEND);
}

int CreateWind( int width, int height )
{
	WNDCLASS             wc;                  // Windows Class Structure
	HINSTANCE hInstance;

	hInstance         = GetModuleHandle( NULL );             // Grab An Instance For Our Window
	wc.style          = CS_NOCLOSE | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc    = WNDPROC( WndProc );                  // WndProc Handles Messages
	wc.cbClsExtra     = 0;                                   // No Extra Window Data
	wc.cbWndExtra     = 0;                                   // No Extra Window Data
	wc.hInstance      = hInstance;                           // Set The Instance
	wc.hIcon          = LoadIcon( NULL, IDI_WINLOGO );       // Load The Default Icon
	wc.hCursor        = LoadCursor( NULL, IDC_ARROW );       // Load The Arrow Pointer
	wc.hbrBackground  = NULL;                                // No Background Required For GL
	wc.lpszMenuName   = NULL;                                // We Don't Want A Menu
	wc.lpszClassName  = "OpenGL";                            // Set The Class Name

	if ( ! RegisterClass( &wc ) )                            // Attempt To Register The Window Class
	{
		MessageBox( NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;
	}

	RECT rect = {0, 0, width, height};
	AdjustWindowRectEx(&rect, WS_POPUPWINDOW, false, WS_EX_TOPMOST | WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
	if ( ! ( g_hWnd=CreateWindowEx(
		WS_EX_TOPMOST | WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,       // Extended Style For The Window
		"OpenGL",                             // Class Name
		"Effect Test App",                    // Window Title
		WS_POPUPWINDOW/*WS_OVERLAPPEDWINDOW*/ |                     // Defined Window Style
		WS_CLIPSIBLINGS |                         // Required Window Style
		WS_CLIPCHILDREN,                          // Required Window Style
		0, 0,                                     // Window Position
		rect.right - rect.left,                                    // Window Width
		rect.bottom - rect.top,                                   // Window Height
		NULL,                                     // No Parent Window
		NULL,                                     // No Menu
		hInstance,                                // Instance
		NULL ) ) )                                // Dont Pass Anything To WM_CREATE
	{
		return 0;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc( HWND      hWnd,
						 UINT      uMsg,
						 WPARAM    wParam,
						 LPARAM    lParam)
{
	switch ( uMsg )      // Check For Windows Messages
	{
	case WM_CREATE:
		{
			//LONG lStyle = GetWindowLong(g_hWnd, GWL_STYLE);
			//lStyle &= ~WS_OVERLAPPEDWINDOW;
			//SetWindowLong(g_hWnd, GWL_STYLE, lStyle);

			//LONG lExStyle = GetWindowLong(g_hWnd, GWL_EXSTYLE);
			//lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE | WS_EX_WINDOWEDGE);
			//SetWindowLong(g_hWnd, GWL_EXSTYLE, lExStyle);

			//SetWindowPos(g_hWnd, NULL, 0,0,0,0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
		}
		break;
	case WM_ACTIVATE:
		{
			if ( ! HIWORD( wParam ) )     // Check Minimization State
			{
				g_active = TRUE;
			}
			else
			{
				g_active = FALSE;
			}
			return 0;
		}

	case WM_SYSCOMMAND:
		{
			if ( ( wParam == SC_SCREENSAVE ) ||
				( wParam == SC_MONITORPOWER ) )
			{
				return 0;
			}
			break;
		}

	case WM_CLOSE:
		{
			PostQuitMessage( 0 );
			return 0;
		}

	case WM_KEYDOWN:
		{
			g_keys[wParam] = TRUE;
			return 0;
		}

	case WM_KEYUP:
		{
			g_keys[wParam] = FALSE;
			return 0;
		}

	case WM_SIZE:
		{
			//ResizeScene( LOWORD( lParam ), HIWORD( lParam ) );  // LoWord=Width, HiWord=Height
			return 0;
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

void BackupBuffers()
{
	int width = 320;
	int height = 480;
	if (g_pixels != NULL) {
		free(g_pixels);
		g_pixels = NULL;
	}
	g_nBitmapWidth = width;
	g_nBitmapHeight = height;
	g_pixels = (GLubyte*)malloc(4 * width * height);
	memset(g_pixels, 0, 4 * width * height);
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, g_pixels);
}

void gles_CaptureScreen()
{
	int BitPerPixel = GetDeviceCaps(g_hDC, BITSPIXEL);//获得颜色模式
	RECT rect;
	GetClientRect(g_hWnd, &rect);
	int Width = rect.right - rect.left;
	int Height = rect.bottom - rect.top;

	HDC hMemDC = CreateCompatibleDC(g_hDC);//内存DC

	HBITMAP hMemBitmap = CreateCompatibleBitmap(g_hDC, Width, Height);//建立和屏幕兼容的bitmap

	HBITMAP hOldmemBitmap = (HBITMAP)SelectObject(hMemDC, hMemBitmap);//将memBitmap选入内存DC

	bool bRes = BitBlt(hMemDC, rect.left, rect.top, Width, Height, g_hDC, 0, 0, SRCCOPY);//复制屏幕图像到内存DC

	//以下代码保存memDC中的位图到文件
	BITMAP bmp;
	if (GetObject(hMemBitmap, sizeof(BITMAP), &bmp) != sizeof(BITMAP)) {
		return;
	}

	BITMAPINFOHEADER bih = {0};//位图信息头
	bih.biBitCount = bmp.bmBitsPixel;//每个像素字节大小
	bih.biCompression = BI_RGB;
	bih.biHeight = bmp.bmHeight;//高度
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//图像数据大小
	bih.biWidth = bmp.bmWidth;//宽度

	byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];//申请内存保存位图数据

	GetDIBits(hMemDC, (HBITMAP) hMemBitmap, 0, Height, p, (LPBITMAPINFO) &bih, DIB_RGB_COLORS);//获取位图数据

	g_nBitmapWidth = bmp.bmWidth;
	g_nBitmapHeight = bmp.bmHeight;
	if (g_pixels != NULL) {
		free(g_pixels);
		g_pixels = NULL;
	}
	g_pixels = (GLubyte*)malloc(4 * g_nBitmapWidth * g_nBitmapHeight);
	::memcpy(g_pixels, p, 4 * g_nBitmapWidth * g_nBitmapHeight);

	delete [] p;

	SelectObject(hMemDC, hOldmemBitmap);
	DeleteDC(hMemDC);
	DeleteObject(hMemBitmap);
}

void *gles_GetScreenData()
{
	return (void*)g_pixels;
}

int gles_GetScreenWidth()
{
	return g_nBitmapWidth;
}

int gles_GetScreenHeight()
{
	return g_nBitmapHeight;
}

