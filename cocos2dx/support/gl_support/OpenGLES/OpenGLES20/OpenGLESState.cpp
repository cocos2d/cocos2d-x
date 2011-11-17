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

#include "OpenGLESState.h"
#include "OpenGLESContext.h"
#include "OpenGLESConfig.h"
#include "Attribute.h"
#include "Uniform.h"
#include "ShaderSource.h"
#include "Shader.h"
#include "OpenGLESImplementation.h"

using namespace OpenGLES;
using namespace OpenGLES::OpenGLES2;

OpenGLESState::OpenGLESState() : stateShaderPrograms(), currentStateShaderProgram(0), stateSize(1 + (UniformId::STATE_UNIFORM_BOOL_COUNT / 32) + UniformId::STATE_UNIFORM_INT_COUNT), stateSizeBool(1 + (UniformId::STATE_UNIFORM_BOOL_COUNT / 32)), activeTexture(0), clientActiveTexture(0)
{
	
}

OpenGLESState::~OpenGLESState()
{
	for (unsigned int i = 0; i < UniformId::COUNT; i++) {
		delete uniforms[i];
	}
	
	for (unsigned int i = 0; i < AttributeId::COUNT; i++) {
		delete attributes[i];
	}
	
	for (unsigned int i = 0; i < ShaderId::COUNT; i++) {
		delete shaders[i];
	}
	
	for (size_t i = 0; i < stateShaderPrograms.size(); i++) {
		delete stateShaderPrograms[i];
	}
	
	delete [] boundTextures;
}

