#ifndef __CC_GL2_HEADER_H__
#define __CC_GL_HEADER_H__

#include "CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "OpenGLES/ES2/gl.h"
#include "OpenGLES/ES2/glext.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
#error "Not tested platform"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
#error "Not tested platform"
#include <IwGL.h>
#endif

#endif