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

#ifndef OpenGLESConfig_H__
#define OpenGLESConfig_H__

#define OPENGLES_DEBUG 1

#include <string>

namespace OpenGLES {

class OpenGLESConfig
{
public:
	static const bool USE_ONLY_UBER_SHADER;
	static const bool DEBUG;
};
	
}

#endif