void OpenGLESState::init(OpenGLESImplementation *implementation)
{	
	for (unsigned int i = 0; i < stateSize; i++) {
		currentState[i] = 0;
	}
	
	boundTextures = new GLuint[implementation->maxTextureImageUnits];
	for (unsigned int i = 0; i < implementation->maxTextureImageUnits; i++)
	{
		boundTextures[i] = 0;
	}
	
	
	// TODO: Read all the following from text file
	
	shaders[ShaderId::MAIN_VERTEX_SHADER] = new ShaderFile(GL_VERTEX_SHADER, "main.vert");
	shaders[ShaderId::LIGHTING_VERTEX_SHADER] = new ShaderFile(GL_VERTEX_SHADER, "lighting.vert");
	shaders[ShaderId::LIGHTING_PER_VERTEX_VERTEX_SHADER] = new ShaderFile(GL_VERTEX_SHADER, "lightingPerVertex.vert");
	shaders[ShaderId::LIGHTING_PER_FRAGMENT_VERTEX_SHADER] = new ShaderFile(GL_VERTEX_SHADER, "lightingPerFragment.vert");
	shaders[ShaderId::FOG_VERTEX_SHADER] = new ShaderFile(GL_VERTEX_SHADER, "fog.glsl");
	shaders[ShaderId::CLIP_PLANE_VERTEX_SHADER] = new ShaderFile(GL_VERTEX_SHADER, "clipPlane.vert");
	shaders[ShaderId::TEXTURE_VERTEX_SHADER] = new ShaderFile(GL_VERTEX_SHADER, "texture.vert");
	shaders[ShaderId::TEXTURE0_VERTEX_SHADER] = new ShaderFile(GL_VERTEX_SHADER, "texture0.vert");
	shaders[ShaderId::TEXTURE1_VERTEX_SHADER] = new ShaderFile(GL_VERTEX_SHADER, "texture1.vert");
	shaders[ShaderId::TEXTURE2_VERTEX_SHADER] = new ShaderFile(GL_VERTEX_SHADER, "texture2.vert");
	
	shaders[ShaderId::MAIN_FRAGMENT_SHADER] = new ShaderFile(GL_FRAGMENT_SHADER, "main.frag");
	shaders[ShaderId::LIGHTING_FRAGMENT_SHADER] = new ShaderFile(GL_FRAGMENT_SHADER, "lighting.frag");
	shaders[ShaderId::LIGHTING_PER_FRAGMENT_FRAGMENT_SHADER] = new ShaderFile(GL_FRAGMENT_SHADER, "lightingPerFragment.frag");
	shaders[ShaderId::FOG_FRAGMENT_SHADER] = new ShaderFile(GL_FRAGMENT_SHADER, "fog.glsl");
	shaders[ShaderId::ALPHA_TEST_FRAGMENT_SHADER] = new ShaderFile(GL_FRAGMENT_SHADER, "alphaTest.frag");
	shaders[ShaderId::CLIP_PLANE_FRAGMENT_SHADER] = new ShaderFile(GL_FRAGMENT_SHADER, "clipPlane.frag");
	shaders[ShaderId::TEXTURE_FRAGMENT_SHADER] = new ShaderFile(GL_FRAGMENT_SHADER, "texture.frag");
	shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER] = new ShaderFile(GL_FRAGMENT_SHADER, "texture0.frag");
	shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER] = new ShaderFile(GL_FRAGMENT_SHADER, "texture1.frag");
	shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER] = new ShaderFile(GL_FRAGMENT_SHADER, "texture2.frag");
	
	attributes[AttributeId::POSITION] = new Attribute();
	attributes[AttributeId::NORMAL] = new Attribute();
	attributes[AttributeId::COLOR] = new Attribute();
	attributes[AttributeId::TEXCOORD0] = new Attribute();
	attributes[AttributeId::TEXCOORD1] = new Attribute();
	attributes[AttributeId::TEXCOORD2] = new Attribute();
	
	
	// Bool uniforms with defines
	
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::POSITION_ENABLED && UniformId::POSITION_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		uniforms[UniformId::POSITION_ENABLED] = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "POSITION_ENABLED", false);
	} else {
		uniforms[UniformId::POSITION_ENABLED] = new Uniform<bool>(false);
	}
	
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::COLOR_ENABLED && UniformId::COLOR_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		uniforms[UniformId::COLOR_ENABLED] = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "COLOR_ENABLED", false);
	} else {
		uniforms[UniformId::COLOR_ENABLED] = new Uniform<bool>(false);
	}
	
	UniformState<bool> *texcoord0Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::TEXCOORD0_ENABLED && UniformId::TEXCOORD0_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		texcoord0Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "TEXCOORD0_ENABLED", false);
		texcoord0Enabled->addDefineShaderFile(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER]);
		uniforms[UniformId::TEXCOORD0_ENABLED] = texcoord0Enabled;
	} else {
		uniforms[UniformId::TEXCOORD0_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::TEXCOORD0_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE_VERTEX_SHADER]);
	uniforms[UniformId::TEXCOORD0_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE0_VERTEX_SHADER]);
	
	UniformState<bool> *texcoord1Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::TEXCOORD1_ENABLED && UniformId::TEXCOORD1_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		texcoord1Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "TEXCOORD1_ENABLED", false);
		texcoord1Enabled->addDefineShaderFile(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER]);
		uniforms[UniformId::TEXCOORD1_ENABLED] = texcoord1Enabled;
	} else {
		uniforms[UniformId::TEXCOORD1_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::TEXCOORD1_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE_VERTEX_SHADER]);
	uniforms[UniformId::TEXCOORD1_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE1_VERTEX_SHADER]);
	
	UniformState<bool> *texcoord2Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::TEXCOORD2_ENABLED && UniformId::TEXCOORD2_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		texcoord2Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "TEXCOORD2_ENABLED", false);
		texcoord2Enabled->addDefineShaderFile(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER]);
		uniforms[UniformId::TEXCOORD2_ENABLED] = texcoord2Enabled;
	} else {
		uniforms[UniformId::TEXCOORD2_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::TEXCOORD2_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE_VERTEX_SHADER]);
	uniforms[UniformId::TEXCOORD2_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE2_VERTEX_SHADER]);
	
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::TEXTURE0_MATRIX_ENABLED && UniformId::TEXTURE0_MATRIX_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		uniforms[UniformId::TEXTURE0_MATRIX_ENABLED] = new UniformState<bool>(shaders[ShaderId::TEXTURE_VERTEX_SHADER], "TEXTURE0_MATRIX_ENABLED", false);
	} else {
		uniforms[UniformId::TEXTURE0_MATRIX_ENABLED] = new Uniform<bool>(false);
	}
	
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::TEXTURE1_MATRIX_ENABLED && UniformId::TEXTURE1_MATRIX_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		uniforms[UniformId::TEXTURE1_MATRIX_ENABLED] = new UniformState<bool>(shaders[ShaderId::TEXTURE_VERTEX_SHADER], "TEXTURE1_MATRIX_ENABLED", false);
	} else {
		uniforms[UniformId::TEXTURE1_MATRIX_ENABLED] = new Uniform<bool>(false);
	}
	
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::TEXTURE2_MATRIX_ENABLED && UniformId::TEXTURE2_MATRIX_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		uniforms[UniformId::TEXTURE2_MATRIX_ENABLED] = new UniformState<bool>(shaders[ShaderId::TEXTURE_VERTEX_SHADER], "TEXTURE2_MATRIX_ENABLED", false);
	} else {
		uniforms[UniformId::TEXTURE2_MATRIX_ENABLED] = new Uniform<bool>(false);
	}
	
	UniformState<bool> *lightingEnabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::LIGHTING_ENABLED && UniformId::LIGHTING_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		lightingEnabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "LIGHTING_ENABLED", false);
		lightingEnabled->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::LIGHTING_ENABLED] = lightingEnabled;
	} else {
		uniforms[UniformId::LIGHTING_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::LIGHTING_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::LIGHTING_VERTEX_SHADER]);
	uniforms[UniformId::LIGHTING_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::LIGHTING_FRAGMENT_SHADER]);
	
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::LIGHT_MODEL_LOCAL_VIEWER_ENABLED && UniformId::LIGHT_MODEL_LOCAL_VIEWER_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		uniforms[UniformId::LIGHT_MODEL_LOCAL_VIEWER_ENABLED] = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "LIGHT_MODEL_LOCAL_VIEWER_ENABLED", false);
	} else {
		uniforms[UniformId::LIGHT_MODEL_LOCAL_VIEWER_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::LIGHT_MODEL_LOCAL_VIEWER_ENABLED]->setFather(lightingEnabled);
	
	UniformState<bool> *lightModelTwoSideEnabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::LIGHT_MODEL_TWO_SIDE_ENABLED && UniformId::LIGHT_MODEL_TWO_SIDE_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		lightModelTwoSideEnabled = new UniformState<bool>(shaders[ShaderId::LIGHTING_VERTEX_SHADER], "LIGHT_MODEL_TWO_SIDE_ENABLED", false);
		lightModelTwoSideEnabled->addDefineShaderFile(shaders[ShaderId::LIGHTING_FRAGMENT_SHADER]);
		uniforms[UniformId::LIGHT_MODEL_TWO_SIDE_ENABLED] = lightModelTwoSideEnabled;
	} else {
		uniforms[UniformId::LIGHT_MODEL_TWO_SIDE_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::LIGHT_MODEL_TWO_SIDE_ENABLED]->setFather(lightingEnabled);
	
	UniformState<bool> *light0Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::LIGHT0_ENABLED && UniformId::LIGHT0_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		light0Enabled = new UniformState<bool>(shaders[ShaderId::LIGHTING_VERTEX_SHADER], "LIGHT0_ENABLED", false);
		light0Enabled->addDefineShaderFile(shaders[ShaderId::LIGHTING_PER_FRAGMENT_FRAGMENT_SHADER]);
		uniforms[UniformId::LIGHT0_ENABLED] = light0Enabled;
	} else {
		uniforms[UniformId::LIGHT0_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::LIGHT0_ENABLED]->setFather(lightingEnabled);
	
	UniformState<bool> *light1Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::LIGHT1_ENABLED && UniformId::LIGHT1_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		light1Enabled = new UniformState<bool>(shaders[ShaderId::LIGHTING_VERTEX_SHADER], "LIGHT1_ENABLED", false);
		light1Enabled->addDefineShaderFile(shaders[ShaderId::LIGHTING_PER_FRAGMENT_FRAGMENT_SHADER]);
		uniforms[UniformId::LIGHT1_ENABLED] = light1Enabled;
	} else {
		uniforms[UniformId::LIGHT1_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::LIGHT1_ENABLED]->setFather(lightingEnabled);
	
	UniformState<bool> *light2Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::LIGHT2_ENABLED && UniformId::LIGHT2_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		light2Enabled = new UniformState<bool>(shaders[ShaderId::LIGHTING_VERTEX_SHADER], "LIGHT2_ENABLED", false);
		light2Enabled->addDefineShaderFile(shaders[ShaderId::LIGHTING_PER_FRAGMENT_FRAGMENT_SHADER]);
		uniforms[UniformId::LIGHT2_ENABLED] = light2Enabled;
	} else {
		uniforms[UniformId::LIGHT2_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::LIGHT2_ENABLED]->setFather(lightingEnabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::NORMAL_ENABLED && UniformId::NORMAL_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		uniforms[UniformId::NORMAL_ENABLED] = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "NORMAL_ENABLED", false);
	} else {
		uniforms[UniformId::NORMAL_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::NORMAL_ENABLED]->setFather(lightingEnabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::RESCALE_NORMAL_ENABLED && UniformId::RESCALE_NORMAL_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		uniforms[UniformId::RESCALE_NORMAL_ENABLED] = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "RESCALE_NORMAL_ENABLED", false);
	} else {
		uniforms[UniformId::RESCALE_NORMAL_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::RESCALE_NORMAL_ENABLED]->setFather(lightingEnabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::NORMALIZE_ENABLED && UniformId::NORMALIZE_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		uniforms[UniformId::NORMALIZE_ENABLED] = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "NORMALIZE_ENABLED", false);
	} else {
		uniforms[UniformId::NORMALIZE_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::NORMALIZE_ENABLED]->setFather(lightingEnabled);
	
	UniformState<bool> *fogEnabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::FOG_ENABLED && UniformId::FOG_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		fogEnabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "FOG_ENABLED", false);
		fogEnabled->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::FOG_ENABLED] = fogEnabled;
	} else {
		uniforms[UniformId::FOG_ENABLED] = new Uniform<bool>(false);
	}
	
	UniformState<bool> *texture0Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::TEXTURE0_ENABLED && UniformId::TEXTURE0_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		texture0Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "TEXTURE0_ENABLED", false);
		texture0Enabled->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::TEXTURE0_ENABLED] = texture0Enabled;
	} else {
		uniforms[UniformId::TEXTURE0_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::TEXTURE0_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE_FRAGMENT_SHADER]);
	uniforms[UniformId::TEXTURE0_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER]);
	
	UniformState<bool> *texture1Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::TEXTURE1_ENABLED && UniformId::TEXTURE1_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		texture1Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "TEXTURE1_ENABLED", false);
		texture1Enabled->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::TEXTURE1_ENABLED] = texture1Enabled;
	} else {
		uniforms[UniformId::TEXTURE1_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::TEXTURE1_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE_FRAGMENT_SHADER]);
	uniforms[UniformId::TEXTURE1_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER]);
	
	UniformState<bool> *texture2Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::TEXTURE2_ENABLED && UniformId::TEXTURE2_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		texture2Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "TEXTURE2_ENABLED", false);
		texture2Enabled->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::TEXTURE2_ENABLED] = texture2Enabled;
	} else {
		uniforms[UniformId::TEXTURE2_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::TEXTURE2_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE_FRAGMENT_SHADER]);
	uniforms[UniformId::TEXTURE2_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER]);
	
	UniformState<bool> *alphaTestEnabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::ALPHA_TEST_ENABLED && UniformId::ALPHA_TEST_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		alphaTestEnabled = new UniformState<bool>(shaders[ShaderId::MAIN_FRAGMENT_SHADER], "ALPHA_TEST_ENABLED", false);
		uniforms[UniformId::ALPHA_TEST_ENABLED] = alphaTestEnabled;
	} else {
		uniforms[UniformId::ALPHA_TEST_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::ALPHA_TEST_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::ALPHA_TEST_FRAGMENT_SHADER]);
	
	UniformState<bool> *clipPlane0Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::CLIP_PLANE0_ENABLED && UniformId::CLIP_PLANE0_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		clipPlane0Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "CLIP_PLANE0_ENABLED", false);
		clipPlane0Enabled->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::CLIP_PLANE0_ENABLED] = clipPlane0Enabled;
	} else {
		uniforms[UniformId::CLIP_PLANE0_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::CLIP_PLANE0_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_VERTEX_SHADER]);
	uniforms[UniformId::CLIP_PLANE0_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_FRAGMENT_SHADER]);
	
	UniformState<bool> *clipPlane1Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::CLIP_PLANE1_ENABLED && UniformId::CLIP_PLANE1_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		clipPlane1Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "CLIP_PLANE1_ENABLED", false);
		clipPlane1Enabled->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::CLIP_PLANE1_ENABLED] = clipPlane1Enabled;
	} else {
		uniforms[UniformId::CLIP_PLANE1_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::CLIP_PLANE1_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_VERTEX_SHADER]);
	uniforms[UniformId::CLIP_PLANE1_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_FRAGMENT_SHADER]);
	
	UniformState<bool> *clipPlane2Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::CLIP_PLANE2_ENABLED && UniformId::CLIP_PLANE2_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		clipPlane2Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "CLIP_PLANE2_ENABLED", false);
		clipPlane2Enabled->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::CLIP_PLANE2_ENABLED] = clipPlane2Enabled;
	} else {
		uniforms[UniformId::CLIP_PLANE2_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::CLIP_PLANE2_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_VERTEX_SHADER]);
	uniforms[UniformId::CLIP_PLANE2_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_FRAGMENT_SHADER]);
	
	UniformState<bool> *clipPlane3Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::CLIP_PLANE3_ENABLED && UniformId::CLIP_PLANE3_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		clipPlane3Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "CLIP_PLANE3_ENABLED", false);
		clipPlane3Enabled->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::CLIP_PLANE3_ENABLED] = clipPlane3Enabled;
	} else {
		uniforms[UniformId::CLIP_PLANE3_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::CLIP_PLANE3_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_VERTEX_SHADER]);
	uniforms[UniformId::CLIP_PLANE3_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_FRAGMENT_SHADER]);
	
	UniformState<bool> *clipPlane4Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::CLIP_PLANE4_ENABLED && UniformId::CLIP_PLANE4_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		clipPlane4Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "CLIP_PLANE4_ENABLED", false);
		clipPlane4Enabled->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::CLIP_PLANE4_ENABLED] = clipPlane4Enabled;
	} else {
		uniforms[UniformId::CLIP_PLANE4_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::CLIP_PLANE4_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_VERTEX_SHADER]);
	uniforms[UniformId::CLIP_PLANE4_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_FRAGMENT_SHADER]);
	
	UniformState<bool> *clipPlane5Enabled = 0;
	if (UniformId::FIRST_STATE_UNIFORM_BOOL <= UniformId::CLIP_PLANE5_ENABLED && UniformId::CLIP_PLANE5_ENABLED <= UniformId::LAST_STATE_UNIFORM_BOOL) {
		clipPlane5Enabled = new UniformState<bool>(shaders[ShaderId::MAIN_VERTEX_SHADER], "CLIP_PLANE5_ENABLED", false);
		clipPlane5Enabled->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::CLIP_PLANE5_ENABLED] = clipPlane5Enabled;
	} else {
		uniforms[UniformId::CLIP_PLANE5_ENABLED] = new Uniform<bool>(false);
	}
	uniforms[UniformId::CLIP_PLANE5_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_VERTEX_SHADER]);
	uniforms[UniformId::CLIP_PLANE5_ENABLED]->addAdditionalRequiredShaderFile(true, shaders[ShaderId::CLIP_PLANE_FRAGMENT_SHADER]);
	
	
	
	// Int uniforms with defines
	
	UniformState<int> *fogMode = 0;
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::FOG_MODE && UniformId::FOG_MODE <= UniformId::LAST_STATE_UNIFORM_INT) {
		fogMode = new UniformState<GLint>(shaders[ShaderId::MAIN_VERTEX_SHADER], "FOG_MODE", GL_EXP);
		fogMode->addDefineShaderFile(shaders[ShaderId::FOG_FRAGMENT_SHADER]);
		uniforms[UniformId::FOG_MODE] = fogMode;
	} else {
		uniforms[UniformId::FOG_MODE] = new Uniform<int>(GL_EXP);
	}
	uniforms[UniformId::FOG_MODE]->setFather(fogEnabled);
	
	UniformState<int> *fogHint = 0;
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::FOG_HINT && UniformId::FOG_HINT <= UniformId::LAST_STATE_UNIFORM_INT) {
		fogHint = new UniformState<GLint>(shaders[ShaderId::MAIN_VERTEX_SHADER], "FOG_HINT", GL_FASTEST);
		fogHint->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::FOG_HINT] = fogHint;
	} else {
		uniforms[UniformId::FOG_HINT] = new Uniform<int>(GL_FASTEST);
	}
	uniforms[UniformId::FOG_HINT]->addAdditionalRequiredShaderFile(GL_FASTEST, shaders[ShaderId::FOG_VERTEX_SHADER]);
	uniforms[UniformId::FOG_HINT]->addAdditionalRequiredShaderFile(GL_NICEST, shaders[ShaderId::FOG_FRAGMENT_SHADER]);
	uniforms[UniformId::FOG_HINT]->setFather(fogEnabled);
	
	UniformState<int> *lightingHint = 0;
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::LIGHTING_HINT && UniformId::LIGHTING_HINT <= UniformId::LAST_STATE_UNIFORM_INT) {
		lightingHint = new UniformState<GLint>(shaders[ShaderId::MAIN_VERTEX_SHADER], "LIGHTING_HINT", GL_FASTEST);
		lightingHint->addDefineShaderFile(shaders[ShaderId::MAIN_FRAGMENT_SHADER]);
		uniforms[UniformId::LIGHTING_HINT] = lightingHint;
	} else {
		uniforms[UniformId::LIGHTING_HINT] = new Uniform<int>(GL_FASTEST);
	}
	uniforms[UniformId::LIGHTING_HINT]->addAdditionalRequiredShaderFile(GL_FASTEST, shaders[ShaderId::LIGHTING_VERTEX_SHADER]);
	uniforms[UniformId::LIGHTING_HINT]->addAdditionalRequiredShaderFile(GL_FASTEST, shaders[ShaderId::LIGHTING_PER_VERTEX_VERTEX_SHADER]);
	uniforms[UniformId::LIGHTING_HINT]->addAdditionalRequiredShaderFile(GL_NICEST, shaders[ShaderId::LIGHTING_FRAGMENT_SHADER]);
	uniforms[UniformId::LIGHTING_HINT]->addAdditionalRequiredShaderFile(GL_NICEST, shaders[ShaderId::LIGHTING_PER_FRAGMENT_VERTEX_SHADER]);
	uniforms[UniformId::LIGHTING_HINT]->addAdditionalRequiredShaderFile(GL_NICEST, shaders[ShaderId::LIGHTING_PER_FRAGMENT_FRAGMENT_SHADER]);
	uniforms[UniformId::LIGHTING_HINT]->setFather(lightingEnabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::ALPHA_FUNC && UniformId::ALPHA_FUNC <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::ALPHA_FUNC] = new UniformState<GLint>(shaders[ShaderId::ALPHA_TEST_FRAGMENT_SHADER], "ALPHA_FUNC", GL_ALWAYS);
	} else {
		uniforms[UniformId::ALPHA_FUNC] = new Uniform<int>(GL_ALWAYS);
	}
	uniforms[UniformId::ALPHA_FUNC]->setFather(alphaTestEnabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_FORMAT && UniformId::TEXTURE0_FORMAT <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_FORMAT] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_FORMAT", GL_RGBA);
	} else {
		uniforms[UniformId::TEXTURE0_FORMAT] = new Uniform<int>(GL_RGBA);
	}
	uniforms[UniformId::TEXTURE0_FORMAT]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_FORMAT && UniformId::TEXTURE1_FORMAT <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_FORMAT] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_FORMAT", GL_RGBA);
	} else {
		uniforms[UniformId::TEXTURE1_FORMAT] = new Uniform<int>(GL_RGBA);
	}
	uniforms[UniformId::TEXTURE1_FORMAT]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_FORMAT && UniformId::TEXTURE2_FORMAT <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_FORMAT] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_FORMAT", GL_RGBA);
	} else {
		uniforms[UniformId::TEXTURE2_FORMAT] = new Uniform<int>(GL_RGBA);
	}
	uniforms[UniformId::TEXTURE2_FORMAT]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_MODE && UniformId::TEXTURE0_ENV_MODE <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_MODE] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_MODE", GL_MODULATE);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_MODE] = new Uniform<int>(GL_MODULATE);
	}
	uniforms[UniformId::TEXTURE0_ENV_MODE]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_MODE && UniformId::TEXTURE1_ENV_MODE <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_MODE] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_MODE", GL_MODULATE);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_MODE] = new Uniform<int>(GL_MODULATE);
	}
	uniforms[UniformId::TEXTURE1_ENV_MODE]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_MODE && UniformId::TEXTURE2_ENV_MODE <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_MODE] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_MODE", GL_MODULATE);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_MODE] = new Uniform<int>(GL_MODULATE);
	}
	uniforms[UniformId::TEXTURE2_ENV_MODE]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_COMBINE_RGB && UniformId::TEXTURE0_ENV_COMBINE_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_COMBINE_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_COMBINE_RGB", GL_MODULATE);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_COMBINE_RGB] = new Uniform<int>(GL_MODULATE);
	}
	uniforms[UniformId::TEXTURE0_ENV_COMBINE_RGB]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_COMBINE_RGB && UniformId::TEXTURE1_ENV_COMBINE_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_COMBINE_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_COMBINE_RGB", GL_MODULATE);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_COMBINE_RGB] = new Uniform<int>(GL_MODULATE);
	}
	uniforms[UniformId::TEXTURE1_ENV_COMBINE_RGB]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_COMBINE_RGB && UniformId::TEXTURE2_ENV_COMBINE_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_COMBINE_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_COMBINE_RGB", GL_MODULATE);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_COMBINE_RGB] = new Uniform<int>(GL_MODULATE);
	}
	uniforms[UniformId::TEXTURE2_ENV_COMBINE_RGB]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_COMBINE_ALPHA && UniformId::TEXTURE0_ENV_COMBINE_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_COMBINE_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_COMBINE_ALPHA", GL_MODULATE);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_COMBINE_ALPHA] = new Uniform<int>(GL_MODULATE);
	}
	uniforms[UniformId::TEXTURE0_ENV_COMBINE_ALPHA]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_COMBINE_ALPHA && UniformId::TEXTURE1_ENV_COMBINE_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_COMBINE_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_COMBINE_ALPHA", GL_MODULATE);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_COMBINE_ALPHA] = new Uniform<int>(GL_MODULATE);
	}
	uniforms[UniformId::TEXTURE1_ENV_COMBINE_ALPHA]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_COMBINE_ALPHA && UniformId::TEXTURE2_ENV_COMBINE_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_COMBINE_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_COMBINE_ALPHA", GL_MODULATE);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_COMBINE_ALPHA] = new Uniform<int>(GL_MODULATE);
	}
	uniforms[UniformId::TEXTURE2_ENV_COMBINE_ALPHA]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_SRC0_RGB && UniformId::TEXTURE0_ENV_SRC0_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_SRC0_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_SRC0_RGB", 0);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_SRC0_RGB] = new Uniform<int>(0);
	}
	uniforms[UniformId::TEXTURE0_ENV_SRC0_RGB]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_SRC1_RGB && UniformId::TEXTURE0_ENV_SRC1_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_SRC1_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_SRC1_RGB", GL_PREVIOUS);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_SRC1_RGB] = new Uniform<int>(GL_PREVIOUS);
	}
	uniforms[UniformId::TEXTURE0_ENV_SRC1_RGB]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_SRC2_RGB && UniformId::TEXTURE0_ENV_SRC2_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_SRC2_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_SRC2_RGB", GL_CONSTANT);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_SRC2_RGB] = new Uniform<int>(GL_CONSTANT);
	}
	uniforms[UniformId::TEXTURE0_ENV_SRC2_RGB]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_SRC0_RGB && UniformId::TEXTURE1_ENV_SRC0_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_SRC0_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_SRC0_RGB", 1);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_SRC0_RGB] = new Uniform<int>(1);
	}
	uniforms[UniformId::TEXTURE1_ENV_SRC0_RGB]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_SRC1_RGB && UniformId::TEXTURE1_ENV_SRC1_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_SRC1_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_SRC1_RGB", GL_PREVIOUS);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_SRC1_RGB] = new Uniform<int>(GL_PREVIOUS);
	}
	uniforms[UniformId::TEXTURE1_ENV_SRC1_RGB]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_SRC2_RGB && UniformId::TEXTURE1_ENV_SRC2_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_SRC2_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_SRC2_RGB", GL_CONSTANT);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_SRC2_RGB] = new Uniform<int>(GL_CONSTANT);
	}
	uniforms[UniformId::TEXTURE1_ENV_SRC2_RGB]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_SRC0_RGB && UniformId::TEXTURE2_ENV_SRC0_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_SRC0_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_SRC0_RGB", 2);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_SRC0_RGB] = new Uniform<int>(2);
	}
	uniforms[UniformId::TEXTURE2_ENV_SRC0_RGB]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_SRC1_RGB && UniformId::TEXTURE2_ENV_SRC1_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_SRC1_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_SRC1_RGB", GL_PREVIOUS);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_SRC1_RGB] = new Uniform<int>(GL_PREVIOUS);
	}
	uniforms[UniformId::TEXTURE2_ENV_SRC1_RGB]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_SRC2_RGB && UniformId::TEXTURE2_ENV_SRC2_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_SRC2_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_SRC2_RGB", GL_CONSTANT);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_SRC2_RGB] = new Uniform<int>(GL_CONSTANT);
	}
	uniforms[UniformId::TEXTURE2_ENV_SRC2_RGB]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_OPERAND0_RGB && UniformId::TEXTURE0_ENV_OPERAND0_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND0_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_OPERAND0_RGB", GL_SRC_COLOR);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND0_RGB] = new Uniform<int>(GL_SRC_COLOR);
	}
	uniforms[UniformId::TEXTURE0_ENV_OPERAND0_RGB]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_OPERAND1_RGB && UniformId::TEXTURE0_ENV_OPERAND1_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND1_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_OPERAND1_RGB", GL_SRC_COLOR);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND1_RGB] = new Uniform<int>(GL_SRC_COLOR);
	}
	uniforms[UniformId::TEXTURE0_ENV_OPERAND1_RGB]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_OPERAND2_RGB && UniformId::TEXTURE0_ENV_OPERAND2_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND2_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_OPERAND2_RGB", GL_SRC_COLOR);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND2_RGB] = new Uniform<int>(GL_SRC_COLOR);
	}
	uniforms[UniformId::TEXTURE0_ENV_OPERAND2_RGB]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_OPERAND0_RGB && UniformId::TEXTURE1_ENV_OPERAND0_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND0_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_OPERAND0_RGB", GL_SRC_COLOR);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND0_RGB] = new Uniform<int>(GL_SRC_COLOR);
	}
	uniforms[UniformId::TEXTURE1_ENV_OPERAND0_RGB]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_OPERAND1_RGB && UniformId::TEXTURE1_ENV_OPERAND1_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND1_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_OPERAND1_RGB", GL_SRC_COLOR);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND1_RGB] = new Uniform<int>(GL_SRC_COLOR);
	}
	uniforms[UniformId::TEXTURE1_ENV_OPERAND1_RGB]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_OPERAND2_RGB && UniformId::TEXTURE1_ENV_OPERAND2_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND2_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_OPERAND2_RGB", GL_SRC_COLOR);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND2_RGB] = new Uniform<int>(GL_SRC_COLOR);
	}
	uniforms[UniformId::TEXTURE1_ENV_OPERAND2_RGB]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_OPERAND0_RGB && UniformId::TEXTURE2_ENV_OPERAND0_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND0_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_OPERAND0_RGB", GL_SRC_COLOR);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND0_RGB] = new Uniform<int>(GL_SRC_COLOR);
	}
	uniforms[UniformId::TEXTURE2_ENV_OPERAND0_RGB]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_OPERAND1_RGB && UniformId::TEXTURE2_ENV_OPERAND1_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND1_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_OPERAND1_RGB", GL_SRC_COLOR);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND1_RGB] = new Uniform<int>(GL_SRC_COLOR);
	}
	uniforms[UniformId::TEXTURE2_ENV_OPERAND1_RGB]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_OPERAND2_RGB && UniformId::TEXTURE2_ENV_OPERAND2_RGB <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND2_RGB] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_OPERAND2_RGB", GL_SRC_COLOR);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND2_RGB] = new Uniform<int>(GL_SRC_COLOR);
	}
	uniforms[UniformId::TEXTURE2_ENV_OPERAND2_RGB]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_SRC0_ALPHA && UniformId::TEXTURE0_ENV_SRC0_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_SRC0_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_SRC0_ALPHA", 0); // TODO: default value
	} else {
		uniforms[UniformId::TEXTURE0_ENV_SRC0_ALPHA] = new Uniform<int>(0);
	}
	uniforms[UniformId::TEXTURE0_ENV_SRC0_ALPHA]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_SRC1_ALPHA && UniformId::TEXTURE0_ENV_SRC1_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_SRC1_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_SRC1_ALPHA", 0);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_SRC1_ALPHA] = new Uniform<int>(0);
	}
	uniforms[UniformId::TEXTURE0_ENV_SRC1_ALPHA]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_SRC2_ALPHA && UniformId::TEXTURE0_ENV_SRC2_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_SRC2_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_SRC2_ALPHA", 0);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_SRC2_ALPHA] = new Uniform<int>(0);
	}
	uniforms[UniformId::TEXTURE0_ENV_SRC2_ALPHA]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_SRC0_ALPHA && UniformId::TEXTURE1_ENV_SRC0_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_SRC0_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_SRC0_ALPHA", 0);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_SRC0_ALPHA] = new Uniform<int>(0);
	}
	uniforms[UniformId::TEXTURE1_ENV_SRC0_ALPHA]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_SRC1_ALPHA && UniformId::TEXTURE1_ENV_SRC1_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_SRC1_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_SRC1_ALPHA", 0);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_SRC1_ALPHA] = new Uniform<int>(0);
	}
	uniforms[UniformId::TEXTURE1_ENV_SRC1_ALPHA]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_SRC2_ALPHA && UniformId::TEXTURE1_ENV_SRC2_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_SRC2_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_SRC2_ALPHA", 0);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_SRC2_ALPHA] = new Uniform<int>(0);
	}
	uniforms[UniformId::TEXTURE1_ENV_SRC2_ALPHA]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_SRC0_ALPHA && UniformId::TEXTURE2_ENV_SRC0_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_SRC0_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_SRC0_ALPHA", 0);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_SRC0_ALPHA] = new Uniform<int>(0);
	}
	uniforms[UniformId::TEXTURE2_ENV_SRC0_ALPHA]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_SRC1_ALPHA && UniformId::TEXTURE2_ENV_SRC1_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_SRC1_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_SRC1_ALPHA", 0);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_SRC1_ALPHA] = new Uniform<int>(0);
	}
	uniforms[UniformId::TEXTURE2_ENV_SRC1_ALPHA]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_SRC2_ALPHA && UniformId::TEXTURE2_ENV_SRC2_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_SRC2_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_SRC2_ALPHA", 0);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_SRC2_ALPHA] = new Uniform<int>(0);
	}
	uniforms[UniformId::TEXTURE2_ENV_SRC2_ALPHA]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_OPERAND0_ALPHA && UniformId::TEXTURE0_ENV_OPERAND0_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND0_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_OPERAND0_ALPHA", GL_SRC_ALPHA);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND0_ALPHA] = new Uniform<int>(GL_SRC_ALPHA);
	}
	uniforms[UniformId::TEXTURE0_ENV_OPERAND0_ALPHA]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_OPERAND1_ALPHA && UniformId::TEXTURE0_ENV_OPERAND1_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND1_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_OPERAND1_ALPHA", GL_SRC_ALPHA);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND1_ALPHA] = new Uniform<int>(GL_SRC_ALPHA);
	}
	uniforms[UniformId::TEXTURE0_ENV_OPERAND1_ALPHA]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE0_ENV_OPERAND2_ALPHA && UniformId::TEXTURE0_ENV_OPERAND2_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND2_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE0_FRAGMENT_SHADER], "TEXTURE0_ENV_OPERAND2_ALPHA", GL_SRC_ALPHA);
	} else {
		uniforms[UniformId::TEXTURE0_ENV_OPERAND2_ALPHA] = new Uniform<int>(GL_SRC_ALPHA);
	}
	uniforms[UniformId::TEXTURE0_ENV_OPERAND2_ALPHA]->setFather(texture0Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_OPERAND0_ALPHA && UniformId::TEXTURE1_ENV_OPERAND0_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND0_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_OPERAND0_ALPHA", GL_SRC_ALPHA);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND0_ALPHA] = new Uniform<int>(GL_SRC_ALPHA);
	}
	uniforms[UniformId::TEXTURE1_ENV_OPERAND0_ALPHA]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_OPERAND1_ALPHA && UniformId::TEXTURE1_ENV_OPERAND1_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND1_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_OPERAND1_ALPHA", GL_SRC_ALPHA);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND1_ALPHA] = new Uniform<int>(GL_SRC_ALPHA);
	}
	uniforms[UniformId::TEXTURE1_ENV_OPERAND1_ALPHA]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE1_ENV_OPERAND2_ALPHA && UniformId::TEXTURE1_ENV_OPERAND2_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND2_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE1_FRAGMENT_SHADER], "TEXTURE1_ENV_OPERAND2_ALPHA", GL_SRC_ALPHA);
	} else {
		uniforms[UniformId::TEXTURE1_ENV_OPERAND2_ALPHA] = new Uniform<int>(GL_SRC_ALPHA);
	}
	uniforms[UniformId::TEXTURE1_ENV_OPERAND2_ALPHA]->setFather(texture1Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_OPERAND0_ALPHA && UniformId::TEXTURE2_ENV_OPERAND0_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND0_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_OPERAND0_ALPHA", GL_SRC_ALPHA);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND0_ALPHA] = new Uniform<int>(GL_SRC_ALPHA);
	}
	uniforms[UniformId::TEXTURE2_ENV_OPERAND0_ALPHA]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_OPERAND1_ALPHA && UniformId::TEXTURE2_ENV_OPERAND1_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND1_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_OPERAND1_ALPHA", GL_SRC_ALPHA);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND1_ALPHA] = new Uniform<int>(GL_SRC_ALPHA);
	}
	uniforms[UniformId::TEXTURE2_ENV_OPERAND1_ALPHA]->setFather(texture2Enabled);
	
	if (UniformId::FIRST_STATE_UNIFORM_INT <= UniformId::TEXTURE2_ENV_OPERAND2_ALPHA && UniformId::TEXTURE2_ENV_OPERAND2_ALPHA <= UniformId::LAST_STATE_UNIFORM_INT) {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND2_ALPHA] = new UniformState<GLint>(shaders[ShaderId::TEXTURE2_FRAGMENT_SHADER], "TEXTURE2_ENV_OPERAND2_ALPHA", GL_SRC_ALPHA);
	} else {
		uniforms[UniformId::TEXTURE2_ENV_OPERAND2_ALPHA] = new Uniform<int>(GL_SRC_ALPHA);
	}
	uniforms[UniformId::TEXTURE2_ENV_OPERAND2_ALPHA]->setFather(texture2Enabled);
	
	
	// Non-state uniforms
	
	uniforms[UniformId::LIGHT0_AMBIENT] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 1.0f);
	uniforms[UniformId::LIGHT1_AMBIENT] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 1.0f);
	uniforms[UniformId::LIGHT2_AMBIENT] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 1.0f);
	uniforms[UniformId::LIGHT0_DIFFUSE] = new Uniform<Vector4<GLfloat> >(1.0f, 1.0f, 1.0f, 1.0f);
	uniforms[UniformId::LIGHT1_DIFFUSE] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::LIGHT2_DIFFUSE] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::LIGHT0_SPECULAR] = new Uniform<Vector4<GLfloat> >(1.0f, 1.0f, 1.0f, 1.0f);
	uniforms[UniformId::LIGHT1_SPECULAR] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::LIGHT2_SPECULAR] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::LIGHT0_POSITION] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 1.0f, 0.0f);
	uniforms[UniformId::LIGHT1_POSITION] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 1.0f, 0.0f);
	uniforms[UniformId::LIGHT2_POSITION] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 1.0f, 0.0f);
	uniforms[UniformId::LIGHT0_SPOT_DIRECTION] = new Uniform<Vector3<GLfloat> >(0.0f, 0.0f, -1.0f);
	uniforms[UniformId::LIGHT1_SPOT_DIRECTION] = new Uniform<Vector3<GLfloat> >(0.0f, 0.0f, -1.0f);
	uniforms[UniformId::LIGHT2_SPOT_DIRECTION] = new Uniform<Vector3<GLfloat> >(0.0f, 0.0f, -1.0f);
	uniforms[UniformId::LIGHT0_SPOT_EXPONENT] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::LIGHT1_SPOT_EXPONENT] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::LIGHT2_SPOT_EXPONENT] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::LIGHT0_SPOT_CUTOFF_ANGLE_COS] = new Uniform<GLfloat>(-1.0f);
	uniforms[UniformId::LIGHT1_SPOT_CUTOFF_ANGLE_COS] = new Uniform<GLfloat>(-1.0f);
	uniforms[UniformId::LIGHT2_SPOT_CUTOFF_ANGLE_COS] = new Uniform<GLfloat>(-1.0f);
	uniforms[UniformId::LIGHT0_CONSTANT_ATTENUATION] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::LIGHT1_CONSTANT_ATTENUATION] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::LIGHT2_CONSTANT_ATTENUATION] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::LIGHT0_LINEAR_ATTENUATION] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::LIGHT1_LINEAR_ATTENUATION] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::LIGHT2_LINEAR_ATTENUATION] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::LIGHT0_QUADRATIC_ATTENUATION] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::LIGHT1_QUADRATIC_ATTENUATION] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::LIGHT2_QUADRATIC_ATTENUATION] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::MATERIAL_AMBIENT] = new Uniform<Vector4<GLfloat> >(0.2f, 0.2f, 0.2f, 1.0f);
	uniforms[UniformId::MATERIAL_DIFFUSE] = new Uniform<Vector4<GLfloat> >(0.8f, 0.8f, 0.8f, 1.0f);
	uniforms[UniformId::MATERIAL_SPECULAR] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 1.0f);
	uniforms[UniformId::MATERIAL_EMISSION] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 1.0f);
	uniforms[UniformId::MATERIAL_SHININESS] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::MODELVIEW_MATRIX] = new Uniform<Matrix4x4<GLfloat> >();
	uniforms[UniformId::MODELVIEW_PROJECTION_MATRIX] = new Uniform<Matrix4x4<GLfloat> >();
	uniforms[UniformId::TRANPOSE_ADJOINT_MODEL_VIEW_MATRIX] = new Uniform<Matrix3x3<GLfloat> >();
	uniforms[UniformId::RESCALE_NORMAL_FACTOR] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::FOG_COLOR] = new Uniform<Vector3<GLfloat> >(0.0f, 0.0f, 0.0f);
	uniforms[UniformId::FOG_DENSITY] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::FOG_START] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::FOG_END] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::GLOBAL_AMBIENT_COLOR] = new Uniform<Vector4<GLfloat> >(0.2f, 0.2f, 0.2f, 1.0f);
	uniforms[UniformId::ALPHA_FUNC_VALUE] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::CLIP_PLANE0_EQUATION] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::CLIP_PLANE1_EQUATION] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::CLIP_PLANE2_EQUATION] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::CLIP_PLANE3_EQUATION] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::CLIP_PLANE4_EQUATION] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::CLIP_PLANE5_EQUATION] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::TEXTURE0_ENV_COLOR] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::TEXTURE1_ENV_COLOR] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::TEXTURE2_ENV_COLOR] = new Uniform<Vector4<GLfloat> >(0.0f, 0.0f, 0.0f, 0.0f);
	uniforms[UniformId::TEXTURE0_ENV_RGB_SCALE] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::TEXTURE1_ENV_RGB_SCALE] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::TEXTURE2_ENV_RGB_SCALE] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::TEXTURE0_ENV_ALPHA_SCALE] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::TEXTURE1_ENV_ALPHA_SCALE] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::TEXTURE2_ENV_ALPHA_SCALE] = new Uniform<GLfloat>(1.0f);
	uniforms[UniformId::TEXTURE0_ENV_BLUR_AMOUNT] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::TEXTURE1_ENV_BLUR_AMOUNT] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::TEXTURE2_ENV_BLUR_AMOUNT] = new Uniform<GLfloat>(0.0f);
	uniforms[UniformId::TEXTURE0_SAMPLER] = new Uniform<GLint>(0);
	uniforms[UniformId::TEXTURE1_SAMPLER] = new Uniform<GLint>(1);
	uniforms[UniformId::TEXTURE2_SAMPLER] = new Uniform<GLint>(2);
	uniforms[UniformId::TEXTURE0_MATRIX] = new Uniform<Matrix4x4<GLfloat> >();
	uniforms[UniformId::TEXTURE1_MATRIX] = new Uniform<Matrix4x4<GLfloat> >();
	uniforms[UniformId::TEXTURE2_MATRIX] = new Uniform<Matrix4x4<GLfloat> >();
}

