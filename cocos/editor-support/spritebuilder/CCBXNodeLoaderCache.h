//
//  CCBXNodeLoaderCache.h
//  cocos2d_libs
//
//  Created by Sergey on 05.12.16.
//
//

#ifndef __cocos2d_libs__CCBXNodeLoaderCache__
#define __cocos2d_libs__CCBXNodeLoaderCache__

#include "base/CCRef.h"
#include "base/CCmap.h"
#include <functional>
#include <map>
#include <string>

NS_CC_BEGIN
namespace spritebuilder {
    
class NodeLoader;

class CC_DLL NodeLoaderCache : public Ref
{
public:
    static NodeLoaderCache *create();
    NodeLoader* get(const std::string &path) const;
    void add(const std::string &path, NodeLoader* loader);
    void clear();
    
    ~NodeLoaderCache();
    
CC_CONSTRUCTOR_ACCESS:
    NodeLoaderCache() {};
    
private:
    std::map<std::string, NodeLoader*> _loaders;
};
    
}

NS_CC_END

#endif /* defined(__cocos2d_libs__CCBXNodeLoaderCache__) */
