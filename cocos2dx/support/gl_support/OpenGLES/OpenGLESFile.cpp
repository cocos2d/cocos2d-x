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

#include "OpenGLESFile.h"
#include "OpenGLESUtil.h"
#include <stdio.h>

using namespace OpenGLES;

OpenGLESFile::OpenGLESFile(std::string n) : offset(0), name(n)
{
//	NSString *stringFromChar = [NSString stringWithCString:n.c_str() length:strlen(n.c_str())];
//	NSString * path = [[NSBundle mainBundle] pathForResource: stringFromChar ofType: nil];
//	const char *filename = (const char*)[path cStringUsingEncoding:1];
//	name = filename;
}

bool OpenGLESFile::open() 
{
//	fp = fopen(name.c_str(), "r");
//	return fp;
	offset = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::string fullpath = cocos2d::CCFileUtils::fullPathFromRelativePath(name.c_str());
#else
	std::string fullpath = cocos2d::CCFileUtils::fullPathFromRelativePath(std::string("shaders/" + name).c_str());
#endif
	fileData = new cocos2d::CCFileData(fullpath.c_str(), "rt");
	return fileData && fileData->getBuffer();
}

char * OpenGLESFile::gets(char * buf, int size)
{
//	return fgets(buf, size, fp);
	int read = 0;
	unsigned char* cur = fileData->getBuffer() + offset;
	while (*cur != '\n' && offset < fileData->getSize() && read < size - 1) {
		buf[read++] = *cur;
		++offset;
	}
	cur[read] = 0;
	
	if (offset >= fileData->getSize())
		offset = fileData->getSize();

	return buf;
}

int OpenGLESFile::seek(long int loffset, int origin)
{
//	return fseek(fp, offset, origin);

	switch (origin) {
		case SEEK_CUR:
			offset += loffset;
			break;			
		case SEEK_END:
			offset = fileData->getSize() + loffset;
			break;			
		case SEEK_SET:
			offset = loffset;
			break;			
		default:
			break;
	}
	if (offset >= fileData->getSize())
		offset = fileData->getSize();
	if (offset < 0)
		offset = 0;
	
	return offset;
}

long int OpenGLESFile::tell()
{
//	return ftell(fp);
	return offset;
}

size_t OpenGLESFile::read(void *ptr, size_t size, size_t count)
{
//	return fread(ptr, size, count, fp);
	int available = fileData->getSize() - offset;
	size_t tocopy = (available > size * count ? size * count : available);
	memcpy(ptr, fileData->getBuffer(), tocopy);
	return tocopy;
}

void OpenGLESFile::close()
{
//	fclose(fp);
	delete fileData;
	fileData = 0;
}

std::string OpenGLESFile::getName()
{
	return name;
}