void OpenGLESState::setActiveUniformLocations( std::vector<UniformSimple *> *activeUniforms )
{
	for (size_t i = 0; i < activeUniforms->size(); i++) 
	{
		UniformSimple *activeUniform = (*activeUniforms)[i];
		int index = activeUniform->getId();
		uniforms[index]->setLocation(activeUniform->getLocation());
	}
}

void OpenGLESState::setActiveAttributeLocations( std::vector<AttributeSimple *> *activeAttributes )
{
	for (size_t i = 0; i < activeAttributes->size(); i++) 
	{
		AttributeSimple *activeAttribute = (*activeAttributes)[i];
		int index = activeAttribute->getId();
		attributes[index]->setLocation(activeAttribute->getLocation());
	}
}

void OpenGLESState::uploadAttributes() 
{
	std::vector<AttributeSimple *> *activeAttributes = currentStateShaderProgram->shaderProgram->getActiveAttributes();
	
	for (size_t i = 0; i < activeAttributes->size(); i++)
	{
		AttributeSimple *activeAttribute = (*activeAttributes)[i];
		attributes[activeAttribute->getId()]->upload(currentStateShaderProgram->shaderProgram);
	}
}

void OpenGLESState::uploadUniforms() 
{
	std::vector<UniformSimple *> *activeUniforms = currentStateShaderProgram->shaderProgram->getActiveUniforms();
	
	for (size_t i = 0; i < activeUniforms->size(); i++)
	{
		UniformSimple *activeUniform = (*activeUniforms)[i];
		uniforms[activeUniform->getId()]->upload(currentStateShaderProgram->shaderProgram);
	}
}

