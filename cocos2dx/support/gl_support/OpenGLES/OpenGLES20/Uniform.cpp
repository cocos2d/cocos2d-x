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

#include "Uniform.h"
#include "ShaderProgram.h"
#include "OpenGLESMath.h"

using namespace OpenGLES::OpenGLES2;

UniformSimple::UniformSimple(int id, GLint location) : id(id), location(location)
{
}

const GLint UniformSimple::getLocation()
{
	return location;
}

const int UniformSimple::getId()
{
	return id;
}

UniformBase::UniformBase(GLint location) : additionalRequiredShaderFiles(), location(location), uploaded(false), father(0)
{
	
}

UniformBase::~UniformBase()
{
	
}

void UniformBase::setLocation( GLint loc )
{
	location = loc;
	uploaded = false;
}

const GLint UniformBase::getLocation()
{
	return location;
}

void UniformBase::addAdditionalRequiredShaderFile(int key, ShaderFile *additionalRequiredShaderFile)
{
	additionalRequiredShaderFiles.push_back(std::make_pair(key, additionalRequiredShaderFile));
}

void UniformBase::setFather(UniformBase *f)
{
	father = f;
}

namespace OpenGLES {
	namespace OpenGLES2 {
		
		template <>
		void Uniform<bool>::setValue( bool val )
		{
			// TODO: Profile whether this if clause is really an optimization
			if (value != val) {
				uploaded = false;
				value = val;
			}
		}
		
		template <>
		void Uniform<bool>::upload( ShaderProgram *program )
		{
			if (!uploaded) {
				program->setUniform1i(location, value ? 1 : 0);
				uploaded = true;
			}
		}
		
		template <>
		void Uniform<GLint>::upload( ShaderProgram *program )
		{
			if (!uploaded) {
				program->setUniform1i(location, value);
				uploaded = true;
			}
		}
		
		template <>
		void Uniform<GLfloat>::upload( ShaderProgram *program )
		{
			if (!uploaded) {
				program->setUniform1f(location, value);
				uploaded = true;
			}
		}
		
		template <>
		void Uniform<Matrix3x3<GLfloat> >::upload( ShaderProgram *program )
		{
			if (!uploaded) {
				program->setUniformMatrix3fv(location, (GLfloat*) &value.m[0]);
				uploaded = true;
			}
		}
		
		template <>
		void Uniform<Matrix4x4<GLfloat> >::upload( ShaderProgram *program )
		{
			if (!uploaded) {
				program->setUniformMatrix4fv(location, (GLfloat*) &value.m[0]);
				uploaded = true;
			}
		}
		
		template <>
		std::string UniformState<bool>::getDefine()
		{
			std::string define = "#define ";
			define += defineName;
			define += " ";
			define += value ? "1" : "0";
			define += "\n";
			
			return define;
		}
		
		template <>
		std::string UniformState<GLint>::getDefine()
		{
			std::string define = "#define ";
			define += defineName;
			define += " ";
			std::stringstream out;
			out << value;
			define += out.str();
			define += "\n";
			
			return define;
		}
	}
}
