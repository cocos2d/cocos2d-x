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

#include "ShaderProgram.h"
#include "OpenGLESUtil.h"
#include "OpenGLESConfig.h"
#include "Shader.h"
#include "Uniform.h"
#include "Attribute.h"
#include "OpenGLESState.h"
#include <string>

using namespace OpenGLES::OpenGLES2;

ShaderProgram::ShaderProgram(OpenGLESString name, Shader *vertexShader, Shader *fragmentShader) : name(name)
{
	program = createProgram(vertexShader, fragmentShader);
	
	delete vertexShader;
	delete fragmentShader;
}

ShaderProgram::ShaderProgram(OpenGLESString name, const void *binary, int length, GLenum binaryformat) : name(name)
{
	// TODO: Binary shader
}

ShaderProgram::~ShaderProgram() 
{	
	for (size_t i = 0; i < attributes.size(); i++) {
		delete attributes[i];
	}
	
	for (size_t i = 0; i < uniforms.size(); i++) {
		delete uniforms[i];
	}
	
	glDeleteProgram(program);
}

GLuint ShaderProgram::createProgram(Shader *vertexShader, Shader *fragmentShader) 
{
	GLuint vertexShaderId = vertexShader->compile();
	GLuint fragmentShaderId = fragmentShader->compile();
	
	glReleaseShaderCompiler();
	
	GLuint program = glCreateProgram();
	
	if (program == 0) 
	{
		OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Creating program ") + name + " failed.");
		return 0;
	}
	
	glAttachShader(program, vertexShaderId);
	
	glAttachShader(program, fragmentShaderId);
	
	glLinkProgram(program);
	
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	
	if (!linked || OpenGLESConfig::DEBUG)
	{
		GLint infoLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
		
		if (infoLength > 1)
		{
			char *infoLog = (char *)malloc(sizeof(char) * infoLength);
			
			glGetProgramInfoLog(program, infoLength, NULL, infoLog);
			
			if (linked) 
			{
				OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("WARNING: Linked program ") + name + " with warnings:\n" + infoLog);
			} 
			else 
			{
				OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Linking program ") + name + " failed:\n" + infoLog);
			}
			free(infoLog);
		}
		
		if (linked != 0)
		{
			OPENGLES_LOG_MESSAGE(OpenGLESString("Linked program ") + name + " successfully.");
		}
		else
		{
			glDeleteProgram(program);
			return 0;
		}
	}
	
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &activeAttributesMaxLength);
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUniforms);
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &activeUniformsMaxLength);
	glGetProgramiv(program, GL_ATTACHED_SHADERS, &attachedShaders);
	
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Active attributes: ") + activeAttributes);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Active attributes max length: ") + activeAttributesMaxLength);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Active uniforms: ") + activeUniforms);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Active uniforms max length: ") + activeUniformsMaxLength);
	OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString("Attached shaders: ") + attachedShaders);
	
	OPENGLES_LOG_DEBUG_MESSAGE("Attributes");
	for (int i = 0; i < activeAttributes; i++) {
		char* attributeName = (char *)malloc(sizeof(char) * activeAttributesMaxLength);
		GLint size;
		GLenum type;
		
		glGetActiveAttrib(program, i, activeAttributesMaxLength, NULL, &size, &type, attributeName);
		GLint attributeLocation = glGetAttribLocation(program, attributeName);
		
		int id = -1;
		if (strcmp(attributeName,"a_position") == 0) {
			id = AttributeId::POSITION;
		} else if (strcmp(attributeName,"a_normal") == 0) {
			id = AttributeId::NORMAL;
		} else if (strcmp(attributeName,"a_color") == 0) {
			id = AttributeId::COLOR;
		} else if (strcmp(attributeName,"a_texCoord0") == 0) {
			id = AttributeId::TEXCOORD0;
		} else if (strcmp(attributeName,"a_texCoord1") == 0) {
			id = AttributeId::TEXCOORD1;
		} else if (strcmp(attributeName,"a_texCoord2") == 0) {
			id = AttributeId::TEXCOORD2;
		} else {
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Missing ") + attributeName);
			return 0;
		}
		
		attributes.push_back(new AttributeSimple(id, attributeLocation));
		
#ifdef OPENGLES_DEBUG
		std::string typeString;
		
		switch (type) {
			case GL_FLOAT:
				typeString = "GL_FLOAT";
				break;
			case GL_FLOAT_VEC2:
				typeString = "GL_FLOAT_VEC2";
				break;
			case GL_FLOAT_VEC3:
				typeString = "GL_FLOAT_VEC3";
				break;
			case GL_FLOAT_VEC4:
				typeString = "GL_FLOAT_VEC4";
				break;
			case GL_FLOAT_MAT2:
				typeString = "GL_FLOAT_MAT2";
				break;
			case GL_FLOAT_MAT3:
				typeString = "GL_FLOAT_MAT3";
				break;
			case GL_FLOAT_MAT4:
				typeString = "GL_FLOAT_MAT4";
				break;
			default:
				typeString = "Unknown";
				OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, "ERROR: Unknown type.");
				break;
		}
		
		OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString(attributeName) + ": type " + typeString + " location: " + attributeLocation);
