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

#include "OpenGLESString.h"
#include <sstream>

using namespace OpenGLES;

OpenGLESString::OpenGLESString(const char *str) : string(str)
{
	
}

OpenGLESString::OpenGLESString(std::string str) : string(str)
{
	
}

OpenGLESString::OpenGLESString(int val) : string()
{
	std::stringstream out;
	out << val;
	string += out.str();
}

OpenGLESString OpenGLESString::operator+ (const char *val)
{
	return OpenGLESString(string + val);
}

OpenGLESString OpenGLESString::operator+ (std::string val)
{
	return OpenGLESString(string + val);
}

OpenGLESString OpenGLESString::operator+ (OpenGLESString val)
{
	return OpenGLESString(string + val());
}

OpenGLESString OpenGLESString::operator+ (int val)
{
	std::stringstream out;
	out << val;
	return OpenGLESString(string + out.str());
}

OpenGLESString OpenGLESString::operator+ (size_t val)
{
	std::stringstream out;
	out << (int)val;
	return OpenGLESString(string + out.str());
}

OpenGLESString OpenGLESString::operator+ (unsigned int val)
{
	std::stringstream out;
	out << val;
	return OpenGLESString(string + out.str());
}

OpenGLESString OpenGLESString::operator+ (float val)
{
	std::stringstream out;
	out << val;
	return OpenGLESString(string + out.str());
}

OpenGLESString OpenGLESString::operator+ (double val)
{
	std::stringstream out;
	out << val;
	return OpenGLESString(string + out.str());
}

std::string OpenGLESString::operator()()
{
	return string;
}
