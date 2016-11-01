//
//  CCBXNodeLoaderLibrary.cpp
//  cocos2d_libs
//
//  Created by Sergey on 29.10.14.
//
//

#include "CCBXNodeLoaderCache.h"
#include "CCBXNodeLoader.h"

NS_CC_BEGIN
namespace spritebuilder {
    
NodeLoaderCache *NodeLoaderCache::create()
{
    NodeLoaderCache *ret = new(std::nothrow) NodeLoaderCache();
    ret->autorelease();
    return ret;
}
NodeLoader* NodeLoaderCache::get(const std::string &path) const
{
    auto it = _loaders.find(path);
    if(it == _loaders.end())
        return nullptr;
    else
        return it->second;
}
void NodeLoaderCache::add(const std::string &path, NodeLoader* loader)
{
    assert(loader);
    if(loader)
    {
        loader->retain();
        assert(_loaders.find(path) == _loaders.end());
        _loaders.emplace(path, loader);
    }
}
    
void NodeLoaderCache::clear()
{
    for(const auto &it:_loaders)
        it.second->release();
    _loaders.clear();
}
    
}

NS_CC_END
