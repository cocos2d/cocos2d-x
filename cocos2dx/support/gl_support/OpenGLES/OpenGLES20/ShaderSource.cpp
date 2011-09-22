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

#include "ShaderSource.h"
#include "ShaderFile.h"
#include "OpenGLESUtil.h"
#include "OpenGLESConfig.h"

using namespace OpenGLES::OpenGLES2;

ShaderSource::ShaderSource( ShaderFile *file) : file(file), additionalSource(), sourceExpanded(false)
{
	
}

ShaderSource::ShaderSource( ShaderFile *file, std::string additionalSource ) : file(file), additionalSource(additionalSource), sourceExpanded(false)
{
	
}

bool ShaderSource::expandSource()
{
	static char tmp[1024*16];

	if (!file->open())
	{
		OPENGLES_LOG_MESSAGE(OpenGLESString("ERROR: Cannot open file ") + file->getName());
		return false;
	}
	file->seek(0, SEEK_END);
	long pos = file->tell();
	file->seek(0, SEEK_SET);

	int n = file->read(tmp, 1, pos);
	tmp[n] = '\0';
	file->close();

	int additionalSourceLength = additionalSource.size();
	char *sourceTmp = (char *)malloc(sizeof(char) * n + additionalSourceLength + 1);
	if (sourceTmp == NULL)
	{
		OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, "ERROR: Cannot allocate memory.");
		return false;
	}

	strcpy(sourceTmp, additionalSource.c_str());
	strncpy(sourceTmp + additionalSourceLength, tmp, n + 1);

	source = sourceTmp;
	sourceExpanded = true;

	return true;
}

std::string ShaderSource::getSource()
{
	if (!sourceExpanded) {
		expandSource();
	}
	return source;
}

ShaderFile* ShaderSource::getFile()
{
	return file;
}

void ShaderSource::appendAdditionalSource( std::string newAdditionalSource )
{
	additionalSource += newAdditionalSource;
	sourceExpanded = false;
}
