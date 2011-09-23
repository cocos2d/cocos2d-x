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

#ifndef OpenGLESString_H_
#define OpenGLESString_H_

#include <string>

namespace OpenGLES {
	
	class OpenGLESString {
	public:
		OpenGLESString(const char *str);
		OpenGLESString(std::string str);
		OpenGLESString(int val);
		
		OpenGLESString operator+ (const char *val);
		OpenGLESString operator+ (std::string val);
		OpenGLESString operator+ (OpenGLESString val);
		OpenGLESString operator+ (size_t val);
		OpenGLESString operator+ (int val);
		OpenGLESString operator+ (unsigned int val);
		OpenGLESString operator+ (float val);
		OpenGLESString operator+ (double val);
		std::string operator()();
	private:
		std::string string;
	};
	
}

#endif