void OpenGLESState::setCurrentProgram()
{
	if (OpenGLESConfig::OPENGLESCONFIG_USE_ONLY_UBER_SHADER) {
		static bool uberShaderCompiled = false;
		if (!uberShaderCompiled) {
			std::vector<ShaderSource *> vertexShaderSources;
			for (unsigned int i = ShaderId::FIRST_VERTEX_SHADER; i <= ShaderId::LAST_VERTEX_SHADER; i++) {
				vertexShaderSources.push_back(new ShaderSource(shaders[i], ""));
			}
			std::vector<ShaderSource * > fragmentShaderSources;
			for (unsigned int i = ShaderId::FIRST_FRAGMENT_SHADER; i <= ShaderId::LAST_FRAGMENT_SHADER; i++) {
				fragmentShaderSources.push_back(new ShaderSource(shaders[i], ""));
			}
			
			Shader *vertexShader = new Shader(GL_VERTEX_SHADER, vertexShaderSources);
			Shader *fragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentShaderSources);
			
			currentStateShaderProgram = new StateShaderProgram(getCopyOfCurrentState(), new ShaderProgram("UberShader", vertexShader, fragmentShader));
			stateShaderPrograms.push_back(currentStateShaderProgram);
			currentStateShaderProgram->shaderProgram->use();
			setActiveUniformLocations(currentStateShaderProgram->shaderProgram->getActiveUniforms());
			setActiveAttributeLocations(currentStateShaderProgram->shaderProgram->getActiveAttributes());
			
			uberShaderCompiled = true;
		}
		
		uploadUniforms();
		uploadAttributes();
		return;
	}
	
	StateShaderProgram *oldStateShaderProgram = currentStateShaderProgram;
	
	// Set current state to faster array
	unsigned int currentBit = 0;
	for (unsigned int i = UniformId::FIRST_STATE_UNIFORM_BOOL; i <= UniformId::LAST_STATE_UNIFORM_BOOL; i++) 
	{
		if (currentBit % 32 == 0) {
			currentState[currentBit/32] = 0;
		}
		
		currentState[currentBit/32] |= (static_cast<UniformState<bool> * >(uniforms[i])->getValue() ? 1 : 0) << (currentBit % 32);
		
		currentBit++;
	}
	
	int index = stateSizeBool;
	for (unsigned int i = UniformId::FIRST_STATE_UNIFORM_INT; i <= UniformId::LAST_STATE_UNIFORM_INT; i++) 
	{
		GLint val = static_cast<UniformState<GLint> * >(uniforms[i])->getValue();
		
		currentState[index] = val;
		
		index++;
	}	
	
	// Check if it matches to any existing state
	int stateIndex = -1;
	for (size_t i = 0; i < stateShaderPrograms.size(); i++)
	{
		bool stateFound = true;
		for (unsigned int j = 0; j < stateSize; j++) {
			if (currentState[j] != stateShaderPrograms[i]->state[j]) {
				stateFound = false;
				break;
			}
		}
		if (stateFound) {
			stateIndex = i;
			break;
		}
	}
	
	// If matched, fetch shader program from cache
	if (stateIndex >= 0) {
		currentStateShaderProgram = stateShaderPrograms[stateIndex];
	} else {
#ifdef OPENGLES_DEBUG
		OPENGLES_LOG_DEBUG_MESSAGE("State binary presentation:");
		OPENGLES_LOG_DEBUG_MESSAGE("Bool states: ");
		for (unsigned int i = 0; i < stateSizeBool; i++) {
			OPENGLES_PRINT_BITS(currentState[i]);
		}
		OPENGLES_LOG_DEBUG_MESSAGE("\nInt states: ");
		for (unsigned int i = stateSizeBool; i < stateSize; i++) {
			OPENGLES_PRINT("%x ", currentState[i]);
		}
		OPENGLES_LOG_DEBUG_MESSAGE("");
#endif
		
		std::vector<ShaderSource *> vertexShaderSources;
		std::vector<ShaderSource * > fragmentShaderSources;
		
		addRequiredShaderSources(vertexShaderSources, fragmentShaderSources);
		
		addDefinesToShaderSources(vertexShaderSources, fragmentShaderSources);
		
		if (OpenGLESConfig::OPENGLESCONFIG_DEBUG) {
			OPENGLES_LOG_MESSAGE("Using shader files:");
			for (size_t i = 0; i < vertexShaderSources.size(); i++)
			{
				OPENGLES_LOG_MESSAGE(vertexShaderSources[i]->getFile()->getName());
			}
			
			for (size_t i = 0; i < fragmentShaderSources.size(); i++)
			{
				OPENGLES_LOG_MESSAGE(fragmentShaderSources[i]->getFile()->getName());
			}
		}
		
		Shader *vertexShader = new Shader(GL_VERTEX_SHADER, vertexShaderSources);
		Shader *fragmentShader = new Shader(GL_FRAGMENT_SHADER, fragmentShaderSources);
		
		currentStateShaderProgram = new StateShaderProgram(getCopyOfCurrentState(), new ShaderProgram(OpenGLESString("Optimized Shader ") + (stateShaderPrograms.size() + 1), vertexShader, fragmentShader));
		stateShaderPrograms.push_back(currentStateShaderProgram);
	}
	
	if (currentStateShaderProgram != oldStateShaderProgram) {
		currentStateShaderProgram->shaderProgram->use();
		setActiveUniformLocations(currentStateShaderProgram->shaderProgram->getActiveUniforms());
		setActiveAttributeLocations(currentStateShaderProgram->shaderProgram->getActiveAttributes());
	}
	
	uploadAttributes();
	uploadUniforms();
}

