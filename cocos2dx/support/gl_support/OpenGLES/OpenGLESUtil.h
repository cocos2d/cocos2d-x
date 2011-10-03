/*
 Copyright 2009 Johannes Vuorinen
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 
 http://www.apache.org/licenses/LICENSE-2.0 
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef OpenGLESUtil_H_
#define OpenGLESUtil_H_

#include "OpenGLESConfig.h"

#ifdef OPENGLES_DEBUG
#define OPENGLES_CHECK_GL_ERROR(X, Y, Z) OpenGLES::OpenGLESUtil::checkGlError(X, Y, Z)
#define OPENGLES_LOG_DEBUG_MESSAGE(...) OpenGLES::OpenGLESUtil::logMessage(__VA_ARGS__)
#define OPENGLES_PRINT(...) OpenGLES::OpenGLESUtil::print(__VA_ARGS__)
#define OPENGLES_PRINT_BITS(X) OpenGLES::OpenGLESUtil::printBits(X)
#else
#define OPENGLES_CHECK_GL_ERROR(X, Y, Z)
#define OPENGLES_LOG_DEBUG_MESSAGE(...)
#define OPENGLES_PRINT(...)
#define OPENGLES_PRINT_BITS(X)
#endif

#define OPENGLES_LOG_MESSAGE(...) if (OpenGLES::OpenGLESConfig::OPENGLESCONFIG_DEBUG) { OpenGLES::OpenGLESUtil::logMessage(__VA_ARGS__); }

#include "OpenGLESContext.h"
#include "OpenGLESString.h"
#include <string>
#include <stdio.h>
#include <stdarg.h>

namespace OpenGLES {
	
	class OpenGLESUtil {
	public:
		static void checkGlError(GLenum errorCode, const char *file, const unsigned int line);
		static void logMessage(const char *file, int line, OpenGLESString msg);
		static void logMessage(OpenGLESString msg);
		static void print( const char* format, ... );
		static void printBits(int val);
	};
	
}

#endif