#endif
	}
	
	OPENGLES_LOG_DEBUG_MESSAGE("Uniforms");
	for (int i = 0; i < activeUniforms; i++) {
		
		char* uniformName = (char *)malloc(sizeof(char) * activeUniformsMaxLength);
		GLint size;
		GLenum uniformType;
		glGetActiveUniform(program, i, activeUniformsMaxLength, NULL, &size, &uniformType, uniformName);
		GLint uniformLocation = glGetUniformLocation(program, uniformName);
		
		int id = -1;
		if (strcmp(uniformName,"u_lightModelLocalViewerEnabled") == 0) {
			id = UniformId::LIGHT_MODEL_LOCAL_VIEWER_ENABLED;
		} else if (strcmp(uniformName,"u_lightModelTwoSideEnabled") == 0) {
			id = UniformId::LIGHT_MODEL_TWO_SIDE_ENABLED;
		} else if (strcmp(uniformName,"u_lightingEnabled") == 0) {
			id = UniformId::LIGHTING_ENABLED;
		} else if (strcmp(uniformName,"u_light0Enabled") == 0) {
			id = UniformId::LIGHT0_ENABLED;
		} else if (strcmp(uniformName,"u_light1Enabled") == 0) {
			id = UniformId::LIGHT1_ENABLED;
		} else if (strcmp(uniformName,"u_light2Enabled") == 0) {
			id = UniformId::LIGHT2_ENABLED;
		} else if (strcmp(uniformName,"u_light0.ambient") == 0) {
			id = UniformId::LIGHT0_AMBIENT;
		} else if (strcmp(uniformName,"u_light1.ambient") == 0) {
			id = UniformId::LIGHT1_AMBIENT;
		} else if (strcmp(uniformName,"u_light2.ambient") == 0) {
			id = UniformId::LIGHT2_AMBIENT;
		} else if (strcmp(uniformName,"u_light0.diffuse") == 0) {
			id = UniformId::LIGHT0_DIFFUSE;
		} else if (strcmp(uniformName,"u_light1.diffuse") == 0) {
			id = UniformId::LIGHT1_DIFFUSE;
		} else if (strcmp(uniformName,"u_light2.diffuse") == 0) {
			id = UniformId::LIGHT2_DIFFUSE;
		} else if (strcmp(uniformName,"u_light0.specular") == 0) {
			id = UniformId::LIGHT0_SPECULAR;
		} else if (strcmp(uniformName,"u_light1.specular") == 0) {
			id = UniformId::LIGHT1_SPECULAR;
		} else if (strcmp(uniformName,"u_light2.specular") == 0) {
			id = UniformId::LIGHT2_SPECULAR;
		} else if (strcmp(uniformName,"u_light0.position") == 0) {
			id = UniformId::LIGHT0_POSITION;
		} else if (strcmp(uniformName,"u_light1.position") == 0) {
			id = UniformId::LIGHT1_POSITION;
		} else if (strcmp(uniformName,"u_light2.position") == 0) {
			id = UniformId::LIGHT2_POSITION;
		} else if (strcmp(uniformName,"u_light0.spotDirection") == 0) {
			id = UniformId::LIGHT0_SPOT_DIRECTION;
		} else if (strcmp(uniformName,"u_light1.spotDirection") == 0) {
			id = UniformId::LIGHT1_SPOT_DIRECTION;
		} else if (strcmp(uniformName,"u_light2.spotDirection") == 0) {
			id = UniformId::LIGHT2_SPOT_DIRECTION;
		} else if (strcmp(uniformName,"u_light0.spotExponent") == 0) {
			id = UniformId::LIGHT0_SPOT_EXPONENT;
		} else if (strcmp(uniformName,"u_light1.spotExponent") == 0) {
			id = UniformId::LIGHT1_SPOT_EXPONENT;
		} else if (strcmp(uniformName,"u_light2.spotExponent") == 0) {
			id = UniformId::LIGHT2_SPOT_EXPONENT;
		} else if (strcmp(uniformName,"u_light0.spotCutoffAngleCos") == 0) {
			id = UniformId::LIGHT0_SPOT_CUTOFF_ANGLE_COS;
		} else if (strcmp(uniformName,"u_light1.spotCutoffAngleCos") == 0) {
			id = UniformId::LIGHT1_SPOT_CUTOFF_ANGLE_COS;
		} else if (strcmp(uniformName,"u_light2.spotCutoffAngleCos") == 0) {
			id = UniformId::LIGHT2_SPOT_CUTOFF_ANGLE_COS;
		} else if (strcmp(uniformName,"u_light0.constantAttenuation") == 0) {
			id = UniformId::LIGHT0_CONSTANT_ATTENUATION;
		} else if (strcmp(uniformName,"u_light1.constantAttenuation") == 0) {
			id = UniformId::LIGHT1_CONSTANT_ATTENUATION;
		} else if (strcmp(uniformName,"u_light2.constantAttenuation") == 0) {
			id = UniformId::LIGHT2_CONSTANT_ATTENUATION;
		} else if (strcmp(uniformName,"u_light0.linearAttenuation") == 0) {
			id = UniformId::LIGHT0_LINEAR_ATTENUATION;
		} else if (strcmp(uniformName,"u_light1.linearAttenuation") == 0) {
			id = UniformId::LIGHT1_LINEAR_ATTENUATION;
		} else if (strcmp(uniformName,"u_light2.linearAttenuation") == 0) {
			id = UniformId::LIGHT2_LINEAR_ATTENUATION;
		} else if (strcmp(uniformName,"u_light0.quadraticAttenuation") == 0) {
			id = UniformId::LIGHT0_QUADRATIC_ATTENUATION;
		} else if (strcmp(uniformName,"u_light1.quadraticAttenuation") == 0) {
			id = UniformId::LIGHT1_QUADRATIC_ATTENUATION;
		} else if (strcmp(uniformName,"u_light2.quadraticAttenuation") == 0) {
			id = UniformId::LIGHT2_QUADRATIC_ATTENUATION;
		} else if (strcmp(uniformName,"u_modelViewMatrix") == 0) {
			id = UniformId::MODELVIEW_MATRIX;
		} else if (strcmp(uniformName,"u_modelViewProjectionMatrix") == 0) {
			id = UniformId::MODELVIEW_PROJECTION_MATRIX;
		} else if (strcmp(uniformName,"u_transposeAdjointModelViewMatrix") == 0) {
			id = UniformId::TRANPOSE_ADJOINT_MODEL_VIEW_MATRIX;
		} else if (strcmp(uniformName,"u_rescaleNormalFactor") == 0) {
			id = UniformId::RESCALE_NORMAL_FACTOR;
		} else if (strcmp(uniformName,"u_material.ambient") == 0) {
			id = UniformId::MATERIAL_AMBIENT;
		} else if (strcmp(uniformName,"u_material.diffuse") == 0) {
			id = UniformId::MATERIAL_DIFFUSE;
		} else if (strcmp(uniformName,"u_material.specular") == 0) {
			id = UniformId::MATERIAL_SPECULAR;
		} else if (strcmp(uniformName,"u_material.emission") == 0) {
			id = UniformId::MATERIAL_EMISSION;
		} else if (strcmp(uniformName,"u_material.shininess") == 0) {
			id = UniformId::MATERIAL_SHININESS;
		} else if (strcmp(uniformName,"u_normalizeEnabled") == 0) {
			id = UniformId::NORMALIZE_ENABLED;
		} else if (strcmp(uniformName,"u_rescaleNormalEnabled") == 0) {
			id = UniformId::RESCALE_NORMAL_ENABLED;
		} else if (strcmp(uniformName,"u_alphaTestEnabled") == 0) {
			id = UniformId::ALPHA_TEST_ENABLED;
		} else if (strcmp(uniformName,"u_alphaFunc") == 0) {
			id = UniformId::ALPHA_FUNC;
		} else if (strcmp(uniformName,"u_alphaFuncValue") == 0) {
			id = UniformId::ALPHA_FUNC_VALUE;
		} else if (strcmp(uniformName,"u_globalAmbientColor") == 0) {
			id = UniformId::GLOBAL_AMBIENT_COLOR;
		} else if (strcmp(uniformName,"u_positionEnabled") == 0) {
			id = UniformId::POSITION_ENABLED;
		} else if (strcmp(uniformName,"u_normalEnabled") == 0) {
			id = UniformId::NORMAL_ENABLED;
		} else if (strcmp(uniformName,"u_colorEnabled") == 0) {
			id = UniformId::COLOR_ENABLED;
		} else if (strcmp(uniformName,"u_texCoord0Enabled") == 0) {
			id = UniformId::TEXCOORD0_ENABLED;
		} else if (strcmp(uniformName,"u_texCoord1Enabled") == 0) {
			id = UniformId::TEXCOORD1_ENABLED;
		} else if (strcmp(uniformName,"u_texCoord2Enabled") == 0) {
			id = UniformId::TEXCOORD2_ENABLED;
		} else if (strcmp(uniformName,"u_texture0Enabled") == 0) {
			id = UniformId::TEXTURE0_ENABLED;
		} else if (strcmp(uniformName,"u_texture1Enabled") == 0) {
			id = UniformId::TEXTURE1_ENABLED;
		} else if (strcmp(uniformName,"u_texture2Enabled") == 0) {
			id = UniformId::TEXTURE2_ENABLED;
		} else if (strcmp(uniformName,"u_texture0Sampler") == 0) {
			id = UniformId::TEXTURE0_SAMPLER;
		} else if (strcmp(uniformName,"u_texture1Sampler") == 0) {
			id = UniformId::TEXTURE1_SAMPLER;
		} else if (strcmp(uniformName,"u_texture2Sampler") == 0) {
			id = UniformId::TEXTURE2_SAMPLER;
		} else if (strcmp(uniformName,"u_texture0Matrix") == 0) {
			id = UniformId::TEXTURE0_MATRIX;
		} else if (strcmp(uniformName,"u_texture1Matrix") == 0) {
			id = UniformId::TEXTURE1_MATRIX;
		} else if (strcmp(uniformName,"u_texture2Matrix") == 0) {
			id = UniformId::TEXTURE2_MATRIX;
		} else if (strcmp(uniformName,"u_texture0MatrixEnabled") == 0) {
			id = UniformId::TEXTURE0_MATRIX_ENABLED;
		} else if (strcmp(uniformName,"u_texture1MatrixEnabled") == 0) {
			id = UniformId::TEXTURE1_MATRIX_ENABLED;
		} else if (strcmp(uniformName,"u_texture2MatrixEnabled") == 0) {
			id = UniformId::TEXTURE2_MATRIX_ENABLED;
		} else if (strcmp(uniformName,"u_texture0Format") == 0) {
			id = UniformId::TEXTURE0_FORMAT;
		} else if (strcmp(uniformName,"u_texture1Format") == 0) {
			id = UniformId::TEXTURE1_FORMAT;
		} else if (strcmp(uniformName,"u_texture2Format") == 0) {
			id = UniformId::TEXTURE2_FORMAT;
		} else if (strcmp(uniformName,"u_texture0EnvMode") == 0) {
			id = UniformId::TEXTURE0_ENV_MODE;
		} else if (strcmp(uniformName,"u_texture1EnvMode") == 0) {
			id = UniformId::TEXTURE1_ENV_MODE;
		} else if (strcmp(uniformName,"u_texture2EnvMode") == 0) {
			id = UniformId::TEXTURE2_ENV_MODE;
		} else if (strcmp(uniformName,"u_texture0EnvColor") == 0) {
			id = UniformId::TEXTURE0_ENV_COLOR;
		} else if (strcmp(uniformName,"u_texture1EnvColor") == 0) {
			id = UniformId::TEXTURE1_ENV_COLOR;
		} else if (strcmp(uniformName,"u_texture2EnvColor") == 0) {
			id = UniformId::TEXTURE2_ENV_COLOR;
		} else if (strcmp(uniformName,"u_texture0EnvRGBScale") == 0) {
			id = UniformId::TEXTURE0_ENV_RGB_SCALE;
		} else if (strcmp(uniformName,"u_texture1EnvRGBScale") == 0) {
			id = UniformId::TEXTURE1_ENV_RGB_SCALE;
		} else if (strcmp(uniformName,"u_texture2EnvRGBScale") == 0) {
			id = UniformId::TEXTURE2_ENV_RGB_SCALE;
		} else if (strcmp(uniformName,"u_texture0EnvAlphaScale") == 0) {
			id = UniformId::TEXTURE0_ENV_ALPHA_SCALE;
		} else if (strcmp(uniformName,"u_texture1EnvAlphaScale") == 0) {
			id = UniformId::TEXTURE1_ENV_ALPHA_SCALE;
		} else if (strcmp(uniformName,"u_texture2EnvAlphaScale") == 0) {
			id = UniformId::TEXTURE2_ENV_ALPHA_SCALE;
		} else if (strcmp(uniformName,"u_texture0EnvBlurAmount") == 0) {
			id = UniformId::TEXTURE0_ENV_BLUR_AMOUNT;
		} else if (strcmp(uniformName,"u_texture1EnvBlurAmount") == 0) {
			id = UniformId::TEXTURE1_ENV_BLUR_AMOUNT;
		} else if (strcmp(uniformName,"u_texture2EnvBlurAmount") == 0) {
			id = UniformId::TEXTURE2_ENV_BLUR_AMOUNT;
		} else if (strcmp(uniformName,"u_texture0EnvCombineRGB") == 0) {
			id = UniformId::TEXTURE0_ENV_COMBINE_RGB;
		} else if (strcmp(uniformName,"u_texture1EnvCombineRGB") == 0) {
			id = UniformId::TEXTURE1_ENV_COMBINE_RGB;
		} else if (strcmp(uniformName,"u_texture2EnvCombineRGB") == 0) {
			id = UniformId::TEXTURE2_ENV_COMBINE_RGB;
		} else if (strcmp(uniformName,"u_texture0EnvCombineAlpha") == 0) {
			id = UniformId::TEXTURE0_ENV_COMBINE_ALPHA;
		} else if (strcmp(uniformName,"u_texture1EnvCombineAlpha") == 0) {
			id = UniformId::TEXTURE1_ENV_COMBINE_ALPHA;
		} else if (strcmp(uniformName,"u_texture2EnvCombineAlpha") == 0) {
			id = UniformId::TEXTURE2_ENV_COMBINE_ALPHA;
		} else if (strcmp(uniformName,"u_fogEnabled") == 0) {
			id = UniformId::FOG_ENABLED;
		} else if (strcmp(uniformName,"u_fogColor") == 0) {
			id = UniformId::FOG_COLOR;
		} else if (strcmp(uniformName,"u_fogMode") == 0) {
			id = UniformId::FOG_MODE;
		} else if (strcmp(uniformName,"u_fogDensity") == 0) {
			id = UniformId::FOG_DENSITY;
		} else if (strcmp(uniformName,"u_fogStart") == 0) {
			id = UniformId::FOG_START;
		} else if (strcmp(uniformName,"u_fogEnd") == 0) {
			id = UniformId::FOG_END;
		} else if (strcmp(uniformName,"u_fogHint") == 0) {
			id = UniformId::FOG_HINT;
		} else if (strcmp(uniformName,"u_lightingHint") == 0) {
			id = UniformId::LIGHTING_HINT;
		} else if (strcmp(uniformName,"u_clipPlane0Enabled") == 0) {
			id = UniformId::CLIP_PLANE0_ENABLED;
		} else if (strcmp(uniformName,"u_clipPlane1Enabled") == 0) {
			id = UniformId::CLIP_PLANE1_ENABLED;
		} else if (strcmp(uniformName,"u_clipPlane2Enabled") == 0) {
			id = UniformId::CLIP_PLANE2_ENABLED;
		} else if (strcmp(uniformName,"u_clipPlane3Enabled") == 0) {
			id = UniformId::CLIP_PLANE3_ENABLED;
		} else if (strcmp(uniformName,"u_clipPlane4Enabled") == 0) {
			id = UniformId::CLIP_PLANE4_ENABLED;
		} else if (strcmp(uniformName,"u_clipPlane5Enabled") == 0) {
			id = UniformId::CLIP_PLANE5_ENABLED;
		} else if (strcmp(uniformName,"u_clipPlane0Equation") == 0) {
			id = UniformId::CLIP_PLANE0_EQUATION;
		} else if (strcmp(uniformName,"u_clipPlane1Equation") == 0) {
			id = UniformId::CLIP_PLANE1_EQUATION;
		} else if (strcmp(uniformName,"u_clipPlane2Equation") == 0) {
			id = UniformId::CLIP_PLANE2_EQUATION;
		} else if (strcmp(uniformName,"u_clipPlane3Equation") == 0) {
			id = UniformId::CLIP_PLANE3_EQUATION;
		} else if (strcmp(uniformName,"u_clipPlane4Equation") == 0) {
			id = UniformId::CLIP_PLANE4_EQUATION;
		} else if (strcmp(uniformName,"u_clipPlane5Equation") == 0) {
			id = UniformId::CLIP_PLANE5_EQUATION;
		} else {
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Missing ") + uniformName);
			return 0;
		}
		
		uniforms.push_back(new UniformSimple(id, uniformLocation));
		
#ifdef OPENGLES_DEBUG		
		std::string typeString;
		
		switch (uniformType) {
			case GL_FLOAT:
				typeString = "GL_FLOAT";
				break;
			case GL_FLOAT_VEC2:
				typeString = "GL_FLOAT_VEC2";
				break;
			case GL_FLOAT_VEC3:
				typeString = "GL_FLOAT_VEC3";
				break;
			case GL_FLOAT_VEC4:
				typeString = "GL_FLOAT_VEC4";
				break;
			case GL_INT:
				typeString = "GL_INT";
				break;
			case GL_INT_VEC2:
				typeString = "GL_INT_VEC2";
				break;
			case GL_INT_VEC3:
				typeString = "GL_INT_VEC3";
				break;
			case GL_INT_VEC4:
				typeString = "GL_INT_VEC4";
				break;
			case GL_BOOL:
				typeString = "GL_BOOL";
				break;
			case GL_BOOL_VEC2:
				typeString = "GL_BOOL_VEC2";
				break;
			case GL_BOOL_VEC3:
				typeString = "GL_BOOL_VEC3";
				break;
			case GL_BOOL_VEC4:
				typeString = "GL_BOOL_VEC4";
				break;
			case GL_FLOAT_MAT2:
				typeString = "GL_FLOAT_MAT2";
				break;
			case GL_FLOAT_MAT3:
				typeString = "GL_FLOAT_MAT3";
				break;
			case GL_FLOAT_MAT4:
				typeString = "GL_FLOAT_MAT4";
				break;
			case GL_SAMPLER_2D:
				typeString = "GL_SAMPLER_2D";
				break;
			case GL_SAMPLER_CUBE:
				typeString = "GL_SAMPLER_CUBE";
				break;
			default:
				typeString = "Unknown";
				OPENGLES_LOG_DEBUG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown type ") + uniformType);
				break;
		}
		
		OPENGLES_LOG_DEBUG_MESSAGE(OpenGLESString(uniformName) + ": type " + typeString + " location: " + uniformLocation);
#endif
	}
	
	OPENGLES_LOG_DEBUG_MESSAGE("\n");
	
	return program;
}

