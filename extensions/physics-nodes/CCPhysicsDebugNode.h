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

#include "extensions/ExtensionMacros.h"
#include "2d/CCDrawNode.h"

struct cpSpace;

NS_CC_EXT_BEGIN

/**
 A BaseData that draws the components of a physics engine.
 
 Supported physics engines:
 - Chipmunk
 - Objective-Chipmunk
 
 @since v2.1
 */

class PhysicsDebugNode : public DrawNode
{

public:
    /** Create a debug node for a regular Chipmunk space. */
    static PhysicsDebugNode* create(cpSpace *space);
    /**
     * @js ctor
     */
    PhysicsDebugNode();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~PhysicsDebugNode();
    

    cpSpace* getSpace() const;
    void setSpace(cpSpace *space);
    
    // Overrides
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

protected:
    cpSpace *_spacePtr;

};

NS_CC_EXT_END

#endif // __PHYSICSNODES_DEBUGNODE_H__