void OpenGLESState::addRequiredShaderSources(std::vector<ShaderSource *> &vertexShaderSources, std::vector<ShaderSource *> &fragmentShaderSources)
{
	vertexShaderSources.push_back(new ShaderSource(shaders[ShaderId::MAIN_VERTEX_SHADER]));
	fragmentShaderSources.push_back(new ShaderSource(shaders[ShaderId::MAIN_FRAGMENT_SHADER]));
	
	for (unsigned int i = 0; i < UniformId::COUNT; i++) {
		std::vector<ShaderFile *> additionalRequiredShaderFiles = uniforms[i]->getAdditionalRequiredShaderFiles();
		for(size_t j = 0; j < additionalRequiredShaderFiles.size(); j++) {
			bool shaderFileFound = false;
			if (additionalRequiredShaderFiles[j]->getType() == GL_VERTEX_SHADER) {
				for (size_t k = 0; k < vertexShaderSources.size(); k++) {
					if (vertexShaderSources[k]->getFile() == additionalRequiredShaderFiles[j]) {
						shaderFileFound = true;
						break;
					}
				}
				if (!shaderFileFound) {
					vertexShaderSources.push_back(new ShaderSource(additionalRequiredShaderFiles[j]));
				}
			} else {
				for (size_t k = 0; k < fragmentShaderSources.size(); k++) {
					if (fragmentShaderSources[k]->getFile() == additionalRequiredShaderFiles[j]) {
						shaderFileFound = true;
						break;
					}
				}
				if (!shaderFileFound) {
					fragmentShaderSources.push_back(new ShaderSource(additionalRequiredShaderFiles[j]));
				}
			}
		}
	}
}

