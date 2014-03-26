/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CC_FRAMEWORK_COMPONENT_H__
#define __CC_FRAMEWORK_COMPONENT_H__

#include "CCRef.h"
#include "CCScriptSupport.h"
#include <string>

NS_CC_BEGIN

class Node;

enum {
    kComponentOnEnter,
    kComponentOnExit,
    kComponentOnUpdate
};

class CC_DLL Component : public Ref
{
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    Component(void);
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Component(void);
    virtual bool init();

    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    virtual bool serialize(void* r);
    virtual bool isEnabled() const;
    virtual void setEnabled(bool b);
    static Component* create(void);
    
    const std::string& getName() const;
    void setName(const std::string& name);
    
    void setOwner(Node *pOwner);
    Node* getOwner() const;

protected:
    Node *_owner;
    std::string _name;
    bool _enabled;
    
#if CC_ENABLE_SCRIPT_BINDING
    ccScriptType _scriptType;         ///< type of script binding, lua or javascript
#endif
};

NS_CC_END

#endif  // __FUNDATION__CCCOMPONENT_H__
