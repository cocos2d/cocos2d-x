/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __PHYSICSNODES_DEBUGNODE_H__
#define __PHYSICSNODES_DEBUGNODE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

#if CC_ENABLE_CHIPMUNK_INTEGRATION

#include "chipmunk.h"

NS_CC_EXT_BEGIN

/**
 A CCBaseData that draws the components of a physics engine.
 
 Supported physics engines:
 - Chipmunk
 - Objective-Chipmunk
 
 @since v2.1
 */

class CCPhysicsDebugNode : public CCDrawNode
{
protected:
    cpSpace *m_pSpacePtr;
    
public:
    /** Create a debug node for a regular Chipmunk space. */
    static CCPhysicsDebugNode* create(cpSpace *space);
    
    virtual ~CCPhysicsDebugNode();
    
    virtual void draw();
    
    cpSpace* getSpace() const;
    void setSpace(cpSpace *space);
    
    CCPhysicsDebugNode();
};

NS_CC_EXT_END

#endif // CC_ENABLE_CHIPMUNK_INTEGRATION

#endif // __PHYSICSNODES_DEBUGNODE_H__
