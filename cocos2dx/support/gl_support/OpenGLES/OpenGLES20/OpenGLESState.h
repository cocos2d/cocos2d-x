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

#ifndef OpenGLState_H__
#define OpenGLState_H__

#include "Uniform.h"
#include <vector>
#include <map>

namespace OpenGLES {
	
	class OpenGLESImplementation;
	
	namespace OpenGLES2 {
		
		class ShaderProgram;
		class Attribute;
		class ShaderSource;
		class OpenGLTexture;
		
		// TODO: read from text file
		namespace ShaderId {
			enum {
				MAIN_VERTEX_SHADER,
				LIGHTING_VERTEX_SHADER,
				LIGHTING_PER_VERTEX_VERTEX_SHADER,
				LIGHTING_PER_FRAGMENT_VERTEX_SHADER,
				CLIP_PLANE_VERTEX_SHADER,
				TEXTURE_VERTEX_SHADER,
				TEXTURE0_VERTEX_SHADER,
				TEXTURE1_VERTEX_SHADER,
				TEXTURE2_VERTEX_SHADER,
				FOG_VERTEX_SHADER,
				
				MAIN_FRAGMENT_SHADER,
				LIGHTING_FRAGMENT_SHADER,
				LIGHTING_PER_FRAGMENT_FRAGMENT_SHADER,
				ALPHA_TEST_FRAGMENT_SHADER,
				CLIP_PLANE_FRAGMENT_SHADER,
				TEXTURE_FRAGMENT_SHADER,
				TEXTURE0_FRAGMENT_SHADER,
				TEXTURE1_FRAGMENT_SHADER,
				TEXTURE2_FRAGMENT_SHADER,
				FOG_FRAGMENT_SHADER,
				
				FIRST_VERTEX_SHADER = MAIN_VERTEX_SHADER,
				LAST_VERTEX_SHADER = FOG_VERTEX_SHADER,
				FIRST_FRAGMENT_SHADER = MAIN_FRAGMENT_SHADER,
				LAST_FRAGMENT_SHADER = FOG_FRAGMENT_SHADER,
				COUNT
			};
		}
		
		// TODO: read from text file
		namespace AttributeId {
			enum {
				POSITION,
				NORMAL,
				COLOR,
				TEXCOORD0,
				TEXCOORD1,
				TEXCOORD2,
				COUNT
			};
		}
		
		// TODO: read from text file
		namespace UniformId {
			enum {
				POSITION_ENABLED,
				NORMAL_ENABLED,
				COLOR_ENABLED,
				TEXCOORD0_ENABLED,
				TEXCOORD1_ENABLED,
				TEXCOORD2_ENABLED,
				LIGHTING_ENABLED,
				LIGHT_MODEL_LOCAL_VIEWER_ENABLED,
				LIGHT_MODEL_TWO_SIDE_ENABLED,
				LIGHT0_ENABLED,
				LIGHT1_ENABLED,
				LIGHT2_ENABLED,
				TEXTURE0_ENABLED,
				TEXTURE1_ENABLED,
				TEXTURE2_ENABLED,
				TEXTURE0_MATRIX_ENABLED,
				TEXTURE1_MATRIX_ENABLED,
				TEXTURE2_MATRIX_ENABLED,
				FOG_ENABLED,
				ALPHA_TEST_ENABLED,
				CLIP_PLANE0_ENABLED,
				CLIP_PLANE1_ENABLED,
				CLIP_PLANE2_ENABLED,
				CLIP_PLANE3_ENABLED,
				CLIP_PLANE4_ENABLED,
				CLIP_PLANE5_ENABLED,
				RESCALE_NORMAL_ENABLED,
				NORMALIZE_ENABLED,
				