void OpenGLESState::addDefinesToShaderSources(std::vector<ShaderSource *> &vertexShaderSources, std::vector<ShaderSource *> &fragmentShaderSources)
{
	for (unsigned int i = UniformId::FIRST_STATE_UNIFORM_BOOL; i <= UniformId::LAST_STATE_UNIFORM_BOOL; i++) 
	{
		UniformState<bool> *uniformState = static_cast<UniformState<bool> * >(uniforms[i]);
		
		std::vector<ShaderFile *> defineShaderFiles = uniformState->getDefineShaderFiles();
		std::string define = uniformState->getDefine();
		addDefineToShaderSources(define, defineShaderFiles, vertexShaderSources, fragmentShaderSources);
	}
	for (unsigned int i = UniformId::FIRST_STATE_UNIFORM_INT; i <= UniformId::LAST_STATE_UNIFORM_INT; i++) 
	{
		UniformState<GLint> *uniformState = static_cast<UniformState<GLint> * >(uniforms[i]);
		std::vector<ShaderFile *> defineShaderFiles = uniformState->getDefineShaderFiles();
		std::string define = uniformState->getDefine();
		addDefineToShaderSources(define, defineShaderFiles, vertexShaderSources, fragmentShaderSources);
	}
	
	// Additional defines for shader optimization
	if ((UniformState<bool> *)(uniforms[UniformId::LIGHTING_ENABLED]) && (UniformState<bool> *)(uniforms[UniformId::LIGHT0_ENABLED]) && (UniformState<bool> *)(uniforms[UniformId::LIGHT1_ENABLED]) && (UniformState<bool> *)(uniforms[UniformId::LIGHT2_ENABLED])) {
		bool nonDirectionalLightEnabled = false;
		if (static_cast<Uniform<bool> * >(uniforms[UniformId::LIGHTING_ENABLED])->getValue()) {
			for (int i = 0; i < 3; i++) {
				if (static_cast<Uniform<bool> * >(uniforms[UniformId::LIGHT0_ENABLED + i])->getValue() && static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::LIGHT0_POSITION + i])->getValue().v[3] != 0.0f) {
					nonDirectionalLightEnabled = true;
					break;
				}
			}
		}
		std::string nonDirectionalLightEnabledString = "#define NON_DIRECTIONAL_LIGHT_ENABLED ";
		nonDirectionalLightEnabledString += nonDirectionalLightEnabled ? "1" : "0";
		nonDirectionalLightEnabledString += "\n";
		vertexShaderSources[ShaderId::MAIN_VERTEX_SHADER]->appendAdditionalSource(nonDirectionalLightEnabledString);
	}
}

