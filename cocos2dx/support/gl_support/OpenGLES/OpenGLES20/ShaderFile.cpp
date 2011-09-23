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

#include "ShaderFile.h"
#include "OpenGLESUtil.h"

using namespace OpenGLES::OpenGLES2;

ShaderFile::ShaderFile( GLenum type, std::string name ) : OpenGLESFile(name), type(type)
{

}

GLenum ShaderFile::getType()
{
	return type;
}

void ShaderFile::setType(GLenum t)
{
	type = t;
}