				FOG_MODE,
				FOG_HINT,
				ALPHA_FUNC,
				TEXTURE0_FORMAT,
				TEXTURE1_FORMAT,
				TEXTURE2_FORMAT,
				TEXTURE0_ENV_MODE,
				TEXTURE1_ENV_MODE,
				TEXTURE2_ENV_MODE,
				TEXTURE0_ENV_COMBINE_RGB,
				TEXTURE1_ENV_COMBINE_RGB,
				TEXTURE2_ENV_COMBINE_RGB,
				TEXTURE0_ENV_COMBINE_ALPHA,
				TEXTURE1_ENV_COMBINE_ALPHA,
				TEXTURE2_ENV_COMBINE_ALPHA,
				TEXTURE0_ENV_SRC0_RGB,
				TEXTURE0_ENV_SRC1_RGB,
				TEXTURE0_ENV_SRC2_RGB,
				TEXTURE1_ENV_SRC0_RGB,
				TEXTURE1_ENV_SRC1_RGB,
				TEXTURE1_ENV_SRC2_RGB,
				TEXTURE2_ENV_SRC0_RGB,
				TEXTURE2_ENV_SRC1_RGB,
				TEXTURE2_ENV_SRC2_RGB,
				TEXTURE0_ENV_OPERAND0_RGB,
				TEXTURE0_ENV_OPERAND1_RGB,
				TEXTURE0_ENV_OPERAND2_RGB,
				TEXTURE1_ENV_OPERAND0_RGB,
				TEXTURE1_ENV_OPERAND1_RGB,
				TEXTURE1_ENV_OPERAND2_RGB,
				TEXTURE2_ENV_OPERAND0_RGB,
				TEXTURE2_ENV_OPERAND1_RGB,
				TEXTURE2_ENV_OPERAND2_RGB,
				TEXTURE0_ENV_SRC0_ALPHA,
				TEXTURE0_ENV_SRC1_ALPHA,
				TEXTURE0_ENV_SRC2_ALPHA,
				TEXTURE1_ENV_SRC0_ALPHA,
				TEXTURE1_ENV_SRC1_ALPHA,
				TEXTURE1_ENV_SRC2_ALPHA,
				TEXTURE2_ENV_SRC0_ALPHA,
				TEXTURE2_ENV_SRC1_ALPHA,
				TEXTURE2_ENV_SRC2_ALPHA,
				TEXTURE0_ENV_OPERAND0_ALPHA,
				TEXTURE0_ENV_OPERAND1_ALPHA,
				TEXTURE0_ENV_OPERAND2_ALPHA,
				TEXTURE1_ENV_OPERAND0_ALPHA,
				TEXTURE1_ENV_OPERAND1_ALPHA,
				TEXTURE1_ENV_OPERAND2_ALPHA,
				TEXTURE2_ENV_OPERAND0_ALPHA,
				TEXTURE2_ENV_OPERAND1_ALPHA,
				TEXTURE2_ENV_OPERAND2_ALPHA,
				LIGHTING_HINT,
				
				MODELVIEW_PROJECTION_MATRIX,
				MODELVIEW_MATRIX,
				TRANPOSE_ADJOINT_MODEL_VIEW_MATRIX,
				TEXTURE0_MATRIX,
				TEXTURE1_MATRIX,
				TEXTURE2_MATRIX,
				TEXTURE0_SAMPLER,
				TEXTURE1_SAMPLER,
				TEXTURE2_SAMPLER,
				TEXTURE0_ENV_COLOR,
				TEXTURE1_ENV_COLOR,
				TEXTURE2_ENV_COLOR,
				TEXTURE0_ENV_RGB_SCALE,
				TEXTURE1_ENV_RGB_SCALE,
				TEXTURE2_ENV_RGB_SCALE,
				TEXTURE0_ENV_ALPHA_SCALE,
				TEXTURE1_ENV_ALPHA_SCALE,
				TEXTURE2_ENV_ALPHA_SCALE,
				TEXTURE0_ENV_BLUR_AMOUNT,
				TEXTURE1_ENV_BLUR_AMOUNT,
				TEXTURE2_ENV_BLUR_AMOUNT,
				RESCALE_NORMAL_FACTOR,
				LIGHT0_AMBIENT,
				LIGHT1_AMBIENT,
				LIGHT2_AMBIENT,
				LIGHT0_DIFFUSE,
				LIGHT1_DIFFUSE,
				LIGHT2_DIFFUSE,
				LIGHT0_SPECULAR,
				LIGHT1_SPECULAR,
				LIGHT2_SPECULAR,
				LIGHT0_POSITION,
				LIGHT1_POSITION,
				LIGHT2_POSITION,
				LIGHT0_SPOT_DIRECTION,
				LIGHT1_SPOT_DIRECTION,
				LIGHT2_SPOT_DIRECTION,
				LIGHT0_SPOT_EXPONENT,
				LIGHT1_SPOT_EXPONENT,
				LIGHT2_SPOT_EXPONENT,
				LIGHT0_SPOT_CUTOFF_ANGLE_COS,
				LIGHT1_SPOT_CUTOFF_ANGLE_COS,
				LIGHT2_SPOT_CUTOFF_ANGLE_COS,
				LIGHT0_CONSTANT_ATTENUATION,
				LIGHT1_CONSTANT_ATTENUATION,
				LIGHT2_CONSTANT_ATTENUATION,
				LIGHT0_LINEAR_ATTENUATION,
				LIGHT1_LINEAR_ATTENUATION,
				LIGHT2_LINEAR_ATTENUATION,
				LIGHT0_QUADRATIC_ATTENUATION,
				LIGHT1_QUADRATIC_ATTENUATION,
				LIGHT2_QUADRATIC_ATTENUATION,
				MATERIAL_AMBIENT,
				MATERIAL_DIFFUSE,
				MATERIAL_SPECULAR,
				MATERIAL_EMISSION,
				MATERIAL_SHININESS,
				FOG_COLOR,
				FOG_DENSITY,
				FOG_START,
				FOG_END,
				ALPHA_FUNC_VALUE,
				CLIP_PLANE0_EQUATION,
				CLIP_PLANE1_EQUATION,
				CLIP_PLANE2_EQUATION,
				CLIP_PLANE3_EQUATION,
				CLIP_PLANE4_EQUATION,
				CLIP_PLANE5_EQUATION,
				GLOBAL_AMBIENT_COLOR,
				
