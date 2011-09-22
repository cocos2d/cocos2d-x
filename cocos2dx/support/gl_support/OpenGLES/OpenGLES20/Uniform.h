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

#ifndef Uniform_H_
#define Uniform_H_

#include <OpenGLES/ES2/gl.h>
#include <string>
#include <sstream>
#include <utility>
#include "ShaderProgram.h"
#include "ShaderFile.h"
#include "OpenGLESMath.h"

namespace OpenGLES {
	namespace OpenGLES2 {
		
		class UniformSimple {
		public:
			UniformSimple(int id, int location);
			const int getId();
			const GLint getLocation();
			
		private:
			int id;
			GLint location;
		};
		
		class UniformBase {
		public:
			UniformBase(GLint location);
			virtual ~UniformBase();
			
			void setLocation(GLint loc);
			const GLint getLocation();
			virtual void upload(ShaderProgram *program) = 0;
			void addAdditionalRequiredShaderFile(int key, ShaderFile *additionalRequiredShaderFile);
			virtual std::vector<ShaderFile *> getAdditionalRequiredShaderFiles() = 0;
			void setFather(UniformBase *father);
			
		protected:
			GLint location;
			bool uploaded;
			std::vector<std::pair<int, ShaderFile *> > additionalRequiredShaderFiles;
			UniformBase *father;
		};
		
		template <class T>
		class Uniform : public UniformBase {
		public:
			Uniform(T value);
			Uniform();
			~Uniform();
			
			void setValue(T val);
			virtual const T getValue();
			void upload(ShaderProgram *program);
			virtual std::vector<ShaderFile *> getAdditionalRequiredShaderFiles();
		protected:	
			T value;
		};
		
		template <>
		class Uniform<Vector3<GLfloat> > : public UniformBase {
		public:
			Uniform(GLfloat x, GLfloat y, GLfloat z) : UniformBase(-1), value(x, y, z) {}
			Uniform(Vector3<GLfloat> value) : UniformBase(-1), value(value) {}
			Uniform() : UniformBase(-1) {}
			~Uniform() {}
			
			void setValue(Vector3<GLfloat> val)
			{
				uploaded = false;
				value = val;
			}
			
			const Vector3<GLfloat> getValue()
			{
				return value;
			}
			
			void upload(ShaderProgram *program)
			{
				if (!uploaded) {
					program->setUniform3fv(location, 1, (GLfloat*) &value.v);
					uploaded = true;
				}
			}
			
			virtual std::vector<ShaderFile *> getAdditionalRequiredShaderFiles()
			{
				std::vector<ShaderFile *> shaderFiles;
				
				for (size_t i = 0; i < this->additionalRequiredShaderFiles.size(); i++)
				{
					if (this->father == 0 || static_cast<Uniform<bool> *>(this->father)->getValue() == true) {
						shaderFiles.push_back(this->additionalRequiredShaderFiles[i].second);
					}
				}
				
				return shaderFiles;
			}
			
		protected:	
			Vector3<GLfloat> value;
		};
		
		template <>
		class Uniform<Vector4<GLfloat> > : public UniformBase {
		public:
			Uniform(GLfloat x, GLfloat y, GLfloat z, GLfloat w) : UniformBase(-1), value(x, y, z, w) {}
			Uniform(Vector4<GLfloat> value) : UniformBase(-1), value(value) {}
			Uniform() : UniformBase(-1) {}
			~Uniform() {}
			
			void setValue(Vector4<GLfloat> val)
			{
				uploaded = false;
				value = val;
			}
			
			const Vector4<GLfloat> getValue()
			{
				return value;
			}
			
			void upload(ShaderProgram *program)
			{
				if (!uploaded) {
					program->setUniform4fv(location, 1, (GLfloat*) &value.v);
					uploaded = true;
				}
			}
			
			virtual std::vector<ShaderFile *> getAdditionalRequiredShaderFiles()
			{
				std::vector<ShaderFile *> shaderFiles;
				
				for (size_t i = 0; i < this->additionalRequiredShaderFiles.size(); i++)
				{
					if (this->father == 0 || static_cast<Uniform<bool> *>(this->father)->getValue() == true) {
						shaderFiles.push_back(this->additionalRequiredShaderFiles[i].second);
					}
				}
				
				return shaderFiles;
			}
			
		protected:	
			Vector4<GLfloat> value;
		};
		
		template <class T>
		class UniformState : public Uniform<T> {
		public:
			UniformState(ShaderFile *defineShaderFile, const char *defineName, T value);
			~UniformState();
			
			std::string getDefine();
			void addDefineShaderFile(ShaderFile *defineShaderFile);
			std::vector<ShaderFile *>& getDefineShaderFiles();
			std::vector<ShaderFile *> getAdditionalRequiredShaderFiles();
			const T getValue();
			
		private:	
			std::string defineName;
			std::vector<ShaderFile *> defineShaderFiles;
		};
		
		
		
		template <class T>
		Uniform<T>::Uniform(T value) : UniformBase(-1), value(value)
		{
			
		}
		
		template <class T>
		Uniform<T>::Uniform() : UniformBase(-1)
		{
			
		}
		
		template <class T>
		Uniform<T>::~Uniform()
		{
			
		}
		
		template <class T>
		void Uniform<T>::setValue( T val )
		{
			// TODO: Profile whether this if clause is an optimization
			//if (value != val) {
			uploaded = false;
			value = val;
			//}
		}
		
		template <class T>
		const T Uniform<T>::getValue()
		{
			return value;
		}
		
		template <class T>
		std::vector<ShaderFile *> Uniform<T>::getAdditionalRequiredShaderFiles()
		{
			std::vector<ShaderFile *> shaderFiles;
			
			for (size_t i = 0; i < this->additionalRequiredShaderFiles.size(); i++)
			{
				if (this->father == 0 || static_cast<Uniform<bool> *>(this->father)->getValue() == true) {
					shaderFiles.push_back(this->additionalRequiredShaderFiles[i].second);
				}
			}
			
			return shaderFiles;
		}
		
		
		template <class T>
		UniformState<T>::UniformState(ShaderFile *defineShaderFile, const char *defineName, T value ) : Uniform<T>(value), defineName(defineName)
		{
			defineShaderFiles.push_back(defineShaderFile);
		}
		
		template <class T>
		UniformState<T>::~UniformState()
		{
			
		}
		
		template <class T>
		void UniformState<T>::addDefineShaderFile(ShaderFile *defineShaderFile)
		{
			defineShaderFiles.push_back(defineShaderFile);
		}
		
		template <class T>
		std::vector<ShaderFile *>& UniformState<T>::getDefineShaderFiles()
		{
			return defineShaderFiles;
		}
		
		template <class T>
		std::vector<ShaderFile *> UniformState<T>::getAdditionalRequiredShaderFiles()
		{
			std::vector<ShaderFile *> shaderFiles;
			
			for (size_t i = 0; i < this->additionalRequiredShaderFiles.size(); i++)
			{
				if (this->additionalRequiredShaderFiles[i].first == this->value && (this->father == 0 || static_cast<Uniform<bool> *>(this->father)->getValue() == true)) {
					shaderFiles.push_back(this->additionalRequiredShaderFiles[i].second);
				}
			}
			
			return shaderFiles;
		}
		
		template <class T>
		const T UniformState<T>::getValue()
		{
			if (this->father == 0 || static_cast<Uniform<bool> *>(this->father)->getValue() == true) {
				return this->value;
			} else {
				return 0;
			}
		}
	}
}

#endif
