/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#ifndef _CCB_CCNODELOADERLIBRARY_H_
#define _CCB_CCNODELOADERLIBRARY_H_

#include "editor-support/cocosbuilder/CCBReader.h"

namespace cocosbuilder {

class NodeLoader;

typedef std::map<std::string, NodeLoader *> NodeLoaderMap;
typedef std::pair<std::string, NodeLoader *> NodeLoaderMapEntry;

class CC_DLL NodeLoaderLibrary : public cocos2d::Ref
{
public:
    /**
     * @js NA
     * @lua NA
     */
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(NodeLoaderLibrary, library);
    /**
     * @js NA
     * @lua NA
     */
    NodeLoaderLibrary();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~NodeLoaderLibrary();
    /**
     * @js NA
     * @lua NA
     */
    void registerDefaultNodeLoaders();
    /**
     * @js NA
     * @lua NA
     */
    void registerNodeLoader(const char * pClassName, NodeLoader * pNodeLoader);
    //void registerNodeLoader(String * pClassName, NodeLoader * pNodeLoader);
    /**
     * @js NA
     * @lua NA
     */
    void unregisterNodeLoader(const char * pClassName);
    //void unregisterNodeLoader(String * pClassName);
    /**
     * @js NA
     * @lua NA
     */
    NodeLoader * getNodeLoader(const char * pClassName);
    //CCNodeLoader * getNodeLoader(String * pClassName);
    /**
     * @js NA
     * @lua NA
     */
    void purge(bool pDelete);
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void registerDefaultCCNodeLoaders() { registerDefaultNodeLoaders(); }
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void registerCCNodeLoader(const char * pClassName, NodeLoader * pNodeLoader) { registerNodeLoader(pClassName, pNodeLoader); };
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE void unregisterCCNodeLoader(const char * pClassName) { unregisterNodeLoader(pClassName); };
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE NodeLoader * getCCNodeLoader(const char * pClassName) { return getNodeLoader(pClassName); };
    
public:
    /**
     * @js NA
     * @lua NA
     */
    static NodeLoaderLibrary * getInstance();
    /**
     * @js NA
     * @lua NA
     */
    static void destroyInstance();
    /**
     * @js NA
     * @lua NA
     */
    static NodeLoaderLibrary * newDefaultNodeLoaderLibrary();
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static NodeLoaderLibrary * sharedNodeLoaderLibrary() { return NodeLoaderLibrary::getInstance(); };
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedNodeLoaderLibrary() { NodeLoaderLibrary::destroyInstance(); };
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static NodeLoaderLibrary * newDefaultCCNodeLoaderLibrary() { return NodeLoaderLibrary::newDefaultNodeLoaderLibrary(); };
    
private:
    NodeLoaderMap _nodeLoaders;
};

}

#endif