				FIRST_STATE_UNIFORM_BOOL = POSITION_ENABLED,
				LAST_STATE_UNIFORM_BOOL = NORMALIZE_ENABLED,
				FIRST_STATE_UNIFORM_INT = FOG_MODE,
				LAST_STATE_UNIFORM_INT = LIGHTING_HINT,
				FIRST_NORMAL_UNIFORM = MODELVIEW_PROJECTION_MATRIX,
				LAST_NORMAL_UNIFORM = GLOBAL_AMBIENT_COLOR,
				COUNT,
				STATE_UNIFORM_BOOL_COUNT = LAST_STATE_UNIFORM_BOOL - FIRST_STATE_UNIFORM_BOOL + 1,
				STATE_UNIFORM_INT_COUNT = LAST_STATE_UNIFORM_INT - FIRST_STATE_UNIFORM_INT + 1
			};
		}
		
		/*namespace UniformId {
		 enum {
		 POSITION_ENABLED,
		 NORMAL_ENABLED,
		 COLOR_ENABLED,
		 TEXCOORD0_ENABLED,
		 TEXCOORD1_ENABLED,
		 TEXCOORD2_ENABLED,
		 LIGHT_MODEL_LOCAL_VIEWER_ENABLED,
		 LIGHT_MODEL_TWO_SIDE_ENABLED,
		 TEXTURE0_ENABLED,
		 TEXTURE1_ENABLED,
		 TEXTURE2_ENABLED,
		 TEXTURE0_MATRIX_ENABLED,
		 TEXTURE1_MATRIX_ENABLED,
		 TEXTURE2_MATRIX_ENABLED,
		 ALPHA_TEST_ENABLED,
		 RESCALE_NORMAL_ENABLED,
		 NORMALIZE_ENABLED,
		 
		 FOG_HINT,
		 ALPHA_FUNC,
		 TEXTURE0_FORMAT,
		 TEXTURE1_FORMAT,
		 TEXTURE2_FORMAT,
		 TEXTURE0_ENV_MODE,
		 TEXTURE1_ENV_MODE,
		 TEXTURE2_ENV_MODE,
		 TEXTURE0_ENV_COMBINE_RGB,
		 TEXTURE1_ENV_COMBINE_RGB,
		 TEXTURE2_ENV_COMBINE_RGB,
		 TEXTURE0_ENV_COMBINE_ALPHA,
		 TEXTURE1_ENV_COMBINE_ALPHA,
		 TEXTURE2_ENV_COMBINE_ALPHA,
		 TEXTURE0_ENV_SRC0_RGB,
		 TEXTURE0_ENV_SRC1_RGB,
		 TEXTURE0_ENV_SRC2_RGB,
		 TEXTURE1_ENV_SRC0_RGB,
		 TEXTURE1_ENV_SRC1_RGB,
		 TEXTURE1_ENV_SRC2_RGB,
		 TEXTURE2_ENV_SRC0_RGB,
		 TEXTURE2_ENV_SRC1_RGB,
		 TEXTURE2_ENV_SRC2_RGB,
		 TEXTURE0_ENV_OPERAND0_RGB,
		 TEXTURE0_ENV_OPERAND1_RGB,
		 TEXTURE0_ENV_OPERAND2_RGB,
		 TEXTURE1_ENV_OPERAND0_RGB,
		 TEXTURE1_ENV_OPERAND1_RGB,
		 TEXTURE1_ENV_OPERAND2_RGB,
		 TEXTURE2_ENV_OPERAND0_RGB,
		 TEXTURE2_ENV_OPERAND1_RGB,
		 TEXTURE2_ENV_OPERAND2_RGB,
		 TEXTURE0_ENV_SRC0_ALPHA,
		 TEXTURE0_ENV_SRC1_ALPHA,
		 TEXTURE0_ENV_SRC2_ALPHA,
		 TEXTURE1_ENV_SRC0_ALPHA,
		 TEXTURE1_ENV_SRC1_ALPHA,
		 TEXTURE1_ENV_SRC2_ALPHA,
		 TEXTURE2_ENV_SRC0_ALPHA,
		 TEXTURE2_ENV_SRC1_ALPHA,
		 TEXTURE2_ENV_SRC2_ALPHA,
		 TEXTURE0_ENV_OPERAND0_ALPHA,
		 TEXTURE0_ENV_OPERAND1_ALPHA,
		 TEXTURE0_ENV_OPERAND2_ALPHA,
		 TEXTURE1_ENV_OPERAND0_ALPHA,
		 TEXTURE1_ENV_OPERAND1_ALPHA,
		 TEXTURE1_ENV_OPERAND2_ALPHA,
		 TEXTURE2_ENV_OPERAND0_ALPHA,
		 TEXTURE2_ENV_OPERAND1_ALPHA,
		 TEXTURE2_ENV_OPERAND2_ALPHA,
		 LIGHTING_HINT,
		 
		 MODELVIEW_PROJECTION_MATRIX,
		 MODELVIEW_MATRIX,
		 TRANPOSE_ADJOINT_MODEL_VIEW_MATRIX,
		 LIGHTING_ENABLED,
		 LIGHT0_ENABLED,
		 LIGHT1_ENABLED,
		 LIGHT2_ENABLED,
		 FOG_MODE,
		 FOG_ENABLED,
		 TEXTURE0_MATRIX,
		 TEXTURE1_MATRIX,
		 TEXTURE2_MATRIX,
		 TEXTURE0_SAMPLER,
		 TEXTURE1_SAMPLER,
		 TEXTURE2_SAMPLER,
		 TEXTURE0_ENV_COLOR,
		 TEXTURE1_ENV_COLOR,
		 TEXTURE2_ENV_COLOR,
		 TEXTURE0_ENV_RGB_SCALE,
		 TEXTURE1_ENV_RGB_SCALE,
		 TEXTURE2_ENV_RGB_SCALE,
		 TEXTURE0_ENV_ALPHA_SCALE,
		 TEXTURE1_ENV_ALPHA_SCALE,
		 TEXTURE2_ENV_ALPHA_SCALE,
		 TEXTURE0_ENV_BLUR_AMOUNT,
		 TEXTURE1_ENV_BLUR_AMOUNT,
		 TEXTURE2_ENV_BLUR_AMOUNT,
		 RESCALE_NORMAL_FACTOR,
		 LIGHT0_AMBIENT,
		 LIGHT1_AMBIENT,
		 LIGHT2_AMBIENT,
		 LIGHT0_DIFFUSE,
		 LIGHT1_DIFFUSE,
		 LIGHT2_DIFFUSE,
		 LIGHT0_SPECULAR,
		 LIGHT1_SPECULAR,
		 LIGHT2_SPECULAR,
		 LIGHT0_POSITION,
		 LIGHT1_POSITION,
		 LIGHT2_POSITION,
		 LIGHT0_SPOT_DIRECTION,
		 LIGHT1_SPOT_DIRECTION,
		 LIGHT2_SPOT_DIRECTION,
		 LIGHT0_SPOT_EXPONENT,
		 LIGHT1_SPOT_EXPONENT,
		 LIGHT2_SPOT_EXPONENT,
		 LIGHT0_SPOT_CUTOFF_ANGLE_COS,
		 LIGHT1_SPOT_CUTOFF_ANGLE_COS,
		 LIGHT2_SPOT_CUTOFF_ANGLE_COS,
		 LIGHT0_CONSTANT_ATTENUATION,
		 LIGHT1_CONSTANT_ATTENUATION,
		 LIGHT2_CONSTANT_ATTENUATION,
		 LIGHT0_LINEAR_ATTENUATION,
		 LIGHT1_LINEAR_ATTENUATION,
		 LIGHT2_LINEAR_ATTENUATION,
		 LIGHT0_QUADRATIC_ATTENUATION,
		 LIGHT1_QUADRATIC_ATTENUATION,
		 LIGHT2_QUADRATIC_ATTENUATION,
		 CLIP_PLANE0_ENABLED,
		 CLIP_PLANE1_ENABLED,
		 CLIP_PLANE2_ENABLED,
		 CLIP_PLANE3_ENABLED,
		 CLIP_PLANE4_ENABLED,
		 CLIP_PLANE5_ENABLED,
		 MATERIAL_AMBIENT,
		 MATERIAL_DIFFUSE,
		 MATERIAL_SPECULAR,
		 MATERIAL_EMISSION,
		 MATERIAL_SHININESS,
		 FOG_COLOR,
		 FOG_DENSITY,
		 FOG_START,
		 FOG_END,
		 ALPHA_FUNC_VALUE,
		 CLIP_PLANE0_EQUATION,
		 CLIP_PLANE1_EQUATION,
		 CLIP_PLANE2_EQUATION,
		 CLIP_PLANE3_EQUATION,
		 CLIP_PLANE4_EQUATION,
		 CLIP_PLANE5_EQUATION,
		 GLOBAL_AMBIENT_COLOR,
		 
		 FIRST_STATE_UNIFORM_BOOL = POSITION_ENABLED,
		 LAST_STATE_UNIFORM_BOOL = NORMALIZE_ENABLED,
		 FIRST_STATE_UNIFORM_INT = FOG_HINT,
		 LAST_STATE_UNIFORM_INT = LIGHTING_HINT,
		 FIRST_NORMAL_UNIFORM = MODELVIEW_PROJECTION_MATRIX,
		 LAST_NORMAL_UNIFORM = GLOBAL_AMBIENT_COLOR,
		 COUNT,
		 STATE_UNIFORM_BOOL_COUNT = LAST_STATE_UNIFORM_BOOL - FIRST_STATE_UNIFORM_BOOL + 1,
		 STATE_UNIFORM_INT_COUNT = LAST_STATE_UNIFORM_INT - FIRST_STATE_UNIFORM_INT + 1
		 };
		 }*/
		
		
		class StateShaderProgram {
		public:
			StateShaderProgram(unsigned int *state, ShaderProgram *program) : state(state), shaderProgram(program)
			{
				
			}
			
