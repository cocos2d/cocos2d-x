/* $Change: 597344 $ */
#ifndef _egl_macro_h_
#define _egl_macro_h_

#define eglGetError sglGetError
#define eglGetDisplay 	sglGetDisplay
#define eglInitialize	sglInitialize
#define eglTerminate sglTerminate
#define eglQueryString sglQueryString
#define eglGetConfigs sglGetConfigs
#define eglChooseConfig sglChooseConfig			   
#define eglGetConfigAttrib sglGetConfigAttrib
#define eglCreateWindowSurface sglCreateWindowSurface
#define eglCreatePbufferSurface sglCreatePbufferSurface
#define eglCreatePixmapSurface sglCreatePixmapSurface
#define eglDestroySurface	sglDestroySurface
#define eglQuerySurface sglQuerySurface		
#define eglBindAPI sglBindAPI	
#define eglQueryAPI sglQueryAPI							
#define eglWaitClient sglWaitClient 
#define eglReleaseThread sglReleaseThread
#define eglCreatePbufferFromClientBuffer sglCreatePbufferFromClientBuffer
#define eglSurfaceAttrib sglSurfaceAttrib
#define eglBindTexImage sglBindTexImage	
#define eglReleaseTexImage sglReleaseTexImage
#define eglSwapInterval sglSwapInterval
#define eglCreateContext sglCreateContext
#define eglDestroyContext sglDestroyContext
#define eglMakeCurrent sglMakeCurrent
#define eglGetCurrentContext sglGetCurrentContext
#define eglGetCurrentSurface sglGetCurrentSurface
#define eglGetCurrentDisplay sglGetCurrentDisplay
#define eglQueryContext sglQueryContext
#define eglWaitGL sglWaitGL
#define eglWaitNative sglWaitNative
#define eglSwapBuffers sglSwapBuffers
#define eglCopyBuffers sglCopyBuffers
#define eglGetProcAddress sglGetProcAddress
#define eglUpdateBufferOSP sglUpdateBufferOSP

#endif // _egl_macro_h_