void OpenGLESState::addDefineToShaderSources(std::string define, std::vector<ShaderFile *> &shaderFiles, std::vector<ShaderSource *> &vertexShaderSources, std::vector<ShaderSource * > &fragmentShaderSources )
{
	for (size_t i = 0; i < shaderFiles.size(); i++) {
		if (shaderFiles[i]->getType() == GL_VERTEX_SHADER) {
			for (size_t j = 0; j < vertexShaderSources.size(); j++)
			{
				if (shaderFiles[i] == vertexShaderSources[j]->getFile()) {
					vertexShaderSources[j]->appendAdditionalSource(define);
				}
			}
		} else {
			for (size_t j = 0; j < fragmentShaderSources.size(); j++)
			{
				if (shaderFiles[i] == fragmentShaderSources[j]->getFile()) {
					fragmentShaderSources[j]->appendAdditionalSource(define);
				}
			}
		}
	}
}

unsigned int* OpenGLESState::getCopyOfCurrentState()
{
	unsigned int *state = (unsigned int *)malloc(sizeof(unsigned int) * stateSize);
	
	for (unsigned int i = 0; i < stateSize; i++) {
		state[i] = currentState[i];
	}
	
	return state;
}

void OpenGLESState::setActiveTexture(int a)
{
	activeTexture = a;
}

int OpenGLESState::getActiveTexture()
{
	return activeTexture;
}

void OpenGLESState::setClientActiveTexture(int a)
{
	clientActiveTexture = a;
}

int OpenGLESState::getClientActiveTexture()
{
	return clientActiveTexture;
}

void OpenGLESState::setBoundTextureFormat(int format)
{
	boundTextureFormats[boundTextures[activeTexture]] = format;
}

void OpenGLESState::setBoundTexture(int i)
{
	boundTextures[activeTexture] = i;
}

void OpenGLESState::setPosition( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer )
{
	attributes[AttributeId::POSITION]->setValues(size, type, stride, pointer);
}

void OpenGLESState::setNormal( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer )
{
	attributes[AttributeId::NORMAL]->setValues(size, type, stride, pointer);
}

void OpenGLESState::setColor( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer )
{
	attributes[AttributeId::COLOR]->setValues(size, type, stride, pointer);
}

void OpenGLESState::setTexCoord( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer )
{
	attributes[AttributeId::TEXCOORD0 + clientActiveTexture]->setValues(size, type, stride, pointer);
}

void OpenGLESState::setPosition( bool enabled )
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::POSITION_ENABLED])->setValue(enabled);
	attributes[AttributeId::POSITION]->setEnabled(enabled);
}

void OpenGLESState::setColor( bool enabled )
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::COLOR_ENABLED])->setValue(enabled);
	attributes[AttributeId::COLOR]->setEnabled(enabled);
}

void OpenGLESState::setNormal( bool enabled )
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::NORMAL_ENABLED])->setValue(enabled);
	attributes[AttributeId::NORMAL]->setEnabled(enabled);
}

bool OpenGLESState::isNormal()
{
	return static_cast<Uniform<bool> * >(uniforms[UniformId::NORMAL_ENABLED])->getValue();
}

void OpenGLESState::setTexture(bool enabled)
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::TEXTURE0_ENABLED + activeTexture])->setValue(enabled);
}

void OpenGLESState::setTexCoord( bool enabled )
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::TEXCOORD0_ENABLED + clientActiveTexture])->setValue(enabled);
	attributes[AttributeId::TEXCOORD0 + clientActiveTexture]->setEnabled(enabled);
}

bool OpenGLESState::isTexCoord(int index)
{
	return static_cast<Uniform<bool> * >(uniforms[UniformId::TEXCOORD0_ENABLED + index])->getValue();
}

void OpenGLESState::setTextureFormat()
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::TEXTURE0_FORMAT + activeTexture])->setValue(boundTextureFormats[boundTextures[activeTexture]]);
}

void OpenGLESState::setTextureEnvMode(GLint val)
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::TEXTURE0_ENV_MODE + activeTexture])->setValue(val);
}

void OpenGLESState::setTextureEnvColor(Vector4<GLfloat> vec)
{
	static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::TEXTURE0_ENV_COLOR + activeTexture])->setValue(vec);
}

void OpenGLESState::setTextureEnvCombineRGB(GLint val)
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::TEXTURE0_ENV_COMBINE_RGB + activeTexture])->setValue(val);
}

void OpenGLESState::setTextureEnvCombineAlpha(GLint val)
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::TEXTURE0_ENV_COMBINE_ALPHA + activeTexture])->setValue(val);
}

void OpenGLESState::setTextureEnvSrcRGB(int index, GLint val)
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::TEXTURE0_ENV_SRC0_RGB + index + 3*activeTexture])->setValue(val);
}

