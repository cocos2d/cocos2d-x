//
// Copyright 2011 Jeff Lamarche
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided
// that the following conditions are met:
//	1. Redistributions of source code must retain the above copyright notice, this list of conditions and
//		the following disclaimer.
//
//	2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions
//		and the following disclaimer in the documentation and/or other materials provided with the
//		distribution.
//
//	THIS SOFTWARE IS PROVIDED BY THE FREEBSD PROJECT ``AS IS'' AND ANY EXPRESS OR IMPLIED
//	WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//	FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FREEBSD PROJECT
//	OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//	OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
//	AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
//	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Adapted for cocos2d http://www.cocos2d-iphone.org

#include "CCGLProgram.h"
#include "ccGLState.h"
#include "ccMacros.h"
#include "CCFileUtils.h"
#include "CCString.h"

NS_CC_BEGIN

#define DEBUG 1

CCGLProgram::CCGLProgram()
{

}

CCGLProgram::~CCGLProgram()
{
	CCLOGINFO("cocos2d: deallocing 0x%X", this);

	// there is no need to delete the shaders. They should have been already deleted.
	CCAssert( vertShader_ == 0, "Vertex Shaders should have been already deleted");
	CCAssert( fragShader_ == 0, "Vertex Shaders should have been already deleted");

	if (program_)
		ccGLDeleteProgram(program_);

}

bool CCGLProgram::initWithVertexShaderFilename(const char* vShaderFilename, const char* fShaderFilename)
{
    program_ = glCreateProgram();

	vertShader_ = fragShader_ = 0;

	if( vShaderFilename ) {
		const char *fullname = CCFileUtils::fullPathFromRelativePath(vShaderFilename);

		if (!compileShader(&vertShader_, GL_VERTEX_SHADER, fullname)) {
			CCLOG("cocos2d: ERROR: Failed to compile vertex shader: %s", vShaderFilename);
		}

	}

    // Create and compile fragment shader
	if( fShaderFilename ) {
		const char *fullname = CCFileUtils::fullPathFromRelativePath(fShaderFilename);

		if (!compileShader(&fragShader_, GL_FRAGMENT_SHADER, fullname)) {
			CCLOG("cocos2d: ERROR: Failed to compile fragment shader: %s", fShaderFilename);
		}
	}

	if( vertShader_ )
		glAttachShader(program_, vertShader_);

	if( fragShader_ )
		glAttachShader(program_, fragShader_);

    return true;
}

const char* CCGLProgram::description()
{
	static char strDescription[100] = {0};
	sprintf(strDescription, "<CCGLProgram = %08X | Program = %i, VertexShader = %i, FragmentShader = %i>", this, program_, vertShader_, fragShader_);
	return strDescription;
}

bool CCGLProgram::compileShader(GLuint * shader, GLenum type, const char* file)
{
    GLint status;
    const GLchar *source;

    source = (GLchar *)CCString::stringWithContentsOfFile(file);
    if (!source)
        return false;

    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);

	if( ! status ) {
		if( type == GL_VERTEX_SHADER )
			CCLOG("cocos2d: %s: %s", file, vertexShaderLog() );
		else
			CCLOG("cocos2d: %s: %s", file, fragmentShaderLog() );

	}
    return status == GL_TRUE;
}

void CCGLProgram::addAttribute(const char* attributeName, GLuint index)
{
	glBindAttribLocation(program_,
						 index,
						 attributeName);
}

void CCGLProgram::updateUniforms()
{
	// Since sample most probably won't change, set it to 0 now.

	uniforms_[kCCUniformMVPMatrix] = glGetUniformLocation(program_, kCCUniformMVPMatrix_s);

	uniforms_[kCCUniformSampler] = glGetUniformLocation(program_, kCCUniformSampler_s);

	ccGLUseProgram( program_ );
	glUniform1i( uniforms_[kCCUniformSampler], 0 );
}

bool CCGLProgram::link()
{
    glLinkProgram(program_);

#if DEBUG
	GLint status;
    glValidateProgram(program_);

    glGetProgramiv(program_, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
		CCLOG("cocos2d: ERROR: Failed to link program: %i", program_);
		if( vertShader_ )
			glDeleteShader( vertShader_ );
		if( fragShader_ )
			glDeleteShader( fragShader_ );
		ccGLDeleteProgram( program_ );
		vertShader_ = fragShader_ = program_ = 0;
        return false;
	}
#endif

    if (vertShader_)
        glDeleteShader(vertShader_);
    if (fragShader_)
        glDeleteShader(fragShader_);

	vertShader_ = fragShader_ = 0;

    return true;
}

void CCGLProgram::use()
{
    ccGLUseProgram(program_);
}

const char* CCGLProgram::logForOpenGLObject(GLuint object, GLInfoFunction infoFunc, GLLogFunction logFunc)
{
    GLint logLength = 0, charsWritten = 0;

    infoFunc(object, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength < 1)
        return 0;

    char *logBytes = (char*)malloc(logLength);
    logFunc(object, logLength, &charsWritten, logBytes);

	CCString* log = new CCString(logBytes);
	log->autorelease();

    free(logBytes);
    return log->toStdString().c_str();
}

const char* CCGLProgram::vertexShaderLog()
{
    return this->logForOpenGLObject(vertShader_, (GLInfoFunction)&glGetProgramiv, (GLLogFunction)&glGetProgramInfoLog);
}

const char* CCGLProgram::fragmentShaderLog()
{
	return this->logForOpenGLObject(fragShader_, (GLInfoFunction)&glGetShaderiv, (GLLogFunction)&glGetShaderInfoLog);
}

const char* CCGLProgram::programLog()
{
    return this->logForOpenGLObject(program_, (GLInfoFunction)&glGetProgramiv, (GLLogFunction)&glGetProgramInfoLog);
}


NS_CC_END
