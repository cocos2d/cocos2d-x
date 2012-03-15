/****************************************************************************
Copyright 2012 cocos2d-x.org
Copyright 2011 Jeff Lamarche
Copyright 2012 Goffredo Marocchi
Copyright 2012 Ricardo Quesada

http://www.cocos2d-x.org
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN false EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCGLProgram.h"
#include "ccGLStateCache.h"
#include "ccMacros.h"
#include "CCFileUtils.h"
#include "support/data_support/uthash.h"
#include "CCString.h"
// extern
#include "kazmath/GL/matrix.h"
#include "kazmath/kazmath.h"

NS_CC_BEGIN

typedef struct _hashUniformEntry
{
	GLvoid*			value;		// value
	unsigned int	location;	// Key
	UT_hash_handle  hh;			// hash entry
} tHashUniformEntry;

CCGLProgram::CCGLProgram()
: program_(0)
, vertShader_(0)
, fragShader_(0)
, hashForUniforms_(NULL)
{
	memset(uniforms_, 0, sizeof(uniforms_));
}

CCGLProgram::~CCGLProgram()
{
	CCLOGINFO("cocos2d: deallocing 0x%X", this);

	// there is no need to delete the shaders. They should have been already deleted.
	CCAssert( vertShader_ == 0, "Vertex Shaders should have been already deleted");
	CCAssert( fragShader_ == 0, "Vertex Shaders should have been already deleted");

	if (program_) 
	{
		ccGLDeleteProgram(program_);
	}

	tHashUniformEntry *current_element, *tmp;

	// Purge uniform hash
	HASH_ITER(hh, hashForUniforms_, current_element, tmp) {
		HASH_DEL(hashForUniforms_, current_element);
		free(current_element->value);
		free(current_element);
	}
}

bool CCGLProgram::initWithVertexShaderByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray)
{
	program_ = glCreateProgram();

	vertShader_ = fragShader_ = 0;

	if( vShaderByteArray ) {

		if (!compileShader(&vertShader_, GL_VERTEX_SHADER, vShaderByteArray)) {
			CCLOG("cocos2d: ERROR: Failed to compile vertex shader");
		}

	}

	// Create and compile fragment shader
	if( fShaderByteArray ) {

		if (!compileShader(&fragShader_, GL_FRAGMENT_SHADER, fShaderByteArray)) {
			CCLOG("cocos2d: ERROR: Failed to compile fragment shader");
		}
	}

	if( vertShader_ ) {
		glAttachShader(program_, vertShader_);
	}

	if( fragShader_ ) {
		glAttachShader(program_, fragShader_);
	}
	hashForUniforms_ = NULL;

	return true;
}

bool CCGLProgram::initWithVertexShaderFilename(const char* vShaderFilename, const char* fShaderFilename)
{
	const GLchar * vertexSource = (GLchar*) CCString::stringWithContentsOfFile(CCFileUtils::fullPathFromRelativePath(vShaderFilename));
	const GLchar * fragmentSource = (GLchar*) CCString::stringWithContentsOfFile(CCFileUtils::fullPathFromRelativePath(fShaderFilename));

	return initWithVertexShaderByteArray(vertexSource, fragmentSource);
}

const char* CCGLProgram::description()
{
	static char strDescription[100] = {0};
	sprintf(strDescription, "<CCGLProgram = %08X | Program = %i, VertexShader = %i, FragmentShader = %i>", this, program_, vertShader_, fragShader_);
	return strDescription;
}

bool CCGLProgram::compileShader(GLuint * shader, GLenum type, const GLchar* source)
{
    GLint status;
 
    if (!source)
        return false;

    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);

	if( ! status ) {
		if( type == GL_VERTEX_SHADER )
			CCLOG("cocos2d: %s", vertexShaderLog() );
		else
			CCLOG("cocos2d: %s", fragmentShaderLog() );

	}
    return ( status == GL_TRUE );
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

	this->use();
	this->setUniformLocationWith1i( uniforms_[kCCUniformSampler], 0 );
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
    return this->logForOpenGLObject(vertShader_, (GLInfoFunction)&glGetShaderiv, (GLLogFunction)&glGetShaderInfoLog);
}

const char* CCGLProgram::fragmentShaderLog()
{
	return this->logForOpenGLObject(fragShader_, (GLInfoFunction)&glGetShaderiv, (GLLogFunction)&glGetShaderInfoLog);
}

const char* CCGLProgram::programLog()
{
    return this->logForOpenGLObject(program_, (GLInfoFunction)&glGetProgramiv, (GLLogFunction)&glGetProgramInfoLog);
}

// Uniform cache

bool CCGLProgram::updateUniformLocation(unsigned int location, GLvoid* data, unsigned int bytes)
{
	bool updated = true;
	tHashUniformEntry *element = NULL;
	HASH_FIND_INT(hashForUniforms_, &location, element);

	if( ! element ) {

		element = (tHashUniformEntry*)malloc( sizeof(*element) );

		// key
		element->location = location;

		// value
		element->value = malloc( bytes );
		memcpy(element->value, data, bytes );

		HASH_ADD_INT(hashForUniforms_, location, element);
	}
	else
	{
		if( memcmp( element->value, data, bytes) == 0 )
			updated = false;
		else
			memcpy( element->value, data, bytes );
	}

	return updated;
}

void CCGLProgram::setUniformLocationWith1i(unsigned int location, GLint i1)
{
	bool updated =  updateUniformLocation(location, &i1, sizeof(i1)*1);

	if( updated )
		glUniform1i( (GLint)location, i1);
}

void CCGLProgram::setUniformLocationWith1f(unsigned int location, GLfloat f1)
{
	bool updated =  updateUniformLocation(location, &f1, sizeof(f1)*1);

	if( updated )
		glUniform1f( (GLint)location, f1);
}

void CCGLProgram::setUniformLocationWith2f(unsigned int location, GLfloat f1, GLfloat f2)
{
	GLfloat floats[2] = {f1,f2};
	bool updated =  updateUniformLocation(location, floats, sizeof(floats));

	if( updated )
		glUniform2f( (GLint)location, f1, f2);
}

void CCGLProgram::setUniformLocationWith3f(unsigned int location, GLfloat f1, GLfloat f2, GLfloat f3)
{
	GLfloat floats[3] = {f1,f2,f3};
	bool updated =  updateUniformLocation(location, floats, sizeof(floats));

	if( updated )
		glUniform3f( (GLint)location, f1, f2, f3);
}

void CCGLProgram::setUniformLocationWith4f(unsigned int location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
	GLfloat floats[4] = {f1,f2,f3,f4};
	bool updated =  updateUniformLocation(location, floats, sizeof(floats));

	if( updated )
		glUniform4f( (GLint)location, f1, f2, f3,f4);
}

void CCGLProgram::setUniformLocationWith2fv(unsigned int location, GLfloat* floats, unsigned int numberOfArrays)
{
	bool updated =  updateUniformLocation(location, floats, sizeof(float)*2*numberOfArrays);

	if( updated )
		glUniform2fv( (GLint)location, (GLsizei)numberOfArrays, floats );
}

void CCGLProgram::setUniformLocationWith3fv(unsigned int location, GLfloat* floats, unsigned int numberOfArrays)
{
	bool updated =  updateUniformLocation(location, floats, sizeof(float)*3*numberOfArrays);

	if( updated )
		glUniform3fv( (GLint)location, (GLsizei)numberOfArrays, floats );
}

void CCGLProgram::setUniformLocationWith4fv(unsigned int location, GLfloat* floats, unsigned int numberOfArrays)
{
	bool updated =  updateUniformLocation(location, floats, sizeof(float)*4*numberOfArrays);

	if( updated )
		glUniform4fv( (GLint)location, (GLsizei)numberOfArrays, floats );
}


void CCGLProgram::setUniformLocationwithMatrix4fv(unsigned int location, GLfloat* matrixArray, unsigned int numberOfMatrices)
{
	bool updated =  updateUniformLocation(location, matrixArray, sizeof(float)*16*numberOfMatrices);

	if( updated )
		glUniformMatrix4fv( (GLint)location, (GLsizei)numberOfMatrices, GL_FALSE, matrixArray);
}

void CCGLProgram::setUniformForModelViewProjectionMatrix()
{
	kmMat4 matrixP;
	kmMat4 matrixMV;
	kmMat4 matrixMVP;

	kmGLGetMatrix(KM_GL_PROJECTION, &matrixP );
	kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV );

	kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);

	setUniformLocationwithMatrix4fv(uniforms_[kCCUniformMVPMatrix], matrixMVP.mat, 1);
}

NS_CC_END
