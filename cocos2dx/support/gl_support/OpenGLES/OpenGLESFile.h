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

#ifndef OpenGLESFile_H_
#define OpenGLESFile_H_

#include <string>
#include "CCFileUtils.h"

namespace OpenGLES {
	
	class OpenGLESFile {
	public:
		OpenGLESFile(std::string name);
		
		bool open();
		char *gets(char * buf, int size);
		int seek(long int offset, int origin);
		long int tell();
		size_t read(void *ptr, size_t size, size_t count);
		void close();
		std::string getName();
		
	private:
		std::string name;
//		FILE *fp;
		cocos2d::CCFileData*	fileData;
		long int offset;
	};
	
}

#endif