void ShaderProgram::use()
{
	glUseProgram(program);
#if OPENGLES_DEBUG
	validate();
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
#endif
}

void ShaderProgram::unuse()
{
	glUseProgram(0);
}

void ShaderProgram::validate()
{
	glValidateProgram(program);
	
	GLint validated;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &validated);
	
	if (!validated)
	{
		GLint infoLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
		
		if (infoLength > 1)
		{
			char *infoLog = (char *)malloc(sizeof(char) * infoLength);
			
			glGetProgramInfoLog(program, infoLength, NULL, infoLog);
			
			OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Validation error in program ") + name + ":\n" + infoLog);
			
			free(infoLog);
		}
	}
}

std::vector<AttributeSimple *>* ShaderProgram::getActiveAttributes()
{
	return &attributes;
}

std::vector<UniformSimple *>* ShaderProgram::getActiveUniforms()
{
	return &uniforms;
}

GLint ShaderProgram::getAttributeLocation(const char* attribName)
{
	GLint res = glGetAttribLocation(program, attribName);
	
	if (res == -1) {
		OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown attribute ") + attribName + " in program " + name);
	}
	
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	
	return res;
}

GLint ShaderProgram::getUniformLocation(const char* uniformName)
{
	GLint res = glGetUniformLocation(program, uniformName);
	
	if (res == -1) {
		OPENGLES_LOG_MESSAGE(__FILE__, __LINE__, OpenGLESString("ERROR: Unknown uniform ") + uniformName + " in program " + name);
	}
	
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
	
	return res;
}

