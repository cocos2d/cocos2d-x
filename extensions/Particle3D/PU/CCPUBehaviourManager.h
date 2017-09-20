/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CC_PU_PARTICLE_3D_BEHAVIOUR_MANAGER_H__
#define __CC_PU_PARTICLE_3D_BEHAVIOUR_MANAGER_H__

#include "base/CCRef.h"
#include "extensions/Particle3D/PU/CCPUScriptTranslator.h"
#include "extensions/Particle3D/PU/CCPUBehaviour.h"
#include "extensions/Particle3D/PU/CCPUSlaveBehaviourTranslator.h"

using namespace std;
NS_CC_BEGIN

class PUBehaviourManager
{
public:
    
    static PUBehaviourManager* Instance();

    /**
     */
    PUScriptTranslator* getTranslator(const std::string &type);
    PUBehaviour* createBehaviour(const std::string &type);

    
CC_CONSTRUCTOR_ACCESS:
    PUBehaviourManager();
    ~PUBehaviourManager();

protected:

    PUSlaveBehaviourTranslator _slaveBehaviourTranslator;
};

NS_CC_END


#endif 