			~StateShaderProgram()
			{
				delete shaderProgram;
			}
			
			unsigned int *state;
			ShaderProgram *shaderProgram;
		};
		
		class OpenGLESState {
		public:
			OpenGLESState();
			~OpenGLESState();
			
			void init(OpenGLESImplementation *implementation);
			void setCurrentProgram();
			
			void setActiveTexture(int a);
			int getActiveTexture();
			void setClientActiveTexture(int a);
			int getClientActiveTexture();
			void setBoundTextureFormat(int format);
			void setBoundTexture(int i);
			
			void setPosition(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
			void setNormal(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
			void setColor(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
			void setTexCoord(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
			
			void setPosition(bool enabled);
			void setNormal(bool enabled);
			bool isNormal();
			void setColor(bool enabled);
			void setTexCoord(bool enabled);
			bool isTexCoord(int index);
			void setTexture(bool enabled);
			void setTextureFormat();
			void setTextureEnvMode(GLint val);
			void setTextureEnvColor(Vector4<GLfloat> vec);
			void setTextureEnvCombineRGB(GLint val);
			void setTextureEnvCombineAlpha(GLint val);
			void setTextureEnvSrcRGB(int index, GLint val);
			void setTextureEnvOperandRGB(int index, GLint val);
			void setTextureEnvSrcAlpha(int index, GLint val);
			void setTextureEnvOperandAlpha(int index, GLint val);
			void setTextureEnvRGBScale(GLfloat val);
			void setTextureEnvAlphaScale(GLfloat val);
			void setTextureEnvBlurAmount(GLfloat val);
			void setLightModelLocalViewer(bool enabled);
			void setLightModelTwoSide(bool enabled);
			void setLighting(bool enabled);
			void setLightingHint(GLint val);
			void setLight(GLenum light, bool enabled);
			void setLightAmbient(GLenum light, Vector4<GLfloat> vec);
			void setLightDiffuse(GLenum light, Vector4<GLfloat> vec);
			void setLightSpecular(GLenum light, Vector4<GLfloat> vec);
			void setLightPosition(GLenum light, Vector4<GLfloat> vec);
			void setLightSpotDirection(GLenum light, Vector3<GLfloat> vec);
			void setLightSpotExponent(GLenum light, GLfloat vec);
			void setLightSpotCutoffAngleCos(GLenum light, GLfloat vec);
			void setLightConstantAttenuation(GLenum light, GLfloat vec);
			void setLightLinearAttenuation(GLenum light, GLfloat vec);
			void setLightQuadraticAttenuation(GLenum light, GLfloat vec);
			void setMaterialAmbient(Vector4<GLfloat> vec);
			void setMaterialDiffuse(Vector4<GLfloat> vec);
			void setMaterialSpecular(Vector4<GLfloat> vec);
			void setMaterialEmission(Vector4<GLfloat> vec);
			void setMaterialShininess(GLfloat val);
			void setModelViewMatrix( Matrix4x4<GLfloat> mat );
			void setModelViewProjectionMatrix( Matrix4x4<GLfloat> mat );
			void setTransposeAdjointModelViewMatrix( Matrix3x3<GLfloat> mat);
			void setNormalize(bool enabled);
			void setRescaleNormal(bool enabled);
			bool isRescaleNormal();
			void setRescaleNormalFactor(GLfloat val);
			void setGlobalAmbientColor(Vector4<GLfloat> vec);
			void setFog(bool enabled);
			void setFogColor(Vector3<GLfloat> vec);
			void setFogMode(GLint val);
			void setFogDensity(GLfloat val);
			void setFogStart(GLfloat val);
			void setFogEnd(GLfloat val);
			void setFogHint(GLint val);
			void setAlphaTest(bool enabled);
			void setAlphaFunc(GLint val);
			void setAlphaFuncValue(GLfloat val);
			void setClipPlane(GLenum clipPlaneIndex, bool enabled);
			void setClipPlane(GLenum clipPlaneIndex, Vector4<GLfloat> vec);
			void getClipPlane(GLenum clipPlaneIndex, GLfloat eqn[4]);
			void setTextureMatrix(int index, Matrix4x4<GLfloat> mat);
			void setTextureMatrix(int index, bool enabled);
			
			int getCachedShaderAmount();
			
		private:
			void setActiveUniformLocations(std::vector<UniformSimple *> *activeUniforms);
			void setActiveAttributeLocations(std::vector<AttributeSimple *> *activeAttributes);
			void uploadAttributes();
			void uploadUniforms();
			void addRequiredShaderSources(std::vector<ShaderSource *> &vertexShaderSources, std::vector<ShaderSource *> &fragmentShaderSources);
			void addDefinesToShaderSources(std::vector<ShaderSource *> &vertexShaderSources, std::vector<ShaderSource *> &fragmentShaderSources);
			void addDefineToShaderSources(std::string define, std::vector<ShaderFile *> &shaderFiles, std::vector<ShaderSource *> &vertexShaderSources, std::vector<ShaderSource * > &fragmentShaderSources );
			unsigned int* getCopyOfCurrentState();
			
			UniformBase *uniforms[UniformId::COUNT];
			Attribute *attributes[AttributeId::COUNT];
			ShaderFile *shaders[ShaderId::COUNT];
			std::vector<StateShaderProgram *> stateShaderPrograms;
			StateShaderProgram *currentStateShaderProgram;
			unsigned int stateSize;
			unsigned int stateSizeBool;
			unsigned int currentState[1 + (UniformId::STATE_UNIFORM_BOOL_COUNT / 32) + UniformId::STATE_UNIFORM_INT_COUNT];
			unsigned int activeTexture;
			unsigned int clientActiveTexture;
			std::map<GLuint, GLint> boundTextureFormats;
			unsigned int *boundTextures;
		};
	}
}

#endif