void ShaderProgram::setAttributeVertexPointer(GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
	glVertexAttribPointer(location, size, type, normalized, stride, pointer);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform3f( const char *name, GLfloat x, GLfloat y, GLfloat z )
{
	glUniform3f(getUniformLocation(name), x, y, z);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform3f( GLint loc, GLfloat x, GLfloat y, GLfloat z )
{
	glUniform3f(loc, x, y, z);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform4f( const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
	glUniform4f(getUniformLocation(name), x, y, z, w);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform4f( GLint loc, GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
	glUniform4f(loc, x, y, z, w);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform1f( const char *name, GLfloat v)
{
	glUniform1f(getUniformLocation(name), v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform1f( GLint loc, GLfloat v)
{
	glUniform1f(loc, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniformMatrix4fv( const char *name, GLfloat* m )
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, m);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniformMatrix4fv( GLint loc, GLfloat* m )
{
	glUniformMatrix4fv(loc, 1, GL_FALSE, m);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniformMatrix3fv( const char *name, GLfloat* m )
{
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, m);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniformMatrix3fv( GLint loc, GLfloat* m )
{
	glUniformMatrix3fv(loc, 1, GL_FALSE, m);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform1i( const char *name, GLint i)
{
	glUniform1i(getUniformLocation(name), i);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform1i(GLint loc, GLint i)
{
	glUniform1i(loc, i);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform1iv( const char *name, GLint count, GLint* i)
{
	glUniform1iv(getUniformLocation(name), count, i);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform1iv( GLint loc, GLint count, GLint* i)
{
	glUniform1iv(loc, count, i);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform4fv( const char *name, GLint count, GLfloat *v )
{
	glUniform4fv(getUniformLocation(name), count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform4fv( GLint loc, GLint count, GLfloat *v )
{
	glUniform4fv(loc, count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform3fv( const char *name, GLint count, GLfloat *v )
{
	glUniform3fv(getUniformLocation(name), count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}

void ShaderProgram::setUniform3fv( GLint loc, GLint count, GLfloat *v )
{
	glUniform3fv(loc, count, v);
	OPENGLES_CHECK_GL_ERROR(glGetError(), __FILE__, __LINE__);
}
