#ifndef __CC_GL_HEADER_H__
#define __CC_GL_HEADER_H__

#include "CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "OpenGLES/ES1/gl.h"
#include "OpenGLES/ES1/glext.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
#error "Not tested platform"
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
#error "Not tested platform"
#include <IwGL.h>
#endif

#endif