void OpenGLESState::setTextureEnvOperandRGB(int index, GLint val)
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::TEXTURE0_ENV_OPERAND0_RGB + index + 3*activeTexture])->setValue(val);
}

void OpenGLESState::setTextureEnvSrcAlpha(int index, GLint val)
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::TEXTURE0_ENV_SRC0_ALPHA + index + 3*activeTexture])->setValue(val);
}

void OpenGLESState::setTextureEnvOperandAlpha(int index, GLint val)
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::TEXTURE0_ENV_OPERAND0_ALPHA + index + 3*activeTexture])->setValue(val);
}

void OpenGLESState::setTextureEnvRGBScale(GLfloat val)
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::TEXTURE0_ENV_RGB_SCALE + activeTexture])->setValue(val);
}

void OpenGLESState::setTextureEnvAlphaScale(GLfloat val)
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::TEXTURE0_ENV_ALPHA_SCALE + activeTexture])->setValue(val);
}

void OpenGLESState::setTextureEnvBlurAmount(GLfloat val)
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::TEXTURE0_ENV_BLUR_AMOUNT + activeTexture])->setValue(val);
}

void OpenGLESState::setLightModelLocalViewer( bool enabled )
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::LIGHT_MODEL_LOCAL_VIEWER_ENABLED])->setValue(enabled);
}

void OpenGLESState::setLightModelTwoSide( bool enabled )
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::LIGHT_MODEL_TWO_SIDE_ENABLED])->setValue(enabled);
}

void OpenGLESState::setLighting( bool enabled )
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::LIGHTING_ENABLED])->setValue(enabled);
}

void OpenGLESState::setLightingHint(GLint val)
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::LIGHTING_HINT])->setValue(val);
}

void OpenGLESState::setLight( GLenum light, bool enabled )
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::LIGHT0_ENABLED + light])->setValue(enabled);
}

void OpenGLESState::setLightAmbient( GLenum light, Vector4<GLfloat> vec )
{
	static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::LIGHT0_AMBIENT + light])->setValue(vec);
}

void OpenGLESState::setLightDiffuse( GLenum light, Vector4<GLfloat> vec )
{
	static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::LIGHT0_DIFFUSE + light])->setValue(vec);
}

void OpenGLESState::setLightSpecular( GLenum light, Vector4<GLfloat> vec )
{
	static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::LIGHT0_SPECULAR + light])->setValue(vec);
}

void OpenGLESState::setLightPosition( GLenum light, Vector4<GLfloat> vec )
{
	static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::LIGHT0_POSITION + light])->setValue(vec);
}

void OpenGLESState::setLightSpotDirection( GLenum light, Vector3<GLfloat> vec )
{
	static_cast<Uniform<Vector3<GLfloat> > * >(uniforms[UniformId::LIGHT0_SPOT_DIRECTION + light])->setValue(vec);
}

void OpenGLESState::setLightSpotExponent( GLenum light, GLfloat val )
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::LIGHT0_SPOT_EXPONENT + light])->setValue(val);
}

void OpenGLESState::setLightSpotCutoffAngleCos( GLenum light, GLfloat val )
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::LIGHT0_SPOT_CUTOFF_ANGLE_COS + light])->setValue(val);
}

void OpenGLESState::setLightConstantAttenuation( GLenum light, GLfloat val )
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::LIGHT0_CONSTANT_ATTENUATION + light])->setValue(val);
}

void OpenGLESState::setLightLinearAttenuation( GLenum light, GLfloat val )
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::LIGHT0_LINEAR_ATTENUATION + light])->setValue(val);
}

void OpenGLESState::setLightQuadraticAttenuation( GLenum light, GLfloat val )
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::LIGHT0_QUADRATIC_ATTENUATION + light])->setValue(val);
}

void OpenGLESState::setMaterialAmbient(Vector4<GLfloat> vec )
{
	static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::MATERIAL_AMBIENT])->setValue(vec);
}

void OpenGLESState::setMaterialDiffuse(Vector4<GLfloat> vec )
{
	static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::MATERIAL_DIFFUSE])->setValue(vec);
}

void OpenGLESState::setMaterialSpecular(Vector4<GLfloat> vec )
{
	static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::MATERIAL_SPECULAR])->setValue(vec);
}

void OpenGLESState::setMaterialEmission(Vector4<GLfloat> vec )
{
	static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::MATERIAL_EMISSION])->setValue(vec);
}

void OpenGLESState::setMaterialShininess(GLfloat val )
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::MATERIAL_SHININESS])->setValue(val);
}

void OpenGLESState::setModelViewMatrix( Matrix4x4<GLfloat> mat )
{
	static_cast<Uniform<Matrix4x4<GLfloat> > * >(uniforms[UniformId::MODELVIEW_MATRIX])->setValue(mat);
}

void OpenGLESState::setModelViewProjectionMatrix( Matrix4x4<GLfloat> mat )
{
	static_cast<Uniform<Matrix4x4<GLfloat> > * >(uniforms[UniformId::MODELVIEW_PROJECTION_MATRIX])->setValue(mat);
}

void OpenGLESState::setTransposeAdjointModelViewMatrix( Matrix3x3<GLfloat> mat )
{
	static_cast<Uniform<Matrix3x3<GLfloat> > * >(uniforms[UniformId::TRANPOSE_ADJOINT_MODEL_VIEW_MATRIX])->setValue(mat);
}

void OpenGLESState::setNormalize( bool enabled )
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::NORMALIZE_ENABLED])->setValue(enabled);
}

void OpenGLESState::setRescaleNormal(bool enabled)
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::RESCALE_NORMAL_ENABLED])->setValue(enabled);
}

bool OpenGLESState::isRescaleNormal()
{
	return static_cast<Uniform<bool> * >(uniforms[UniformId::RESCALE_NORMAL_ENABLED])->getValue();
}

void OpenGLESState::setRescaleNormalFactor(GLfloat val)
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::RESCALE_NORMAL_FACTOR])->setValue(val);
}

void OpenGLESState::setGlobalAmbientColor( Vector4<GLfloat> vec )
{
	static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::GLOBAL_AMBIENT_COLOR])->setValue(vec);
}

void OpenGLESState::setFog( bool enabled )
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::FOG_ENABLED])->setValue(enabled);
}

void OpenGLESState::setFogColor(Vector3<GLfloat> vec)
{
	static_cast<Uniform<Vector3<GLfloat> > * >(uniforms[UniformId::FOG_COLOR])->setValue(vec);
}

void OpenGLESState::setFogMode(GLint val)
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::FOG_MODE])->setValue(val);
}

void OpenGLESState::setFogDensity(GLfloat val)
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::FOG_DENSITY])->setValue(val);
}

void OpenGLESState::setFogStart(GLfloat val)
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::FOG_START])->setValue(val);
}

void OpenGLESState::setFogEnd(GLfloat val)
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::FOG_END])->setValue(val);
}

void OpenGLESState::setFogHint(GLint val)
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::FOG_HINT])->setValue(val);
}

void OpenGLESState::setAlphaTest( bool enabled )
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::ALPHA_TEST_ENABLED])->setValue(enabled);
}

void OpenGLESState::setAlphaFunc(GLint val)
{
	static_cast<Uniform<GLint> * >(uniforms[UniformId::ALPHA_FUNC])->setValue(val);
}

void OpenGLESState::setAlphaFuncValue(GLfloat val)
{
	static_cast<Uniform<GLfloat> * >(uniforms[UniformId::ALPHA_FUNC_VALUE])->setValue(val);
}

void OpenGLESState::setClipPlane(GLenum clipPlaneIndex, bool enabled)
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::CLIP_PLANE0_ENABLED + clipPlaneIndex])->setValue(enabled);
}

void OpenGLESState::setClipPlane(GLenum clipPlaneIndex, Vector4<GLfloat> vec)
{
	static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::CLIP_PLANE0_EQUATION + clipPlaneIndex])->setValue(vec);
}

void OpenGLESState::getClipPlane(GLenum clipPlaneIndex, GLfloat eqn[4])
{
	Vector4<GLfloat> vec = static_cast<Uniform<Vector4<GLfloat> > * >(uniforms[UniformId::CLIP_PLANE0_EQUATION + clipPlaneIndex])->getValue();
	eqn[0] = vec[0];
	eqn[1] = vec[1];
	eqn[2] = vec[2];
	eqn[3] = vec[3];
}

void OpenGLESState::setTextureMatrix(int index, Matrix4x4<GLfloat> mat)
{
	static_cast<Uniform<Matrix4x4<GLfloat> > * >(uniforms[UniformId::TEXTURE0_MATRIX + index])->setValue(mat);
}

void OpenGLESState::setTextureMatrix(int index, bool enabled)
{
	static_cast<Uniform<bool> * >(uniforms[UniformId::TEXTURE0_MATRIX_ENABLED + index])->setValue(enabled);
}

int OpenGLESState::getCachedShaderAmount()
{
	return stateShaderPrograms.size();
}
